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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_LOW_PRIM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_LOW_PRIM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

namespace prim {

//-----------------------------------------------------------------------------

template <typename T>
struct p_car : nat <p_car <T> > { };

template <>
struct p_car <list_details::null> : nat <p_car <list_details::null> > { };

template <typename T, typename TN>
struct p_car <node <T, TN> > : id <T> { };

//-----------------------------------------------------------------------------

template <typename T>
struct p_cdr : nat <p_cdr <T> > { };

template <>
struct p_cdr <list_details::null> : nat <p_cdr <list_details::null> > { };

template <typename T, typename TN>
struct p_cdr <node <T, TN> > : TN { };

//-----------------------------------------------------------------------------

template <typename T, typename R>
struct p_cons : nat <p_cons <skip, R> > { };

template <typename T>
struct p_cons <T, list_details::null> : node <T> { };

template <typename T, typename R, typename RN>
struct p_cons <T, node <R, RN> > : node <T, node <R, RN> > { };

//-----------------------------------------------------------------------------

template <typename T>
struct p_null : nat <p_null <T> > { };

template <>
struct p_null <list_details::null> : _true { };

template <typename T, typename TN>
struct p_null <node <T, TN> > : _false { };

//-----------------------------------------------------------------------------

template <typename T>
struct p_atom : _true { };

template <typename T, typename TN>
struct p_atom <node <T, TN> > : _false { };

//-----------------------------------------------------------------------------

template <typename T1, typename T2>
struct p_eq : t_if <
	t_and <typename p_atom <T1>::type, typename p_atom <T2>::type>,
	t_eq <T1, T2>, nat <p_eq <T1, T2> >
>::type { };

//-----------------------------------------------------------------------------

template <typename T>
struct p_num : _false { };

template <int N>
struct p_num <number <N> > : _true { };

//-----------------------------------------------------------------------------

template <typename T1, typename T2>
struct p_lt : nat <p_lt <T1, T2> > { };

template <int N1, int N2>
struct p_lt <number <N1>, number <N2> > : t_lt <number <N1>, number <N2> > { };

//-----------------------------------------------------------------------------

template <typename T1, typename T2>
struct p_add : nat <p_add <T1, T2> > { };

template <int N1, int N2>
struct p_add <number <N1>, number <N2> > : t_add <number <N1>, number <N2> > { };

//-----------------------------------------------------------------------------

template <typename T1, typename T2>
struct p_sub : nat <p_sub <T1, T2> > { };

template <int N1, int N2>
struct p_sub <number <N1>, number <N2> > : t_sub <number <N1>, number <N2> > { };

//-----------------------------------------------------------------------------

template <typename T1, typename T2>
struct p_mul : nat <p_mul <T1, T2> > { };

template <int N1, int N2>
struct p_mul <number <N1>, number <N2> > : t_mul <number <N1>, number <N2> > { };

//-----------------------------------------------------------------------------

template <typename T1, typename T2>
struct p_quot : nat <p_quot <T1, T2> > { };

template <int N>
struct p_quot <number <N>, number <0> > :
	nat <p_quot <number <N>, number <0> > > { };

template <int N1, int N2>
struct p_quot <number <N1>, number <N2> > :
	t_quot <number <N1>, number <N2> > { };

//-----------------------------------------------------------------------------

}  // namespace prim

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_t       <prim::p_car>             ::name[] = "p_car";
template <> char template_t       <prim::p_cdr>             ::name[] = "p_cdr";
template <> char template_tt      <prim::p_cons>            ::name[] = "p_cons";
template <> char template_t       <prim::p_null>            ::name[] = "p_null";
template <> char template_t       <prim::p_atom>            ::name[] = "p_atom";
template <> char template_tt      <prim::p_eq>              ::name[] = "p_eq";

template <> char template_t       <prim::p_num>             ::name[] = "p_num";
template <> char template_tt      <prim::p_lt>              ::name[] = "p_lt";
template <> char template_tt      <prim::p_add>             ::name[] = "p_add";
template <> char template_tt      <prim::p_sub>             ::name[] = "p_sub";
template <> char template_tt      <prim::p_mul>             ::name[] = "p_mul";
template <> char template_tt      <prim::p_quot>            ::name[] = "p_quot";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details

using namespace list_details::prim;

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_LOW_PRIM_HPP
