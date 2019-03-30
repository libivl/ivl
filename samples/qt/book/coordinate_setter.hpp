#ifndef COORDINATE_SETTER_HPP
#define COORDINATE_SETTER_HPP

#include <vector>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using namespace std;

//-----------------------------------------------------------------------------

class coordinate_setter : public dialog,
	public method_binder <coordinate_setter>
{
	typedef coordinate_setter T;
	using method_binder <T>::bind;

	table_widget      *table;
	push_button       *add_row_button;
	dialog_button_box *button_box;
	vector <QPointF>  *coordinates;

	slot <void ()> add_row;

public:

//-----------------------------------------------------------------------------

	coordinate_setter(vector <QPointF>* coords, QWidget *parent = 0) :
		dialog(parent), coordinates(coords)
	{
		bind(add_row).to <T, &T::add_row_>();

//-----------------------------------------------------------------------------

		table = new table_widget(0, 2);
		table->setHorizontalHeaderLabels(QStringList() << tr("X") << tr("Y"));

		for (int row = 0; row < coordinates->size(); ++row)
		{
			add_row_(false);
			QPointF point = (*coordinates)[row];
			table->item(row, 0)->setText(QString::number(point.x()));
			table->item(row, 1)->setText(QString::number(point.y()));
		}

		add_row_button = new push_button(tr("&Add Row"));
		button_box = new dialog_button_box(Qt::Horizontal);
		button_box->addButton(add_row_button, dialog_button_box::ActionRole);
		*button_box << dialog_button_box::Ok << dialog_button_box::Cancel;

		add_row_button->clicked.connect(add_row);
		button_box->accepted.connect(accept);
		button_box->rejected.connect(reject);

//-----------------------------------------------------------------------------

		col_layout *layout = new col_layout(this);
		*layout << table << button_box;

		setWindowTitle(tr("Coordinate Setter"));
	}

//-----------------------------------------------------------------------------

	void done(int result)
	{
		if (result == dialog::Accepted)
		{
			coordinates->clear();
			for (int row = 0; row < table->rowCount(); ++row)
			{
				double x = table->item(row, 0)->text().toDouble();
				double y = table->item(row, 1)->text().toDouble();
				coordinates->push_back(QPointF(x, y));
			}
		}
		QDialog::done(result);  // TODO: reimplement all QDialog virtual methods in dialog
	}

private:

//-----------------------------------------------------------------------------

	void add_row_() { add_row_(true); }

	void add_row_(bool edit)
	{
		int row = table->rowCount();
		table->insertRow(row);

		QTableWidgetItem *item0 = new QTableWidgetItem;
		item0->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		table->setItem(row, 0, item0);

		QTableWidgetItem *item1 = new QTableWidgetItem;
		item1->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
		table->setItem(row, 1, item1);

		table->setCurrentItem(item0);
		if (edit)
			table->editItem(item0);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // COORDINATE_SETTER_HPP
