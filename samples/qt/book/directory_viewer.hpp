#ifndef DIRECTORY_VIEWER_HPP
#define DIRECTORY_VIEWER_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class directory_viewer : public dialog, public method_binder <directory_viewer>
{
	typedef directory_viewer T;
	using method_binder <T>::bind;

	tree_view *tree;
	dir_model *model;
	dialog_button_box *button_box;

	slot <void()> create_directory, remove;

public:

//-----------------------------------------------------------------------------

	directory_viewer(QWidget *parent = 0) : dialog(parent)
	{
		bind(create_directory).to <&T::create_directory_>();
		bind(remove)          .to <&T::remove_>();

//-----------------------------------------------------------------------------

		model = new dir_model;
		model->setReadOnly(false);
		model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

		tree = new tree_view;
		tree->setModel(model);
		tree->header()->setStretchLastSection(true);
		tree->header()->setSortIndicator(0, Qt::AscendingOrder);
		tree->header()->setSortIndicatorShown(true);
		tree->header()->setClickable(true);

		QModelIndex index = model->index(QDir::currentPath());
		tree->expand(index);
		tree->scrollTo(index);
		tree->resizeColumnToContents(0);

		push_button *mkdir_button  = new push_button(tr("&Create Directory..."));
		push_button *remove_button = new push_button(tr("&Remove"));

		button_box = new dialog_button_box(Qt::Horizontal);
		button_box->addButton(mkdir_button,  dialog_button_box::ActionRole);
		button_box->addButton(remove_button, dialog_button_box::ActionRole);
		button_box->addButton(tr("&Quit"),   dialog_button_box::AcceptRole);

		mkdir_button->clicked.connect(create_directory);
		remove_button->clicked.connect(remove);
		button_box->accepted.connect(accept);

//-----------------------------------------------------------------------------

		col_layout *layout = new col_layout(this);
		*layout << tree << button_box;

		setWindowTitle(tr("Directory Viewer"));
	}

private:

//-----------------------------------------------------------------------------

	void create_directory_()
	{
		QModelIndex index = tree->currentIndex();
		if (!index.isValid())
			return;

		QString dir_name = input_dialog::getText(this,
			tr("Create Directory"),
			tr("Directory name"));
		if (!dir_name.isEmpty())
			if (!model->mkdir(index, dir_name).isValid())
				message_box::information(this, tr("Create Directory"),
					tr("Failed to create the directory"));
	}

	void remove_()
	{
		QModelIndex index = tree->currentIndex();
		if (!index.isValid())
			return;

		bool ok;
		ok = model->fileInfo(index).isDir() ?
			model->rmdir(index) : model->remove(index);
		if (!ok)
			message_box::information(this, tr("Remove"),
				tr("Failed to remove %1").arg(model->fileName(index)));
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // DIRECTORY_VIEWER_HPP
