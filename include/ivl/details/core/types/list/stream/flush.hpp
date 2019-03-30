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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STREAM_FLUSH_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STREAM_FLUSH_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

// defined below
template <typename I, typename V, typename S, typename X, typename Y>
struct scan_id;

template <typename T, typename S, typename X = single <T>, typename Y = empty>
struct scan : scan_id <T, typename identify <T, S, 1>::type, S, X, Y> { };

template <typename S, typename X, typename Y>
struct scan <null, S, X, Y> : Y { };

template <typename T, typename TN, typename S, typename X, typename Y>
struct scan <node <T, TN>, S, X, Y> : merge <
	typename scan <T, S, X, Y>::type,
	typename scan <TN, S, X, Y>::type
> { };

template <typename F, typename E, typename S, typename X>
struct scan <closure <F, E>, S, X> : scan <F, join <E, S>, X> { };

//-----------------------------------------------------------------------------

template <typename I, typename V, typename S, typename X, typename Y>
struct scan_check :
	t_if <in <V, X>, add <V, Y>, scan <V, S, add <V, X>, Y> >::type { };

template <typename I, typename V, typename S, typename X, typename Y>
struct scan_id : t_if <t_eq <I, V>, Y, scan_check <I, V, S, X, Y> >::type { };

//-----------------------------------------------------------------------------

// defined below
template <typename I, typename V, typename S, typename X, typename Y>
struct subst_id;

template <
	typename T, typename S, typename X = single <T>,
	typename Y = typename scan <T, S>::type
>
struct subst : subst_id <T, typename identify <T, S, 1>::type, S, X, Y> { };

template <typename S, typename X, typename Y>
struct subst <null, S, X, Y> : null { };

template <typename T, typename TN, typename S, typename X, typename Y>
struct subst <node <T, TN>, S, X, Y> : node <
	typename subst <T, S, X, Y>::type,
	typename subst <TN, S, X, Y>::type
> { };

template <typename F, typename E, typename S, typename X, typename Y>
struct subst <closure <F, E>, S, X, Y> :
	id <closure <typename subst <F, join <E, S>, X, Y>::type, E> > { };

//-----------------------------------------------------------------------------

template <typename I, typename V = term>
struct rec : id <rec <I, V> > { };

template <typename I, typename V, typename T, typename Y>
struct subst_label : t_if <in <V, Y>, rec <I, T>, T> { };

template <typename I, typename V, typename S, typename X, typename Y>
struct subst_val :
	subst_label <I, V, typename subst <V, S, add <V, X>, Y>::type, Y> { };

template <typename R, typename V, typename X>
struct subst_first : t_if <t_eq <V, typename X::first>, block <R>, R> { };

template <typename I, typename V, typename S, typename X, typename Y>
struct subst_rec : subst_first <rec <I>, V, X> { };

template <typename I, typename V, typename S, typename X, typename Y>
struct subst_check : t_if <
	in <V, X>, subst_rec <I, V, S, X, Y>, subst_val <I, V, S, X, Y>
>::type { };

template <typename I, typename V, typename S, typename X, typename Y>
struct subst_id :
	t_if <t_eq <I, V>, id <I>, subst_check <I, V, S, X, Y> >::type { };

//-----------------------------------------------------------------------------

template <typename T>
struct flush : subst <typename T::type, typename T::state> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_tt      <rec>                   ::name[] = "rec";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STREAM_FLUSH_HPP
