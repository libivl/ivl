/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

	signal <void (const QPoint&)>  custom_context_menu_requested;

	slot <void (bool)>             set_enabled;
	slot <void (bool)>             set_disabled;
	slot <void (bool)>             set_window_modified;
	slot <void (const QString&)>   set_window_title;
#ifndef QT_NO_STYLE_STYLESHEET
	slot <void (const QString&)>   set_style_sheet;
#endif
	slot <void ()>                 set_focus;
	slot <void ()>                 update;
	slot <void ()>                 repaint;
	slot <void (bool)>             set_visible;
	slot <void (bool)>             set_hidden;
	slot <void ()>                 show;
	slot <void ()>                 hide;
	slot <void (bool)>             set_shown;
	slot <void ()>                 show_minimized;
	slot <void ()>                 show_maximized;
	slot <void ()>                 show_full_screen;
	slot <void ()>                 show_normal;
	slot <bool ()>                 close;
	slot <void ()>                 raise;
	slot <void ()>                 lower;

//-----------------------------------------------------------------------------
