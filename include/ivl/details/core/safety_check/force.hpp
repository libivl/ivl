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

#ifndef IVL_CORE_DETAILS_SAFETY_CHECK_FORCE_HPP
#define IVL_CORE_DETAILS_SAFETY_CHECK_FORCE_HPP

namespace ivl {
namespace array_details {

template <class A, class IS_ARRAY>
class force_impl { };

template <class A>
class force_impl<A, types::t_false>
{
	A& a;
	typedef force_impl derived_type;
	derived_type& derived() { return static_cast<derived_type&>(*this); }

public:
	typedef A base_class;
	base_class& base() { return a; }
	const base_class& base() const { return a; }

	force_impl(A& a) : a(a) { }

	derived_type& operator=(const force_impl& b) { a = b; return *this; }

	template <class B>
	derived_type& operator=(const B& b) { a = b; return derived(); }

	template <class B>
	derived_type& operator+=(const B& b) { a += b; return derived(); }

	template <class B>
	derived_type& operator-=(const B& b) { a -= b; return derived(); }

	template <class B>
	derived_type& operator*=(const B& b) { a *= b; return derived(); }

	template <class B>
	derived_type& operator/=(const B& b) { a /= b; return derived(); }

	template <class B>
	derived_type& operator%=(const B& b) { a %= b; return derived(); }

	template <class B>
	derived_type& operator&=(const B& b) { a &= b; return derived(); }

	template <class B>
	derived_type& operator|=(const B& b) { a |= b; return derived(); }

	template <class B>
	derived_type& operator^=(const B& b) { a ^= b; return derived(); }

	template <class B>
	derived_type& operator<<=(const B& b) { a <<= b; return derived(); }

	template <class B>
	derived_type& operator>>=(const B& b) { a >>= b; return derived(); }
};

template <class A>
struct force_array_type
{
	typedef typename types::bare_type<A>::type a_t;

	typedef typename types::change_data_class_set<data::force
				<typename a_t::derived_type>,
			typename types::normal_type<a_t>::type>::type arr_type;

	typedef typename types::apply_const<arr_type, types::is_const<A> >
		::type type;
};

template <class A>
class force_impl<A, types::t_true>
:
public force_array_type<A>::type
{
	typedef force_impl derived_type;
	derived_type& derived() { return static_cast<derived_type&>(*this); }
public:
	typedef typename force_array_type<A>::type base_class;
	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	force_impl(A& a) : base_class(a) { }

	derived_type& operator=(const force_impl& b)
	{
		base().assign(b.base());
		return *this;
	}

	template <class B>
	derived_type& operator=(const B& b)
	{
		base().assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator+=(const B& b)
	{
		base().plus_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator-=(const B& b)
	{
		base().minus_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator*=(const B& b)
	{
		base().times_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator/=(const B& b)
	{
		base().divide_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator&=(const B& b)
	{
		base().mod_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator|=(const B& b)
	{
		base().bitor_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator<<=(const B& b)
	{
		base().bitlshift_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator>>=(const B& b)
	{
		base().bitrshift_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator^=(const B& b)
	{
		base().bitxor_assign(b);
		return derived();
	}
};
/*
template <class A>
class force_wrapper
:
public internal::reference_face<A>,
public force_impl<A, typename types::is_ivl_array<A>::type, force_wrapper<A> >
{
	typedef internal::reference_face<A> ref_base;
	typedef force_impl<A, typename
		types::is_ivl_array<A>::type, force_wrapper<A> >
			base_impl;
public:
	typedef typename ref_base::base_class base_class;
	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	force_wrapper(A& a) : ref_base(a) { }

	using base_impl::operator=;
	force_wrapper& operator=(const force_wrapper& o)
	{
		base_impl::operator=(o);
		return *this;
	}
};
*/
/*
template <class A>
struct force_return
{
	typedef typename types::bare_type<A>::type a_t;

	types::t_if<typename types::is_ivl_array<a_t>::type,
		typename types::change_data_class_set<data::force
				<typename a_t::derived_type>,
			typename types::normal_type<a_t>::type>::type,
		force_val<A>

}
*/
} /* namespace array_details */

template <class A>
array_details::force_impl<A, typename
	types::is_ivl_array<A>::type> force(A& a)
{
	return a;
}

template <class A>
array_details::force_impl<const A, typename
	types::is_ivl_array<A>::type> force(const A& a)
{
	return a;
}

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_SAFETY_CHECK_FORCE_HPP
