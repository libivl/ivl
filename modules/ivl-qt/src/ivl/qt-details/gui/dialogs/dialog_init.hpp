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

	connect(this, SIGNAL(finished(int)), SLOT(finished_(int)));
	connect(this, SIGNAL(accepted()),    SLOT(accepted_()));
	connect(this, SIGNAL(rejected()),    SLOT(rejected_()));

	typedef QDialog D;

	bind(open)           .to <D, &D::open>();
	bind(exec)           .to <D, &D::exec>();
	bind(done)           .to <D, &D::done>();
	bind(accept)         .to <D, &D::accept>();
	bind(reject)         .to <D, &D::reject>();
	bind(show_extension) .to <D, &D::showExtension>();

//-----------------------------------------------------------------------------
