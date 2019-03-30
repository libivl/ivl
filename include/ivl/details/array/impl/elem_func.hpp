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

#ifndef IVL_DETAILS_ARRAY_BASE_ELEM_FUNC_HPP
#define IVL_DETAILS_ARRAY_BASE_ELEM_FUNC_HPP

namespace ivl {

//-----------------------------------------------------------------------------
// binary elem func result definition

namespace array_details {

struct bin_elem_func {};
struct bin_scalar_r {};
struct bin_scalar_l {};
struct bin_val_func {};

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class A2,
	class MATCH
>
struct bin_elem_func_result {};

} /* namespace array_details */

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class A2
>
class binary_elem_func_result
{
	typedef typename types::t_if<
		types::t_and<types::is_ivl_array<A1>, types::is_ivl_array<A2> >,
			array_details::bin_elem_func,
			typename types::t_if<types::is_ivl_array<A1>,
				array_details::bin_scalar_r,
					typename types::t_if<types::is_ivl_array<A2>,
						array_details::bin_scalar_l,
						array_details::bin_val_func>::type>::type>::type
							match_type;
public:
	typedef typename
		array_details::bin_elem_func_result<T, F, A1, A2, match_type>
		::type type;
	typedef typename
		array_details::bin_elem_func_result<T, F, A1, A2, match_type>
		::wrapper_type wrapper_type;

	static inline
	typename array_details::bin_elem_func_result<T, F, A1, A2, match_type>
	::type from(const A1& a1, const A2& a2)
	{
		return array_details::bin_elem_func_result<T, F, A1, A2, match_type>
			::from(a1, a2);
	}
};

//-----------------------------------------------------------------------------

// iavr: shortcut to a binary_elem_func_result directly from F, A1, A2
template <
	template <typename, typename, typename> class F,
	class A1,
	class A2
>
struct binary_elem_func_call : public
	binary_elem_func_result <
		typename F <
			types::term,
			typename types::get_value<A1>::inner_type,
			typename types::get_value<A2>::inner_type
		>::default_ret_type,
		F, A1, A2
	>
{ };

// iavr: shortcut to a binary_elem_func_result directly from
// functor FN with cost COST, and types A1, A2
template <
	template <typename, typename> class FN,
	class A1,
	class A2,
	int COST = -1
>
struct binary_elem_call : public
	binary_elem_func_call <fun::map2elem2 <FN, COST>::template fun, A1, A2>
	{ };

//-----------------------------------------------------------------------------
// iavr: conversion from binary 'op' functor directly to element function

namespace fun {

template <
	typename OP,
	template <typename, typename> class MAP = types::maps::max,
	int COST = default_cost
	>
struct op2el2
{
	template <typename A, typename B>
	struct F : public op2map2 <OP, MAP, COST>::template fun <A, B> { };

	template <class A, class B>
	typename binary_elem_call <F, A, B>::type
	operator()(const A& a, const B& b)
	{
		return binary_elem_call <F, A, B>::from(a, b);
	}
};

template <typename OP, typename RET, int COST = default_cost>
struct fixed_op2el2 :
public op2el2 <OP, types::maps::fixed <RET, 2>::template map, COST> { };

}  // namespace fun

//-----------------------------------------------------------------------------
// unary elem func result definition

namespace array_details {

struct un_elem_func {};
struct un_val_func {};

template <
	class T,
	template <typename, typename> class F,
	class A,
	class MATCH
>
struct un_elem_func_result {};

} /* namespace array_details */


template <
	class T,
	template <typename, typename> class F,
	class A
>
class unary_elem_func_result
{
	typedef typename types::t_if<types::is_ivl_array<A>,
		array_details::un_elem_func, array_details::un_val_func>
		::type match_type;
public:
	typedef typename
		array_details::un_elem_func_result<T, F, A, match_type>
		::type type;
	typedef typename
		array_details::un_elem_func_result<T, F, A, match_type>
		::wrapper_type wrapper_type;

	static inline
	type from(const A& a1)
	{
		return array_details::un_elem_func_result<T, F, A, match_type>
			::from(a1);
	}
};

// ---------------------------------------------------------------

// iavr: shortcut to a unary_elem_func_result directly from F, A
template <
	template <typename, typename> class F,
	class A
>
struct unary_elem_func_call : public
	unary_elem_func_result <
		typename F <
			types::term,
			typename types::get_value<A>::inner_type
		>::default_ret_type,
		F, A
	>
{ };

// iavr: shortcut to a unary_elem_func_result directly from
// functor FN with cost COST, and type A
template <
	template <typename> class FN,
	class A,
	int COST = -1
>
struct unary_elem_call : public
	unary_elem_func_call <fun::map2elem1<FN, COST>::template fun, A> { };

//-----------------------------------------------------------------------------
// iavr: conversion from unary 'op' functor directly to element function

namespace fun {

template <
	typename OP,
	template <typename> class MAP = types::maps::id,
	int COST = default_cost
	>
struct op2el1
{
	template <typename A>
	struct F : public op2map1 <OP, MAP, COST>::template fun <A> { };

