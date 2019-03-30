#ifndef SETTINGS_VIEWER_HPP
#define SETTINGS_VIEWER_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class settings_viewer : public dialog,
	public method_binder <settings_viewer>
{
	typedef settings_viewer T;
	using method_binder <T>::bind;

	tree_widget       *tree;
	dialog_button_box *button_box;

	QString organization;
	QString application;

	slot <void ()> open;

public:

//-----------------------------------------------------------------------------

	settings_viewer(QWidget *parent = 0): dialog(parent)
	{
		bind(open).to <&T::open_>();

//-----------------------------------------------------------------------------

		tree = new tree_widget;
		tree->setColumnCount(2);
		tree->setHeaderLabels(QStringList() << tr("Key") << tr("Value"));
		tree->header()->setResizeMode(0, QHeaderView::Stretch);
		tree->header()->setResizeMode(1, QHeaderView::Stretch);

		button_box = new dialog_button_box
			(dialog_button_box::Open | dialog_button_box::Close);

		button_box->accepted.connect(open);
		button_box->rejected.connect(close);

//-----------------------------------------------------------------------------

		col_layout *layout = new col_layout(this);
		*layout << tree << button_box;

		setWindowTitle(tr("Settings Viewer"));

//-----------------------------------------------------------------------------

		organization = "Trolltech";
		application = "Designer";
		read_settings();
	}

private:

//-----------------------------------------------------------------------------

	void open_()
	{
		dialog d(this);

		label *org_label = new label(tr("&Organization:")),
		      *app_label = new label(tr("&Application:"));

		line_edit *org_edit  = new line_edit(organization),
		          *app_edit  = new line_edit(application);

		org_label->setBuddy(org_edit);
		app_label->setBuddy(app_edit);

		dialog_button_box *button_box = new dialog_button_box
			(dialog_button_box::Ok | dialog_button_box::Cancel);

		button_box->accepted.connect(d.accept);
		button_box->rejected.connect(d.reject);

//-----------------------------------------------------------------------------

		grid_layout *grid = new grid_layout(&d);
		*grid << org_label << org_edit << nl
		      << app_label << app_edit << nl
		      << col_span(2)(button_box);

		d.setWindowTitle(tr("Choose Settings"));

		if (d.exec())
		{
			organization = org_edit->text();
			application = app_edit->text();
			read_settings();
		}
	}

//-----------------------------------------------------------------------------

	void read_settings()
	{
		QSettings settings(organization, application);

		tree->clear();
		add_child_settings(settings, 0, "");

		tree->sortByColumn(0);
		tree->setFocus();
		setWindowTitle(tr("Settings Viewer - %1 by %2")
			.arg(application).arg(organization));
	}

//-----------------------------------------------------------------------------

	void add_child_settings(QSettings &settings, QTreeWidgetItem *parent,
									const QString &group)
	{
		if (!parent)
			parent = tree->invisibleRootItem();

		QTreeWidgetItem *item;
		settings.beginGroup(group);

		foreach (QString key, settings.childKeys())
		{
			item = new QTreeWidgetItem(parent);
			item->setText(0, key);
			item->setText(1, settings.value(key).toString());
		}

		foreach (QString group, settings.childGroups())
		{
			item = new QTreeWidgetItem(parent);
			item->setText(0, group);
			add_child_settings(settings, item, group);
		}

		settings.endGroup();
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // SETTINGS_VIEWER_HPP
