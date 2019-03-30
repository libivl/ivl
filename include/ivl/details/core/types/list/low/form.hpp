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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_LOW_FORM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_LOW_FORM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------
// t_if variation which is defined only if condition is boolean (_true, _false)
// and nat otherwise

template <class C, class T, class A>
struct bool_if : nat <bool_if <C, skip, skip> >, bad <> { };

template <class C, class T, class A>
struct bool_if <nat <C>, T, A> : nat <C>, bad <> { };

template <class T, class A>
struct bool_if <_true, T, A> : T { };

template <class T, class A>
struct bool_if <_false, T, A> : A { };

//-----------------------------------------------------------------------------
// cond primitive: conditional evaluation, specified by a list of condition /
// expression pairs. the last condition should always be _else. the first
// expression is evaluated and returned for which the condition evaluates to
// _true; or _else's expression if none found. C = condition, A = alternative,
// N = next pair. when lazy, just evaluate all pairs for substitutions.

template <typename T, typename S>
struct cond : nat <cond <T, skip> >, bad <> { };

template <typename C, typename T, typename A, typename S>
struct cond_2 : bool_if <C, eval <T, S>, cond <A, S> > { };

template <typename C, typename T, typename A>
struct cond_1 : cond_2 <typename C::type, T, A, typename C::state> { };

template <typename C, typename T, typename A, typename S>
struct cond <node <node <C, node <T> >, A>, S> :
	cond_1 <eval <C, S>, T, A> { };

template <typename T, typename S>
struct cond <node <node <scheme::_else, node <T> > >, S> : eval <T, S> { };

template <typename T, typename S>
struct value <node <scheme::cond, T>, S> : cond <T, S> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_ttt     <bool_if>               ::name[] = "bool_if";
template <> char template_tt      <cond>                  ::name[] = "cond";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_LOW_FORM_HPP
