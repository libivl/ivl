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

#ifndef IVL_QT_GUI_ITEM_VIEWS_TREE_WIDGET_HPP
#define IVL_QT_GUI_ITEM_VIEWS_TREE_WIDGET_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QTreeWidget>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ tree_widget : public QTreeWidget,
	public widget_base <tree_widget>,
	public method_binder <tree_widget, QTreeWidget, QTreeView>
{
	Q_OBJECT
	typedef QTreeWidget T;
	typedef QTreeView B;

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

	// QTreeWidget
	void itemPressed_(QTreeWidgetItem* item, int col)        { item_pressed(item, col); }
	void itemClicked_(QTreeWidgetItem* item, int col)        { item_clicked(item, col); }
	void itemDoubleClicked_(QTreeWidgetItem* item, int col)  { item_double_clicked(item, col); }
	void itemActivated_(QTreeWidgetItem* item, int col)      { item_activated(item, col); }
	void itemEntered_(QTreeWidgetItem* item, int col)        { item_entered(item, col); }
	void itemChanged_(QTreeWidgetItem* item, int col)        { item_changed(item, col); }
	void itemExpanded_(QTreeWidgetItem* item)                { item_expanded(item); }
	void itemCollapsed_(QTreeWidgetItem* item)               { item_collapsed(item); }
	void itemSelectionChanged_()                             { item_selection_changed(); }
	void currentItemChanged_(QTreeWidgetItem *curr,
									 QTreeWidgetItem *prev)          { current_item_changed(curr, prev); }

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

		// QTreeWidget
		connect(this, SIGNAL(itemPressed(QTreeWidgetItem*, int)),        SLOT(itemPressed_(QTreeWidgetItem*, int)));
		connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),        SLOT(itemClicked_(QTreeWidgetItem*, int)));
		connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),  SLOT(itemDoubleClicked_(QTreeWidgetItem*, int)));
		connect(this, SIGNAL(itemActivated(QTreeWidgetItem*, int)),      SLOT(itemActivated_(QTreeWidgetItem*, int)));
		connect(this, SIGNAL(itemEntered(QTreeWidgetItem*, int)),        SLOT(itemEntered_(QTreeWidgetItem*, int)));
		connect(this, SIGNAL(itemChanged(QTreeWidgetItem*, int)),        SLOT(itemChanged_(QTreeWidgetItem*, int)));
		connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)),            SLOT(itemExpanded_(QTreeWidgetItem*)));
		connect(this, SIGNAL(itemCollapsed(QTreeWidgetItem*)),           SLOT(itemCollapsed_(QTreeWidgetItem*)));
		connect(this, SIGNAL(itemSelectionChanged()),                    SLOT(itemSelectionChanged_()));
		connect(this, SIGNAL(currentItemChanged(QTreeWidgetItem*,
															 QTreeWidgetItem*)),      SLOT(currentItemChanged_(QTreeWidgetItem*, QTreeWidgetItem*)));

		// QTreeView
		bind(hide_column)                .to <&B::hideColumn>();
		bind(show_column)                .to <&B::showColumn>();
		bind(expand)                     .to <&B::expand>();
		bind(collapse)                   .to <&B::collapse>();
		bind(resize_column_to_contents)  .to <&B::resizeColumnToContents>();
		bind(sort_by_column)             .to <B, &B::sortByColumn>();
		bind(expand_all)                 .to <B, &B::expandAll>();
		bind(collapse_all)               .to <B, &B::collapseAll>();
		bind(expand_to_depth)            .to <B, &B::expandToDepth>();

		// QTreeWidget
		bind(scroll_to_item) .to <&T::scrollToItem>();
		bind(expand_item)    .to <&T::expandItem>();
		bind(collapse_item)  .to <&T::collapseItem>();
		bind(clear)          .to <&T::clear>();
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

	// QTreeWidget
	signal <void (QTreeWidgetItem*, int)>  item_pressed;
	signal <void (QTreeWidgetItem*, int)>  item_clicked;
	signal <void (QTreeWidgetItem*, int)>  item_double_clicked;
	signal <void (QTreeWidgetItem*, int)>  item_activated;
	signal <void (QTreeWidgetItem*, int)>  item_entered;
	signal <void (QTreeWidgetItem*, int)>  item_changed;
	signal <void (QTreeWidgetItem*)>       item_expanded;
	signal <void (QTreeWidgetItem*)>       item_collapsed;
	signal <void ()>                       item_selection_changed;
	signal <void (QTreeWidgetItem*,
					  QTreeWidgetItem*)>       current_item_changed;

	// QTreeWidget
	slot <void (const QTreeWidgetItem*,
					QAbstractItemView::ScrollHint)>  scroll_to_item;
	slot <void (const QTreeWidgetItem*)>         expand_item;
	slot <void (const QTreeWidgetItem*)>         collapse_item;
	slot <void ()>                               clear;

//-----------------------------------------------------------------------------

	explicit tree_widget(QWidget* parent = 0) : QTreeWidget(parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QTreeWidget&
operator<<(QTreeWidget& t, QTreeWidgetItem* i) { t.addTopLevelItem(i); return t; }

inline QTreeWidgetItem&
operator<<(QTreeWidgetItem& t, QTreeWidgetItem* i) { t.addChild(i); return t; }

// TODO
// addScrollBarWidget ( QWidget * widget, Qt::Alignment alignment )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::tree_widget;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_TREE_WIDGET_HPP