	template <class A>
	typename unary_elem_call <F, A>::type
	operator()(const A& a) { return unary_elem_call <F, A>::from(a); }
};

template <typename OP, typename RET, int COST = default_cost>
struct fixed_op2el1 :
public op2el1 <OP, types::maps::fixed <RET>::template map, COST> { };

}  // namespace fun

//-----------------------------------------------------------------------------
// elem func classes


template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class A2
>
class elem_func_binary : public

//	types::change_data_class_set<
//		typename data::binary_elem_func_traits<F, A1, A2, false>::
//		type, typename A1::derived_type>::type

array_details::binary_operator_result<
	typename binary_elem_func_result<T, F,
		typename A1::elem_type, typename A2::elem_type>::type,
	A1, A2,
	data::binary_elem_func<F,
		typename A1::derived_type, typename A2::derived_type, false>,
	data::binary_elem_func<F,
		typename A2::derived_type, typename A1::derived_type, true> >::type

{
public:
	//typedef typename types::change_data_class_set<
	//	typename data::binary_elem_func_traits<F, A1, A2, false>::
	//	type, typename A1::derived_type>::type base_class;
	typedef typename array_details::binary_operator_result<
		typename binary_elem_func_result<T, F,
			typename A1::elem_type, typename A2::elem_type>::type,
		A1, A2,
		data::binary_elem_func<F,
			typename A1::derived_type, typename A2::derived_type, false>,
		data::binary_elem_func<F,
			typename A2::derived_type, typename A1::derived_type, true> >::
			type base_class;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }


	elem_func_binary(const A1& a1, const A2& a2)
	{
		// sets the underlying array references, switching them if SWAP
        this->setref(this->ref1(a1.derived(), a2.derived()),
                    this->ref2(a1.derived(), a2.derived()));

		this->validate();
	}

	elem_func_binary(const elem_func_binary& a) : base_class(a) { }

	elem_func_binary& operator=(const elem_func_binary& o)
	{ base_class::operator=(o); return *this; }

};

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class T2
>
class elem_func_scalar_r : public
	types::change_elem_type<typename
			binary_elem_func_result<T, F,
				typename A1::elem_type, T2>::type,
		typename types::change_data_class_set<
		data::binary_elem_func<F, typename A1::derived_type,
			typename array_details::scalar_to_array<T2,
				typename A1::derived_type>::type, false>,
		typename A1::derived_type>::type>::type
{
public:
	typedef typename types::change_elem_type<typename
			binary_elem_func_result<T, F,
				typename A1::elem_type, T2>::type,
		typename types::change_data_class_set<
		data::binary_elem_func<F, typename A1::derived_type,
			typename array_details::scalar_to_array<T2,
				typename A1::derived_type>::type, false>,
		typename A1::derived_type>::type>::type base_class;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	elem_func_scalar_r(const A1& a1, const T2& t2)
	{
		this->setref(a1.derived(),
			typename array_details::scalar_to_array<T2,
				typename A1::derived_type>
				::type(a1.derived().size()));
		this->in2->setval(t2);
	}

	elem_func_scalar_r(const elem_func_scalar_r& a) : base_class(a) { }

	elem_func_scalar_r& operator=(const elem_func_scalar_r& o)
	{ base_class::operator=(o); return *this; }

};

template <
	class T,
	template <typename, typename, typename> class F,
	class T1,
	class A2
>
class elem_func_scalar_l : public
	types::change_elem_type<typename
			binary_elem_func_result<T, F,
				T1, typename A2::elem_type>::type,
		typename types::change_data_class_set<
		data::binary_elem_func<F, typename A2::derived_type,
			typename array_details::scalar_to_array<T1,
				typename A2::derived_type>::type, true>,
		typename A2::derived_type>::type>::type
{
public:
	typedef typename types::change_elem_type<typename
			binary_elem_func_result<T, F,
				T1, typename A2::elem_type>::type,
		typename types::change_data_class_set<
		data::binary_elem_func<F, typename A2::derived_type,
			typename array_details::scalar_to_array<T1,
				typename A2::derived_type>::type, true>,
		typename A2::derived_type>::type>::type base_class;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	elem_func_scalar_l(const T1& t1, const A2& a2)
	{
		this->setref(a2.derived(),
			typename array_details::scalar_to_array<T1,
				typename A2::derived_type>
				::type(a2.derived().size()));
		this->in2->setval(t1);
	}

	elem_func_scalar_l(const elem_func_scalar_l& a) : base_class(a) { }

	elem_func_scalar_l& operator=(const elem_func_scalar_l& o)
	{ base_class::operator=(o); return *this; }

};

template <
	class T,
	template <typename, typename> class F,
	class A
