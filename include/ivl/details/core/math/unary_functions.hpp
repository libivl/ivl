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

#ifndef IVL_CORE_DETAILS_MATH_UNARY_FUNCTIONS_HPP
#define IVL_CORE_DETAILS_MATH_UNARY_FUNCTIONS_HPP

namespace ivl {
namespace math {

// -------------------------------------------------------------
// basic mathematical unary functions
// about numbers definitions etc.

template <class T>
inline
int is_inf(T x)
{
	if(x == std::numeric_limits<T>::infinity())
		return 1;
	else if(x == -std::numeric_limits<T>::infinity())
		return -1;
	else
		return 0;
}

#include "platform_specific/isnan_impl.hpp"

template <class T>
inline
int is_inf(const std::complex<T>& x)
{
	return is_inf(x.real()) || is_inf(x.imag());
}

template <class T>
inline
int is_nan(std::complex<T> x)
{
	return is_nan(x.real()) || is_nan(x.imag());
}

template <class T>
T sign(const T& a)
{
	if (a > T(0))
		return T(1);
	else if (a < T(0))
		return T(-1);
	else
		return T(0);
}

template <class T>
T sign(const std::complex<T>& a)
{
	if (a.real() > T(0))
		return T(1);
	else if (a.real() < T(0))
		return T(-1);
	else
		return T(0);
}
// -------------------------------------------------------------------
// unary mathematical functions
// simple ones. already existant in std, or in some implementations
// of std, or half-implemented (not for complex).
// TODO: some might need to be moved to the next section
// -------------------------------------------------------------------

using std::abs;
using std::exp;
using std::sqrt;

using std::floor;

template <class T>
inline
std::complex<T> floor(const std::complex<T> &x)
{
	return std::complex<T>(std::floor(x.real()), std::floor(x.imag()));
}

using std::ceil;

template <class T>
inline
std::complex<T> ceil(const std::complex<T> &x)
{
	return std::complex<T>(std::ceil(x.real()), std::ceil(x.imag()));
}

#include "platform_specific/round_impl.hpp"

template <class T>
inline
std::complex<T> round(const std::complex<T> &x)
{
	return std::complex<T>(::round(x.real()), ::round(x.imag()));
}

template <class T>
inline
std::complex<T> conj(const std::complex<T> &x)
{
	return std::complex<T>(x.real(), -x.imag());
}

template <class T>
inline
T angle(const std::complex<T> &x)
{
	return std::log(x).imag();
}

template <class T>
inline
T sqr(const T& x)
{
	return x * x;
}

// ------------------------------------------------------------------
// functions that are not defined in std
// ------------------------------------------------------------------

template <class T>
inline
T fix(const T elem)
{
	T res = floor(abs(elem));
	return (elem < cast<T>(0.0)) ? -res : res;
}

template <class T>
inline
T fix(const std::complex<T>& elem)
{
	T res = floor(abs(elem));
	return (elem.real() < cast<T>(0.0)) ? -res : res;
}

using std::log;

// iavr
// TODO: ivl_func: log[base](elem)
// TODO: also out of math, elem_func etc.
template <class T>
inline
T log_base(const T base, const T elem)
{
	return cast<T>(log(elem)) / cast<T>(log(base));
}

// TODO: speed improve. dont call actual log function for log10
template <class T>
inline
T log10(const T elem)
{
	return log_base(T(10), elem);  // iavr
// 	return cast<T>(log(elem)) / cast<T>(log(T(10)));
}

// TODO: speed improve. dont call actual log function for log2
template <class T>
inline
T log2(const T elem)
{
	return log_base(T(2), elem);  // iavr
// 	return cast<T>(log(elem)) / cast<T>(log(T(2)));
}

template <class T>
inline
T ln(const T elem)
{
	return cast<T>(log(elem));
}

template <class T>
inline
T nextpow2(const T& elem)
{
	return std::pow(cast<T>(2), ceil(log2(elem)));
}

// special right now for single element only
template <class T>
inline
T rand(const T& from, const T& to)
{
	size_t total = size_t(to - from + 1);
	return T(std::rand() % total) + from;
}
inline
double rand(double from, double to)
{
// 	size_t total = size_t(to - from + 1);
// 	return std::fmod(std::rand()/1000.0, total) + from;
	return std::rand() * (to - from) / RAND_MAX;  // iavr
}
inline
float rand(float from, float to)
{
// 	size_t total = size_t(to - from + 1);
// 	return std::fmod(std::rand()/1000.0, total) + from;
	return std::rand() * (to - from) / RAND_MAX;  // iavr
}

} /* namespace math */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_MATH_UNARY_FUNCTIONS_HPP
