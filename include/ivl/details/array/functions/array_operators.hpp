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

#ifndef IVL_ARRAY_DETAILS_ARRAY_OPERATORS_HPP
#define IVL_ARRAY_DETAILS_ARRAY_OPERATORS_HPP

namespace ivl {

// this file needs removal!

#if 0


//Todo: This file needs cleaning up and
// the operations need to be generated and then commentized
// instead of having the #defines

// This implementation is only temporary



// --- array-scalar





#define HELP3(opname, funcname, classname) \
 \
template <class A1, class A2> \
inline \
typename binary_elem_func_result< \
		typename types::get_value<A1>::type, \
		classname, A1, A2>::type operator opname( \
	const A1& a1, const A2& a2) \
{ \
	return funcname(a1, a2); \
};\

#define HELPb(opname, funcname, classname) \
 \
template <class A1, class A2> \
inline \
typename binary_elem_func_result<bool, classname, A1, A2> \
::type operator opname( \
	const A1& a1, const A2& a2) \
{ \
	return funcname(a1, a2); \
};\




#define HELP3__A(OP, FUNC, times_class) \
template<class T, class S, class K> \
inline \
const elem_func_scalar_l<T, times_class, T, array<T, S, K> > operator OP(const T& s, \
						const array<T, S, K>& a) \
{ \
	return FUNC(s, a); \
} \
template<class T, class S, class K> \
inline \
const elem_func_scalar_r<T, times_class, array<T, S, K>, T> operator OP( \
						const array<T, S, K>& a, const T& s) \
{ \
	return FUNC(a, s); \
} \
template<class T, class S1, class K1, class S2, class K2> \
inline \
const elem_func_binary<T, times_class, array<T, S1, K1>, array<T, S2, K2> > operator OP( \
						const array<T, S1, K1>& a, const array<T, S2, K2>& b) \
{ \
	return FUNC(a, b); \
} \


#define HELPb__A(OP, FUNC, times_class) \
template<class T, class S, class K> \
inline \
const elem_func_scalar_l<bool, times_class, T, array<T, S, K> > operator OP(const T& s, \
						const array<T, S, K>& a) \
{ \
	return FUNC(s, a); \
} \
template<class T, class S, class K> \
inline \
const elem_func_scalar_r<bool, times_class, array<T, S, K>, T> operator OP( \
						const array<T, S, K>& a, const T& s) \
{ \
	return FUNC(a, s); \
} \
template<class T, class S1, class K1, class S2, class K2> \
inline \
const elem_func_binary<bool, times_class, array<T, S1, K1>, array<T, S2, K2> > operator OP( \
						const array<T, S1, K1>& a, const array<T, S2, K2>& b) \
{ \
	return FUNC(a, b); \
} \



// TODO: commentize before generate!

HELP3__A( * , ivl::times, times_class)
HELP3__A( / , ivl::rdivide, rdivide_class)
HELP3__A( % , ivl::rem, rem_class)
HELP3__A( + , ivl::plus, plus_class)
HELP3__A( - , ivl::minus, minus_class)


template<class T, class S, class K>
inline
const elem_func_scalar_l<T, power_class, T, array<T, S, K> > operator^(const T& s,
						const array<T, S, K>& a)
{
	return ivl::power(s, a);
}
template<class T, class S, class K>
inline
const elem_func_scalar_r<T, power_class, array<T, S, K>, T> operator^(
						const array<T, S, K>& a, const T& s)
{
	return ivl::power(a, s);
}
template<class T, class S1, class K1, class S2, class K2>
inline
const elem_func_binary<T, bitxor_class, array<T, S1, K1>, array<T, S2, K2> > operator^(
						const array<T, S1, K1>& a, const array<T, S1, K1>& b)
{
	return ivl::bitxor(a, b);
}


HELP3__A( &  , ivl::cbitand , bitand_class )
HELP3__A( |  , ivl::cbitor , bitor_class )
HELP3__A( <<  , ivl::bitlshift , bitlshift_class )
HELP3__A( >>  , ivl::bitrshift , bitrshift_class )

HELPb__A( &&  ,  ivl::logical_and , and_class )
HELPb__A( ||  ,  ivl::logical_or , or_class )


template<class T, class S, class K>
inline
const elem_func_scalar_l<bool, eq_class, T, array<T, S, K> > operator ==(const T& s,
						const array<T, S, K>& a)
{
	return ivl::eq(s, a);
}
template<class T, class S, class K>
inline
const elem_func_scalar_r<bool, eq_class, array<T, S, K>, T> operator ==(
						const array<T, S, K>& a, const T& s)
{
	return ivl::eq(a, s);
}
template<class T, class S1, class K1, class S2, class K2>
inline
const elem_func_binary<bool, eq_class, array<T, S1, K1>, array<T, S2, K2> > operator ==(
						const array<T, S1, K1>& a, const array<T, S2, K2>& b)
{
	return ivl::eq(a, b);
}

HELPb__A( !=  , ivl::ne , ne_class )
HELPb__A( <  , ivl::lt , lt_class ) // note: we would like here to add op < for complex<T>
HELPb__A( >  , ivl::gt , gt_class )
HELPb__A( <=  , ivl::le , le_class )
HELPb__A( >=  , ivl::ge , ge_class )



template<class T, class S>
bool operator<(const std::complex<T>& x, const std::complex<S>& y)
{
	return lt(x, y);
}

template<class T, class S>
bool operator>(const std::complex<T>& x, const std::complex<S>& y)
{
	return gt(x, y);
}

template<class T, class S>
bool operator<=(const std::complex<T>& x, const std::complex<S>& y)
{
	return le(x, y);
}

template<class T, class S>
bool operator>=(const std::complex<T>& x, const std::complex<S>& y)
{
	return ge(x, y);
}




// unary (copy paste from below)
//todo: make them elem-funcs

//--------------------------------------------------------------
// UNARY OPERATORS (templates)


