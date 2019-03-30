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

#ifndef IVL_CORE_DETAILS_DATA_CONVERSIONS_ARRAY_ND_HPP
#define IVL_CORE_DETAILS_DATA_CONVERSIONS_ARRAY_ND_HPP

// This file is a sequel to conversions_array.hpp
// It is exactly the same thing, but for data types that were not
// included at all, when including array.hpp
// Those data types are only defined when including array_nd.hpp.
// When used in simple array<> classes they simply fallback to the
// same implementation as normal.

namespace ivl {

namespace data {


// The following structs describe the promotions that happen to the data types
// when new arrays are automatically created as function return values.

template<class D>
struct conversion<normal_2d<D> >
{
	struct array_creation
	{
		typedef normal similar_type; // all new types used to be normal!!!
		typedef normal new_type;
	};
	struct array_nd_creation
	{
		typedef normal_2d<> similar_type;
		typedef normal new_type;
	};
	struct derived_creation
	{
		typedef normal_2d<> similar_type;
		typedef normal_2d<> new_type;
	};
};


template<int N, class D>
struct conversion<normal_image<N, D> >
{
	struct array_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
	struct array_nd_creation
	{
		typedef normal_image<N> similar_type;
		typedef normal new_type;
	};
	struct derived_creation
	{
		typedef normal_image<N> similar_type;
		typedef normal_image<N> new_type; // but N will change!!!!!!!!!! or no.
	};
};

} //namespace data

} //namespace ivl



#endif // IVL_CORE_DETAILS_DATA_CONVERSIONS_ARRAY_ND_HPP
