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

#ifndef IVL_CORE_DETAILS_TYPES_EXTRACTION_HPP
#define IVL_CORE_DETAILS_TYPES_EXTRACTION_HPP

namespace ivl {
namespace types {

// identity type
template <class T>
struct t_id { typedef T type; };

/*
Template types extraction.
Helps us extract a desired parameter
from a template class.
*/


template<int I, class F>
struct get_templ_arg { };

// get the type T itself for a non-template class.
template<class T>
struct get_templ_arg<1, T> { typedef T type; };

// classes of 2 class arguments
template<template<typename, typename> class F,
class T1, class T2>
struct get_templ_arg<1, F<T1, T2> > { typedef T1 type; };

template<template<typename, typename> class F,
class T1, class T2>
struct get_templ_arg<2, F<T1, T2> > { typedef T2 type; };

// classes of 3 class arguments
template<template<typename, typename, typename> class F,
class T1, class T2, class T3>
struct get_templ_arg<1, F<T1, T2, T3> > { typedef T1 type; };

template<template<typename, typename, typename> class F,
class T1, class T2, class T3>
struct get_templ_arg<2, F<T1, T2, T3> > { typedef T2 type; };

template<template<typename, typename, typename> class F,
class T1, class T2, class T3>
struct get_templ_arg<3, F<T1, T2, T3> > { typedef T3 type; };

// classes of 4 class arguments
template<template<typename, typename, typename, typename> class F,
class T1, class T2, class T3, class T4>
struct get_templ_arg<1, F<T1, T2, T3, T4> > { typedef T1 type; };

template<template<typename, typename, typename, typename> class F,
class T1, class T2, class T3, class T4>
struct get_templ_arg<2, F<T1, T2, T3, T4> > { typedef T2 type; };

template<template<typename, typename, typename, typename> class F,
class T1, class T2, class T3, class T4>
struct get_templ_arg<3, F<T1, T2, T3, T4> > { typedef T3 type; };

template<template<typename, typename, typename, typename> class F,
class T1, class T2, class T3, class T4>
struct get_templ_arg<4, F<T1, T2, T3, T4> > { typedef T4 type; };





} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_EXTRACTION_HPP