	/**
	 * \brief Unary Plus
	 *
	 * Apply unary plus to all elements.
	 * @return A new structure of the same type and size where unary plus is
	 * applied an all elements.
	 */
template <class T, class S, class K>
typename array<T, S, K>::
create_similar operator+(const array<T, S, K>& in)
{
	return typename array<T, S, K>::create_similar(ivl::uplus(in.derived()));
}

	/**
	 * \brief Unary Minus
	 *
	 * Apply unary minus to all elements.
	 * @return A new structure of the same type and size where unary minus
	 * is applied to all elements.
	 */
template <class T, class S, class K>
typename array<T, S, K>::
create_similar operator-(const array<T, S, K>& in)
{
	return typename array<T, S, K>::
		create_similar(ivl::uminus(in.derived()));
}

	/**
	 * \brief One's Complement of each element
	 *
	 * Compute the one's complement of each element and return it.
	 */
template <class T, class S, class K>
typename array<T, S, K>::
create_similar operator~(const array<T, S, K>& in)
{
	return typename array<T, S, K>::
		create_similar(ivl::bitcmp(in.derived()));
}

/** @name Logical operators
@{*/

	/**
	 * \brief Apply logical negation (!) on each element of the %array.
	 *
	 * @return an array of booleans of the same dimensions with this one.
	 */

template <class T, class S, class K>
typename types::to_bool<typename array<T, S, K>::create_similar>::
type operator!(const array<T, S, K>& in)
{
	//TODO: with elem functions!
	typename types::to_bool<typename array<T, S, K>::create_similar>::
		type a(in.size());

	for (size_t i = 0; i < a.length(); ++i)
		a[i] = !in[i];

	return a;
}

// unary assign(copied from below). need to make loop


//--------------------------------------------------------------
// array UNARY OPERATORS

	/**
	 * \brief Prefix Increment
	 *
	 * Apply prefix increment to all elements (++elem).
	 * @return Itself
	 */
template <class T, class S, class K>
typename array<T, S, K>::derived_type& operator++(array<T, S, K>& in)
{
	in = ivl::plus(in, elem_cast<T>(1));
	return in.derived();
}

	/**
	 * \brief Postfix Increment
	 *
	 * Apply postfix increment to all elements (elem++).
	 * @return Itself before the increment is applied.
	 */
template <class T, class S, class K>
typename array<T, S, K>::create_similar operator++(array<T, S, K>& in, int)
{
	typename array<T, S, K>::create_similar a(in.derived());
	in = ivl::plus(in, elem_cast<T>(1));
	return a;
}

	/**
	 * \brief Prefix Decrement
	 *
	 * Apply prefix decrement to all elements (--elem).
	 * @return Itself
	 */
template <class T, class S, class K>
typename array<T, S, K>::derived_type& operator--(array<T, S, K>& in)
{
	in = ivl::minus(in, elem_cast<T>(1));
	return in.derived();
}

