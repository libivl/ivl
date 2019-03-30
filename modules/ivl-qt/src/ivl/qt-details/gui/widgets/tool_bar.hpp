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

#ifndef IVL_QT_GUI_WIDGETS_TOOL_BAR_HPP
#define IVL_QT_GUI_WIDGETS_TOOL_BAR_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QToolBar>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ tool_bar : public QToolBar, public widget_base <tool_bar>,
	public method_binder <tool_bar, QToolBar>
{
	Q_OBJECT
	typedef QToolBar T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QToolBar
	void actionTriggered_(QAction *action)                  { action_triggered(action); }
	void movableChanged_(bool movable)                      { movable_changed(movable); }
	void allowedAreasChanged_(Qt::ToolBarAreas areas)       { allowed_areas_changed(areas); }
	void orientationChanged_(Qt::Orientation orientation)   { orientation_changed(orientation); }
	void iconSizeChanged_(const QSize &iconSize)            { icon_size_changed(iconSize); }
	void toolButtonStyleChanged_(Qt::ToolButtonStyle style) { tool_button_style_changed(style); }
	void topLevelChanged_(bool topLevel)                    { top_level_changed(topLevel); }
	void visibilityChanged_(bool visible)                   { visibility_changed(visible); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QToolBar
		connect(this, SIGNAL(actionTriggered(QAction*)),                   SLOT(actionTriggered_(QAction*)));
		connect(this, SIGNAL(movableChanged(bool)),                        SLOT(movableChanged_(bool)));
		connect(this, SIGNAL(allowedAreasChanged(Qt::ToolBarAreas)),       SLOT(allowedAreasChanged_(Qt::ToolBarAreas)));
		connect(this, SIGNAL(orientationChanged(Qt::Orientation)),         SLOT(orientationChanged_(Qt::Orientation)));
		connect(this, SIGNAL(iconSizeChanged(const QSize&)),               SLOT(iconSizeChanged_(const QSize&)));
		connect(this, SIGNAL(toolButtonStyleChanged(Qt::ToolButtonStyle)), SLOT(toolButtonStyleChanged_(Qt::ToolButtonStyle)));
		connect(this, SIGNAL(topLevelChanged(bool)),                       SLOT(topLevelChanged_(bool)));
		connect(this, SIGNAL(visibilityChanged(bool)),                     SLOT(visibilityChanged_(bool)));

		// QToolBar
		bind(set_icon_size)         .to <&T::setIconSize>();
		bind(set_tool_button_style) .to <&T::setToolButtonStyle>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QToolBar
	signal <void (QAction*)>             action_triggered;
	signal <void (bool)>                 movable_changed;
	signal <void (Qt::ToolBarAreas)>     allowed_areas_changed;
	signal <void (Qt::Orientation)>      orientation_changed;
	signal <void (const QSize&)>         icon_size_changed;
	signal <void (Qt::ToolButtonStyle)>  tool_button_style_changed;
	signal <void (bool)>                 top_level_changed;
	signal <void (bool)>                 visibility_changed;

	// QToolBar
	slot <void (const QSize&)>        set_icon_size;
	slot <void (Qt::ToolButtonStyle)> set_tool_button_style;

//-----------------------------------------------------------------------------

	explicit tool_bar(QWidget* parent = 0) :
		QToolBar(parent) { init(); }

	explicit tool_bar(const QString &title, QWidget* parent = 0) :
		QToolBar(title, parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QToolBar&
operator<<(QToolBar& t, const QString& text) { t.addAction(text); return t; }

inline QToolBar&
operator<<(QToolBar& t, QAction* a) { t.addAction(a); return t; }

inline QToolBar&
operator<<(QToolBar& t, QWidget* w) { t.addWidget(w); return t; }

inline QToolBar&
operator<<(QToolBar& t, separator_arg) { t.addSeparator(); return t; }

// TODO
// addAction ( QAction * action )
// addAction ( const QString & text )
// addAction ( const QIcon & icon, const QString & text )
// addAction ( const QString & text, const QObject * receiver, const char * member )
// addAction ( const QIcon & icon, const QString & text, const QObject * receiver, const char * member )
// addSeparator ()
// addWidget ( QWidget * widget )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::tool_bar;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_TOOL_BAR_HPP
