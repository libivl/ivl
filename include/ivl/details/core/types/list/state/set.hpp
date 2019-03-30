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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STATE_SET_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STATE_SET_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename I = term, typename J = term>
struct from : from <typename if_term <I, J, I>::type> { };

template <typename I>
struct from <I, term> { typedef I first; };

struct empty : id <empty>, from <>
{
	template <typename Q>
	struct member : _false { };
};

template <typename I, typename X>
struct add : id <add <I, X> >, from <typename X::first, I>
{
	template <typename Q>
	struct member :
		t_if <t_eq <I, Q>, _true, typename X::template member <Q> >::type { };
};

template <typename X, typename Y>
struct merge : id <merge <X, Y> >, from <typename X::first, typename Y::first>
{
	template <typename Q>
	struct member : t_if <
		typename X::template member <Q>, _true, typename Y::template member <Q>
	>::type { };
};

template <typename X>
struct merge <X, empty> : X { };

template <typename X>
struct merge <empty, X> : X { };

template <>
struct merge <empty, empty> : empty { };

template <typename I>
struct single : add <I, empty> { };

template <typename Q, typename X>
struct in : X::template member <Q> { };

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STATE_SET_HPP
