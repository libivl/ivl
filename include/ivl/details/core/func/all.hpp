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

#ifndef IVL_CORE_DETAILS_FUNC_ALL_HPP
#define IVL_CORE_DETAILS_FUNC_ALL_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

struct all_impl : public ivl_func<all_impl>
{
	struct op_impl {
		template <class T>
		bool operator()(bool& s, const T& v) {
			return v ? false : (s = false, true);
		}
	} op;

	/**
	 * \brief True if all elements are nonzero
	 */
	template<class J, class T, class S>
	void operate(J& s, sep, const array<T, S>& a)
	{
		s = reduce[yn][cond] (op) (a, true);
	}

	template<class T, class S>
	T operator()(const array<T, S>& a)
	{
		return call<T>(a);
	}

	/**
	 * \brief Index all elements of an array
	 */
	inline
	index_array_all_type operator()()
	{
		return index_array_all_type();
	}

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun { typedef func_details::all_impl all; }

static __attribute__ ((unused)) fun::all all;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_FUNC_ALL_HPP
