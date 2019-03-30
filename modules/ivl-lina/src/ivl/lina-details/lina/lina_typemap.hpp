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

#ifndef IVL_LINA_DETAILS_LINA_TYPEMAP_HPP
#define IVL_LINA_DETAILS_LINA_TYPEMAP_HPP

#if 0
#include<complex>

namespace ivl {
namespace lina_details {


template<class KEY> struct type_map { typedef KEY type; };
/*
 * This struct saves me some class specializations. There are cases where we
 * have lapack routines that requires 4 clapack::real argument as input and
 * the complex version of the very same routine requires 3 complex and 1 real.
 * Instead of reimplementing the whole class we simply use a typemap that
 * depends on the template parameter T and leads to different behaviour for
 * different template types...
 */

template<class T>
struct type_map<std::complex<T> > { typedef T type; };

} /* namespace lina_details */
} /* namespace ivl */

#endif

#endif // IVL_LINA_DETAILS_LINA_TYPEMAP_HPP
