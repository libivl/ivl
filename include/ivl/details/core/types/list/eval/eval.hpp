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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_EVAL_EVAL_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_EVAL_EVAL_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename T>
struct is_const : is_op <T> { };

template <typename X>
struct is_const <nat <X> > : _true { };

template <>      struct is_const <_true>       : _true { };
template <>      struct is_const <_false>      : _true { };
template <int N> struct is_const <number <N> > : _true { };

template <typename T, typename THEN, typename ELSE>
struct if_const : t_if <is_const <T>, THEN, ELSE> { };

//-----------------------------------------------------------------------------
// identify booleans, numbers, function objects, or look up identifier
// otherwise

template <typename T, typename S, int Z = 0>
struct identify : if_const <T, give <T, S>, lookup <T, S, Z> >::type { };

//-----------------------------------------------------------------------------

template <typename T, typename S = init>
struct value : identify <T, S> { };

template <typename S>
struct value <null, S> : null, idle <S> { };

//-----------------------------------------------------------------------------

template <typename T, typename E, typename M>
struct eval_mem : value <T, at <E, M> > { };

template <typename T, typename E, typename X>
struct eval_mem <T, E, deny <X> > :
	nat <eval_mem <skip, skip, deny <X> > >, bad <> { };

template <typename T, typename E, typename M>
struct eval_env : eval_mem <T, E, M> { };

template <typename T, typename X, typename M>
struct eval_env <T, fail <X>, M> :
	nat <eval_env <T, fail <X>, skip> >, bad <> { };

template <typename T, typename S = init>
struct eval : eval_env <T, typename S::env, typename S::mem> { };

//-----------------------------------------------------------------------------

// defined in macro
template <typename T, typename S>
struct lazy;

template <typename T, typename S, int Z = 0>
struct eval_mode : eval <T, S> { };

template <typename T, typename S>
struct eval_mode <T, S, 1> : lazy <T, S> { };

//-----------------------------------------------------------------------------

// defined in stream
template <typename T, bool NL = false>
struct block;

template <typename L, typename S = init>
struct embed : eval <typename list_model <typename L::list>::type, S> { };

template <typename T, typename S>
struct use : if_list <T, embed <T, S>, give <typename T::type, S> >::type { };

template <typename R>
struct yield : eval <R> { typedef block <R, false> disp; };

template <typename L>
struct prop : yield <typename list_model <L>::type>
{
	template <typename V>
	struct map : list <L, V> { };
};

//-----------------------------------------------------------------------------
// evaluate all expressions in a list and return a list with the values

template <typename T, typename S, int Z = 0>
struct eval_list : nat <eval_list <T, skip, Z> >, bad <> { };

template <typename S, int Z>
struct eval_list <null, S, Z> : null, idle <S> { };

template <typename T, typename TN>
struct eval_list_2 : node <T, typename TN::type>, state_of <TN> { };

template <typename T, typename TN, int Z>
struct eval_list_1 :
	eval_list_2 <typename T::type, eval_list <TN, typename T::state, Z> > { };

template <typename T, typename TN, typename S, int Z>
struct eval_list <node <T, TN>, S, Z> :
	eval_list_1 <eval_mode <T, S, Z>, TN, Z> { };

//-----------------------------------------------------------------------------

template <typename F, typename V, typename S, bool A>
struct apply_cond : apply_map <F, V, S> { };

template <typename F, typename V, typename S>
struct apply_cond <F, V, S, false> : node <F, V>, idle <S> { };

template <typename F, typename V, typename S, bool A>
struct apply_args_2 : apply_cond <F, V, S, A> { };

template <typename F, typename X, typename S, bool A>
struct apply_args_2 <F, nat <X>, S, A> : nat <X>, bad <> { };

template <typename F, typename V, bool A>
struct apply_args_1 :
	apply_args_2 <F, typename V::type, typename V::state, A> { };

template <typename F, typename V, typename S, bool A = true>
struct apply_args : apply_args_1 <F, eval_list <V, S>, A> { };

//-----------------------------------------------------------------------------

template <typename O, typename F, typename V, typename S>
struct apply_fun : apply_args <F, V, S> { };

template <typename O, typename F, typename V, typename S>
struct apply_fun <O, op <F, 0>, V, S> : apply_args <op <F, 0>, V, S> { };

template <typename F, typename V, typename S>
struct apply_op : apply_fun <F, typename F::derived_type, V, S> { };

template <typename F, typename V, typename S>
struct apply_test :
	if_op <F, apply_op <F, V, S>, apply_args <F, V, S, false> >::type { };

template <typename F, typename V>
struct apply : apply_test <typename F::type, V, typename F::state> { };

template <typename F, typename V, typename S>
struct value <node <F, V>, S> : apply <eval <F, S>, V> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_tt      <value>                 ::name[] = "value";
template <> char template_ttt     <eval_env>              ::name[] = "eval_env";
template <> char template_ttt     <eval_mem>              ::name[] = "eval_mem";
template <> char template_tt      <eval>                  ::name[] = "eval";
template <> char template_tti     <eval_list>             ::name[] = "eval_list";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_EVAL_EVAL_HPP
