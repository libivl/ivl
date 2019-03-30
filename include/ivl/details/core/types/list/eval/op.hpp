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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_EVAL_OP_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_EVAL_OP_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------
// template function (struct) representation, with specified (op_N) or
// arbitrary (op) arity (number of arguments). can be derived, in which case
// map points to the base class. op can be lazy, in which case the expressions
// given for its arguments are not evaluated. F = function, A = argument.

template <typename T>
struct is_op : is_base <template_class_id, T> { };

template <typename T, typename THEN, typename ELSE>
struct if_op : t_if <is_op <T>, THEN, ELSE> { };

//-----------------------------------------------------------------------------

template <typename F, int Z = 0>
struct op : template_class <0, op <F, Z> > { };

template <typename T, int Z = 0>
struct map_op : op <types::t2 <T::template map>, Z> { };

//-----------------------------------------------------------------------------

template <typename O>
struct pt { };

template <typename T, int Z = 0>
struct pt_map_op : op <pt <types::t2 <T::template map> >, Z> { };

//-----------------------------------------------------------------------------

template <typename F, typename V, typename S>
struct apply_op_map: nat <apply_op_map <F, V, S> >, bad <> { };

template <template <typename, typename> class F, typename V, typename S>
struct apply_op_map <types::t2 <F>, V, S> : F <V, S> { };

//-----------------------------------------------------------------------------
// apply a template function to a list of values for its arguments. checks the
// number of values if the arity is specified. F = function, V = value.

template <typename F, typename V, typename S>
struct apply_map: nat <apply_map <F, V, S> >, bad <> { };

template <typename F, int Z, typename V, typename S>
struct apply_map <op <F, Z>, V, S> : apply_op_map <F, V, S> { };

template <template <typename> class F, typename V, typename S>
struct apply_map <types::t1 <F>, node <V>, S> : F <V>, idle <S> { };

template <
	template <typename, typename> class F,
	typename V1, typename V2, typename S
>
struct apply_map <types::t2 <F>, node <V1, node <V2> >, S> :
	F <V1, V2>, idle <S> { };

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_ttt     <apply_op_map>          ::name[] = "apply_op_map";
template <> char template_ttt     <apply_map>             ::name[] = "apply_map";

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_EVAL_OP_HPP
