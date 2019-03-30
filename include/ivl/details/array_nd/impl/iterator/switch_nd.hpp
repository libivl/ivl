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

#ifndef IVL_ARRAY_ND_DETAILS_IMPL_ITERATOR_SWITCH_ND_HPP
#define IVL_ARRAY_ND_DETAILS_IMPL_ITERATOR_SWITCH_ND_HPP

namespace ivl {

namespace array_nd_details {
/*
template <class T, class IS_AR>
struct switch_nd_op {};

template <class T, class IS_AR>
struct switch_nd_op<T, types::t_true>
{
	template <class A, class IT>
	static inline T get(A& a, const IT& it, int d) { return T(a->size(d), it); }
};

template <class T, class IS_AR>
struct switch_nd_op<T, types::t_false>
{
	template <class A, class IT>
	static inline T get(A& a, const IT& it, int d) { return *it; }
};
*/
} /* namespace array_nd_details */

template<class T, class IT, class A, int D>
class switch_nd
{
	A* a;
	IT it;
public:
	typedef std::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef typename IT::difference_type difference_type;
	typedef internal::pointer_face<T> pointer;
	typedef internal::reference_face<T, switch_nd> reference;

	typedef switch_nd this_type;

	// constructors
	switch_nd() { }
	switch_nd(const switch_nd& o) : it(o.it), a(o.a) { }
	//template<int D2>
	//switch_nd(const switch_nd<T, IT, A, D2>& o) : it(o.it), a(o.a) { }

	switch_nd(const IT& it, A& a) : it(it), a(a) { }

	reference operator*() const
		{ return reference(T(a->size(D), a->_begin(D, it)), *this); }

	reference operator[](size_t j) const
		{ return it[j]; }

	pointer operator->() const
		{ return pointer(*this, T(a->size(D), a->_begin(D, it))); }


	// increment-decrement
	this_type& operator++() { ++it; return *this; }
	this_type& operator--() { --it; return *this; }

	this_type operator++(int)
		{ this_type tmp(*this); ++it; return tmp; }

	this_type operator--(int)
		{ this_type tmp(*this); --it; return tmp; }

	// random access
	this_type operator +(const typename IT::difference_type j) const
		{ this_type tmp(it + j, a); return tmp; }

	this_type operator -(const typename IT::difference_type j) const
		{ this_type tmp(it - j, a); return tmp; }

	this_type& operator +=(const typename IT::difference_type j)
		{ it += j; return *this; }

	this_type& operator -=(const typename IT::difference_type j)
		{ it -= j; return *this; }

	// difference
	typename IT::difference_type operator -(const this_type& a) const
		{ return it - a.it; }

	// comparing
	bool operator==(const this_type& o) const { return it == o.it; }
	bool operator!=(const this_type& o) const { return it != o.it; }
	bool operator<(const this_type& o) const { return it < o.it; }
	bool operator<=(const this_type& o) const
		{ return ((*this < it) || (*this == it)); }
	bool operator>(const this_type& o) const
		{ return ((!(*this < it)) && (!(*this == it))); }
	bool operator>=(const this_type& o) const { return !(*this < it); }
};

} /* namespace ivl */

#endif // IVL_ARRAY_ND_DETAILS_IMPL_ITERATOR_SWITCH_ND_HPP


