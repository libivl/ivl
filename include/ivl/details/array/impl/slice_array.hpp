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

#ifndef IVL_ARRAY_DETAILS_SLICE_ARRAY_HPP
#define IVL_ARRAY_DETAILS_SLICE_ARRAY_HPP

namespace ivl {

//-----------------------------------------------------------------------------

template<class A>
class slice_array
: public array<typename A::elem_type, data::slice<A> >
{
public:
	typedef slice_array this_type;
	typedef typename this_type::array_type base_class;

	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// convert temporary object to non-const reference
	this_type& ref() { return *this; }

	slice_array() { }
	slice_array(const this_type& o) : base_class(o.base()) { }
	template <class R>
	slice_array(const tuple<A&, const R&>& t)
		: base_class(t.v1, t.v2) { }

	//using base_class::operator=;
	this_type& operator=(const this_type& o)
	{
		base_class::operator=(o);
		return *this;
	}
	template<class K>
	this_type& operator=(const K& o)
	{
		base_class::operator=(o);
		return *this;
	}
};

//-----------------------------------------------------------------------------

template<class A>
class crange_array
: public array<typename A::elem_type, 
	data::ref_iterator<typename A::iterator, 
		typename A::const_iterator, 0, typename A::has_c_ptr> >
{
public:
	typedef crange_array this_type;
	typedef typename this_type::array_type base_class;

	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// convert temporary object to non-const reference
	this_type& ref() { return *this; }

	crange_array() { }
	crange_array(const this_type& o) : base_class(o.base()) { }
	template <class R>
	crange_array(const tuple<A&, const R&>& t)
		: base_class(t.v1.begin() + t.v2.first, t.v2.last - t.v2.first + 1) { }

	//using base_class::operator=;
	this_type& operator=(const this_type& o)
	{
		base_class::operator=(o);
		return *this;
	}
	template<class K>
	this_type& operator=(const K& o)
	{
		base_class::operator=(o);
		return *this;
	}
};

template<class A>
class crange_array<const A>
: public array<typename A::elem_type, 
	data::ref_iterator<types::not_a_type, 
		typename A::const_iterator, 0, typename A::has_c_ptr> >
{
public:
	typedef crange_array this_type;
	typedef typename this_type::array_type base_class;

	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// convert temporary object to non-const reference
	this_type& ref() { return *this; }

	crange_array() { }
	crange_array(const this_type& o) : base_class(o.base()) { }
	template <class R>
	crange_array(const tuple<const A&, const R&>& t)
		: base_class(t.v1.begin() + t.v2.first, t.v2.last - t.v2.first + 1) { }

	//using base_class::operator=;
	this_type& operator=(const this_type& o)
	{
		base_class::operator=(o);
		return *this;
	}
	template<class K>
	this_type& operator=(const K& o)
	{
		base_class::operator=(o);
		return *this;
	}
};

//-----------------------------------------------------------------------------

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_SLICE_ARRAY_HPP
