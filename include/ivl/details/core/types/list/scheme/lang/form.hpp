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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_FORM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_FORM_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_KEYWORD(let_arg,        "let_arg")
IVL_KEYWORD(let_f,          "let@")
IVL_KEYWORD(let,            "let")
IVL_KEYWORD(let_rec,        "let_rec")

//-----------------------------------------------------------------------------

template <> struct define_syntax <let_arg> :
_<abbrev,
	_<_<_<n, dot, p>, t>, _<n, _<fun, p, t> > >,
	_<_<i, v>, _<i, v> >
>
{ };

// template <> struct define <let_f> :
// _<lambda, _<f>, _<mac,
// 	_<_<_<i, v>, etc>, b, etc>,
// 	_<f, _<_<let_arg, i, v>, etc>, b, etc>
// > >
// { };

template <> struct define <let_f> :
_<lambda, _<f>, _<pac,
	_<_<_<i, v>, etc> >,
	_<f, _<_<let_arg, i, v>, etc> >
> >
{ };

template <> struct define_syntax <let> :
_<let_f, _<fun,
	_<_<_<i, v>, etc> >,
	_<mac, _<b, etc>, _<_<lambda, _<i, etc>, b, etc>, v, etc> >
> >
{ };

template <> struct define_syntax <let_rec> :
_<let_f, _<fun,
	_<_<_<i, v>, etc> >,
	_<mac, _<b, etc>,
		_<let, _<_<i, _0>, etc>,
			_<let, _<_<var <T>, v>, etc>, _<set_b, i, var <T> >, etc>,
			b, etc
		>
	>
> >
{ };

//-----------------------------------------------------------------------------

// template <> struct define_syntax <let> :
// _<rules, _<>, _<
// 	_<let, _<_<a, v>, etc>, b, etc>,
// 	_<_<lambda, _<a, etc>, b, etc>, v, etc>
// > >
// { };

// template <> struct define_syntax <let_rec> :
// _<rules, _<>, _<
// 	_<let_rec, _<_<a, v>, etc>, b, etc>,
// 	_<let, _<_<a, _0>, etc>,
// 		_<let, _<_<var <f>, v>, etc>, _<set_b, a, var <f> >, etc>,
// 		b, etc
// 	>
// > >
// { };

//-----------------------------------------------------------------------------

IVL_KEYWORD(be_f,           "be@")
IVL_KEYWORD(be,             "be")
IVL_KEYWORD(be_rec,         "be_rec")

//-----------------------------------------------------------------------------

template <> struct define <be_f> :
_<fun, _<f>, _<pac, _<i, v>, _<f, _<_<i, v> > > > >
{ };

template <> struct define_syntax <be>     : _<be_f, let>     { };
template <> struct define_syntax <be_rec> : _<be_f, let_rec> { };

//-----------------------------------------------------------------------------

IVL_KEYWORD(make_f,         "make@")
IVL_KEYWORD(make,           "make")
IVL_KEYWORD(make_rec,       "make_rec")
IVL_KEYWORD(match,          "match")

//-----------------------------------------------------------------------------

template <> struct define_syntax <make_f> :
_<fun, _<f>, _<macro,
	_<_<_<n, dot, v>, c, etc>, _<f, n, _<function, c, etc>, _<n, dot, v> > >,
	_<_<i, v>, _<f, i, v, i> >
> >
{ };

template <> struct define_syntax <make>      : _<make_f, be>      { };
template <> struct define_syntax <make_rec>  : _<make_f, be_rec>  { };

template <> struct define_syntax <match> :
_<mac, _<v, c, etc>, _<_<function, c, etc>, dot, v> >
{ };

//-----------------------------------------------------------------------------

IVL_KEYWORD(_if,            "_if")

//-----------------------------------------------------------------------------
#ifdef IVL_LIST_LL
//-----------------------------------------------------------------------------

template <> struct define_syntax <_if> :
_<mac, _<c, t, e>, _<cond, _<c, t>, _<_else, e> > >
{ };

//-----------------------------------------------------------------------------
#else
//-----------------------------------------------------------------------------

template <> struct define <_if> :
_<function,
	_<_<_false>, _<mac, _<t, e>, e> >,
	_<_<_true>,  _<mac, _<t, e>, t> >
>
{ };

template <> struct define_syntax <cond> :
_<mac, _<_<c, t>, e, etc>,  _<_if, c, t, _<cond, e, etc> > >
{ };

template <> struct define <_else> : _true { };

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------

IVL_KEYWORD(is,             "is")
IVL_KEYWORD(_not,           "not")
IVL_KEYWORD(_and,           "and")
IVL_KEYWORD(_or,            "or")

//-----------------------------------------------------------------------------

template <> struct define <is> :
_<function,
	_<_<_false>, _false>,
	_<_<_true>,  _true>
>
{ };

template <> struct define <_not> :
_<function,
	_<_<_false>, _true>,
	_<_<_true>,  _false>
>
{ };

template <> struct define_syntax <_and> :
_<macro,
	_<_<>, _true>,
	_<_<a>, _<is, a> >,
	_<_<a, b, etc>, _<_if, a, _<_and, b, etc>, _false> >
>
{ };

template <> struct define_syntax <_or> :
_<macro,
	_<_<>, _false>,
	_<_<a>, _<is, a> >,
	_<_<a, b, etc>, _<_if, a, _true, _<_or, b, etc> > >
>
{ };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_FORM_HPP
