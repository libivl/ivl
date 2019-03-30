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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_FUNCTIONS_CASES_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_FUNCTIONS_CASES_HPP

namespace ivl {

namespace types {

namespace lists {

namespace details {

//-----------------------------------------------------------------------------
	
template<class RULE, class B, class KW>
struct cas_rule : public nat { };

template<class P, class PS, class T, class B, class KW>
struct cas_rule<node<node<P, PS>, node<T, node<null, null> > >, B, KW>
{
	typedef typename match<node<P, PS>, B, KW, node<null, null> >
		::type match_type;
	typedef typename t_if<t_eq<match_type, nat>, nat, 
		l_replace<match_type, T> 
		//sr_eval<T, match_type> 
		>::type::type type;
};

//-----------------------------------------------------------------------------

template<class RULES, class BODY, class KEYWORDS>
struct cas_test : public nat { };

// no match!
template<class B, class KW>
struct cas_test<node<null, null>, B, KW> : public nat { };

template<class R, class RS, class B, class KW>
struct cas_test<node<R, RS>, B, KW>
{
	typedef typename cas_rule<R, B, KW>::type r_type;
	typedef typename t_if<t_eq<r_type, nat>, cas_test<RS, B, KW>,
		t_id<r_type> >::type::type type;
};

template<class RULES, class BODY>
struct cas_main : nat { }; //public _<lambda, _<RULES>, _<> > { }; // nat

// special case of syntax rule without literals that has only one case
template<class N, class NS, class B>
struct cas_main<node<node<N, NS>, node<null, null> >, B> : cas_main
	<node<node<null, null>, node<node<N, NS>, node<null, null> > >, B>
{ };

template<class K, class KS, class R, class RS, class B>
struct cas_main<node<node<K, KS>, node<R, RS> >, B> : public
	cas_test<node<R, RS>, B, node<K, KS> > { };

//-----------------------------------------------------------------------------

//TODO: tidy
struct cas_v : scheme::identifier<cas_v> { };
} // namespace details
} // namespace lists
namespace scheme {
template<> char label <lists::details::cas_v>::text[] = "#autovar#"; // # N;
} // namespace scheme
namespace lists {
namespace details {

template<class RULES>
struct cas_count : nat { }; 

// special case of case rule without literals that has only one case
template<class N, class NS>
struct cas_count<node<node<N, NS>, node<null, null> > > : 
	match_count<typename N::val, node<null, null>, var<cas_v, 0> >
{ };

template<class K, class KS, class R, class RS>
struct cas_count<node<node<K, KS>, node<R, RS> > > : 
	match_count<typename R::val, node<null, null>, var<cas_v, 0> > { };

//-----------------------------------------------------------------------------
	
} // namespace details

template<class RULES, class BODY>
struct cases_t
{
	typedef typename lists::details::cas_main<
		typename model<RULES>::type, 
		typename eval<BODY>::type>
		::type replaced_type;

	typedef typename lists::eval<replaced_type>::type type;	
	//typedef 
};

} // namespace lists
//-----------------------------------------------------------------------------

struct cases : scheme::label<cases> { };
template <> char scheme::label <cases>::text[] = "cases";

// here is also a possible distinction.
namespace lists {

// add 'cases' to binders
template<> struct binder<cases> : t_true { };

// obtain vars from 'cases' expression
// NOTE: TODO: should be unique. also should be : variable_id instances only
template<class TS> 
struct binder_vars<cases, TS> : 
	details::flatten<typename 
			//node<typename // dbg
		details::cars2<TS>
			//::type, nat> // dbg			
	::type> 
	{ };

template<class T1>
struct run<node<cases, T1> > : node<cases, T1> { };

/* was:
template<class T1, class T2>
struct run<node<node<cases, T1>, T2> > : cases_t<T1, T2> { };
*/

struct run_cases : scheme::label<run_cases> { };
template <> char scheme::label <run_cases>::text[] = "cases!";

template<class T1, class T2>
struct run<node<node<run_cases, T1>, T2> > : cases_t<T1, T2> { };

namespace details {

// ((cases C) L) -> ((lambda V1..Vcount{C} ((cases C) V1..Vcount{C})) L)
template<class T1, class T2, class CVARS>
struct case_transition : 
	run<node<node<lambda, node<CVARS, 
		node<node<node<run_cases, T1>, CVARS> , node<null, null> > > >, T2>
	> { };

} // namespace details

template<class T1, class T2>
struct run<node<node<cases, T1>, T2> > : details::
	case_transition<T1, T2, typename details::cas_count<T1>::type> { };

template<class T1>
struct run<node<node<cases, T1>, node<null, null> > > : public
	t_id<node<node<cases, T1>, node<null, null> > > { };
	
} // namespace lists

//-----------------------------------------------------------------------------

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LIST_FUNCTIONS_CASES_HPP
