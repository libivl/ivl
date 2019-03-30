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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_LIST_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_LIST_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(map,            "map")
IVL_TOKEN(map_s,          "map*")
IVL_TOKEN(fold,           "fold")
IVL_TOKEN(fold_s,         "fold*")

//-----------------------------------------------------------------------------

template <> struct define <map>    : _<iter,   _<>, cons> { };
template <> struct define <map_s>  : _<iter_s, _<>, cons> { };

template <> struct define <fold>   : _<it,   id> { };
template <> struct define <fold_s> : _<it_s, id> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(fold_1f,        "fold1@")
IVL_TOKEN(fold_1,         "fold1")
IVL_TOKEN(fold_1s,        "fold1*")

//-----------------------------------------------------------------------------

template <> struct define <fold_1f> :
_<fun, _<o, f>, _<if_null, oops, _<fun, _<a, l>, _<o, a, f, l> > > >
{ };

template <> struct define <fold_1>  : _<fold_1f, fold>   { };
template <> struct define <fold_1s> : _<fold_1f, fold_s> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(any,            "any")
IVL_TOKEN(any_s,          "any*")
IVL_TOKEN(all,            "all")
IVL_TOKEN(all_s,          "all*")

//-----------------------------------------------------------------------------

template <> struct define <any>   : _<iter,   _false, _or> { };
template <> struct define <any_s> : _<iter_s, _false, _or> { };

template <> struct define <all>   : _<iter,   _true, _and> { };
template <> struct define <all_s> : _<iter_s, _true, _and> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(count,          "count")
IVL_TOKEN(count_s,        "count*")
IVL_TOKEN(filter,         "filter")
IVL_TOKEN(filter_s,       "filter*")

//-----------------------------------------------------------------------------

template <> struct define <count>   : _<accum,   _0, next, ___> { };
template <> struct define <count_s> : _<accum_s, _0, next, add> { };

template <> struct define <filter>   : _<accum,   _<>, cons, ___>  { };
template <> struct define <filter_s> : _<accum_s, _<>, cons, cons> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(lat,            "lat?")
IVL_TOKEN(length,         "length")
IVL_TOKEN(length_s,       "length*")
IVL_TOKEN(join,           "join")

//-----------------------------------------------------------------------------

template <> struct define <lat> : _<all, atom> { };

template <> struct define <length>   : _<count,   each>  { };
template <> struct define <length_s> : _<count_s, each> { };

template <> struct define <join> : _<cyc_r, fold, cons> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(member,         "member?")
IVL_TOKEN(member_s,       "member*")
IVL_TOKEN(occur,          "occur")
IVL_TOKEN(occur_s,        "occur*")

//-----------------------------------------------------------------------------

template <> struct define <member>   : _<un, any,   eq> { };
template <> struct define <member_s> : _<un, any_s, eq> { };

template <> struct define <occur>   : _<un, count,   eq> { };
template <> struct define <occur_s> : _<un, count_s, eq> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(in,             "in?")
IVL_TOKEN(not_in,         "not_in?")
IVL_TOKEN(in_eq,          "in_eq?")

//-----------------------------------------------------------------------------

template <> struct define <in>     : _<inv, member>     { };
template <> struct define <not_in> : _<un_2, _not, in>  { };
template <> struct define <in_eq>  : _<if_list, in, eq> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(edit_f,         "edit@")
IVL_TOKEN(edit,           "edit")
IVL_TOKEN(edit_m,         "edit+")
IVL_TOKEN(edit_s,         "edit*")

//-----------------------------------------------------------------------------

template <> struct define <edit_f> :
_<fun, _<s, f, o, p>, _<_<s, cons>, _<>,
	_<f, _<in_eq, p>, _<fix, _<join, _<o, p> > >, cons>
> >
{ };

template <> struct define <edit>   : _<edit_f, scan_u, f_if>   { };
template <> struct define <edit_m> : _<edit_f, scan_u, f_if_m> { };
template <> struct define <edit_s> : _<edit_f, scan_s, f_if_m> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(f_remove,       "@remove")
IVL_TOKEN(f_insert_l,     "@insert<")
IVL_TOKEN(f_insert_r,     "@insert>")
IVL_TOKEN(f_subst,        "@subst")

//-----------------------------------------------------------------------------

template <> struct define <f_remove>   : _<fun, _<p>,    _<> >     { };
template <> struct define <f_insert_l> : _<fun, _<n, p>, _<n, p> > { };
template <> struct define <f_insert_r> : _<fun, _<n, p>, _<p, n> > { };
template <> struct define <f_subst>    : _<fun, _<n, p>, _<n> >    { };

//-----------------------------------------------------------------------------

IVL_TOKEN(remove,         "remove")
IVL_TOKEN(insert_l,       "insert<")
IVL_TOKEN(insert_r,       "insert>")
IVL_TOKEN(subst,          "subst")
IVL_TOKEN(subst2,         "subst2")

//-----------------------------------------------------------------------------

template <> struct define <remove>   : _<edit,     f_remove>   { };
template <> struct define <insert_l> : _<un, edit, f_insert_l> { };
template <> struct define <insert_r> : _<un, edit, f_insert_r> { };
template <> struct define <subst>    : _<un, edit, f_subst>    { };
template <> struct define <subst2>   : _<un, edit, f_subst>    { };

//-----------------------------------------------------------------------------

IVL_TOKEN(remove_m,       "remove+")
IVL_TOKEN(insert_lm,      "insert<+")
IVL_TOKEN(insert_rm,      "insert>+")
IVL_TOKEN(subst_m,        "subst+")
IVL_TOKEN(subst2_m,       "subst2+")

//-----------------------------------------------------------------------------

template <> struct define <remove_m>  : _<edit_m,     f_remove>   { };
template <> struct define <insert_lm> : _<un, edit_m, f_insert_l> { };
template <> struct define <insert_rm> : _<un, edit_m, f_insert_r> { };
template <> struct define <subst_m>   : _<un, edit_m, f_subst>    { };
template <> struct define <subst2_m>  : _<un, edit_m, f_subst>    { };

//-----------------------------------------------------------------------------

IVL_TOKEN(remove_s,       "remove*")
IVL_TOKEN(insert_ls,      "insert<*")
IVL_TOKEN(insert_rs,      "insert>*")
IVL_TOKEN(subst_s,        "subst*")
IVL_TOKEN(subst2_s,       "subst2*")

//-----------------------------------------------------------------------------

template <> struct define <remove_s>  : _<edit_s,     f_remove>   { };
template <> struct define <insert_ls> : _<un, edit_s, f_insert_l> { };
template <> struct define <insert_rs> : _<un, edit_s, f_insert_r> { };
template <> struct define <subst_s>   : _<un, edit_s, f_subst>    { };
template <> struct define <subst2_s>  : _<un, edit_s, f_subst>    { };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_LIST_HPP
