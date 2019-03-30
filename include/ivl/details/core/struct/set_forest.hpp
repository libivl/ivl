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

#ifndef IVL_CORE_DETAILS_STRUCT_SET_FOREST_HPP
#define IVL_CORE_DETAILS_STRUCT_SET_FOREST_HPP

#include <map>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

template <typename T>
struct null_value_int { T operator()() { return -1; } };

template <typename T>
struct null_value_ptr { T operator()() { return 0; } };

template <typename T>
struct null_value_default { T operator()() { return T(); } };

template <typename T>
struct null_value : types::t_if <
	types::is_integer <T>,
	null_value_int <T>,
	typename types::t_if <
		types::is_ptr <T>,
		null_value_ptr <T>,
		null_value_default <T>
	>::type
>::type { };

}  //namespace types

//-----------------------------------------------------------------------------

template <
	typename T = size_t, typename OFFSET = fun::id
 	, bool SPARSE = false
>
class set_forest
{
	class component
	{
		types::null_value <T> null;
	public:
		T parent;
		size_t rank;

		component() : parent(null()), rank(0) { }
	};

//-----------------------------------------------------------------------------

 	typedef typename types::t_if <
 		types::t_expr <SPARSE>,
 		array <component>,
 		std::map <size_t, component>
 	>::type container;

	types::null_value <T> null;
 	container f;
	const OFFSET& offset;

	component& comp(const T& x) { return f[offset(x)]; }

	T& parent(const T& x) { return comp(x).parent; }

	size_t& rank(const T& x) { return comp(x).rank; }

//-----------------------------------------------------------------------------

public:

	// constructor for normal, (non-sparse), size required
	set_forest(const size_t n, const OFFSET& o = OFFSET(), 
		types::static_enable_if_b<!SPARSE> = 0) :
		f(types::r_if_b<SPARSE>(n, container())), offset(o) { }

	// constructor for sparse, size not given
	set_forest(const OFFSET& o = OFFSET(), 
		types::static_enable_if_b<SPARSE> = 0) :
		f(), offset(o) { }

	// constructor for sparse, to be used for compatibility with non-sparse
	//template<class I>
	//set_forest(I n, const OFFSET& o = OFFSET(), 
	//	typename types::enable_if_b<SPARSE, int, I>::type = 0) :
	//	f(), offset(o) { }
		
	set_forest(const container& f, const OFFSET& o = OFFSET()) :
		f(f), offset(o) { }

	const T& set(const T& x)
	{
		T& p = parent(x);
		if (p == null())
			return x;
		else
		{
			p = set(p);
			return p;
		}
	}

	const T& union_(const T& x1, const T& x2)
	{
		T      &p1 = parent(x1), &p2 = parent(x2);
		size_t &r1 = rank(x1),   &r2 = rank(x2);
		if(r1 < r2) { p1 = x2; return x2; }
		else        { p2 = x1; if (r1 == r2) r1++; return x1; }
	}

	const T& join(const T& x1, const T& x2)
	{
		return set(x1) == set(x2) ? x1 : union_(x1, x2);
	}

	const container& forest() const { return f; }

};

//-----------------------------------------------------------------------------

} // namespace ivl

#endif // IVL_CORE_DETAILS_STRUCT_SET_FOREST_HPP