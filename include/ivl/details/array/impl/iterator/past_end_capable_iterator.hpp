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

#ifndef IVL_ARRAY_DETAILS_ITERATOR_PAST_END_CAPABLE_ITERATOR_HPP
#define IVL_ARRAY_DETAILS_ITERATOR_PAST_END_CAPABLE_ITERATOR_HPP

namespace ivl {

namespace data {

template<class IT>
class past_end_capable_iterator
{
protected:
	IT base_it;
	ptrdiff_t npos;

	template <class F> friend class past_end_capable_iterator;

public:
	// note about this iterator:
	// on differences, equalities etc. considers that the base is
	// always the beginning, and that it is the same among operands.
	// this disables us from using rbegin based iterators as reference,
	// and compare them to begin based ones.

	typedef past_end_capable_iterator this_type;

	// iterator_traits
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename IT::value_type value_type;
	typedef ptrdiff_t difference_type;
	typedef typename IT::pointer pointer;
	typedef typename IT::reference reference;

	typedef ptrdiff_t iter_border_walker;

	// constructors
	past_end_capable_iterator() { }
	// constructor with the iterator and the position of 
	// the iterator from begin()
	past_end_capable_iterator(const IT& it, ptrdiff_t nps)
		: base_it(it), npos(nps) { }
	// constructor with the iterator for begin() only. possibly faster.
	past_end_capable_iterator(int, const IT& it)
		: base_it(it), npos(0) { }
	// copy constructors
	past_end_capable_iterator(const past_end_capable_iterator& it)
		: base_it(it.base_it) { npos = it.npos; }
	template <class O>
	past_end_capable_iterator(const past_end_capable_iterator<O>& it)
		: base_it(it.base_it) { npos = it.npos; }

	// members

	//TODO: nat yet: operator IT() const { return base_it + npos; }

	const IT& begin_pos() const { return base_it; }

	// dereference
	value_type* operator ->() { return (base_it + npos).operator ->(); }

	reference operator*() { return base_it[npos]; }

	reference operator*() const { return base_it[npos]; }

	reference operator[] (ptrdiff_t i) { return base_it[i + npos]; }

	reference operator[] (ptrdiff_t i) const { return base_it[i + npos]; }

	// increment-decrement
	this_type& operator++() { ++npos; return *this; }
	this_type& operator--() { --npos; return *this; }

	this_type operator++(int) { this_type tmp(*this); npos++; return tmp; }
	this_type operator--(int) { this_type tmp(*this); npos--; return tmp; }

	// random access
	this_type operator +(const difference_type j) const
		{ this_type tmp(base_it, npos + j); return tmp; }
	this_type operator -(const difference_type j) const
		{ this_type tmp(base_it, npos - j); return tmp; }
	this_type& operator +=(const difference_type j) { npos+=j; return *this; }
	this_type& operator -=(const difference_type j) { npos-=j; return *this; }

	// difference
	difference_type operator -(const this_type& a) const
		{ return (npos - a.npos); }

	// copy same type operator
	this_type& operator=(const this_type& it)
		{ base_it = it.base_it; npos = it.npos; return *this; }
	// copy relevant type operator
	template <class O>
	this_type& operator=(const past_end_capable_iterator<O>& it)
		{ base_it = it.base_it; npos = it.npos; return *this; }

	bool operator==(const this_type& it) const { return (npos == it.npos); }
	bool operator!=(const this_type& it) const { return (npos != it.npos); }
	bool operator<(const this_type& it) const { return (npos < it.npos); }
	bool operator<=(const this_type& it) const { return (npos <= it.npos); }
	bool operator>(const this_type& it) const { return (npos > it.npos); }
	bool operator>=(const this_type& it) const { return (npos >= it.npos); }

};

} /* namespace data */


template<class IT>
class auto_past_end_capable_iterator
{
protected:
	IT base_it;
	ptrdiff_t npos;

	template <class F> friend class auto_past_end_capable_iterator;

public:
	// note about this iterator:
	// on differences, equalities etc. considers that the base is
	// always the beginning, and that it is the same among operands.
	// this disables us from using rbegin based iterators as reference,
	// and compare them to begin based ones.

	typedef auto_past_end_capable_iterator this_type;

	// iterator_traits
    typedef std::random_access_iterator_tag iterator_category;
    typedef typename IT::value_type value_type;
	typedef ptrdiff_t difference_type;
	typedef typename IT::pointer pointer;
	typedef typename IT::reference reference;

	typedef ptrdiff_t iter_border_walker;

	// constructors
	auto_past_end_capable_iterator() { }
	auto_past_end_capable_iterator(const IT& it)
		: base_it(it), npos(0) { }
	auto_past_end_capable_iterator(const IT& it, ptrdiff_t n)
		: base_it(it), npos(n) { }

	auto_past_end_capable_iterator(const auto_past_end_capable_iterator& it)
		: base_it(it.base_it) { npos = it.npos; }
	template <class O>
	auto_past_end_capable_iterator(const auto_past_end_capable_iterator<O>& it)
		: base_it(it.base_it) { npos = it.npos; }

	// members
	operator IT() const { return base_it + npos; }

	//const IT& begin_pos() const { return base_it; }

	// dereference
	value_type* operator ->() { return (base_it + npos).operator ->(); }

	reference operator*() { return base_it[npos]; }

	reference operator*() const { return base_it[npos]; }

	reference operator[] (ptrdiff_t i) { return base_it[i + npos]; }

	reference operator[] (ptrdiff_t i) const { return base_it[i + npos]; }

	// increment-decrement
	this_type& operator++() { ++npos; return *this; }
	this_type& operator--() { --npos; return *this; }

	this_type operator++(int) { this_type tmp(*this); npos++; return tmp; }
	this_type operator--(int) { this_type tmp(*this); npos--; return tmp; }

	// random access
	this_type operator +(const difference_type j) const
		{ this_type tmp(base_it, npos + j); return tmp; }
	this_type operator -(const difference_type j) const
		{ this_type tmp(base_it, npos - j); return tmp; }
	this_type& operator +=(const difference_type j) { npos+=j; return *this; }
	this_type& operator -=(const difference_type j) { npos-=j; return *this; }

	// difference
	difference_type operator -(const this_type& a) const
		{ return (base_it - a.base_it + npos - a.npos); }

	// copy same type operator
	this_type& operator=(const this_type& it)
		{ base_it = it.base_it; npos = it.npos; return *this; }
	// copy relevant type operator
	template <class O>
	this_type& operator=(const auto_past_end_capable_iterator<O>& it)
		{ base_it = it.base_it; npos = it.npos; return *this; }

	bool operator==(const this_type& it) const 
		{ return (base_it - it.base_it + npos == it.npos); }
	bool operator!=(const this_type& it) const 
		{ return (base_it - it.base_it + npos != it.npos); }
	bool operator<(const this_type& it) const 
		{ return (base_it - it.base_it + npos < it.npos); }
	bool operator<=(const this_type& it) const 
		{ return (base_it - it.base_it + npos <= it.npos); }
	bool operator>(const this_type& it) const 
		{ return (base_it - it.base_it + npos > it.npos); }
	bool operator>=(const this_type& it) const 
		{ return (base_it - it.base_it + npos >= it.npos); }

};


} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_ITERATOR_PAST_END_CAPABLE_ITERATOR_HPP
