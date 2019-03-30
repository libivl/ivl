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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_DATA_TOOLS_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_DATA_TOOLS_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename L, typename R>
struct append : nat <append <L, R> > { };

template <typename R, typename RN>
struct append <null, node <R, RN> > : node <R, RN> { };

template <typename L, typename LN, typename R, typename RN>
struct append <node <L, LN>, node <R, RN> > :
	node <L, typename append <LN, typename node <R, RN>::type>::type> { };

//-----------------------------------------------------------------------------

template <typename T>
struct reverse : nat <reverse <T> > { };

template <>
struct reverse <null> : null { };

template <typename T, typename TN>
struct reverse <node <T, TN> > :
	append <typename reverse <TN>::type, typename node <T>::type> { };

//-----------------------------------------------------------------------------

template <typename Q, typename L>
struct member : _false { };

template <typename Q>
struct member <Q, null> : _false { };

template <typename Q, typename T, typename TN>
struct member <Q, node <T, TN> > :
	t_if <t_eq <Q, T>, _true, member <Q, TN> >::type { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_tt      <append>                ::name[] = "append";
template <> char template_t       <reverse>               ::name[] = "reverse";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_DATA_TOOLS_HPP
