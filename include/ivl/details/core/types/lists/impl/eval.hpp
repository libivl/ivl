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

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_EVAL_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_EVAL_HPP

namespace ivl {

namespace types {

namespace lists {

//-----------------------------------------------------------------------------

// list evaluation: 

template <class T>
struct run : public t_id<T> { };

template <class T>
struct eval
{
	typedef typename prefnode_2<T>::type to_node;
	typedef typename run<to_node>::type type;
};

template <class T>
struct pre : t_id<T> { };

//-----------------------------------------------------------------------------

namespace details {

template <class LZ, class TT, class T1, class T2>
struct runtpl : public nat { };

// default case if actually for CMD = t_false
// behavior: a list with no command simply evaluates all its sublists, if any.
template<class CMD, class T1, class T2>
struct runcmd : public node<typename eval<T1>::type, 
	typename runcmd<CMD, typename prefnode<typename T2::val>::type, 
						 typename T2::next>::type> { };

// natty cases						 
/*template<class CMD, class T1>
struct runcmd<CMD, T1, nat> : node<nat, node<null, null> > { };
template<class CMD>
struct runcmd<CMD, nat, nat> : node<nat, node<null, null> > { };*/

template<>
struct runcmd<t_false, null, null> : public node<null, null> { };

// lookup command
template<class T1, class T2>
struct runcmd<t_true, T1, T2> : 
	public run<node<typename pre<
		typename model<scheme::define<T1> >::type>::type, T2> > { };
	//public run<node<typename model<typename scheme::define<T1>::node_type >::type, T2> > { };

//template<class T1, class T2>
//struct runcmd<t_true

template<class T1, class T2>
struct runcmd<nat, T1, T2> : public t_id<nat> { };

template<class T1, class T2>
struct runcmd<template_class_id, T1, T2> : 
	runtpl<typename is_base<lazy_args_id, T1>::type, 
			typename T1::template_class_type, T1, T2> { };

//-----------------------------------------------------------------------------

template<class T>
struct cmd_categ1
{
	//typedef t_false type;
	typedef scheme::define<T> def_t;
	typedef typename t_if<is_base<nat, def_t>, t_false, t_true>::type type;
	//typedef typename t_if<t_eq<def_t, null>, t_false, t_true>::type type;
};

template<class T>
struct cmd_categ 
{
	typedef typename t_if<is_base<template_class_id, T>, 
		t_id<template_class_id>, cmd_categ1<T> >::type::type type;
};

template<class T1, class T2>
struct cmd_categ<node<T1, T2> > : public t_false { };

template<>
struct cmd_categ<null> : public t_false { };

template<>
struct cmd_categ<nat> : public nat { };

} // namespace details

//-----------------------------------------------------------------------------

// default run: command
template <class T1, class T2>
struct run<node<T1, T2> > : public details::runcmd<
	typename details::cmd_categ<typename prefnode<T1>::type>::type, T1, T2> 
{ };

	
// run: recursive into nodes
// does a final evaluation after evaluating node<T1, T2> and S, if changed.
template <class T1, class T2, class S>
struct run<node<node<T1, T2>, S> >
{
	//typedef node<typename run<node<T1, T2> >::type,
	//	typename run<S>::type> type;

	typedef typename prefnode<T1>::type t1_t;
	typedef typename run<node<t1_t, T2> >::type ri_t;
	typedef typename t_if<t_eq<ri_t, node<t1_t, T2> >,
		details::runcmd<t_false, node<t1_t, T2>, S>,
		eval<node<ri_t, S> > >::type::type type;
   //::last eval=>run?

/*
	typedef typename runin<node<T1, T2> >::type ri_t;
//	typedef typename t_if<t_eq<node<T1, T2>, ri_t>, 
//		node<node<T1, T2>, S>, run<node<ri_t, S> > >
//		::type::type type;
	typedef node<ri_t, S> type;
*/
};

template <>
struct run<node<null, null> > : public node<null, null> { };

// disability of syntax_rules in main run
/*template<class S>
struct run<node<syntax_rules, S> > : nat { };

template<class D, class S>
struct run<node<node<syntax_rules, D>, S> > : nat { };
*/
//-----------------------------------------------------------------------------

namespace details {

template <class L>
struct test_size : public nat { };

template <>
struct test_size<node<null, null> > : public number<0> { };

template <class T1, class T2>
struct test_size<node<T1, T2> > : public t_add<number<1>, 
	typename test_size<T2>::type> { };

//-----------------------------------------------------------------------------

// run template class functions

template <class DER, class T1, class T2>
struct runtpl<t_false, template_class<0, DER>, T1, T2> 
{
	typedef typename map<eval, T2>::type l1;
	typedef typename DER::template map<l1>::type type;
};

template <class DER, class T1, class T2>
struct runtpl<t_true, template_class<0, DER>, T1, T2> 
{
	typedef typename DER::template map<T2>::type type;
};

template <class LZ, class F, class T2>
struct runtplc : public nat { };

template <class LZ, int N, class DER, class T1, class T2>
struct runtpl<LZ, template_class<N, DER>, T1, T2> 
	: public t_if<t_le<number<N>, typename test_size<T2>::type>,
		runtplc<LZ, template_class<N, DER>, T2>,
		t_id<node<T1, T2> > >::type { };
	
//-----------------------------------------------------------------------------

template <class DER, class T2>
struct runtplc<t_true, template_class<1, DER>, T2> 
{
	typedef typename T2::val j1;
	typedef typename DER::template map<j1>::type type;
};

template <class DER, class T2>
struct runtplc<t_false, template_class<1, DER>, T2> 
{
	typedef typename eval<typename T2::val>::type j1;
	typedef typename DER::template map<j1>::type type;
};

template <class DER, class T2>
struct runtplc<t_true, template_class<2, DER>, T2> 
{
	typedef typename T2::val j1;
	typedef typename T2::next::val j2;
	typedef typename DER::template map<j1, j2>::type type;
};

template <class DER, class T2>
struct runtplc<t_false, template_class<2, DER>, T2> 
{
	typedef typename eval<typename T2::val>::type j1;
	typedef typename eval<typename T2::next::val>::type j2;
	typedef typename DER::template map<j1, j2>::type type;
};

template <class DER, class T2>
struct runtplc<t_true, template_class<3, DER>, T2> 
{
	typedef typename T2::val j1;
	typedef typename T2::next::val j2;
	typedef typename T2::next::next::val j3;
	typedef typename DER::template map<j1, j2, j3>::type type;
};

template <class DER, class T2>
struct runtplc<t_false, template_class<3, DER>, T2> 
{
	typedef typename eval<typename T2::val>::type j1;
	typedef typename eval<typename T2::next::val>::type j2;
	typedef typename eval<typename T2::next::next::val>::type j3;
	typedef typename DER::template map<j1, j2, j3>::type type;
};

//-----------------------------------------------------------------------------

} // namespace details

} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_EVAL_HPP
