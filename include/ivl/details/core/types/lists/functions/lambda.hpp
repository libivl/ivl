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

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LAMBDA_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LAMBDA_HPP

namespace ivl {

namespace types {

//-----------------------------------------------------------------------------

namespace lists {

namespace details {
	
template<class T1, class T2, class T3>
struct lambda_t
{
	typedef typename lists::details::l_replace<typename lists::
		details::l_dot<typename model<T1>::type, typename eval<T3>::type>::type, 
			typename model<T2>::type>::type replaced_type;

	typedef typename lists::eval<replaced_type>::type type;
};

} // namespace details

} // namespace lists

//-----------------------------------------------------------------------------

struct lambda : lists::lazy_args_id, t3<lists::details::lambda_t>
	{ };
	//, scheme::keyword<lambda> { };
template <> char scheme::label <t3<lists::details::lambda_t> >::text[] = "lambda";
template <> char scheme::label <lambda>::text[] = "lambda";


// here is also a possible distinction.
namespace lists {

// add 'lambda' to binders
template<> struct binder<lambda> : public t_true { };

// obtain vars from 'lambda' expression
// NOTE: case of lambda having 1 variable only: binder should care
template<class T, class TV, class TS> 
struct binder_vars<lambda, node<node<T, TV>, TS> > : node<T, TV> { };
template<class T, class TS> 
struct binder_vars<lambda, node<T, TS> > : node<T, node<null, null> > { };
template<class TS>
struct binder_vars<lambda, TS> : TS::val { }; // unknown case, but try demodel

namespace details {

//-----------------------------------------------------------------------------
		
template<class V, class T, class V0, class T0, class B>
struct l_compare : nat { };

template<class V, class VS, class T, class TS, class V0, class T0, class B>
struct l_compare<node<V, VS>, node<T, TS>, V0, T0, B>
	: l_compare<VS, TS, node<V, V0>, node<T, T0>, B> { };

// equal
template<class V0, class T0, class B>
struct l_compare<node<null, null>, node<null, null>, V0, T0, B> :
	l_concat<node<lambda, node<V0, B> >, 
		node<T0, node<null, null> >
	> { };
	
// less
template<class V, class VS, class V0, class T0, class B>
struct l_compare<node<V, VS>, node<null, null>, V0, T0, B> :
/*
	node<lambda, node<node<V, VS>, node<
		node<node<lambda, node<V0, B> >, T0>, node<null, null> > > > { };
*/
	node<node<lambda, node<V0, node<
		node<lambda, node<node<V, VS>, B> >, node<null, null> > > >, T0> { };


// more
template<class T, class TS, class V0, class T0, class B>
struct l_compare<node<null, null>, node<T, TS>, V0, T0, B> :
	node<
		typename run<typename l_concat<node<lambda, node<V0, B> >, 
		node<T0, node<null, null> >
	>::type>::type, node<T, TS> > { };


} // namespace details

//can be done:
//optionally: convert non-node model<typename T1::val>::type to 
// node<model<typename T1::val>::type, node<null, null> > for 1-var-only
//
template<class T1, class T2>
struct run<node<node<lambda, T1>, T2> > : run<typename details::l_compare<
	typename model<typename T1::val>::type, T2,
		node<null, null>, node<null, null>, typename T1::next>::type> { };

/*
// was:
template<class T1, class T2>
struct run<node<node<lambda, T1>, T2> > : public
	run<typename l_concat<node<lambda, T1>, 
		node<T2, node<null, null> >
		//node<typename lists::run<T2>::type, node<null, null> >
	>::type> { };
*/

template<class T1>
struct run<node<node<lambda, T1>, node<null, null> > > : public
	t_id<node<node<lambda, T1>, node<null, null> > > { };
	
} // namespace lists

//-----------------------------------------------------------------------------

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LAMBDA_HPP
