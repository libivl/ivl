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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_EVAL_LAZY_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_EVAL_LAZY_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename T, typename S = init>
struct expand : identify <T, S, 1> { };

template <typename S>
struct expand <null, S> : null, idle <S> { };

//-----------------------------------------------------------------------------

template <typename T, typename E, typename M>
struct lazy_mem : expand <T, at <E, M> > { };

template <typename T, typename E, typename X>
struct lazy_mem <T, E, deny <X> > :
	nat <lazy_mem <skip, skip, deny <X> > >, bad <> { };

template <typename T, typename E, typename M>
struct lazy_env : lazy_mem <T, E, M> { };

template <typename T, typename X, typename M>
struct lazy_env <T, fail <X>, M> :
	nat <lazy_env <skip, fail <X>, skip> >, bad <> { };

template <typename T, typename S = init>
struct lazy : lazy_env <T, typename S::env, typename S::mem> { };

//-----------------------------------------------------------------------------

template <typename O, typename F, typename V, typename S>
struct apply_fun <O, op <F, 1>, V, S> :
	eval <typename apply_op_map <F, V, S>::type, S> { };

template <typename F, typename V, typename S>
struct expand <node <F, V>, S> : eval_list <node <F, V>, S, 1> { };

//-----------------------------------------------------------------------------

template <typename L, typename R, typename E>
struct closure <node <scheme::rules, node <L, R> >, E> :
	map_op <call <matcher <L, R, E, 1> >, 1> { };

template <typename D, typename S>
struct value <node <scheme::rules, D>, S> : idle <S>,
	id <closure <node <scheme::rules, D>, typename S::env> > { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_tt      <expand>                ::name[] = "expand";
template <> char template_ttt     <lazy_env>              ::name[] = "lazy_env";
template <> char template_ttt     <lazy_mem>              ::name[] = "lazy_mem";
template <> char template_tt      <lazy>                  ::name[] = "lazy";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_EVAL_LAZY_HPP
