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
list_tools.hpp: necessary structs for lookup and other operations needed.
*/

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_TOOLS_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_TOOLS_HPP

namespace ivl {

namespace types {
namespace lists {
namespace details {

//-----------------------------------------------------------------------------

// search for a key and return val in pairs (key, val) or nat if not found
template<class N, class T>
struct lookup : public nat { };

template<class N>
struct lookup<N, node<null, null> > : public nat { };

template<class N, class T, class TV, class TS>
struct lookup<N, node<node<T, TV>, TS> > : public lookup<N, TS> { };

template<class N, class TV, class TS>
struct lookup<N, node<node<N, TV>, TS> > : public t_id<typename TV::val> { };

//-----------------------------------------------------------------------------

// substitute N with val if (N, val) found in pairs (key, val) T
template<class N, class T>
struct lookup_sub : nat { };

template<class N>
struct lookup_sub<N, node<null, null> > : t_id<N> { };

template<class N, class T, class TV, class TS>
struct lookup_sub<N, node<node<T, TV>, TS> > : lookup_sub<N, TS> { };

template<class N, class TV, class TS>
struct lookup_sub<N, node<node<N, TV>, TS> > : t_id<typename TV::val> { };

//-----------------------------------------------------------------------------

// remove a keys in N and its corresponding val from pairs (key, val) T
template<class N, class T>
struct remove_keys : public nat { };

template<class N>
struct remove_keys<N, node<null, null> > : node<null, null> { };

template<class N, class K, class KS, class TS>
struct remove_keys<N, node<node<K, KS>, TS> > : t_if<l_in<K, N>, 
	remove_keys<N, TS>,
	node<node<K, KS>, typename remove_keys<N, TS>::type> >::type { };

//-----------------------------------------------------------------------------

// convert a recursive list to a same-order flat linear representation
template<class T>
struct flatten : public nat { };

template<>
struct flatten<node<null, null> > : node<null, null> { };

template<class T, class TS>
struct flatten<node<T, TS> > : public node<T, typename flatten<TS>::type> { };

template<class T, class TD, class TS>
struct flatten<node<node<T, TD>, TS> > : public l_concat<
	typename flatten<node<T, TD> >::type, typename flatten<TS>::type> { };

//-----------------------------------------------------------------------------

// dot product of two lists m, n as in: m... dot n... -> (m n)...
template<class M, class N>
struct l_dot : public nat { };

template<>
struct l_dot<node<null, null>, node<null, null> > : node<null, null> { };

template<class M, class MS, class N, class NS>
struct l_dot<node<M, MS>, node<N, NS> > :
	node<
		node<M, node<N, node<null, null> > >,
		typename l_dot<MS, NS>::type> { };

//-----------------------------------------------------------------------------

template<class T1, class T2>
struct l_either : t_if<t_eq<typename T1::type, nat>, T2, T1>::type { };
	
//-----------------------------------------------------------------------------

} // namespace details

} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_TOOLS_HPP
