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

#ifndef IVL_ARRAY_ND_DETAILS_CAT_ARRAY_HPP
#define IVL_ARRAY_ND_DETAILS_CAT_ARRAY_HPP

namespace ivl {

//TODO: please wipe this file
#if 0
//! Defines a cat array that will be used to concatenate arrays (1- and n- dimensional), and ranges.
template <class T>
class cat_array : public array_nd<T, cat_array<T> >
{

public:

	// Constructors
	cat_array() : array_nd<T, cat_array<T> >(0) { };

	template<class S>
	cat_array(const array_nd<T, S>& a) : array_nd<T, cat_array<T> >(a) { };
	template<class S, bool C>
	cat_array(const sub_array<T, S, C>& a) : array_nd<T,  cat_array<T> >(a) { };
	cat_array(const array<T>& a) : array_nd<T, cat_array<T> >(idx(a.length()), a) { };
	cat_array(const T& s) : array_nd<T, cat_array<T> >(1,s) { };
	cat_array(const range<T>& ra) : array_nd<T, cat_array<T> >(ra.length())
	{
		size_t i = 0;
		for (T j = ra.first; j <= ra.last; j += ra.step)
			(*this)[i++] = j;
	};
};

//! ostream operator<< overload for cat_array
template <class T>
std::ostream& operator<<(std::ostream& os, const cat_array<T>& a)
{
	os << "[" << array_nd<T>(a) << "]";
	return os;
}

#endif
} // namespace ivl

#endif // IVL_ARRAY_ND_DETAILS_CAT_ARRAY_HPP
