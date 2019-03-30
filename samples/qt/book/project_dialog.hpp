#ifndef PROJECT_DIALOG_HPP
#define PROJECT_DIALOG_HPP

#include "project_list.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using ivl::center;

//-----------------------------------------------------------------------------

class project_dialog : public dialog, public method_binder <project_dialog>
{
	typedef project_dialog T;
	using method_binder <T>::bind;

	label        *label_A, *label_B;
	project_list *proj_A, *proj_B;
	tool_button  *left_button, *right_button;

public:

	slot <void ()> move_left, move_right;

//-----------------------------------------------------------------------------

	project_dialog(QWidget* parent = 0) : dialog(parent)
	{
		bind(move_left) .to <&T::move_left_>();
		bind(move_right).to <&T::move_right_>();

//-----------------------------------------------------------------------------

		label_A = new label(tr("Project A"));
		label_B = new label(tr("Project B"));

		proj_A = new project_list;
		proj_B = new project_list;

		*proj_A << "Giosue Carducci" << "Eyvind Johnson" << "Sally Prudhomme"
		        << "Henryk Sienkiewicz" << "Carl Spitteler"
		        << "Rabindranath Tagore" << "Kawabata Yasunari";

		*proj_B << "Rudolf Eucken" << "Anatole France" << "Rudyard Kipling"
		        << "Thomas Mann" << "Eugene O'Neill" << "Sigrid Undset";

		left_button  = new tool_button(QIcon(":/project_images/left_arrow.png"));
		right_button = new tool_button(QIcon(":/project_images/right_arrow.png"));

		left_button->clicked.connect(move_left);
		right_button->clicked.connect(move_right);

//-----------------------------------------------------------------------------

		grid_layout *layout = new grid_layout(this);
		*layout
			<< center(label_A)     << tab            << center(label_B)     << nl
			<< row_span(4)(proj_A) << row_stretch(1) << row_span(4)(proj_B) << nl
			<< tab                 << left_button                           << nl
			<< tab                 << right_button                          << nl
			<< tab                 << row_stretch(1);

		setWindowTitle(tr("Choose Project"));
	}

private:

//-----------------------------------------------------------------------------

	void move_left_()  { move_item(proj_B, proj_A); }
	void move_right_() { move_item(proj_A, proj_B); }

	void move_item(project_list* source, project_list* target)
	{
		if (source->currentItem())
		{
			QListWidgetItem *newItem = source->currentItem()->clone();
			target->addItem(newItem);
			target->setCurrentItem(newItem);
			delete source->currentItem();
		}
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // PROJECT_DIALOG_HPP
