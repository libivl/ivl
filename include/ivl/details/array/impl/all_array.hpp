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

#ifndef IVL_ARRAY_DETAILS_ALL_ARRAY_HPP
#define IVL_ARRAY_DETAILS_ALL_ARRAY_HPP

namespace ivl {

template<class A, bool IS_CONST>
class all_array
: public array<typename A::elem_type,
	data::ref_iterator<
		typename types::t_if<types::t_expr<IS_CONST>, types::term,
			typename A::iterator>::type,
		typename A::const_iterator> >
{
private:
	typedef all_array prv_this_type;
	typedef typename prv_this_type::array_type base_class;

public:
	all_array(typename
		types::t_if<types::t_expr<IS_CONST>, const A&, A&>::type a)
		: base_class(a.begin(), a.length(), a.end()) { }

	all_array(const all_array& o) : base_class(o) { }

	//using base_class::operator=;

/* No need for this anymore. The correct thing happens with operator=
automatically as long as it detects that iter_array is not resizeable
	all_array& operator=(const typename A::elem_type& val)
	{
		base_class::operator=(array<typename A::elem_type,
				data::ref_val_repeat, types::term>(this->length(), val));
		return *this;
	}
*/
	template<class K>
	all_array& operator=(const K& k)
	{
		base_class::operator=(k);
		return *this;
	}

	all_array& operator=(const all_array& o)
	{
		base_class::operator=(o);
		return *this;
	}
};


} // namespace ivl

#endif // IVL_ARRAY_DETAILS_ALL_ARRAY_HPP
