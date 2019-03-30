#ifndef EDITOR_HPP
#define EDITOR_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class text_editor : public text_edit,
	public method_binder <text_editor>
{
	typedef text_editor T;
	using method_binder <T>::bind;

	QString curr_file;
	bool untitled;
	action *act;

	slot <void ()> document_modified;

public:

//-----------------------------------------------------------------------------

	text_editor(QWidget *parent = 0) : text_edit(parent)
	{
		bind(document_modified) .to <&T::document_modified_>();

		act = new action(this);
		act->setCheckable(true);
		act->triggered.connect(show);
		act->triggered.connect(set_focus);

		text_changed.connect(document_modified);

		untitled = true;

		setWindowIcon(QPixmap(":/images/document.png"));
		setWindowTitle("[*]");
		setAttribute(Qt::WA_DeleteOnClose);
	}

//-----------------------------------------------------------------------------

	QSize sizeHint() const
	{
		return QSize(72 * fontMetrics().width('x'),
						 25 * fontMetrics().lineSpacing());
	}

//-----------------------------------------------------------------------------

	action* window_menu_action() const { return act; }

//-----------------------------------------------------------------------------

	void new_file()
	{
		static int document_number = 1;

		curr_file = tr("document%1.txt").arg(document_number);
		setWindowTitle(curr_file + "[*]");
		act->setText(curr_file);
		untitled = true;
		++document_number;
	}

//-----------------------------------------------------------------------------

	bool save()
	{
		return untitled ?
			save_as() : save_file(curr_file);
	}

//-----------------------------------------------------------------------------

	bool save_as()
	{
		QString filename = file_dialog::getSaveFileName(this, tr("Save As"), curr_file);
		return filename.isEmpty() ?
			false : save_file(filename);
	}

//-----------------------------------------------------------------------------

	static text_editor* open(QWidget *parent = 0)
	{
		QString filename = file_dialog::getOpenFileName(parent, tr("Open"), ".");
		return filename.isEmpty() ?
			0 : open_file(filename, parent);
	}

//-----------------------------------------------------------------------------

	static text_editor* open_file(const QString &filename, QWidget *parent = 0)
	{
		text_editor *editor = new text_editor(parent);
		if (editor->read_file(filename))
		{
			editor->set_current_file(filename);
			return editor;
		}
		else
		{
			delete editor;
			return 0;
		}
	}

protected:

//-----------------------------------------------------------------------------

	void closeEvent(QCloseEvent *event)
	{
		ok_to_continue() ?
			event->accept() : event->ignore();
	}

private:

//-----------------------------------------------------------------------------

	void document_modified_()
	{
		setWindowModified(true);
	}

//-----------------------------------------------------------------------------

	bool ok_to_continue()
	{
		if (document()->isModified())
		{
			int r = QMessageBox::warning(this, tr("MDI Text Editor"),
				tr("File %1 has been modified.\n"
					"Do you want to save your changes?")
				.arg(stripped_name(curr_file)),
				QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
			if (r == QMessageBox::Yes)
				return save();
			else if (r == QMessageBox::Cancel)
				return false;
		}
		return true;
	}

//-----------------------------------------------------------------------------

	bool save_file(const QString& filename)
	{
		if (write_file(filename))
		{
			set_current_file(filename);
			return true;
		}
		else
			return false;
	}

//-----------------------------------------------------------------------------

	void set_current_file(const QString& filename)
	{
		curr_file = filename;
		untitled = false;
		act->setText(stripped_name(curr_file));
		document()->setModified(false);
		setWindowTitle(stripped_name(curr_file) + "[*]");
		setWindowModified(false);
	}

//-----------------------------------------------------------------------------

	bool read_file(const QString& filename)
	{
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			QMessageBox::warning(this, tr("MDI Text Editor"),
				tr("Cannot read file %1:\n%2.")
				.arg(file.fileName())
				.arg(file.errorString()));
			return false;
		}

		QTextStream in(&file);
		application::setOverrideCursor(Qt::WaitCursor);
		setPlainText(in.readAll());
		application::restoreOverrideCursor();
		return true;
	}

//-----------------------------------------------------------------------------

	bool write_file(const QString& filename)
	{
		QFile file(filename);
		if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QMessageBox::warning(this, tr("MDI Text Editor"),
				tr("Cannot write file %1:\n%2.")
				.arg(file.fileName())
				.arg(file.errorString()));
			return false;
		}

		QTextStream out(&file);
		application::setOverrideCursor(Qt::WaitCursor);
		out << toPlainText();
		application::restoreOverrideCursor();
		return true;
	}

//-----------------------------------------------------------------------------

	QString stripped_name(const QString& full_filename)
	{
		return QFileInfo(full_filename).fileName();
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // EDITOR_HPP
