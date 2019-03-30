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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_STREAM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_STREAM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

using ivl::operator<<;

//-----------------------------------------------------------------------------

template <typename O>
O& operator<<(O& o, inf_p) { return o << "+inf"; }

template <typename O>
O& operator<<(O& o, inf_m) { return o << "-inf"; }

//-----------------------------------------------------------------------------

template <typename O>
O& operator<<(O& o, op2 <t_lt>) { return o << "@lt"; }

template <typename O>
O& operator<<(O& o, op2 <t_add>) { return o << "@add"; }

template <typename O>
O& operator<<(O& o, op2 <t_sub>) { return o << "@sub"; }

template <typename O>
O& operator<<(O& o, op2 <t_mul>) { return o << "@mul"; }

template <typename O>
O& operator<<(O& o, op2 <t_quot>) { return o << "@quot"; }

//-----------------------------------------------------------------------------

}  // namespace scheme

// TODO: remove this
using scheme::operator<<;

}  // namespace types

using ivl::types::scheme::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LANG_STREAM_HPP
