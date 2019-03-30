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

#ifndef IVL_ARRAY_2D_DETAILS_ARRAY_2D_COMMON_BASE_HPP
#define IVL_ARRAY_2D_DETAILS_ARRAY_2D_COMMON_BASE_HPP

namespace ivl {

template <class T, class OPTS>
class array_common_base<array_2d<T, OPTS> >
:
public
	array_nd<T, typename types::derive_opts<array_2d<T, OPTS> >::type>,
public
	array_common_base<common_container_base<T, array_2d<T, OPTS> > >
{
private:
	// the type of the array_2d
	typedef array_2d<T, OPTS> t;

	typedef array_nd<T, typename types::derive_opts<
		array_2d<T, OPTS> >::type> prv_base_class;
	typedef array_common_base<common_container_base<T,
		array_2d<T, OPTS> > > prv_common;

	typedef ivl::array<typename
		data::wrap_2d_iterator<prv_base_class>::value_type,
		ref_iterator<data::wrap_2d_iterator<prv_base_class> > > wrap_2d_t;
	typedef data::wrap_2d_iterator<prv_base_class> wrap_it;

	typedef ivl::array<typename
		data::wrap_2d_iterator<const prv_base_class>::value_type,
		data::ref_iterator<data::wrap_2d_iterator<const prv_base_class> >
			> const_wrap_2d_t;
	typedef data::wrap_2d_iterator<const prv_base_class> const_wrap_it;

	typedef ivl::array<typename
		data::wrap_2d_iterator<prv_base_class>::value_type,
		data::ref_iterator<data::wrap_2d_iterator<prv_base_class, 0, 1> >
			> wrap_2d_r_t;
	typedef data::wrap_2d_iterator<prv_base_class, 0, 1> wrap_it_r;

	typedef ivl::array<typename
		data::wrap_2d_iterator<const prv_base_class>::value_type,
		data::ref_iterator<data::wrap_2d_iterator<const prv_base_class, 0, 1> >
			> const_wrap_2d_r_t;
	typedef data::wrap_2d_iterator<const prv_base_class, 0, 1> const_wrap_it_r;

public:
	typedef t array_2d_type;
	typedef t array_nd_or_2d_type;
	typedef t current_type;
	typedef t container_type;

	typedef typename prv_base_class::all_init_arg all_init_arg;
	typedef typename prv_base_class::data_init_arg data_init_arg;

	t& to_current() { return static_cast<t&>(*this); }
	const t& to_current() const { return static_cast<const t&>(*this); }
	t& to_array_2d() { return static_cast<t&>(*this); }
	const t& to_array_2d() const { return static_cast<const t&>(*this); }

	typedef typename types::derive<t>::type derived_type;

	t& derived() { return static_cast<derived_type&>(to_array_2d()); }
	const t& derived() const
		{ return static_cast<const derived_type&>(to_array_2d()); }

	typedef prv_base_class base_class;

	//! default constructor
	array_common_base() { }

	//! copy constructor
	array_common_base(const array_common_base& o) : base_class(o) { }

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
	array_common_base(const array<size_t, S>& sz, const data_init_arg& y)
        : base_class(sz, y) { }

	//! chain constructor with size_array and other array
	template <class S, class J, class D>
	array_common_base(const array<size_t, S>& sz, const array<J, D>& a)
		: base_class(sz, a) { }

	//! chain constructor with other array
	template <class J, class D>
	array_common_base(const array_nd<J, D>& a)
		: base_class(a) { }

	//! (special for ref_iterator) chain constructor with other array
	template <class J, class D>
	array_common_base(array_nd<J, D>& a)
		: base_class(a) { }

	//propagation of operator =
	using base_class::operator=;
	array_common_base& operator=(const array_common_base& a)
	{
		base_class::operator=(a);
		return *this;
	}

	// special object for matrix-based operations
	using base_class::operator();

	core_details::matrix_based<const t&> operator()() const
		{ return to_current(); }

	array_2d<T, ivl::normal_2d> operator()(const core_details::transpose_arg& c) const;


//	wrap_2d_t wrap() { return wrap_2d_t(to_array_2d()); }

//	const_wrap_2d_t wrap() const { return const_wrap_2d_t(to_array_2d()); }

	wrap_2d_r_t as_rows()
		{ return wrap_2d_r_t(wrap_it_r(to_array_2d()), to_array_2d().rows()); }
	const_wrap_2d_r_t as_rows() const
		{ return const_wrap_2d_r_t(const_wrap_it_r(to_array_2d()), to_array_2d().rows()); }

	//const_wrap_2d_r_t as_rows() const
	//	{ return const_wrap_2d_r_t(to_array_2d()); }

	wrap_2d_t as_columns()
		{ return wrap_2d_t(wrap_it(to_array_2d()), to_array_2d().columns()); }
	const_wrap_2d_t as_columns() const
		{ return const_wrap_2d_t(const_wrap_it(to_array_2d()), to_array_2d().columns()); }

	//const_wrap_2d_t as_columns() const
//		{ return const_wrap_2d_t(to_array_2d()); }


	using prv_common::operator-;
	using prv_common::operator+;
	using prv_common::operator|;
	using prv_common::operator~;
	using prv_common::operator!;
	using prv_common::operator*;
	using prv_common::operator->*;


};

} /* namespace ivl */

#endif // IVL_ARRAY_2D_DETAILS_ARRAY_2D_COMMON_BASE_HPP
