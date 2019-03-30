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

	connect(this, SIGNAL(pressed(const QModelIndex&)),        SLOT(pressed_(const QModelIndex&)));
	connect(this, SIGNAL(clicked(const QModelIndex&)),        SLOT(clicked_(const QModelIndex&)));
	connect(this, SIGNAL(doubleClicked(const QModelIndex&)),  SLOT(doubleClicked_(const QModelIndex&)));
	connect(this, SIGNAL(activated(const QModelIndex&)),      SLOT(activated_(const QModelIndex&)));
	connect(this, SIGNAL(entered(const QModelIndex&)),        SLOT(entered_(const QModelIndex&)));
	connect(this, SIGNAL(viewportEntered()),                  SLOT(viewportEntered_()));

	{
		typedef QAbstractItemView A;

		bind(reset)              .to <A, &A::reset>();
		bind(set_root_index)     .to <A, &A::setRootIndex>();
		bind(do_items_layout)    .to <A, &A::doItemsLayout>();
		bind(select_all)         .to <A, &A::selectAll>();
		bind(edit)               .to <A, &A::edit>();
		bind(clear_selection)    .to <A, &A::clearSelection>();
		bind(set_current_index)  .to <A, &A::setCurrentIndex>();
		bind(scroll_to_top)      .to <A, &A::scrollToTop>();
		bind(scroll_to_bottom)   .to <A, &A::scrollToBottom>();
		bind(update_1)           .to <A, &A::update>();  // TODO: overloading with QWidget::update
	}

//-----------------------------------------------------------------------------
