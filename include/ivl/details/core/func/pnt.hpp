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

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_DETAILS_FUNC_PNT_HPP
#define IVL_CORE_DETAILS_FUNC_PNT_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace core_details {

template <class J, class J1, class J2>
struct pnt_
{
	typedef types::number<0> cost;
	static inline point<int> elem_op(int y, int x)
	{
		return ivl::point<int>(y, x);
	}
};

} // namespace core_details
static __attribute__ ((unused)) struct pnt_impl : public ivl_func<pnt_impl>,
	public binary_elem_base<point<int>, int, int, core_details::pnt_>
{
	typedef binary_elem_base<point<int>, int, int, core_details::pnt_> pnt_base;

	using pnt_base::operator();
	using pnt_base::operator[];

	//TODO: proper elem func
	/*
	template <class T>
	point<T, 2> operator()(const T& x, const T& y)
	{
		return point<T, 2>(x, y);
	}
	*/

	template <class T>
	point<T, 3> operator()(const T& x, const T& y, const T& z)
	{
		return point<T, 3>(x, y, z);
	}

} pnt;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_FUNC_PNT_HPP
