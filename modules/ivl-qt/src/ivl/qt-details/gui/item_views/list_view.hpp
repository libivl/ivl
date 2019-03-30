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

#ifndef IVL_QT_GUI_ITEM_VIEWS_LIST_VIEW_HPP
#define IVL_QT_GUI_ITEM_VIEWS_LIST_VIEW_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QListView>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ list_view : public QListView,
	public widget_base <list_view>,
	public method_binder <list_view, QListView>
{
	Q_OBJECT
	typedef QListView T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QAbstractItemView
	void pressed_(const QModelIndex& index)         { pressed(index); }
	void clicked_(const QModelIndex& index)         { clicked(index); }
	void doubleClicked_(const QModelIndex& index)   { double_clicked(index); }
	void activated_(const QModelIndex& index)       { activated(index); }
	void entered_(const QModelIndex& index)         { entered(index); }
	void viewportEntered_()                         { viewport_entered(); }

	// QListView
	void indexesMoved_(const QModelIndexList& idx)  { indexes_moved(idx); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractItemView
		#include "abstract_item_view_init.hpp"

		// QListView
		connect(this, SIGNAL(indexesMoved(const QModelIndexList&)), SLOT(indexesMoved_(const QModelIndexList&)));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractItemView
	#include "abstract_item_view_decl.hpp"

	// QListView
	signal <void (const QModelIndexList&)> indexes_moved;

//-----------------------------------------------------------------------------

	explicit list_view(QWidget* parent = 0) : QListView(parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::list_view;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_LIST_VIEW_HPP
