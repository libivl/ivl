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

#ifndef IVL_QT_GUI_ITEM_VIEWS_TABLE_WIDGET_HPP
#define IVL_QT_GUI_ITEM_VIEWS_TABLE_WIDGET_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QTableWidget>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ table_widget : public QTableWidget,
	public widget_base <table_widget>,
	public method_binder <table_widget, QTableWidget, QTableView>
{
	Q_OBJECT
	typedef QTableWidget T;
	typedef QTableView B;

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

	// QTableWidget
	void itemPressed_(QTableWidgetItem* item)        { item_pressed(item); }
	void itemClicked_(QTableWidgetItem* item)        { item_clicked(item); }
	void itemDoubleClicked_(QTableWidgetItem* item)  { item_double_clicked(item); }
	void itemActivated_(QTableWidgetItem* item)      { item_activated(item); }
	void itemEntered_(QTableWidgetItem* item)        { item_entered(item); }
	void itemChanged_(QTableWidgetItem* item)        { item_changed(item); }
	void cellPressed_(int row, int col)              { cell_pressed(row, col); }
	void cellClicked_(int row, int col)              { cell_clicked(row, col); }
	void cellDoubleClicked_(int row, int col)        { cell_double_clicked(row, col); }
	void cellActivated_(int row, int col)            { cell_activated(row, col); }
	void cellEntered_(int row, int col)              { cell_entered(row, col); }
	void cellChanged_(int row, int col)              { cell_changed(row, col); }
	void itemSelectionChanged_()                     { item_selection_changed(); }
	void currentItemChanged_(QTableWidgetItem *curr,
									 QTableWidgetItem *prev) { current_item_changed(curr, prev); }
	void currentCellChanged_(int curr_row,
		int curr_col, int prev_row, int prev_col)     { current_cell_changed(curr_row, curr_col, prev_row, prev_col); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractItemView
		#include "abstract_item_view_init.hpp"

		// QTableWidget
		connect(this, SIGNAL(itemPressed(QTableWidgetItem*)),           SLOT(itemPressed_(QTableWidgetItem*)));
		connect(this, SIGNAL(itemClicked(QTableWidgetItem*)),           SLOT(itemClicked_(QTableWidgetItem*)));
		connect(this, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),     SLOT(itemDoubleClicked_(QTableWidgetItem*)));
		connect(this, SIGNAL(itemActivated(QTableWidgetItem*)),         SLOT(itemActivated_(QTableWidgetItem*)));
		connect(this, SIGNAL(itemEntered(QTableWidgetItem*)),           SLOT(itemEntered_(QTableWidgetItem*)));
		connect(this, SIGNAL(itemChanged(QTableWidgetItem*)),           SLOT(itemChanged_(QTableWidgetItem*)));
		connect(this, SIGNAL(cellPressed(int, int)),                    SLOT(cellPressed_(int, int)));
		connect(this, SIGNAL(cellClicked(int, int)),                    SLOT(cellClicked_(int, int)));
		connect(this, SIGNAL(cellDoubleClicked(int, int)),              SLOT(cellDoubleClicked_(int, int)));
		connect(this, SIGNAL(cellActivated(int, int)),                  SLOT(cellActivated_(int, int)));
		connect(this, SIGNAL(cellEntered(int, int)),                    SLOT(cellEntered_(int, int)));
		connect(this, SIGNAL(cellChanged(int, int)),                    SLOT(cellChanged_(int, int)));
		connect(this, SIGNAL(itemSelectionChanged()),                   SLOT(itemSelectionChanged_()));
		connect(this, SIGNAL(currentItemChanged(QTableWidgetItem*,
															 QTableWidgetItem*)),    SLOT(currentItemChanged_(QTableWidgetItem*, QTableWidgetItem*)));
		connect(this, SIGNAL(currentCellChanged(int, int, int, int)),   SLOT(currentCellChanged_(int, int, int, int)));

		// QTableView
		bind(select_row)                 .to <&B::selectRow>();
		bind(select_column)              .to <&B::selectColumn>();
		bind(hide_row)                   .to <&B::hideRow>();
		bind(hide_column)                .to <&B::hideColumn>();
		bind(show_row)                   .to <&B::showRow>();
		bind(show_column)                .to <&B::showColumn>();
		bind(resize_row_to_contents)     .to <&B::resizeRowToContents>();
		bind(resize_rows_to_contents)    .to <&B::resizeRowsToContents>();
		bind(resize_column_to_contents)  .to <&B::resizeColumnToContents>();
		bind(resize_columns_to_contents) .to <&B::resizeColumnsToContents>();
		bind(sort_by_column)             .to <B, &B::sortByColumn>();
		bind(set_show_grid)              .to <&B::setShowGrid>();

		// QTableWidget
		bind(scroll_to_item) .to <&T::scrollToItem>();
		bind(insert_row)     .to <&T::insertRow>();
		bind(insert_column)  .to <&T::insertColumn>();
		bind(remove_row)     .to <&T::removeRow>();
		bind(remove_column)  .to <&T::removeColumn>();
		bind(clear)          .to <&T::clear>();
		bind(clear_contents) .to <&T::clearContents>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractItemView
	#include "abstract_item_view_decl.hpp"

	// QTableView
	slot <void (int)>   select_row;
	slot <void (int)>   select_column;
	slot <void (int)>   hide_row;
	slot <void (int)>   hide_column;
	slot <void (int)>   show_row;
	slot <void (int)>   show_column;
	slot <void (int)>   resize_row_to_contents;
	slot <void ()>      resize_rows_to_contents;
	slot <void (int)>   resize_column_to_contents;
	slot <void ()>      resize_columns_to_contents;
	slot <void (int)>   sort_by_column;
	slot <void (bool)>  set_show_grid;

	// QTableWidget
	signal <void (QTableWidgetItem*)>   item_pressed;
	signal <void (QTableWidgetItem*)>   item_clicked;
	signal <void (QTableWidgetItem*)>   item_double_clicked;
	signal <void (QTableWidgetItem*)>   item_activated;
	signal <void (QTableWidgetItem*)>   item_entered;
	signal <void (QTableWidgetItem*)>   item_changed;
	signal <void (int, int)>            cell_pressed;
	signal <void (int, int)>            cell_clicked;
	signal <void (int, int)>            cell_double_clicked;
	signal <void (int, int)>            cell_activated;
	signal <void (int, int)>            cell_entered;
	signal <void (int, int)>            cell_changed;
	signal <void ()>                    item_selection_changed;
	signal <void (QTableWidgetItem*,
					  QTableWidgetItem*)>   current_item_changed;
	signal <void (int, int, int, int)>  current_cell_changed;

	// QTableWidget
	slot <void (const QTableWidgetItem*,
					QAbstractItemView::ScrollHint)>  scroll_to_item;
	slot <void (int)>                            insert_row;
	slot <void (int)>                            insert_column;
	slot <void (int)>                            remove_row;
	slot <void (int)>                            remove_column;
	slot <void ()>                               clear;
	slot <void ()>                               clear_contents;

//-----------------------------------------------------------------------------

	explicit table_widget(QWidget* parent = 0) :
		QTableWidget(parent) { init(); }

	table_widget(int rows, int columns, QWidget* parent = 0) :
		QTableWidget(rows, columns, parent) { init(); }

};

//-----------------------------------------------------------------------------

// TODO
// addScrollBarWidget ( QWidget * widget, Qt::Alignment alignment )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::table_widget;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_TABLE_WIDGET_HPP