	/**
	 * \brief Postfix Decrement
	 *
	 * Apply postfix decrement to all elements (elem--).
	 * @return Itself before the decrement is applied.
	 */
template <class T, class S, class K>
typename array<T, S, K>::create_similar operator--(array<T, S, K>& in, int)
{
	typename array<T, S, K>::create_similar a = in.derived();
	in = ivl::minus(in, elem_cast<T>(1));
	return a;
}

















// The rest are only kept for comment information
// and they are defined-out (like commented-out)




#if 0

#ifdef IVL_MATLAB
	/**
	 * \brief Assign an existing Matlab mxArray
	 *
	 * eg:
	 * \code ivl::array<int> a;
	 * a = lrhs[0]; \endcode
	 *
	 * If the mxArray contains elements of different class
	 * than the type of the %array elements, an exception will occur
	 */
template <class T, class S, class K>
typename array<T, S, K>::derived_type& operator=(array<T, S, K>& a, const mxArray* mx)
{
}
#endif


//==============================================================
// array SELF-assign numeric operators
/**
 * @name Arithmetic operators
@{*/

//--------------------------------------------------------------
// array UNARY OPERATORS

	/**
	 * \brief Prefix Increment
	 *
	 * Apply prefix increment to all elements (++elem).
	 * @return Itself
	 */
template <class T, class S, class K>
typename array<T, S, K>::derived_type& operator++(array<T, S, K>& in)
{
	in = ivl::plus(in, elem_cast<T>(1));
	return in.derived();
}

	/**
	 * \brief Postfix Increment
	 *
	 * Apply postfix increment to all elements (elem++).
	 * @return Itself before the increment is applied.
	 */
template <class T, class S, class K>
typename array<T, S, K>::create_similar operator++(array<T, S, K>& in, int)
{
	typename array<T, S, K>::create_similar a(in.derived());
	in = ivl::plus(in, elem_cast<T>(1));
	return a;
}

	/**
	 * \brief Prefix Decrement
	 *
	 * Apply prefix decrement to all elements (--elem).
	 * @return Itself
	 */
template <class T, class S, class K>
typename array<T, S, K>::derived_type& operator--(array<T, S, K>& in)
{
	in = ivl::minus(in, elem_cast<T>(1));
	return in.derived();
}

	/**
	 * \brief Postfix Decrement
	 *
	 * Apply postfix decrement to all elements (elem--).
	 * @return Itself before the decrement is applied.
	 */
template <class T, class S, class K>
typename array<T, S, K>::create_similar operator--(array<T, S, K>& in, int)
{
	typename array<T, S, K>::create_similar a = in.derived();
	in = ivl::minus(in, elem_cast<T>(1));
	return a;
}

//--------------------------------------------------------------
// array BINARY OPERATORS

//! multiply array elements by \e s
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator*=(array<T, S, K>& in, const T& s)
{
	in = ivl::times(in, s);
	return in.derived();
}

//! divide array elements by \e s
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator/=(array<T, S, K>& in, const T& s)
{
	in = ivl::rdivide(in, s);
	return in.derived();
}

//! Perform modulo \e s on all elements
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator%=(array<T, S, K>& in, const T& s)
{
	in = ivl::mod(in, s);
	return in.derived();
}

//! Add \e s to array elements.
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator+=(array<T, S, K>& in, const T& s)
{
	in = ivl::plus(in, s);
	return in.derived();
}

//! Subtract \e s from array elements
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator-=(array<T, S, K>& in, const T& s)
{
	in = ivl::minus(in, s);
	return in.derived();
}

	/**
	 * \brief Add the elements of \e a.
	 *
	 * Add to this structure the structure \e a in an element-wise fashion.
	 * @return Itself
	 */
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator+=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::plus(in, a);
	return in.derived();
}

	/**
	 * \brief Subtract the elements of \e a.
	 *
	 * Subtract of this structure the structure \e a in an element-wise
	 * fashion.
	 * @return Itself
	 */
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator-=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::minus(in, a);
	return in.derived();
}

//! Bitwise XOR each element with \e s.
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator^=(array<T, S, K>& in, const T& s)
{
	in = ivl::bitxor(in, s);
	return in.derived();
}

