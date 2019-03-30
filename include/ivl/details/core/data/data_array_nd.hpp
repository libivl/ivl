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

#ifndef IVL_CORE_DETAILS_DATA_DATA_ARRAY_ND_HPP
#define IVL_CORE_DETAILS_DATA_DATA_ARRAY_ND_HPP


namespace ivl {

namespace data {

template <class DT = types::term>
struct normal_2d
: public data_type_base<normal_2d<DT> >
{
	typedef seq_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_true is_writeable;
	typedef types::t_true is_createable;
	typedef types::t_true is_resizeable;
	typedef types::t_true has_c_ptr;
	typedef types::t_true is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<10> optimal_access_cost;
};

template <int N = 0, class DT = types::term>
struct normal_image
: public data_type_base<normal_image<N, DT> >
{
	typedef seq_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_true is_writeable;
	typedef types::t_true is_createable;
	typedef types::t_true is_resizeable;
	typedef types::t_true has_c_ptr;
	typedef types::t_true is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<10> optimal_access_cost;
	enum { Ch = N };
};

template <int N, class DT>
struct get_image_channels<normal_image<N, DT> >
{
	typedef types::number<N> type;
};

} //namespace data

typedef data::normal_2d<> normal_2d;
typedef data::normal_image<> normal_image;

} //namespace ivl



#endif // IVL_CORE_DETAILS_DATA_DATA_ARRAY_ND_HPP
