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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_EVAL_FUN_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_EVAL_FUN_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

// defined in pattern
template <typename I, typename V, typename S>
struct args;

template <typename L, typename I, typename V, typename S>
struct pattern;

//-----------------------------------------------------------------------------

template <typename F>
struct call
{
	template <typename S>
	struct attach : join <layer <typename F::env>, S> { };

	template <typename R, typename S>
	struct ret : type_of <R>, join <S, R> { };

	template <typename V, typename S>
	struct apply : F::template map <V, S> { };

	template <typename V, typename S>
	struct map : ret <apply <V, typename attach <S>::state>, S> { };
};

//-----------------------------------------------------------------------------
// lambda form: construct a closure object that contains the lambda node and
// a snapshot of the current environment of evaluation. a closure is a function
// object that, when applied to a list of values, just evaluates the body of
// the closure after extending the table with an entry that contains the
// arguments of the closure and the given values. a closure also supports an
// optional name that is used by define. when lazy, just evaluate all arguments
// and body for substitutions. A = arguments, B = body, V = values, N = name,
// K = lambda keyword, D = remaining definition, F = entire lambda node.

namespace ns { namespace lambda {
	template <typename BI, typename S> struct body { };
} }

template <typename A, typename B, typename E>
struct lambda : eid <E>
{
	template <typename X>
	struct nat : nested_nat <lambda <A, B, skip>, X> { };

	template <typename BI, typename S>
	struct body : nat <ns::lambda::body <BI, skip> >, bad <> { };

	template <typename S>
	struct body <null, S> : nat <ns::lambda::body <null, skip> >, bad <> { };

	template <typename BI, typename S>
	struct body <node <BI>, S> : eval <BI, S> { };

	template <typename BI, typename BN, typename S>
	struct body <node <BI, BN>, S> :
		body <BN, typename eval <BI, S>::state> { };

	template <typename V, typename S>
	struct map : body <B, typename args <A, V, S>::state> { };
};

//-----------------------------------------------------------------------------

template <typename F, typename E>
struct closure : nat <closure <F, skip> > { };

template <typename A, typename B, typename E>
struct closure <node <scheme::lambda, node <A, B> >, E> :
	map_op <call <lambda <A, B, E> > > { };

template <typename D, typename S>
struct value <node <scheme::lambda, D>, S> :
	id <closure <node <scheme::lambda, D>, typename S::env> >, idle <S> { };

//-----------------------------------------------------------------------------

namespace ns { namespace matcher {
	template <typename RI, typename V, typename S> struct rule { };
} }

template <typename L, typename R, typename E, int Z = 0>
struct matcher : eid <E>
{
	template <typename X>
	struct nat : nested_nat <matcher <L, R, skip>, X> { };

	template <typename RI, typename V, typename S>
	struct rule : nat <ns::matcher::rule <RI, V, skip> >, bad <> { };

	template <typename T, typename SI, typename RN, typename V, typename S>
	struct test : if_ok <SI, eval_mode <T, SI, Z>, rule <RN, V, S> >::type { };

	template <
		typename N, typename P, typename T, typename RN, typename V, typename S
	>
	struct rule <node <node <node <N, P>, node <T> >, RN>, V, S> :
		test <T, typename pattern <L, P, V, S>::state, RN, V, S> { };

	template <typename V, typename S>
	struct map : rule <R, V, S> { };
};

//-----------------------------------------------------------------------------

template <typename L, typename R, typename E>
struct closure <node <scheme::cases, node <L, R> >, E> :
	map_op <call <matcher <L, R, E> > > { };

template <typename D, typename S>
struct value <node <scheme::cases, D>, S> :
	id <closure <node <scheme::cases, D>, typename S::env> >, idle <S> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_ttt     <lambda>                ::name[] = "lambda";
template <> char template_tt      <ns::lambda::body>      ::name[] = "body";
template <> char template_tt      <closure>               ::name[] = "closure";
template <> char template_ttti    <matcher>               ::name[] = "matcher";
template <> char template_ttt     <ns::matcher::rule>     ::name[] = "rule";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_EVAL_FUN_HPP
