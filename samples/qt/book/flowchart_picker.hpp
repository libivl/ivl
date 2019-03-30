#ifndef FLOWCHART_PICKER_HPP
#define FLOWCHART_PICKER_HPP

#include <map>

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using namespace std;

//-----------------------------------------------------------------------------

class flowchart_picker : public dialog
{
	list_widget       *list;
	dialog_button_box *button_box;
	int id;

public:

//-----------------------------------------------------------------------------

	flowchart_picker(const map <int, QString>& symbol_map, QWidget *parent = 0)
		: dialog(parent)
	{
		id = -1;

		list = new list_widget;
		list->setIconSize(QSize(30, 30));

		typedef typename map <int, QString>::const_iterator I;
		for (I i = symbol_map.begin(); i != symbol_map.end(); i++)
		{
			QListWidgetItem* item = new QListWidgetItem(i->second, list);
			item->setIcon(symbol_icon(i->second));
			item->setData(Qt::UserRole, i->first);
		}

		button_box = new dialog_button_box
			(dialog_button_box::Ok | dialog_button_box::Cancel);

		button_box->accepted.connect(accept);
		button_box->rejected.connect(reject);

//-----------------------------------------------------------------------------

		col_layout *layout = new col_layout(this);
		*layout << list << button_box;

		setWindowTitle(tr("Flowchart Symbol Picker"));
	}

//-----------------------------------------------------------------------------

	int selected_id() const { return id; }

	void done(int result)
	{
		id = -1;
		if (result == dialog::Accepted)
		{
			QListWidgetItem *item = list->currentItem();
			if (item)
				id = item->data(Qt::UserRole).toInt();
		}
		QDialog::done(result);  // TODO: reimplement all QDialog virtual methods in dialog
	}

private:

//-----------------------------------------------------------------------------

	QIcon symbol_icon(const QString &name)
	{
		QString filename = ":/flowchart_images/" + name.toLower();
		filename.replace(' ', '-');
		return QIcon(filename);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // FLOWCHART_PICKER_HPP
