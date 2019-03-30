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

#ifndef IVL_QT_GUI_GRAPHICS_VIEW_GRAPHICS_SCENE_HPP
#define IVL_QT_GUI_GRAPHICS_VIEW_GRAPHICS_SCENE_HPP

#include "../../core.hpp"
#include <QGraphicsScene>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ graphics_scene : public QGraphicsScene,
	public method_binder <graphics_scene, QGraphicsScene>
{
	Q_OBJECT
	typedef QGraphicsScene T;

private slots:

	// QGraphicsScene
    void changed_(const QList<QRectF>& region) { changed(region); }
    void sceneRectChanged_(const QRectF& rect) { scene_rect_changed(rect); }
    void selectionChanged_()                   { selection_changed(); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QGraphicsScene
		connect(this, SIGNAL(changed(const QList<QRectF>&)),   SLOT(changed_(const QList<QRectF>&)));
		connect(this, SIGNAL(sceneRectChanged(const QRectF&)), SLOT(sceneRectChanged_(const QRectF&)));
		connect(this, SIGNAL(selectionChanged()),              SLOT(selectionChanged_()));

		// QGraphicsScene
		bind(update)          .to <T, &T::update,
		                           c_struct <QRectF> >();
		                           // defaults: (const QRectF& rect = QRectF())
		bind(invalidate)      .to <T, &T::invalidate,
		                           c_struct <QRectF>, c_enum <SceneLayer, AllLayers> >();
		                           // defaults: (const QRectF& rect = QRectF(), SceneLayers layers = AllLayers)
		bind(advance)         .to <&T::advance>();
		bind(clear_selection) .to <&T::clearSelection>();
		bind(clear)           .to <&T::clear>();
	}

public:

//-----------------------------------------------------------------------------

	// QGraphicsScene
	signal <void (const QList<QRectF>&)> changed;
	signal <void (const QRectF&)>        scene_rect_changed;
	signal <void ()>                     selection_changed;

	// QGraphicsScene
	slot <void (const QRectF&)>               update;
	slot <void (const QRectF&, SceneLayers)>  invalidate;
	slot <void ()>                            advance;
	slot <void ()>                            clear_selection;
	slot <void ()>                            clear;

//-----------------------------------------------------------------------------

	graphics_scene(QObject* parent = 0) :
		QGraphicsScene(parent) { init(); }

	graphics_scene(const QRectF& scene_rect, QObject* parent = 0) :
		QGraphicsScene(scene_rect, parent) { init(); }

	graphics_scene(qreal x, qreal y, qreal width, qreal height,
						QObject *parent = 0) :
		QGraphicsScene(x, y, width, height, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::graphics_scene;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_GRAPHICS_VIEW_GRAPHICS_SCENE_HPP
