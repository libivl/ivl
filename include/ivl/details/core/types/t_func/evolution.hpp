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

#ifndef IVL_CORE_DETAILS_TYPES_EVOLUTION_HPP
#define IVL_CORE_DETAILS_TYPES_EVOLUTION_HPP

namespace ivl {
namespace types {


/* These structs allow the compile-time translation from one
 * template type to another. Or otherwise said, they perform
** type promotion for template types */

//--------------------------------------------------------------

// -------------------------- TODO : style -------------

//--------------------------------------------------------------


/** \brief changes the element type of an array
 *
 * Changes the element type of a given array type, providing the Derived
 * (the second) template argument of the array.
 * It is used in functions where the array-type varies and is given
 * as a template argument (e.g. can be array_nd, array_2d or array).
 * This struct will preserve the array type while it will change the
 * type of the elements.
 *
**/
template <class KEY, class FROM = bool> struct to_type
{
	typedef KEY type;
};

template <class KEY>
struct to_type<KEY, term>
{
	typedef term type;
};

template <class KEY, template<typename> class D, class T>
struct to_type<KEY, D<T> >
{
	typedef D<KEY> type;
};

// spec param class
// todo: make a is_ivl_array check to further specialize
template <class KEY, template<typename, typename> class D, class T, class DS>
struct to_type<KEY, D<T, DS> >
{
	typedef D<KEY, typename DS::template change_derived_param<
		typename to_type<KEY, typename DS::derived_param>::type>::type> type;
};

// note: to_type should only be used for creating new types, which will have 'term' as DERINFO
// any other intermediate types would be illegal, since directly casting one class from one type
// to another type of elements is an unsupported practice.
// A reinterpret cast should take care to not only cast the D<T, ..> to D<KEY, ..> but also
// D<T, A, DERINFO> type; to D<T, A, typename to_type<KEY, DERINFO>::type > type;

//--------------------------------------------------------------


template <class X> struct to_bool : public to_type<bool, X> {};

/** \brief promote is used to promote T to a larger type
 *
 * This class is used to promote small integers to larger type integers
 * and leaves all floating point types as they are.
 * It is used to store the result of functions such as sum
 *
 * A few details about this type. (Kimon)
 * It is a hard decision to conclude on the promotions
 * that will be made to each type. And this is because
 * the need for promotion depends on the actual function that
 * uses the promotion.
 * Using a one-type-up promotion like in boost would be inadequate
 * for most operations. For example summing up an array of 8-bit chars
 * could easily produce a value larger than a 16-bit short, if we
 * sum up more than 256 array elements. On the other hand, promoting
 * to 64-bit long longs could seriously reduce performance if 64-bit
 * operations are not supported by the compiler or host processor.
 * So the following decision is made for the moment. The existing
 * implementation of ivl I consider it to be a 32-bit library at its
 * basis. If anyone would want numbers up to 64-bit high to perform
 * an operation such as summing, they should have to write their
 * own specialization of this function. This logic has some sense
 * considering that 32-bit numbers usually cover the default image
 * processing needs.
 * *However* 32-bit ints are not explicitly stated in this promotion.
 * The compiler-defined 'long' type is used instead. This is one more
 * decision. The logic is the following. As for now (2009) Gcc and Visual
 * Studio in 32-bit mode, where we work, treat long as a 32-bit integer.
 * Any less than that wouldn't be implemeted by any new compiler.
 * In the case that a compiler treats long as a larger type, e.g. 64-bit,
 * would mean that 64-bit operations are totaly supported and therefore,
 * such a promotion would be benefit. So I leave the decision for the
 * promotion on the compiler.
 *
 * The promotions are defined in the file
 * ./platform_specific/promote_int_impl.hpp
 *
 * so that any platform-specific treatment is made with #ifdef to
 * make sure that all supported compilers work well with the defined
 * specializations.
***/
template <class T> struct promote : public
	t_if<is_ivl_array<T>,
		to_type<typename promote<typename subtype<T>::type>::type, T>,
		to_type<T> >::type { };

template<> struct promote<term> { typedef bool type; };

#include "platform_specific/promote_int_impl.hpp"

template <class Z> struct promote<std::complex<Z> > :
	public to_type<typename std::complex<typename promote<Z>::type> > { };

/** \brief to_real is used to promote complex types to real types
 *
 * This struct promotes any type of std::complex<T> to simply T
 * and leaves all other types as they are. It is used for template functions
 * that combine the use of complex and real numbers.
 *
 **/
template <class T> struct to_real : public
	t_if<is_ivl_array<T>,
		to_type<typename to_real<typename subtype<T>::type>::type, T>,
		to_type<T> >::type { };

template<> struct to_real<term> { typedef bool type; };

template<class T>
struct to_real<std::complex<T> > : public to_type<T> { };

/** \brief to_complex is used to promote real-only types to complex types
 *
 * This struct promotes any type T to std::complex<T>, in case
 * T is a simple type. If however T is a complex type, it leaves it as it is.
 * It is used to avoid std::complex<std::complex<T> > issues, where
 * in template functions where both complex and real types are used.
*/
template <class T> struct to_complex : public
	t_if<is_ivl_array<T>,
		to_type<typename to_complex<typename subtype<T>::type>::type, T>,
		to_type<std::complex<T> > >::type { };

template<> struct to_complex<term> { typedef bool type; };

template<class T>
struct to_complex<std::complex<T> > : public to_type<std::complex<T> > { };

/** \brief converts any type to floting-point
 *
 *
 */
template <class T> struct to_floating : public
	t_if<is_ivl_array<T>,
		to_type<typename to_floating<typename subtype<T>::type>::type, T>,
		to_type<double> >::type { };

template<> struct to_floating<term> { typedef bool type; };

template<>
struct to_floating<float> : public to_type<float> { };

template <class Z> struct to_floating<std::complex<Z> > :
	public to_type<std::complex<typename to_floating<Z>::type> > { };

/** \brief converts any type to a floting-point real number
 *
 *
 */
template <class T> struct to_real_floating : public
	t_if<is_ivl_array<T>,
		to_type<typename to_real_floating<typename
			subtype<T>::type>::type, T>,
		to_type<double> >::type { };

template<> struct to_real_floating<term> { typedef bool type; };

template<>
struct to_real_floating<float> : public to_type<float> { };

template <class Z> struct to_real_floating<std::complex<Z> > :
	public to_real_floating<Z> { };

/** \brief converts any type to according signed type
 *
 *
 */
template <class T> struct to_signed : public
	t_if<is_ivl_array<T>,
		to_type<typename to_signed<typename
			subtype<T>::type>::type, T>,
		to_type<int> >::type { };

template<> struct to_signed<term> { typedef bool type; };

template <>
struct to_signed<float> : public to_type<float> { };

template <>
struct to_signed<double> : public to_type<double> { };

template <class Z> struct to_signed<std::complex<Z> > :
	public to_type<std::complex<typename to_signed<Z>::type> > { };

/** \brief converts any type to according unsigned type
 *
 *
 */
template <class T> struct to_unsigned : public
	t_if<is_ivl_array<T>,
		to_type<typename to_unsigned<typename
			subtype<T>::type>::type, T>,
		to_type<unsigned> >::type { };

template<> struct to_unsigned<term> { typedef bool type; };

template <>
struct to_unsigned<float> : public to_type<float> { };

template <>
struct to_unsigned<double> : public to_type<double> { };

template <class Z> struct to_unsigned<std::complex<Z> > :
	public to_type<std::complex<typename to_unsigned<Z>::type> > { };

#include "platform_specific/signed_impl.hpp"

} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_EVOLUTION_HPP
