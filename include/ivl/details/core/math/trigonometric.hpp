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

#ifndef IVL_CORE_DETAILS_MATH_TRIGONOMETRIC_HPP
#define IVL_CORE_DETAILS_MATH_TRIGONOMETRIC_HPP

namespace ivl {
namespace math {
/* Note:
Functions is the math namespace need not be used directly.
They are brought to the ivl namespace by element functions.
The element functions are the same but they are defined
for both single elements and arrays.
*/

// - Chapter 1------ Unary trigonometric functions first ---------------------

/* First section: trigonometric functions (circular functions) took
directly from std */

using std::cos;
using std::sin;
using std::tan;
using std::cosh;
using std::sinh;
using std::tanh;

/* Second section: trigonometric functions (circular functions) that are
defined in std but maybe not for all types (not for complex). */

using std::atan;

template <class T>
std::complex<T> atan(const std::complex<T> & c)
{
	T real = c.real();
	T imag = c.imag();

	std::complex<T> log_v = log(std::complex<T>(T(1) - imag, real)
					/ std::complex<T>(T(1) + imag, -real));

	return std::complex<T>(log_v.imag() * T(1.0/2),
				-log_v.real() * T(1.0/2));
}

using std::asin;

template <class T>
std::complex<T> asin(const std::complex<T> & c)
{
	typedef typename std::complex<T> tp;
	T real = c.real();
	T imag = c.imag();
	std::complex<T> ic(-imag, real);
	std::complex<T> expr = log(ic + sqrt(tp(1) - c * c));

	return std::complex<T>(expr.imag(), -expr.real());
}

using std::acos;

template <class T>
std::complex<T> acos(const std::complex<T> & c)
{
	typedef typename std::complex<T> tp;
	std::complex<T> expr = sqrt(tp(1) - c * c);
	std::complex<T> iexpr(-expr.imag(), expr.real());
	expr = log(c + iexpr);

	return std::complex<T>(expr.imag(), -expr.real());
}

/* Third section: trigonometric functions which are not existant in std,
and implemented here */

template <class T>
T acosh(const T& c)
{
	return log (c + sqrt (c * c - T(1)));
}

template <class T>
std::complex<T> acosh(const std::complex<T> & c)
{
	typedef typename std::complex<T> tp;
	return log(c + (c + tp(1)) * sqrt((c - tp(1)) / (c + tp(1))));
}

template <class T>
T asinh(const T& c)
{
	return log (c + sqrt (c * c + T(1)));
}

template <class T>
std::complex<T> asinh(const std::complex<T> & c)
{
	typedef typename std::complex<T> tp;
	return log(c + sqrt(tp(1) + c * c));
}

template <class T>
T atanh(const T& c)
{
	return 0.5 * log((T(1) + c) / (T(1) - c));
}

template <class T>
std::complex<T> atanh(const std::complex<T> & c)
{
	typedef typename std::complex<T> tp;
	return log((tp(1) + c) * sqrt(tp(1) / (tp(1) - c * c)));
}

// small note: cast<T> is used, because we are sure that T is not an array type.
template <class T>
inline
T cot(const T elem)
{
	return cast<T>(1) / tan(elem);
}

template <class T>
inline
T coth(const T elem)
{
	const T tmp = exp(elem);
	return (tmp +
		cast<T>(1) / tmp) / (tmp - cast<T>(1) / tmp);
}

template <class T>
inline
T csc(const T elem)
{
	return (cast<T>(1) / sin(elem));
}

template <class T>
inline
T csch(const T elem)
{
	T tmp = exp(elem);
	return cast<T>(2) / (tmp - cast<T>(1) / tmp);
}

template <class T>
inline
T sec(const T elem)
{
	return (cast<T>(1) / cos(elem));
}

template <class T>
inline
T sech(const T elem)
{
	T tmp = exp(elem);
	return (cast<T>(2) / (tmp + cast<T>(1) / tmp));
}

template <class T>
inline
T acot(const T elem)
{
	return atan(cast<T>(1) / elem);
}

template <class T>
inline
T acoth(const T elem)
{
	return log((elem + cast<T>(1)) /
		(elem - cast<T>(1))) / cast<T>(2);
}

template <class T>
inline
T acsc(const T elem)
{
	return asin(cast<T>(1) / elem);
}

template <class T>
inline
T acsch(const T elem)
{
	return log((sign(elem) * cast<T>(sqrt(cast<T>(1) +
		elem * elem)) + cast<T>(1)) / elem);
}

template <class T>
inline
T asec(const T elem)
{
	return acos(cast<T>(1) / elem);
}

template <class T>
inline
T asech(const T elem)
{
	return log((sqrt(cast<T>(1) - elem * elem) +
		cast<T>(1)) / elem);
}

// - Chapter 2------ Binary trigonometric functions (second) ----------------
// (basically atan2)

using std::atan2;

} /* namespace math */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_MATH_TRIGONOMETRIC_HPP
