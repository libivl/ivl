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

#ifndef IVL_QT_GUI_WIDGETS_GROUP_BOX_HPP
#define IVL_QT_GUI_WIDGETS_GROUP_BOX_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QGroupBox>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ group_box : public QGroupBox,
	public widget_base <group_box>,
	public method_binder <group_box, QGroupBox>
{
	Q_OBJECT
	typedef QGroupBox T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QGroupBox
	void clicked_(bool checked) { clicked(checked); }
	void toggled_(bool checked) { toggled(checked); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QGroupBox
		connect(this, SIGNAL(clicked(bool)), SLOT(clicked_(bool)));
		connect(this, SIGNAL(toggled(bool)), SLOT(toggled_(bool)));

		// QGroupBox
		bind(set_checked).to <&T::setChecked>();
	}

//-----------------------------------------------------------------------------

	typedef defaults <void (bool), c_false>
	clicked_signature;  // defaults: (bool checked = false)

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QGroupBox
	signal <clicked_signature>  clicked;
	signal <void (bool)>        toggled;

	// QGroupBox
	slot <void (bool)> set_checked;

//-----------------------------------------------------------------------------

	explicit group_box(QWidget* parent = 0) :
		QGroupBox(parent) { init(); }

	explicit group_box(const QString& title, QWidget* parent = 0) :
		QGroupBox(title, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::group_box;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_GROUP_BOX_HPP
