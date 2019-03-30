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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STATE_ACCESS_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STATE_ACCESS_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

struct let_op { };
struct set_op { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename E, typename M, typename O>
struct access : bad <access <I, skip, skip, skip, O> > { };

template <typename I, typename V, typename E, typename M>
struct access <I, V, E, M, let_op> : E::template let <I, V, M> { };

template <typename I, typename V, typename E, typename M>
struct access <I, V, E, M, set_op> : E::template set <I, V, M> { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename E, typename M, typename O>
struct check_null : access <I, V, E, M, O> { };

template <typename E, typename M, typename O>
struct check_null <null, null, E, M, O> : to <E, M> { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename S, typename O>
struct check_term : check_null <I, V, typename S::env, typename S::mem, O> { };

template <typename V, typename S, typename O>
struct check_term <term, V, S, O> :
	bad <check_term <term, V, skip, skip> > { };

template <typename I, typename S, typename O>
struct check_term <I, term, S, O> :
	bad <check_term <I, term, skip, skip> > { };

template <typename S, typename O>
struct check_term <term, term, S, O> :
	bad <check_term <term, term, skip, skip> > { };

//-----------------------------------------------------------------------------

template <typename E, typename M>
struct ok : _true { };

template <typename X, typename M>
struct ok <fail <X>, M> : _false { };

template <typename E, typename X>
struct ok <E, deny <X> > : _false { };

template <typename X, typename Y>
struct ok <fail <X>, deny <Y> > : _false { };

template <typename S, typename THEN, typename ELSE>
struct if_ok : t_if <ok <typename S::env, typename S::mem>, THEN, ELSE> { };

template <typename S, typename T>
struct on_bad : if_ok <S, S, T>::type { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename S, typename O>
struct check : if_ok <S, check_term <I, V, S, O>, S>::type { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename S>
struct let : check <I, V, S, let_op> { };

template <typename I, typename V, typename S>
struct set : check <I, V, S, set_op> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_ttttt   <access>                ::name[] = "access";
template <> char template_tttt    <check_term>            ::name[] = "check_term";

template <typename O> O& operator<< (O& o, name <let_op>)     { return o << "let_op"; }

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STATE_ACCESS_HPP
