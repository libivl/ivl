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

#ifndef IVL_CORE_DETAILS_COMMON_FWD_DECL_HPP
#define IVL_CORE_DETAILS_COMMON_FWD_DECL_HPP

namespace ivl {

// forward declarations. no way to avoid them, because there is recursivity
template<class T, class S> class array;
template<class T, class S> class array_nd;

// iavr: array_2d decl. needed by elem_ref in core/types/types.hpp
template<class T, class S> class array_2d;

class index_array;

/*
template <class T, class S, class K, class J, class D, class P>
void copy(array<T, S, K>& out, const array<J, D, P>& in);

template <class T, class S, class K, class J, class D, class P>
void copy_out(array<T, S, K>& out, const array<J, D, P>& in);

template <class T, class S, class K, class J, class D, class P>
void copy_n(array<T, S, K>& out, const array<J, D, P>& in, int n);

template <class T, class S, class K, class J>
void copy(array<T, S, K>& out, const J* it_src);

template <class T, class S, class K>
void copy(array<T, S, K>& out, const T& val);
*/

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_COMMON_FWD_DECL_HPP
