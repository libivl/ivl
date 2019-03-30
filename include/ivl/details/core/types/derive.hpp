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

#ifndef IVL_CORE_DETAILS_TYPES_DERIVE_HPP
#define IVL_CORE_DETAILS_TYPES_DERIVE_HPP


namespace ivl {

//forward declaration
//template <class T, int N, class S, class K> class image;

namespace data {

//forward declaration
//template <int N> struct normal_image;

// forward declarations
/*
template <class T, template <typename, typename, typename> class A, class Derived>
class data_base;

template <class T, template <typename, typename, typename> class A, class DI>
class data_base_inst;

template <class T, template <typename, typename, typename> class A, class DI>
class iactset;
*/

}// namespace data

namespace types {

// TODO: what about this?
/* These structs allow the compile-time translation from one
 * template type to another. Or otherwise said, they perform
** type promotion for template types */

//-----------------------------------------------------------------------------

template<class T, class I = int>
class static_enable_if : public static_enable_if<typename T::type, I>
{
	public:
	static_enable_if(I x) : static_enable_if<typename T::type, I>(x) {}
};

template<class I>
class static_enable_if<types::t_false, I> 
	: t_id<static_enable_if<types::t_false, I> >
{
	private:
	static_enable_if(I) { }
};

template<class I>
class static_enable_if<types::t_true, I>
	: t_id<static_enable_if<types::t_true, I> >
{
	public:
	static_enable_if(I) { }
};

//-----------------------------------------------------------------------------

// same for bool

template<bool B, class I = int>
class static_enable_if_b : static_enable_if<typename t_expr<B>::type, I>
{
	public:
	static_enable_if_b(I x) : 
		static_enable_if<typename t_expr<B>::type, I>(x) {}
};

//-----------------------------------------------------------------------------

// used to validate that a class is of a certain class type
// has a private constructor if class A != class B which wont allow construction
// of the class that contains that type
template<class A, class B>
class validate_class
{
	private:
	validate_class() { }
};

template<class A>
class validate_class<A, A>
{
	public:
	validate_class() { }
};


// struct that
//typedef <template<typename, typename, typename> class D, class T, class DERIVED_CLASS>


namespace types_details
{




template <class PRIMARY, class DERINFO>
struct derive_logic
{
	typedef DERINFO type;
};

template <class PRIMARY>
struct derive_logic <PRIMARY, term>
{
	typedef PRIMARY type;
};

}// namespace types_details


template <class T>
struct derive_opts { };

template <template <typename, typename> class A, class T, class DS>
struct derive_opts<A<T, DS> >
{
	typedef typename t_if<t_eq<typename DS::derived_param, term>,
		typename DS::template change_derived_param<A<T, DS> >::type, DS>
		::type type;
};

template <class PRIMARY>
struct derive
{
	typedef PRIMARY type;
};

// opts parameter class
template <template <typename, typename> class A,
		  class T, class DS>
struct derive <A <T, DS> >
{
	typedef typename types_details::derive_logic <A <T, DS>,
		typename DS::derived_param>::type type;
};


// -------------------------------------------------------------

template <class DERIVED_CLASS, class X>
struct change_derived_class { };
// spec parameter class
template <class DERIVED_CLASS, template <typename, typename> class A,
	class T, class DS>
struct change_derived_class <DERIVED_CLASS, A <T, DS> >
{
	typedef A <T, typename DS::template
		change_derived_param<DERIVED_CLASS>::type> type;
};

// -------------------------------------------------------------

// returns an array type with the data class changed to DATA.
// X has to be the derived class.
template <class DATA, class X>
struct change_data_class_set
{
	// TODO: fix better, @@@, for high classes e.g. point<DATA>
	typedef typename change_data_class_set<DATA, typename X::derived_type>::type type;
};

namespace types_details {

template <class DATA, class X, class REPL, class IS_TERM>
struct change_data_class_set_tool
{
	// if the class is below the array-hierarchy classes
	// we get the lowest possible ancestor that is.
	//TODO: revise this
	typedef typename change_data_class_set<DATA,
		typename change_derived_class<types::term,
			typename X::container_type>::type>::type type;
};

template <class DATA, class X, class REPL>
struct change_data_class_set_tool<DATA, X, REPL, t_true>
{
	typedef REPL type;
};

} /* namespace types_details */

//
// spec parameter class
template <class DATA, template <typename, typename> class A,
	class T, class DS>
struct change_data_class_set <DATA, A <T, DS> >
{
	typedef typename types_details::
			change_data_class_set_tool<DATA, A<T, DS>, A<T, DATA>,
			typename t_eq<typename DS::derived_param, term>::type>::type
			 type;
};


// -------------------------------------------------------------

template <class ELEM_TYPE, class X>
struct change_elem_type { };

// this is a new approach
template <class E>
struct change_elem_type<E, term>
{
	typedef term type;
};

//
// opts parameter class
template <class ELEM_TYPE, template <typename, typename> class A,
	class T, class DS>
struct change_elem_type <ELEM_TYPE, A <T, DS> >
{
	typedef A <ELEM_TYPE, typename DS::template change_derived_param<
		typename change_elem_type<ELEM_TYPE, typename DS::derived_param>
		::type>::type> type;
};


// -------------------------- TODO : style -------------

template <class A>
struct normal_type
{
	//Note: for now, change_data_class_set also resets the derived_type to
	//types::term. However this could change.
	//An idea is to allow only change data class and change_elem_type to
	//classes that end with term (are derived).
	//However, normal_type will certainly reset the derived_type to term...
	//
	// so for backup reasons I place here the valid implementation of
	// change_data_class_set
	//
	//	// if the class is below the array-hierarchy classes
	//	// we get the lowest possible ancestor that is.
	//	typedef typename change_data_class_set<DATA,
	//		typename change_derived_class<types::term,
	//			typename X::array_type>::type>::type type;
	//
	//
	typedef typename change_data_class_set<data::mem<>, A>::type type;
};

namespace types_details {

template <class DATA, class A, class IS_ARRAY>
struct change_data_class_set_rec_tool { };

template <class DATA, class T>
struct change_data_class_set_rec_tool<DATA, T, t_false>
{
	typedef T type;
};

template <class DATA, class A>
struct change_data_class_set_rec_tool<DATA, A, t_true>
{
	typedef typename change_elem_type<
		typename change_data_class_set_rec_tool<DATA, typename A::elem_type,
			typename is_ivl_array<typename A::elem_type>::type>::type,
		typename change_data_class_set<DATA, A>::type>::type type;
};

} /* namespace types_details */

template <class DATA, class A>
struct change_data_class_set_rec :
	public types_details::
	change_data_class_set_rec_tool<DATA, A, typename is_ivl_array<A>::type>
{
};

} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_DERIVE_HPP
