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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STATE_LOOKUP_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STATE_LOOKUP_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename T, typename THEN, typename ELSE>
struct if_none : t_if <t_eq <T, none>, THEN, ELSE> { };

template <typename T, typename D>
struct on_none : if_none <typename T::type, D, T>::type { };

//-----------------------------------------------------------------------------

// defined in eval
template <typename T, typename S>
struct use;

template <typename Q, typename S>
struct global_syntax : use <scheme::define_syntax <Q>, S> { };

template <typename Q, typename S>
struct global : use <scheme::define <Q>, S> { };

template <typename Q, typename E, typename M>
struct local_env : E::template lookup <Q, M> { };

template <typename Q, typename S>
struct local : local_env <Q, typename S::env, typename S::mem>, idle <S> { };

template <typename Q, typename E, typename M>
struct bound_env : E::template bound <Q, M> { };

template <typename Q, typename S>
struct bound : bound_env <Q, typename S::env, typename S::mem> { };

//-----------------------------------------------------------------------------

template <typename Q, typename S>
struct lookup_syntax : on_none <global_syntax <Q, S>, give <Q, S> > { };

template <typename Q, typename S, int Z>
struct lookup_global : on_none <global <Q, S>, lookup_syntax <Q, S> > { };

template <typename Q, typename S>
struct lookup_global <Q, S, 1> : give <Q, S> { };

template <typename Q, typename S, int Z>
struct lookup_local : on_none <local <Q, S>, lookup_global <Q, S, Z> > { };

template <typename Q, typename S, int Z>
struct lookup : lookup_local <Q, S, Z> { };

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STATE_LOOKUP_HPP
