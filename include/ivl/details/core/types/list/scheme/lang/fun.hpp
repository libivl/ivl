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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_FUN_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_FUN_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_KEYWORD(rules_lz,       "rules-")
IVL_KEYWORD(cases_pt,       "cases|")

//-----------------------------------------------------------------------------

template <> struct define_syntax <rules_lz> :
_<rules, _<>, _<
	_<___, l, _<p, t>, etc>,
	_<rules, l, _<p, _<quote, t> >, etc>
> >
{ };

template <> struct define_syntax <cases_pt> :
_<rules, _<>, _<
	_<___, l, c, etc>,
	_<partial, _<cases, l, c, etc> >
> >
{ };

//-----------------------------------------------------------------------------

IVL_KEYWORD(func_f,         "func@")
IVL_KEYWORD(abbrev,         "abbrev")
IVL_KEYWORD(macro,          "macro")
IVL_KEYWORD(function,       "function")

//-----------------------------------------------------------------------------

template <> struct define <func_f> :
_<lambda, _<f>, _<rules, _<>, _<
	_<___, _<p, t>, etc>,
	_<f, _<>, _<_<___, dot, p>, t>, etc>
> > >
{ };

template <> struct define_syntax <abbrev>   : _<func_f, rules_lz> { };
template <> struct define_syntax <macro>    : _<func_f, rules>    { };
template <> struct define_syntax <function> : _<func_f, cases_pt> { };

//-----------------------------------------------------------------------------

IVL_KEYWORD(curry_f,        "curry@")
IVL_KEYWORD(abb,            "abb")
IVL_KEYWORD(mac,            "mac")
IVL_KEYWORD(fun,            "fun")
IVL_KEYWORD(pac,            "pac")

//-----------------------------------------------------------------------------

template <> struct define <curry_f> :
_<lambda, _<f>, _<macro, _<_<dot, c>, _<f, c> > > >
{ };

template <> struct define_syntax <abb> : _<curry_f, abbrev>   { };
template <> struct define_syntax <mac> : _<curry_f, macro>    { };
template <> struct define_syntax <fun> : _<curry_f, function> { };

template <> struct define_syntax <pac> :
_<mac, _<p, t>, _<partial, _<mac, p, t> > >
{ };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_FUN_HPP
