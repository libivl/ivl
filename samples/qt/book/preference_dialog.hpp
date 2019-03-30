#ifndef PREFERENCE_DIALOG_HPP
#define PREFERENCE_DIALOG_HPP

//-----------------------------------------------------------------------------

namespace qt_book {

using namespace ivl;

//-----------------------------------------------------------------------------

class preference_dialog : public dialog
{
	stacked_layout    *stack;
	list_widget       *list;
	widget            *appearance_page, *browser_page, *mail_page, *advanced_page;
	dialog_button_box *button_box;

	group_box    *open_group, *toolbars_group;
	check_box    *browser_check, *mail_check, *newsgroup_check;
	radio_button *pictures_text_radio, *pictures_only_radio, *text_only_radio;
	check_box    *tooltips_check, *site_icons_check, *resize_images_check;

	group_box    *display_group, *home_group, *web_buttons_group;
	radio_button *blank_radio, *home_radio, *last_radio;
	label        *location_label;
	line_edit    *location_edit;
	check_box    *bookmarks_check, *go_check, *home_check, *search_check,
	             *print_check;

	group_box *general_group, *mail_buttons_group;
	check_box *confirm_check, *remember_check, *file_check, *next_check,
	          *stop_check, *junk_check;

	group_box *features_group;
	check_box *java_check, *ftp_check;
	line_edit *ftp_edit;

public:

//-----------------------------------------------------------------------------

	preference_dialog(QWidget *parent = 0) : dialog(parent)
	{
		create_appearance_page();
		create_browser_page();
		create_mail_page();
		create_advanced_page();

		button_box = new dialog_button_box(dialog_button_box::Ok
		                                 | dialog_button_box::Cancel);

		list = new list_widget;
		*list << tr("Appearance")  << tr("Web Browser")
		      << tr("Mail & News") << tr("Advanced");
		list->setCurrentRow(0);

//-----------------------------------------------------------------------------

		stack = new stacked_layout;
		*stack << appearance_page << browser_page << mail_page << advanced_page;

		grid_layout *main_layout = new grid_layout(this);
		*main_layout << col_stretch(1) << col_stretch(3) << nl
		             << list           << stack          << nl
		             << ivl::qt_details::left(col_span(2)(button_box));

		setWindowTitle(tr("Preferences"));

//-----------------------------------------------------------------------------

		button_box->accepted.connect(accept);
		button_box->rejected.connect(reject);
		list->current_row_changed.connect(stack->set_current_index);

	}

private:

//-----------------------------------------------------------------------------

	void create_appearance_page()
	{
		appearance_page = new widget;

		open_group = new group_box(tr("Open at startup"));
		browser_check = new check_box(tr("Web browser"), true);
		mail_check = new check_box(tr("Mail editor"), true);
		newsgroup_check = new check_box(tr("Newsgroups"));

		toolbars_group = new group_box(tr("Show toolbars as"));
		pictures_text_radio = new radio_button(tr("Pictures and text"), true);
		pictures_only_radio = new radio_button(tr("Pictures only"));
		text_only_radio = new radio_button(tr("Text only"));

		tooltips_check = new check_box(tr("Show tooltips"), true);
		site_icons_check = new check_box(tr("Show web site icons"), true);
		resize_images_check = new check_box(tr("Resize large images to fit in the window"));

//-----------------------------------------------------------------------------

		col_layout *open_layout = new col_layout(open_group);
		*open_layout << browser_check << mail_check << newsgroup_check;

		col_layout *toolbars_layout = new col_layout(toolbars_group);
		*toolbars_layout << pictures_text_radio << pictures_only_radio
		                 << text_only_radio;

		col_layout *page_layout = new col_layout(appearance_page);
		page_layout->setMargin(0);
		*page_layout << open_group << toolbars_group << tooltips_check
		             << site_icons_check << resize_images_check << stretch;
	}

//-----------------------------------------------------------------------------

	void create_browser_page()
	{
		browser_page = new widget;

		display_group = new group_box(tr("Display on startup"));
		blank_radio = new radio_button(tr("Blank page"));
		home_radio = new radio_button(tr("Blank page"), true);
		last_radio = new radio_button(tr("Last page visited"));

		home_group = new group_box(tr("Home Page"));
		location_label = new label(tr("Location:"));
		location_edit = new line_edit;
		location_edit->setText("http://www.trolltech.com/");

		web_buttons_group = new group_box(tr("Select the buttons you want in the toolbar"));
		bookmarks_check = new check_box(tr("Bookmarks"), true);
		go_check = new check_box(tr("Go"));
		home_check = new check_box(tr("Home"), true);
		search_check = new check_box(tr("Search"), true);
		print_check = new check_box(tr("Print"), true);

//-----------------------------------------------------------------------------

		col_layout *display_layout = new col_layout(display_group);
		*display_layout << blank_radio << home_radio << last_radio;

		row_layout *home_layout = new row_layout(home_group);
		*home_layout << location_label << location_edit;

		grid_layout *web_buttons_layout = new grid_layout(web_buttons_group);
		*web_buttons_layout << bookmarks_check << search_check << nl
		                    << go_check        << print_check  << nl
		                    << home_check;

		col_layout *page_layout = new col_layout(browser_page);
		page_layout->setMargin(0);
		*page_layout << display_group << home_group << web_buttons_group
		             << stretch;
	}

//-----------------------------------------------------------------------------

	void create_mail_page()
	{
		mail_page = new widget;

		general_group = new group_box(tr("General settings"));
		confirm_check = new check_box(tr("Warn when moving folders to the Trash"), true);
		remember_check = new check_box(tr("Remember the last selected message"), true);

		mail_buttons_group = new group_box(tr("Select the buttons you want in the toolbar"));
		file_check = new check_box(tr("File"));
		next_check = new check_box(tr("Next"), true);
		stop_check = new check_box(tr("Stop"));
		junk_check = new check_box(tr("Junk"), true);

//-----------------------------------------------------------------------------

		col_layout *general_layout = new col_layout(general_group);
		*general_layout << confirm_check << remember_check;

		grid_layout *mail_buttons_layout = new grid_layout(mail_buttons_group);
		*mail_buttons_layout << file_check << stop_check << nl
		                     << next_check << junk_check;

		col_layout *page_layout = new col_layout(mail_page);
		page_layout->setMargin(0);
		*page_layout << general_group << mail_buttons_group << stretch;
	}

//-----------------------------------------------------------------------------

	void create_advanced_page()
	{
		advanced_page = new widget;

		features_group = new group_box(tr("Features that help interpret web pages"));
		java_check = new check_box(tr("Enable Java"), true);
		ftp_check = new check_box(tr("Use this email address for anonymous FTP:"));
		ftp_edit = new line_edit;
		ftp_edit->setEnabled(false);

//-----------------------------------------------------------------------------

		ftp_check->toggled.connect(ftp_edit->set_enabled);

//-----------------------------------------------------------------------------

		grid_layout *features_layout = new grid_layout(features_group);
		*features_layout << col_span(2)(java_check) << nl
		                 << col_span(2)(ftp_check)  << nl
		                 << tab       << ftp_edit;

		col_layout *page_layout = new col_layout(advanced_page);
		page_layout->setMargin(0);
		*page_layout << features_group << stretch;
	}

};

//-----------------------------------------------------------------------------

}  // namespace qt_book

//-----------------------------------------------------------------------------

#endif  // PREFERENCE_DIALOG_HPP
