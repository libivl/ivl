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

/*! \file unary_element_functions.hpp
    \brief Unary element-wise functions for arrays

    Unary functions that apply on array elements like this:
	a[i] = func(b[i]);
*/

#ifndef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP
#define IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP

// Macros are be used only because this file is full of repeated definitions.
// they are undefined after the definitions are made. Therefore they are
// temporary and they do not affect the developpers code who include ivl.
#ifdef UD
#define IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD UD
#undef UD
#endif
#ifdef UD_AR
#define IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD_AR UD_AR
#undef UD_AR
#endif
#ifdef UO
#define IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO UO
#undef UO
#endif
#ifdef UO_AR
#define IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO_AR UO_AR
#undef UO_AR
#endif

namespace ivl {

/**
 * \defgroup UnElemFunc Unary element-wise functions for array-based structures
 * This group defines unary functions that apply to each element of an
 * array-based structure.
@{*/

namespace array_details {

template <class T, class J, class T_IS_IVL_ARRAY>
struct cast_class_details { };

// allows cast to create arrays with 1 element instead of elements.
// this may be helpful for changing the structure type of some arrays
template <class T, class J>
struct cast_class_details<T, J, types::t_true>
{
	typedef types::number<12> cost;
	static inline T elem_op(const J& elem1)
	{
		return T(1, math::cast<typename T::elem_type>(elem1));
	}
};

template <class T, class J>
struct cast_class_details<T, J, types::t_false>
{
	typedef types::number<2> cost;
	static inline T elem_op(const J& elem1)
	{
		return math::cast<T>(elem1);
	}
};

} /* namespace array_details */

template<class T, class J>
struct cast_class
: public array_details::cast_class_details<T, J, typename
	types::is_ivl_array<T>::type>
{
};

template<class R, class A>
inline
typename unary_elem_func_result<
	typename types::change_data_class_set_rec<data::fixed<1>, R>::type,
		cast_class, A>::type cast(const A& in)
{
	return unary_elem_func_result<
		typename types::change_data_class_set_rec<data::fixed<1>, R>::type,
			cast_class, A>::from(in);
}


/*
template<class T, class S>
struct cast_class
{
	static inline T elem_op(const S& elem) { return cast<T>(elem); };
};

//! Cast each element to type R
template<class R, class T, class S, class K>
inline
elem_func_unary<R, cast_class, array<T, S, K> > cast(const array<T, S, K>& a)
{
	return elem_func_unary<R, cast_class, array<T, S, K> >(a);
};
*/


#define UD(rtype, name, costval) \
 \
template<class T, class J> \
struct name ## _unary_class \
{ \
	typedef types::number<costval> cost; \
	typedef typename types::t_if<types::t_eq<rtype, types::term>, \
		J, rtype>::type default_ret_type; \
	typedef typename types::t_if<types::t_eq<T, types::term>, \
		default_ret_type, T>::type func_ret_type; \
	static inline func_ret_type elem_op(const J& elem1) \
	{ \
		return math::name(elem1); \
	} \
}; \
\
template<class A>										\
inline													\
typename unary_elem_func_result<						\
	typename name ## _unary_class< \
		types::term, typename types::get_value<A>::type>\
		::default_ret_type,	\
		name ## _unary_class, A>::type name(			\
			const A& in)								\
{														\
	return unary_elem_func_result<						\
	typename name ## _unary_class< \
		types::term, typename types::get_value<A>::type>\
		::default_ret_type,	\
		name ## _unary_class, A>::from(in); \
}


#define UD_AR(rtype, name, costval) \
 \