//! Bitwise AND each element with \e s.
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator&=(array<T, S, K>& in, const T& s)
{
	in = ivl::cbitand(in, s);
	return in.derived();
}

//! Bitwise OR each element with \e s.
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator|=(array<T, S, K>& in, const T& s)
{
	in = ivl::cbitor(in, s);
	return in.derived();
}

/**
 * @name Bitwise operators
@{*/
	//! Bitwise left shift all elements \e s times.
template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator<<=(array<T, S, K>& in, const T& s)
{
	in = ivl::bitlshift(in, s);
	return in.derived();
}

	//! Bitwise right shift all elements \e s times.

template<class T, class S, class K>
typename array<T, S, K>::derived_type& operator>>=(array<T, S, K>& in, const T& s)
{
	in = ivl::bitrshift(in, s);
	return in.derived();
}

// multiply array elements by array s elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator*=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::times(in, a);
	return in.derived();
}

// divide array elements by array s elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator/=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::rdivide(in, a);
	return in.derived();
}

// remainder array elements by array s elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator%=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::rem(in, a);
	return in.derived();
}

// XOR array s elements into array elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator^=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::bitxor(in, a);
	return in.derived();
}

// OR array s elements into array elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator|=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::cbitor(in, a);
	return in.derived();
}

// AND array s elements into array elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator&=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::cbitand(in, a);
	return in.derived();
}

// left shift array elements by array s elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator<<=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::bitlshift(in, a);
	return in.derived();
}

// right shift array elements by array s elements
template<class T, class S, class K, class D, class P>
typename array<T, S, K>::derived_type& operator>>=(array<T, S, K>& in, const array<T, D, P>& a)
{
	in = ivl::bitrshift(in, a);
	return in.derived();
}
#endif
#if 0
//==============================================================
// array CONST (new-type-returning) numeric operators


//--------------------------------------------------------------
// UNARY OPERATORS (templates)


	/**
	 * \brief Unary Plus
	 *
	 * Apply unary plus to all elements.
	 * @return A new structure of the same type and size where unary plus is
	 * applied an all elements.
	 */
template <class T, class S, class K>
typename array<T, S, K>::
create_similar operator+(const array<T, S, K>& in)
{
	return typename array<T, S, K>::create_similar(ivl::uplus(in.derived()));
}

	/**
	 * \brief Unary Minus
	 *
	 * Apply unary minus to all elements.
	 * @return A new structure of the same type and size where unary minus
	 * is applied to all elements.
	 */
template <class T, class S, class K>
typename array<T, S, K>::
create_similar operator-(const array<T, S, K>& in)
{
	return typename array<T, S, K>::
		create_similar(ivl::uminus(in.derived()));
}

	/**
	 * \brief One's Complement of each element
	 *
	 * Compute the one's complement of each element and return it.
	 */
template <class T, class S, class K>
typename array<T, S, K>::
create_similar operator~(const array<T, S, K>& in)
{
	return typename array<T, S, K>::
		create_similar(ivl::bitcmp(in.derived()));
}

/** @name Logical operators
@{*/

	/**
	 * \brief Apply logical negation (!) on each element of the %array.
	 *
	 * @return an array of booleans of the same dimensions with this one.
	 */

template <class T, class S, class K>
typename types::to_bool<typename array<T, S, K>::create_similar>::
type operator!(const array<T, S, K>& in)
{
	//TODO: with elem functions!
	typename types::to_bool<typename array<T, S, K>::create_similar>::
		type a(in.size());

	for (size_t i = 0; i < a.length(); ++i)
		a[i] = !in[i];

	return a;
}
#endif
/**@}*/

