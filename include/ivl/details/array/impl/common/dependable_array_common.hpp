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

#ifndef IVL_ARRAY_DETAILS_COMMON_DEPENDABLE_ARRAY_COMMON_HPP
#define IVL_ARRAY_DETAILS_COMMON_DEPENDABLE_ARRAY_COMMON_HPP

namespace ivl {

namespace array_details {



// This class provides specializations of the array_common_base
// that depend on some traits of the array: is_writeable, is_resizeable.
template <
class T, class S,
class BASE,
class IS_WRITEABLE, class IS_RESIZEABLE>
class dependable_array_common
{
};

// Writeable but Not Resizeable
template <class T, class S, class B>
class dependable_array_common<T, S, B, types::t_true, types::t_false>
: public readwrite_array_common<T, S, B, types::t_true>
{
private:
	typedef array<T, S> t;
	typedef dependable_array_common prv_this_type;
	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }

protected:
	typedef dependable_array_common direct_base;

	template <class J, class D>
	void init_size_with_array(const array<J, D>& o)
	{
		// need this because we want only first elements
		ivl::copy_out(*this, o);

		//loop_on<loops::assign_copy_class>(to_array().derived(), o);
	}

	template <class J>
	void init_size_with_element(const J& o)
	{
		loop_on<loops::assign_copy_class>(to_array(), o);
	}

public:
	typedef typename prv_this_type::derived_type derived_type;

	template <class A>
	derived_type& assign_array(const A& o)
	{
		CHECK(to_array().length() == o.length(), eshape());
		// users guide: is you have a compiler error here it probably means that
		// you are calling assign_array with something that is not an ivl array.

		loop_on<loops::assign_copy_class>(to_array().derived(), o);
		return to_array().derived();
	}

	template <class A>
	derived_type& assign_array(const ret<A>& o)
	{
		CHECK(to_array().length() == o.length(), eshape());
		// users guide: is you have a compiler error here it probably means that
		// you are calling assign_array with something that is not an ivl array.

		to_array().derived().swap(o.ret_base());
		return to_array().derived();
	}

	// writeable but not resizeable arrays behave like this: assign
	// the value to all elements when assign_element is called.
	template <class J>
	derived_type& assign_element(const J& o)
	{
		loop_on<loops::assign_copy_class>(to_array().derived(), o);
		return to_array().derived();
	}

	dependable_array_common() {}
};

// Resizeable but Not Writeable (not usual.)
template <class T, class S, class B>
class dependable_array_common<T, S, B, types::t_false, types::t_true>
: public readwrite_array_common<T, S, B, types::t_false>
{
private:
	typedef array<T, S> t;
	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }

protected:
	typedef dependable_array_common direct_base;
/*
	template <class D, class P>
	const derived_type& operator=(const array<T, D, P>& o) const
	{
		// silently exist but cannot be called
		return to_array().derived();
	}
*/

public:
	dependable_array_common() {}
};

// Writeable and Resizeable
template <class T, class S, class B>
class dependable_array_common<T, S, B, types::t_true, types::t_true>
: public readwrite_array_common<T, S, B, types::t_true>
{
private:
	typedef array<T, S> t;
	typedef dependable_array_common prv_this_type;

	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }

protected:
	typedef dependable_array_common direct_base;

	template <class J, class D>
	void init_size_with_array(const array<J, D>& o)
	{
		// need this because we want only first elements
		ivl::copy_out(to_array(), o);

		//loop_on<loops::assign_copy_class>(to_array().derived(), o);
	}

	template <class J>
	void init_size_with_element(const J& o)
	{
		loop_on<loops::assign_copy_class>(to_array(), o);
	}

public:
	typedef typename prv_this_type::derived_type derived_type;

	template <class A>
	derived_type& assign_array(const A& o)
	{
		// users guide: is you have a compiler error here it probably means that
		// you are calling assign_array with something that is not an ivl array.

		//NO WAY: resize(0) before resize() is optimum when assigning.
		//to_array().derived().resize(typename A::derived_type::size_type(0));


		//?maybe?:to_array().derived().reshape(
		//		o.template highest_common_class<derived_type>().size()); // resize_like
		//?or?:to_array().template highest_common_class<A>().reshape(
		//		o.template highest_common_class<derived_type>().size()); // resize_like


		to_array().template highest_common_class<A>().reshape(
				o.template highest_common_class<t>().size()); // resize_like


		//TODO: shouldn't this be:
		//to_array().derived().resize(
		//		o.template highest_common_class<t>().size()); // resize_like
		//by resize rule? shouldn't resize be always called on derived()?
		//or no, it should handle on itself, for any level, but then
		// NEEDS FIX, for all array classes to support this!!
		// anyway it certainly wont work well for vector<T>.resize()!!!! :)

		loop_on<loops::assign_copy_class>(to_array().derived(), o);
		return to_array().derived();
	}

	template <class A>
	derived_type& assign_array(ret<A>& o)
	{
		to_array().derived().swap(o.ret_base());
		return to_array().derived();
	}

	template <class J>
	derived_type& assign_element(const J& s)
	{
		typedef typename derived_type::size_type sz_t;
		// Note: not all arrays support resizing with (1, s)
		// however this statement works for all array types because
		// fixed dim arrays have size_type of dims<N> which
		// has a constructor that initializes all dimensions with
		// the argument, e.g. sz_t(1) is [1, 1] in a size_dim<2>.

		//to_array().derived().reset(sz_t(1), s);
		to_array().derived().resize(sz_t(0));
		to_array().derived().resize(sz_t(1), cast<T>(s));
		return to_array().derived();
	}

	dependable_array_common() {}
};

// Not writeable Not resizeable
template <class T, class S, class B>
class dependable_array_common<T, S, B, types::t_false, types::t_false>
: public readwrite_array_common<T, S, B, types::t_false>
{
private:
	typedef array<T, S> t;
	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }

protected:
	typedef dependable_array_common direct_base;
/*
	template <class D, class P>
	const derived_type& operator=(const array<T, D, P>& o) const
	{
		// silently exist but cannot be called
	}
*/

public:
	dependable_array_common() {}
};



} /* namespace array_details */

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_COMMON_DEPENDABLE_ARRAY_COMMON_HPP
