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

#ifndef IVL_CORE_DETAILS_MATH_UNARY_OPERATORS_HPP
#define IVL_CORE_DETAILS_MATH_UNARY_OPERATORS_HPP

namespace ivl {
namespace math {

// ------------------------------------------------------------------
// definition of functions that correspond to each operator
using std::operator+;
using std::operator-;

//todo : check if this is a c++ predefined name
template <class T>
inline
T bitcmp(const T& elem)
{
	return ~(elem);
}

template <class T>
inline
bool cnot(const T& elem)
{
	return !(elem);
}

// Note: do not change unsigned type to signed. C++ does not.
template <class T>
inline
T uminus(const T& elem)
{
	return -(elem);
}

template <class T>
inline
T uplus(const T& elem)
{
	return +(elem);
}

template <class T>
inline
typename types::deref_ptr<T>::type dereference(const T& elem)
{
	return *(elem);
}

// ------------------------------------------------------------------
// definition of operators based on the actual functions
/*
template <class T> inline
T operator~(const T& elem) { return bitcmp(elem); }

template <class T> inline
T operator!(const T& elem) { return cnot(elem); }

template <class T> inline
T operator-(const T& elem) { return uminus(elem); }

template <class T> inline
T operator+(const T& elem) { return uplus(elem); }
*/
} /* namespace math */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_MATH_UNARY_OPERATORS_HPP
