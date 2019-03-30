#ifndef MAIL_CLIENT_HPP
#define MAIL_CLIENT_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class mail_client : public main_window
{
	splitter *main_splitter, *right_splitter;
	tree_widget *folder_tree, *message_tree;
	text_edit *edit;

//-----------------------------------------------------------------------------

public:

	mail_client()
	{
		QIcon folder_icon(style()->standardPixmap(QStyle::SP_DirClosedIcon));
		QIcon trash_icon(style()->standardPixmap(QStyle::SP_FileIcon));

		QStringList folder_labels;
		folder_labels << tr("Folders");

		folder_tree = new tree_widget;
		folder_tree->setHeaderLabels(folder_labels);
		add_folder(folder_icon, tr("Inbox"));
		add_folder(folder_icon, tr("Outbox"));
		add_folder(folder_icon, tr("Sent"));
		add_folder(trash_icon, tr("Trash"));

//-----------------------------------------------------------------------------

		QStringList message_labels;
		message_labels << tr("Subject") << tr("Sender") << tr("Date");

		message_tree = new tree_widget;
		message_tree->setHeaderLabels(message_labels);
		add_message(tr("Happy New Year!"),
						tr("Grace K. <grace@software-inc.com>"),
						tr("2006-12-31"));
		add_message(tr("Radically new concept!"),
						tr("Grace K. <grace@software-inc.com>"),
						tr("2006-12-22"));
		add_message(tr("Accounts"),
						tr("pascale@nospam.com"),
						tr("2006-12-31"));
		add_message(tr("Expenses"),
						tr("Joe Bloggs <joe@bloggs.com>"),
						tr("2006-12-25"));
		add_message(tr("Re: Expenses"),
						tr("Andy <andy@nospam.com>"),
						tr("2007-01-02"));
		add_message(tr("Re: Accounts"),
						tr("Joe Bloggs <joe@bloggs.com>"),
						tr("2007-01-03"));
		add_message(tr("Re: Accounts"),
						tr("Andy <andy@nospam.com>"),
						tr("2007-01-03"));
		message_tree->resizeColumnToContents(0);
		message_tree->resizeColumnToContents(1);

//-----------------------------------------------------------------------------

		edit = new text_edit;
		edit->setReadOnly(true);
		edit->setHtml(
			"<table bolder=0>"
			"<tr><td align=right><b>Subject:</b>"
			"<td><p>Happy New Year!"
			"<tr><td align=right><b>Date:</b>"
			"<td><p>Sun, 31 Dec 2006"
			"<tr><td align=right><b>From:</b>"
			"<td><p>Grace K. &lt;grace@software-inc.com&gt;"
			"<tr><td align=right><b>To:</b>"
			"<td>all@software-inc.com"
			"</table>"
			"<br>I want to seize this occasion to thank "
			"everybody for the year that has gone, and want "
			"to wish you the best for next year. It has been "
			"a pleasure to work with you all on the Hawk "
			"project, and I'm sure we'll get concrete "
			"results shortly."
			"<br><br>Happy New Year!"
			"<br>--Grace"
		);

//-----------------------------------------------------------------------------

		*menuBar() << tr("&File") << tr("&Edit") << tr("&View") << tr("F&older")
		           << tr("&Message") << tr("&Settings") << tr("&Help");
		statusBar()->showMessage(tr("No new messages on server"));

		right_splitter = new splitter(Qt::Vertical);
		*right_splitter << message_tree << stretch(1)(edit);

		main_splitter = new splitter(Qt::Horizontal);
		*main_splitter << folder_tree << stretch(1)(right_splitter);

		setCentralWidget(main_splitter);
		setWindowTitle(tr("Mail Client"));
		read_settings();
	}

protected:

//-----------------------------------------------------------------------------

void closeEvent(QCloseEvent *event)
{
	write_settings();
	event->accept();
}

private:

//-----------------------------------------------------------------------------

	void add_folder(const QIcon &icon, const QString &name)
	{
		QTreeWidgetItem *root;
		if (folder_tree->topLevelItemCount() == 0)
		{
			root = new QTreeWidgetItem(folder_tree);
			root->setText(0, tr("Mail"));
			folder_tree->setItemExpanded(root, true);
		}
		else
			root = folder_tree->topLevelItem(0);

		QTreeWidgetItem *item = new QTreeWidgetItem(root);
		item->setText(0, name);
		item->setIcon(0, icon);

		if (!folder_tree->currentItem())
			folder_tree->setCurrentItem(item);
	}

//-----------------------------------------------------------------------------

	void add_message(const QString &subject, const QString &from,
						  const QString &date)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(message_tree);
		item->setText(0, subject);
		item->setText(1, from);
		item->setText(2, date);

		if (!message_tree->currentItem())
			message_tree->setCurrentItem(item);
	}

//-----------------------------------------------------------------------------

	void read_settings()
	{
		QSettings settings("Software Inc.", "Mail Client");

		settings.beginGroup("main_window");
		restoreGeometry(settings.value("geometry").toByteArray());
		main_splitter->restoreState(settings.value("main_splitter").toByteArray());
		right_splitter->restoreState(settings.value("right_splitter").toByteArray());
		settings.endGroup();
	}

//-----------------------------------------------------------------------------

	void write_settings()
	{
		QSettings settings("Software Inc.", "Mail Client");

		settings.beginGroup("main_window");
		settings.setValue("geometry", saveGeometry());
		settings.setValue("main_splitter", main_splitter->saveState());
		settings.setValue("right_splitter", right_splitter->saveState());
		settings.endGroup();
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // MAIL_CLIENT_HPP
