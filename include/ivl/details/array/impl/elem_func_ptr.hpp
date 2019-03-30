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

#ifndef IVL_DETAILS_ARRAY_BASE_ELEM_FUNC_PTR_HPP
#define IVL_DETAILS_ARRAY_BASE_ELEM_FUNC_PTR_HPP

// NOTE
// TODO: remove this
// Elem func ptr is a temporary class, before tup elem func is created
// to support pointer to functions elem func

namespace ivl {



// ---------------------------------------------------------------
// binary elem func result definition

namespace array_details {

struct bin_elem_func_ptr {};
struct bin_scalar_r_ptr {};
struct bin_scalar_l_ptr {};
struct bin_val_func_ptr {};

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class A2,
	class MATCH
>
struct bin_elem_func_result_ptr {};

} /* namespace array_details */

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class A2
>
class binary_elem_func_result_ptr
{
	typedef typename types::t_if<
		types::t_and<types::is_ivl_array<A1>, types::is_ivl_array<A2> >,
			array_details::bin_elem_func_ptr,
			typename types::t_if<types::is_ivl_array<A1>,
				array_details::bin_scalar_r_ptr,
					typename types::t_if<types::is_ivl_array<A2>,
						array_details::bin_scalar_l_ptr,
						array_details::bin_val_func_ptr>::type>::type>::type
							match_type;
public:
	typedef typename
		array_details::bin_elem_func_result_ptr<T, F, A1, A2, match_type>
		::type type;
	typedef typename
		array_details::bin_elem_func_result_ptr<T, F, A1, A2, match_type>
		::wrapper_type wrapper_type;
	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;

	static inline
	typename array_details::bin_elem_func_result_ptr<T, F, A1, A2, match_type>
	::type from(ptr_t p1, const A1& a1, const A2& a2)
	{
		return array_details::bin_elem_func_result_ptr<T, F, A1, A2, match_type>
			::from(p1, a1, a2);
	}
};

// ---------------------------------------------------------------
// unary elem func result definition

// --------------------------------------------------------------------
// elem func classes


template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class A2
>
class elem_func_binary_ptr : public

//	types::change_data_class_set<
//		typename data::binary_elem_func_traits<F, A1, A2, false>::
//		type, typename A1::derived_type>::type

array_details::binary_operator_result<
	typename binary_elem_func_result_ptr<T, F,
		typename A1::elem_type, typename A2::elem_type>::type,
	A1, A2,
	data::binary_elem_func_ptr<F,
		typename A1::derived_type, typename A2::derived_type, false>,
	data::binary_elem_func_ptr<F,
		typename A2::derived_type, typename A1::derived_type, true> >::type

{
public:
	//typedef typename types::change_data_class_set<
	//	typename data::binary_elem_func_traits<F, A1, A2, false>::
	//	type, typename A1::derived_type>::type base_class;
	typedef typename array_details::binary_operator_result<
		typename binary_elem_func_result_ptr<T, F,
			typename A1::elem_type, typename A2::elem_type>::type,
		A1, A2,
		data::binary_elem_func_ptr<F,
			typename A1::derived_type, typename A2::derived_type, false>,
		data::binary_elem_func_ptr<F,
			typename A2::derived_type, typename A1::derived_type, true> >::
			type base_class;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;

	elem_func_binary_ptr(ptr_t p1, const A1& a1, const A2& a2)
	{
		// sets the underlying array references, switching them if SWAP
		this->setref(p1, ref1(a1.derived(), a2.derived()),
					ref2(a1.derived(), a2.derived()));

		this->validate();
	}

	elem_func_binary_ptr(const elem_func_binary_ptr& a) : base_class(a) { }

	elem_func_binary_ptr& operator=(const elem_func_binary_ptr& o)
	{ base_class::operator=(o); return *this; }

};

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class T2
>
class elem_func_scalar_r_ptr : public
	types::change_elem_type<typename
			binary_elem_func_result_ptr<T, F,
				typename A1::elem_type, T2>::type,
		typename types::change_data_class_set<
		data::binary_elem_func_ptr<F, typename A1::derived_type,
			typename array_details::scalar_to_array<T2,
				typename A1::derived_type>::type, false>,
		typename A1::derived_type>::type>::type
{
public:
	typedef typename types::change_elem_type<typename
			binary_elem_func_result_ptr<T, F,
				typename A1::elem_type, T2>::type,
		typename types::change_data_class_set<
		data::binary_elem_func_ptr<F, typename A1::derived_type,
			typename array_details::scalar_to_array<T2,
				typename A1::derived_type>::type, false>,
		typename A1::derived_type>::type>::type base_class;

	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;
	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	elem_func_scalar_r_ptr(ptr_t p1, const A1& a1, const T2& t2)
	{
		this->setref(p1, a1.derived(),
			typename array_details::scalar_to_array<T2,
				typename A1::derived_type>
				::type(a1.derived().size()));
		this->in2->setval(t2);
	}

	elem_func_scalar_r_ptr(const elem_func_scalar_r_ptr& a) : base_class(a) { }

	elem_func_scalar_r_ptr& operator=(const elem_func_scalar_r_ptr& o)
	{ base_class::operator=(o); return *this; }

};

template <
	class T,
	template <typename, typename, typename> class F,
	class T1,
	class A2
>
class elem_func_scalar_l_ptr : public
	types::change_elem_type<typename
			binary_elem_func_result_ptr<T, F,
				T1, typename A2::elem_type>::type,
		typename types::change_data_class_set<
		data::binary_elem_func_ptr<F, typename A2::derived_type,
			typename array_details::scalar_to_array<T1,
				typename A2::derived_type>::type, true>,
		typename A2::derived_type>::type>::type
{
public:
	typedef typename types::change_elem_type<typename
			binary_elem_func_result_ptr<T, F,
				T1, typename A2::elem_type>::type,
		typename types::change_data_class_set<
		data::binary_elem_func_ptr<F, typename A2::derived_type,
			typename array_details::scalar_to_array<T1,
				typename A2::derived_type>::type, true>,
		typename A2::derived_type>::type>::type base_class;
	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	elem_func_scalar_l_ptr(ptr_t p1, const T1& t1, const A2& a2)
	{
		this->setref(p1, a2.derived(),
			typename array_details::scalar_to_array<T1,
				typename A2::derived_type>
				::type(a2.derived().size()));
		this->in2->setval(t1);
	}

	elem_func_scalar_l_ptr(const elem_func_scalar_l_ptr& a) : base_class(a) { }

	elem_func_scalar_l_ptr& operator=(const elem_func_scalar_l_ptr& o)
	{ base_class::operator=(o); return *this; }

};


namespace array_details {

// ---------------------------------------------------------------
// binary elem func result implementation

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class A2
>
struct bin_elem_func_result_ptr<T, F, A1, A2, bin_elem_func_ptr>
{
	typedef typename elem_func_binary_ptr<T, F, A1, A2>::base_class type;
	typedef elem_func_binary_ptr<T, F, A1, A2> wrapper_type;
	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;

