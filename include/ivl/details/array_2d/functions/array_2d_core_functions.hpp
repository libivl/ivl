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

#ifndef IVL_ARRAY_2D_DETAILS_ARRAY_2D_CORE_FUNCTIONS_HPP
#define IVL_ARRAY_2D_DETAILS_ARRAY_2D_CORE_FUNCTIONS_HPP


namespace ivl {

template <class T, class S>
inline
array_2d<T> row(const array<T, S>& a)
{
	return array_2d<T>(1, a.length(), a);
}

template <class T, class S>
inline
array_2d<T> col(const array<T, S>& a)
{
	return array_nd<T>(a.length(), 1, a);
}

template <class T>
inline
array_2d<T, data::fixed<1> > cell(const T& t)
{
	return array_2d<T>(1, 1, t);
}

template <class T, class T1>
inline
array_2d<T, data::fixed<2> > row(const T& t0, const T1 & t1)
{
	array_2d<T> a(1, 2);
	a[0] = t0; a[1] = t1;
	return a;
}

template <class T, class T1, class T2>
inline
array_2d<T, data::fixed<3> > row(const T& t0, const T1 & t1, const T2 & t2)
{
	array_2d<T> a(1, 3);
	a[0] = t0; a[1] = t1; a[2] = t2;
	return a;
}

template <class T, class T1, class T2, class T3>
inline
array_2d<T, data::fixed<4> > row(const T& t0, const T1 & t1, const T2 & t2, const T3 & t3)
{
	array_2d<T> a(1, 4);
	a[0] = t0; a[1] = t1; a[2] = t2; a[3] = t3;
	return a;
}

template <class T, class T1>
inline
array_2d<T, data::fixed<2> > col(const T& t0, const T1 & t1)
{
	array_2d<T> a(2, 1);
	a[0] = t0; a[1] = t1;
	return a;
}

template <class T, class T1, class T2>
inline
array_2d<T, data::fixed<3> > col(const T& t0, const T1 & t1, const T2 & t2)
{
	array_2d<T> a(3, 1);
	a[0] = t0; a[1] = t1; a[2] = t2;
	return a;
}

template <class T, class T1, class T2, class T3>
inline
array_2d<T, data::fixed<4> > col(const T& t0, const T1 & t1, const T2 & t2, const T3 & t3)
{
	array_2d<T> a(4, 1);
	a[0] = t0; a[1] = t1; a[2] = t2; a[3] = t3;
	return a;
}



} /* namespace ivl */

#endif // IVL_ARRAY_2D_DETAILS_ARRAY_2D_CORE_FUNCTIONS_HPP
