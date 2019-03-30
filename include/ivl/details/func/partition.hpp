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

#ifndef IVL_FUNC_PARTITION
#define IVL_FUNC_PARTITION

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

template <template <bool> class DER, bool OFF>
struct partition_base : public ivl_func <DER <OFF> >
{
	typedef ivl_func <DER <OFF> > base;

//-----------------------------------------------------------------------------

	/**
	 * \brief Define partition by interval lengths
	 */
	DER <false>
	operator[](key::len) { return DER <false> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Define partition by interval begin offsets
	 */
	DER <true>
	operator[](key::off) { return DER <true> (); }

//-----------------------------------------------------------------------------

	template <typename T1, typename S1, typename S2>
	array <typename array <T1, S1>::create_similar>
	operator()(const array <T1, S1>& a, const array <size_t, S2>& begin)
	{
		return typename base::template
			call <array <typename array <T1, S1>::create_similar> > (a, begin);
	}

};

//-----------------------------------------------------------------------------

template <bool OFF = true>
struct partition_impl;

template <>
struct partition_impl <false> : public partition_base <partition_impl, false>
{

	/**
	 * \brief Partition an array into arrays of specified lengths
	 *
	 * @param a input array
	 * @param len array containing interval lengths
	 *
	 * @return (_, p) where
	 * @param p array containing arrays p[i] such that p[i].length() = len[i]
	 * and a = [p[0] ... p[n]] where n = len.length()
	 */
	template <
		typename T1, typename S11, typename S12,
		typename T2, typename S2, typename S3
	>
	void operate(array <array <T1, S11>, S12>& p, sep,
					 const array <T2, S2>& a, const array <size_t, S3>& len)
	{
		// TODO: make it a view
		typedef typename array <array <T1, S11>, S12>::iterator P;
		typedef typename array <size_t, S3>::const_iterator S;

		if (len.empty()) { p.init(); return; }
		p.init(len.length());
		S l = len.begin();
		size_t q = 0, r = q;
		for (P i = p.begin(), e = p.end(); i != e; q = r, l++)
			*i++ = a[q, _, (r += *l) - 1];
	}

};

//-----------------------------------------------------------------------------

template <>
struct partition_impl <true> : public partition_base <partition_impl, true>
{

	/**
	 * \brief Partition an array into arrays beginning at specified offsets
	 *
	 * @param a input array
	 * @param begin non-decreasing array containing beginning offsets
	 *
	 * @return (_, p) where
	 * @param p array containing arrays p[i] such that p[i][0] refers to
	 * a[begin[i]] and a = [p[0] ... p[n]] where n = begin.length()
	 */
	template <
		typename T1, typename S11, typename S12,
		typename T2, typename S2, typename S3
	>
	void operate(array <array <T1, S11>, S12>& p, sep,
					 const array <T2, S2>& a, const array <size_t, S3>& begin)
	{
		// TODO: make it a view
		typedef typename array <array <T1, S11>, S12>::iterator P;
		typedef typename array <size_t, S3>::const_iterator S;

		if (begin.empty()) { p.init(); return; }
		p.init(begin.length());
		S b = begin.begin();
		size_t q = *b, r = q;
		for (P i = p.begin(), e = p.end(); i != e; q = r)
		{
			r = ++b == begin.end() ? a.length() : *b;
			*i++ = a[q, _, r - 1];
		}
	}

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun { typedef func_details::partition_impl <> partition; }

static  __attribute__ ((unused)) fun::partition partition;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUNC_PARTITION
