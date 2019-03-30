#ifndef TEAM_LEADERS_HPP
#define TEAM_LEADERS_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class team_leaders_dialog : public dialog,
	public method_binder <team_leaders_dialog>
{
	typedef team_leaders_dialog T;
	using method_binder <T>::bind;

	list_view         *view;
	string_list_model *model;
	dialog_button_box *button_box;

	slot <void ()> insert, del;

public:

//-----------------------------------------------------------------------------

	team_leaders_dialog(const QStringList &leaders, QWidget *parent = 0)
		: dialog(parent)
	{
		bind(insert).to <&T::insert_>();
		bind(del)   .to <&T::del_>();

//-----------------------------------------------------------------------------

		model = new string_list_model(this);
		model->setStringList(leaders);

		view = new list_view;
		view->setModel(model);
		view->setEditTriggers
			(QAbstractItemView::AnyKeyPressed | QAbstractItemView::DoubleClicked);

		push_button *insert_button = new push_button(tr("&Insert")),
		            *delete_button = new push_button(tr("&Delete"));

		button_box = new dialog_button_box;
		button_box->addButton(insert_button, dialog_button_box::ActionRole);
		button_box->addButton(delete_button, dialog_button_box::ActionRole);
		*button_box << dialog_button_box::Ok << dialog_button_box::Cancel;

		insert_button->clicked.connect(insert);
		delete_button->clicked.connect(del);
		button_box->accepted.connect(accept);
		button_box->rejected.connect(reject);

//-----------------------------------------------------------------------------

		col_layout *layout = new col_layout(this);
		*layout << view << button_box;

		setWindowTitle(tr("Team Leaders"));
	}

//-----------------------------------------------------------------------------

	QStringList leaders() const
	{
		return model->stringList();
	}

private:

//-----------------------------------------------------------------------------

	void insert_()
	{
		int row = view->currentIndex().row();
		model->insertRows(row, 1);

		QModelIndex index = model->index(row);
		view->setCurrentIndex(index);
		view->edit(index);
	}

	void del_()
	{
		model->removeRows(view->currentIndex().row(), 1);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // TEAM_LEADERS_HPP
