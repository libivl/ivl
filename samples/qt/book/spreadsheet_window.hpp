#ifndef SPREADSHEET_WINDOW_HPP
#define SPREADSHEET_WINDOW_HPP

#include "find_dialog.hpp"
#include "goto_cell_dialog.hpp"
#include "sort_dialog.hpp"
#include "spreadsheet.hpp"

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class spreadsheet_window : public main_window,
	public method_binder <spreadsheet_window>
{
	typedef spreadsheet_window T;
	using method_binder <T>::bind;

	spreadsheet*  sheet;
	find_dialog*  find_dlg;
	label*        location_label;
	label*        formula_label;
	QStringList   recent_files;
	QString       curr_file;

	enum { max_recent_files = 5 };
	action *recent_file_actions[max_recent_files], *sep_action;
	menu *file_menu, *edit_menu, *select_menu, *tools_menu, *options_menu, *help_menu;
	tool_bar *file_tool_bar, *edit_tool_bar;

	action *new_action, *open_action, *save_action, *save_as_action, *exit_action;
	action *cut_action, *copy_action, *paste_action, *delete_action;
	action *select_row_action, *select_column_action, *select_all_action;
	action *find_action, *goto_cell_action, *recalc_action, *sort_action;
	action *show_grid_action, *auto_recalc_action, *about_action, *about_qt_action;

	slot <void ()> new_file, open;
	slot <bool ()> save, save_as;
	slot <void ()> find, goto_cell, sort, about;
	slot <void ()> open_recent_file, update_status_bar, spreadsheet_modified;

public:

//-----------------------------------------------------------------------------

	spreadsheet_window()
	{
		bind(new_file)             .to <&T::new_file_>();
		bind(open)                 .to <&T::open_>();
		bind(save)                 .to <&T::save_>();
		bind(save_as)              .to <&T::save_as_>();
		bind(find)                 .to <&T::find_>();
		bind(goto_cell)            .to <&T::goto_cell_>();
		bind(sort)                 .to <&T::sort_>();
		bind(about)                .to <&T::about_>();
		bind(open_recent_file)     .to <&T::open_recent_file_>();
		bind(update_status_bar)    .to <&T::update_status_bar_>();
		bind(spreadsheet_modified) .to <&T::spreadsheet_modified_>();

		find_dlg = 0;
		sheet = new spreadsheet;
		setCentralWidget(sheet);

		create_actions();
		create_menus();
		create_context_menu();
		create_tool_bars();
		create_status_bar();

		read_settings();
		setWindowIcon(QIcon(":/spreadsheet_images/icon.png"));
		set_current_file("");
	}

protected:

//-----------------------------------------------------------------------------

	void closeEvent(QCloseEvent *event)
	{
		if (ok_to_continue())
		{
			write_settings();
			event->accept();
		}
		else
			event->ignore();
	}

private:

//-----------------------------------------------------------------------------

	void new_file_()
	{
		if (ok_to_continue())
		{
			sheet->clear();
			set_current_file("");
		}
	}

//-----------------------------------------------------------------------------

	void open_()
	{
		if (ok_to_continue())
		{
			QString file_name = file_dialog::getOpenFileName(this,
												tr("Open Spreadsheet"), ".",
												tr("Spreadsheet files (*.sp)"));
			if (!file_name.isEmpty())
				load_file(file_name);
		}
	}

//-----------------------------------------------------------------------------

	bool save_()
	{
		if (curr_file.isEmpty())
			return save_as();
		else
			return save_file(curr_file);
	}

//-----------------------------------------------------------------------------

	bool save_as_()
	{
		QString file_name = file_dialog::getSaveFileName(this,
											tr("Save Spreadsheet"), ".",
											tr("Spreadsheet files (*.sp)"));
		if (file_name.isEmpty())
			return false;

		return save_file(file_name);
	}

//-----------------------------------------------------------------------------

	void find_()
	{
		if (!find_dlg)
		{
			find_dlg = new find_dialog(this);
			find_dlg->find_next.connect(sheet->find_next);
			find_dlg->find_prev.connect(sheet->find_prev);
		}

		find_dlg->show();
		find_dlg->raise();
		find_dlg->activateWindow();
	}

//-----------------------------------------------------------------------------

	void goto_cell_()
	{
		goto_cell_dialog dialog(this);
		if (dialog.exec())
		{
			QString str = dialog.cell().toUpper();
			sheet->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
		}
	}

//-----------------------------------------------------------------------------

	void sort_()
	{
		sort_dialog dialog(this);
		QTableWidgetSelectionRange range = sheet->selected_range();
		dialog.set_column_range('A' + range.leftColumn(),
										'A' + range.rightColumn());

		if (dialog.exec())
		{
			spreadsheet_compare compare;
			for (int i = 0; i < spreadsheet_compare::key_count; i++)
			{
				compare.keys     [i] = dialog.column(i);
				compare.ascending[i] = dialog.ascending(i);
			}
			sheet->sort(compare);
		}
	}

//-----------------------------------------------------------------------------

	void about_()
	{
		message_box::about(this, tr("About Spreadsheet"),
					tr("<h2>Spreadsheet 1.1</h2>"
						"<p>Copyright &copy; 2008 Software Inc."
						"<p>Spreadsheet is a small application that "
						"demonstrates QAction, QMainWindow, QMenuBar, "
						"QStatusBar, QTableWidget, QToolBar, and many other "
						"Qt classes."));
	}

//-----------------------------------------------------------------------------

	void open_recent_file_()
	{
		if (ok_to_continue())
		{
			QAction* action = qobject_cast <QAction*>(sender());  // TODO: implement sender
			if (action)
				load_file(action->data().toString());
		}
	}

//-----------------------------------------------------------------------------

	void update_status_bar_()
	{
		location_label->setText(sheet->current_location());
		formula_label->setText(sheet->current_formula());
	}

//-----------------------------------------------------------------------------

	void spreadsheet_modified_()
	{
		setWindowModified(true);
		update_status_bar();
	}

//-----------------------------------------------------------------------------

	void create_actions()
	{
		new_action = new action(tr("&New"), this);
		new_action->setIcon(QIcon(":/spreadsheet_images/new.png"));
		new_action->setShortcut(QKeySequence::New);
		new_action->setStatusTip(tr("Create a new spreadsheet file"));
		new_action->triggered.connect(new_file);

		open_action = new action(tr("&Open..."), this);
		open_action->setIcon(QIcon(":/spreadsheet_images/open.png"));
		open_action->setShortcut(QKeySequence::Open);
		open_action->setStatusTip(tr("Open an existing spreadsheet file"));
		open_action->triggered.connect(open);

		save_action = new action(tr("&Save"), this);
		save_action->setIcon(QIcon(":/spreadsheet_images/save.png"));
		save_action->setShortcut(QKeySequence::Save);
		save_action->setStatusTip(tr("Save the spreadsheet to disk"));
		save_action->triggered.connect(save);

		save_as_action = new action(tr("Save &As..."), this);
		save_as_action->setStatusTip(tr("Save the spreadsheet under a new "
												"name"));
		save_as_action->triggered.connect(save_as);

		sep_action = new separator_action;
		for (int i = 0; i < max_recent_files; ++i) {
			recent_file_actions[i] = new action(this);
			recent_file_actions[i]->setVisible(false);
			recent_file_actions[i]->triggered.connect(open_recent_file);
		}

		exit_action = new action(tr("E&xit"), this);
		exit_action->setShortcut(tr("Ctrl+Q"));
		exit_action->setStatusTip(tr("Exit the application"));
		exit_action->triggered.connect(close);

		cut_action = new action(tr("Cu&t"), this);
		cut_action->setIcon(QIcon(":/spreadsheet_images/cut.png"));
		cut_action->setShortcut(QKeySequence::Cut);
		cut_action->setStatusTip(tr("Cut the current selection's contents "
											"to the clipboard"));
		cut_action->triggered.connect(sheet->cut);

		copy_action = new action(tr("&Copy"), this);
		copy_action->setIcon(QIcon(":/spreadsheet_images/copy.png"));
		copy_action->setShortcut(QKeySequence::Copy);
		copy_action->setStatusTip(tr("Copy the current selection's contents "
											"to the clipboard"));
		copy_action->triggered.connect(sheet->copy);

		paste_action = new action(tr("&Paste"), this);
		paste_action->setIcon(QIcon(":/spreadsheet_images/paste.png"));
		paste_action->setShortcut(QKeySequence::Paste);
		paste_action->setStatusTip(tr("Paste the clipboard's contents into "
												"the current selection"));
		paste_action->triggered.connect(sheet->paste);

		delete_action = new action(tr("&Delete"), this);
		delete_action->setShortcut(QKeySequence::Delete);
		delete_action->setStatusTip(tr("Delete the current selection's "
												"contents"));
		delete_action->triggered.connect(sheet->del);

		select_row_action = new action(tr("&Row"), this);
		select_row_action->setStatusTip(tr("Select all the cells in the "
													"current row"));
		select_row_action->triggered.connect(sheet->select_current_row);

		select_column_action = new action(tr("&Column"), this);
		select_column_action->setStatusTip(tr("Select all the cells in the "
														"current column"));
		select_column_action->triggered.connect(sheet->select_current_column);

		select_all_action = new action(tr("&All"), this);
		select_all_action->setShortcut(QKeySequence::SelectAll);
		select_all_action->setStatusTip(tr("Select all the cells in the "
													"spreadsheet"));
		select_all_action->triggered.connect(sheet->select_all);

		find_action = new action(tr("&Find..."), this);
		find_action->setIcon(QIcon(":/spreadsheet_images/find.png"));
		find_action->setShortcut(QKeySequence::Find);
		find_action->setStatusTip(tr("Find a matching cell"));
		find_action->triggered.connect(find);

		goto_cell_action = new action(tr("&Go to Cell..."), this);
		goto_cell_action->setIcon(QIcon(":/spreadsheet_images/gotocell.png"));
		goto_cell_action->setShortcut(tr("Ctrl+G"));
		goto_cell_action->setStatusTip(tr("Go to the specified cell"));
		goto_cell_action->triggered.connect(goto_cell);

		recalc_action = new action(tr("&Recalculate"), this);
		recalc_action->setShortcut(tr("F9"));
		recalc_action->setStatusTip(tr("Recalculate all the "
														"spreadsheet's formulas"));
		recalc_action->triggered.connect(sheet->recalc);

		sort_action = new action(tr("&Sort..."), this);
		sort_action->setStatusTip(tr("Sort the selected cells or all the "
											"cells"));
		sort_action->triggered.connect(sort);

		show_grid_action = new action(tr("&Show Grid"), this);
		show_grid_action->setCheckable(true);
		show_grid_action->setChecked(sheet->showGrid());
		show_grid_action->setStatusTip(tr("Show or hide the spreadsheet's grid"));
		show_grid_action->toggled.connect(sheet->set_show_grid);

		auto_recalc_action = new action(tr("&Auto-Recalculate"), this);
		auto_recalc_action->setCheckable(true);
		auto_recalc_action->setChecked(sheet->auto_recalculate());
		auto_recalc_action->setStatusTip(tr("Switch auto-recalculation on or "
													"off"));
		auto_recalc_action->toggled.connect(sheet->set_auto_recalc);

		about_action = new action(tr("&About"), this);
		about_action->setStatusTip(tr("Show the application's About box"));
		about_action->triggered.connect(about);

		about_qt_action = new action(tr("About &Qt"), this);
		about_qt_action->setStatusTip(tr("Show the Qt library's About box"));
		about_qt_action->triggered.connect(application::about_qt);
	}

//-----------------------------------------------------------------------------

	void create_menus()
	{
		file_menu = new menu(tr("&File"));
		*file_menu << new_action << open_action << save_action
		           << save_as_action << sep_action;
		for (int i = 0; i < max_recent_files; ++i)
			*file_menu << recent_file_actions[i];
		*file_menu << separator << exit_action;

		select_menu = new menu(tr("&Select"));
		*select_menu << select_row_action << select_column_action << select_all_action;

		edit_menu = new menu(tr("&Edit"));
		*edit_menu << cut_action << copy_action << paste_action << delete_action;
		*edit_menu << select_menu << separator << find_action << goto_cell_action;

		tools_menu = new menu(tr("&Tools"));
		*tools_menu << recalc_action << sort_action;

		options_menu = new menu(tr("&Options"));
		*options_menu << show_grid_action << auto_recalc_action;

		help_menu = new menu(tr("&Help"));
		*help_menu << about_action << about_qt_action;

		*menuBar() << file_menu << edit_menu << tools_menu << options_menu
		           << separator << help_menu;
	}

//-----------------------------------------------------------------------------

	void create_context_menu()
	{
		*sheet << cut_action << copy_action << paste_action;
		sheet->setContextMenuPolicy(Qt::ActionsContextMenu);
	}

//-----------------------------------------------------------------------------

	void create_tool_bars()
	{
		file_tool_bar = new tool_bar(tr("&File"));
		*file_tool_bar << new_action << open_action << save_action;

		edit_tool_bar = new tool_bar(tr("&Edit"));
		*edit_tool_bar << cut_action << copy_action << paste_action
		               << separator << find_action << goto_cell_action;

		*this << file_tool_bar << edit_tool_bar;
	}

//-----------------------------------------------------------------------------

	void create_status_bar()
	{
		location_label = new label(" W999 ");
		location_label->setAlignment(Qt::AlignHCenter);
		location_label->setMinimumSize(location_label->sizeHint());

		formula_label = new label;
		formula_label->setIndent(3);

		statusBar()->addWidget(location_label);  // TODO: operator<<
		statusBar()->addWidget(formula_label, 1);

		sheet->current_cell_changed.connect(update_status_bar);
		sheet->modified.connect(spreadsheet_modified);

		update_status_bar();
	}

//-----------------------------------------------------------------------------

	void read_settings()
	{
		QSettings settings("Software Inc.", "Spreadsheet");

		restoreGeometry(settings.value("geometry").toByteArray());

		recent_files = settings.value("recent_files").toStringList();
		update_recent_file_actions();

		bool show_grid = settings.value("showGrid", true).toBool();
		show_grid_action->setChecked(show_grid);

		bool auto_recalc = settings.value("autoRecalc", true).toBool();
		auto_recalc_action->setChecked(auto_recalc);
	}

//-----------------------------------------------------------------------------

	void write_settings()
	{
		QSettings settings("Software Inc.", "Spreadsheet");

		settings.setValue("geometry", saveGeometry());
		settings.setValue("recent_files", recent_files);
		settings.setValue("showGrid", show_grid_action->isChecked());
		settings.setValue("autoRecalc", auto_recalc_action->isChecked());
	}

//-----------------------------------------------------------------------------

	bool ok_to_continue()
	{
		if (isWindowModified())
		{
			int r = message_box::warning(this, tr("Spreadsheet"),
				tr("The document has been modified.\n"
					"Do you want to save your changes?"),
				message_box::Yes | message_box::No | message_box::Cancel);
			if (r == message_box::Yes)
				return save();
			else if (r == message_box::Cancel)
				return false;
		}
		return true;
	}

//-----------------------------------------------------------------------------

	bool load_file(const QString &file_name)
	{
		if (!sheet->read_file(file_name))
		{
			statusBar()->showMessage(tr("Loading canceled"), 2000);
			return false;
		}

		set_current_file(file_name);
		statusBar()->showMessage(tr("File loaded"), 2000);
		return true;
	}

//-----------------------------------------------------------------------------

	bool save_file(const QString &file_name)
	{
		if (!sheet->write_file(file_name))
		{
			statusBar()->showMessage(tr("Saving canceled"), 2000);
			return false;
		}

		set_current_file(file_name);
		statusBar()->showMessage(tr("File saved"), 2000);
		return true;
	}

//-----------------------------------------------------------------------------

	void set_current_file(const QString &file_name)
	{
		curr_file = file_name;
		setWindowModified(false);

		QString shown_name = tr("Untitled");
		if (!curr_file.isEmpty())
		{
			shown_name = stripped_name(curr_file);
			recent_files.removeAll(curr_file);
			recent_files.prepend(curr_file);
			update_recent_file_actions();
		}

		setWindowTitle(tr("%1[*] - %2").arg(shown_name).arg(tr("Spreadsheet")));
	}

//-----------------------------------------------------------------------------

	void update_recent_file_actions()
	{
		QMutableStringListIterator i(recent_files);
		while (i.hasNext())
		{
			if (!QFile::exists(i.next()))
				i.remove();
		}

		for (int j = 0; j < max_recent_files; ++j)
		{
			if (j < recent_files.count())
			{
				QString text =
					tr("&%1 %2").arg(j + 1).arg(stripped_name(recent_files[j]));
				recent_file_actions[j]->setText(text);
				recent_file_actions[j]->setData(recent_files[j]);
				recent_file_actions[j]->setVisible(true);
			}
			else
				recent_file_actions[j]->setVisible(false);
		}
		sep_action->setVisible(!recent_files.isEmpty());
	}

//-----------------------------------------------------------------------------

	QString stripped_name(const QString &full_file_name)
	{
		return QFileInfo(full_file_name).fileName();
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // SPREADSHEET_WINDOW_HPP
