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

#ifndef IVL_QT_GUI_WIDGETS_DOCK_WIDGET_HPP
#define IVL_QT_GUI_WIDGETS_DOCK_WIDGET_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QDockWidget>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ dock_widget : public QDockWidget, public widget_base <dock_widget>,
	public method_binder <dock_widget, QDockWidget>
{
	Q_OBJECT
	typedef QDockWidget T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QDockWidget
	void featuresChanged_(QDockWidget::DockWidgetFeatures features) { features_changed(features); }
	void topLevelChanged_(bool top_level)                           { top_level_changed(top_level); }
	void allowedAreasChanged_(Qt::DockWidgetAreas allowed_areas)    { allowed_areas_changed(allowed_areas); }
	void visibilityChanged_(bool visible)                           { visibility_changed(visible); }
	void dockLocationChanged_(Qt::DockWidgetArea area)              { dock_location_changed(area); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QDockWidget
		connect(this, SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)), SLOT(featuresChanged_(QDockWidget::DockWidgetFeatures)));
		connect(this, SIGNAL(topLevelChanged(bool)),                            SLOT(topLevelChanged_(bool)));
		connect(this, SIGNAL(allowedAreasChanged(Qt::DockWidgetAreas)),         SLOT(allowedAreasChanged_(Qt::DockWidgetAreas)));
		connect(this, SIGNAL(visibilityChanged(bool)),                          SLOT(visibilityChanged_(bool)));
		connect(this, SIGNAL(dockLocationChanged(Qt::DockWidgetArea)),          SLOT(dockLocationChanged_(Qt::DockWidgetArea)));

	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QDockWidget
	signal <void (QDockWidget::DockWidgetFeatures)> features_changed;
	signal <void (bool)>                            top_level_changed;
	signal <void (Qt::DockWidgetAreas)>             allowed_areas_changed;
	signal <void (bool)>                            visibility_changed;
	signal <void (Qt::DockWidgetArea)>              dock_location_changed;

//-----------------------------------------------------------------------------

	explicit dock_widget(QWidget* parent = 0, Qt::WindowFlags flags = 0) :
		QDockWidget(parent, flags) { init(); }

	explicit dock_widget(const QString& title, QWidget* parent = 0,
								Qt::WindowFlags flags = 0) :
		QDockWidget(title, parent, flags) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::dock_widget;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_DOCK_WIDGET_HPP
