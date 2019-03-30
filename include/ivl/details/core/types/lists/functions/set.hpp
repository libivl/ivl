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

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_FUNCTIONS_SET_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_FUNCTIONS_SET_HPP

namespace ivl {

namespace types {

//-----------------------------------------------------------------------------

namespace lists {

namespace details {
	

} // namespace details

} // namespace lists

//-----------------------------------------------------------------------------

struct set_b : //lists::lazy_args_id, t3<lists::details::lambda_t>, 
	scheme::keyword<set_b> { };
template <> char scheme::label <set_b>::text[] = "set!";


// here is also a possible distinction.
namespace lists {

// add 'lambda' to binders
	template<> struct binder<set_b> : public t_true { };

// obtain vars from 'lambda' expression
	template<>
	struct binder_vars<set_b, nat> : node<null, null> { };
	
	template<class TS> 
	struct binder_vars<set_b, TS> : 
		node<typename TS::val, node<null, null> > { };

/*
template<class T1, class T2>
struct run<node<node<lambda, T1>, T2> > : public
	run<typename l_concat<node<lambda, T1>, 
		node<T2, node<null, null> >
		//node<typename lists::run<T2>::type, node<null, null> >
	>::type> { };

template<class T1>
struct run<node<node<lambda, T1>, node<null, null> > > : public
	t_id<node<node<lambda, T1>, node<null, null> > > { };
*/	
} // namespace lists

//-----------------------------------------------------------------------------

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_FUNCTIONS_SET_HPP
