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

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_SUBSTITUTION_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_SUBSTITUTION_HPP

namespace ivl {

namespace types {

namespace lists {


template<class T>
struct unquote_rule { };
template<class T>
struct deunquote_rule { };

template<class K, class V>
struct unquote_rule<node<K, node<V, node<null, null> > > > :
	node<K, node<node<scheme::unquote, node<node<V, node<null, null> >, 
		node<null, null> > >, node<null, null> > > { };
	
template<class K, class V>
struct deunquote_rule<node<K, node<node<scheme::unquote, node<
	node<V, node<null, null> >, node<null, null> > >, node<null, null> > > > :
			node<K, node<V, node<null, null> > > { };

template<class S>
struct unquote_rules : seq<node<null, null>, unquote_rule, node, S> { };
template<class S>
struct deunquote_rules : seq<node<null, null>, deunquote_rule, node, S> { };

template<> struct binder<scheme::unquote> : t_id<unquote_rule<t_false> > { };
template<class TS> 
struct binder_vars<scheme::unquote, TS> : node<null, null> { };

namespace details {

//-----------------------------------------------------------------------------

// tests if form var<..., N> is somewhere in pattern T
template<int N, class T>
struct infvi : t_false { };

template<int N, class T>
struct infvi<N, var<T, N> > : t_true { };

template<int N, class T, class TS>
struct infvi<N, node<T, TS> > : t_or<infvi<N, T>, infvi<N, TS> > { };

//-----------------------------------------------------------------------------

template<int N, class T>
struct maxvi : number<1> { };

template<int N, class T>
struct maxvi<N, var<T, N> > : number<N> { };

template<int N, class T, class TS>
struct maxvi<N, node<T, TS> > : t_max<maxvi<N, T>, maxvi<N, TS> > { };

//-----------------------------------------------------------------------------

template<int N, class T>
struct testfvi : t_if<infvi<N, T>, testfvi<(N+1), T>, number<N> >::type { };
// searches for a non-used int in the form var<..., #int> in pattern T
// NOTE: this is some place that could be optimized.
// a potentially easy optimization is to block itself from binders.
// the max+1 optimization was not preferred because of the potential
// disaster of accumulating fvi++ for a number of computation cycles
// that is greater than MAX_INT.
// However an applicable mostly O(1) efficient and still generic optimization 
// is to allow max+1 optimization for up to a constant number, e.g. 1024^2 and
// when above that number, use the current, looping 1..inf, brute force method.
//template<class T>
//struct free_var_int : testfvi<0, T> { };

// NOTE: and it is made:
// hybrid finder, using the method described below
template<class T>
struct bestfvi
{
	typedef typename t_add<typename maxvi<1, T>::type, number<1> >
		::type maxfvi;
	typedef typename t_if<t_gt<maxfvi, number<1024*1024> >,
		testfvi<0, T>, t_id<maxfvi> >::type::type type;
};
template<class T>
struct free_var_int : bestfvi<T> { };

//-----------------------------------------------------------------------------

template<class N, class T>
struct fviapply : nat { };

template<int N>
struct fviapply<number<N>, node<null, null> > : node<null, null> { };

template<int N, class T, class TS>
struct fviapply<number<N>, node<T, TS> > : node<var<T, N>, 
	typename fviapply<number<N>, TS>::type> { };

template<int N, class T, int K, class TS>
struct fviapply<number<N>, node<var<T, K>, TS> > : node<var<T, N>,
	typename fviapply<number<N>, TS>::type> { };

//-----------------------------------------------------------------------------


// recursively check if var V is in list L
template<class V, class L>
struct free_var : public nat { };

template<class V>
struct free_var<V, node<null, null> > : t_false { };

template<>
struct free_var<null, node<null, null> > : t_false { };

template<class V, class S>
struct free_var<V, node<V, S> > : t_true { };

template<class V, class P, class S>
struct free_var<V, node<P, S> > : free_var<V, S> { };

template<class V, class VS, class S>
struct free_var<node<V, VS>, node<node<V, VS>, S> > : t_true { };

// recursion helper
// pass through some other binder T of any type
template<class BINDER, class V, class T, class TS>
struct free_var_into : 
	t_if<l_in<V, typename binder_vars<T, TS>::type>, 
	t_false, free_var<V, node<T, TS> > >::type { };

// non-binder
template<class V, class T, class TS>
struct free_var_into<t_false, V, T, TS> : free_var<V, node<T, TS> > { };

template<class V, class P, class PS, class S>
struct free_var<V, node<node<P, PS>, S> > : t_if<
	free_var_into<typename binder<P>::type, V, P, PS>,
	t_true, free_var<V, S> >::type { };

//-----------------------------------------------------------------------------

template<class FOUND, class K, class KS>
struct rlookup_join : KS { };

template<class K, class KS>
struct rlookup_join<t_true, K, KS> : node<K, typename KS::type> { };

// find set of vals that exist in N from pairs (key, val) T
template<class N, class T>
struct rlookup : public nat { };

template<class N>
struct rlookup<N, node<null, null> > : node<null, null> { };

template<class N, class K, class KV, class TS>
struct rlookup<N, node<node<K, node<KV, node<null, null> > >, TS> > :
	rlookup_join<typename free_var<N, KV>::type, K, rlookup<N, TS> > { };

//-----------------------------------------------------------------------------

// l_replace0: base for l_replace
// default: atom replace
template<class S, class E>
struct l_replace0 : lookup_sub<E, S> { };

template<class T>
struct l_first : nat { };
template<class T>
struct l_first<node<T, node<null, null> > > : t_id<T> { };

// lambda_replace: replaces variables key with val in E for (key, val) in S.
template<class S, class E>
struct l_replace : l_first<
	typename l_replace0<S, node<E, node<null, null> > >::type> { };

//-----------------------------------------------------------------------------

// change binders B from their name to var<.., #unique id> in T
template<class T, class B>
struct l_rebind
{
	typedef typename free_var_int<T>::type fvi;
	typedef typename l_dot<B, typename fviapply<fvi, B>::type>::type r_s;
	typedef typename l_replace0<r_s, T>::type type;
};

//-----------------------------------------------------------------------------

// recursion helper
template<class NOT_MACRO, class S, class T, class TS>
struct l_replaceinto0 : l_replace0<S, node<T, TS> > { };

// l_replace de-macrofier. uses l_replace instead of l_replace0 to re-check.
// do not make use of pre<.> since 'syntax_rules' is specially treated below.
template<class S, class T, class TS>
struct l_replaceinto0<t_false, S, T, TS> : l_replace<S, 
	node<typename lists::model<scheme::define_syntax<T> >::type, TS> > { };

// general case, try l_replace demacrofier
template<class BINDER, class S, class T, class TS>
struct l_replaceinto : l_replaceinto0<typename 
	is_base<nat, scheme::define_syntax<T> >::type, S, T, TS> { };

// pass through some other binder T
template<class S, class T, class TS>
struct l_replaceinto<t_true, S, T, TS>
{
	typedef typename binder_vars<T, TS>::type bind_vars;
	typedef typename remove_keys<bind_vars, S>::type filtered_set;
	typedef typename rlookup<bind_vars, S>::type bad_binders;
	typedef typename t_if<t_eq<bad_binders, node<null, null> >, 
		t_id<TS>, l_rebind<TS, bad_binders> >::type::type filtered_ts;
	typedef typename l_replace0<filtered_set, filtered_ts>::type ts_type;
	typedef node<T, ts_type> type;
};

// pass through some other binder T which demands the unquote rule
template<class S, class T, class TS>
struct l_replaceinto<unquote_rules<t_true>, S, T, TS>
{
	typedef typename binder_vars<T, TS>::type bind_vars;
	typedef typename remove_keys<bind_vars, S>::type filtered_set;
	typedef typename rlookup<bind_vars, S>::type bad_binders;
	typedef typename t_if<t_eq<bad_binders, node<null, null> >, 
		t_id<TS>, l_rebind<TS, bad_binders> >::type::type filtered_ts;
	typedef typename unquote_rules<filtered_set>::type quoted_set;
	typedef typename l_replace0<quoted_set, filtered_ts>::type ts_type;
	typedef node<T, ts_type> type;
};

// pass through some other binder T which breaks the unquote rule
// no bind_vars or rebind -only- because such rules do not have any bind vars
template<class S, class T, class TS>
struct l_replaceinto<unquote_rules<t_false>, S, T, TS>
{
	typedef typename deunquote_rules<S>::type original_set;
	typedef typename l_replace0<original_set, TS>::type ts_type;
	typedef node<T, ts_type> type;
};

// pass through some other binder T which only disallows rebind [set]
// TODO: but this needs some thought
template<class S, class T, class TS>
struct l_replaceinto<number<0>, S, T, TS>
{
	typedef typename binder_vars<T, TS>::type bind_vars;
	typedef typename remove_keys<bind_vars, S>::type filtered_set;
	typedef typename l_replace0<filtered_set, TS>::type ts_type;
	typedef node<T, ts_type> type;
};

// walk list, recurse into list
template<class S, class E, class ES>
struct l_replace0<S, node<E, ES> > :  
	node<typename l_replace0<S, E>::type, 
		typename l_replace0<S, ES>::type> { };

// demacrofier: command for syntax_rules. 
// uses l_replace instead of l_replace0 to re-check
template<class S, class BS, class ES>
struct l_replace0<S, node<node<scheme::syntax_rules, BS>, ES> >  :  
	l_replace<S, typename lists::details::sr_main<BS, ES>::type> { };
		
template<class S, class B, class BS, class ES>
struct l_replace0<S, node<node<B, BS>, ES> >  :  
	node<typename l_replaceinto<typename binder<B>::type, S, B, BS>::type, 
		typename l_replace0<S, ES>::type> { };

//-----------------------------------------------------------------------------

template<class S, class T, class TD>
struct l_replace0<S, node<dotsy<node<T, TD> >, node<null, null> > > : conses <
		typename l_replace0<S, node<dotsy<T>, node<null, null> > >::type,
		typename l_replace0<S, node<dotsy<TD>, node<null, null> > >::type> { };

template<class T, class S>
struct l_test_dots : lookup<T, S> { };

template<class T, class TS, class S>
struct l_test_dots<node<T, TS>, S> : l_either<
	l_test_dots<T, S>, l_test_dots<TS, S> > { };

template<class S>
struct l_test_dots<node<null, null>, S> : nat { };

template<class S, class T, class TD>
struct l_replace0<S, node<node<T, TD>, dots> > 
{
	// search for any known vars in the pattern
	typedef typename l_test_dots<node<T, TD>, S>::type found_t;
	typedef typename t_if<t_eq<found_t, nat>, node<node<T, TD>, dots>,
		l_replace0<S, node<dotsy<node<T, TD> >, node<null, null> > >
	>::type::type type;
};

template<class S, class T>		
struct l_replace0<S, node<dotsy<T>, node<null, null> > >
{
	typedef typename lookup<node<T, dots>, S>::type lu_t0;
	typedef typename detect_var<lu_t0>::type lu_t;
	typedef typename t_if<t_eq<lu_t0, nat>, 
		node<T, node<null, null> >, lu_t>::type type;
};

template <class S, class T>
struct l_replace0<S, node<T, dots> >
{
	typedef typename lookup<node<T, dots>, S>::type lu_t0;
	typedef typename detect_var<lu_t0>::type lu_t;
	typedef typename t_if<t_eq<lu_t0, nat>, // either
		node<T, dots>, lu_t>::type type;
};

template <class S>
struct l_replace0<S, node<dotsy<node<null, null> >, node<null, null> > > : 
	node<null, null> { };

// NOTE: imprudent rule, assumes never existing pattern _<_<>, etc>
// TODO: may not be needed
//template <class S>
//struct l_replace0<S, node<node<null, null>, dots> > : node<null, null> { };

template<class S, class T>
struct l_replace0<S, node<onedot, node<T, node<null, null> > > > :
	l_either<lookup<T, S>, node<onedot, node<T, node<null, null> > > > { };

//-----------------------------------------------------------------------------
		
// atom replace
//template<class S, class E>
//struct l_replace0<S, E> 
	
//-----------------------------------------------------------------------------

} // namespace details

} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_SUBSTITUTION_HPP
