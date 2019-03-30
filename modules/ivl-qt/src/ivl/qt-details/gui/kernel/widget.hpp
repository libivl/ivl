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

#ifndef IVL_QT_GUI_KERNEL_WIDGET_HPP
#define IVL_QT_GUI_KERNEL_WIDGET_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QWidget>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ widget : public QWidget, public widget_base <widget>,
	public method_binder <widget, QWidget>
{
	Q_OBJECT

private slots:
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

private:
	void init()
	{
		#include "../kernel/widget_init.hpp"
	}

public:
	#include "../kernel/widget_decl.hpp"

	explicit widget(QWidget* parent = 0, Qt::WindowFlags flags = 0) :
		QWidget(parent, flags) { init(); }

};

//-----------------------------------------------------------------------------

inline QWidget&
operator<<(QWidget& w, QAction* a) { w.addAction(a); return w; }

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::widget;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_WIDGET_HPP
