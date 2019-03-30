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

#ifndef IVL_ARRAY_DETAILS_COMMON_CONVERSIONS_ARRAY_COMMON_HPP
#define IVL_ARRAY_DETAILS_COMMON_CONVERSIONS_ARRAY_COMMON_HPP

namespace ivl {

namespace array_details {


template <class T, class OPTS, class BASE_ARRAY>
class conversions_array_common
: public BASE_ARRAY
{
private:
	typedef BASE_ARRAY base_array;

	typedef typename base_array::data_type prv_data_type;

	typedef typename base_array::derived_type prv_derived_type;

	typedef typename data::conversion<prv_data_type>::array_creation create_ar;

	typedef typename data::conversion<prv_data_type>::
		array_nd_creation create_nd;

	typedef typename data::conversion<
		prv_data_type>::derived_creation create_dv;



public:

	typedef array<T, typename create_ar::new_type> new_array;

	typedef array<T, typename create_ar::similar_type> similar_array;

	typedef typename types::
		change_data_class_set<
				typename create_dv::new_type, 
				//typename types::change_elem_type<
				//	typename types::create_new< // TODO:: should probably be new_elem_type
				//		typename types::get_templ_arg<
				//			1, 
							prv_derived_type
				//		>::type>::type,
				//prv_derived_type>::type
			>::type create_new;

	typedef typename types::
		change_data_class_set<
				typename create_dv::similar_type, 
				//typename types::change_elem_type<
				//	typename types::create_similar< // TODO:: should probably be similar_elem_type
				//		typename types::get_templ_arg<
				//			1, 
							prv_derived_type
				//		>::type>::type,
				//prv_derived_type>::type
			>::type create_similar;


};

} /* namespace array_details */

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_COMMON_CONVERSIONS_ARRAY_COMMON_HPP
