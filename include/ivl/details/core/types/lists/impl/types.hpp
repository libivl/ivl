/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the nulls of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the nulls
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

/*
lists/impl/types.hpp: A collection of basic node type functions, as templates.
*/

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_TYPES_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_TYPES_HPP

namespace ivl {

namespace types {
//-----------------------------------------------------------------------------

// check if var V is in list L
template<class V, class L>
struct l_in : public nat { };

template<class V>
struct l_in<V, node<null, null> > : t_false { };

template<>
struct l_in<null, node<null, null> > : t_false { };

template<class V, class S>
struct l_in<V, node<V, S> > : t_true { };

template<class V, class P, class S>
struct l_in<V, node<P, S> > : l_in<V, S> { };

//-----------------------------------------------------------------------------

// recursively check if var V is in list L
template<class V, class L>
struct l_find : public nat { };

template<class V>
struct l_find<V, node<null, null> > : t_false { };

template<>
struct l_find<null, node<null, null> > : t_false { };

template<class V, class S>
struct l_find<V, node<V, S> > : t_true { };

template<class V, class P, class S>
struct l_find<V, node<P, S> > : l_find<V, S> { };

template<class V, class VS, class S>
struct l_find<node<V, VS>, node<node<V, VS>, S> > : t_true { };

// TODO: fixing this
template<class V, class P, class PS, class S>
struct l_find<V, node<node<P, PS>, S> > : t_if<l_find<V, node<P, PS> >,
	t_true, l_find<V, S> >::type { };

//-----------------------------------------------------------------------------

template <class L1, class L2>
struct l_concat : public lists::seq<L2, t_id, node, L1> { };

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// first element
template <class T>
struct l_car : public nat { };

template <>
struct l_car<node<null, null> > : public nat { };

template <class T1, class T2>
struct l_car<node<T1, T2> > : public t_id<T1> { };

//-----------------------------------------------------------------------------

// remove first element
template <class T>
struct l_cdr : public nat { };

template <>
struct l_cdr<node<null, null> > : public nat { };

template <class T1, class T2>
struct l_cdr<node<T1, T2> > : public t_id<T2> { };

//-----------------------------------------------------------------------------

// push front
template <class T1, class T2>
struct l_cons : public nat { };

template <class K, class T1, class T2>
struct l_cons<K, node<T1, T2> > : public t_id<node<K, node<T1, T2> > > { };

//-----------------------------------------------------------------------------




} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_TYPES_HPP
