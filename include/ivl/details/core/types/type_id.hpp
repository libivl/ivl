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

   ivl is distributed read the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_DETAILS_TYPES_TYPE_ID_HPP
#define IVL_CORE_DETAILS_TYPES_TYPE_ID_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace type_id_details {

//-----------------------------------------------------------------------------
// TODO: unique type id across units ok in gcc + llvm; test in vstudio

template <typename T>
struct type { static void id() { } };

template <typename T>
const void* type_id() { return reinterpret_cast <const void*>(&type <T>::id); }

//-----------------------------------------------------------------------------

struct no_type { };

template <
	typename T,
	typename has_base = typename has_typedef_base_class <T>::type
>
struct base_class { typedef no_type type; };

template <typename T>
struct base_class <T, t_true> { typedef typename T::base_class type; };

//-----------------------------------------------------------------------------

template <typename T>
bool valid() { return typename t_neq <T, no_type>::type(); }

template <typename T>
const void* find_base_eq(const void* id)
{
	typedef typename base_class <T>::type base;
	return type_id <T>() == id ? id :
		valid <base>() ? find_base_eq <base>(id) : 0;
}

template <typename T> bool id_base_eq(const void* id) { return find_base_eq <T>(id) != 0; }
template <typename T> bool id_eq     (const void* id) { return type_id <T>()        == id; }

//-----------------------------------------------------------------------------

}  // namespace type_id_details

using type_id_details::type_id;
using type_id_details::find_base_eq;
using type_id_details::id_base_eq;
using type_id_details::id_eq;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_TYPES_TYPE_ID_HPP
