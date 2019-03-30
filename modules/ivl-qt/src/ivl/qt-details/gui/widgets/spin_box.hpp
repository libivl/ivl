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

#ifndef IVL_QT_GUI_WIDGETS_SPIN_BOX_HPP
#define IVL_QT_GUI_WIDGETS_SPIN_BOX_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QSpinBox>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ spin_box : public QSpinBox, public widget_base <spin_box>,
	public method_binder <spin_box, QSpinBox>
{
	Q_OBJECT
	typedef QSpinBox T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QAbstractSpinBox
	void editingFinished_() { editing_finished(); }

	// QSpinBox
	void valueChanged_(int v)            { value_changed_0(v); }  // TODO: overloading
	void valueChanged_(const QString& s) { value_changed_1(s); }  // TODO: overloading

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractSpinBox
		#include "abstract_spin_box_init.hpp"

		// QSpinBox
		connect(this, SIGNAL(valueChanged(int)),            SLOT(valueChanged_(int)));
		connect(this, SIGNAL(valueChanged(const QString&)), SLOT(valueChanged_(const QString&)));

		// QSpinBox
		bind(set_value)  .to <&T::setValue>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractSpinBox
	#include "abstract_spin_box_decl.hpp"

	// QSpinBox
	signal <void (int)>            value_changed_0;  // TODO: overloading
	signal <void (const QString&)> value_changed_1;  // TODO: overloading

	// QSpinBox
	slot <void (int)>              set_value;

//-----------------------------------------------------------------------------

	explicit spin_box(QWidget* parent = 0) :
		QSpinBox(parent) { init(); }

};

//-----------------------------------------------------------------------------

class _ivlqt_export_ double_spin_box : public QDoubleSpinBox,
	public method_binder <double_spin_box, QDoubleSpinBox, QAbstractSpinBox>
{
	Q_OBJECT
	typedef QDoubleSpinBox T;
	typedef QAbstractSpinBox B;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QAbstractSpinBox
	void editingFinished_() { editing_finished(); }

	// QDoubleSpinBox
	void valueChanged_(double v)         { value_changed_0(v); }  // TODO: overloading
	void valueChanged_(const QString& s) { value_changed_1(s); }  // TODO: overloading

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractSpinBox
		connect(this, SIGNAL(editingFinished()),            SLOT(editingFinished_()));

		// QDoubleSpinBox
		connect(this, SIGNAL(valueChanged(double)),         SLOT(valueChanged_(double)));
		connect(this, SIGNAL(valueChanged(const QString&)), SLOT(valueChanged_(const QString&)));

		// QAbstractSpinBox
		bind(step_up)    .to <&B::stepUp>();
		bind(step_down)  .to <&B::stepDown>();
		bind(select_all) .to <&B::selectAll>();
		bind(clear)      .to <&B::clear>();

		// QDoubleSpinBox
		bind(set_value)  .to <&T::setValue>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractSpinBox
	signal <void ()> editing_finished;

	// QAbstractSpinBox
	slot <void ()>   step_up;
	slot <void ()>   step_down;
	slot <void ()>   select_all;
	slot <void ()>   clear;

	// QDoubleSpinBox
	signal <void (double)>         value_changed_0;  // TODO: overloading
	signal <void (const QString&)> value_changed_1;  // TODO: overloading

	// QDoubleSpinBox
	slot <void (double)>           set_value;

//-----------------------------------------------------------------------------

	explicit double_spin_box(QWidget* parent = 0) :
		QDoubleSpinBox(parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::spin_box;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_SPIN_BOX_HPP
