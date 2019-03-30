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

#ifndef IVL_ARRAY_DETAILS_WRAP_STL_HPP
#define IVL_ARRAY_DETAILS_WRAP_STL_HPP

namespace ivl {

template <class C>
class wrap_stl
:
public
	array<
	typename C::value_type,
	typename data::ref_iterator<typename types::t_if<types::is_const<C>,
			types::term, typename C::iterator>::type,
		typename C::const_iterator, 0>::type>
{
public:
	typedef wrap_stl this_type;
	typedef typename this_type::container_type base_class;

	wrap_stl(C& c) : base_class(c.begin(), c.size(), c.end()) { }
};

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_WRAP_STL_HPP
