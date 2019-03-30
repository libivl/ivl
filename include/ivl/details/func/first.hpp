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

#ifndef IVL_FUNC_FIRST
#define IVL_FUNC_FIRST

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

struct first_ord_impl : public func_details::find_base <first_ord_impl>
{
	using func_details::find_base <first_ord_impl>::operate;

	/**
	 * \brief Find the first non-zero element of an ordered array
	 *
	 * @param a array to search in
	 * @param s offset to start searching from
	 *
	 * @return offset of the first non-zero element, \e a.length() if none found
	 */
	template <class P, class T, class S>
	void operate(P& pos, sep,
					 const array <T, S>& a, size_t s = npos)
	{
		// TODO: a[p] (p: size_t) should cost the same as *p (p: iterator)
		// e.g. in a slice_array

		size_t &from = pos = (s == npos) ? 0 : s, to = a.length(), mid;
		while (from != to) {
			mid = (from + to) / 2;
			if (a[mid]) to = mid;
			else from = mid + 1;
		}
	}

	template <class T, class S>
	size_t operator()(const array<T, S>& a, size_t s = npos)
	{
		return call <size_t> (this)(a, s);
	}

};

//-----------------------------------------------------------------------------

struct first_impl : public func_details::find_base <first_impl>
{
	using func_details::find_base <first_impl>::operate;

	/**
	 * \brief Find the first non-zero element of an array
	 *
	 * @param a array to search in
	 * @param s offset to start searching from
	 *
	 * @return offset of the first non-zero element, \e a.length() if none found
	 */
	template <class P, class T, class S>
	void operate(P& pos, sep,
					 const array <T, S>& a, size_t s = npos)
	{
		pos = (s == npos) ?
		      reduce[sz][off][cond]          (op_cond) (a, a.length()) :
		      reduce[sz][off][cond][begin=s] (op_cond) (a, a.length()) ;
	}

	template <class T, class S>
	size_t operator()(const array<T, S>& a, size_t s = npos)
	{
		return call <size_t>(this)(a, s);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Find first k non-zero elements
	 */
	find_k_impl operator[](const size_t k) { return find_k_impl(k); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Binary search in ordered array
	 */
	first_ord_impl operator[](key::ord) { return first_ord_impl(); }

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun     { typedef func_details::first_impl         first; }
namespace key_fun { typedef key_fun <key::first, fun::first> first; }

//-----------------------------------------------------------------------------

static  __attribute__ ((unused)) key_fun::first first;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_FIRST
