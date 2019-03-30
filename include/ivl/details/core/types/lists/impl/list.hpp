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

/* impl/list.hpp: The definition of the basic list and node classes */

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_HPP

namespace ivl {

namespace types {

//-----------------------------------------------------------------------------

// dependency forward declarations

namespace lists {

namespace details {

template<int J, class N> struct get_node_index { };

} // namespace details

// identifier struct that all lists inherit
struct listie_id { };

} // namespace lists

//-----------------------------------------------------------------------------

// list primitives

// node is the primitive used to create a list.
template<class T1, class T2>
struct node
{
	typedef T1 val;
	typedef T2 next;
	typedef node type;
	typedef node node_type;

	// get argument J of a list, starting with index 1.
	template<int J>
	struct val_t : 
		public lists::details::get_node_index<J, node<T1, T2> > { }; 
};

struct nat { typedef nat type; };

struct null { };

typedef node<null, null> null_node;

//-----------------------------------------------------------------------------

namespace lists {

template <class T, int K = 0>
struct var : t_id <var <T, K> > { };

} // namespace lists

namespace scheme {

struct word_id { };

struct label_id : word_id { };

struct identifier_id { };

template<class T>
struct define_syntax : nat { };

template<class T>
struct define : define_syntax<T> { };

template<class T>
struct label : public label_id { static char text[]; typedef label<T> word; };

template <typename T>
struct keyword : word_id { typedef keyword<T> word; };

template <typename T>
struct identifier : identifier_id, label <T> { };

} // namespace scheme

//-----------------------------------------------------------------------------

// evaluation primitive structs: eval, convertion to node, auto-eval

namespace lists {

// evaluates a list
template<class L>
struct eval;

// converts all lists to node<..> recursively
template <class L>
struct model;

// converts all lists to node<..> recursively while preserving keywords
template <class L>
struct disp;

namespace details {

template <class L>
struct to_node : public L::node_type { };

} // namespace details

// converts one list to node<..>
template<class L>
struct reqnode : 
	t_if<is_base<listie_id, L>, details::to_node<L>, nat>::type { };

// helper structs to change output properites of a list
template<class L> struct listie_script { };
template<class L> struct listie_disp { };

// base class of a list, that stores the evaluation result in itself.
template<class L>
struct listie : public reqnode<L>::type, public listie_id
{
	typedef typename eval<L>::type type;
	
	typedef lists::model<L> model;
	typedef listie<L> listie_type;
	typedef listie_script<L> script;
	typedef listie_disp<L> disp;
	
};

template<class L> struct reqnode<listie<L> > : public reqnode<L> { };

// Note: The following types are less commonly used by the end-user of the
// lists, however they are required by the programmer who wants to be
// able to have the full features on adding custom primitives.

// struct that needs to be inherited by a primitive to disable 
// automatic argument evaluation
struct lazy_args_id { };

// returns true if the primitive T belongs to binders
template <class T>
struct binder : public t_false { };

// returns the list of variables bound by binder T in expression node<T, TS>
template <class T, class TS>
struct binder_vars : public nat { };

} // namespace lists

//-----------------------------------------------------------------------------

// declaration of list and _

template<
	class T1 = null, class T2 = null, class T3 = null, class T4 = null,
	class T5 = null, class T6 = null, class T7 = null, class T8 = null,
	class T9 = null, class T10 = null, class T11 = null, class T12 = null,
	class T13 = null, class T14 = null, class T15 = null, class T16 = null,
	class T17 = null, class T18 = null, class T19 = null, class T20 = null,
	class T21 = null, class T22 = null, class T23 = null, class T24 = null
>
struct list : public lists::listie<list<
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> >
{
};

template<
	class T1 = null, class T2 = null, class T3 = null, class T4 = null,
	class T5 = null, class T6 = null, class T7 = null, class T8 = null,
	class T9 = null, class T10 = null, class T11 = null, class T12 = null,
	class T13 = null, class T14 = null, class T15 = null, class T16 = null,
	class T17 = null, class T18 = null, class T19 = null, class T20 = null,
	class T21 = null, class T22 = null, class T23 = null, class T24 = null
>
struct _ : public list<
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
>
{
};

namespace lists {

template<
	class T1, class T2, class T3, class T4, 
	class T5, class T6, class T7, class T8,
	class T9, class T10, class T11, class T12,
	class T13, class T14, class T15, class T16,
	class T17, class T18, class T19, class T20,
	class T21, class T22, class T23, class T24
>
struct reqnode<list<
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> > : public node<T1, typename reqnode<list<
	     T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> >::type> { }; 
	
template<>
struct reqnode<list<> > : public node<null, null> { };

template<
	class T1, class T2, class T3, class T4, 
	class T5, class T6, class T7, class T8,
	class T9, class T10, class T11, class T12,
	class T13, class T14, class T15, class T16,
	class T17, class T18, class T19, class T20,
	class T21, class T22, class T23, class T24
>
struct reqnode<_<
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> > : public reqnode<list<
	T1,  T2,  T3,  T4,  T5,  T6,  T7,  T8,  T9,  T10, T11, T12,
	T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, T23, T24
> > { }; 

} // namespace lists

//-----------------------------------------------------------------------------

namespace scheme {

template <class L, class A>
struct alias : L, A 
{ 
	typedef A disp; 
	typedef lists::listie_script<alias<L, A> > script;
};

} // namespace scheme

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_HPP
