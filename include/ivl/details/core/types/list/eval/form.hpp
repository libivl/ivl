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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_EVAL_FORM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_EVAL_FORM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename T>
struct quote : nat <quote <T> > { };

template <typename T>
struct quote <node <T> > : id <T> { };

template <typename T, typename S>
struct value <node <scheme::quote, T>, S> : quote <T>, idle <S> { };

//-----------------------------------------------------------------------------
// set! form

template <typename D, typename S>
struct set_bang : bad <set_bang <D, skip> > { };

template <typename I, typename V, typename S>
struct set_bang <node <I, node <V> >, S> :
	set <I, typename eval <V, S>::type, S> { };

template <typename D, typename S>
struct value <node <scheme::set_b, D>, S> :
	nat <value <node <scheme::set_b, D>, skip> >, set_bang <D, S> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_t       <quote>                 ::name[] = "quote";
template <> char template_tt      <set_bang>              ::name[] = "set_bang";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_EVAL_FORM_HPP
