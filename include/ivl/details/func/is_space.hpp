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

#ifndef IVL_FUNC_IS_SPACE_HPP
#define IVL_FUNC_IS_SPACE_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

class is_space_impl : public ivl_func <is_space_impl>
{
	template <class C>
	struct F : public types::maps::id <bool>, public fun::costs <12>
	{
		bool operator()(const C& c) { return ::isspace(c) != 0; }
	};

public:

//-----------------------------------------------------------------------------

	template <class A>
	typename unary_elem_call <F, A>::type
	operator()(const A& a) { return unary_elem_call <F, A>::from(a); }

	template <class I, class A>
	void operate(I& i, sep, const A& a) { i = (*this)(a); }
};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun { typedef func_details::is_space_impl is_space; }

static  __attribute__ ((unused)) fun::is_space is_space;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUNC_IS_SPACE_HPP
