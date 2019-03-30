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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_FUN_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_FUN_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(id,             "id")
IVL_TOKEN(_1st,           "1st")
IVL_TOKEN(_2nd,           "2nd")

//-----------------------------------------------------------------------------

template <> struct define <id>   : _<fun, _<x>,      x> { };

template <> struct define <_1st> : _<fun, _<x, ___>, x> { };
template <> struct define <_2nd> : _<fun, _<___, y>, y> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(fix,            "fix")
IVL_TOKEN(bad,            "bad")
IVL_TOKEN(each,           "each")
IVL_TOKEN(other,          "other")

//-----------------------------------------------------------------------------

template <> struct define <fix>   : _<mac, _<x>, _<fun, _<___>, x> > { };

template <> struct define <bad>   : _<fix, oops>  { };
template <> struct define <each>  : _<fix, _true> { };
template <> struct define <other> : _<fix, _else> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(un,             "un")
IVL_TOKEN(un_2,           "un2")
IVL_TOKEN(bin,            "bin")
IVL_TOKEN(bin_2,          "bin2")

//-----------------------------------------------------------------------------

template <> struct define <un>   : _<fun, _<o, f, x>,    _<o, _<f, x> > >    { };
template <> struct define <un_2> : _<fun, _<o, f, x, y>, _<o, _<f, x, y> > > { };

template <> struct define <bin> :
_<fun, _<o, f, g, x>, _<o, _<f, x>, _<g, x> > >
{ };

template <> struct define <bin_2> :
_<fun, _<o, f, g, x, y>, _<o, _<f, x, y>, _<g, x, y> > >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(inv,            "inv")
IVL_TOKEN(sym,            "sym")
IVL_TOKEN(cyc_l,          "cyc<")
IVL_TOKEN(cyc_r,          "cyc>")

//-----------------------------------------------------------------------------

template <> struct define <inv> : _<fun, _<f, x, y>, _<f, y, x> > { };

template <> struct define <sym> :
_<fun, _<f>, _<bin_2, _and, f, _<inv, f> > >
{ };

template <> struct define <cyc_l> : _<fun, _<f, x, y, z>, _<f, y, z, x> > { };
template <> struct define <cyc_r> : _<fun, _<f, x, y, z>, _<f, z, x, y> > { };

//-----------------------------------------------------------------------------

IVL_TOKEN(f_cons,         "@cons")
IVL_TOKEN(f_split,        "@split")
IVL_TOKEN(cur,            "cur")
IVL_TOKEN(uncur,          "uncur")

//-----------------------------------------------------------------------------

template <> struct define <f_cons> :
_<fun, _<f, a, l>, _<f, _<a, dot, l> > >
{ };

template <> struct define <f_split> :
_<fun, _<f, _<a, dot, l> >, _<f, a, l> >
{ };

template <> struct define <cur> :
_<mac, _<f, dot, a>, _<fun, _<f, dot, a>, _<f, a> > >
{ };

template <> struct define <uncur> :
_<mac, _<f, dot, a>, _<fun, _<f, a>, _<f, dot, a> > >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(cur_0,          "cur0")
IVL_TOKEN(cur_1,          "cur1")
IVL_TOKEN(cur_2,          "cur2")
IVL_TOKEN(cur_3,          "cur3")
IVL_TOKEN(cur_4,          "cur4")
IVL_TOKEN(cur_5,          "cur5")

//-----------------------------------------------------------------------------

template <> struct define <cur_0> : _<cur, f>                { };
template <> struct define <cur_1> : _<cur, f, x>             { };
template <> struct define <cur_2> : _<cur, f, x, y>          { };
template <> struct define <cur_3> : _<cur, f, x, y, z>       { };
template <> struct define <cur_4> : _<cur, f, x, y, z, u>    { };
template <> struct define <cur_5> : _<cur, f, x, y, z, u, v> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(uncur_0,        "uncur0")
IVL_TOKEN(uncur_1,        "uncur1")
IVL_TOKEN(uncur_2,        "uncur2")
IVL_TOKEN(uncur_3,        "uncur3")
IVL_TOKEN(uncur_4,        "uncur4")
IVL_TOKEN(uncur_5,        "uncur5")

//-----------------------------------------------------------------------------

