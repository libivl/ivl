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

#ifndef IVL_QT_GUI_ITEM_VIEWS_TABLE_VIEW_HPP
#define IVL_QT_GUI_ITEM_VIEWS_TABLE_VIEW_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QTableView>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ table_view : public QTableView,
	public widget_base <table_view>,
	public method_binder <table_view, QTableView>
{
	Q_OBJECT
	typedef QTableView T;

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

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractItemView
		#include "abstract_item_view_init.hpp"

		// QTableView
		bind(select_row)                 .to <&T::selectRow>();
		bind(select_column)              .to <&T::selectColumn>();
		bind(hide_row)                   .to <&T::hideRow>();
		bind(hide_column)                .to <&T::hideColumn>();
		bind(show_row)                   .to <&T::showRow>();
		bind(show_column)                .to <&T::showColumn>();
		bind(resize_row_to_contents)     .to <&T::resizeRowToContents>();
		bind(resize_rows_to_contents)    .to <&T::resizeRowsToContents>();
		bind(resize_column_to_vontents)  .to <&T::resizeColumnToContents>();
		bind(resize_columns_to_contents) .to <&T::resizeColumnsToContents>();
		bind(sort_by_column)             .to <T, &T::sortByColumn>();
		bind(set_show_grid)              .to <&T::setShowGrid>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractItemView
	#include "abstract_item_view_decl.hpp"

	// QTableView
	slot <void (int)>  select_row;
	slot <void (int)>  select_column;
	slot <void (int)>  hide_row;
	slot <void (int)>  hide_column;
	slot <void (int)>  show_row;
	slot <void (int)>  show_column;
	slot <void (int)>  resize_row_to_contents;
	slot <void ()>     resize_rows_to_contents;
	slot <void (int)>  resize_column_to_vontents;
	slot <void ()>     resize_columns_to_contents;
	slot <void (int)>  sort_by_column;
	slot <void (bool)> set_show_grid;

//-----------------------------------------------------------------------------

	explicit table_view(QWidget* parent = 0) : QTableView(parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::table_view;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_TABLE_VIEW_HPP
