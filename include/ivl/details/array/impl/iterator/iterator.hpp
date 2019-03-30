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

#ifndef IVL_CORE_DETAILS_ITERATOR_ITERATOR_HPP
#define IVL_CORE_DETAILS_ITERATOR_ITERATOR_HPP


namespace ivl {

// forward declaration of array_nd
template <class X, class Y> class array_nd;

namespace data {

namespace data_details {

// expands an iterator class that has a defined base() member with
// const and, if possible, non-const, arrow(->) and dereference(*)
// operators.
// This class is used to avoid specializing iterators as const and mon-const.
template <class C, class T, bool CONST = false, class REF = T&>
class iter_operator_expander
{
};

template <class C, class T, class REF>
class iter_operator_expander<C, T, false, REF>
{
protected:
	C& derived() { return static_cast<C&>(*this); }
	const C& derived() const { return static_cast<const C&>(*this); }

public:
	//! arrow operator
	T* operator ->() { return &(derived().base()); }
	//! const arrow operator
	const T* operator ->() const { return &(derived().base()); }

	//! dereference iterator
	REF operator *() { return (derived().base()); }
	//! const dereference iterator
	typename types::apply_const<REF>::type operator *() const
		{ return (derived().base()); }
};

template <class C, class T, class REF>
class iter_operator_expander<C, T, true, REF>
{
protected:
	const C& derived() const { return static_cast<const C&>(*this); }

public:
	//! const arrow operator
	const T* operator ->() const { return &(derived().base()); }

