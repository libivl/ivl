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

#ifndef IVL_ARRAY_ND_DETAILS_IMPL_ITER_ARRAY_ND_HPP
#define IVL_ARRAY_ND_DETAILS_IMPL_ITER_ARRAY_ND_HPP

namespace ivl {

template<class A>
array_nd<typename A::elem_type, const_link>
	const_iter_array_nd(const A& a)
{
	return array_nd<typename A::elem_type, const_link>(a);
}

template<class A>
array_nd<typename A::elem_type, const_link>
	iter_array_nd(const A& a)
{
	return array_nd<typename A::elem_type, const_link>(a);
}

template<class A>
array_nd<typename A::elem_type, rw_link>
	iter_array_nd(A& a)
{
	return array_nd<typename A::elem_type, rw_link>(a);
}

// ----

template<class A, class S>
array_nd<typename A::elem_type, const_link>
	const_iter_array_nd(const A& a, const array<size_t, S>& sz)
{
	array_nd<typename A::elem_type, const_link> r(sz);
	r.setref(a);
	return r;
}

template<class A, class S>
array_nd<typename A::elem_type, const_link>
	iter_array_nd(const A& a, const array<size_t, S>& sz)
{
	array_nd<typename A::elem_type, const_link> r(sz);
	r.setref(a);
	return r;
}

template<class A, class S>
array_nd<typename A::elem_type, rw_link>
	iter_array_nd(A& a, const array<size_t, S>& sz)
{
	array_nd<typename A::elem_type, rw_link> r(sz);
	r.setref(a);
	return r;
}

// ----

template<class T, class S>
array_nd<T, const_link>
	const_iter_array_nd(const T* a, const array<size_t, S>& sz)
{
	array_nd<T, const_link> r(sz);
	r.setref(a, ivl::prod(sz));
	return r;
}

template<class T, class S>
array_nd<T, const_link>
	iter_array_nd(const T* a, const array<size_t, S>& sz)
{
	array_nd<T, const_link> r(sz);
	r.setref(a, ivl::prod(sz));
	return r;
}

template<class T, class S>
array_nd<T, rw_link>
	iter_array_nd(T* a, const array<size_t, S>& sz)
{
	array_nd<T, rw_link> r(sz);
	r.setref(a, ivl::prod(sz));
	return r;
}

} /* namespace ivl */

#endif // IVL_ARRAY_ND_DETAILS_IMPL_ITER_ARRAY_ND_HPP
