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

#ifndef IVL_ARRAY_DETAILS_COMMON_FWD_DECL_HPP
#define IVL_ARRAY_DETAILS_COMMON_FWD_DECL_HPP

namespace ivl {


//forward declarations


//class size_range;
class index_array;
struct index_array_all_type;

template<class T> class range;
template<class T> class crange;

/*template<class T, class S> class slice_array;
template<class T, class S, bool is_const> class resizable_slice_array;
template<class T, class S> class indirect_array;
template<class T, class S, bool is_const> class resizable_indirect_array;
template<class T, class S> class mask_array;
template<class T, class S, bool is_const> class resizable_mask_array;
*/
template<class T, bool B> class all_array;

template<class T, class S, bool C> class sub_array;


template<class T, class S> class array;



// forward declarations

/*! array of size_t */
typedef array<size_t, mem> size_array;

/*! array of bool */
typedef array<bool, mem> bool_array;



template <class T, class S, class J, class D>
void copy(array<T, S>& out, const array<J, D>& in);

template <class T, class S, class J, class D>
void copy_out(array<T, S>& out, const array<J, D>& in);

template <class T, class S, class J, class D>
void copy_n(array<T, S>& out, const array<J, D>& in, int n);

template <class T, class S, class J>
void copy(array<T, S>& out, const J* it_src);

template <class T, class S>
void copy(array<T, S>& out, const T& val,
		types::term as_element = types::term());


//forward declaration of function
template <class T, class S, class D>
bool isequal(const array<T, S>& a, const array<T, D>& b);


template <class T, class S>
std::ostream& print(std::ostream& os, const ivl::array<T, S>& in);


} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_COMMON_FWD_DECL_HPP
