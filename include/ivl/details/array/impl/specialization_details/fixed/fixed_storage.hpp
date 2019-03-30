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

#ifndef IVL_ARRAY_SPECIALIZATION_DETAILS_FIXED_STORAGE_HPP
#define IVL_ARRAY_SPECIALIZATION_DETAILS_FIXED_STORAGE_HPP

namespace ivl {
namespace array_details {

template<class T, int N, class NAMING>
class fixed_storage
{
public:
	T base_ptr[N];
};

///specialized storage class for points, having y, x, [z] as elements.
template<>
class fixed_storage<size_t, 2, data::point_naming>
{
	typedef size_t t;
public:
	union {
		t base_ptr[2];
		struct { t y; t x; };
		struct { t r; t c; };
	};
};

template<>
class fixed_storage<size_t, 3, data::point_naming>
{
	typedef size_t t;
public:
	union {
		t base_ptr[3];
		struct { t y; t x; t z; };
		struct { t r; t c; };
	};
};

template<>
class fixed_storage<int, 2, data::point_naming>
{
	typedef int t;
public:
	union {
		t base_ptr[2];
		struct { t y; t x; };
		struct { t r; t c; };
	};
};

template<>
class fixed_storage<int, 3, data::point_naming>
{
	typedef int t;
public:
	union {
		t base_ptr[3];
		struct { t y; t x; t z; };
		struct { t r; t c; };
	};
};

template<>
class fixed_storage<double, 2, data::point_naming>
{
	typedef double t;
public:
	union {
		t base_ptr[2];
		struct { t y; t x; };
	};
};

template<>
class fixed_storage<double, 3, data::point_naming>
{
	typedef double t;
public:
	union {
		t base_ptr[3];
		struct { t y; t x; t z; };
	};
};

template<>
class fixed_storage<float, 2, data::point_naming>
{
	typedef float t;
public:
	union {
		t base_ptr[2];
		struct { t y; t x; };
	};
};

template<>
class fixed_storage<float, 3, data::point_naming>
{
	typedef float t;
public:
	union {
		t base_ptr[3];
		struct { t y; t x; t z; };
	};
};

///specialized storage class for dims, having h(eight), w(idth), [d(epth)].
template<>
class fixed_storage<size_t, 2, data::dims_naming>
{
	typedef size_t t;
public:
	union {
		t base_ptr[2];
		struct { t h; t w; };
	};
};

template<>
class fixed_storage<size_t, 3, data::dims_naming>
{
	typedef size_t t;
public:
	union {
		t base_ptr[3];
		struct { t h; t w; t d; };
	};
};

template<>
class fixed_storage<int, 2, data::dims_naming>
{
	typedef int t;
public:
	union {
		t base_ptr[2];
		struct { t h; t w; };
	};
};

template<>
class fixed_storage<int, 3, data::dims_naming>
{
	typedef int t;
public:
	union {
		t base_ptr[3];
		struct { t h; t w; t d; };
	};
};

template<>
class fixed_storage<double, 2, data::dims_naming>
{
	typedef double t;
public:
	union {
		t base_ptr[2];
		struct { t h; t w; };
	};
};

template<>
class fixed_storage<double, 3, data::dims_naming>
{
	typedef double t;
public:
	union {
		t base_ptr[3];
		struct { t h; t w; t d; };
	};
};

template<>
class fixed_storage<float, 2, data::dims_naming>
{
	typedef float t;
public:
	union {
		t base_ptr[2];
		struct { t h; t w; };
	};
};

template<>
class fixed_storage<float, 3, data::dims_naming>
{
	typedef float t;
public:
	union {
		t base_ptr[3];
		struct { t h; t w; t d; };
	};
};

///specialized storage class for colors, having
///gray or r, g, b or r, g, b, a as elements.

template<>
class fixed_storage<unsigned char, 1, data::color_naming>
{
	typedef unsigned char t;
public:
	union {
		t base_ptr[1];
		struct { t gray; };
	};
};

template<>
class fixed_storage<char, 1, data::color_naming>
{
	typedef char t;
public:
	union {
		t base_ptr[1];
		struct { t gray; };
	};
};

template<>
class fixed_storage<short, 1, data::color_naming>
{
	typedef short t;
public:
	union {
		t base_ptr[1];
		struct { t gray; };
	};
};

template<>
class fixed_storage<int, 1, data::color_naming>
{
	typedef int t;
public:
	union {
		t base_ptr[1];
		struct { t gray; };
	};
};

template<>
class fixed_storage<float, 1, data::color_naming>
{
	typedef float t;
public:
	union {
		t base_ptr[1];
		struct { t gray; };
	};
};

template<>
class fixed_storage<double, 1, data::color_naming>
{
	typedef double t;
public:
	union {
		t base_ptr[1];
		struct { t gray; };
	};
};
//
template<>
class fixed_storage<unsigned char, 3, data::color_naming>
{
	typedef unsigned char t;
public:
	union {
		t base_ptr[3];
		struct { t r; t g; t b; };
	};
};

template<>
class fixed_storage<char, 3, data::color_naming>
{
	typedef char t;
public:
	union {
		t base_ptr[3];
		struct { t r; t g; t b; };
	};
};

template<>
class fixed_storage<short, 3, data::color_naming>
{
	typedef short t;
public:
	union {
		t base_ptr[3];
		struct { t r; t g; t b; };
	};
};

template<>
class fixed_storage<int, 3, data::color_naming>
{
	typedef int t;
public:
	union {
		t base_ptr[3];
		struct { t r; t g; t b; };
	};
};

template<>
class fixed_storage<float, 3, data::color_naming>
{
	typedef float t;
public:
	union {
		t base_ptr[3];
		struct { t r; t g; t b; };
	};
};

template<>
class fixed_storage<double, 3, data::color_naming>
{
	typedef double t;
public:
	union {
		t base_ptr[3];
		struct { t r; t g; t b; };
	};
};
//
template<>
class fixed_storage<unsigned char, 4, data::color_naming>
{
	typedef unsigned char t;
public:
	union {
		t base_ptr[4];
		struct { t r; t g; t b; t a; };
	};
};

template<>
class fixed_storage<char, 4, data::color_naming>
{
	typedef char t;
public:
	union {
		t base_ptr[4];
		struct { t r; t g; t b; t a; };
	};
};

template<>
class fixed_storage<short, 4, data::color_naming>
{
	typedef short t;
public:
	union {
		t base_ptr[4];
		struct { t r; t g; t b; t a; };
	};
};

template<>
class fixed_storage<int, 4, data::color_naming>
{
	typedef int t;
public:
	union {
		t base_ptr[4];
		struct { t r; t g; t b; t a; };
	};
};

template<>
class fixed_storage<float, 4, data::color_naming>
{
	typedef float t;
public:
	union {
		t base_ptr[4];
		struct { t r; t g; t b; t a; };
	};
};

template<>
class fixed_storage<double, 4, data::color_naming>
{
	typedef double t;
public:
	union {
		t base_ptr[4];
		struct { t r; t g; t b; t a; };
	};
};
//

} /* namespace array_details */
} /* namespace ivl */

#endif // IVL_ARRAY_SPECIALIZATION_DETAILS_FIXED_STORAGE_HPP
