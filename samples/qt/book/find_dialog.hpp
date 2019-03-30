#ifndef FIND_DIALOG_HPP
#define FIND_DIALOG_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class find_dialog : public dialog, public method_binder <find_dialog>
{
	typedef find_dialog T;
	using method_binder <T>::bind;

private:

	label         *what_label;
	line_edit     *what_edit;
	check_box     *case_box, *back_box;
	push_button   *find_button, *close_button;

public:

//-----------------------------------------------------------------------------

	signal <void (const QString&, Qt::CaseSensitivity)> find_next;
	signal <void (const QString&, Qt::CaseSensitivity)> find_prev;

	slot <void ()>                find_clicked;
	slot <void (const QString&)>  enable_find;

//-----------------------------------------------------------------------------

	find_dialog(QWidget* parent = 0) : dialog(parent)
	{
		bind(find_clicked)  .to <&T::find_clicked_>();
		bind(enable_find)   .to <&T::enable_find_>();

//-----------------------------------------------------------------------------

		what_label = new label(tr("Find &what:"));
		what_edit = new line_edit;
		what_label->setBuddy(what_edit);

		case_box = new check_box(tr("Match &case"));
		back_box = new check_box(tr("Search &backward"));

		find_button = new push_button(tr("&Find"));
		find_button->setDefault(true);
		find_button->setEnabled(false);

		close_button = new push_button(tr("Close"));

		what_edit->text_changed.connect(enable_find);
		find_button->clicked.connect(find_clicked);
		close_button->clicked.connect(close);

//-----------------------------------------------------------------------------

		row_layout* top_left_layout = new row_layout;
		*top_left_layout << what_label << what_edit;

		col_layout* left_layout = new col_layout;
		*left_layout << top_left_layout << case_box << back_box;

		col_layout* right_layout = new col_layout;
		*right_layout << find_button << close_button << stretch;

		row_layout* main_layout = new row_layout;
		*main_layout << left_layout << right_layout;

		setLayout(main_layout);
		setWindowTitle(tr("Find"));
		setFixedHeight(sizeHint().height());
	}

private:

//-----------------------------------------------------------------------------

	void find_clicked_()
	{
		QString text = what_edit->text();
		Qt::CaseSensitivity cs =
			case_box->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
		back_box->isChecked() ?
			find_prev(text, cs) : find_next(text, cs);
	}

//-----------------------------------------------------------------------------

	void enable_find_(const QString &text)
	{
		find_button->setEnabled(!text.isEmpty());
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // FIND_DIALOG_HPP