//--------------------------------------------------------------
// BINARY OPERATORS (templates)

	/**
	 * \brief Multiply with the elements of \e a.
	 *
	 * Multiply this structure with the structure \e a in an element-wise
	 * fashion.
	 * @return Itself
	 */

 	/**
	 * \brief Divide with the elements of \e a.
	 *
	 * Divide this structure with the structure \e a in an element-wise
	 * fashion.
	 * @return Itself
	 */

	/**
	 * \brief Compute module with the elements of \e a.
	 *
	 * Divide each element of this with the element of \e a in the same
	 * position and assign the reminder.
	 * @return Itself
	 */

	/**
	 * \brief Bitwise left shift
	 *
	 * Shift all the elements to the left as many times as the corresponding
	 * element of \e a implies.
	 * @return Itself
	 */

	/**
	 * \brief Bitwise right shift
	 *
	 * Shift all the elements to the right as many times as the corresponding
	 * element of \e a implies.
	 * @return Itself
	 */

	/**
	 * \brief Bitwise XOR with the elements of \e a.
	 *
	 * Perform bitwise XOR of this structure with \a in an element-wise
	 * fashion.
	 * @return Itself
	 */

	/**
	 * \brief Bitwise AND with the elements of \e a.
	 *
	 * Perform bitwise AND of this structure with \a in an element-wise
	 * fashion.
	 * @return Itself
	 */

	/**
	 * \brief Bitwise OR with the elements of \e a.
	 *
	 * Perform bitwise OR of this structure with \a in an element-wise
	 * fashion.
	 * @return Itself
	 */









/**
 * @name Arithmetical Operations
 *
 * \relates array_base
@{*/



#if 0

/**
 * \brief Array bit-wise XOR
 *
 * Element by element XOR of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, bitxor_class, T, S1, T, S2> operator^(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::bitxor(a, b);
}






//! Multiply with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, times_class, T, S, T> operator*(const T& s,
						const array_base<T, S>& a)
{
	return ivl::times(s, a);
}

//! Multiply with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, times_class, T, S, T> operator*(const array_base<T, S>& a,
							const T& s)
{
	return ivl::times(a, s);
}

//! Divide with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, rdivide_class, T, S, T> operator/(const T& s,
						const array_base<T, S>& a)
{
	return ivl::rdivide(s, a);
}

//! Divide with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, rdivide_class, T, S, T> operator/(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::rdivide(a, s);
}


//! Modulus with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, cmod_class, T, S, T> operator%(
						const T& s,
						const array_base<T, S>& a)
{
	return ivl::cmod(s, a);
}

//! Modulus with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, cmod_class, T, S, T> operator%(const array_base<T, S>& a,
							const T& s)
{
	return ivl::cmod(a, s);
}


//! Addition with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, plus_class, T, S, T> operator+(const T& s,
						const array_base<T, S>& a)
{
	return ivl::plus(s, a);
}

//! Addition with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, plus_class, T, S, T> operator+(const array_base<T, S>& a,
								const T& s)
{
	return ivl::plus(a, s);
}


//! Subtraction with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, minus_class, T, S, T> operator-(const T& s,
						const array_base<T, S>& a)
{
	return ivl::minus(s, a);
}

//! Subtraction with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, minus_class, T, S, T> operator-(const array_base<T, S>& a,
							const T& s)
{
	return ivl::minus(a, s);
}

// ---array-array

/**
 * \brief Array multiply
 *
 * Element by element multiplication of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, times_class, T, S1, T, S2> operator*(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::times(a, b);
}


/**
 * \brief Array division
 *
 * Element by element division of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, rdivide_class, T, S1, T, S2> operator/(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::rdivide(a, b);
}


/**
 * \brief Array modulus
 *
 * Element by element modulus of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, cmod_class, T, S1, T, S2> operator%(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::cmod(a, b);
}



/**
 * \brief Array addition
 *
 * Element by element addition of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, plus_class, T, S1, T, S2> operator+(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::plus(a, b);
}


/**
 * \brief Array subtraction
 *
 * Element by element subtraction of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, minus_class, T, S1, T, S2> operator-(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::minus(a, b);
}

//@}

/**
 * @name Bitwise Operations
 *
 * \relates array_base
@{*/

//--- array-scalar

//! Bitwise XOR with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_l<T, power_class, T, S, T> operator^(const T& s,
							const array_base<T, S>& a)
{
	return ivl::power(s, a);
}

//! Bitwise XOR with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_r<T, power_class, T, S, T> operator^(const array_base<T, S>& a,
							const T& s)
{
	return ivl::power(a, s);
}


//! Bitwise AND with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, bitand_class, T, S, T> operator&(const T& s,
						const array_base<T, S>& a)
{
	return ivl::cbitand(s, a);
}

//! Bitwise AND with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, bitand_class, T, S, T> operator&(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::cbitand(a, s);
}

//! Bitwise OR with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, bitor_class, T, S, T> operator|(const T& s,
						const array_base<T, S>& a)
{
	return ivl::cbitor(s, a);
}

