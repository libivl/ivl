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

#ifndef IVL_QT_GUI_ITEM_VIEWS_LIST_WIDGET_HPP
#define IVL_QT_GUI_ITEM_VIEWS_LIST_WIDGET_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QListWidget>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ list_widget : public QListWidget,
	public widget_base <list_widget>,
	public method_binder <list_widget, QListWidget, QListView>
{
	Q_OBJECT
	typedef QListWidget T;
	typedef QListView B;

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

	// QListWidget
	void itemPressed_(QListWidgetItem* item)        { item_pressed(item); }
	void itemClicked_(QListWidgetItem* item)        { item_clicked(item); }
	void itemDoubleClicked_(QListWidgetItem* item)  { item_double_clicked(item); }
	void itemActivated_(QListWidgetItem* item)      { item_activated(item); }
	void itemEntered_(QListWidgetItem* item)        { item_entered(item); }
	void itemChanged_(QListWidgetItem* item)        { item_changed(item); }
	void itemSelectionChanged_()                    { item_selection_changed(); }
	void currentItemChanged_(QListWidgetItem *curr,
									 QListWidgetItem *prev) { current_item_changed(curr, prev); }
	void currentTextChanged_(const QString& text)   { current_text_changed(text); }
	void currentRowChanged_(int row)                { current_row_changed(row); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractItemView
		#include "abstract_item_view_init.hpp"

		// QListView
		connect(this, SIGNAL(indexesMoved(const QModelIndexList&)),    SLOT(indexesMoved_(const QModelIndexList&)));

		// QListWidget
		connect(this, SIGNAL(itemPressed(QListWidgetItem*)),           SLOT(itemPressed_(QListWidgetItem*)));
		connect(this, SIGNAL(itemClicked(QListWidgetItem*)),           SLOT(itemClicked_(QListWidgetItem*)));
		connect(this, SIGNAL(itemDoubleClicked(QListWidgetItem*)),     SLOT(itemDoubleClicked_(QListWidgetItem*)));
		connect(this, SIGNAL(itemActivated(QListWidgetItem*)),         SLOT(itemActivated_(QListWidgetItem*)));
		connect(this, SIGNAL(itemEntered(QListWidgetItem*)),           SLOT(itemEntered_(QListWidgetItem*)));
		connect(this, SIGNAL(itemChanged(QListWidgetItem*)),           SLOT(itemChanged_(QListWidgetItem*)));
		connect(this, SIGNAL(itemSelectionChanged()),                  SLOT(itemSelectionChanged_()));
		connect(this, SIGNAL(currentItemChanged(QListWidgetItem*,
															 QListWidgetItem*)),    SLOT(currentItemChanged_(QListWidgetItem*, QListWidgetItem*)));
		connect(this, SIGNAL(currentTextChanged(const QString&)),      SLOT(currentTextChanged_(const QString&)));
		connect(this, SIGNAL(currentRowChanged(int)),                  SLOT(currentRowChanged_(int)));

		// QListWidget
		bind(scroll_to_item) .to <&T::scrollToItem>();
		bind(clear)          .to <&T::clear>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractItemView
	#include "abstract_item_view_decl.hpp"

	// QListView
	signal <void (const QModelIndexList&)> indexes_moved;

	// QListWidget
	signal <void (QListWidgetItem*)>   item_pressed;
	signal <void (QListWidgetItem*)>   item_clicked;
	signal <void (QListWidgetItem*)>   item_double_clicked;
	signal <void (QListWidgetItem*)>   item_activated;
	signal <void (QListWidgetItem*)>   item_entered;
	signal <void (QListWidgetItem*)>   item_changed;
	signal <void ()>                   item_selection_changed;
	signal <void (QListWidgetItem*,
					  QListWidgetItem*)>   current_item_changed;
	signal <void (const QString&)>     current_text_changed;
	signal <void (int)>                current_row_changed;

	// QListWidget
	slot <void (const QListWidgetItem*,
					QAbstractItemView::ScrollHint)>  scroll_to_item;
	slot <void ()>                               clear;

//-----------------------------------------------------------------------------

	explicit list_widget(QWidget* parent = 0) : QListWidget(parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QListWidget&
operator<<(QListWidget& l, const QString & label) { l.addItem(label); return l; }

inline QListWidget&
operator<<(QListWidget& l, QListWidgetItem* item) { l.addItem(item); return l; }

// TODO
// addScrollBarWidget ( QWidget * widget, Qt::Alignment alignment )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::list_widget;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_LIST_WIDGET_HPP
