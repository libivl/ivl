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

#ifndef IVL_CORE_DETAILS_TYPES_MATCH_HPP
#define IVL_CORE_DETAILS_TYPES_MATCH_HPP

namespace ivl {

namespace types {

namespace matches {

using lists::details::lookup;
using lists::details::lookup_sub;

// ----------------------------------------------------------------------------

struct match_var_id { };

struct t : match_var_id { };
struct t1 : match_var_id { };
struct t2 : match_var_id { };
struct t3 : match_var_id { };
struct t4 : match_var_id { };
struct t5 : match_var_id { };
struct t6 : match_var_id { };
struct t7 : match_var_id { };
struct t8 : match_var_id { };
struct t9 : match_var_id { };

struct s : match_var_id { };
struct s1 : match_var_id { };
struct s2 : match_var_id { };
struct s3 : match_var_id { };
struct s4 : match_var_id { };
struct s5 : match_var_id { };
struct s6 : match_var_id { };
struct s7 : match_var_id { };
struct s8 : match_var_id { };
struct s9 : match_var_id { };

struct k : match_var_id { };
struct k1 : match_var_id { };
struct k2 : match_var_id { };
struct k3 : match_var_id { };
struct k4 : match_var_id { };
struct k5 : match_var_id { };
struct k6 : match_var_id { };
struct k7 : match_var_id { };
struct k8 : match_var_id { };
struct k9 : match_var_id { };

// ----------------------------------------------------------------------------

template<class T1, class T2>
struct mtt2 { };

template<class T1, class T2, class T3>
struct mtt3 { };

template <class T>
struct is_var : is_base<match_var_id, typename bare_type<T>::type> { };

template <class P>
struct dependant : lazy<P>::template reduce<is_var, t_or> { };

template <class P>
struct dependant_tree : lazy<P>::template seq<is_var, t_id> { };

template<class L>
struct replacer
{
	template<class E>
	struct r_s : lookup_sub<E, L> { };
	
	template<class P>
	struct replace : lazy<P>::template seq<r_s, t_id> { };
};

template<>
struct replacer<nat> 
{ 
	template<class P>
	struct replace : nat { };
};

// ----------------------------------------------------------------------------

template<class K, class L, class S>
struct merge_key_spec : t_if<t_eq<S, typename K::val>, L, nat> { };

template<class K, class L>
struct merge_key_spec<K, L, nat> : node<K, L> { };

template<class K, class L>
struct merge_key : merge_key_spec<K, L, 
	typename lookup<typename K::val, L>::type> { };

template<class K>
struct merge_key<K, nat> : nat { };

template<class L1, class L2>
struct merge : nat { };

template<class N, class NS, class L>
struct merge<node<N, NS>, L> : merge<NS, typename merge_key<N, L>::type> { };

template<class N, class NS>
struct merge<node<N, NS>, nat> : nat { };

template<class L>
struct merge<null_node, L> : t_id<L> { };

template<>
struct merge<null_node, nat> : nat { };

// ----------------------------------------------------------------------------

template <class T, class P, class D>
struct match_spec_2 : nat { };

// T is a variable
template <class T, class P>
struct match_spec_2<T, P, t_true> : 
	node<node<P, node<T, null_node> >, null_node> { };

template <class T, class P, class D>
struct match_spec : nat { };

template <class T>
struct match_spec<T, T, t_false> : null_node { };

template <class T, class P>
struct match : match_spec<T, P, typename dependant<P>::type> { }; 

template <class T, class P>
struct match_spec<T, P, t_true> : 
	match_spec_2<T, P, typename dependant_tree<P>::type> { };

template<template<class> class C, class T1, class P1>
struct match<C<T1>, C<P1> > : match<T1, P1> { };

template<template<class, class> class C, class T1, class P1, class T2, class P2>
struct match<C<T1, T2>, C<P1, P2> > : merge<typename match<T1, P1>::type, 
	typename match<T2, P2>::type> { };

template<template<class, class, class> class C, 
	class T1, class P1, class T2, class P2, class T3, class P3>
struct match<C<T1, T2, T3>, C<P1, P2, P3> > : merge<typename match<T1, P1>::type, 
	typename match<mtt2<T2, T3>, mtt2<P2, P3> >::type> { };

template<template<class, class, class, class> class C, 
	class T1, class P1, class T2, class P2, class T3, class P3, class T4, class P4>
struct match<C<T1, T2, T3, T4>, C<P1, P2, P3, P4> > : merge<typename match<T1, P1>::type, 
	typename match<mtt3<T2, T3, T4>, mtt3<P2, P3, P4> >::type> { };

// ----------------------------------------------------------------------------

template <class T, class P>
struct test_pattern
{
	typedef typename match<T, P>::type l_t;
	typedef typename replacer<l_t>::template replace<P>::type r_t;
	typedef typename is_conv<T, r_t>::type type;
};

template<class T>
struct has_ivl_base : has_typedef_base_class<T> { };

template <class T, class P, class B>
struct test_pattern_base_test 
{
	typedef typename T::base_class b_t;
	typedef typename has_ivl_base<b_t>::type b_t_b;
	typedef test_pattern<T, P> t_pat;
	typedef typename t_pat::type t_1;
	
	typedef typename t_if<t_and<t_not<t_1>, 
		t_neq<b_t, typename bare_type<T>::type> >,
			test_pattern_base_test<b_t, P, b_t_b>,
			t_1>::type::type type;
};

template <class T, class P>
struct test_pattern_base_test<T, P, t_false> : test_pattern<T, P> { };

template <class T, class P>
struct test_pattern_base : 
	test_pattern_base_test<T, P, typename has_ivl_base<T>::type> { };


} // namespace matches

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_MATCH_HPP
