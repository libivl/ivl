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

#ifndef IVL_QT_GUI_ITEM_VIEWS_TREE_VIEW_HPP
#define IVL_QT_GUI_ITEM_VIEWS_TREE_VIEW_HPP

#include "../../core.hpp"
#include <QTreeView>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ tree_view : public QTreeView,
	public method_binder <tree_view, QTreeView>
{
	Q_OBJECT
	typedef QTreeView T;

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

	// QTreeView
	void expanded_(const QModelIndex& index)   { expanded(index); }
	void collapsed_(const QModelIndex& index)  { collapsed(index); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractItemView
		#include "abstract_item_view_init.hpp"

		// QTreeView
		connect(this, SIGNAL(expanded(const QModelIndex&)),  SLOT(expanded_(const QModelIndex&)));
		connect(this, SIGNAL(collapsed(const QModelIndex&)), SLOT(collapsed_(const QModelIndex&)));

		// QTreeView
		bind(hide_column)                .to <&T::hideColumn>();
		bind(show_column)                .to <&T::showColumn>();
		bind(expand)                     .to <&T::expand>();
		bind(collapse)                   .to <&T::collapse>();
		bind(resize_column_to_contents)  .to <&T::resizeColumnToContents>();
		bind(sort_by_column)             .to <T, &T::sortByColumn>();
		bind(expand_all)                 .to <T, &T::expandAll>();
		bind(collapse_all)               .to <T, &T::collapseAll>();
		bind(expand_to_depth)            .to <T, &T::expandToDepth>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractItemView
	#include "abstract_item_view_decl.hpp"

	// QTreeView
	signal <void (const QModelIndex &index)> expanded;
	signal <void (const QModelIndex &index)> collapsed;

	// QTreeView
	slot <void (int)>                      hide_column;
	slot <void (int)>                      show_column;
	slot <void (const QModelIndex &index)> expand;
	slot <void (const QModelIndex &index)> collapse;
	slot <void (int)>                      resize_column_to_contents;
	slot <void (int)>                      sort_by_column;
	slot <void ()>                         expand_all;
	slot <void ()>                         collapse_all;
	slot <void (int)>                      expand_to_depth;

//-----------------------------------------------------------------------------

	explicit tree_view(QWidget* parent = 0) : QTreeView(parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::tree_view;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_TREE_VIEW_HPP
