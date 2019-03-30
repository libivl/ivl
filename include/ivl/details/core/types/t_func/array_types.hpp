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

#ifndef IVL_CORE_DETAILS_TYPES_ARRAY_TYPES_HPP
#define IVL_CORE_DETAILS_TYPES_ARRAY_TYPES_HPP

namespace ivl {
namespace types {

//-----------------------------------------------------------------------------
	
namespace types_details {

template <class T, class IS_ARRAY>
struct get_value_t {};

template <class T>
struct get_value_t<T, t_false>
{
	typedef term subtype;
	typedef T type;
	typedef T inner_type;
};
/*
template <class T>
struct get_value_t<T, t_true>
: public get_value_t<typename T::elem_type,
	typename types::is_array<typename T::elem_type>::type>
{
};*/
template <class T>
struct get_value_t<T, t_true>
{
	typedef typename T::elem_type type;
	typedef typename T::elem_type subtype;
	typedef typename get_value_t<typename T::elem_type,
		typename is_ivl_array<typename T::elem_type>::type>
		::inner_type inner_type;
};

} /* namespace types_details */

template <class T>
class get_value
: public
	types_details::get_value_t<T, typename types::is_ivl_array<T>::type>
{
};

template <class T>
struct get_inner_value
{
	typedef typename types_details::
		get_value_t<T, typename types::is_ivl_array<T>::type>::
			inner_type type;
};

template <class T>
struct subtype
{
	typedef typename types_details::
		get_value_t<T, typename types::is_ivl_array<T>::type>::
			subtype type;
};	
	

//-----------------------------------------------------------------------------
// iavr: reference to element of array
// kimon: made it more generic
namespace types_details {

template <class T>
struct elem_ref_impl : t_id<typename bare_type<T>::type::best_reference> { };

template <class T>
struct elem_ref_impl<const T> : 
	t_id<typename bare_type<T>::type::const_reference> { };

template <class T>
struct elem_ref_impl<const T&> : 
	t_id<typename bare_type<T>::type::const_reference> { };
	
} // namespace types_details

template <class T>
struct elem_ref : t_if<is_ivl_array<typename bare_type<T>::type>, 
	types_details::elem_ref_impl<T>,
	apply_const<typename bare_type<T>::type&, is_const<T> > >::type { };

template <class T>
struct elem_ref_inner : t_if<is_ivl_array<typename bare_type<T>::type>, 
	elem_ref_inner<typename elem_ref<T>::type>,
	elem_ref<T> >::type { };

//-----------------------------------------------------------------------------

// iavr: specify type T or choose default type D
// if T is term

template<class T, class D>
struct spec_or_default
{
	typedef typename t_if<t_eq<T, term>, D, T>::type type;
};


//-----------------------------------------------------------------------------

namespace types_details {

template <class T, class IS_ARRAY>
struct create_new_tool { };

template <class T>
struct create_new_tool<T, t_true>
{
	typedef typename T::create_new create_new;
	typedef typename T::create_similar create_similar;
};

template <class T>
struct create_new_tool<T, t_false>
{
	typedef T create_new;
	typedef T create_similar;
};

} /* namespace types_details */

template <class T>
struct create_new
{
	typedef typename types_details::create_new_tool<T,
		typename is_ivl_array<T>::type>::create_new type;
};

template <class T>
struct create_similar
{
	typedef typename types_details::create_new_tool<T,
		typename is_ivl_array<T>::type>::create_similar type;
};

// ---------------------------------------------------------------------


} /* namespace types */

} /* namespace ivl */


#endif // IVL_CORE_DETAILS_TYPES_ARRAY_TYPES_HPP
