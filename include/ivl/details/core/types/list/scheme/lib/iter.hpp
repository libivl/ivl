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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_ITER_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_ITER_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(star,           "*")
IVL_TOKEN(be_star,        "be*")

//-----------------------------------------------------------------------------

template <> struct define <star> :
_<fun, _<f, g>, _<make_rec, _<s>,
	_<_<_<dot, l> >, _<f, l, s> >,
	_<_<a>, _<g, a> >
> >
{ };

template <> struct define_syntax <be_star> :
_<fun, _<g>, _<pac, _<n, f>, _<let_rec, _<
	_<F, f>,
	_<n, _<function,
		_<_<_<_<_<dot>, L>, _<dot>, M> >, _<g, _<n, L>, _<n, M> > >,
		_<_<E>, _<F, E> >
	> >
> > > >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(scan_f,         "scan@")
IVL_TOKEN(scan,           "scan")
IVL_TOKEN(scan_u,         "scan^")
IVL_TOKEN(scan_s,         "scan*")

//-----------------------------------------------------------------------------

template <> struct define <scan_f> :
_<fun, _<r, e, f>, _<make_f, r, _<s>,
	_<_<_<> >, e>,
	_<_<_<a, dot, l> >, _<f, a, l, s> >
> >
{ };

template <> struct define <scan>   : _<scan_f, be_rec> { };
template <> struct define <scan_u> : _<fix, scan> { };
template <> struct define <scan_s> : _<un, scan_f, be_star> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(it_f,           "it@")
IVL_TOKEN(it,             "it")
IVL_TOKEN(it_s,           "it*")
IVL_TOKEN(iter,           "iter")
IVL_TOKEN(iter_s,         "iter*")

//-----------------------------------------------------------------------------

template <> struct define <it_f> :
_<fun, _<s, m, e, f>, _<_<s, f>, e, _<
	fun, _<a, l, i>, _<f, _<m, a>, _<i, l> >
> > >
{ };

template <> struct define <it>   : _<it_f, scan_u> { };
template <> struct define <it_s> : _<it_f, scan_s> { };

template <> struct define <iter>   : _<cyc_r, it>   { };
template <> struct define <iter_s> : _<cyc_r, it_s> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(f_if,           "@if")
IVL_TOKEN(f_if_m,         "@if+")

//-----------------------------------------------------------------------------

template <> struct define <f_if> :
_<fun, _<p, f, h>, _<fun, _<a, l, e>, _<
	_if, _<p, a>, _<f, a, l>, _<h, a, _<e, l> >
> > >
{ };

template <> struct define <f_if_m> :
_<fun, _<p, f, h>, _<fun, _<a, l, e>, _<
	_<if_f, p, f, h>, a, _<e, l>
> > >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(accum_f,        "accum@")
IVL_TOKEN(accum,          "accum")
IVL_TOKEN(accum_s,        "accum*")

//-----------------------------------------------------------------------------

template <> struct define <accum_f> :
_<fun, _<s, e, f, g, p>, _<_<s, g>, e, _<f_if_m, p, f, _2nd> > >
{ };

template <> struct define <accum>   : _<accum_f, scan_u> { };
template <> struct define <accum_s> : _<accum_f, scan_s> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(it_n,           "it#")

//-----------------------------------------------------------------------------

template <> struct define <it_n> :
_<fun, _<e, f>, _<make_rec, _<i>,
	_<_<_0>, e>,
	_<_<n>, _<f, _<i, _<dec_t, n> > > >
> >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(scan_ll,        "scan::")
IVL_TOKEN(scan_ln,        "scan:#")

//-----------------------------------------------------------------------------

template <> struct define <scan_ll> :
_<fun, _<e, p, q, f>, _<make_rec, _<i>,
	_<_<_<>, _<> >, e>,
	_<_<_<>, _<dot, v> >, _<q, v> >,
	_<_<_<dot, u>, _<> >, _<p, u> >,
	_<_<_<dot, u>, _<dot, v> >, _<f, u, v, i> >
> >
{ };

template <> struct define <scan_ln> :
_<fun, _<e, p, q, f>, _<make_rec, _<i>,
	_<_<_<>, _0>, e>,
	_<_<_<>, n>, _<q, n> >,
	_<_<_<dot, u>, _0>, _<p, u> >,
	_<_<_<dot, u>,  n>, _<f, u, n, i> >
> >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(it_ll,          "it::")
IVL_TOKEN(it_ln,          "it:#")
IVL_TOKEN(it_1n,          "it1#")

//-----------------------------------------------------------------------------

template <> struct define <it_ll> :
_<fun, _<e, p, q, f, g>, _<scan_ll, e, _<f_split, p>, _<f_split, q>,
	_<fun, _<_<a, dot, u>, _<b, dot, v>, i>, _<f, _<g, a, b>, _<i, u, v> > >
> >
{ };

template <> struct define <it_ln> :
_<fun, _<e, p, q, f, g>, _<scan_ln, e, _<f_split, p>, q,
	_<fun, _<_<a, dot, u>, n, i>, _<f, _<g, a, n>, _<i, u, _<dec_t, n> > > >
> >
{ };

template <> struct define <it_1n> : _<fun, _<p>, _<it_ln, oops, p, bad> > { };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_ITER_HPP
