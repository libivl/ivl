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

#ifndef IVL_QT_GUI_KERNEL_BOX_LAYOUT_HPP
#define IVL_QT_GUI_KERNEL_BOX_LAYOUT_HPP

#include <QBoxLayout>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

template <typename L>
class box_layout_base
{
	L& derived() { return static_cast <L&>(*this); }

protected:

	void add(QLayout* layout, int s = 0, ivl::alignment = none)
	{
		derived().addLayout(layout, s);
	}

	void add(QSpacerItem* item, int = 0, ivl::alignment = none)
	{
		derived().addSpacerItem(item);
	}

	void add(QWidget* widget, int s = 0, ivl::alignment a = none)
	{
		derived().addWidget(widget, s, a);
	}

//-----------------------------------------------------------------------------

	template <typename T>
	void add(const obj_stretch_arg <T>& stretch, int s = 0, ivl::alignment a = none)
	{
		add(stretch.object, stretch, a);
	}

	template <typename T>
	void add(const align_arg <T>& align, int s = 0, ivl::alignment a = none)
	{
		add(align.object, s, align);
	}

//-----------------------------------------------------------------------------

	void add(spacing_arg s) { derived().addSpacing(s); }
	void add(stretch_arg s) { derived().addStretch(s); }

public:

//-----------------------------------------------------------------------------

	template <typename T>
	L& operator<<(T& o) { add(o); return derived(); }

	template <typename T>
	L& operator<<(const T& o) { add(o); return derived(); }

};

//-----------------------------------------------------------------------------

struct row_layout : public QHBoxLayout,
	public box_layout_base <row_layout>
{
	row_layout() : QHBoxLayout() { }
	explicit row_layout(QWidget* parent) : QHBoxLayout(parent) { }
};

struct col_layout : public QVBoxLayout,
	public box_layout_base <col_layout>
{
	col_layout() : QVBoxLayout() { }
	explicit col_layout(QWidget* parent) : QVBoxLayout(parent) { }
};

//-----------------------------------------------------------------------------

} // qt_details

using qt_details::row_layout;
using qt_details::col_layout;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_BOX_LAYOUT_HPP
