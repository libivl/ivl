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

#ifndef IVL_QT_GUI_WIDGETS_MAIN_WINDOW_HPP
#define IVL_QT_GUI_WIDGETS_MAIN_WINDOW_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QMainWindow>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ main_window : public QMainWindow,
	public widget_base <main_window>,
	public method_binder <main_window, QMainWindow>
{
	Q_OBJECT
	typedef QMainWindow T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QMainWindow
	void iconSizeChanged_(const QSize& s)               { icon_size_changed(s); }
	void toolButtonStyleChanged_(Qt::ToolButtonStyle s) { tool_button_style_changed(s); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QMainWindow
		connect(this, SIGNAL(iconSizeChanged (const QSize&)),
		              SLOT  (iconSizeChanged_(const QSize&)));
		connect(this, SIGNAL(toolButtonStyleChanged (Qt::ToolButtonStyle)),
		              SLOT  (toolButtonStyleChanged_(Qt::ToolButtonStyle)));

		// QMainWindow
#ifndef QT_NO_DOCKWIDGET
		bind(set_animated)             .to <&T::setAnimated>();
		bind(set_dock_nesting_enabled) .to <&T::setDockNestingEnabled>();
#endif
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QMainWindow
	signal <void (const QSize&)>        icon_size_changed;
	signal <void (Qt::ToolButtonStyle)> tool_button_style_changed;

	// QMainWindow
#ifndef QT_NO_DOCKWIDGET
	slot <void (bool)> set_animated;
	slot <void (bool)> set_dock_nesting_enabled;
#endif

//-----------------------------------------------------------------------------

	explicit main_window(QWidget* parent = 0, Qt::WindowFlags flags = 0) :
		QMainWindow(parent, flags) { init(); }

};

//-----------------------------------------------------------------------------

#ifndef QT_NO_TOOLBAR
inline QMainWindow&
operator<<(QMainWindow& w, QToolBar* t) { w.addToolBar(t); return w; }

inline QMainWindow&
operator<<(QMainWindow& w, const QString& title) { w.addToolBar(title); return w; }
#endif

// TODO
// addDockWidget ( Qt::DockWidgetArea area, QDockWidget * dockwidget )
// addDockWidget ( Qt::DockWidgetArea area, QDockWidget * dockwidget, Qt::Orientation orientation )
// addToolBar ( Qt::ToolBarArea area, QToolBar * toolbar )
// addToolBar ( QToolBar * toolbar )
// addToolBar ( const QString & title )
// addToolBarBreak ( Qt::ToolBarArea area = Qt::TopToolBarArea )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::main_window;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_MAIN_WINDOW_HPP
