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

#ifndef IVL_CORE_DETAILS_TYPES_MAP_HPP
#define IVL_CORE_DETAILS_TYPES_MAP_HPP

namespace ivl {
namespace types {
namespace maps {

//-----------------------------------------------------------------------------
// identity type map

template <class A>
struct id { typedef A type; };

//-----------------------------------------------------------------------------
// N-ary type map to fixed type R

template<class R, int N = 1>
struct fixed
{
	template <class A>
	struct map : public id <R> { };
};

template<class R>
struct fixed <R, 2>
{
	template <class A1, class A2>
	struct map : public id <R> { };
};

//-----------------------------------------------------------------------------
// N-ary type map to fixed number NUM

template <int NUM, int N = 1>
struct fixed_num : public fixed <number <NUM>, N> { };

//-----------------------------------------------------------------------------

template <typename NEW, typename OLD>
struct subst
{
	template <typename T>
	struct map : public t_if <t_eq <T, OLD>, NEW, T> { };
};

//-----------------------------------------------------------------------------
// CHOOSE either fixed type R or N-ary type map MAP
// (different class name per N because MAP is a template class with
// varying number of template parameters)

template<
	template<typename, typename> class CHOOSE,
	template<typename> class MAP
>
struct choose_map1
{
	template<class R, class A>
	struct map : public CHOOSE<R, typename MAP<A>::type> { };
};

template<
	template<typename, typename> class CHOOSE,
	template<typename, typename> class MAP
>
struct choose_map2
{
	template<class R, class A1, class A2>
	struct map : public CHOOSE<R, typename MAP<A1, A2>::type> { };
};

//-----------------------------------------------------------------------------
// fixed type R or default type D if R is term

template<class R, class D>
struct default_type
{
	typedef typename t_if<t_eq<R, term>, D, R>::type type;
};

//-----------------------------------------------------------------------------
// fixed type R or default type map MAP if R is term

template<
	template<typename> class MAP
>
struct default_map1 : public choose_map1<default_type, MAP> { };

template<
	template<typename, typename> class MAP
>
struct default_map2 : public choose_map2<default_type, MAP> { };

//-----------------------------------------------------------------------------
// fixed type R or default type A if R is term
// (same as default_type<R, A>)

template<class R, class A>
struct default1 : public default_map1<id>::map<R, A> { };

//-----------------------------------------------------------------------------
// fixed type R or default type max<A1, A2> if R is term

template<class R, class A1, class A2>
struct default_max2 : public default_map2<max>::map<R, A1, A2> { };

//-----------------------------------------------------------------------------

}  // namespace maps
}  // namespace types
}  // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_MAP_HPP
