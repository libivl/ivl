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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SYNTAX_BUILD_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SYNTAX_BUILD_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename T, typename TN>
struct conses : nat <conses <T, TN> > { };

template <>
struct conses <null, null> : null { };

template <typename T, typename TR>
struct conses <node <T, TR>, null> :
	node <node <T>, typename conses <TR, null>::type> { };

template <typename T, typename TR, typename N, typename NN, typename NR>
struct conses <node <T, TR>, node <node <N, NN>, NR> > :
	node <node <T, node <N, NN> >, typename conses <TR, NR>::type> { };

//-----------------------------------------------------------------------------

template <typename T>
struct conses <node <T, dots>, null> : node <node <T>, dots> { };

template <typename T, typename N, typename NN>
struct conses <node <T, dots>, node <node <N, NN> > > :
	node <node <T, node <N, NN> > > { };

template <typename T, typename N, typename NN, typename NR>
struct conses <node <T, dots>, node <node <N, NN>, NR> > : node <
	node <T, node <N, NN> >,
	typename conses <node <T, dots>, NR>::type
> { };

template <typename N, typename NN>
struct conses <null, node <node <N, NN>, dots> > : null { };

template <typename T, typename TR, typename N, typename NN>
struct conses <node <T, TR>, node <node <N, NN>, dots> > : node <
	node <T, node <N, NN> >,
	typename conses <TR, node <node <N, NN>, dots> >::type
> { };

template <typename T, typename N, typename NN>
struct conses <node <T, dots>, node <node <N, NN>, dots> > :
	node <node <T, node <N, NN> >, dots> { };

//-----------------------------------------------------------------------------

template <typename T, int K>
struct conses <node <var <T, K>, dots>, null> :
	node <node <var <T, K> >, dots> { };

template <typename T, int K, typename N, typename NN>
struct conses <node <var <T, K>, dots>, node <node <N, NN> > > :
	node <node <var <T, K>, node <N, NN> > > { };

template <typename T, int K, typename N, typename NN, typename NR>
struct conses <node <var <T, K>, dots>, node <node <N, NN>, NR> > :
	node <
		node <var <T, K>, node <N, NN> >,
		typename conses <node <var <T, K+1>, dots>, NR>::type
	> { };

template <typename N, int K, typename NN>
struct conses <null, node <node <var <N, K>, NN>, dots> > : null { };

template <typename T, typename TR, typename N, int K, typename NN>
struct conses <node <T, TR>, node <node <var <N, K>, NN>, dots> > :
	node <
		node <T, node <var <N, K>, NN> >,
		typename conses <TR, node <node <var <N, K+1>, NN>, dots> >::type
	> { };

template <typename T, int K, typename N, typename NN>
struct conses <node <var <T, K>, dots>, node <node <N, NN>, dots> > :
	node <node <var <T, K>, node <N, NN> >, dots> { };

template <typename T, typename N, int K, typename NN>
struct conses <node <T, dots>, node <node <var <N, K>, NN>, dots> > :
	node <node <T, node <var <N, K>, NN> >, dots> { };

template <typename T, int J, typename N, int K, typename NN>
struct conses <node <var <T, J>, dots>, node <node <var <N, K>, NN>, dots> > :
	node <node <var <T, J>, node <var <N, K>, NN> >, dots> { };

//-----------------------------------------------------------------------------

template <typename T, typename S>
struct build : nat <build <T, skip> > { };

template <typename T, typename S>
struct build <node <T, dots>, S> : lookup <node <T, dots>, S, 1> { };

template <typename S>
struct build <node <null, dots>, S> : null, idle <S> { };

template <typename T, typename TN, typename S>
struct build <node <node <T, TN>, dots>, S> : idle <S>, conses <
	typename build <node <T, dots>, S>::type,
	typename build <node <TN, dots>, S>::type
> { };

template <typename T, typename S>
struct build <node <node <scheme::dot, node <T> >, dots>, S> :
	build <node <T, dots>, S> { };

//-----------------------------------------------------------------------------

template <typename T, typename S>
struct value <node <T, dots>, S> : build <node <T, dots>, S> { };

template <typename T, typename S>
struct expand <node <T, dots>, S> : build <node <T, dots>, S> { };

//-----------------------------------------------------------------------------

template <typename T, typename S, int Z>
struct eval_list <node <T, dots>, S, Z> : eval_mode <node <T, dots>, S, Z> { };

//-----------------------------------------------------------------------------

template <typename T, typename S>
struct tail : nat <tail <T, skip> >, bad <> { };

template <typename T, typename TN, typename S>
struct tail <node <T, TN>, S> : node <T, TN>, idle <S> { };

template <typename T>
struct tail_env : tail <typename T::type, typename T::state> { };

//-----------------------------------------------------------------------------

template <typename T, typename S, int Z = 0>
struct eval_tail : nat <eval_tail <T, skip, Z> >, bad <> { };

template <typename S, int Z>
struct eval_tail <null, S, Z> : give <scheme::dot, S> { };

template <typename T, typename S, int Z>
struct eval_tail <node <T>, S, Z> : tail_env <eval_mode <T, S, Z> > { };

//-----------------------------------------------------------------------------

template <typename T, typename S>
struct value <node <scheme::dot, T>, S> : eval_tail <T, S> { };

template <typename T, typename S>
struct expand <node <scheme::dot, T>, S> : eval_tail <T, S, 1> { };

//-----------------------------------------------------------------------------

template <typename T, typename S, int Z>
struct eval_list <node <scheme::dot, T>, S, Z> :
	eval_mode <node <scheme::dot, T>, S, Z> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_ti      <scheme::var>           ::name[] = "var";

template <> char template_tt      <conses>                ::name[] = "conses";
template <> char template_tt      <tail>                  ::name[] = "tail";
template <> char template_tti     <eval_tail>             ::name[] = "eval_tail";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SYNTAX_BUILD_HPP
