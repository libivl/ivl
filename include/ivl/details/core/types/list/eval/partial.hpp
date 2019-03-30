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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_EVAL_PARTIAL_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_EVAL_PARTIAL_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename T, typename S, int Z>
struct eval_cond : t_if <t_expr <Z == 0>, eval <T, S>, give <T, S> > { };

template <typename V, typename VN, typename S>
struct eval_node : eval <typename node <V, VN>::type, S> { };

//-----------------------------------------------------------------------------

template <typename V, typename VN>
struct re_eval : eval_node <typename V::type, VN, typename V::state> { };

template <typename V>
struct re_eval <V, null> : V { };

template <typename F, typename V, typename VN, typename S>
struct apply_next_2 : re_eval <apply_op_map <F, V, S>, VN> { };

template <typename F, typename X, typename VN, typename S>
struct apply_next_2 <F, nat <X>, VN, S> : nat <X>, bad <> { };

template <typename F, typename V, typename VN>
struct apply_next_1 :
	apply_next_2 <F, typename V::type, VN, typename V::state> { };

template <typename O, typename F, typename V, typename S, int Z>
struct apply_next : nat <apply_next <O, skip, V, skip, Z> >, bad <> { };

template <typename O, typename F, typename S, int Z>
struct apply_next <O, F, null, S, Z> : give <O, S> { };

template <typename O, typename F, typename V, typename VN, typename S, int Z>
struct apply_next <O, F, node <V, VN>, S, Z> :
	apply_next_1 <F, typename eval_cond <V, S, Z>::type, VN> { };

//-----------------------------------------------------------------------------

template <typename F, typename V, typename S>
struct apply_init_2 : eval_list <node <F, V>, S> { };

template <typename F, typename S>
struct apply_init_2 <F, null, S> : give <F, S> { };

template <typename O, typename F, typename V, typename S, int Z>
struct apply_init_1 : apply_init_2 <F, V, S> { };

template <typename O, typename F, typename V, typename S, int Z>
struct apply_init_1 <O, op <pt <F>, Z>, V, S, Z> :
	apply_next <O, F, V, S, Z> { };

template <typename O, typename F, typename V, int Z>
struct apply_init :
	apply_init_1 <O, typename F::type, V, typename F::state, Z> { };

template <typename O, typename F, typename V, typename S>
struct apply_fun <O, op <pt <F>, 0>, V, S> :
	apply_init <O, apply_op_map <F, term, S>, V, 0> { };

template <typename O, typename F, typename V, typename S>
struct apply_fun <O, op <pt <F>, 1>, V, S> :
	apply_init <O, apply_op_map <F, term, S>, V, 1> { };

//-----------------------------------------------------------------------------

template <typename F, typename V, typename S>
struct apply_partial : nat <apply_partial <F, V, skip> >, bad <> { };

template <typename F, typename V, typename S>
struct apply_partial <op <F, 0>, V, S> : apply_op_map <F, V, S> { };

template <typename F, typename V, typename S>
struct apply_partial <op <F, 1>, V, S> :
	eval <typename apply_op_map <F, V, S>::type, S> { };

//-----------------------------------------------------------------------------

template <typename C, typename A, typename G, int Z>
struct partial;

template <typename C, typename A, typename G, int Z>
struct part : id <part <C, A, G, Z> >, pt_map_op <partial <C, A, G, Z>, Z> { };

//-----------------------------------------------------------------------------

namespace ns { namespace partial {
	template <typename AI, typename V, typename S> struct input { };
	template <typename AI, typename V, typename S> struct init { };
} }

template <typename C, typename A, typename G, int Z>
struct partial
{
	template <typename X>
	struct nat : nested_nat <partial <C, skip, G, Z>, X> { };

	template <typename V>
	struct add : append <G, node <V> > { };

	template <typename GI, typename S>
	struct apply : apply_partial <typename C::derived_type, GI, S> { };

	template <typename AI, typename V, typename S>
	struct input : nat <ns::partial::input <AI, skip, skip> >, bad <> { };

	template <typename AI, typename V, typename S>
	struct input <node <AI>, V, S> : apply <typename add <V>::type, S> { };

	template <typename AI, typename AN, typename V, typename S>
	struct input <node <AI, AN>, V, S> : idle <S>,
		part <C, AN, typename add <V>::type, Z> { };

	template <typename AI, typename V, typename S>
	struct init : input <AI, V, S> { };

	template <typename AI, typename S>
	struct init <AI, term, S> :
		nat <ns::partial::init <AI, skip, skip> >, bad <> { };

	template <typename S>
	struct init <null, term, S> : apply <G, S> { };

	template <typename V, typename S>
	struct map : init <A, V, S> { };

	template <typename AI, typename AN, typename S>
	struct init <node <AI, AN>, term, S> :
		id <op <pt <types::t2 <map> >, Z> >, idle <S> { };
};

//-----------------------------------------------------------------------------

template <typename A, int Z = 0>
struct sign : id <sign <A, Z> > { };

template <typename F, int Z = 0>
struct get_pattern : nat <get_pattern <F, Z> > { };

template <typename L, typename N, typename P, typename T, typename RN, int Z>
struct get_pattern <node <L, node <node <node <N, P>, node <T> >, RN> >, Z> :
	sign <P, Z> { };

template <typename F>
struct get_sign : nat <get_sign <F> > { };

template <typename A, typename B>
struct get_sign <node <scheme::lambda, node <A, B> > > : sign <A> { };

template <typename D>
struct get_sign <node <scheme::cases, D> > : get_pattern <D> { };

template <typename D>
struct get_sign <node <scheme::rules, D> > : get_pattern <D, 1> { };

//-----------------------------------------------------------------------------

template <typename C, typename A, typename S>
struct part_sign : nat <part_sign <C, A, S> >, bad <> { };

template <typename C, typename P, int Z, typename S>
struct part_sign <C, sign <P, Z>, S> : part <C, P, null, Z>, idle <S> { };

template <typename T, typename S>
struct part_fun : nat <part_fun <T, skip> >, bad <> { };

template <typename F, typename E, typename S>
struct part_fun <closure <F, E>, S> :
	part_sign <closure <F, E>, typename get_sign <F>::type, S> { };

template <typename D, typename S>
struct depart : nat <depart <D, skip> >, bad <> { };

template <typename T, typename S>
struct depart <node <T>, S> : part_fun <typename eval <T, S>::type, S> { };

template <typename D, typename S>
struct value <node <scheme::partial, D>, S> : depart <D, S> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_tttti   <apply_next>            ::name[] = "apply_next";
template <> char template_ttt     <apply_partial>         ::name[] = "apply_partial";
template <> char template_ttti    <part>                  ::name[] = "part";
template <> char template_ttt     <ns::partial::input>    ::name[] = "input";
template <> char template_ttt     <ns::partial::init>     ::name[] = "init";
template <> char template_ti      <get_pattern>           ::name[] = "get_pattern";
template <> char template_t       <get_sign>              ::name[] = "get_sign";
template <> char template_ttt     <part_sign>             ::name[] = "part_sign";
template <> char template_tt      <part_fun>              ::name[] = "part_fun";
template <> char template_tt      <depart>                ::name[] = "depart";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_EVAL_PARTIAL_HPP
