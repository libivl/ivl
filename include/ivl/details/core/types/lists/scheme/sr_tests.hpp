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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_SR_TESTS_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_SR_TESTS_HPP

namespace ivl {

namespace types {

namespace scheme {

//-----------------------------------------------------------------------------

typedef lists::details::is_identifier<v>::type is_id_v;

KEYWORD(sr, "sr" )
template<> struct define<sr> : 
_<fun_rules, _<
	_<v>,
	_<lambda, _<>, _<v, v> >
> > { };

KEYWORD(sr2, "sr2" )
template<> struct define<sr2> : 
_<fun_rules, _<>, 
_<
	_<v>,
	_<lambda, _<>, _<v, v> >
>,
_<
	_<v, w, v>,
	_<lambda, _<>, _<number<2>, v, v> >
>,
_<
	_<v, v>,
	_<lambda, _<>, _<number<3>, v, v> >
>,
_<
	_<v, w>,
	_<lambda, _<>, _<number<4>, v, v> >
> 
> { };

KEYWORD(sr32, "sr32" )
template<> struct define<sr32> : 
_<fun_rules, _<>, 
_<
	_<_<v, etc>, _<w, etc> >,
	_<lambda, _<>, _<_<v, etc>, _<v, etc>, _<w, etc>, v, w, number<1>, _<_<v, w>, etc> > >
> 
> { };

KEYWORD(sr31, "sr31" )
template<> struct define<sr31> : 
_<fun_rules, _<number<0> >, 
_<
	_<_<number<0>, v, etc> >,
	_<lambda, _<>, _<number<1>, _<v, etc>, _<number<0>, v, etc> > >
>,
_<
	_<_<number<1>, v, etc> >,
	_<lambda, _<>, _<number<1>, number<2>, _<v, etc>, _<number<1>, v, etc> > >
> 
> { };
KEYWORD(fif,            "fif")

template <> struct define <fif> :
_<fun_rules, _<
	_<c, t, e>,
	_<cond, _<c, t>, _<_else, e> >
> >
{ };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types
}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_SR_TESTS_HPP
