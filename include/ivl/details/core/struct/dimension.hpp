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

#ifndef IVL_CORE_DETAILS_TYPES_DIMENSION_HPP
#define IVL_CORE_DETAILS_TYPES_DIMENSION_HPP

namespace ivl {

//-----------------------------------------------------------------------------

struct dim_impl;

class dimension {
	size_t d;

public:
	dimension(size_t d = 0) : d(d) { }
	operator size_t() const { return d; }
};

struct dim_impl {
	dimension operator()(size_t d) { return dimension(d); }
};

static __attribute__ ((unused))
dim_impl dim;

//-----------------------------------------------------------------------------

static __attribute__ ((unused))  dimension _0 = dim(0);
static __attribute__ ((unused))  dimension _1 = dim(1);
static __attribute__ ((unused))  dimension _2 = dim(2);
static __attribute__ ((unused))  dimension _3 = dim(3);
static __attribute__ ((unused))  dimension _4 = dim(4);
static __attribute__ ((unused))  dimension _5 = dim(5);
static __attribute__ ((unused))  dimension _6 = dim(6);
static __attribute__ ((unused))  dimension _7 = dim(7);
static __attribute__ ((unused))  dimension _8 = dim(8);
static __attribute__ ((unused))  dimension _9 = dim(9);

static __attribute__ ((unused))  dimension _i = dim(0);
static __attribute__ ((unused))  dimension _j = dim(1);
static __attribute__ ((unused))  dimension _k = dim(2);
static __attribute__ ((unused))  dimension _l = dim(3);
static __attribute__ ((unused))  dimension _m = dim(4);
static __attribute__ ((unused))  dimension _n = dim(5);

//-----------------------------------------------------------------------------

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_DIMENSION_HPP

