#ifndef DRAG_FILE_WINDOW_HPP
#define DRAG_FILE_WINDOW_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class drag_file_window : public main_window
{
	text_edit* edit;

public:

	drag_file_window()
	{
		edit = new text_edit;
		setCentralWidget(edit);

		edit->setAcceptDrops(false);
		setAcceptDrops(true);

		setWindowTitle(tr("Text Editor"));
	}

protected:

//-----------------------------------------------------------------------------

	void dragEnterEvent(QDragEnterEvent* event)
	{
		if (event->mimeData()->hasFormat("text/uri-list"))
			event->acceptProposedAction();
	}

	void dropEvent(QDropEvent* event)
	{
		QList <QUrl> urls = event->mimeData()->urls();
		if (urls.isEmpty())
			return;

		QString filename = urls.first().toLocalFile();
		if (filename.isEmpty())
			return;

		if (read_file(filename))
			setWindowTitle(tr("%1 - %2").arg(filename).arg(tr("Drag File")));
	}

private:

//-----------------------------------------------------------------------------

	bool read_file(const QString& filename)
	{
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::warning(this, tr("Text Editor"),
				tr("Cannot read file %1:\n%2.")
				.arg(file.fileName())
				.arg(file.errorString()));
			return false;
		}

		QTextStream in(&file);
		application::setOverrideCursor(Qt::WaitCursor);
		edit->setPlainText(in.readAll());
		application::restoreOverrideCursor();
		return true;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // DRAG_FILE_WINDOW_HPP