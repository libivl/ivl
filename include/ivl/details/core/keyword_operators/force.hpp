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

template <class BASE>
class force_op
:
public BASE
{
	typedef force_op derived_type;
	derived_type& derived() { return static_cast<derived_type&>(*this); }
public:
	typedef typename BASE::type type;
	typedef typename BASE::base_class base_class;
	typedef force_op this_type;

	template<class A>
	force_op(A& a) : BASE(a) { }

	derived_type& operator=(const this_type& b)
	{
		this->base().assign(b.base());
		return *this;
	}

	template <class B>
	derived_type& operator=(const B& b)
	{
		this->base().assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator+=(const B& b)
	{
		this->base().plus_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator-=(const B& b)
	{
		this->base().minus_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator*=(const B& b)
	{
		this->base().times_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator/=(const B& b)
	{
		this->base().divide_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator&=(const B& b)
	{
		this->base().mod_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator|=(const B& b)
	{
		this->base().bitor_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator<<=(const B& b)
	{
		this->base().bitlshift_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator>>=(const B& b)
	{
		this->base().bitrshift_assign(b);
		return derived();
	}

	template <class B>
	derived_type& operator^=(const B& b)
	{
		this->base().bitxor_assign(b);
		return derived();
	}
};

template <class A, class IS_ARRAY>
class force_impl { };

template <class A>
class force_impl<A, types::t_false>
{
	/*A& a;
	typedef force_impl derived_type;
	derived_type& derived() { return static_cast<derived_type&>(*this); }
*/
public:
	typedef A& type;
/*
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
	*/
};

template <class A>
struct force_array_type
{
	typedef typename types::bare_type<A>::type a_t;

	typedef typename types::change_data_class_set<data::wrap_array
				<typename a_t::derived_type, data::force_wrap_array_attr>,
			typename types::normal_type<a_t>::type>::type arr_type;

	typedef typename types::apply_const<arr_type, types::is_const<A> >
		::type type;
};

template <class A>
class force_impl<A, types::t_true>
:
public force_array_type<A>::type
{
public:
	typedef force_op<force_impl> type;

	typedef typename force_array_type<A>::type base_class;
	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }
	//base_class& base() const{ return const_cast<base_class&>(*this); }

	force_impl() {}
	force_impl(A& a) : base_class(a) { }
};

template <class A, class B>
class base_referer
:
public B
{
	A r;
public:
	base_referer(const A& a) : r(a)
	{
		this->base().init(r);
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
typename array_details::force_impl<A, typename
	types::is_ivl_array<A>::type>::type force(A& a)
{
	return a;
}

// holds the object in a new temporary array when we have a referer object.
template <class X>
array_details::force_op<array_details::
	base_referer<X, array_details::force_impl<X, types::t_true> > >
force(const data::referer<X>& x)
{
	return x.derived();
}

// ---------------------------------------------

namespace core_details {

template<class IS_ARRAY>
struct force_assign_tool
{
	template<class X, class Y>
	static inline void assign(X& x, const Y& y) { x = y; }
};
template<>
struct force_assign_tool<types::t_true>
{
	template<class X, class Y>
	static inline void assign(X& x, const Y& y) { x.assign(y); }
};

} /* namespace core_details */

template <class X, class Y>
void force_assign(X& x, const Y& y)
{
	using namespace core_details;
	force_assign_tool<typename types::is_ivl_array<X>::type>::assign(x, y);
}

/*
template <class A>
array_details::force_impl<A, typename // not <const A..> but <A..>
	types::is_ivl_array<A>::type> force(const A& a)
{
	return const_cast<A&>(a);
}
*/
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_SAFETY_CHECK_FORCE_HPP
