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

#ifndef IVL_FUNC_JOIN
#define IVL_FUNC_JOIN

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

struct join : public ivl_func <join>
{

//-----------------------------------------------------------------------------

	/**
	 * \brief Join (concatenate) an array of arrays into a flat array
	 *
	 * @param a input array of arrays
	 *
	 * @return (_, f) where
	 * @param f is concatenated array [a[0] ... a[n]] where n = a.length()
	 */
	template <typename T1, typename S1, typename T2, typename S21, typename S22>
	void operate(array <T1, S1>& f, sep,
					 const array <array <T2, S21>, S22>& a)
	{
		// TODO: make it a view
		typedef array <T2, S21> A;
		typedef typename array <T1, S1>::iterator F;
		typedef typename array <A, S22>::const_iterator P;

		if(a.empty()) { f.init(); return; }

			// TODO: this should be size_t len = sum(a[&A::length]());
			size_t len = 0;
			for (P i = a.begin(), e = a.end(); i != e; i++)
				len += i->length();

		f.init(len);
		F p = f.begin();
		for (P i = a.begin(), e = a.end(); i != e; i++)
			p = std::copy(i->begin(), i->end(), p);
	}

	template <typename T1, typename S11, typename S12>
	typename array <T1, S11>::create_similar
	operator()(const array <array <T1, S11>, S12>& a)
	{
		return call <typename array <T1, S11>::create_similar> (a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Join (concatenate) two arrays into a flat array
	 *
	 * @param a first input array
	 * @param b second input array
	 *
	 * @return (_, f) where
	 * @param f is concatenated array [a b]
	 */
	template <
		typename T1, typename S1, typename T2, typename S2,
		typename T3, typename S3
	>
	void operate(array <T1, S1>& f, sep,
					 const array <T2, S2>& a, const array <T3, S3>& b)
	{
		// TODO: make it a view
		typedef typename array <T1, S1>::iterator F;

		size_t len = a.length() + b.length();
		f.init(len);
		F p = std::copy(a.begin(), a.end(), f.begin());
		std::copy(b.begin(), b.end(), p);
	}

	template <typename T1, typename S1, typename T2, typename S2>
	typename array <typename types::maps::max <T1, T2>::type, S1>::create_new
	operator()(const array <T1, S1>& a, const array <T2, S2>& b)
	{
		typedef typename types::maps::max <T1, T2>::type T;
		return call <typename array <T, S1>::create_new> (a, b);
	}

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun { typedef func_details::join join; }

static  __attribute__ ((unused)) fun::join join;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_FUNC_JOIN