//! Bitwise OR with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, bitor_class, T, S, T> operator|(const array_base<T, S>& a,
							const T& s)
{
	return ivl::cbitor(a, s);
}

//! Bitwise left shift with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, bitlshift_class, T, S, T> operator<<(const T& s,
						const array_base<T, S>& a)
{
	return ivl::bitlshift(s, a);
}

//! Bitwise left shift with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_r<T, bitlshift_class, T, S, T> operator<<(const array_base<T,
							S>& a, const T& s)
{
	return ivl::bitlshift(a, s);
}


//! Bitwise right shift with scalar (left)
template<class T, class S>
inline
const elem_func_scalar_l<T, bitrshift_class, T, S, T> operator>>(const T& s,
						const array_base<T, S>& a)
{
	return ivl::bitrshift(s, a);
}

//! Bitwise right shift with scalar (right)
template<class T, class S>
inline
const elem_func_scalar_r<T, bitrshift_class, T, S, T> operator>>(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::bitrshift(a, s);
}

//--- array-array

/**
 * \brief Array bit-wise XOR
 *
 * Element by element XOR of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, bitxor_class, T, S1, T, S2> operator^(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::bitxor(a, b);
}

/**
 * \brief Array bit-wise AND
 *
 * Element by element AND of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, bitand_class, T, S1, T, S2> operator&(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::cbitand(a, b);
}


/**
 * \brief Array bit-wise OR
 *
 * Element by element OR of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, bitor_class, T, S1, T, S2> operator|(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::cbitor(a, b);
}

/**
 * \brief Array arithmentical left shift
 *
 * Element by element left shift of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, bitlshift_class, T, S1, T, S2> operator<<(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::bitlshift(a, b);
}

/**
 * \brief Array arithmentical right shift
 *
 * Element by element right shift of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<T, bitrshift_class, T, S1, T, S2> operator>>(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::bitrshift(a, b);
}

/**@}*/

// ----- boolean operators

/**
 * @name Logical & relational operators
 *
 * All operations of this type are element-wise and return a boolean for each
 * element. Thus, the return type is a boolean structure of the same dimensions
 * as the input.
@{*/


