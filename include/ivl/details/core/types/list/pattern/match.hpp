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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SYNTAX_MATCH_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SYNTAX_MATCH_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

typedef node <scheme::etc> dots;

//-----------------------------------------------------------------------------

template <typename T>
struct cars : nat <cars <T> > { };

template <>
struct cars <null> : null { };

template <typename TR>
struct cars <node <null, TR> > : nat <cars <node <null, TR> > > { };

template <typename T, typename TN, typename TR>
struct cars <node <node <T, TN>, TR> > :
	node <T, typename cars <TR>::type> { };

//-----------------------------------------------------------------------------

template <typename T>
struct cdrs : nat <cdrs <T> > { };

template <>
struct cdrs <null> : null { };

template <typename TR>
struct cdrs <node <null, TR> > : nat <cdrs <node <null, TR> > > { };

template <typename T, typename TN, typename TR>
struct cdrs <node <node <T, TN>, TR> > :
	node <TN, typename cdrs <TR>::type> { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename S>
struct bind_ident : let <I, V, S> { };

template <typename T, typename TN, typename V, typename S>
struct bind_ident <node <T, TN>, V, S> :
	bad <bind_ident <node <T, TN>, V, skip> > { };

template <typename I, typename V, typename S>
struct bind : if_ok <S, bind_ident <I, V, S>, S>::type { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename S>
struct args : bad <args <I, V, skip> > { };

template <typename S>
struct args <null, null, S> : let <null, null, S> { };

template <typename I, typename IN, typename V, typename VN, typename S>
struct args <node <I, IN>, node <V, VN>, S> :
	args <IN, VN, typename bind <I, V, S>::state> { };

//-----------------------------------------------------------------------------

using scheme::var;

template <typename T, typename THEN, typename ELSE>
struct if_ident :
	t_if <is_base <scheme::identifier_id, T>, THEN, ELSE> { };

template <typename T, typename THEN, typename ELSE>
struct if_ident <var <T>, THEN, ELSE> : if_ident <T, THEN, ELSE> { };

//-----------------------------------------------------------------------------

template <typename U, typename V, typename S>
struct unify_eq :
	t_if <t_eq <U, V>, S, bad <unify_eq <U, V, skip> > >::type { };

template <typename I, typename U, typename V, typename S>
struct unify_val :
	if_none <U, let <I, V, S>, unify_eq <U, V, S> >::type { };

template <typename I, typename V, typename S>
struct unify_ident : unify_val <I, typename bound <I, S>::type, V, S> { };

template <typename L, typename I, typename V, typename S>
struct unify_literal : t_if <
	member <I, L>, unify_eq <I, V, S>, unify_ident <I, V, S>
>::type { };

template <typename L, typename I, typename V, typename S>
struct unify_const :
	if_ident <I, unify_literal <L, I, V, S>, unify_eq <I, V, S> >::type { };

template <typename L, typename I, typename V, typename S>
struct unify_const <L, node <I, dots>, V, S> : if_ident <I,
	unify_ident <node <I, dots>, V, S>,
	bad <unify_const <skip, node <I, dots>, V, skip> >
>::type { };

template <typename L, typename I, typename V, typename S>
struct unify_list : t_if <
	t_eq <node <scheme::___, dots>, I>, S, unify_const <L, I, V, S>
>::type { };

template <typename L, typename I, typename V, typename S>
struct unify_expr :
	t_if <t_eq <scheme::___, I>, S, unify_list <L, I, V, S> >::type { };

template <typename L, typename I, typename V, typename S>
struct unify : if_ok <S, unify_expr <L, I, V, S>, S>::type { };

//-----------------------------------------------------------------------------

template <typename L, typename I, typename V, typename S>
struct unify_type : bad <unify_type <skip, I, V, skip> > { };

template <typename L, typename I, int N, typename S>
struct unify_type <L, node <scheme::hash, node <I> >, number <N>, S> :
	unify <L, I, number <N>, S> { };

//-----------------------------------------------------------------------------

template <typename L, typename I, typename V, typename S>
struct match;

template <typename L, typename I, typename V, typename S>
struct pattern : if_ok <S, match <L, I, V, S>, S>::type { };

//-----------------------------------------------------------------------------

template <typename L, typename I, typename V, typename S = init>
struct match : unify <L, I, V, S> { };

template <typename L, typename S>
struct match <L, null, null, S> : let <null, null, S> { };

template <typename L, typename I, typename IN, typename V, typename S>
struct match <L, node <I, IN>, V, S> :
	bad <match <skip, node <I, IN>, V, skip> > { };

template <
	typename L, typename I, typename IN,
	typename V, typename VN, typename S
>
struct match <L, node <I, IN>, node <V, VN>, S> :
	pattern <L, IN, VN, typename pattern <L, I, V, S>::state> { };

//-----------------------------------------------------------------------------

template <typename L, typename I, typename V, typename VN, typename S>
struct match <L, node <I, dots>, node <V, VN>, S> :
	unify <L, node <I, dots>, node <V, VN>, S> { };

//-----------------------------------------------------------------------------

template <typename L, typename VR, typename S>
struct match <L, node <null, dots>, node <null, VR>, S> :
	let <null, null, S> { };

template <typename L, typename I, typename IN, typename S>
struct match <L, node <node <I, IN>, dots>, null, S> : pattern <
	L, node <IN, dots>, null,
	typename pattern <L, node <I, dots>, null, S>::state
> { };

template <
	typename L, typename I, typename IN,
	typename V, typename VN, typename VR, typename S
>
struct match <L, node <node <I, IN>, dots>, node <node <V, VN>, VR>, S> :
	pattern <
		L, node <IN, dots>, node <VN, typename cdrs <VR>::type>,
		typename pattern <
			L, node <I, dots>, node <V, typename cars <VR>::type>, S
		>::state
	> { };

//-----------------------------------------------------------------------------

template <typename L, typename IN, typename V, typename VN, typename S>
struct match <L, node <scheme::dot, node <IN> >, node <V, VN>, S> :
	pattern <L, IN, node <V, VN>, S> { };

//-----------------------------------------------------------------------------

template <typename L, typename V, typename S>
struct match <L, node <scheme::bar, null>, V, S> :
	bad <match <skip, node <scheme::bar, null>, V, skip> > { };

template <typename L, typename I, typename IN, typename V, typename S>
struct match <L, node <scheme::bar, node <I, IN> >, V, S> :
	on_bad <
		pattern <L, I, V, S>,
		pattern <L, node <scheme::bar, IN>, V, S>
	> { };

//-----------------------------------------------------------------------------

template <typename L, typename I, typename IN, typename V, typename S>
struct match <L, node <I, node <scheme::as, node <IN> > >, V, S> :
	pattern <L, IN, V, typename pattern <L, I, V, S>::state> { };

template <
	typename L, typename I, typename IN, typename V, typename VN, typename S
>
struct match <L, node <I, node <scheme::as, node <IN> > >, node <V, VN>, S> :
	pattern <
		L, IN, node <V, VN>, typename pattern <L, I, node <V, VN>, S>::state
	> { };

//-----------------------------------------------------------------------------

template <typename L, typename I, typename V, typename S>
struct match <L, node <scheme::hash, node <I> >, V, S> :
	unify_type <L, node <scheme::hash, node <I> >, V, S> { };

template <typename L, typename I, typename V, typename VN, typename S>
struct match <L, node <scheme::hash, node <I> >, node <V, VN>, S> :
	bad <match <skip, node <scheme::hash, node <I> >, node <V, VN>, skip> > { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_t       <cars>                  ::name[] = "cars";
template <> char template_t       <cdrs>                  ::name[] = "cdrs";
template <> char template_ttt     <bind>                  ::name[] = "bind";
template <> char template_ttt     <args>                  ::name[] = "args";
template <> char template_ttt     <bind_ident>            ::name[] = "bind_ident";
template <> char template_ttt     <unify_eq>              ::name[] = "unify_eq";
template <> char template_tttt    <unify_type>            ::name[] = "unify_type";
template <> char template_tttt    <match>                 ::name[] = "match";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SYNTAX_MATCH_HPP
