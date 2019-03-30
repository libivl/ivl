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

#ifndef IVL_CORE_DETAILS_IVL_FUNC_TOOLS_GET_1ST_ELEM_TYPE_HPP
#define IVL_CORE_DETAILS_IVL_FUNC_TOOLS_GET_1ST_ELEM_TYPE_HPP

namespace ivl {

namespace core_details {

namespace get_1st_elem_type_details {

template <class TUP, int I, int E, class VT, class IS_C>
struct get_1st_t_op_3 { };

template <class TUP, int I, int E, class VT>
struct get_1st_t_op_2
: public get_1st_t_op_3<TUP, I, E, VT, typename types::is_ivl_array<VT>::type>
{
};

template <class TUP, int I, int E>
struct get_1st_t_op_1
: public get_1st_t_op_2<TUP, I, E, typename TUP::template val_t<I>::type>
{
};

template <class TUP, int I>
struct get_1st_t_op_1<TUP, I, E>
{
	// If there is an error here you probably supplied
	// a wrong argument to a template rvalue-func function.
	// no ::type
};

// specializations
template <class TUP, int I, int E, class VT>
struct get_1st_t_op_3 <TUP, I, E, VT, types::t_true>
{
	typedef typename VT::elem_type type;
};

template <class TUP, int I, int E, class VT>
struct get_1st_t_op_3 <TUP, I, E, VT, types::t_false>
{
	typedef typename get_1st_t_op1<TUP, I + 1, E>::type type;
};

} /* namespace get_1st_elem_type_details */

template <class TUP>
struct get_1st_elem_type
{
	typedef typename get_1st_elem_type_details::
		get_1st_t_op_1<TUP, 1, TUP::size + 1>::type type;
};

} /* namespace core_details */

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_IVL_FUNC_TOOLS_GET_1ST_ELEM_TYPE_HPP
