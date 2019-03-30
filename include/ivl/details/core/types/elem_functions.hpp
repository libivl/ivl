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

#ifndef IVL_CORE_DETAILS_TYPES_ELEMENT_FUNCTIONS_HPP
#define IVL_CORE_DETAILS_TYPES_ELEMENT_FUNCTIONS_HPP

#if 0
namespace ivl {

namespace data {

//forward declarations
template <template<typename, typename> class F, class A1>
struct use_elem_func_unary_set;
template <template<typename, typename, typename> class F, class A1, class S2>
struct use_elem_func_scalar_r_set;
template <template<typename, typename, typename> class F, class S1, class A2>
struct use_elem_func_scalar_l_set;
template <template<typename, typename, typename> class F, class A1, class A2>
struct use_elem_func_binary_set;

} /*namespace data*/

namespace types {


template <class T, template <typename, typename> class F, class A1, class DERIVED_CLASS>
class elem_func_unary_info { };

template <class T, template <typename, typename> class F,
	class I1, class X1, class Z1, class DERIVED_CLASS>
class elem_func_unary_info<T, F, array<I1, X1, Z1>, DERIVED_CLASS>
{
	typedef I1 elem1_type;

	typedef array <I1, X1, Z1> in1_type;
	typedef typename in1_type::derived_type in1_derived;
	typedef typename to_type<T, in1_derived>::type out_class;

	typedef typename in1_derived::created_data_class_set created_data_class_set;

	typedef typename change_data_class_set <data::use_elem_func_unary_set<F, in1_type>,
		out_class>::type base_class_basic;

	typedef typename change_derived_class <DERIVED_CLASS, base_class_basic>::type base_class;
};


template <class T, template <typename, typename, typename> class F, class A1, class S2, class DERIVED_CLASS>
class elem_func_scalar_r_info { };

template <class T, template <typename, typename, typename> class F,
	class I1, class X1, class Z1, class S2, class DERIVED_CLASS>
class elem_func_scalar_r_info<T, F, array<I1, X1, Z1>, S2, DERIVED_CLASS>
{
	typedef I1 elem1_type;
	typedef S2 elem2_type;

	typedef array <I1, X1, Z1> in1_type;
	typedef typename in1_type::derived_type in1_derived;

	typedef typename to_type<T, in1_derived>::type out_class;

	typedef typename in1_derived::created_data_class_set created_data_class_set;

	typedef typename change_data_class_set <data::use_elem_func_scalar_r_set<F, in1_type, elem2_type>,
		out_class>::type base_class_basic;

	typedef typename change_derived_class <DERIVED_CLASS, base_class_basic>::type base_class;
};


template <class T, template <typename, typename, typename> class F, class S1, class A2, class DERIVED_CLASS>
class elem_func_scalar_l_info { };

template <class T, template <typename, typename, typename> class F,
	class S1, class I2, class X2, class Z2, class DERIVED_CLASS>
class elem_func_scalar_l_info<T, F, S1, array<I2, X2, Z2>, DERIVED_CLASS>
{
	typedef S1 elem1_type;
	typedef I2 elem2_type;

	typedef array <I2, X2, Z2> in2_type;
	typedef typename in2_type::derived_type in2_derived;

	typedef typename to_type<T, in2_derived>::type out_class;

	typedef typename in2_derived::created_data_class_set created_data_class_set;

	typedef typename change_data_class_set <data::use_elem_func_scalar_l_set<F, elem1_type, in2_type>,
		out_class>::type base_class_basic;

	typedef typename change_derived_class <DERIVED_CLASS, base_class_basic>::type base_class;
};


template <class T, template <typename, typename, typename> class F, class A1, class A2, class DERIVED_CLASS>
class elem_func_binary_info { };

template <class T, template <typename, typename, typename> class F,
	class I1, class X1, class Z1, class I2, class X2, class Z2, class DERIVED_CLASS>
class elem_func_binary_info<T, F, array<I1, X1, Z1>, array<I2, X2, Z2>, DERIVED_CLASS>
{
	typedef I1 elem1_type;
	typedef I2 elem2_type;

	typedef array <I1, X1, Z1> in1_type;
	typedef typename in1_type::derived_type in1_derived;
	typedef array <I2, X2, Z2> in2_type;
	typedef typename in2_type::derived_type in2_derived;
	typedef typename to_type<T, in1_derived>::type in1_canonical;
	typedef typename to_type<T, in2_derived>::type in2_canonical;

	typedef typename t_if<is_base_eq<in1_canonical, in2_canonical>,
						in2_canonical, in1_canonical>::type out_class;

	typedef typename in1_derived::created_data_class_set created_data_class_set;

	typedef typename change_data_class_set <data::use_elem_func_binary_set<F, in1_type, in2_type>,
		out_class>::type base_class_basic;

	typedef typename change_derived_class <DERIVED_CLASS, base_class_basic>::type base_class;
};


} /* namespace types */

} /* namespace ivl */
#endif

#endif // IVL_CORE_DETAILS_TYPES_ELEMENT_FUNCTIONS_HPP
