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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_INTRO_STREAM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_INTRO_STREAM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {
namespace intro {

using ivl::operator<<;

//-----------------------------------------------------------------------------

template <bool NL = false> struct delim { };
template <bool NL = false> struct member { };
template <bool NL = false> struct langle { };
template <bool NL = false> struct rangle { };

template <typename O>
O& operator<< (O& o, delim <>) { return o << ", "; }

template <typename O>
O& operator<< (O& o, member <>) { return o << "::"; }

template <typename O>
O& operator<< (O& o, langle <>) { return o << " <"; }

template <typename O>
O& operator<< (O& o, rangle <>) { return o << ">"; }

template <typename O>
O& operator<< (O& o, delim <true>) { return o << "," << std::endl; }

template <typename O>
O& operator<< (O& o, member <true>) { return o << std::endl << "::"; }

template <typename O>
O& operator<< (O& o, langle <true>)
{
	return o << " <" << indent++ << std::endl;
}

template <typename O>
O& operator<< (O& o, rangle <true>)
{
	return o << indent-- << std::endl << ">";
}

//-----------------------------------------------------------------------------

template <bool B>  struct boolean { };

template <typename T, bool NL = true>  struct type_name { };
template <typename T, bool NL = true>  struct type_list { };
template <typename T, bool NL = true>  struct type_list_in { };

//-----------------------------------------------------------------------------

template <
	typename T1 = term, typename T2 = term, typename T3 = term,
	typename T4 = term, typename T5 = term, typename T6 = term
>
struct list { };

//-----------------------------------------------------------------------------

template <typename O, typename T>
O& operator<< (O& o, name <T>) { return o << T (); }

//-----------------------------------------------------------------------------

template <typename O, bool NL, typename X>
O& operator<< (O& o, type_name <X, NL>) { return o << name <X> (); }

template <typename O, bool NL, bool B>
O& operator<< (O& o, type_name <boolean <B>, NL>) { return o << B; }

template <typename O, bool NL, int N>
O& operator<< (O& o, type_name <number <N>, NL>) { return o << number <N> (); }

//-----------------------------------------------------------------------------

template <typename O, bool NL, typename T, typename TN>
O& operator<< (O& o, type_name <nested <T, TN>, NL>)
{
	return o << type_name <T, NL> () << member <NL> () << type_name <TN, NL> ();
}

//-----------------------------------------------------------------------------

template <typename O, bool NL, typename T>
O& operator<< (O& o, type_list <T, NL>)
{
	return o << langle <NL> () << type_name <T, NL> () << rangle <NL> ();
}

template <typename O, bool NL, typename T>
O& operator<< (O& o, type_list_in <T, NL>)
{
	return o << langle <> () << type_name <T, NL> () << " " << rangle <> ();
}

//-----------------------------------------------------------------------------

template <typename O, bool NL, typename T>
O& operator<< (O& o, type_name <list <T>, NL>)
{
	return o << type_name <T, NL> ();
}

template <
	typename O, bool NL,
	typename T1, typename T2, typename T3,
	typename T4, typename T5, typename T6
>
O& operator<< (O& o, type_name <list <T1, T2, T3, T4, T5, T6>, NL>)
{
	return o << type_name <T1, NL> () << delim <NL> () <<
		type_name <list <T2, T3, T4, T5, T6>, NL> ();
}

//-----------------------------------------------------------------------------

template <
	typename O, bool NL,
	template <bool> class F,
	bool X
>
O& operator<< (O& o, type_name <F <X>, NL>)
{
	return o << template_b <F>::name << type_list <boolean <X>, NL> ();
}

template <
	typename O, bool NL,
	template <int> class F,
	int X
>
O& operator<< (O& o, type_name <F <X>, NL>)
{
	return o << template_i <F>::name << type_list <number <X>, NL> ();
}

template <
	typename O, bool NL,
	template <typename> class F,
	typename X
>
O& operator<< (O& o, type_name <F <X>, NL>)
{
	return o << template_t <F>::name << type_list <X, NL> ();
}

//-----------------------------------------------------------------------------

template <
	typename O, bool NL,
	template <typename, bool> class F,
	typename X1, bool X2
>
O& operator<< (O& o, type_name <F <X1, X2>, NL>)
{
	return o << template_tb <F>::name <<
		type_list <list <X1, boolean <X2> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, int> class F,
	typename X1, int X2
>
O& operator<< (O& o, type_name <F <X1, X2>, NL>)
{
	return o << template_ti <F>::name <<
		type_list <list <X1, number <X2> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, typename> class F,
	typename X1, typename X2
>
O& operator<< (O& o, type_name <F <X1, X2>, NL>)
{
	return o << template_tt <F>::name <<
		type_list <list <X1, X2>, NL> ();
}

//-----------------------------------------------------------------------------

template <
	typename O, bool NL,
	template <typename, typename, bool> class F,
	typename X1, typename X2, bool X3
>
O& operator<< (O& o, type_name <F <X1, X2, X3>, NL>)
{
	return o << template_ttb <F>::name <<
		type_list <list <X1, X2, boolean <X3> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, typename, int> class F,
	typename X1, typename X2, int X3
>
O& operator<< (O& o, type_name <F <X1, X2, X3>, NL>)
{
	return o << template_tti <F>::name <<
		type_list <list <X1, X2, number <X3> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, typename, typename> class F,
	typename X1, typename X2, typename X3
>
O& operator<< (O& o, type_name <F <X1, X2, X3>, NL>)
{
	return o << template_ttt <F>::name <<
		type_list <list <X1, X2, X3>, NL> ();
}

//-----------------------------------------------------------------------------

template <
	typename O, bool NL,
	template <typename, typename, typename, bool> class F,
	typename X1, typename X2, typename X3, bool X4
>
O& operator<< (O& o, type_name <F <X1, X2, X3, X4>, NL>)
{
	return o << template_tttb <F>::name <<
		type_list <list <X1, X2, X3, boolean <X4> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, typename, typename, int> class F,
	typename X1, typename X2, typename X3, int X4
>
O& operator<< (O& o, type_name <F <X1, X2, X3, X4>, NL>)
{
	return o << template_ttti <F>::name <<
		type_list <list <X1, X2, X3, number <X4> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, typename, typename, typename> class F,
	typename X1, typename X2, typename X3, typename X4
>
O& operator<< (O& o, type_name <F <X1, X2, X3, X4>, NL>)
{
	return o << template_tttt <F>::name <<
		type_list <list <X1, X2, X3, X4>, NL> ();
}

//-----------------------------------------------------------------------------

template <
	typename O, bool NL,
	template <typename, typename, typename, typename, bool> class F,
	typename X1, typename X2, typename X3, typename X4, bool X5
>
O& operator<< (O& o, type_name <F <X1, X2, X3, X4, X5>, NL>)
{
	return o << template_ttttb <F>::name <<
		type_list <list <X1, X2, X3, X4, boolean <X5> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, typename, typename, typename, int> class F,
	typename X1, typename X2, typename X3, typename X4, int X5
>
O& operator<< (O& o, type_name <F <X1, X2, X3, X4, X5>, NL>)
{
	return o << template_tttti <F>::name <<
		type_list <list <X1, X2, X3, X4, number <X5> >, NL> ();
}

template <
	typename O, bool NL,
	template <typename, typename, typename, typename, typename> class F,
	typename X1, typename X2, typename X3, typename X4, typename X5
>
O& operator<< (O& o, type_name <F <X1, X2, X3, X4, X5>, NL>)
{
	return o << template_ttttt <F>::name <<
		type_list <list <X1, X2, X3, X4, X5>, NL> ();
}

//-----------------------------------------------------------------------------

template <
	typename O, bool NL,
	template <template <typename> class> class F,
	template <typename> class X
>
O& operator<< (O& o, type_name <F <X>, NL>)
{
	return o << template_1t_ <F>::name << langle <NL> () <<
		template_t <X>::name << rangle <NL> ();
}

template <
	typename O, bool NL,
	template <template <typename, typename> class> class F,
	template <typename, typename> class X
>
O& operator<< (O& o, type_name <F <X>, NL>)
{
	return o << template_2tt_ <F>::name << langle <NL> () <<
		template_tt <X>::name << rangle <NL> ();
}

//-----------------------------------------------------------------------------

}  // namespace intro
}  // namespace list_details

using list_details::intro::operator<<;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_INTRO_STREAM_HPP
