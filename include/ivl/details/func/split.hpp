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

#ifndef IVL_FUNC_SPLIT
#define IVL_FUNC_SPLIT

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

struct split : public ivl_func <split>
{

//-----------------------------------------------------------------------------

	/**
	 * \brief Split an array into two arrays as specified by a mask
	 *
	 * @param a array to split
	 * @param m mask (boolean array) specifying the split
	 *
	 * @return (_, l, r) where
	 * @param l (left) is a[m]
	 * @param r (right) is a[!m]
	 */
	template <
		typename T1, typename S1, typename T2, typename S2,
		typename T3, typename S3, typename S4
	>
	void operate(array <T1, S1>& l, array <T2, S2>& r, sep,
					 const array <T3, S3>& a, const array <bool, S4>& m)
	{
		l = a[m];
		r = a[!m];
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Return offsets of an array split as specified by a mask
	 *
	 * @param m mask (boolean array) specifying the array split
	 *
	 * @return (_, l, r) where
	 * @param l (left offsets) is find(m)
	 * @param r (right offsets) is find(!m)
	 */
	template <typename T1, typename S1, typename T2, typename S2, typename S3>
	void operate(array <T1, S1>& l, array <T2, S2>& r, sep,
					 const array <bool, S3>& m)
	{
		l = ivl::find(m);
		r = ivl::find(!m);
	}

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun { typedef func_details::split split; }

static  __attribute__ ((unused)) fun::split split;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUNC_SPLIT
