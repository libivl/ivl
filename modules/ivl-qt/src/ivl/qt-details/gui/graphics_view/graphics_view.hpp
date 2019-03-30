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

#ifndef IVL_QT_GUI_GRAPHICS_VIEW_GRAPHICS_VIEW_HPP
#define IVL_QT_GUI_GRAPHICS_VIEW_GRAPHICS_VIEW_HPP

#include "../../core.hpp"
#include <QGraphicsView>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ graphics_view : public QGraphicsView,
	public method_binder <graphics_view, QGraphicsView>
{
	Q_OBJECT
	typedef QGraphicsView T;

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QGraphicsView
		bind(update_scene)      .to <T, &T::updateScene>();
		bind(invalidate_scene)  .to <T, &T::invalidateScene,
		                             c_struct <QRectF>,
		                             c_enum <QGraphicsScene::SceneLayer, QGraphicsScene::AllLayers> >();
		                             // defaults: (const QRectF& rect = QRectF(), QGraphicsScene::SceneLayers layers = AllLayers)
		bind(update_scene_rect) .to <T, &T::updateSceneRect>();
	}

public:

//-----------------------------------------------------------------------------

	// QGraphicsView
	slot <void (const QList <QRectF>&)>                      update_scene;
	slot <void (const QRectF&, QGraphicsScene::SceneLayers)> invalidate_scene;
	slot <void (const QRectF&)>                              update_scene_rect;

//-----------------------------------------------------------------------------

	graphics_view(QWidget* parent = 0) :
		QGraphicsView(parent) { init(); }

	graphics_view(QGraphicsScene* scene, QWidget* parent = 0) :
		QGraphicsView(scene, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::graphics_view;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_GRAPHICS_VIEW_GRAPHICS_VIEW_HPP
