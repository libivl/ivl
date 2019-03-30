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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_DATA_MODEL_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_DATA_MODEL_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

// not a type (undefined)
template <typename X = term>
struct nat : id <nat <X> > { };

template <typename O, typename I>
struct nested_nat : nat <intro::nested <O, I> > { };

//-----------------------------------------------------------------------------

// internal list representation: T is first expression, TN points to next node
template <typename, typename>
struct node;

typedef node <term, term> null;

template <typename T = term, typename TN = null>
struct node : id <node <T, TN> > { };

//-----------------------------------------------------------------------------

template <typename T, typename X>
struct node <nat <X>, T> : nat <X> { };

template <typename T, typename X>
struct node <T, nat <X> > : nat <X> { };

template <typename X, typename EN>
struct node <nat <X>, nat <EN> > : nat <X> { };

template <typename T, typename TN, typename X>
struct node <node <T, TN>, nat <X> > : nat <X> { };

template <typename T, typename TN, typename X>
struct node <nat <X>, node <T, TN> > : nat <X> { };

//-----------------------------------------------------------------------------

template <typename T, typename TN, typename R>
struct node <node <T, TN>, R> :
	id <node <typename node <T, TN>::type, R> > { };

template <typename T, typename TN, typename R>
struct node <R, node <T, TN> > :
	id <node <R, typename node <T, TN>::type> > { };

template <typename T, typename TN, typename R, typename RN>
struct node <node <T, TN>, node <R, RN> > :
	id <node <typename node <T, TN>::type, typename node <R, RN>::type> > { };

//-----------------------------------------------------------------------------
// root node of alias or derived classes. A = alias.

template <typename T>
struct root : nat <root <T> > { };

//-----------------------------------------------------------------------------
// root node of list

template <
	typename T1,  typename T2,  typename T3,  typename T4,  typename T5,
	typename T6,  typename T7,  typename T8,  typename T9,  typename T10,
	typename T11, typename T12, typename T13, typename T14, typename T15,
	typename T16, typename T17, typename T18, typename T19, typename T20,
	typename T21, typename T22, typename T23, typename T24
>
struct root <list <
		T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
		T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
	> > :
	node <T1, typename root <list <
		T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12, T13,
		T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
	> >::type> { };

template <>
struct root <list <> > : null { };

//-----------------------------------------------------------------------------
// root node of _

template <
	typename T1,  typename T2,  typename T3,  typename T4,  typename T5,
	typename T6,  typename T7,  typename T8,  typename T9,  typename T10,
	typename T11, typename T12, typename T13, typename T14, typename T15,
	typename T16, typename T17, typename T18, typename T19, typename T20,
	typename T21, typename T22, typename T23, typename T24
>
struct root <_<
		T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
		T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
	> > :
	root <list <
		T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
		T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
	> > { };

//-----------------------------------------------------------------------------
// model (representation) of type T. this is T for atoms, but if T is a
// list or _, then T and all nested lists are recursively replaced by
// their node representation, starting from their root node

// defined below
template <typename T>
struct model;

template <typename L>
struct list_model : model <typename root <L>::type> { };

template <typename T>
struct model : if_list <T, list_model <T> >::type { };

template <typename T1, typename T2>
struct model <node <T1, T2> > :
	node <typename model <T1>::type, typename model <T2>::type> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_t       <nat>             ::name[] = "nat";
template <> char template_tt      <node>            ::name[] = "node";
template <> char template_t       <root>            ::name[] = "root";

template <typename O> O& operator<< (O& o, name <null>)       { return o << "()"; }

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_DATA_MODEL_HPP
