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

#ifndef IVL_CORE_DETAILS_RVALUE_HPP
#define IVL_CORE_DETAILS_RVALUE_HPP

namespace ivl {

#if 1
template<class DERIVED>
class rvalue_base
: public types::rvalue_identifier,
public tuple_rvalue<rvalue_base<DERIVED> >
{
private:
	typedef DERIVED derived_type;

public:
	rvalue_base() {}

	const derived_type& derived() const
		{ return static_cast<const derived_type&>(*this); }

	derived_type& derived()
		{ return static_cast<derived_type&>(*this); }

	template<class T>
	void tuple_output(T& t) const
	{
		apply_tuple_output(t, derived());
	}


	/*
	template<class T>
	void tuple_output(T& t)
	{

	}
	*/
};


template<class CONV, class DERIVED>
class rvalue_output_converter
: public rvalue_base<DERIVED>
{
private:
	typedef rvalue_output_converter<CONV, DERIVED> this_type;
	typedef DERIVED derived_type;

public:
	typedef CONV conv_type;

	rvalue_output_converter() {}

	const derived_type& derived() const
		{ return static_cast<const derived_type&>(*this); }

	derived_type& derived()
		{ return static_cast<derived_type&>(*this); }
};


template <class DERIVED>
class rvalue
: public rvalue_base<DERIVED>
{
public:
	rvalue() {}
};

#endif

}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_RVALUE_HPP
