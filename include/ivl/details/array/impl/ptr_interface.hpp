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

#ifndef IVL_ARRAY_DETAILS_PTR_INTERFACE_HPP
#define IVL_ARRAY_DETAILS_PTR_INTERFACE_HPP

namespace ivl {

namespace array_details {

template<
	class A,
	class WRITEABLE = typename A::is_writeable,
	class HAS_C_PTR = typename A::has_c_ptr
>
struct ptr_interface
{
};

// non-const&, with c_ptr
template<class A>
struct ptr_interface<A, types::t_true, types::t_true>
{
public:
	typedef typename A::elem_type elem_type;
	elem_type* ptr;
	ptr_interface(A& a)
	{
		ptr = a.c_ptr();
	}
};

// const&, with c_ptr
template<class A>
struct ptr_interface<A, types::t_false, types::t_true>
{
public:
	typedef typename A::elem_type elem_type;
	const elem_type* ptr;
	ptr_interface(const A& a)
	{
		ptr = a.c_ptr();
	}
};

// non-const&, without c_ptr
template<class A>
struct ptr_interface<A, types::t_true, types::t_false>
{
	A& original; // this is a reference type

	//array<typename A::elem_type> temporary;
	// the below line could yield better performance than a single dim array in
	// copying from-to array_nd's.
	// in case seq_nd is faster loop in some types e.g. subarrays.
	// though this is not proven.
	typename types::normal_type<A>::type temporary;

public:
	typedef typename A::elem_type elem_type;
	elem_type* ptr;

	ptr_interface(A& a) : original(a), temporary(a)
	{
		ptr = temporary.c_ptr();
	}
	~ptr_interface()
	{
		original = temporary;
	}
};

// const&, without c_ptr
template<class A>
struct ptr_interface<A, types::t_false, types::t_false>
{
	const A& original; // this is a reference type

	//array<typename A::elem_type> temporary;
	// the below line could yield better performance than a single dim array in
	// copying from array_nd's.
	// in case seq_nd is faster loop in some types e.g. subarrays.
	// though this is not proven.
	typename types::normal_type<A>::type temporary;

public:
	typedef typename A::elem_type elem_type;
	const elem_type* ptr;

	ptr_interface(A& a) : original(a), temporary(a)
	{
		ptr = temporary.c_ptr();
	}
};

} /* namespace array_details */


/* This class provides a pointer interface to an existing array
of any type. If the array type has has_c_ptr = types::t_true,
the array is used as is, without copy. If not, a temporary array
is created, the data is copied from the original array and,
if the array type is not const, the
data is copied back to the original array at destruction. */

template <class A>
struct ptr_interface
: public array_details::ptr_interface<
	typename types::bare_type<A>::type,
	typename types::t_and<types::t_not<types::is_const<A> >,
		typename A::is_writeable>::type,
	typename A::has_c_ptr>
{
	typedef array_details::ptr_interface<
	typename types::bare_type<A>::type,
	typename types::t_and<types::t_not<types::is_const<A> >,
		typename A::is_writeable>::type,
	typename A::has_c_ptr> base_class;

	template <class X>
	ptr_interface(X& a) : base_class(a) { }
};

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_PTR_INTERFACE_HPP
