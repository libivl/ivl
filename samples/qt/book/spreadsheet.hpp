#ifndef SPREADSHEET_HPP
#define SPREADSHEET_HPP

#include "spreadsheet_cell.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

struct spreadsheet_compare
{
	enum { key_count = 3 };
	int keys[key_count];
	bool ascending[key_count];

//-----------------------------------------------------------------------------

	bool operator()(const QStringList &row1, const QStringList &row2) const
	{
		for (int i = 0; i < key_count; ++i)
		{
			int column = keys[i];
			if (column != -1 && row1[column] != row2[column])
				return ascending[i] ? row1[column] < row2[column] :
				                      row1[column] > row2[column];
		}
		return false;
	}

};

//-----------------------------------------------------------------------------

class spreadsheet : public table_widget,
	public method_binder <spreadsheet>
{
	typedef spreadsheet T;
	using method_binder <T>::bind;

	enum { magic_number = 0x7F51C883, row_count = 999, column_count = 26 };
	bool auto_recalc;

	slot <void ()> something_changed;

public:

	signal <void ()> modified;

	slot <void ()> cut, copy, paste, del;
	slot <void ()> select_current_row, select_current_column;
	slot <void ()> recalc;
	slot <void (bool)> set_auto_recalc;
	slot <void (const QString&, Qt::CaseSensitivity)> find_next, find_prev;

//-----------------------------------------------------------------------------

	spreadsheet(QWidget *parent = 0) : table_widget(parent)
	{
		bind(something_changed)      .to <&T::something_changed_>();
		bind(cut)                    .to <&T::cut_>();
		bind(copy)                   .to <&T::copy_>();
		bind(paste)                  .to <&T::paste_>();
		bind(del)                    .to <&T::del_>();
		bind(select_current_row)     .to <&T::select_current_row_>();
		bind(select_current_column)  .to <&T::select_current_column_>();
		bind(recalc)                 .to <&T::recalc_>();
		bind(set_auto_recalc)        .to <&T::set_auto_recalc_>();
		bind(find_next)              .to <&T::find_next_>();
		bind(find_prev)              .to <&T::find_prev_>();

		item_changed.connect(something_changed);

		auto_recalc = true;
		setItemPrototype(new spreadsheet_cell);
		setSelectionMode(ContiguousSelection);
		clear();
	}

//-----------------------------------------------------------------------------

	bool auto_recalculate() const { return auto_recalc; }

	QString current_location() const
	{
		return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
	}

	QString current_formula() const
	{
		return formula(currentRow(), currentColumn());
	}

	QTableWidgetSelectionRange selected_range() const
	{
		QList <QTableWidgetSelectionRange> ranges = selectedRanges();
		if (ranges.isEmpty())
			return QTableWidgetSelectionRange();
		return ranges.first();
	}

//-----------------------------------------------------------------------------

	void clear()
	{
		setRowCount(0);
		setColumnCount(0);
		setRowCount(row_count);
		setColumnCount(column_count);

		for (int i = 0; i < column_count; ++i)
		{
			QTableWidgetItem *item = new QTableWidgetItem;
			item->setText(QString(QChar('A' + i)));
			setHorizontalHeaderItem(i, item);
		}

		setCurrentCell(0, 0);
	}

//-----------------------------------------------------------------------------

	bool read_file(const QString &fileName)
	{
		QFile file(fileName);
		if (!file.open(QIODevice::ReadOnly))
		{
			QMessageBox::warning(this, tr("Spreadsheet"),
										tr("Cannot read file %1:\n%2.")
										.arg(file.fileName())
										.arg(file.errorString()));
			return false;
		}

		QDataStream in(&file);
		in.setVersion(QDataStream::Qt_4_3);

		quint32 magic;
		in >> magic;
		if (magic != magic_number)
		{
			QMessageBox::warning(this, tr("Spreadsheet"),
										tr("The file is not a Spreadsheet file."));
			return false;
		}

		clear();

		quint16 row;
		quint16 column;
		QString str;

		application::setOverrideCursor(Qt::WaitCursor);
		while (!in.atEnd())
		{
			in >> row >> column >> str;
			set_formula(row, column, str);
		}
		application::restoreOverrideCursor();
		return true;
	}

//-----------------------------------------------------------------------------

	bool write_file(const QString &fileName)
	{
		QFile file(fileName);
		if (!file.open(QIODevice::WriteOnly))
		{
			QMessageBox::warning(this, tr("Spreadsheet"),
										tr("Cannot write file %1:\n%2.")
										.arg(file.fileName())
										.arg(file.errorString()));
			return false;
		}

		QDataStream out(&file);
		out.setVersion(QDataStream::Qt_4_3);

		out << quint32(magic_number);

		application::setOverrideCursor(Qt::WaitCursor);
		for (int row = 0; row < row_count; ++row)
			for (int column = 0; column < column_count; ++column)
			{
				QString str = formula(row, column);
				if (!str.isEmpty())
					out << quint16(row) << quint16(column) << str;
			}
		application::restoreOverrideCursor();
		return true;
	}

//-----------------------------------------------------------------------------

	void sort(const spreadsheet_compare &compare)
	{
		QList<QStringList> rows;
		QTableWidgetSelectionRange range = selected_range();
		int i;

		for (i = 0; i < range.rowCount(); ++i)
		{
			QStringList row;
			for (int j = 0; j < range.columnCount(); ++j)
				row.append(formula(range.topRow() + i,
										 range.leftColumn() + j));
			rows.append(row);
		}

		qStableSort(rows.begin(), rows.end(), compare);

		for (i = 0; i < range.rowCount(); ++i)
			for (int j = 0; j < range.columnCount(); ++j)
				set_formula(range.topRow() + i, range.leftColumn() + j, rows[i][j]);

		clearSelection();
		something_changed();
	}

private:

//-----------------------------------------------------------------------------

	void something_changed_()
	{
		if (auto_recalc)
			recalc();
		emit modified();
		viewport()->update();
	}

//-----------------------------------------------------------------------------

	void cut_() { copy(); del(); }

//-----------------------------------------------------------------------------

	void copy_()
	{
		QTableWidgetSelectionRange range = selected_range();
		QString str;

		for (int i = 0; i < range.rowCount(); ++i)
		{
			if (i > 0) str += "\n";
			for (int j = 0; j < range.columnCount(); ++j)
			{
				if (j > 0) str += "\t";
				str += formula(range.topRow() + i, range.leftColumn() + j);
			}
		}
		application::clipboard()->setText(str);
	}

//-----------------------------------------------------------------------------

	void paste_()
	{
		QTableWidgetSelectionRange range = selected_range();
		QString str = application::clipboard()->text();
		QStringList rows = str.split('\n');
		int numRows = rows.count();
		int numColumns = rows.first().count('\t') + 1;

		if (range.rowCount() * range.columnCount() != 1
					&& (range.rowCount() != numRows
					|| range.columnCount() != numColumns))
		{
			QMessageBox::information(this, tr("Spreadsheet"),
						tr("The information cannot be pasted because the copy "
							"and paste areas aren't the same size."));
			return;
		}

		for (int i = 0; i < numRows; ++i)
		{
			QStringList columns = rows[i].split('\t');
			for (int j = 0; j < numColumns; ++j)
			{
				int row = range.topRow() + i;
				int column = range.leftColumn() + j;
				if (row < row_count && column < column_count)
					set_formula(row, column, columns[j]);
			}
		}
		something_changed();
	}

//-----------------------------------------------------------------------------

	void del_()
	{
		QList<QTableWidgetItem *> items = selectedItems();
		if (!items.isEmpty())
		{
			foreach (QTableWidgetItem *item, items)
				delete item;
			something_changed();
		}
	}

//-----------------------------------------------------------------------------

	void select_current_row_()    { selectRow(currentRow()); }
	void select_current_column_() { selectColumn(currentColumn()); }

//-----------------------------------------------------------------------------

	void recalc_()
	{
		for (int row = 0; row < row_count; ++row)
			for (int column = 0; column < column_count; ++column)
				if (cell(row, column))
					cell(row, column)->set_dirty();
		viewport()->update();
	}

//-----------------------------------------------------------------------------

	void set_auto_recalc_(bool auto_recalc)
	{
		this->auto_recalc = auto_recalc;
		if (auto_recalc)
			recalc();
	}

//-----------------------------------------------------------------------------

	void find_next_(const QString &str, Qt::CaseSensitivity cs)
	{
		int row = currentRow();
		int column = currentColumn() + 1;

		while (row < row_count)
		{
			while (column < column_count)
			{
				if (text(row, column).contains(str, cs))
				{
					clearSelection();
					setCurrentCell(row, column);
					activateWindow();
					return;
				}
				++column;
			}
			column = 0;
			++row;
		}
		application::beep();
	}

//-----------------------------------------------------------------------------

	void find_prev_(const QString &str, Qt::CaseSensitivity cs)
	{
		int row = currentRow();
		int column = currentColumn() - 1;

		while (row >= 0)
		{
			while (column >= 0)
			{
				if (text(row, column).contains(str, cs))
				{
					clearSelection();
					setCurrentCell(row, column);
					activateWindow();
					return;
				}
				--column;
			}
			column = column_count - 1;
			--row;
		}
		application::beep();
	}

//-----------------------------------------------------------------------------

	spreadsheet_cell* cell(int row, int column) const
	{
		return static_cast <spreadsheet_cell*>(item(row, column));
	}

	void set_formula(int row, int column, const QString &formula)
	{
		spreadsheet_cell* c = cell(row, column);
		if (!c)
		{
			c = new spreadsheet_cell;
			setItem(row, column, c);
		}
		c->set_formula(formula);
	}

	QString formula(int row, int column) const
	{
		spreadsheet_cell* c = cell(row, column);
		if (c)
			return c->formula();
		else
			return "";
	}

	QString text(int row, int column) const
	{
		spreadsheet_cell* c = cell(row, column);
		if (c)
			return c->text();
		else
			return "";
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // SPREADSHEET_HPP
