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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_PRIM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_PRIM_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

template <template <typename> class F>
struct op1 : types::t1 <F> { };

template <template <typename, typename> class F>
struct op2 : types::t2 <F> { };

//-----------------------------------------------------------------------------

IVL_KEYWORD(car,            "car")
IVL_KEYWORD(cdr,            "cdr")
IVL_KEYWORD(cons,           "cons")
IVL_KEYWORD(null,           "null?")
IVL_KEYWORD(atom,           "atom?")
IVL_KEYWORD(eq,             "eq?")

//-----------------------------------------------------------------------------
#ifdef IVL_LIST_LL
//-----------------------------------------------------------------------------

template <> struct define <car>           : op1 <p_car>           { };
template <> struct define <cdr>           : op1 <p_cdr>           { };
template <> struct define <cons>          : op2 <p_cons>          { };
template <> struct define <null>          : op1 <p_null>          { };
template <> struct define <atom>          : op1 <p_atom>          { };
template <> struct define <eq>            : op2 <p_eq>            { };

//-----------------------------------------------------------------------------
#else
//-----------------------------------------------------------------------------

template <> struct define <car>  : _<fun, _<_<a, dot, ___> >, a>           { };
template <> struct define <cdr>  : _<fun, _<_<___, dot, l> >, l>           { };
template <> struct define <cons> : _<fun, _<a, _<dot, l> >, _<a, dot, l> > { };

template <> struct define <null> :
_<function,
	_<_<_<> >, _true>,
	_<_<_<dot, ___> >, _false>
>
{ };

template <> struct define <atom> :
_<function,
	_<_<_<dot, ___> >, _false>,
	_<_<___>, _true>
>
{ };

template <> struct define <eq> :
_<function,
	_<_<a, a>, _true>,
	_<_<___, ___>, _false>
>
{ };

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------

IVL_KEYWORD(o_lt,           "<")
IVL_KEYWORD(o_add,          "+")
IVL_KEYWORD(o_sub,          "-")
IVL_KEYWORD(o_mul,          "*")
IVL_KEYWORD(o_quot,         "/")

//-----------------------------------------------------------------------------

template <> struct define <o_lt>          : op2 <t_lt>            { };
template <> struct define <o_add>         : op2 <t_add>           { };
template <> struct define <o_sub>         : op2 <t_sub>           { };
template <> struct define <o_mul>         : op2 <t_mul>           { };
template <> struct define <o_quot>        : op2 <t_quot>          { };

//-----------------------------------------------------------------------------

IVL_KEYWORD(num,            "num?")
IVL_KEYWORD(lt,             "lt?")
IVL_KEYWORD(add,            "add")
IVL_KEYWORD(sub,            "sub")
IVL_KEYWORD(mul,            "mul")
IVL_KEYWORD(quot,           "quot")

//-----------------------------------------------------------------------------
#ifdef IVL_LIST_LL
//-----------------------------------------------------------------------------

template <> struct define <num>           : op1 <p_num>    { };
template <> struct define <lt>            : op2 <p_lt>     { };
template <> struct define <add>           : op2 <p_add>    { };
template <> struct define <sub>           : op2 <p_sub>    { };
template <> struct define <mul>           : op2 <p_mul>    { };
template <> struct define <quot>          : op2 <p_quot>   { };

//-----------------------------------------------------------------------------
#else
//-----------------------------------------------------------------------------

IVL_KEYWORD(bin_n,          "bin#")

//-----------------------------------------------------------------------------

template <> struct define <bin_n> :
_<lambda, _<f>, _<fun,
	_<_<hash, n1>, _<hash, n2> >, _<f, n1, n2>
> >
{ };

//-----------------------------------------------------------------------------

template <> struct define <num> :
_<function,
	_<_<_<hash, ___> >, _true>,
	_<_<___>, _false>
>
{ };

template <> struct define <lt>     : _<bin_n, o_lt>     { };
template <> struct define <add>    : _<bin_n, o_add>    { };
template <> struct define <sub>    : _<bin_n, o_sub>    { };
template <> struct define <mul>    : _<bin_n, o_mul>    { };

template <> struct define <quot> :
_<function,
	_<_<_<hash, n1>, _0>, oops>,
	_<_<_<hash, n1>, _<hash, n2> >, _<o_quot, n1, n2> >
>
{ };

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_PRIM_HPP
