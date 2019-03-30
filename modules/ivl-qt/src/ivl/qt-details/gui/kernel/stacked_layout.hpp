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

#ifndef IVL_QT_GUI_KERNEL_STACKED_LAYOUT_HPP
#define IVL_QT_GUI_KERNEL_STACKED_LAYOUT_HPP

#include "../../core.hpp"
#include <QStackedLayout>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ stacked_layout : public QStackedLayout,
	public method_binder <stacked_layout, QStackedLayout>
{
	Q_OBJECT
	typedef QStackedLayout T;

private slots:

	// QStackedLayout
	void widgetRemoved_(int index)  { widget_removed(index); }
	void currentChanged_(int index) { current_changed(index); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QStackedLayout
		connect(this, SIGNAL(widgetRemoved(int)),  SLOT(widgetRemoved_(int)));
		connect(this, SIGNAL(currentChanged(int)), SLOT(currentChanged_(int)));

		// QStackedLayout
		bind(set_current_index)  .to <&T::setCurrentIndex>();
		bind(set_current_widget) .to <&T::setCurrentWidget>();
	}

public:

//-----------------------------------------------------------------------------

	// QStackedLayout
	signal <void (int)> widget_removed;
	signal <void (int)> current_changed;

	// QStackedLayout
	slot<void (int)>      set_current_index;
	slot<void (QWidget*)> set_current_widget;

//-----------------------------------------------------------------------------

	stacked_layout() :
		QStackedLayout() { init(); }

	explicit stacked_layout(QWidget* parent) :
		QStackedLayout(parent) { init(); }

	explicit stacked_layout(QLayout* parent_layout) :
		QStackedLayout(parent_layout) { init(); }

};

//-----------------------------------------------------------------------------

inline QStackedLayout&
operator<<(QStackedLayout& s, QWidget* w) { s.addWidget(w); return s; }

inline QStackedLayout&
operator<<(QStackedLayout& s, QLayoutItem* i) { s.addItem(i); return s; }

//-----------------------------------------------------------------------------

} // qt_details

using qt_details::stacked_layout;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_STACKED_LAYOUT_HPP
