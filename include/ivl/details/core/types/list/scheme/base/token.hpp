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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_BASE_TOKEN_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_BASE_TOKEN_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

struct token_id { };
struct keyword_id { };
struct identifier_id { };

template <typename T>
struct token : token_id, t_id <T> { };

template <typename T>
struct keyword : keyword_id, token <T> { };

template <typename T>
struct identifier : identifier_id, token <T> { };

template <typename T>
struct label { static char text[]; };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_BASE_TOKEN_HPP
