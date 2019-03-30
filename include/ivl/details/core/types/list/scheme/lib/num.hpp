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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_NUM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_NUM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(gt,             "gt?")
IVL_TOKEN(le,             "le?")
IVL_TOKEN(ge,             "ge?")
IVL_TOKEN(neq,            "!eq?")
IVL_TOKEN(eqn,            "eq#?")
IVL_TOKEN(neqn,           "!eq#?")

//-----------------------------------------------------------------------------

template <> struct define <gt>   : _<inv, lt> { };
template <> struct define <le>   : _<un_2, _not, gt> { };
template <> struct define <ge>   : _<un_2, _not, lt> { };
template <> struct define <neq>  : _<un_2, _not, eq> { };

template <> struct define <eqn>  : _<sym, le> { };
template <> struct define <neqn> : _<un_2, _not, eqn> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(tri,          "tri")
IVL_TOKEN(tri_l,        "tri<")
IVL_TOKEN(tri_r,        "tri>")
IVL_TOKEN(tri_f,        "tri@")
IVL_TOKEN(tri_lf,       "tri<@")
IVL_TOKEN(tri_rf,       "tri>@")

//-----------------------------------------------------------------------------

template <> struct define <tri> :
_<fun, _<c, l, e, g>,
 	_<cond_c, _<_<gt, c>, l>, _<_<eq, c>, e>, _<_<lt, c>, g> >
> { };

template <> struct define <tri_l> : _<f1_dup, tri> { };
template <> struct define <tri_r> : _<f2_dup, tri> { };

template <> struct define <tri_f>  : _<f4_dup, tri>   { };
template <> struct define <tri_lf> : _<f3_dup, tri_l> { };
template <> struct define <tri_rf> : _<f3_dup, tri_r> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(zero,           "zero?")
IVL_TOKEN(neg,            "neg")
IVL_TOKEN(sign,           "sign")
IVL_TOKEN(abs,            "abs")
IVL_TOKEN(min,            "min")
IVL_TOKEN(max,            "max")

//-----------------------------------------------------------------------------

template <> struct define <zero> : _<eq,  _0> { };
template <> struct define <neg>  : _<sub, _0> { };

template <> struct define <sign> : _<tri,    _0, _1m, _0, _1> { };
template <> struct define <abs>  : _<tri_rf, _0, neg, id>     { };

template <> struct define <min>  : _<choose, lt> { };
template <> struct define <max>  : _<choose, gt> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(add_t,          "add!")
IVL_TOKEN(sub_t,          "sub!")
IVL_TOKEN(quot_t,         "quot!")

//-----------------------------------------------------------------------------

template <> struct define <add_t> :
_<fun, _<m>, _<be, a, _<add, m>, _<
	_<tri, _0, _<tri_lf, _0, bad, a>, bad, _<tri_rf, _0, a, bad> >, m
> > >
{ };

template <> struct define <sub_t> : _<fun, _<m>, _<un, _<add_t, m>, neg> > { };

template <> struct define <quot_t> :
_<function,
	_<_<_0>, bad>,
	_<_<m>, _<function,
		_<_<_<bar, _0, _1, _1m> >, oops>,
		_<_<n>, _<quot, m, n> >
	> >
>
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(inc,            "inc")
IVL_TOKEN(inc_t,          "inc!")
IVL_TOKEN(dec,            "dec")
IVL_TOKEN(dec_t,          "dec!")
IVL_TOKEN(next,           "next")

//-----------------------------------------------------------------------------

template <> struct define <inc>   : _<add,   _1> { };
template <> struct define <inc_t> : _<add_t, _1> { };

template <> struct define <dec>   : _<inv, sub,   _1> { };
template <> struct define <dec_t> : _<inv, sub_t, _1> { };

template <> struct define <next> : _<fix, inc> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(rem,            "rem")
IVL_TOKEN(mod,            "mod")
IVL_TOKEN(div,            "div?")
IVL_TOKEN(even,           "even?")
IVL_TOKEN(odd,            "odd?")
IVL_TOKEN(sgn,            "sgn")

//-----------------------------------------------------------------------------

template <> struct define <rem> :
_<fun, _<m, n>, _<sub, m, _<mul, _<quot, m, n>, n> > >
{ };

template <> struct define <mod> :
_<fun, _<m, n>, _<be, r, _<rem, m, n>, _<
	_if, _<ge, m, _0>, r, _<add, r, _<abs, n> >
> > >
{ };

template <> struct define <div>  : _<inv, _<un_2, zero, rem> > { };
template <> struct define <even> : _<div, _2>                  { };
template <> struct define <odd>  : _<un, _not, even>           { };
template <> struct define <sgn>  : _<if_c, even, _1, _1m>      { };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_NUM_HPP
