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

#ifndef IVL_DETAILS_ARRAY_BASE_ARRAY_BASE_HPP
#define IVL_DETAILS_ARRAY_BASE_ARRAY_BASE_HPP

namespace ivl {

//! Base class for all type of arrays
template <class T, class SPEC, bool VALID = true>
class array_base :
	public SPEC, public types::array_identifier
{
private:
	typedef array_base prv_this_type;

	// note: only the array_base can get the derived type directly from SPEC
	typedef typename prv_this_type::derived_param prv_derived_type;

	template <class A>
	struct hc_tpl
	{
		typedef typename types::highest_common<
			prv_derived_type,
			typename A::derived_type>::type_a type;
	};
	struct invalid_init_arg {};

public:
	typedef T elem_type;
	typedef array_base this_type;

	// useful
	typedef typename SPEC::template change_derived_param<types::term>
		::type data_type;
	typedef typename data::get_image_channels<data_type>::type im_channels;
	enum { Ch = im_channels::value };
	//
	typedef types::invalid_arg_t<invalid_init_arg> all_init_arg;
	typedef types::invalid_arg_t<invalid_init_arg> data_init_arg;

    typedef prv_derived_type derived_type;

	const derived_type& derived() const
		{ return *static_cast<const derived_type*>(this); }
	derived_type& derived()
		{ return *static_cast<derived_type*>(this); }
	derived_type& const_cast_derived() const
		{ return *static_cast<derived_type*>(const_cast<array_base*>(this)); }

	template <class A>
	const typename hc_tpl<A>::type& highest_common_class(const A* = 0) const
		{ return *static_cast<const typename hc_tpl<A>::type*>(this); }
	template <class A>
	typename hc_tpl<A>::type& highest_common_class(const A* = 0)
		{ return *static_cast<typename hc_tpl<A>::type*>(this); }

};

template <class T, class S>
class array_base<T, S, false>
{
	array_base() {} // private
};

// TODO: this is just wrong! no functions should be actually declared for array_base.
// there is array_common_base for such purposes
//! ostream operator<< overload for array_base
template <class T, class S>
std::ostream& operator<<(std::ostream& os, const array_base <T, S, true>& in)
{
	return in.derived().print(os);
}

template <class C>
class array_common_base
{
};

template <class T, class C>
class common_container_base
{
};

} //namespace ivl

#endif // IVL_DETAILS_ARRAY_BASE_ARRAY_BASE_HPP
