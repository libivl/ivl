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




template <class T,
		 template <typename, typename, typename> class F,
		 class A1, class A2, bool SWAP_ARGS,
		 class PARAMS, // this argument is redundant. used for convenience
		 class DERIVED_INFO
	     >
class array_nd<T,
	data::array_traits<data::binary_elem_func_data_id<F, A1, A2, SWAP_ARGS>,
	PARAMS>, DERIVED_INFO> :

	public array<T, data::array_traits<data::binary_elem_func_data_id<F,
		A1, A2, SWAP_ARGS>, PARAMS>,
		typename types::derive <array_nd <T, data::array_traits<data::
			binary_elem_func_data_id<F, A1, A2, SWAP_ARGS>, PARAMS>,
			DERIVED_INFO> >::type>,

	public
	array_nd_details::basic_iterator_nd_interface<T, DATA_CLASS_SET, DERIVED_INFO>,
	public
	array_nd_details::array_nd_common_expander<T, DATA_CLASS_SET, DERIVED_INFO>
{
private:
	class not_a_type {};


public:
	typedef DATA_CLASS_SET data_type;

	typedef array_nd <T, data_type, DERIVED_INFO> this_type;

	typedef this_type this_array_nd_type;

	typedef typename types::derive<this_type>::type derived_type;

	typedef array<T, data_type, derived_type> base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! return type of size_nd in that data-specific class
	typedef typename A1::size_nd_type size_nd_type;

	//! return type of stride in that data-specific class
	typedef typename types::t_if<typename array_nd::has_random_access,
		typename A1::stride_type, not_a_type>::type stride_type;

	//! types that specify the defined parenthesis operators for this class
	typedef typename types::t_and<
		typename A1::has_1d_parenthesis,
		typename A2::has_1d_parenthesis,
		>::type has_1d_parenthesis;

	typedef typename types::t_and<
		typename A1::has_2d_parenthesis,
		typename A2::has_2d_parenthesis,
		>::type has_2d_parenthesis;

	typedef typename types::t_and<
		typename A1::has_3d_parenthesis,
		typename A2::has_3d_parenthesis,
		>::type has_3d_parenthesis;

	typedef typename types::t_and<
		typename A1::has_nd_parenthesis,
		typename A2::has_nd_parenthesis,
		>::type has_nd_parenthesis;

	using base_class::derived;

	//! get base class
	base_class& base() { return *this; }
	const base_class& base() const { return *this; }

	/** @name Element access (multidimensional)
	 * Elements can be accessed by specifying the
	 */
	//@{
	T& operator()(size_t s1);
	T& operator()(size_t s1, size_t s2);
	T& operator()(size_t s1, size_t s2, size_t s3);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5, size_t s6);
	//! Selects a single, mutable element of the array,
	//! using a size_array for the coordinates.
	template<class S, class K>
	T& operator()(const array<size_t, S, K>& indx)
		{ return derived()[sub2ind(derived(), indx)]; }

	const T& operator()(size_t s1) const;
	const T& operator()(size_t s1, size_t s2) const;
	const T& operator()(size_t s1, size_t s2, size_t s3) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5, size_t s6) const;
	//! Selects a single, const element of the array,
	//! using a size_array for the coordinates.
	template<class S, class K>
	const T& operator()(const array<size_t, S, K>& indx) const
		{ return derived()[sub2ind(derived(), indx)]; }
	//@}



/** @name constructors */
/**@{*/

	//! Default constructor
	array_nd() { }

	//! Copy constructor
	array_nd(const array_nd& a) { in1 = a.in1; in2 = a.in2; }

/**@}*/



/** @name Size functions (multidimensional)
@{*/
	//! Get the size for each dimension
	size_nd_type size_nd() const { return in1->size_nd(); }

	//! Get the size for a specific dimension
	size_t size_nd(size_t d) const { return in1->size_nd(d); }

	//! Get the stride for each dimension
	stride_type stride(typename tool::brackets_arg
		enable = typename tool::brackets_arg()) const { return in1->stride(); }

	//! Get the size for each dimension
	size_type size() const { return in1->size(); }

	//! Get the number of dimensions
	size_t ndims() const { return in1->ndim(); }
/**@}*/



};


