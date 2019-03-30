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

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_FUNCTIONS_SYNTAXRULES_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_FUNCTIONS_SYNTAXRULES_HPP

namespace ivl {

namespace types {

namespace lists {

//-----------------------------------------------------------------------------

struct syntax_rules_init : scheme::keyword<syntax_rules_init> { };
template<> char scheme::label<syntax_rules_init>::text[] = "syntax_rules*";

template<class T> 
struct pre<node<scheme::syntax_rules, T> > : node<syntax_rules_init, T> { };

//=============================================================================

template<class RULES, class BODY>
struct syntax_rules_t //:  _<lambda, _<BODY>, _<> > //{ }; // nat { };
{
	//typedef number<1> type;
	typedef typename lists::details::sr_main<
		typename model<RULES>::type, typename model<BODY>::type>::type r_t;

	typedef typename lists::eval<r_t>::type type;	
};

// disable direct execution of syntax rules.
// this will prevent plain define-syntax lists from being run.
template<class T1, class T2>
struct run<node<node<scheme::syntax_rules, T1>, T2> > : nat { };
template<class T2>
struct run<node<scheme::syntax_rules, T2> > : nat { };

// persist when having form sr, ..
template<class T2>
struct run<node<syntax_rules_init, T2> > : 
	node<syntax_rules_init, T2>{ };

template<class T1, class T2>
struct run<node<node<syntax_rules_init, T1>, T2> > :
	syntax_rules_t<T1, T2> { };

template<class T1>
struct run<node<node<syntax_rules_init, T1>, node<null, null> > > : nat { };

//-----------------------------------------------------------------------------


} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_FUNCTIONS_SYNTAXRULES_HPP
