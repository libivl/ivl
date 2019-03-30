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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_LETREC_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_LETREC_HPP

namespace ivl {

namespace types {

// letrec
struct letrec;

//-----------------------------------------------------------------------------

namespace lists {
namespace details {

template<class T1, class T2, class T3>
struct letrec_t
{	
	typedef typename model<T1>::type t1_t;
	typedef typename model<T2>::type t2_t;
	typedef typename eval<T3>::type t3_t;

	typedef typename lists::details::l_replace<
		node<node<t1_t, 
			node<node<letrec, node<t1_t, node<t2_t, node<null, null> > > >, 
				node<null, null> >
			>, node<null, null> >,		
		node<t2_t, t3_t> >::type replaced_type; 
		// Note: TODO: is node<T2, T3> assumptions safe enough? should be concat?
	typedef typename lists::eval<replaced_type>::type type;
};

} // namespace details
} // namespace lists

struct letrec : lists::lazy_args_id, t3<lists::details::letrec_t> { };

//-----------------------------------------------------------------------------

// here is also a possible distinction.
namespace lists {

// add 'letrec' to binders
template<> struct binder<letrec> : public t_true { };

// obtain vars from 'letrec' expression
template<class TS> 
struct binder_vars<letrec, TS> 
	: public node<typename TS::val, node<null, null> > { };

template<class T1, class T2>
struct run<node<node<letrec, T1>, T2> > : public
	run<typename l_concat<node<letrec, T1>,
		node<T2, node<null, null> >
		//node<typename lists::run<T2>::type, node<null, null> >
	>::type> { };

template<class T1>
struct run<node<node<letrec, T1>, node<null, null> > > : public
	t_id<node<node<letrec, T1>, node<null, null> > > { };

} // namespace lists

//-----------------------------------------------------------------------------

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LIST_LETREC_HPP