/**
 * \brief Array logical AND with scalar (left)
 *
 * Logical OR all elements with scalar \e s.
 * @return A boolean structure of the same size that hosts the result.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, and_class, T, S, T> operator&&(const T& s,
						const array_base<T, S>& a)
{
	return ivl::logical_and(s, a);
}

/**
 * \brief Array logical AND with scalar (right)
 *
 * Element by element right shift of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, and_class, T, S, T> operator&&(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::logical_and(a, s);
}

/**
 * \brief Array logical AND
 *
 * Element by element logical OR of two array-based structures
 * @return A boolean structure of the same size that hosts the result.
 * \warning The two arrays must have the same dimensions.
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, and_class, T, S1, T, S2> operator&&(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::logical_and(a, b);
}

/**
 * \brief Array logical OR with scalar (left)
 *
 * Logical OR all elements with scalar \e s.
 * @return A boolean structure of the same size that hosts the result.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, or_class, T, S, T> operator||(const T& s,
						const array_base<T, S>& a)
{
	return ivl::logical_or(s, a);
}

/**
 * \brief Array logical OR with scalar (right)
 *
 * Element by element right shift of two array-based structures
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, or_class, T, S, T> operator||(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::logical_or(a, s);
}

/**
 * \brief Array logical OR
 *
 * Element by element logical OR of two array-based structures
 * @return A boolean structure of the same size that hosts the result.
 * \warning The two arrays must have the same dimensions.
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, or_class, T, S1, T, S2> operator||(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::logical_or(a, b);
}

/**
 * \brief Array's element-wise equality check with scalar (right)
 *
 * Check if all elements are equal to scalar \e s.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, eq_class, T, S, T> operator==(const T& s,
						const array_base<T, S>& a)
{
	return ivl::eq(s, a);
}

/**
 * \brief Array's element-wise equality check with scalar (left)
 *
 * Check if all elements are equal to scalar \e s.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, eq_class, T, S, T> operator==(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::eq(a, s);
}

/**
 * \brief Array element-wise equality check
 *
 * Element by element equality check of two array-based structures.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, eq_class, T, S1, T, S2> operator==(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::eq(a, b);
}

/**
 * \brief Array's element-wise inequality check with scalar (left)
 *
 * Check if all elements are inequal to scalar \e s.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, ne_class, T, S, T> operator!=(const T& s,
						const array_base<T, S>& a)
{
	return ivl::ne(s, a);
}

/**
 * \brief Array's element-wise inequality check with scalar (right)
 *
 * Check if all elements are inequal to scalar \e s.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, ne_class, T, S, T> operator!=(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::ne(a, s);
}

/**
 * \brief Array element-wise inequality check
 *
 * Element by element inequality check of two array-based structures.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, ne_class, T, S1, T, S2> operator!=(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::ne(a, b);
}

/**
 * \brief Array's element-wise 'less than' check with scalar (left)
 *
 * Check if all elements are less than scalar \e s.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, lt_class, T, S, T> operator<(const T& s,
						const array_base<T, S>& a)
{
	return ivl::lt(s, a);
}

/**
 * \brief Array's element-wise 'less than' check with scalar (right)
 *
 * Check if scalar \e s is less than each element.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, lt_class, T, S, T> operator<(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::lt(a, s);
}

/**
 * \brief Array element-wise 'less than' check
 *
 * Check if the elements of \e a are less than the corresponding elements of
 * \e b.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, lt_class, T, S1, T, S2> operator<(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::lt(a, b);
}

/**
 * \brief Array's element-wise 'greater than' check with scalar (left)
 *
 * Check if all elements are greater than scalar \e s.
 * @return A boolean structure of the same size that hosts the result.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, gt_class, T, S, T> operator>(const T& s,
						const array_base<T, S>& a)
{
	return ivl::gt(s, a);
}

/**
 * \brief Array's element-wise 'greater than' check with scalar (right)
 *
 * Check if scalar \e s is greater than each element.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, gt_class, T, S, T> operator>(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::gt(a, s);
}

/**
 * \brief Array element-wise 'greater than' check
 *
 * Check if the elements of \e a are greater than the corresponding elements of
 * \e b.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 * \warning The two arrays must have the same dimensions.
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, gt_class, T, S1, T, S2> operator>(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::gt(a, b);
}

/**
 * \brief Array's element-wise 'less than or equal to' check with scalar (left)
 *
 * Check if all elements are less than or equal to scalar \e s.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, le_class, T, S, T> operator<=(const T& s,
						const array_base<T, S>& a)
{
	return ivl::le(s, a);
}

/**
 * \brief Array's element-wise 'less than or equal to' check with scalar (right)
 *
 * Check if scalar \e s is less than or equal to each element.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, le_class, T, S, T> operator<=(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::le(a, s);
}

/**
 * \brief Array element-wise 'less than or equal to' check
 *
 * Check if the elements of \e a are less than or equal to the corresponding
 * elements of \e b.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison
 * \warning The two arrays must have the same dimensions
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, le_class, T, S1, T, S2> operator<=(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::le(a, b);
}

/**
 * \brief Array's element-wise 'greater than or equal to' check with scalar
 * (left)
 *
 * Check if all elements are greater than scalar or equal to \e s.
 * @return A boolean structure of the same size that hosts the result.
 */
template<class T, class S>
inline
const elem_func_scalar_l<bool, ge_class, T, S, T> operator>=(const T& s,
						const array_base<T, S>& a)
{
	return ivl::ge(s, a);
}

/**
 * \brief Array's element-wise 'greater than or equal to' check with scalar
 * (right)
 *
 * Check if scalar \e s is greater than or equal to each element.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 */
template<class T, class S>
inline
const elem_func_scalar_r<bool, ge_class, T, S, T> operator>=(
						const array_base<T, S>& a,
						const T& s)
{
	return ivl::ge(a, s);
}

/**
 * \brief Array element-wise 'greater than or equal to' check
 *
 * Check if the elements of \e a are greater than or equal to the corresponding
 * elements of \e b.
 * @return A boolean structure of the same size that hosts the result of each
 * element comparison.
 * \warning The two arrays must have the same dimensions.
 */
template<class T, class S1, class S2>
inline
const elem_func_binary<bool, ge_class, T, S1, T, S2> operator>=(
						const array_base<T, S1>& a,
						const array_base<T, S2>& b)
{
	return ivl::ge(a, b);
}

/**@}*/

#endif

#endif

} // namespace ivl

#endif // IVL_ARRAY_DETAILS_ARRAY_OPERATORS_HPP