	//! const dereference iterator
	typename types::apply_const<REF>::type // TODO:This does not result to const T&!!!!
		operator *() const { return (derived().base()); }
};


// expands an iterator that has a defined base() and base(size_t) members with
// const and, if possible, non-const, arrow(->), dereference(*) and []
// (random access) operators.
// This class is used to avoid specializing iterators as const and mon-const.
template <class C, class T, bool CONST = false, class REF = T&>
class rnd_iter_operator_expander
{
};

template <class C, class T, class REF>
class rnd_iter_operator_expander<C, T, false, REF>
	: public iter_operator_expander<C, T, false, REF>
{
private:
	friend class iter_operator_expander<C, T, false, REF>;

protected:
	using iter_operator_expander<C, T, false, REF>::derived;

public:
	//! random access
	REF operator [](size_t j) { return (derived().base(j)); }
	//! const random access
	typename types::apply_const<REF>::type operator [](size_t j) const
		{ return (derived().base(j)); }
};

template <class C, class T, class REF>
class rnd_iter_operator_expander<C, T, true, REF>
	: public iter_operator_expander<C, T, true, REF>
{
protected:
	using iter_operator_expander<C, T, true, REF>::derived;

public:
	//! const random access
	typename types::apply_const<REF>::type operator [](size_t j) const
		{ return (derived().base(j)); }
};

} /* namespace data_details */

template <class T, class OWNER, bool CONST = false, class REF = T&>
class index_iterator //: public std::iterator_traits<T*>
	:
	public data_details::
		rnd_iter_operator_expander<
			index_iterator<T, OWNER, CONST, REF>, T, CONST, REF>,
	public
		types::t_if<types::is_ivl_array<OWNER>, types::
		ivl_array_reference_based_iterator_identifier, types::term>::type,
	public
		types::past_end_capable_iterator_identifier
{
private:
	template <class X, class Y, bool C, class R> friend class index_iterator;

	friend class data_details::iter_operator_expander
		<index_iterator<T, OWNER, CONST, REF>, T, CONST, REF>;

	typedef typename types::apply_const<T, types::t_expr<CONST> >
		::type best_value_type;

	typedef typename types::apply_const<REF, types::t_expr<CONST> >
		::type best_ref_type;

	// this struct is used to disable specific specialization members
	struct not_a_type { OWNER* o; size_t i; operator size_t() { return 0; } };

	typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
		types::code_word<> >::type invalid_if_const;

	OWNER* o;
	size_t i;

protected:
	inline const REF base(
		types::code_word<> ok = types::code_word<>()) const
		{ return (*o)[i]; }

	inline best_ref_type base(
		invalid_if_const disable = invalid_if_const())
		{ return (*o)[i]; }

	inline const REF base(size_t j,
		types::code_word<> ok = types::code_word<>()) const
		{ return (*o)[i + j]; }

	inline best_ref_type base(size_t j,
		invalid_if_const disable = invalid_if_const())
		{ return (*o)[i + j]; }


public:
	typedef index_iterator<T, OWNER, CONST, REF> this_type;

	// iterator_traits
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef best_value_type* pointer;
	typedef best_ref_type reference;

	// constructors
	index_iterator() { }
	index_iterator(const this_type& it) : o(it.o), i(it.i) { }
	template <bool C>
	index_iterator(const index_iterator<T, OWNER, C, REF>& it)
		: o(it.o), i(it.i) { }

	index_iterator(OWNER& owner, size_t pos) : o(&owner), i(pos) { }

	OWNER& owner() { return *o; }
	const OWNER& owner() const { return *o; }

	// members

	// increment-decrement
	this_type& operator++() { ++i; return *this; }
	this_type& operator--() { --i; return *this; }

	this_type operator++(int) { this_type tmp(*this); i++; return tmp; }
	this_type operator--(int) { this_type tmp(*this); i--; return tmp; }

	// random access
	this_type operator +(const size_t j) const
		{ this_type tmp(o, i + j); return tmp; }
	this_type operator -(const size_t j) const
		{ this_type tmp(o, i - j); return tmp; }
	this_type& operator +=(const size_t j) { i += j; return *this; }
	this_type& operator -=(const size_t j) { i -= j; return *this; }

	// difference
	difference_type operator -(const index_iterator& a) const {
		return difference_type(i - a.i);
	}

	//copy same type iterator
	this_type& operator=(const this_type& it) { o = it->o; i = it->i; return *this; }
	//copy relevant type iterator
	template<bool C>
	this_type& operator=(const index_iterator<T, OWNER, C>& it)
		{ o = it->o; i = it->i; return *this; }

	bool operator==(const this_type& it) const { return (o == it.o) && (i == it.i); }
	bool operator!=(const this_type& it) const { return (i != it.i) || (o != it.o); }
	bool operator<(const this_type& it) const { return (i < it.i); }
	bool operator<=(const this_type& it) const { return (i <= it.i); }
	bool operator>(const this_type& it) const { return (i > it.i); }
	bool operator>=(const this_type& it) const { return (i >= it.i); }
};


template <class T, bool CONST>
class ptr_iterator //: public std::iterator_traits<T*>
	: public data_details::
		rnd_iter_operator_expander<ptr_iterator<T, CONST>, T, CONST>,
	public
		types::pointer_based_iterator_identifier,
	public
		types::past_end_capable_iterator_identifier
{
private:
	template <class X, bool Y> friend class ptr_iterator;

	template <class X, class Y, bool C, class Z>
	friend class data_details::rnd_iter_operator_expander;
	template <class X, class Y, bool C, class Z>
	friend class data_details::iter_operator_expander;

    typedef typename types::apply_const<T, types::t_expr<CONST> >
		::type best_value_type;

    typedef typename types::apply_const<T&, types::t_expr<CONST> >
		::type best_ref_type;

	// this struct is used to disable specific specialization members
	struct not_a_type { T* ptr; operator size_t() { return 0; } };

	typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
		types::code_word<> >::type invalid_if_const;

	best_value_type* ptr;

protected:
	inline const T& base(
		types::code_word<> ok = types::code_word<>()) const
		{ return *ptr; }

	inline best_ref_type base( // TODO:this does not result to T& !!!
		invalid_if_const disable = invalid_if_const())
		{ return *ptr; }

	inline const T& base(size_t j,
		types::code_word<> ok = types::code_word<>()) const
		{ return ptr[j]; }

	inline best_ref_type base(size_t j,
		invalid_if_const disable = invalid_if_const())
		{ return ptr[j]; }

public:
	typedef ptr_iterator<T, CONST> this_type;

	// iterator_traits
    typedef std::random_access_iterator_tag iterator_category;
    typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef best_value_type* pointer;
	typedef best_value_type& reference;

	typedef ptrdiff_t iter_border_walker;

	// constructors
	ptr_iterator() { ptr = 0; }
	ptr_iterator(const this_type& it) : ptr(it.ptr) { }
	template <bool C>
	ptr_iterator(const ptr_iterator<T, C>& it) : ptr(it.ptr) { }
	ptr_iterator(pointer ptrdata) : ptr(ptrdata) { }

	// members

	// increment-decrement
	this_type& operator++() { ++ptr; return *this; }
	this_type& operator--() { --ptr; return *this; }

	this_type operator++(int) { this_type tmp(*this); ptr++; return tmp; }
	this_type operator--(int) { this_type tmp(*this); ptr--; return tmp; }

	// random access
	this_type operator +(const difference_type j) const { this_type tmp(ptr + j); return tmp; }
	this_type operator -(const difference_type j) const { this_type tmp(ptr - j); return tmp; }
	this_type& operator +=(const difference_type j) { ptr+=j; return *this; }
	this_type& operator -=(const difference_type j) { ptr-=j; return *this; }

	// difference
	difference_type operator -(const ptr_iterator& a) const { return (ptr - a.ptr); }

	// copy same type operator
	this_type& operator=(const this_type& it) { ptr = it.ptr; return *this; }
	// copy relevant type operator
	template <bool C>
	this_type& operator=(const ptr_iterator<T, C>& it) { ptr = it.ptr; return *this; }

	bool operator==(const this_type& it) const { return (ptr == it.ptr); }
	bool operator!=(const this_type& it) const { return (ptr != it.ptr); }
	bool operator<(const this_type& it) const { return (ptr < it.ptr); }
	bool operator<=(const this_type& it) const { return (ptr <= it.ptr); }
	bool operator>(const this_type& it) const { return (ptr > it.ptr); }
	bool operator>=(const this_type& it) const { return (ptr >= it.ptr); }
};



} /*namespace data */

} /*namespace ivl */

#endif // IVL_CORE_DETAILS_ITERATOR_ITERATOR_HPP
