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

#ifndef IVL_CORE_DETAILS_TYPES_TEMPLATE_FUN_HPP
#define IVL_CORE_DETAILS_TYPES_TEMPLATE_FUN_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

// function templates mapped to structs
struct template_function_id { };

template <int NUM, class DERIVED>
struct template_function : public template_function_id
{
	const static int N = NUM;
	typedef DERIVED derived_type;
	typedef template_function <NUM, DERIVED> template_function_type;
};

//-----------------------------------------------------------------------------

template<template <typename> class F>
struct tfun1 : public template_function <1, tfun1 <F> >
{
	typedef tfun1 <F> type;
	template <class T1>
	struct map : F <T1> { };
};

template<template <typename, typename> class F>
struct tfun2 : public template_function <2, tfun2 <F> >
{
	typedef tfun2 <F> type;
	template <class T1, class T2>
	struct map : F <T1, T2> { };
};

template<template <typename, typename, typename> class F>
struct tfun3 : public template_function <3, tfun3 <F> >
{
	typedef tfun3 <F> type;
	template <class T1, class T2, class T3>
	struct map : F <T1, T2, T3> { };
};

//-----------------------------------------------------------------------------

} // namespace types

//-----------------------------------------------------------------------------

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_TEMPLATE_FUN_HPP
