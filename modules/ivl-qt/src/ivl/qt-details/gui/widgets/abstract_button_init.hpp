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

	connect(this, SIGNAL(pressed()),     SLOT(pressed_()));
	connect(this, SIGNAL(released()),    SLOT(released_()));
	connect(this, SIGNAL(clicked(bool)), SLOT(clicked_(bool)));
	connect(this, SIGNAL(toggled(bool)), SLOT(toggled_(bool)));

	{
		typedef QAbstractButton A;

		bind(set_icon_size) .to <A, &A::setIconSize>();
		bind(animate_click) .to <A, &A::animateClick, c_int <100> >();  // defaults: (int msec = 100)
		bind(click)         .to <A, &A::click>();
		bind(toggle)        .to <A, &A::toggle>();
		bind(set_checked)   .to <A, &A::setChecked>();
	}

//-----------------------------------------------------------------------------
