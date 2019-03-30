#ifndef EDITOR_WINDOW_HPP
#define EDITOR_WINDOW_HPP

#include "editor.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class editor_window : public main_window,
	public method_binder <editor_window>
{
	typedef editor_window T;
	using method_binder <T>::bind;

	mdi_area *area;
	label *ready_label;

	menu *file_menu, *edit_menu, *window_menu, *help_menu;
	tool_bar *file_tool_bar, *edit_tool_bar;

	action_group *window_action_group;
	action *new_action, *open_action, *save_action, *save_as_action, *exit_action,
	       *cut_action, *copy_action, *paste_action,
	       *close_action, *close_all_action, *tile_action, *cascade_action,
	       *next_action, *previous_action, *sep_action,
	       *about_action, *about_qt_action;

	slot <void ()> open, save, save_as, cut, copy, paste, about,
	               update_actions, load_files;

public:

	slot <void ()> new_file;
	slot <void (const QString&)> open_file;

//-----------------------------------------------------------------------------

	editor_window()
	{
		bind(load_files) .to <&T::load_files_>();
		bind(new_file)   .to <&T::new_file_>();
		bind(open_file)  .to <&T::open_file_>();

		bind(open)           .to <&T::open_>();
		bind(save)           .to <&T::save_>();
		bind(save_as)        .to <&T::save_as_>();
		bind(cut)            .to <&T::cut_>();
		bind(copy)           .to <&T::copy_>();
		bind(paste)          .to <&T::paste_>();
		bind(about)          .to <&T::about_>();
		bind(update_actions) .to <&T::update_actions_>();

		area = new mdi_area;
		setCentralWidget(area);
		area->sub_window_activated.connect(update_actions);

		create_actions();
		create_menus();
		create_tool_bars();
		create_status_bar();

		setWindowIcon(QPixmap(":/editor_images/icon.png"));
		setWindowTitle(tr("MDI Editor"));
		qtimer::single_shot(0, load_files);
	}

protected:

//-----------------------------------------------------------------------------

	void closeEvent(QCloseEvent *event)
	{
		area->closeAllSubWindows();
		area->subWindowList().isEmpty() ?
			event->accept() :
			event->ignore();
	}

private:

//-----------------------------------------------------------------------------

	void load_files_()
	{
		QStringList args = QApplication::arguments();
		args.removeFirst();
		if (!args.isEmpty())
		{
			foreach (QString arg, args)
				open_file(arg);
			area->cascadeSubWindows();
		}
		else
			new_file();
		area->activateNextSubWindow();
	}

//-----------------------------------------------------------------------------

	void new_file_()
	{
		text_editor *editor = new text_editor;
		editor->new_file();
		add_editor(editor);
	}

	void open_file_(const QString &fileName)
	{
		text_editor *editor = text_editor::open_file(fileName, this);
		if (editor)
			add_editor(editor);
	}

//-----------------------------------------------------------------------------

	void open_()
	{
		text_editor *editor = text_editor::open(this);
		if (editor)
			add_editor(editor);
	}

	void save_()
	{
		if (active_editor())
			active_editor()->save();
	}

	void save_as_()
	{
		if (active_editor())
			active_editor()->save_as();
	}

//-----------------------------------------------------------------------------

	void cut_()
	{
		if (active_editor())
			active_editor()->cut();
	}

	void copy_()
	{
		if (active_editor())
			active_editor()->copy();
	}

	void paste_()
	{
		if (active_editor())
			active_editor()->paste();
	}

//-----------------------------------------------------------------------------

	void about_()
	{
		QMessageBox::about(this, tr("About MDI text_editor"), tr(
			"<h2>text_editor 1.1</h2>"
			"<p>Copyright &copy; 2007 Software Inc."
			"<p>MDI text_editor is a small application that demonstrates "
			"mdi_area.")
		);
	}

//-----------------------------------------------------------------------------

	void update_actions_()
	{
		bool has_editor = (active_editor() != 0);
		bool has_selection = active_editor()
								&& active_editor()->textCursor().hasSelection();

		save_action      -> setEnabled(has_editor);
		save_as_action   -> setEnabled(has_editor);
		cut_action       -> setEnabled(has_selection);
		copy_action      -> setEnabled(has_selection);
		paste_action     -> setEnabled(has_editor);
		close_action     -> setEnabled(has_editor);
		close_all_action -> setEnabled(has_editor);
		tile_action      -> setEnabled(has_editor);
		cascade_action   -> setEnabled(has_editor);
		next_action      -> setEnabled(has_editor);
		previous_action  -> setEnabled(has_editor);
		sep_action       -> setVisible(has_editor);

		if (active_editor())
			active_editor()->window_menu_action()->setChecked(true);
	}

//-----------------------------------------------------------------------------

	void create_actions()
	{
		new_action = new action(tr("&New"), this);
		new_action->setIcon(QIcon(":/editor_images/new.png"));
		new_action->setShortcut(QKeySequence::New);
		new_action->setStatusTip(tr("Create a new file"));
		new_action->triggered.connect(new_file);

		open_action = new action(tr("&Open..."), this);
		open_action->setIcon(QIcon(":/editor_images/open.png"));
		open_action->setShortcut(QKeySequence::Open);
		open_action->setStatusTip(tr("Open an existing file"));
		open_action->triggered.connect(open);

		save_action = new action(tr("&Save"), this);
		save_action->setIcon(QIcon(":/editor_images/save.png"));
		save_action->setShortcut(QKeySequence::Save);
		save_action->setStatusTip(tr("Save the file to disk"));
		save_action->triggered.connect(save);

		save_as_action = new action(tr("Save &As..."), this);
		save_as_action->setStatusTip(tr("Save the file under a new name"));
		save_as_action->triggered.connect(save_as);

		exit_action = new action(tr("E&xit"), this);
		exit_action->setShortcut(tr("Ctrl+Q"));
		exit_action->setStatusTip(tr("Exit the application"));
		exit_action->triggered.connect(close);

		cut_action = new action(tr("Cu&t"), this);
		cut_action->setIcon(QIcon(":/editor_images/cut.png"));
		cut_action->setShortcut(QKeySequence::Cut);
		cut_action->setStatusTip(tr("Cut the current selection to the clipboard"));
		cut_action->triggered.connect(cut);

		copy_action = new action(tr("&Copy"), this);
		copy_action->setIcon(QIcon(":/editor_images/copy.png"));
		copy_action->setShortcut(QKeySequence::Copy);
		copy_action->setStatusTip(tr("Copy the current selection to the clipboard"));
		copy_action->triggered.connect(copy);

		paste_action = new action(tr("&Paste"), this);
		paste_action->setIcon(QIcon(":/editor_images/paste.png"));
		paste_action->setShortcut(QKeySequence::Paste);
		paste_action->setStatusTip(tr("Paste the clipboard's contents at the cursor position"));
		paste_action->triggered.connect(paste);

		close_action = new action(tr("Cl&ose"), this);
		close_action->setShortcut(QKeySequence::Close);
		close_action->setStatusTip(tr("Close the active window"));
		close_action->triggered.connect(area->close_active_sub_window);

		close_all_action = new action(tr("Close &All"), this);
		close_all_action->setStatusTip(tr("Close all the windows"));
		close_all_action->triggered.connect(close);

		tile_action = new action(tr("&Tile"), this);
		tile_action->setStatusTip(tr("Tile the windows"));
		tile_action->triggered.connect(area->tile_sub_windows);

		cascade_action = new action(tr("&Cascade"), this);
		cascade_action->setStatusTip(tr("Cascade the windows"));
		cascade_action->triggered.connect(area->cascade_sub_windows);

		next_action = new action(tr("Ne&xt"), this);
		next_action->setShortcut(QKeySequence::NextChild);
		next_action->setStatusTip(tr("Move the focus to the next window"));
		next_action->triggered.connect(area->activate_next_sub_window);

		previous_action = new action(tr("Pre&vious"), this);
		previous_action->setShortcut(QKeySequence::PreviousChild);
		previous_action->setStatusTip(tr("Move the focus to the previous window"));
		previous_action->triggered.connect(area->activate_previous_sub_window);

		sep_action = new separator_action;

		about_action = new action(tr("&About"), this);
		about_action->setStatusTip(tr("Show the application's About box"));
		about_action->triggered.connect(about);

		about_qt_action = new action(tr("About &Qt"), this);
		about_qt_action->setStatusTip(tr("Show the Qt library's About box"));
		about_qt_action->triggered.connect(application::about_qt);

		window_action_group = new action_group(this);
	}

//-----------------------------------------------------------------------------

	void create_menus()
	{
		file_menu = new menu(tr("&File"));
		*file_menu << new_action << open_action << save_action << save_as_action
		           << separator << exit_action;

		edit_menu = new menu(tr("&Edit"));
		*edit_menu << cut_action << copy_action << paste_action;

		window_menu = new menu(tr("&Window"));
		*window_menu << close_action << close_all_action << separator
		             << tile_action << cascade_action << separator
		             << next_action << previous_action << sep_action;

		help_menu = new menu(tr("&Help"));
		*help_menu << about_action << about_qt_action;

		*menuBar() << file_menu << edit_menu << window_menu
		           << separator << help_menu;
	}

//-----------------------------------------------------------------------------

	void create_tool_bars()
	{
		file_tool_bar = new tool_bar(tr("File"));
		*file_tool_bar << new_action << open_action << save_action;

		edit_tool_bar = new tool_bar(tr("Edit"));
		*edit_tool_bar << cut_action << copy_action << paste_action;

		*this << file_tool_bar << edit_tool_bar;
	}

//-----------------------------------------------------------------------------

	void create_status_bar()
	{
		ready_label = new label(tr(" Ready"));
		statusBar()->addWidget(ready_label, 1);  // TODO: operator<<
	}

//-----------------------------------------------------------------------------

	void add_editor(text_editor *editor)
	{
		editor->copy_available.connect(cut_action->set_enabled);
		editor->copy_available.connect(copy_action->set_enabled);

		QMdiSubWindow *window = area->addSubWindow(editor);
		*window_menu         << editor->window_menu_action();
		*window_action_group << editor->window_menu_action();
		window->show();
	}

//-----------------------------------------------------------------------------

	text_editor *active_editor()
	{
		QMdiSubWindow *window = area->activeSubWindow();
		if (window)
			return static_cast <text_editor*>(window->widget());
		return 0;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // EDITOR_WINDOW_HPP
