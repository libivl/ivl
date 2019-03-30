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

#ifndef IVL_QT_GUI_WIDGETS_SLIDER_HPP
#define IVL_QT_GUI_WIDGETS_SLIDER_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QSlider>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ slider : public QSlider, public widget_base <slider>,
	public method_binder <slider, QSlider, QAbstractSlider>
{
	Q_OBJECT
	typedef QSlider T;
	typedef QAbstractSlider B;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QAbstractSlider
	void valueChanged_(int value)          { value_changed(value); }
	void sliderPressed_()                  { slider_pressed(); }
	void sliderMoved_(int position)        { slider_moved(position); }
	void sliderReleased_()                 { slider_released(); }
	void rangeChanged_(int min, int max)   { range_changed(min, max); }
	void actionTriggered_(int action)      { action_triggered(action); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractSlider
		connect(this, SIGNAL(valueChanged(int)),      SLOT(valueChanged_(int)));
		connect(this, SIGNAL(sliderPressed()),        SLOT(sliderPressed_()));
		connect(this, SIGNAL(sliderMoved(int)),       SLOT(sliderMoved_(int)));
		connect(this, SIGNAL(sliderReleased()),       SLOT(sliderReleased_()));
		connect(this, SIGNAL(rangeChanged(int, int)), SLOT(rangeChanged_(int, int)));
		connect(this, SIGNAL(actionTriggered(int)),   SLOT(actionTriggered_(int)));

		// QAbstractSlider
		bind(set_value)        .to <&B::setValue>();
		bind(set_orientation)  .to <&B::setOrientation>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractSlider
	signal <void (int)>      value_changed;
	signal <void ()>         slider_pressed;
	signal <void (int)>      slider_moved;
	signal <void ()>         slider_released;
	signal <void (int, int)> range_changed;
	signal <void (int)>      action_triggered;

	// QAbstractSlider
	slot <void (int)>             set_value;
	slot <void (Qt::Orientation)> set_orientation;

//-----------------------------------------------------------------------------

	explicit slider(QWidget* parent = 0) :
		QSlider(parent) { init(); }

	explicit slider(Qt::Orientation orientation, QWidget* parent = 0) :
		QSlider(orientation, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::slider;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_SLIDER_HPP
