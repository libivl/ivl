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

#ifndef IVL_ARRAY_2D_DETAILS_ARRAY_2D_BASE_HPP
#define IVL_ARRAY_2D_DETAILS_ARRAY_2D_BASE_HPP

namespace ivl {

template<class T, class D> class array_2d;
typedef array_2d<bool, mem> bool_array_2d;
/*
template<class T> std::ostream& print(std::ostream& os, const array_2d<T, mem>& in);
*/

#include "specialization/array_2d_class.hpp"
//#include "specialization/unary_elem_func_class.hpp"
//#include "specialization/binary_elem_func_class.hpp"
//#include "specialization/subarray_class.hpp"

/*
template <class T>
inline
std::ostream& print(std::ostream& os, const array_2d<T>& in)
{
	return print_array_nd(os, in);
}
*/

} // namespace ivl

#endif // IVL_ARRAY_ND_DETAILS_ARRAY_ND_BASE_HPP
