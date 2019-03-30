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

#ifndef IVL_ARRAY_DETAILS_ITER_ARRAY_HPP
#define IVL_ARRAY_DETAILS_ITER_ARRAY_HPP

namespace ivl {


template<class T, int N>
array<T, rw_link> lnk(T (&a)[N])
{
        return array<T, rw_link>(N, a);
}

template<class T, int N>
array<T, const_link> lnk(const T (&a)[N])
{
	return array<T, const_link>(N, a);
}

//
#if 0

template<class A>
array<typename A::elem_type, const_link>
	const_iter_array(const A& a)
{
	return array<typename A::elem_type, const_link>(a);
}

template<class A>
array<typename A::elem_type, const_link>
	iter_array(const A& a)
{
	return array<typename A::elem_type, const_link>(a);
}

template<class A>
array<typename A::elem_type, rw_link>
	iter_array(A& a)
{
	return array<typename A::elem_type, rw_link>(a);
}

// ----

template<class A>
array<typename A::elem_type, const_link>
	const_iter_array(const A& a, size_t l)
{
	return array<typename A::elem_type, const_link>(l, a);
}

template<class A>
array<typename A::elem_type, const_link>
	iter_array(const A& a, size_t l)
{
	return array<typename A::elem_type, const_link>(l, a);
}

template<class A>
array<typename A::elem_type, rw_link>
	iter_array(A& a, size_t l)
{
	return array<typename A::elem_type, rw_link>(l, a);
}

// ----

template<class T>
array<T, typename const_link>
	const_iter_array(const T* a, size_t l)
{
	return array<T, const_link> r(a, l);
}

template<class T>
array<T, typename const_link>
	iter_array(const T* a, size_t l)
{
	return array<T, const_link> r(a, l);
}

template<class T>
array<T, typename rw_link>
	iter_array(T* a, size_t l)
{
	return array<T, rw_link> r(a, l);
}


/*
template<class CONST_IT>
array<typename CONST_IT::value_type,
	typename data::ref_iterator<0, CONST_IT, types::term>::type>
	const_iter_array(const CONST_IT& it)
{
	return array<typename CONST_IT::value_type,
	typename data::ref_iterator_traits<0, CONST_IT, types::term>::type>(it);
}

template<class IT>
array<typename IT::value_type,
	typename data::ref_iterator<0, IT, types::term>::type>
	iter_array(const IT& it)
{
	return array<typename IT::value_type,
	typename data::ref_iterator_traits<0, IT, types::term>::type>(it);
}
*/

#if 0
// well written definitions
template
<
class T,
class CONST_IT,
int N = 0,
class DATA_CLASS_SET = typename
	data::ref_iterator_traits<N, CONST_IT, types::term>::type
>
class const_iter_array :
	public
	array<T, DATA_CLASS_SET, types::term>
{
public:
	typedef const_iter_array this_type;

	typedef array<T, DATA_CLASS_SET, types::term> base_class;

	const_iter_array(const CONST_IT& it) : base_class(it) { }

	const_iter_array(const CONST_IT& it, const CONST_IT& e)
	: base_class(it, e - it, e) { }

	const_iter_array(const CONST_IT& it, int n)
	: base_class(it, n, it + n) { }

	using base_class::operator=;
	this_type& operator = (const this_type& o) {
		return base_class::operator=(o);
	}

};


template
<
class T,
class IT,
class CONST_IT,
int N = 0,
class DATA_CLASS_SET = typename
	data::ref_iterator_traits<N, IT, CONST_IT>::type
>
class iter_array :
	public
	array<T, DATA_CLASS_SET, types::term>
{
public:
	typedef iter_array this_type;

	typedef array<T, DATA_CLASS_SET,
		typename types::derive<this_type>::type> base_class;

	iter_array(const IT& it) : base_class(it) { }

	iter_array(const IT& it, const IT& e) : base_class(it, e - it, e) { }

	iter_array(const IT& it, int n) : base_class(it, n, it + n) { }

	using base_class::operator=;
	this_type& operator = (const this_type& o) {
		return base_class::operator=(o);
	}
};
#endif
#endif


}; /*namespace ivl*/

#endif // IVL_ARRAY_DETAILS_TUPLE_HPP
