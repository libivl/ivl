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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_SET_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_SET_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(set,            "set?")
IVL_TOKEN(mk_set,         "mk_set")
IVL_TOKEN(sect,           "sect?")
IVL_TOKEN(supset,         "supset?")
IVL_TOKEN(subset,         "subset?")
IVL_TOKEN(eq_set,         "eq_set?")

//-----------------------------------------------------------------------------

template <> struct define <set> :
_<scan, _true, _<fun, _<a, l, s>, _<_and, _<not_in, l, a>, _<s, l> > > >
{ };

template <> struct define <mk_set> :
_<fold, _<>, _<bin_2, cons, _1st, remove_m> >
{ };

template <> struct define <sect>   : _<un, any, in> { };
template <> struct define <supset> : _<un, all, in> { };
template <> struct define <subset> : _<inv, supset> { };
template <> struct define <eq_set> : _<sym, subset> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(diff,           "diff")
IVL_TOKEN(section,        "section")
IVL_TOKEN(_union,         "union")
IVL_TOKEN(section_m,      "section+")
IVL_TOKEN(union_m,        "union+")

//-----------------------------------------------------------------------------

template <> struct define <diff>    : _<inv, _<un, filter, not_in> > { };
template <> struct define <section> : _<inv, _<un, filter, in> >     { };
template <> struct define <_union>  : _<bin_2, join, diff, _2nd>     { };

template <> struct define <section_m> : _<fold_1,    section> { };
template <> struct define <union_m>   : _<fold, _<>, _union>  { };

//-----------------------------------------------------------------------------

IVL_TOKEN(pair,           "pair?")
IVL_TOKEN(first,          "first")
IVL_TOKEN(second,         "second")
IVL_TOKEN(third,          "third")
IVL_TOKEN(rev,            "rev")

//-----------------------------------------------------------------------------

template <> struct define <pair> :
_<function,
	_<_<_<___, ___> >, _true>,
	_<_<___>, _false>
>
{ };

template <> struct define <first>   : _<car> { };
template <> struct define <second>  : _<un, first,  cdr> { };
template <> struct define <third>   : _<un, second, cdr> { };
template <> struct define <rev>     : _<fun, _<_<a, b> >, _<b, a> > { };

//-----------------------------------------------------------------------------

IVL_TOKEN(leftmost,       "leftmost")
IVL_TOKEN(first_e,        "first:")
IVL_TOKEN(second_e,       "second:")
IVL_TOKEN(third_e,        "third:")
IVL_TOKEN(rev_e,          "rev:")

//-----------------------------------------------------------------------------

template <> struct define <leftmost> :
_<cond_list, oops, _<inv, _<fix, leftmost> >, id>
{ };

template <> struct define <first_e>  : _<un_e, first> { };
template <> struct define <second_e> : _<un_e, second> { };
template <> struct define <third_e>  : _<un_e, third> { };
template <> struct define <rev_e>    : _<un_e, rev> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(rel,            "rel?")
IVL_TOKEN(func,           "func?")
IVL_TOKEN(one2one,        "one2one?")

//-----------------------------------------------------------------------------

template <> struct define <rel>     : _<bin, _and, set, _<all, pair> > { };
template <> struct define <func>    : _<un, set, first_e>              { };
template <> struct define <one2one> : _<un, set, second_e>             { };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_SET_HPP
