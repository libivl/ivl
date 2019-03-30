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

#ifndef IVL_QT_GUI_KERNEL_WIDGET_BASE_HPP
#define IVL_QT_GUI_KERNEL_WIDGET_BASE_HPP

#include <QWidget>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

template <typename W>
class widget_base
{
	W& derived() { return static_cast <W&>(*this); }

	class tab_order_struct
	{
		QWidget *last_widget;

	public:
		tab_order_struct() : last_widget(0) { }

		tab_order_struct& operator<<(QWidget *w)
		{
			if(last_widget)
				W::setTabOrder(last_widget, w);
			last_widget = w;
			return *this;
		}
	};

public:
	tab_order_struct tab_order;
};

//-----------------------------------------------------------------------------

}  // qt_details

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_WIDGET_BASE_HPP
