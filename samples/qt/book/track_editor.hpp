#ifndef TRACK_EDITOR_HPP
#define TRACK_EDITOR_HPP

#include <vector>
#include <iostream>
#include "track_delegate.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;
using namespace std;

//-----------------------------------------------------------------------------

struct track
{
	QString title;
	int duration;

	track(const QString &title = "", int duration = 0) :
		title(title), duration(duration) { }
};

//-----------------------------------------------------------------------------

class track_editor : public dialog, public method_binder <track_editor>
{
	typedef track_editor T;
	using method_binder <T>::bind;

	table_widget      *table;
	dialog_button_box *button_box;
	vector <track>    &tracks;

	slot <void ()> add_track;

public:

//-----------------------------------------------------------------------------

	track_editor(vector <track>& tracks, QWidget* parent = 0) :
		dialog(parent), tracks(tracks)
	{
		bind(add_track).to <&T::add_track_>();

//-----------------------------------------------------------------------------

		table = new table_widget(tracks.size(), 2);
		table->setItemDelegate(new track_delegate(1));
		table->setHorizontalHeaderLabels
			(QStringList() << tr("track") << tr("Duration"));

		for (unsigned row = 0; row < tracks.size(); ++row)
		{
			track t = tracks[row];

			QTableWidgetItem* item0 = new QTableWidgetItem(t.title);
			table->setItem(row, 0, item0);

			QTableWidgetItem* item1
					= new QTableWidgetItem(QString::number(t.duration));
			item1->setTextAlignment(Qt::AlignRight);
			table->setItem(row, 1, item1);
		}

		table->resizeColumnToContents(0);

		push_button* add_track_button = new push_button(tr("&Add track"));
		button_box = new dialog_button_box
			(dialog_button_box::Ok | dialog_button_box::Cancel);
		button_box->addButton(add_track_button, dialog_button_box::ActionRole);  // TODO: <<

		add_track_button->clicked.connect(add_track);
		button_box->accepted.connect(accept);
		button_box->rejected.connect(reject);

//-----------------------------------------------------------------------------

		col_layout *layout = new col_layout(this);
		*layout << table << button_box;

		setWindowTitle(tr("track Editor"));
	}

//-----------------------------------------------------------------------------

	void done(int result)
	{
		if (result == dialog::Accepted)
		{
			tracks.clear();
			QTableWidgetItem* item;
			for (int row = 0; row < table->rowCount(); ++row)
			{
				item = table->item(row, 0);
				QString title = item ? item->text() : "";
				item = table->item(row, 1);
				int duration = item ? item->text().toInt() : 0;
				tracks.push_back(track(title, duration));
			}
		}
		QDialog::done(result);  // TODO: reimplement all QDialog virtual methods in dialog
	}

private:

//-----------------------------------------------------------------------------

	void add_track_()
	{
		int row = table->rowCount();
		table->insertRow(row);
		QTableWidgetItem* item = new QTableWidgetItem;
		table->setItem(row, 0, item);
		table->setCurrentItem(item);
		table->editItem(item);
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // TRACK_EDITOR_HPP
