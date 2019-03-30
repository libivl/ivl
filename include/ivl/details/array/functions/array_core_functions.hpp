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

#ifndef IVL_ARRAY_DETAILS_ARRAY_CORE_FUNCTIONS_HPP
#define IVL_ARRAY_DETAILS_ARRAY_CORE_FUNCTIONS_HPP

namespace ivl {

//--------------------------------------------------------------
// Auxiliary functions for array creation

// array construction by element values

/**
 * @name Array construction by providing element values
 * \relates array
@{*/
//! Create an array with one element
template <class T>
array<typename types::create_new<T>::type, fixed<1> > array_data(const T& p1)
{
	return array<typename types::create_new<T>::type, fixed<1> >(1, p1);
}

//! Create an array with two elements
template <class T, class T1>
array<typename types::create_new<T>::type, fixed<2> > array_data(const T& p1,
																const T1& p2)
{
	array<typename types::create_new<T>::type, fixed<2> > a(2);
	a[0] = p1; a[1] = p2;
	return a;
}

//! Create an array with three elements
template <class T, class T1, class T2>
array<typename types::create_new<T>::type, fixed<3> > array_data(const T& p1,
													const T1& p2, const T2& p3)
{
	array<typename types::create_new<T>::type, fixed<3> > a(3);
	a[0] = p1; a[1] = p2; a[2] = p3;
	return a;
}

//! Create an array with four elements
template <class T, class T1, class T2, class T3>
array<typename types::create_new<T>::type, fixed<4> > array_data(const T& p1,
									const T1& p2, const T2& p3, const T3& p4)
{
	array<typename types::create_new<T>::type, fixed<4> > a(4);
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4;
	return a;
}

//! Create an array with five elements
template <class T, class T1, class T2, class T3, class T4>
array<typename types::create_new<T>::type, fixed<5> > array_data(const T& p1,
						const T1& p2, const T2& p3, const T3& p4, const T4& p5)
{
	array<typename types::create_new<T>::type, fixed<5> > a(5);
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5;
	return a;
}

//! Create an array with six elements
template <class T, class T1, class T2, class T3, class T4, class T5>
array<typename types::create_new<T>::type, fixed<6> > array_data(const T& p1,
		const T1& p2, const T2& p3, const T3& p4, const T4& p5, const T5& p6)
{
	array<typename types::create_new<T>::type, fixed<6> > a(6);
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5; a[5] = p6;
	return a;
}

//! Create an array with seven elements
template <class T, class T1, class T2, class T3, class T4, class T5, class T6>
array<typename types::create_new<T>::type, fixed<7> > array_data(const T& p1,
					const T1& p2, const T2& p3, const T3& p4, const T4& p5,
													const T5& p6, const T6& p7)
{
	array<typename types::create_new<T>::type, fixed<7> > a(7);
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5; a[5] = p6; a[6] = p7;
	return a;
}
/**@}*/

/**
 * @name Size_array construction by providing element values
 * \relates array
@{*/
/*
//! Create a size_array with one element.
inline
size_array idx(size_t p1)
	{ return arr<size_t>(p1); }

//! Create a size_array with two element.
inline
size_array idx(size_t p1, size_t p2)
	{ return arr<size_t>(p1, p2); }

//! Create a size_array with three elements
inline
size_array idx(size_t p1, size_t p2, size_t p3)
	{ return arr<size_t>(p1, p2, p3); }

//! Create a size_array with four elements
inline
size_array idx(size_t p1, size_t p2, size_t p3, size_t p4)
	{ return arr<size_t>(p1, p2, p3, p4); }

//! Create a size_array with five elements
inline
size_array idx(size_t p1, size_t p2, size_t p3, size_t p4, size_t p5)
	{ return arr<size_t>(p1, p2, p3, p4, p5); }

//! Create a size_array with six elements
inline
size_array idx(size_t p1, size_t p2, size_t p3, size_t p4, size_t p5, size_t p6)
	{ return arr<size_t>(p1, p2, p3, p4, p5, p6); }
*/


//! Create a size_array with one element.
inline
array<size_t, fixed<1> > idx(size_t p1)
{
	return array<size_t, fixed<1> >(1, p1);
}

//! Create a size_array with two element.
inline
array<size_t, fixed<2> > idx(size_t p1, size_t p2)
{
	array<size_t, fixed<2> > a;
	a[0] = p1; a[1] = p2;
	return a;
}

//! Create a size_array with three elements
inline
array<size_t, fixed<3> > idx(size_t p1, size_t p2, size_t p3)
{
	array<size_t, fixed<3> > a;
	a[0] = p1; a[1] = p2; a[2] = p3;
	return a;
}

//! Create a size_array with four elements
inline
array<size_t, fixed<4> > idx(size_t p1, size_t p2, size_t p3, size_t p4)
{
	array<size_t, fixed<4> > a;
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4;
	return a;
}

//! Create a size_array with five elements
inline
array<size_t, fixed<5> > idx(size_t p1, size_t p2, size_t p3, size_t p4,
								size_t p5)
{
	array<size_t, fixed<5> > a;
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5;
	return a;
}

//! Create a size_array with six elements
inline
array<size_t, fixed<6> > idx(size_t p1, size_t p2, size_t p3, size_t p4,
								size_t p5, size_t p6)
{
	array<size_t, fixed<6> > a;
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5; a[5] = p6;
	return a;
}

//! Create a size_array with seven elements
inline
array<size_t, fixed<7> > idx(size_t p1, size_t p2, size_t p3, size_t p4,
								size_t p5, size_t p6, size_t p7)
{
	array<size_t, fixed<7> > a;
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5; a[5] = p6; a[6] = p7;
	return a;
}

//! Create a size_array with eight elements
inline
array<size_t, fixed<7> > idx(size_t p1, size_t p2, size_t p3, size_t p4,
								size_t p5, size_t p6, size_t p7, size_t p8)
{
	array<size_t, fixed<8> > a;
	a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5; a[5] = p6; a[6] = p7; a[7] = p8;
	return a;
}

/**@}*/

//--------------------------------------------------------------
// array MEMBER FUNCTIONS

/**
 * \brief Smallest of all elements
 *
 * Note: In WIN32 targets you have to either #undef min or compile
 * with IVL_USE_MINMAX to be able to use this function
**/

template<class T, class S>
typename types::create_new<T>::type
	array_common_base<array<T, S> >::min() const
{
	typename array_type::const_iterator it = to_array().begin();
	typename array_type::const_iterator end = to_array().end();
	CHECK(it != end, eshape);
	T s = *it;
	for (; it != end; ++it)
		if (*it < s)
			s = *it;
	return (s);
}

/**
 * \brief Largest of all elements
 *
 * Note: In WIN32 targets you have to either #undef max or compile
 * with IVL_USE_MINMAX to be able to use this function
 */

template<class T, class S>
typename types::create_new<T>::type
	array_common_base<array<T, S> >::max() const
// Note: developer's notice: if you see `function returning an array' error
// here means that you are either explicitly or implicitly trying to
// initialize an array which elements type is a c array, which is invalid.
{
	typename array_type::const_iterator it = to_array().begin();
	typename array_type::const_iterator end = to_array().end();
	CHECK(it != end, eshape);
	T s = *it;
	for (; it != end; ++it)
		if (*it > s)
			s = *it;
	return (s);
}


//--------------------------------------------------------------
// array NON-MEMBER FUNCTIONS

/**
 * @name Array non-member functions
 * \relates array
@{*/

//! return array left shifted
template<class T, class S>
typename array<T, S>::create_similar shift(const array<T, S>& in, int count, T val = T())
{
	typename array<T, S>::create_similar out(in.derived().size());
	size_t len = in.length();

	for (size_t i = 0; i < len; i++) {
		int j = int(i) - count;
		out[i] = (j >= 0 && j < int(len)) ? in[size_t(j)] : val;
	}

	return out;
}

//! array of cumulative product of elements
template<class T, class S>
typename array<T, S>::create_similar cumprod(const array<T, S>& in)
{
	typename array<T, S>::create_similar out(in.derived().size());
	size_t len = in.length();

	out[0] = in[0];
	for(size_t i = 1; i < len; i++)
		out[i] = in[i] * out[i - 1];

	return out;
}

//! Product of all elements
template<class T, class S>
typename types::promote<T>::type prod(const array<T, S>& in)
{
	typedef typename types::promote<T>::type return_type;
	return_type s = 1;
	for (size_t i = 0; i < in.length(); ++i)
		s *= cast<return_type>(in[i]);
	return s;
}

//! converts index vector to single-dim index
template<class S, class D>
inline
size_t sub2ind(const array<size_t, S>& stride, const array<size_t, D>& b)
{
	size_t offs = b[0];
	size_t ndims = stride.length();

	for(size_t i = 1; i < ndims; i++)
		offs += stride[i] * b[i];

	return offs;
}

/**@}*/

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_ARRAY_CORE_FUNCTIONS_HPP
