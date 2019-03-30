#ifndef FIND_FILE_DIALOG_HPP
#define FIND_FILE_DIALOG_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class find_file_dialog : public dialog
{
	label *named_label, *look_in_label;
	line_edit *look_in_edit, *named_edit;
	check_box *subfolders_check;
	table_widget *table;
	label *message_label;
	push_button *find_button;
	push_button *stop_button;
	push_button *close_button;
	push_button *help_button;

public:

//-----------------------------------------------------------------------------

	find_file_dialog(QWidget *parent = 0) : dialog(parent)
	{
		named_label = new label(tr("&Named:"));
		named_edit = new line_edit;
		named_label->setBuddy(named_edit);

		look_in_label = new label(tr("&Look in:"));
		look_in_edit = new line_edit;
		look_in_label->setBuddy(look_in_edit);

		subfolders_check = new check_box(tr("Include subfolders"));

		QStringList labels;
		labels << tr("Name") << tr("In Folder") << tr("Size") << tr("Modified");

		table = new table_widget;
		table->setColumnCount(4);
		table->setHorizontalHeaderLabels(labels);

		message_label = new label(tr("0 files found"));
		message_label->setFrameShape(label::Panel);
		message_label->setFrameShadow(label::Sunken);

		find_button  = new push_button(tr("&Find"));
		stop_button  = new push_button(tr("Stop"));
		close_button = new push_button(tr("Close"));
		help_button  = new push_button(tr("Help"));

		close_button->clicked.connect(close);

//-----------------------------------------------------------------------------

		grid_layout *left_layout = new grid_layout;
		*left_layout << named_label    << named_edit    << nl
		             << look_in_label  << look_in_edit  << nl
		             << col_span(2)(subfolders_check)   << nl
		             << col_span(2)(table)              << nl
		             << col_span(2)(message_label);

		col_layout *right_layout = new col_layout;
		*right_layout << find_button << stop_button << close_button
		              << stretch     << help_button;

		row_layout *main_layout = new row_layout(this);
		*main_layout << left_layout << right_layout;

		setWindowTitle(tr("Find Files or Folders"));
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // FIND_FILE_DIALOG_HPP
