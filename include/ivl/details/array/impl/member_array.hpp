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

#ifndef IVL_ARRAY_DETAILS_MEMBER_ARRAY_HPP
#define IVL_ARRAY_DETAILS_MEMBER_ARRAY_HPP

namespace ivl {

template<class A, class B>
class member_array
: public array<B, data::member<A, B> >
{
public:
	typedef member_array this_type;
	typedef typename this_type::array_type base_class;

	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// convert temporary object to non-const reference
	this_type& ref() { return *this; }

	member_array() { }
	member_array(const this_type& o) : base_class(o.base()) { }
	template<class P>
	member_array(const tuple<A&, P>& t)
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

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_MEMBER_ARRAY_HPP
