#ifndef GOTO_CELL_DIALOG_HPP
#define GOTO_CELL_DIALOG_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class goto_cell_dialog : public dialog, public method_binder <goto_cell_dialog>
{
	typedef goto_cell_dialog T;
	using method_binder <T>::bind;

private:

	label*             cell_label;
	line_edit*         cell_edit;
	dialog_button_box* button_box;

public:

//-----------------------------------------------------------------------------

	slot <void (const QString&)> cell_changed;

//-----------------------------------------------------------------------------

	goto_cell_dialog(QWidget *parent = 0) : dialog(parent)
	{
		bind(cell_changed).to <&T::cell_changed_>();

//-----------------------------------------------------------------------------

		QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
		cell_edit = new line_edit;
		cell_edit->setValidator(new QRegExpValidator(regExp, this));

		cell_label = new label(tr("&Cell Location:"));
#ifndef QT_NO_SHORTCUT
		cell_label->setBuddy(cell_edit);
#endif

		button_box = new dialog_button_box;
		button_box->setOrientation(Qt::Horizontal);
		button_box->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);
		button_box->button(QDialogButtonBox::Ok)->setEnabled(false);

		button_box->accepted.connect(accept);
		button_box->rejected.connect(reject);
		cell_edit->text_changed.connect(cell_changed);

//-----------------------------------------------------------------------------

		row_layout* cell_layout = new row_layout;
		*cell_layout << cell_label << cell_edit;

		col_layout* goto_layout = new col_layout;
		*goto_layout << cell_layout << button_box;

		setLayout(goto_layout);
		setWindowTitle(tr("Go to Cell"));
	}

//-----------------------------------------------------------------------------

	QString cell() const { return cell_edit->text(); }

private:

//-----------------------------------------------------------------------------

	void cell_changed_(const QString&)
	{
		button_box->button(QDialogButtonBox::Ok)->
			setEnabled(cell_edit->hasAcceptableInput());
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // GOTO_CELL_DIALOG_HPP
