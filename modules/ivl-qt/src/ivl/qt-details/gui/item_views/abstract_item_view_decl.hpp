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

	signal <void (const QModelIndex&)>  pressed;
	signal <void (const QModelIndex&)>  clicked;
	signal <void (const QModelIndex&)>  double_clicked;
	signal <void (const QModelIndex&)>  activated;
	signal <void (const QModelIndex&)>  entered;
	signal <void ()>                    viewport_entered;

	slot <void ()>                    reset;
	slot <void (const QModelIndex&)>  set_root_index;
	slot <void ()>                    do_items_layout;
	slot <void ()>                    select_all;
	slot <void (const QModelIndex&)>  edit;
	slot <void ()>                    clear_selection;
	slot <void (const QModelIndex&)>  set_current_index;
	slot <void ()>                    scroll_to_top;
	slot <void ()>                    scroll_to_bottom;
	slot <void (const QModelIndex&)>  update_1;  // TODO: overloading with QWidget::update

//-----------------------------------------------------------------------------