template <> struct define <uncur_0> : _<uncur, f>                { };
template <> struct define <uncur_1> : _<uncur, f, x>             { };
template <> struct define <uncur_2> : _<uncur, f, x, y>          { };
template <> struct define <uncur_3> : _<uncur, f, x, y, z>       { };
template <> struct define <uncur_4> : _<uncur, f, x, y, z, u>    { };
template <> struct define <uncur_5> : _<uncur, f, x, y, z, u, v> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(dup,            "dup")
IVL_TOKEN(f1_dup,         "f1dup")
IVL_TOKEN(f2_dup,         "f2dup")
IVL_TOKEN(f3_dup,         "f3dup")
IVL_TOKEN(f4_dup,         "f4dup")

//-----------------------------------------------------------------------------

template <> struct define <dup> : _<fun, _<f, x>, _<f, x, x> > { };

template <> struct define <f1_dup> : _<cur_2, dup> { };
template <> struct define <f2_dup> : _<cur_3, dup> { };
template <> struct define <f3_dup> : _<cur_4, dup> { };
template <> struct define <f4_dup> : _<cur_5, dup> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(dup_2,          "dup2")
IVL_TOKEN(f1_dup_2,       "f1dup2")
IVL_TOKEN(f2_dup_2,       "f2dup2")
IVL_TOKEN(f3_dup_2,       "f3dup2")
IVL_TOKEN(f4_dup_2,       "f4dup2")

//-----------------------------------------------------------------------------

template <> struct define <dup_2> : _<fun, _<f, x, y>, _<f, x, y, x, y> > { };

template <> struct define <f1_dup_2> : _<cur_2, dup_2> { };
template <> struct define <f2_dup_2> : _<cur_3, dup_2> { };
template <> struct define <f3_dup_2> : _<cur_4, dup_2> { };
template <> struct define <f4_dup_2> : _<cur_5, dup_2> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(if_c,           "if-")
IVL_TOKEN(if_f,           "if@")
IVL_TOKEN(cond_c,         "cond-")
IVL_TOKEN(cond_f,         "cond@")

//-----------------------------------------------------------------------------

template <> struct define <if_c> :
_<fun, _<p, t, e, x>, _<_if, _<p, x>, t, e> >
{ };

template <> struct define <if_f> : _<f3_dup, if_c> { };

template <> struct define <cond_c> :
_<mac,
	_<_<p, c>, etc>,
	_<fun, _<X>, _<cond, _<_<p, X>, c>, etc> >
>
{ };

template <> struct define <cond_f> :
_<mac, _<c, etc>, _<dup, _<cond_c, c, etc> > >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(rel_c,          "rel-")
IVL_TOKEN(rel_f,          "rel@")
IVL_TOKEN(choose,         "choose")

//-----------------------------------------------------------------------------

template <> struct define <rel_c> :
_<fun, _<p, t, e, x, y>, _<_if, _<p, x, y>, t, e> >
{ };

template <> struct define <rel_f> : _<f3_dup_2, rel_c> { };

template <> struct define <choose> :
_<fun, _<p>, _<rel_f, p, _1st, _2nd> >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(if_null,        "if_null")
IVL_TOKEN(if_list,        "if_list")
IVL_TOKEN(cond_list,      "cond_list")

//-----------------------------------------------------------------------------

template <> struct define <if_null> :
_<fun, _<e, f>, _<function,
	_<_<_<> >, e>,
	_<_<_<a, dot, l> >, _<f, a, l> >
> >
{ };

template <> struct define <if_list> :
_<fun, _<f, g>, _<function,
	_<_<_<dot, l> >, _<f, l> >,
	_<_<a>, _<g, a> >
> >
{ };

template <> struct define <cond_list> :
_<fun, _<e, f, g>, _<function,
	_<_<_<> >, e>,
	_<_<_<a, dot, l> >, _<f, a, l> >,
	_<_<a>, _<g, a> >
> >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(Y,              "Y")

//-----------------------------------------------------------------------------

template <> struct define <Y> :
_<lambda, _<f>, _<
	_<lambda, _<g>, _<g, g> >,
	_<lambda, _<h>, _<
		f, _<lambda, _<x>, _<_<h, h>, x> >
	> >
> >
{ };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_FUN_HPP
