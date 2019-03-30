/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_QT_CORE_TUPLE_HPP
#define IVL_QT_CORE_TUPLE_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

// TODO: integrate with types::term
struct term { };

template <
	typename T00 = term, typename T01 = term, typename T02 = term,
	typename T03 = term, typename T04 = term, typename T05 = term,
	typename T06 = term, typename T07 = term, typename T08 = term,
	typename T09 = term
> struct tuple { };

//-----------------------------------------------------------------------------

template <typename T>
struct car;

template <
	typename T00, typename T01, typename T02, typename T03, typename T04,
	typename T05, typename T06, typename T07, typename T08, typename T09
> struct car <tuple <T00, T01, T02, T03, T04, T05, T06, T07, T08, T09> >
{
	typedef T00 type;
};

//-----------------------------------------------------------------------------

template <typename T>
struct cdr;

template <
	typename T00, typename T01, typename T02, typename T03, typename T04,
	typename T05, typename T06, typename T07, typename T08, typename T09
> struct cdr <tuple <T00, T01, T02, T03, T04, T05, T06, T07, T08, T09> >
{
	typedef tuple <T01, T02, T03, T04, T05, T06, T07, T08, T09> type;
};

//-----------------------------------------------------------------------------

template <unsigned P, typename T>
struct at : at <P - 1, typename cdr <T>::type> { };

template <typename T>
struct at <0, T> : car <T> { };

//-----------------------------------------------------------------------------

}  // namespace delegate_details

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_TUPLE_HPP
