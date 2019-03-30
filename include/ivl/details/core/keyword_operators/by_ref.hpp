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

#ifndef IVL_CORE_DETAILS_OPERATION_RVAL_HPP
#define IVL_CORE_DETAILS_OPERATION_RVAL_HPP

namespace ivl {


///! normalize an output function argument.
///! allows subarrays and all other referencing arrays to be passed by
///! reference as output variables in functions.
/// This is actually a simple const-cast. Can't be avoided since
/// subarrays are normally temporary objects, and declaring them as
/// variables would be not good since the type of a subarray is too
/// complicated.
template <class A>
inline A& by_ref(const A& a) { return const_cast<A&>(a); }



}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_OPERATION_RVAL_HPP