	static inline type from(ptr_t p1, const A1& a1, const A2& a2)
	{
		return elem_func_binary_ptr<T, F, A1, A2>(p1, a1, a2).base();
	}
};

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class T2
>
struct bin_elem_func_result_ptr<T, F, A1, T2, bin_scalar_r_ptr>
{
	typedef typename elem_func_scalar_r_ptr<T, F, A1, T2>::base_class type;
	typedef elem_func_scalar_r_ptr<T, F, A1, T2> wrapper_type;
	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;

	static inline type from(ptr_t p1, const A1& a1, const T2& a2)
	{
		return elem_func_scalar_r_ptr<T, F, A1, T2>(p1, a1, a2).base();
	}
};

template <
	class T,
	template <typename, typename, typename> class F,
	class T1,
	class A2
>
struct bin_elem_func_result_ptr<T, F, T1, A2, bin_scalar_l_ptr>
{
	typedef typename elem_func_scalar_l_ptr<T, F, T1, A2>::base_class type;
	typedef elem_func_scalar_l_ptr<T, F, T1, A2> wrapper_type;
	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;

	static inline type from(ptr_t p1, const T1& a1, const A2& a2)
	{
		return elem_func_scalar_l_ptr<T, F, T1, A2>(p1, a1, a2).base();
	}
};

template <
	class T,
	template <typename, typename, typename> class F,
	class T1,
	class T2
>
struct bin_elem_func_result_ptr<T, F, T1, T2, bin_val_func_ptr>
{
	typedef T type;
	typedef T wrapper_type;
	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;

	static inline T from(ptr_t p1, const T1& v1, const T2& v2)
	{
		return F<T, T1, T2>::elem_op(p1, v1, v2);
	}
};

} /* namespace array_details */

// classes that can be used directly to get an element function from one
// (unary) or two (binary) classes and an element operation functor.
// these two classes are wrappers for an according elem_func_binary or
// elem_func_scalar_l or elem_func_scalar_r or elem_func_unary class which
// is direct wrapper to an according array<.> or array_nd<.> or any
// ivl container class with an elem_class data type.

template<
	template <typename, typename, typename> class F,
	class A1, class A2
>
struct binary_elem_func_ptr : public binary_elem_func_result_ptr<
	typename F<types::term,
		typename types::get_value<A1>::type,
		typename types::get_value<A2>::type>::default_ret_type,
		F, A1, A2>::wrapper_type
{
private:
	typedef typename binary_elem_func_result_ptr<
	typename F<types::term,
		typename types::get_value<A1>::type,
		typename types::get_value<A2>::type>::default_ret_type,
		F, A1, A2>::wrapper_type prv_base;
	typedef typename F<types::term, types::term, types::term>::ptr_t ptr_t;
public:
	template<class A, class B>
	binary_elem_func_ptr(ptr_t p1, const A& a1, const B& a2) : prv_base(p1, a1, a2) { }

	template<class T1, class T2>
	binary_elem_func_ptr(ivl::tuple<T1, T2> a)
		: prv_base(a.val(types::number<1>()), a.val(types::number<2>()), a.val(types::number<3>())) { }

	binary_elem_func_ptr(const binary_elem_func_ptr& a) : prv_base(a) { }

	binary_elem_func_ptr& operator=(const binary_elem_func_ptr& o)
	{ prv_base::operator=(o); return *this; }
};


} /* namespace ivl */

#endif // IVL_DETAILS_ARRAY_BASE_ELEM_FUNC_HPP
