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

#ifndef IVL_ARRAY_DETAILS_SLICE_HPP
#define IVL_ARRAY_DETAILS_SLICE_HPP

namespace ivl {

template <class T> class range;

/**
 * \brief A slice
 *
 * This class has the same members with the class range (with different names),
 * and it is used to define a slice in an array. It's main purpose of existence
 * if to be inherited by slice_array which associates %slices with arrays.
 */
class slice
{

public:
	size_t start;	//!< the starting offset
	size_t length;	//!< the number of elements
	ptrdiff_t stride;	//!< the distance between elements

	///@name Constructors
	//@{
	//! Default constructor
	slice() : start(0), length(0), stride(0) { }

	//! construct slice from starting offset, length, and stride
	slice(size_t st, size_t len, ptrdiff_t str):
		start(st), length(len), stride(str) { }

	//! construct slice from size_range
	slice(range<size_t> ra); 
	//@}
};


} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_SLICE_HPP
