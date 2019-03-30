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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STATE_ENV_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STATE_ENV_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

using scheme::none;

//-----------------------------------------------------------------------------

template <typename E>
struct eid { typedef E env; };

template <typename T>
struct env_of : eid <typename T::env> { };

//-----------------------------------------------------------------------------

template <typename S>
struct sid { typedef S state; };

template <typename S>
struct idle : env_of <S>, mem_of <S>, sid <S> { };

template <typename T, typename S>
struct give : id <T>, idle <S> { };

template <typename E, typename M = clear>
struct at : eid <E>, mid <M>, sid <at <E, M> > { };

template <typename E, typename M>
struct to : E, M, sid <at <E, M> > { };

template <typename E, typename M>
struct join : at <typename E::env, typename M::mem> { };

template <typename T>
struct state_of : idle <typename T::state> { };

//-----------------------------------------------------------------------------

// defined below
template <typename I, typename V, int P>
struct extend;

template <typename I, typename E, typename M>
struct insert_pos : to <extend <I, E, M::size>, M> { };

template <typename I, typename V, typename E, typename M>
struct insert : insert_pos <I, E, grow <V, M> > { };

//-----------------------------------------------------------------------------

template <typename T>
struct ident { typedef T identifier; };

//-----------------------------------------------------------------------------

template <typename I, typename E, int P>
struct extend : eid <extend <I, E, P> >, above <E>, ident <I>
{
	typedef extend <I, E, P> T;

	template <typename Q, typename M>
	struct lookup : t_if <t_eq <I, Q>,
		typename M::template read <P>,
		typename E::template lookup <Q, M>
	>::type { };

	template <typename Q, typename M>
	struct bound : t_if <t_eq <I, Q>,
		typename M::template read <P>,
		typename E::template bound <Q, M>
	>::type { };

	template <typename K, typename V, typename M>
	struct assign : t_if <t_eq <I, K>,
		typename M::template write <P, V>,
		typename E::template assign <K, V, M>
	>::type { };

	template <typename K, typename V, typename M>
	struct let : insert <K, V, T, M> { };

	template <typename K, typename V, typename M>
	struct set : to <T, typename assign <K, V, M>::mem> { };
};

//-----------------------------------------------------------------------------

template <typename E>
struct layer : eid <layer <E> >, above <E>, ident <term>
{
	template <typename Q, typename M>
	struct lookup: E::template lookup <Q, M> { };

	template <typename Q, typename M>
	struct bound : none { };

	template <typename I, typename V, typename M>
	struct assign : E::template assign <I, V, M> { };

	template <typename I, typename V, typename M>
	struct let : insert <I, V, layer <E>, M> { };

	template <typename I, typename V, typename M>
	struct set : E::template set <I, V, M> { };
};

//-----------------------------------------------------------------------------

namespace ns {

namespace fail  { template <typename Q, typename M> struct lookup { }; }
namespace blank { template <typename I, typename V> struct set { }; }
namespace blank { template <typename I, typename V> struct assign { }; }

}

//-----------------------------------------------------------------------------

template <typename X = term>
struct fail : eid <fail <X> >, above <fail <X> >, ident <term>
{
	template <typename Y>
	struct nat : nested_nat <fail <X>, Y> { };

	template <typename Q, typename M>
	struct lookup : nat <ns::fail::lookup <Q, M> > { };

	template <typename Q, typename M>
	struct bound : lookup <Q, M> { };

	template <typename I, typename V, typename M>
	struct let : to <fail <X>, deny <> > { };

	template <typename I, typename V, typename M>
	struct set : to <fail <X>, deny <> > { };
};

template <typename O, typename I>
struct nested_fail : fail <intro::nested <O, I> > { };

//-----------------------------------------------------------------------------

struct blank : eid <blank>, above <blank>, ident <term>
{
	template <typename X>
	struct fail : nested_fail <blank, X> { };

	template <typename Q, typename M>
	struct lookup : none { };

	template <typename Q, typename M>
	struct bound : none { };

	template <typename I, typename V, typename M>
	struct let : insert <I, V, blank, M> { };

	template <typename I, typename V, typename M>
	struct set : to <fail <ns::blank::set <I, skip> >, deny <> > { };

	template <typename I, typename V, typename M>
	struct assign : to <fail <ns::blank::assign <I, skip> >, deny <> > { };
};

//-----------------------------------------------------------------------------

template <typename X = term, typename Y = term>
struct bad : at <fail <X>, deny <Y> > { };

struct init : at <blank, clear> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_tt      <at>                    ::name[] = "at";
template <> char template_t       <fail>                  ::name[] = "fail";
template <> char template_tt      <ns::fail::lookup>      ::name[] = "lookup";
template <> char template_tt      <ns::blank::set>        ::name[] = "set";
template <> char template_tt      <ns::blank::assign>     ::name[] = "assign";
template <> char template_tti     <extend>                ::name[] = "extend";
template <> char template_t       <layer>                 ::name[] = "layer";

template <typename O> O& operator<< (O& o, name <blank>)      { return o << "blank"; }

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STATE_ENV_HPP
