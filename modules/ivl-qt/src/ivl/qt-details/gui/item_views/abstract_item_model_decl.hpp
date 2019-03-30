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

	typedef QModelIndex MI;

	signal <void (const MI&, const MI&)>                data_changed;
	signal <void (Qt::Orientation, int, int)>           header_data_changed;
	signal <void ()>                                    layout_changed;
	signal <void ()>                                    layout_about_to_be_changed;
	signal <void (const MI&, int, int)>                 rows_about_to_be_inserted;
	signal <void (const MI&, int, int)>                 rows_about_to_be_removed;
	signal <void (const MI&, int, int)>                 columns_about_to_be_inserted;
	signal <void (const MI&, int, int)>                 columns_about_to_be_removed;
	signal <void (const MI&, int, int)>                 rows_inserted;
	signal <void (const MI&, int, int)>                 rows_removed;
	signal <void (const MI&, int, int)>                 columns_inserted;
	signal <void (const MI&, int, int)>                 columns_removed;
	signal <void ()>                                    model_about_to_be_reset;
	signal <void ()>                                    model_reset;
	signal <void (const MI&, int, int, const MI&, int)> rows_about_to_be_moved;
	signal <void (const MI&, int, int, const MI&, int)> columns_about_to_be_moved;
	signal <void (const MI&, int, int, const MI&, int)> rows_moved;
	signal <void (const MI&, int, int, const MI&, int)> columns_moved;

	slot <bool ()> submit;
	slot <void ()> revert;

//-----------------------------------------------------------------------------
