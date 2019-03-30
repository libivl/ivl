/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the nulls of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the nulls
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_NUM_ITER_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_NUM_ITER_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(gcd,            "gcd")
IVL_TOKEN(lcm,            "lcm")
IVL_TOKEN(exp,            "exp")
IVL_TOKEN(log,            "log")

//-----------------------------------------------------------------------------

template <> struct define <gcd> :
_<fun, _<m>, _<function,
	_<_<_0>, _<abs, m> >,
	_<_<n>, _<gcd, n, _<rem, m, n> > >
> >
{ };

template <> struct define <lcm> : _<un_2, abs, _<bin_2, quot, mul, gcd> > { };

template <> struct define <exp> :
_<function,
	_<_<_1>, _<fix, _1> >,
	_<_<_1m>, sgn>,
	_<_<n>, _<it_n, _1, _<mul, n> > >
>
{ };

template <> struct define <log> :
_<fun, _<m, n>, _<let, _<_<m1, _<abs, m> >, _<n1, _<abs, n> > >, _<
	cond,
	_<_<_and, _<le, m1, _1>, _<eq, m, n> >, _1>,
	_<_<_and, _<neq, m, _0>, _<eq, n, _1> >, _0>,
	_<_<_or, _<le, m1, _1>, _<le, n1, _1> >, oops>,
	_<_<le, m1, n1>, _<inc, _<log, m, _<quot_t, n, m> > > >,
	_<_<eq, _<sign, m>, _<sign, n> >, _0>,
	_<_else, oops>
> > >
{ };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_NUM_ITER_HPP
