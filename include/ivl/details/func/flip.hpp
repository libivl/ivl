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

#ifndef IVL_FUNC_FLIP
#define IVL_FUNC_FLIP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

using keys::key_val;

//-----------------------------------------------------------------------------

template <typename SWAP = fun::swap>
struct flip_in_impl : public ivl_func <flip_in_impl <SWAP> >
{

//-----------------------------------------------------------------------------

	/**
	 * \brief Flip elements of an array in-place
	 *
	 * @param a array to flip
	 */
	template <class T, class S>
	array<T, S>& operator()(array<T, S>& a)
	{
		size_t len = a.length();
		if(len < 2) return a;
		typename array <T, S>::iterator f = a.begin(), r = f + a.length();
		r--;  // TODO: should be just r = f + a.length() - 1;
		SWAP swap;

		if (len % 2) do swap(*f, *r); while (++f != --r);
		else         do swap(*f, *r); while (f++ != --r);

		return a;
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Use specified swap operator
	 */
	template <typename S>
	flip_in_impl <S>
	operator[](key_val <key::swp, S>) { return flip_in_impl <S> (); }
};

//-----------------------------------------------------------------------------

class flip_impl : public ivl_func <flip_impl>
{
	typedef ivl_func <flip_impl> base;

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Flip elements of an array, return flipped array
	 *
	 * @param a array to flip
	 *
	 * @return flipped array
	 */
	template <class T1, class S1, class T2, class S2>
	void operate(array <T1, S1>& f, sep, const array<T2, S2>& a)
	{
		// TODO: make it a view
		f.init(a.derived().size());

		typename array <T1, S1>::reverse_iterator i1 = f.rbegin();
		typename array <T2, S2>::const_iterator i2 = a.begin(), e = a.end();

		for(; i2 != e; i1++, i2++)
			*i1 = *i2;
	}

	template <class T, class S>
	typename array<T, S>::create_similar
	operator()(const array<T, S>& a)
	{
		return typename base::template
			call <typename array<T, S>::create_similar> (this) (a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Use in-place operation
	 */
	flip_in_impl <> operator[](key::in) { return flip_in_impl <> (); }
};

//-----------------------------------------------------------------------------

};  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun {

typedef func_details::flip_impl       flip;
typedef func_details::flip_in_impl <> flip_in;

}

namespace key_fun { typedef key_fun <key::flip, fun::flip> flip; }

//-----------------------------------------------------------------------------

static  __attribute__ ((unused)) key_fun::flip flip;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_FLIP
