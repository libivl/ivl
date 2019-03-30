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

#ifndef IVL_CORE_DETAILS_MATH_BINARY_OPERATORS_HPP
#define IVL_CORE_DETAILS_MATH_BINARY_OPERATORS_HPP

namespace ivl {
namespace math {


// ------------------------------------------------------------------
// FUNCTIONS definition of functions that correspond to each operator

//---------------------- Relational Operators

using std::operator <;
using std::operator >;
using std::operator <=;
using std::operator >=;
using std::operator ==;
using std::operator !=;


//less than
template <class T, class S>
inline bool lt(const T& a, const S& b)
{
	return a < b;
}

template <class T, class S>
inline bool lt(const std::complex<T> &a, const std::complex<S> &b)
{
	return a.real() < b.real();
}

//less than or equal
template <class T, class S>
inline bool le(const T& a, const S& b)
{
	return a <= b;
}

template <class T, class S>
inline bool le(const std::complex<T> &a, const std::complex<S> &b)
{
	return a.real() <= b.real();
}

//greater than
template <class T, class S>
inline bool gt(const T& a, const S& b)
{
	return a > b;
}

template <class T, class S>
inline bool gt(const std::complex<T> &a, const std::complex<S> &b)
{
	return a.real() > b.real();
}

//greater than or equal
template <class T, class S>
inline bool ge(const T& a, const S& b)
{
	return a >= b;
}

template <class T, class S>
inline bool ge(const std::complex<T> &a, const std::complex<S> &b)
{
	return a.real() >= b.real();
}

//test for equality
template <class T, class S>
inline bool eq(const T& a, const S& b)
{
	return a == b;
}

template <class T, class S>
inline bool eq(const std::complex<T> &a, const std::complex<S> &b)
{
	return (a.real() == b.real()) && (a.imag() == b.imag());
}

//test for unequality
template <class T, class S>
inline bool ne(const T& a, const S& b)
{
	return a != b;
}

template <class T, class S>
inline bool ne(const std::complex<T> &a, const std::complex<S> &b)
{
	return (a.real() != b.real()) || (a.imag() != b.imag());
}

//---------------------- Logical Operators

template <class T, class S>
inline bool logical_or(const T& a, const S& b)
{
	return a || b;
}

template <class T, class S>
inline bool logical_and(const T& a, const S& b)
{
	return a && b;
}

//---------------------- Bitwise Operators

template <class T>
inline T bitlshift(const T& a, int b)
{
	return a << b;
}

template <class T>
inline T bitrshift(const T& a, int b)
{
	return a >> b;
}

template <class T, class S>
inline
typename types::maps::max<T, S>::type cbitor(const T& a, const S& b)
{
	return a | b;
}

template <class T, class S>
inline
typename types::maps::max<T, S>::type cbitand(const T& a, const S& b)
{
	return a & b;
}

//---------------------- Mathematical Operators

using std::operator+;
using std::operator-;
using std::operator/;
using std::operator*;

template <class T, class S>
inline
typename types::maps::max<T, S>::type plus(const T& a, const S& b)
{
	return a + b;
}

template <class T, class S>
inline
typename types::maps::max<T, S>::type minus(const T& a, const S& b)
{
	return a - b;
}

template <class T, class S>
inline
typename types::maps::max<T, S>::type times(const T& a, const S& b)
{
	return a * b;
}

template <class T, class S>
inline
typename types::maps::max<T, S>::type rdivide(const T& a, const S& b)
{
	return a / b;
}

template <class T, class S>
inline
typename types::maps::max<T, S>::type rem(const T& s, S length)
{
	return s % length;
}

template <class T>
double rem(const T& s, double length)
{
	// todo: find a better implementation
	double md = s - floor(s / length) * length;
	if(md < 0) md = -md;
	return (s < 0) ? -md : md;
}

template <class T>
float rem(const T& s, float length)
{
	// todo: find a better implementation
	float md = s - floor(s / length) * length;
	if(md < 0) md = -md;
	return (s < 0) ? -md : md;
}
/*
template <class T, class S>
inline T power(const T& x, const S& y)
{
	using std::pow; // TODO: definition of pow in right place. This line may not be needed if this is made.
	return pow(x, y);
}

inline int power(int x, int y)
{
	// TODO: fix this well, for all types. Also add integer power with different algorithm.
	return std::pow((double)x, y);
}

*/
} /* namespace math */

// ------------------------------------------------------------------
// OPERATORS definition of operators based on the actual functions

//---------------------- Relational Operators

// according operators for complex
template <class T, class S>
bool operator < (const std::complex<T> &a, const std::complex<S> &b)
{
    using namespace ivl::math;
    return lt(a, b);
}

template <class T, class S>
bool operator <= (const std::complex<T> &a, const std::complex<S> &b)
{
    using namespace ivl::math;
    return le(a, b);
}

template <class T, class S>
bool operator > (const std::complex<T> &a, const std::complex<S> &b)
{
    using namespace ivl::math;
    return gt(a, b);
}

template <class T, class S>
bool operator >= (const std::complex<T> &a, const std::complex<S> &b)
{
    using namespace ivl::math;
    return ge(a, b);
}

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_MATH_BINARY_OPERATORS_HPP
