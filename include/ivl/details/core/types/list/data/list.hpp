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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_DATA_LIST_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_DATA_LIST_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

typedef t_true _true;
typedef t_false _false;

//-----------------------------------------------------------------------------

// identity
template <typename T>
struct id { typedef T type; };

// has type of
template <typename T>
struct type_of : id <typename T::type> { };

//-----------------------------------------------------------------------------

// node or list terminator
struct term : id <term> { };

template <typename T, typename THEN, typename ELSE>
struct if_term : t_if <t_eq <T, term>, THEN, ELSE> { };

//-----------------------------------------------------------------------------

// defined in eval
template <typename L>
struct prop;

// list base class identifier
struct list_id { };

// list base class containing the derived list L
template <typename L>
struct base : list_id, prop <L> { typedef L list; };

//-----------------------------------------------------------------------------
// list structure, just inheriting its base

template <
	typename T1  = term, typename T2  = term, typename T3  = term,
	typename T4  = term, typename T5  = term, typename T6  = term,
	typename T7  = term, typename T8  = term, typename T9  = term,
	typename T10 = term, typename T11 = term, typename T12 = term,
	typename T13 = term, typename T14 = term, typename T15 = term,
	typename T16 = term, typename T17 = term, typename T18 = term,
	typename T19 = term, typename T20 = term, typename T21 = term,
	typename T22 = term, typename T23 = term, typename T24 = term
>
struct list :
	base <list <
		T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
		T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
	> > { };

//-----------------------------------------------------------------------------
// just a synonym for list

template <
	typename T1  = term, typename T2  = term, typename T3  = term,
	typename T4  = term, typename T5  = term, typename T6  = term,
	typename T7  = term, typename T8  = term, typename T9  = term,
	typename T10 = term, typename T11 = term, typename T12 = term,
	typename T13 = term, typename T14 = term, typename T15 = term,
	typename T16 = term, typename T17 = term, typename T18 = term,
	typename T19 = term, typename T20 = term, typename T21 = term,
	typename T22 = term, typename T23 = term, typename T24 = term
>
struct _ : list <
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> { };

//-----------------------------------------------------------------------------

template <typename T>
struct is_list : is_base <list_id, T> { };

template <typename T, typename THEN, typename ELSE = id <T> >
struct if_list : t_if <is_list <T>, THEN, ELSE> { };

//-----------------------------------------------------------------------------
// is_list for list

template <
	typename T1,  typename T2,  typename T3,  typename T4,  typename T5,
	typename T6,  typename T7,  typename T8,  typename T9,  typename T10,
	typename T11, typename T12, typename T13, typename T14, typename T15,
	typename T16, typename T17, typename T18, typename T19, typename T20,
	typename T21, typename T22, typename T23, typename T24
>
struct is_list <list <
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> > : _true { };

//-----------------------------------------------------------------------------
// is_list for _

template <
	typename T1,  typename T2,  typename T3,  typename T4,  typename T5,
	typename T6,  typename T7,  typename T8,  typename T9,  typename T10,
	typename T11, typename T12, typename T13, typename T14, typename T15,
	typename T16, typename T17, typename T18, typename T19, typename T20,
	typename T21, typename T22, typename T23, typename T24
>
struct is_list <_<
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> > : _true { };

//-----------------------------------------------------------------------------

namespace intro {

template <typename O> O& operator<< (O& o, name <term>)       { return o << "term"; }

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details

//-----------------------------------------------------------------------------

using list_details::list;
using list_details::_;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_DATA_LIST_HPP
