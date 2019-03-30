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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_TUP_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_TUP_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(un_e,           "un:")
IVL_TOKEN(un_s,           "un*")
IVL_TOKEN(bin_e,          "bin:")
IVL_TOKEN(sym_e,          "sym:")

//-----------------------------------------------------------------------------

template <> struct define <un_e> : _<fun, _<f>, _<if_list, _<map, f>, f> > { };
template <> struct define <un_s> : _<star, _<inv, map> > { };

template <> struct define <bin_e> : _<it_ll, _<>, bad,  bad,  cons> { };
template <> struct define <sym_e> : _<it_ll, _<>, cons, cons, cons> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(tup,            "tup?")
IVL_TOKEN(sum,            "sum")
IVL_TOKEN(prod,           "prod")
IVL_TOKEN(min_m,          "min+")
IVL_TOKEN(max_m,          "max+")

//-----------------------------------------------------------------------------

template <> struct define <tup> : _<all, num> { };

template <> struct define <sum>  : _<fold, _0, add> { };
template <> struct define <prod> : _<fold, _1, mul> { };

template <> struct define <min_m> : _<fold, inf_p, min> { };
template <> struct define <max_m> : _<fold, inf_m, max> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(inc_e,          "inc:")
IVL_TOKEN(dec_e,          "dec:")
IVL_TOKEN(inc_et,         "inc:!")
IVL_TOKEN(dec_et,         "dec:!")

//-----------------------------------------------------------------------------

template <> struct define <inc_e>  : _<un_e, inc> { };
template <> struct define <dec_e>  : _<un_e, dec> { };

template <> struct define <inc_et> : _<un, inc_e, _<filter, _<gt, _0> > > { };
template <> struct define <dec_et> : _<un, dec_e, _<filter, _<lt, _0> > > { };

//-----------------------------------------------------------------------------

IVL_TOKEN(add_e,          "add:")
IVL_TOKEN(sub_e,          "sub:")
IVL_TOKEN(sign_e,         "sign:")
IVL_TOKEN(neg_e,          "neg:")
IVL_TOKEN(abs_e,          "abs:")
IVL_TOKEN(min_e,          "min:")
IVL_TOKEN(max_e,          "max:")

//-----------------------------------------------------------------------------

template <> struct define <add_e>  : _<sym_e, add> { };
template <> struct define <sub_e>  : _<bin_e, sub> { };

template <> struct define <sign_e> : _<un_e, sign> { };
template <> struct define <neg_e>  : _<un_e, neg>  { };
template <> struct define <abs_e>  : _<un_e, abs> { };

template <> struct define <min_e>  : _<sym_e, min> { };
template <> struct define <max_e>  : _<sym_e, max> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(mul_e,          "mul:")
IVL_TOKEN(quot_e,         "quot:")
IVL_TOKEN(rem_e,          "rem:")
IVL_TOKEN(mod_e,          "mod:")
IVL_TOKEN(exp_e,          "exp:")
IVL_TOKEN(log_e,          "log:")

//-----------------------------------------------------------------------------

template <> struct define <mul_e>  : _<sym_e, mul>  { };
template <> struct define <quot_e> : _<bin_e, quot> { };

template <> struct define <rem_e>  : _<bin_e, rem> { };
template <> struct define <mod_e>  : _<bin_e, mod> { };

template <> struct define <exp_e>  : _<bin_e, exp> { };
template <> struct define <log_e>  : _<bin_e, log> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(it_lp,          "it_:^")
IVL_TOKEN(it_1p,          "it_1^")

//-----------------------------------------------------------------------------

template <> struct define <it_lp> :
_<fun, _<e, p, q, f>, _<scan_ll, e, _<f_split, p>, q,
	_<fun, _<_<a, dot, u>, n, i>,
		_<_<_if, _<member, _0, n>, f, cons>, a, _<i, u, _<dec_et, n> > >
	>
> >
{ };

template <> struct define <it_1p> : _<it_lp, _<>, cons, bad> { };

//-----------------------------------------------------------------------------

IVL_TOKEN(select_n,       "select#")
IVL_TOKEN(edit_n,         "edit#")

//-----------------------------------------------------------------------------

template <> struct define <select_n> :
_<inv, _<un, un_s, _<it_1n, _1st, _2nd, ___> > >
{ };

template <> struct define <edit_n> :
_<fun, _<o, n, l>, _<be, f, _<un, join, o>,
	_<if_list, _<it_1p, f, l>, _<it_1n, f, cons, _1st, l>, n>
> >
{ };

//-----------------------------------------------------------------------------

IVL_TOKEN(remove_n,       "remove#")
IVL_TOKEN(insert_ln,      "insert<#")
IVL_TOKEN(insert_rn,      "insert>#")
IVL_TOKEN(subst_n,        "subst#")

//-----------------------------------------------------------------------------

template <> struct define <remove_n>  : _<edit_n,     f_remove>   { };
template <> struct define <insert_ln> : _<un, edit_n, f_insert_l> { };
template <> struct define <insert_rn> : _<un, edit_n, f_insert_r> { };
template <> struct define <subst_n>   : _<un, edit_n, f_subst>    { };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_TUP_HPP
