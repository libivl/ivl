#ifndef SORT_DIALOG_H
#define SORT_DIALOG_H

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using ivl::left;
using ivl::right;
using ivl::center;
using ivl::middle;

//-----------------------------------------------------------------------------

class sort_dialog : public dialog
{
	enum { key_count = 3 };

	group_box    *sort_box[key_count];
	label        *column_label[key_count], *order_label[key_count];
	combo_box    *column_combo[key_count], *order_combo[key_count];

	push_button  *ok, *cancel, *more;

	col_layout   *button_layout;
	grid_layout  *sort_layout[key_count], *main_layout;

public:

//-----------------------------------------------------------------------------

	sort_dialog(QWidget *parent = 0) : dialog(parent)
	{
		sort_box[0] = new group_box(tr("&Primary Key"));
		sort_box[1] = new group_box(tr("&Secondary Key"));
		sort_box[2] = new group_box(tr("&Tertiary Key"));
		sort_box[1]->hide();
		sort_box[2]->hide();

		for (int i = 0; i < key_count; i++)
		{
			column_label[i] = new label(tr("Column:"));
			column_combo[i] = new combo_box();
			order_label[i]  = new label(tr("Order:"));
			order_combo[i]  = new combo_box();
			order_combo[i] -> addItem(tr("Ascending"));
			order_combo[i] -> addItem(tr("Descending"));
		}

		ok     = new push_button(tr("OK"));
		ok    -> setDefault(true);
		cancel = new push_button(tr("Cancel"));
		more   = new push_button(tr("&More"));
		more  -> setCheckable(true);

		more->toggled.connect(sort_box[1]->set_visible);
		more->toggled.connect(sort_box[2]->set_visible);
		ok->clicked.connect(accept);
		cancel->clicked.connect(reject);

//-----------------------------------------------------------------------------

		for (int i = 0; i < key_count; i++)
		{
			sort_layout[i] = new grid_layout(sort_box[i]);
			*sort_layout[i] << column_label[i] << column_combo[i] << col_stretch(1) << nl
			                << order_label[i]  << col_span(2)(order_combo[i]);
		}

		button_layout = new col_layout;
		*button_layout << ok << cancel << stretch << more;

		main_layout = new grid_layout(this);
		main_layout->setSizeConstraint(QLayout::SetFixedSize);
		*main_layout << sort_box[0]    << button_layout << nl
						 << sort_box[1]                     << nl
						 << sort_box[2]                     << nl
		             << row_stretch(1);

		tab_order << column_combo[0] << order_combo[0]
		          << column_combo[1] << order_combo[1]
		          << column_combo[2] << order_combo[2]
		          << ok << cancel << more;

		setWindowTitle(tr("Sort"));
		set_column_range('A', 'Z');
	}

//-----------------------------------------------------------------------------

	int column(int i) const
	{
		return i ? column_combo[i]->currentIndex() - 1 :
		           column_combo[i]->currentIndex();
	}

	bool ascending(int i) const { return order_combo[i]->currentIndex() == 0; }

//-----------------------------------------------------------------------------

	void set_column_range(QChar first, QChar last)
	{
		for (int i = 0; i < key_count; i++)
			column_combo[i]->clear();

		*column_combo[1] << tr("None");
		*column_combo[2] << tr("None");
		column_combo[0]->setMinimumSize(column_combo[1]->sizeHint());

		for (QChar ch = first; ch <= last; ch = ch.unicode() + 1)
			for (int i = 0; i < key_count; i++)
				column_combo[i]->addItem(QString(ch));
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // SORT_DIALOG_H
