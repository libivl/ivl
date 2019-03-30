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

#ifndef IVL_QT_CORE_TYPES_HPP
#define IVL_QT_CORE_TYPES_HPP

#include <qnamespace.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

using namespace ivl::types;

//-----------------------------------------------------------------------------

template <typename T>
class wrapper
{
	T value;
public:
	typedef T type;
	wrapper(T v) : value(v) { }
	operator T() const { return value; }
	T operator*() const { return value; }
};

//-----------------------------------------------------------------------------

template <typename T>
struct object_arg
{
	T& object;
	object_arg(T& o) : object(o) { }
};

//-----------------------------------------------------------------------------

struct separator_arg { };

//-----------------------------------------------------------------------------

struct spacing_arg : wrapper <int>
{
	spacing_arg(int v) : wrapper <int>(v) { }
};

//-----------------------------------------------------------------------------

struct closed_stretch_arg;

template <typename T>
struct obj_stretch_arg;

struct stretch_arg : wrapper <int>,
	constructor <closed_stretch_arg (int)>
{
	stretch_arg(int v = 0) : wrapper <int>(v) { }
};

struct closed_stretch_arg : stretch_arg,
	constructor <obj_stretch_arg <_> (), closed_stretch_arg>
{
	using constructor <obj_stretch_arg <_> (), closed_stretch_arg>::operator();
	closed_stretch_arg(int v) : stretch_arg(v) { }
};

template <typename T>
struct obj_stretch_arg : object_arg <T>, wrapper <int>
{
	obj_stretch_arg(T& o, int s) : object_arg <T>(o), wrapper <int>(s) { }
};

//-----------------------------------------------------------------------------

template <typename T>
struct align_arg;

struct alignment : wrapper <Qt::Alignment>,
	constructor <align_arg <_> (), alignment>
{
	typedef wrapper <Qt::Alignment> W;
	alignment(Qt::Alignment a) : W(a) { }
	alignment operator|(alignment a) const { return **this | *a; }
};

template <typename T>
struct align_arg : object_arg <T>, wrapper <alignment>
{
	typedef wrapper <alignment> W;
	align_arg(T& o, alignment a) : object_arg <T>(o), W(a) { }
};

//-----------------------------------------------------------------------------

static  __attribute__ ((unused))
separator_arg separator;

static  __attribute__ ((unused))
constructor <spacing_arg (int)> spacing;

static  __attribute__ ((unused))
stretch_arg stretch;

static  __attribute__ ((unused))
alignment left(Qt::AlignLeft), right(Qt::AlignRight), center(Qt::AlignHCenter),
          top(Qt::AlignTop), bottom(Qt::AlignBottom), middle(Qt::AlignVCenter),
          justify(Qt::AlignJustify), none(Qt::Alignment(0));

//-----------------------------------------------------------------------------

}  // namespace qt_details

//-----------------------------------------------------------------------------

using qt_details::separator;
using qt_details::spacing;
using qt_details::stretch;
using qt_details::alignment;
using qt_details::left;
using qt_details::right;
using qt_details::center;
using qt_details::top;
using qt_details::bottom;
using qt_details::middle;
using qt_details::justify;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_TYPES_HPP
