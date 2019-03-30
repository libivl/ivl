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

#ifndef IVL_QT_GUI_WIDGETS_MENU_HPP
#define IVL_QT_GUI_WIDGETS_MENU_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QMenu>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ menu : public QMenu, public widget_base <menu>,
	public method_binder <menu, QMenu>
{
	Q_OBJECT
	typedef QMenu T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QMenu
	void aboutToShow_()           { about_to_show(); }
	void aboutToHide_()           { about_to_hide(); }
	void triggered_(QAction *a)   { triggered(a); }
	void hovered_(QAction *a)     { hovered(a); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QMenu
		connect(this, SIGNAL(aboutToShow()),        SLOT(aboutToShow_()));
		connect(this, SIGNAL(aboutToHide()),        SLOT(aboutToHide_()));
		connect(this, SIGNAL(triggered(QAction*)),  SLOT(triggered_(QAction*)));
		connect(this, SIGNAL(hovered(QAction*)),    SLOT(hovered_(QAction*)));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QMenu
	signal <void ()>          about_to_show;
	signal <void ()>          about_to_hide;
	signal <void (QAction*)>  triggered;
	signal <void (QAction*)>  hovered;

//-----------------------------------------------------------------------------

	explicit menu(QWidget* parent = 0) :
		QMenu(parent) { init(); }

	explicit menu(const QString &title, QWidget* parent = 0) :
		QMenu(title, parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QMenu&
operator<<(QMenu& m, const QString& text) { m.addAction(text); return m; }

inline QMenu& operator<<(QMenu& m, QAction* a) { m.addAction(a); return m; }
inline QMenu& operator<<(QMenu& m, QMenu* s)   { m.addMenu(s);   return m; }

inline QMenu&
operator<<(QMenu& m, separator_arg) { m.addSeparator(); return m; }

// TODO
// addAction ( const QString & text )
// addAction ( const QIcon & icon, const QString & text )
// addAction ( const QString & text, const QObject * receiver, const char * member, const QKeySequence & shortcut = 0 )
// addAction ( const QIcon & icon, const QString & text, const QObject * receiver, const char * member, const QKeySequence & shortcut = 0 )
// addAction ( QAction * action )
// addMenu ( QMenu * menu )
// addMenu ( const QString & title )
// addMenu ( const QIcon & icon, const QString & title )
// addSeparator ()

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::menu;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_MENU_HPP
