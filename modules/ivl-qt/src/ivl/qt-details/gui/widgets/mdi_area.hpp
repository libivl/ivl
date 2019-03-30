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

#ifndef IVL_QT_GUI_WIDGETS_MDI_AREA_HPP
#define IVL_QT_GUI_WIDGETS_MDI_AREA_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QMdiArea>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ mdi_area : public QMdiArea,
	public widget_base <mdi_area>,
	public method_binder <mdi_area, QMdiArea>
{
	Q_OBJECT
	typedef QMdiArea T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QMdiArea
	void subWindowActivated_(QMdiSubWindow* window) { sub_window_activated(window); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QMdiArea
		connect(this, SIGNAL(subWindowActivated(QMdiSubWindow*)), SLOT(subWindowActivated_(QMdiSubWindow*)));

		// QMdiArea
		bind(set_active_subWindow)         .to <&T::setActiveSubWindow>();
		bind(tile_sub_windows)             .to <&T::tileSubWindows>();
		bind(cascade_sub_windows)          .to <&T::cascadeSubWindows>();
		bind(close_active_sub_window)      .to <&T::closeActiveSubWindow>();
		bind(close_all_sub_windows)        .to <&T::closeAllSubWindows>();
		bind(activate_next_sub_window)     .to <&T::activateNextSubWindow>();
		bind(activate_previous_sub_window) .to <&T::activatePreviousSubWindow>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QMdiArea
	signal <void (QMdiSubWindow*)> sub_window_activated;

	// QMdiArea
	slot <void (QMdiSubWindow*)> set_active_subWindow;
	slot <void ()>               tile_sub_windows;
	slot <void ()>               cascade_sub_windows;
	slot <void ()>               close_active_sub_window;
	slot <void ()>               close_all_sub_windows;
	slot <void ()>               activate_next_sub_window;
	slot <void ()>               activate_previous_sub_window;

//-----------------------------------------------------------------------------

	explicit mdi_area(QWidget* parent = 0) :
		QMdiArea(parent) { init(); }

};

//-----------------------------------------------------------------------------

// TODO: QMdiSubWindow

//-----------------------------------------------------------------------------

inline QMdiArea&
operator<<(QMdiArea& a, QWidget* w) { a.addSubWindow(w); return a; }

// TODO
// addSubWindow ( QWidget * widget, Qt::WindowFlags windowFlags = 0 )
// addScrollBarWidget ( QWidget * widget, Qt::Alignment alignment )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::mdi_area;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_MDI_AREA_HPP
