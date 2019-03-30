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

/*! \file binary_element_functions.hpp
    \brief Binary element-wise functions for arrays

    Binary functions that apply on array elements like this:
	a[i] = func(b[i], c[i]);
	a[i] = func(b[i], s);
	a[i] = func(s, b[i]);
*/

#ifndef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP
#define IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP

// Macros are be used only because this file is full of repeated definitions.
// they are undefined after the definitions are made. Therefore they are
// temporary and they do not affect the developpers code who include ivl.
#ifdef BD
#define IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BD BD
#undef BD
#endif
#ifdef BO
#define IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO BO
#undef BO
#endif
#ifdef BO_AR
#define IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_AR BO_AR
#undef BO_AR
#endif
#ifdef BO_LAR
#define IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_LAR BO_LAR
#undef BO_LAR
#endif
#ifdef BMAX
#define IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BMAX BMAX
#undef BMAX
#endif

namespace ivl {

/**
 * \defgroup BinElemFunc Binary element-wise functions for array-based structures
 * This group defines element-wise binary functions. The input of each function
 * can be either an array-based structures or a scalar.
@{*/

#define BD(rtype, name, costval) \
 \
template<class T, class J, class K> \
struct name ## _class \
{ \
	typedef types::number<costval> cost; \
	typedef typename types::t_if<types::t_eq<rtype, types::term>, \
		J, rtype>::type default_ret_type; \
	typedef typename types::t_if<types::t_eq<T, types::term>, \
		default_ret_type, T>::type func_ret_type; \
	static inline func_ret_type elem_op(const J& elem1, const K& elem2) \
	{ \
		return math::name(elem1, elem2); \
	} \
}; \
\
template <class A1, class A2> \
inline \
typename binary_elem_func_result< \
	typename name ## _class< \
		types::term, \
		typename types::get_value<A1>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, A1, A2>::type name ( \
	const A1& a1, const A2& a2) \
{ \
	return binary_elem_func_result< \
	typename name ## _class< \
		types::term, \
		typename types::get_value<A1>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, A1, A2>::from(a1, a2); \
} \

#define BO(oper, name) \
 \
template <class A1, class A2> \
inline \
typename binary_elem_func_result< \
	typename name ## _class< \
		types::term, \
		typename types::get_value<A1>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, A1, A2>::type operator oper ( \
	const A1& a1, const A2& a2) \
{ \
	return binary_elem_func_result< \
		typename name ## _class< \
		types::term, \
		typename types::get_value<A1>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, A1, A2>::from(a1, a2); \
} \

#define BO_AR(oper, name) \
 \
template <class T, class S, class A2> \
inline \
typename binary_elem_func_result< \
	typename name ## _class< \
		types::term, \
		typename types::get_value<T>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, array_base<T, S>, A2>::type operator oper ( \
	const array_base<T, S>& a1, const A2& a2) \
{ \
	return binary_elem_func_result< \
		typename name ## _class< \
		types::term, \
		typename types::get_value<T>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, array_base<T, S>, A2>::from(a1, a2); \
} \
\
template <class A1, class T, class S> \
inline \
typename binary_elem_func_result< \
	typename name ## _class< \
		types::term, \
		typename types::get_value<A1>::type, \
		typename types::get_value<T>::type>::default_ret_type, \
		name ## _class, A1, array_base<T, S> >::type operator oper ( \
	const A1& a1, const array_base<T, S, \
		types::t_not<types::is_ivl_array<A1> >::value >& a2) \
{ \
	return binary_elem_func_result< \
		typename name ## _class< \
		types::term, \
		typename types::get_value<A1>::type, \
		typename types::get_value<T>::type>::default_ret_type, \
		name ## _class, A1, array_base<T, S> >::from(a1, a2); \
}




#define BO_LAR(oper, name) \
 \
template <class T, class S, class A2> \
inline \
typename binary_elem_func_result< \
	typename name ## _class< \
		types::term, \
		typename types::get_value<T>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, array<T, S>, A2>::type operator oper ( \
	const array<T, S>& a1, const A2& a2) \
{ \
	return binary_elem_func_result< \
		typename name ## _class< \
		types::term, \
		typename types::get_value<T>::type, \
		typename types::get_value<A2>::type>::default_ret_type, \
		name ## _class, array<T, S>, A2>::from(a1, a2); \
}