template<class T, class J> \
struct name ## _unary_class \
{ \
	typedef types::number<costval> cost; \
	typedef typename types::t_if<types::t_eq<rtype, types::term>, \
		J, rtype>::type default_ret_type; \
	typedef typename types::t_if<types::t_eq<T, types::term>, \
		default_ret_type, T>::type func_ret_type; \
	static inline func_ret_type elem_op(const J& elem1) \
	{ \
		return math::name(elem1); \
	} \
}; \
\
template<class A>										\
inline													\
typename unary_elem_func_result<						\
	typename name ## _unary_class< \
		types::term, typename types::get_value<A>::type>\
		::default_ret_type,	\
		name ## _unary_class, A>::type name(			\
			const array_common_base<A>& in)				\
{														\
	return unary_elem_func_result<						\
	typename name ## _unary_class< \
		types::term, typename types::get_value<A>::type>\
		::default_ret_type,	\
		name ## _unary_class, A>::from(in.to_current());\
}


#define UO(oper, name) \
 \
template <class A> \
inline \
typename unary_elem_func_result< \
	typename name ## _unary_class< \
		types::term, typename types::get_value<A>::type>\
		::default_ret_type,	\
		name ## _unary_class, A>::type operator oper ( \
			const A& in) \
{ \
	return unary_elem_func_result< \
	typename name ## _unary_class< \
		types::term, typename types::get_value<A>::type>\
		::default_ret_type,	\
		name ## _unary_class, A>::from(in); \
} \

#define UO_AR(oper, name) \
 \
template <class T, class S, class K> \
inline \
typename unary_elem_func_result< \
	typename name ## _unary_class< \
		types::term, T>\
		::default_ret_type,	\
		name ## _unary_class, array<T, S, K> >::type \
			operator oper ( \
				const ivl::array<T, S, K>& in) \
{ \
	return unary_elem_func_result< \
	typename name ## _unary_class< \
		types::term, T>\
		::default_ret_type,	\
		name ## _unary_class, array<T, S, K> >::from(in);\
} \


// definitions for unary elem functions:

UD(J, uminus, 7)
UD(J, uplus, 1)
UD(J, bitcmp, 7)
UD(bool, cnot, 7)

// dereference operator, only for arrays (not for other types)
UD(typename types::deref_ptr<J>::type, dereference, 7)


// trigonometric
UD(J, cos, 150)
UD(J, sin, 150)
UD(J, tan, 150)
UD(J, cosh, 150)
UD(J, sinh, 150)
UD(J, tanh, 150)
UD(J, acos, 150)
UD(J, asin, 150)
UD(J, atan, 150)
UD(J, acosh, 150)
UD(J, asinh, 150)
UD(J, atanh, 150)
UD(J, cot, 150)
UD(J, csc, 150)
UD(J, sec, 150)
UD(J, coth, 150)
UD(J, csch, 150)
UD(J, sech, 150)
UD(J, acot, 150)
UD(J, acsc, 150)
UD(J, asec, 150)
UD(J, acoth, 150)
UD(J, acsch, 150)
UD(J, asech, 150)

// unary functions
UD(int, is_inf, 12)
UD(int, is_nan, 12)
UD(J, sign, 12)

UD(J, abs, 30)
UD(J, sqrt, 120)
UD(J, exp, 120)
UD(J, floor, 40)
UD(J, ceil, 40)
UD(J, round, 40)
UD(J, conj, 40)
UD(J, sqr, 40)

UD(typename types::to_real<J>::type, angle, 150)

UD(J, fix, 150)
UD(J, log, 150)
UD(J, log2, 150)
UD(J, log10, 150)
UD(J, ln, 150)
UD(J, nextpow2, 150)


} // namespace ivl

#undef UD
#undef UD_AR
#undef UO
#undef UO_AR

#ifdef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD_AR
#define UD_AR IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD_AR
#undef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD_AR
#endif
#ifdef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD
#define UD IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD
#undef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UD
#endif
#ifdef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO
#define UO IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO
#undef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO
#endif
#ifdef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO_AR
#define UO_AR IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO_AR
#undef IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP_SAVE_UO_AR
#endif

#endif // IVL_ARRAY_DETAILS_UNARY_ELEMENT_FUNCTIONS_HPP