>
class elem_func_unary : public
	types::change_elem_type<typename
		unary_elem_func_result<T, F, typename A::elem_type>::type,
		typename types::change_data_class_set<data::
		unary_elem_func<F, typename A::derived_type>,
			typename A::derived_type>::type>::type
{
public:
	typedef typename types::change_elem_type<typename
		unary_elem_func_result<T, F, typename A::elem_type>::type,
		typename types::change_data_class_set<data::
		unary_elem_func<F, typename A::derived_type>,
			typename A::derived_type>::type>
		::type base_class;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	elem_func_unary(const A& a1) { this->setref(a1.derived()); }

	elem_func_unary(const elem_func_unary& a) : base_class(a) { }

	elem_func_unary& operator=(const elem_func_unary& o)
	{ base_class::operator=(o); return *this; }

	~elem_func_unary() { }

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
struct bin_elem_func_result<T, F, A1, A2, bin_elem_func>
{
	typedef typename elem_func_binary<T, F, A1, A2>::base_class type;
	typedef elem_func_binary<T, F, A1, A2> wrapper_type;

	static inline type from(const A1& a1, const A2& a2)
	{
		return elem_func_binary<T, F, A1, A2>(a1, a2).base();
	}
};

template <
	class T,
	template <typename, typename, typename> class F,
	class A1,
	class T2
>
struct bin_elem_func_result<T, F, A1, T2, bin_scalar_r>
{
	typedef typename elem_func_scalar_r<T, F, A1, T2>::base_class type;
	typedef elem_func_scalar_r<T, F, A1, T2> wrapper_type;

	static inline type from(const A1& a1, const T2& a2)
	{
		return elem_func_scalar_r<T, F, A1, T2>(a1, a2).base();
	}
};

template <
	class T,
	template <typename, typename, typename> class F,
	class T1,
	class A2
>
struct bin_elem_func_result<T, F, T1, A2, bin_scalar_l>
{
	typedef typename elem_func_scalar_l<T, F, T1, A2>::base_class type;
	typedef elem_func_scalar_l<T, F, T1, A2> wrapper_type;

	static inline type from(const T1& a1, const A2& a2)
	{
		return elem_func_scalar_l<T, F, T1, A2>(a1, a2).base();
	}
};

template <
	class T,
	template <typename, typename, typename> class F,
	class T1,
	class T2
>
struct bin_elem_func_result<T, F, T1, T2, bin_val_func>
{
	typedef T type;
	typedef T wrapper_type;

	static inline T from(const T1& v1, const T2& v2)
	{
		return F<T, T1, T2>::elem_op(v1, v2);
	}
};

// ---------------------------------------------------------------
// unary elem func result implementation

template <
	class T,
	template <typename, typename> class F,
	class A
>
struct un_elem_func_result<T, F, A, un_elem_func>
{
	typedef typename elem_func_unary<T, F, A>::base_class type;
	typedef elem_func_unary<T, F, A> wrapper_type;

	static inline type from(const A& a1)
	{
		return elem_func_unary<T, F, A>(a1).base();
	}
};

template <
	class T,
	template <typename, typename> class F,
	class T1
>
struct un_elem_func_result<T, F, T1, un_val_func>
{
	typedef T type;
	typedef T wrapper_type;

	static inline T from(const T1& v1)
	{
		return F<T, T1>::elem_op(v1);
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
struct binary_elem_func : public binary_elem_func_result<
	typename F<types::term,
		typename types::get_value<A1>::inner_type,
		typename types::get_value<A2>::inner_type>::default_ret_type,
		F, A1, A2>::wrapper_type
{
private:
	typedef typename binary_elem_func_result<
	typename F<types::term,
		typename types::get_value<A1>::inner_type,
		typename types::get_value<A2>::inner_type>::default_ret_type,
		F, A1, A2>::wrapper_type prv_base;
public:
	template<class A, class B>
	binary_elem_func(const A& a1, const B& a2) : prv_base(a1, a2) { }

	template<class T1, class T2>
	binary_elem_func(ivl::tuple<T1, T2> a)
		: prv_base(a.val(types::number<1>()), a.val(types::number<2>())) { }

	binary_elem_func(const binary_elem_func& a) : prv_base(a) { }

	binary_elem_func& operator=(const binary_elem_func& o)
	{ prv_base::operator=(o); return *this; }
};

template<
	template <typename, typename> class F,
	class A1
>
struct unary_elem_func : public unary_elem_func_result<
	typename F<types::term,
		typename types::get_value<A1>::inner_type>::default_ret_type,
		F, A1>::wrapper_type
{
private:
	typedef typename unary_elem_func_result<
	typename F<types::term,
		typename types::get_value<A1>::inner_type>::default_ret_type,
		F, A1>::wrapper_type prv_base;
public:
	template<class A>
	unary_elem_func(const A& a1) : prv_base(a1) { }

	unary_elem_func(const unary_elem_func& a) : prv_base(a) { }

	unary_elem_func& operator=(const unary_elem_func& o)
	{ prv_base::operator=(o); return *this; }
};

} /* namespace ivl */

#endif // IVL_DETAILS_ARRAY_BASE_ELEM_FUNC_HPP
