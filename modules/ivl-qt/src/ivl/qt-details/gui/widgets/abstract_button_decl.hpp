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

private:

	typedef defaults <void (bool), c_false>
	clicked_signature;  // defaults: (bool checked = false)

public:

//-----------------------------------------------------------------------------

	// QAbstractButton
	signal <void ()>            pressed;
	signal <void ()>            released;
	signal <clicked_signature>  clicked;
	signal <void (bool)>        toggled;

	// QAbstractButton
	slot <void (const QSize&)>  set_icon_size;
	slot <void (int)>           animate_click;
	slot <void ()>              click;
	slot <void ()>              toggle;
	slot <void (bool)>          set_checked;
