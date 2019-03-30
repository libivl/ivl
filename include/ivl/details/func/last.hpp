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

#ifndef IVL_FUNC_LAST
#define IVL_FUNC_LAST

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

struct last_ord_impl : public func_details::find_base <last_ord_impl>
{
	using func_details::find_base <last_ord_impl>::operate;

	/**
	 * \brief Find the last non-zero element of an ordered array
	 *
	 * @param a array to search in
	 * @param s offset up to which to search
	 *
	 * @return offset of the last non-zero element, \e -1 if none found
	 */
	template <class P, class T, class S>
	void operate(P& pos, sep,
					 const array <T, S>& a, size_t s = npos)
	{
		size_t &from = pos = npos, to = (s == npos) ? a.length() -1 : s, mid;
		while (from != to) {
			mid = (from + to + 1) / 2;
			if (a[mid]) from = mid;
			else to = mid - 1;
		}
	}

	template <class T, class S>
	size_t operator()(const array<T, S>& a, size_t s = npos)
	{
		return call <size_t> (this)(a, s);
	}

};

//-----------------------------------------------------------------------------

struct last_k_impl : public func_details::find_base<last_k_impl>
{
	using func_details::find_base <last_k_impl>::operate;

	// maximum number of elements to return
	size_t k;

	last_k_impl(const size_t k) : k(k) { }

	/**
	 * \brief Find the k last non-zero elements of an array
	 *
	 * @param a array to search in
	 * @param s offset up to which to search
	 *
	 * @return array containing offsets of k last non-zero elements found
	 */
	template <class T1, class S1, class T2, class S2>
	void operate(array <T1, S1>& pos, sep,
					 const array <T2, S2>& a, const size_t s = npos)
	{
		pos = flip( (s == npos) ?
		      collect[sz][off][rev][max=k]          (op) (a) :
		      collect[sz][off][rev][max=k][begin=s] (op) (a) );
	}

	template <class T, class S>
	size_array operator()(const array <T, S>& a, size_t s = npos)
	{
		return call <size_array>(this)(a, s);
	}

};

//-----------------------------------------------------------------------------

struct last_impl : public func_details::find_base<last_impl>
{
	using func_details::find_base <last_impl>::operate;

	/**
	 * \brief Find the last non-zero element of an array
	 *
	 * @param a array to search in
	 * @param s offset up to which to search
	 *
	 * @return offset of the last non-zero element, \e -1 if none found
	 */
	template <class P, class T, class S>
	void operate(P& pos, sep, const array <T, S>& a, const size_t s = npos)
	{
		pos = (s == npos) ?
		      reduce[sz][off][rev][cond]          (op_cond) (a, npos) :
		      reduce[sz][off][rev][cond][begin=s] (op_cond) (a, npos) ;
	}

	template <class T, class S>
	size_t operator()(const array<T, S>& a, size_t s = npos)
	{
		return call <size_t> (this)(a, s);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Find last k non-zero elements
	 */
	last_k_impl operator[](const size_t k) { return last_k_impl(k); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Binary search in ordered array
	 */
	last_ord_impl operator[](key::ord) { return last_ord_impl(); }

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun     { typedef func_details::last_impl        last; }
namespace key_fun { typedef key_fun <key::last, fun::last> last; }

//-----------------------------------------------------------------------------

static  __attribute__ ((unused)) key_fun::last last;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif // IVL_FUNC_LAST
