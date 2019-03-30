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

/* syntax.hpp: a set of utilities used for syntax-rule parsing */

#ifndef IVL_CORE_DETAILS_TYPES_LIST_IMPL_SYNTAX_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_IMPL_SYNTAX_HPP

namespace ivl {

namespace types {

namespace lists {

namespace details {

//-----------------------------------------------------------------------------

template<class RULE, class STACK, class NUM>
struct match_count : nat { };

template<class S, class V, int N>
struct match_count<node<null, null>, S, var<V, N> > : S { };

template<class R, class RS, class S, class V, int N>
struct match_count<node<R, RS>, S, var<V, N> > : 
	match_count<RS, node<var<V, N>, S>, var<V, N+1> > { };

// ... other rules too ...	

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

template<class RV, class R, class N, class MV>
struct match_uni : nat { };

// ??? case
template<class R, class MV>
struct match_uni<nat, R, nat, MV> : nat { };

template<class RV, class R, class MV>
struct match_uni<RV, R, RV, MV> : MV { };

template<class R, class N, class MV>
struct match_uni<nat, R, N, MV> : 
	node<node<R, node<N, node<null, null> > >, MV> { };

//-----------------------------------------------------------------------------

template<class IS_KW, class R, class N, class MV>
struct match_var : match_uni<typename lookup<R, MV>::type, R, N, MV> { };

template<class R, class N>
struct match_var<t_false, R, N, nat> : nat { };

template<class R, class N, class MV>
struct match_var<t_true, R, N, MV> : nat { };

template<class R, class MV>
struct match_var<t_true, R, R, MV> : MV { };

//-----------------------------------------------------------------------------

template<class RULE, class NODE, class KW, class MV>
struct match : match_var<typename t_if<l_in<RULE, KW>, t_true,
	t_not<is_identifier<RULE> > >::type::type, RULE, NODE, MV> { };

template<class KW, class MV>
struct match<node<null, null>, node<null, null>, KW, MV> : public MV { };

// no match!
template<class N, class NS, class KW, class MV>
struct match<node<null, null>, node<N, NS>, KW, MV> : public nat { };

//-----------------------------------------------------------------------------

template<class R, class N, class KW, class MV>
struct match_join : match<R, N, KW, MV> { };

template<class R, class N, class KW>
struct match_join<R, N, KW, nat> : nat { };

template<class R, class RS, class N, class NS, class KW, class MV>
struct match<node<R, RS>, node<N, NS>, KW, MV> :
	match_join<RS, NS, KW, typename match<R, N, KW, MV>::type> { };

//-----------------------------------------------------------------------------

template<class RS, class N, class NS, class KW, class MV>
struct match<node<onedot, node<RS, node<null, null> > >, node<N, NS>, KW, MV> :
	match<RS, node<N, NS>, KW, MV> { };

// TODO: re-think	
template<class RS, class N, class NS, class KW, class MV>
struct match<node<node<onedot, node<null, null> >, 
	node<RS, node<null, null> > >, node<N, NS>, KW, MV> :
		match<RS, node<N, NS>, KW, MV> { };

template<class R, class N, class NS, class KW, class MV>
struct match<node<R, dots>, node<N, NS>, KW, MV> :
	match_var<t_false, node<R, dots>, node<N, NS>, 
		typename match_var<t_false, R, N, MV>::type> { };

template<class NS, class KW>
struct match_join<node<node<null, null>, dots>, NS, KW, nat> : nat { };

template<class NS, class KW, class MV>
struct match_join<node<node<null, null>, dots>, NS, KW, MV> : MV { };

template<class R, class RS, class N, class NS, class KW, class MV>
struct match<node<node<R, RS>, dots>, node<N, NS>, KW, MV> : match<
	node<node<R, dots>, node<RS, dots> >, 
	node<typename cars<node<N, NS> >::type, typename cdrs<node<N, NS> >::type>,
		KW, MV> { };
		
//-----------------------------------------------------------------------------

template<class T, class MV>
struct sr_eval
{
	typedef typename lookup<T, MV>::type lu_t;
	typedef typename t_if<t_eq<lu_t, nat>, T, lu_t>::type type;
};

template<class T, class TS, class MV>
struct sr_eval<node<T, TS>, MV> : public
	node<typename sr_eval<T, MV>::type,
		typename sr_eval<TS, MV>::type> { };
	
template<class T, class TD, class TS, class MV>
struct sr_eval<node<node<T, TD>, TS>, MV> : public
	node<typename sr_eval<node<T, TD>, MV>::type, 
		typename sr_eval<TS, MV>::type> { };
		
template<class T, class TD, class MV>
struct sr_eval<node<node<T, TD>, dots>, MV> : public
	conses <
		typename sr_eval<node<T, dots>, MV>::type,
		typename sr_eval<node<TD, dots>, MV>::type
	> { };

/*template <class T, class MV>
struct sr_eval<node<T, dots>, MV> :
	detect_var<typename lookup<node<T, dots>, MV>::type> { };
*/
template <class T, class MV>
struct sr_eval<node<T, dots>, MV> 
{
	typedef typename lookup<node<T, dots>, MV>::type lu_t0;
	typedef typename detect_var<lu_t0>::type lu_t;
	typedef typename t_if<t_eq<lu_t0, nat>, 
		node<T, node<null, null> >, lu_t>::type type;
};
	
template <class MV>
struct sr_eval<node<node<null, null>, dots>, MV> : node<null, null> { };

template<class T, class MV>
struct sr_eval<node<onedot, node<T, node<null, null> > >, MV> : 
	lookup<T, MV> { };

// TODO: re-think		
template<class T, class MV>
struct sr_eval<node<node<onedot, node<null, null> >, 
	node<T, node<null, null> > >, MV> : 
		lookup<T, MV> { };

//-----------------------------------------------------------------------------

// TODO: decide: l_replace with MV, or plain t_id?+
// Later notice: or let as is.
template<class TD, class MV> 
struct sr_eval<node<scheme::unquote, node<node<TD, node<null, null> >, 
	node<null, null> > >, MV> : t_id<TD> { };

//-----------------------------------------------------------------------------

template<class RULE, class B, class KW>
struct sr_rule : public nat { };

template<class P, class PS, class T, class B, class KW>
struct sr_rule<node<node<P, PS>, node<T, node<null, null> > >, B, KW>
{
	typedef typename match<node<P, PS>, B, KW, node<null, null> >
		::type match_type;
	typedef typename t_if<t_eq<match_type, nat>, nat, sr_eval<T, match_type> >
		::type::type type;
};

//-----------------------------------------------------------------------------

template<class RULES, class BODY, class KEYWORDS>
struct sr_test : public nat { };

// no match!
template<class B, class KW>
struct sr_test<node<null, null>, B, KW> : public nat { };

template<class R, class RS, class B, class KW>
struct sr_test<node<R, RS>, B, KW>
{
	typedef typename sr_rule<R, B, KW>::type r_type;
	typedef typename t_if<t_eq<r_type, nat>, sr_test<RS, B, KW>,
		t_id<r_type> >::type::type type;
};

template<class RULES, class BODY>
struct sr_main : nat { }; //public _<lambda, _<RULES>, _<> > { }; // nat

// special case of syntax rule without literals that has only one case
template<class N, class NS, class B>
struct sr_main<node<node<N, NS>, node<null, null> >, B> : public
	sr_main<node<node<null, null>, node<node<N, NS>, node<null, null> > >, B>
{ };

template<class K, class KS, class R, class RS, class B>
struct sr_main<node<node<K, KS>, node<R, RS> >, B> : public
	sr_test<node<R, RS>, B, node<K, KS> > { };

//-----------------------------------------------------------------------------
	
} // namespace details

} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LIST_IMPL_SYNTAX_HPP
