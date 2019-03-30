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

#ifndef IVL_CORE_DETAILS_MATH_CONSTANT_HPP
#define IVL_CORE_DETAILS_MATH_CONSTANT_HPP

namespace ivl {

//-----------------------------------------------------------------------------

/*
//! epsilon
extern const double epsilon;

//! infinity of double
extern const double infty;

//! pi math constant
extern const double pi;

//! imaginary part, like in matlab
extern const std::complex<double> i;
extern const std::complex<double> j;
*/

//-----------------------------------------------------------------------------

//! pi math constant
static const double pi = 3.14159265358979323846264338327950288419716939937510;

//! infinity of double
static const double infty = std::numeric_limits<double>::infinity();

//! epsilon
static const double epsilon = std::numeric_limits<double>::epsilon();

inline double eps(double p = 1.0)
{
	return pow(epsilon, p);
}

//-----------------------------------------------------------------------------

namespace math {

namespace math_details {

inline double get_infty() { return infty; } // suppress unused warning

}  // namespace math_details

//! imaginary part, the complex number (0, 1)
static const std::complex<double> i(0, 1);

//! imaginary part, the complex number (0, 1)
static const std::complex<double> j(0, 1);

}  // namespace math

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_MATH_CONSTANT_HPP
