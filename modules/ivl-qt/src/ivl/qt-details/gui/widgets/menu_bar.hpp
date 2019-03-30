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

#ifndef IVL_QT_GUI_WIDGETS_MENU_BAR_HPP
#define IVL_QT_GUI_WIDGETS_MENU_BAR_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QMenuBar>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ menu_bar : public QMenuBar, public widget_base <menu_bar>,
	public method_binder <menu_bar, QMenuBar>
{
	Q_OBJECT
	typedef QMenuBar T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QMenuBar
	void triggered_(QAction *a)   { triggered(a); }
	void hovered_(QAction *a)     { hovered(a); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QMenuBar
		connect(this, SIGNAL(triggered(QAction*)),  SLOT(triggered_(QAction*)));
		connect(this, SIGNAL(hovered(QAction*)),    SLOT(hovered_(QAction*)));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QMenuBar
	signal <void (QAction*)>  triggered;
	signal <void (QAction*)>  hovered;

	// QMenuBar
	// slot <void (bool)> set_visible;  // available as (virtual) QWidget::set_visible

//-----------------------------------------------------------------------------

	explicit menu_bar(QWidget* parent = 0) :
		QMenuBar(parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QMenuBar&
operator<<(QMenuBar& m, QAction* a) { m.addAction(a); return m; }

inline QMenuBar&
operator<<(QMenuBar& m, QMenu* s) { m.addMenu(s); return m; }

inline QMenuBar&
operator<<(QMenuBar& m, const QString& title) { m.addMenu(title); return m; }

inline QMenuBar&
operator<<(QMenuBar& m, separator_arg) { m.addSeparator(); return m; }

// TODO
// addAction ( const QString & text )
// addAction ( const QString & text, const QObject * receiver, const char * member )
// addAction ( QAction * action )
// addMenu ( QMenu * menu )
// addMenu ( const QString & title )
// addMenu ( const QIcon & icon, const QString & title )
// addSeparator ()

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::menu_bar;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_MENU_BAR_HPP
