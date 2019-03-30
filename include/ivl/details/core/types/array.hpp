/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License 
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms 
   of the GNU General Public License version 2 as published by the Free 
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License 
   and a copy of the GNU Lesser General Public License along 
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_CORE_DETAILS_TYPES_ARRAY_HPP
#define IVL_CORE_DETAILS_TYPES_ARRAY_HPP

namespace ivl {

namespace types {



namespace types_details
{
/*
template <class F> struct base_class {};
// 3 parameter template
template <template<typename, typename, typename> class CC> struct class_container
{
	template <class A, class B, class C>
	struct instance
	{
		typedef CC <A, B, C> type;
	};
};
*/

} /* namespace types_details */



namespace types_details
{

template <class A, class B>
struct is_hierarchy_base_eq_tool
: public is_hierarchy_base_eq_tool <A, typename B::base_class> { };

template <class A>
struct is_hierarchy_base_eq_tool<A, A> : public t_true { };

template <class X, class Y>
struct is_hierarchy_base_eq_tool<ivl::array<X, Y>, ivl::array<X, Y> >
: public t_true { };

// Note: used to be X, P, Q, however this restriction was relaxed since
// we are going to allow 'affairs' between different data-type arrays.
template <class X, class Y, class J, class P>
struct is_hierarchy_base_eq_tool<ivl::array<X, Y>, ivl::array<J, P> >
: public t_true { };

template <class A, class X, class Y>
struct is_hierarchy_base_eq_tool<A, ivl::array<X, Y> >
: public t_false { };

} /* namespace types_details */

// A and B must be ivl arrays. returns A base or equal to B in the ivl
// hierarchy tree, only in the matter of the array type (array, array_nd ...).
template <class A, class B>
struct is_hierarchy_base_eq
: public types_details::is_hierarchy_base_eq_tool<
	typename change_data_class_set<data::mem<>, A>::type,
	typename change_data_class_set<data::mem<>, B>::type> { };

// A and B must be ivl arrays. returns A is equal to B in the ivl
// hierarchy tree, only in the matter of the array type (array != array_nd ...).
// another name could be is_same_level
template <class A, class B>
struct is_hierarchy_eq
: public t_and<is_hierarchy_base_eq<A, B>, is_hierarchy_base_eq<B, A> > { };


template <class A, class B>
struct highest_common;

namespace types_details {

template <class A, class B, class A_ISBASEOF_B, class B_ISBASEOF_A>
struct hc {};

template <class A, class B>
struct hc<A, B, t_true, t_true>
{
	typedef A type_a;
	typedef B type_b;
};

template <class A, class B>
struct hc<A, B, t_false, t_true> :
	public highest_common<typename A::base_class, B> {};

template <class A, class B>
struct hc<A, B, t_true, t_false> :
	public highest_common<A, typename B::base_class> {};

template <class A, class B>
struct hc<A, B, t_false, t_false> :
	public highest_common<A, typename B::base_class> {};

} /* namespace types_details */


//! Given two ivl array classes this struct finds the maximum derived class
//! that is in the hierarchy tree of both classes.
template <class A, class B>
struct highest_common :
public types_details::hc<A, B,
	typename is_hierarchy_base_eq<A, B>::type,
	typename is_hierarchy_base_eq<B, A>::type>
{
	typedef typename highest_common::type_a type_a;
	typedef typename highest_common::type_b type_b;
};
/* todo:wipe
//! Given two ivl array classes this struct finds the maximum derived class
//! that is in the hierarchy tree of both classes ignoring completely the
//! data type template argument of the class and checking only the template
//! class itself.
//! It returns that class in two types. One is the type that is in the
//! hierarchy tree of class A and one type that is in the tree of class B.
//! It also returns one type of a class with normal data type.
template <class A, class B>
struct highest_common_template
{
	typedef typename highest_common<
		typename change_data_class_set<data::normal, A>::type,
		typename change_data_class_set<data::normal, B>::type>
		::type type_normal;

	typedef typename change_data_class_set<
		typename A::data_type, type_normal>::type type_a;


	typedef typename change_data_class_set<
		typename B::data_type, type_normal>::type type_b;


};
*/




namespace types_details {

template <class A, class B, class A_IS_ARRAY, class B_IS_ARRAY>
struct is_kind_base_eq_tool { };

template <class A, class B>
struct is_kind_base_eq_tool <A, B, t_true, t_true>
: public is_hierarchy_base_eq<A, B>
{
	typedef is_kind_base_eq_tool<
		typename get_value<A>::type, typename get_value<B>::type,
		typename is_ivl_array<typename get_value<A>::type>::type,
		typename is_ivl_array<typename get_value<B>::type>::type> rec;

	typedef typename t_and<is_hierarchy_base_eq<A, B>,
		typename rec::base_eq_recurse>::type base_eq_recurse;

	typedef typename t_and<is_hierarchy_eq<A, B>,
		typename rec::eq_recurse>::type eq_recurse;
};

// and the big question is: should this yield true? B element is convertible
// to array A with 1 element! Making it true would also not affect equality.
template <class A, class B>
struct is_kind_base_eq_tool <A, B, t_true, t_false>
: public t_false
{
	typedef t_false base_eq_recurse;
	typedef t_false eq_recurse;
};

template <class A, class B>
struct is_kind_base_eq_tool <A, B, t_false, t_true>
: public t_false
{
	typedef t_false base_eq_recurse;
	typedef t_false eq_recurse;
};

// TODO: actually should be only true if B is convertible to A.
// which is kind of possible to detect.
// However the 'any type by any type' array data relaxation is decided to be
// the rule for the situations that is_kind_base_eq_tool will be needed.
// for the same reason, is_kind_eq will not check at all for data type equality.
template <class A, class B>
struct is_kind_base_eq_tool <A, B, t_false, t_false>
: public t_true
{
	typedef t_true base_eq_recurse;
	typedef t_true eq_recurse;
};

} /* namespace types_details */

template <class A, class B>
struct is_kind_base_eq
: public types_details::is_kind_base_eq_tool<A, B,
	typename is_ivl_array<A>::type, typename is_ivl_array<B>::type>::type { };

template <class A, class B>
struct is_kind_eq
: public t_and<is_kind_base_eq<A, B>, is_kind_base_eq<B, A> > { };

// Need some decent naming here:
// The struct below does the following: Checks if a class A is base or equal
// of class B, only in hierarchy terms, e.g. array <= array_nd, but also
// looking at the data type. e.g. array<array> <= array<array_nd>
// and array<array> <= array_nd<array>. etc.
template <class A, class B>
struct is_kind_base_eq_recurse
: public types_details::is_kind_base_eq_tool<A, B,
	typename is_ivl_array<A>::type, typename is_ivl_array<B>::type>
	::base_eq_recurse { };

template <class A, class B>
struct is_kind_eq_recurse
: public types_details::is_kind_base_eq_tool<A, B,
	typename is_ivl_array<A>::type, typename is_ivl_array<B>::type>
	::eq_recurse { };

//-----------------------------------------------------------------------------

template <class J>
struct single_element : public internal::reference_face<J> { };

//-----------------------------------------------------------------------------

template <class T>
struct get_base_class : t_id<typename T::base_class> { };

//-----------------------------------------------------------------------------

} /* namespace types */

} /* namespace ivl */


#endif // CORE_DETAILS_TYPES_ARRAY_HPP
