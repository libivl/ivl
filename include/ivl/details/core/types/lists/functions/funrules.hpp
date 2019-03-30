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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_FUNCTIONS_FUNRULES_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_FUNCTIONS_FUNRULES_HPP

namespace ivl {

namespace types {

namespace lists {

template<class RULES, class BODY>
struct fun_rules_t
{
	typedef typename lists::details::sr_main<
		typename model<RULES>::type, typename eval<BODY>::type>
		::type replaced_type;

	typedef typename lists::eval<replaced_type>::type type;	
};

} // namespace lists
//-----------------------------------------------------------------------------

//struct fun_rules : lists::lazy_args_id, t2<lists::fun_rules_t> { };
struct fun_rules : scheme::label<fun_rules> { };
//template <> char scheme::label <t2<lists::fun_rules_t> >::text[] = "fun_rules";
template <> char scheme::label <fun_rules>::text[] = "fun_rules";

// here is also a possible distinction.
namespace lists {

// add 'fun_rules' to binders
template<> struct binder<fun_rules> : unquote_rules<t_true> { };

// obtain vars from 'fun_rules' expression
template<class TS> 
struct binder_vars<fun_rules, TS> : 
	details::flatten<typename details::cars2<TS>::type> { };
/*
template<class T1, class T2>
struct run<node<node<fun_rules, T1>, T2> > : public
	run<typename l_concat<node<fun_rules, node<T1, node<null, null> > >, 
		node<T2, node<null, null> >
	>::type> { };
*/
template<class T1>
struct run<node<fun_rules, T1> > : node<fun_rules, T1> { };


template<class T1, class T2>
struct run<node<node<fun_rules, T1>, T2> > : fun_rules_t<T1, T2> { };

template<class T1>
struct run<node<node<fun_rules, T1>, node<null, null> > > : public
	t_id<node<node<fun_rules, T1>, node<null, null> > > { };
	
} // namespace lists

//-----------------------------------------------------------------------------

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LIST_FUNCTIONS_FUNRULES_HPP
