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

#ifndef IVL_IMAGE_DETAILS_IMAGE_COMMON_BASE_HPP
#define IVL_IMAGE_DETAILS_IMAGE_COMMON_BASE_HPP

namespace ivl {

template <class T, class OPTS>
class array_common_base<image<T, OPTS> >
:
	public types::t_if<

	// image of 1 channel is array_2d !
	types::t_eq<typename data::get_image_channels<
		OPTS>::type, types::number<1> >,

	//types::t_expr<(
	//	OPTS::image_channels == 1)>,

	array_2d<T, typename types::derive_opts<image<T, OPTS> >::type>,

	array_nd<T, typename types::derive_opts<image<T, OPTS> >::type>

	>::type,

	public array_common_base<common_container_base<T, image<T, OPTS> > >
{
private:
	//typedef typename data::get_image_channels<
	//	typename OPTS::data_type>::type prv_im_channels;

	//enum { N = prv_im_channels::value };

	// the type of the image
	typedef image<T, OPTS> t;

	typedef array_common_base<
		common_container_base<T, image<T, OPTS> > > prv_common;

	typedef array_common_base prv_this_type;

	typedef typename prv_this_type::array_nd_or_2d_type prv_base_class;
	/*
	typedef typename types::t_if<types::t_expr<(N == 1)>, // image of 1 channel is array_2d !
		array_2d<T, DATA_CLASS_SET, typename types::derive <t> ::type>,
		array_nd<T, DATA_CLASS_SET, typename types::derive <t> ::type>
	>::type prv_base_class;*/

public:
	using prv_base_class::Ch;

	typedef prv_base_class base_class;

	typedef t image_type;
	typedef t current_type;
	typedef t container_type;

	typedef typename prv_base_class::all_init_arg all_init_arg;
	typedef typename prv_base_class::data_init_arg data_init_arg;

	t& to_current() { return static_cast<t&>(*this); }
	const t& to_current() const { return static_cast<const t&>(*this); }
	t& to_image() { return static_cast<t&>(*this); }
	const t& to_image() const { return static_cast<const t&>(*this); }

	typedef typename types::derive<t>::type derived_type;

	t& derived() { return static_cast<derived_type&>(to_image()); }
	const t& derived() const
		{ return static_cast<const derived_type&>(to_image()); }

	//! default constructor
	array_common_base() { }

	//! copy constructor
	array_common_base(array_common_base& o) : base_class(o) { }

	//! chain constructor with all_init_arg (for special array types)
	array_common_base(all_init_arg y) : base_class(y) { }

	//! chain constructor with size_array
	template <class S>
	array_common_base(const array<size_t, S>& sz) : base_class(sz) { }

	//! chain constructor with size_array and pointer
	template <class S>
	array_common_base(const array<size_t, S>& sz, const T* x)
		: base_class(sz, x) { }

	//! chain constructor with size_array and value reference
	template <class S>
	array_common_base(const array<size_t, S>& sz, const T& x)
		: base_class(sz, x) { }

	//! chain constructor with size_array and data_init_arg (special arg)
	template <class S>
	array_common_base(const array<size_t, S>& sz, const data_init_arg &y)
        : base_class(sz, y) { }

	//! chain constructor with size_array and other array
	template <class S, class J, class D>
	array_common_base(const array<size_t, S>& sz, const array<J, D>& a)
		: base_class(sz, a) { }

	//! chain constructor with other array
	template <class J, class D>
	array_common_base(const array_nd<J, D>& x) : base_class(x) { }

	//! (special for ref_iterator) chain constructor with other array
	template <class J, class D>
	array_common_base(array_nd<J, D>& x) : base_class(x) { }

	//propagation of operator =
	using base_class::operator=;
	array_common_base& operator=(const array_common_base& a)
	{
		base_class::operator=(a);
		return *this;
	}

	using prv_common::operator-;
	using prv_common::operator+;
	using prv_common::operator|;
	using prv_common::operator~;
	using prv_common::operator!;
	using prv_common::operator*;
	using prv_common::operator->*;

};

} /* namespace ivl */

#endif // IVL_IMAGE_DETAILS_IMAGE_COMMON_BASE_HPP