#define BMAX typename types::maps::max<J, K>::type

// definitions for elem functions:
// BD(return type, math::function name)
// for the return type you can use the types
// J, K: first, second element type accordingly

// trigonometric
BD(BMAX, atan2, 150)

// functions
BD(BMAX, mod, 50);

// functions that correspond to operators
BD(BMAX, rem, 50);
BO_AR(%, rem);
BD(BMAX, power, 150);
BO_AR(^, power);

BD(BMAX, plus, 7);
//BO_AR(+, plus);
BD(BMAX, minus, 7);
//BO_AR(-, minus);

//----------------------

BD(BMAX, times, 12);



//----------------------
BO_AR(*, times);
//----------------------


//BD(K, rdivide, 40);
//BO_AR(/, rdivide);
BD(BMAX, rdivide, 40);
BO_AR(/, rdivide);

// rel operators
BD(bool, lt, 7);
BO_AR(<, lt);
BD(bool, le, 7);
BO_AR(<=, le);
BD(bool, gt, 7);
BO_AR(>, gt);
BD(bool, ge, 7);
BO_AR(>=, ge);
BD(bool, eq, 7);
BO_AR(==, eq);
BD(bool, ne, 7);
BO_AR(!=, ne);

// logical operators
BD(bool, logical_and, 7)
BO_AR(&&, logical_and)
BD(bool, logical_or, 7)
BO_AR(||, logical_or)

// bit operators
//todo:write as methods
BD(BMAX, cbitor, 7)
//BO_AR(|, cbitor)
BD(BMAX, cbitand, 7)
BO_AR(&, cbitand)
BD(J, bitlshift, 12)
// BO_LAR(<<, bitlshift)
BO_AR(<<, bitlshift)  // iavr: enable shift of scalar + vector, or vector + scalar
BD(J, bitrshift, 12)
BO_LAR(>>, bitrshift)
// BO_AR(>>, bitrshift)  // iavr: enable shift of scalar + vector, or vector + scalar


/*
template <class T, class S, class K, class A2>
inline
typename binary_elem_func_result<
	typename plus_class<
		types::term,
		typename types::get_value<T>::type,
		typename types::get_value<A2>::type>::default_ret_type,
		plus_class, array_base<T, S, K>, A2>::type operator + (
	const array_base<T, S, K>& a1, const A2& a2)
{
	return binary_elem_func_result<
		typename plus_class<
		types::term,
		typename types::get_value<T>::type,
		typename types::get_value<A2>::type>::default_ret_type,
		plus_class, array_base<T, S, K>, A2>::from(a1, a2);
}

template <class A1, class T, class S, class K>
inline
typename binary_elem_func_result<
	typename plus_class<
		types::term,
		typename types::get_value<A1>::type,
		typename types::get_value<T>::type>::default_ret_type,
		plus_class, A1, array_base<T, S, K> >::type operator + (
	const A1& a1, const array_base<T, S, K,
		types::t_not<types::is_ivl_array<A1> >::value >& a2)
{
	return binary_elem_func_result<
		typename plus_class<
		types::term,
		typename types::get_value<A1>::type,
		typename types::get_value<T>::type>::default_ret_type,
		plus_class, A1, array_base<T, S, K> >::from(a1, a2);
}
*/



} /* namespace ivl */

#undef BD
#undef BO
#undef BO_AR
#undef BO_LAR
#undef BMAX

#ifdef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BD
#define BD IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BD
#undef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BD
#endif
#ifdef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO
#define BO IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO
#undef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO
#endif
#ifdef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_AR
#define BO_AR IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_AR
#undef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_AR
#endif
#ifdef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_LAR
#define BO_LAR IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_LAR
#undef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BO_LAR
#endif
#ifdef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BMAX
#define BMAX IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BMAX
#undef IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP_SAVE_BMAX
#endif

#endif // IVL_ARRAY_DETAILS_BINARY_ELEMENT_FUNCTIONS_HPP
