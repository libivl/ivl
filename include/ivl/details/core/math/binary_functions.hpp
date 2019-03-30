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

#ifndef IVL_CORE_DETAILS_MATH_BINARY_FUNCTIONS_HPP
#define IVL_CORE_DETAILS_MATH_BINARY_FUNCTIONS_HPP

namespace ivl {
namespace math {

//! maximum of two objects
template <class T, class S>
inline
typename types::maps::max<T, S>::type max(const T& t, const S& s)
{
	if(t > s)
		return t;
	else
		return s;
}

//! minimum of two objects
template <class T, class S>
inline
typename types::maps::max<T, S>::type min(const T& t, const S& s)
{
	if(t < s)
		return t;
	else
		return s;
}

//! mod function
template <class T, class S>
typename types::maps::max<T, S>::type mod(const T& s, S length)
{
	typename types::maps::max<T, S>::type rem_result = s % length;
	return (rem_result >= 0) ? rem_result : (rem_result + length);
}

inline
double mod(const double& s, double length)
{
	return s - floor(s / length) * length;
}

inline
float mod(const float& s, float length)
{
	return s - floor(s / length) * length;
}

template <class T>
inline
std::complex<T> pow(const std::complex<T> &x, int y)
{
	// kimon: todo: should define element cast above and use that.......
	return std::complex<T>(std::pow(
		std::complex<T>(types::to_floating<T>::type(x.real()),
			types::to_floating<T>::type(x.image()), y)));
}

template <class T>
inline
T pow(const T &x, int y)
{
	return T(std::pow(typename types::to_floating<T>::type(x), y));
}

template <class T>
inline
std::complex<T> pow(const std::complex<T> &x, double y)
{
	// kimon: todo: should define element cast above and use that.......
	return std::complex<T>(std::pow(
		std::complex<T>(types::to_floating<T>::type(x.real()),
			types::to_floating<T>::type(x.image()), y)));
}

template <class T>
inline
T pow(const T &x, double y)
{
	return T(std::pow(typename types::to_floating<T>::type(x), y));
}

} /* namespace math */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_MATH_BINARY_FUNCTIONS_HPP
