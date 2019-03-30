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

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_DETAILS_FUNC_ARR_HPP
#define IVL_CORE_DETAILS_FUNC_ARR_HPP

// note: kimon:
// unfortunately, i now need lists, however, the code is not implementation
// dependant
#include "../types/lists/impl/list.hpp"
#include "../types/lists/impl/seq.hpp"
#include "../types/lists/impl/types.hpp"

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace core_details {

namespace arr_details {

// ----------------------------------------------------------------------------

using namespace ivl::types;

template<class T>
struct tup_empty : types::t_eq<typename T::size_value_type, types::number<0> >
{ };

template<class T>
struct tup_test : t_if<
	types::t_eq<typename T::size_value_type, types::number<0> >,
	tuple<>, T>
{ };

template<class T>
struct tup_car { typedef typename T::template val_t<1>::type type; };

template<class T>
struct tup_cdr : types::t_if<
	types::t_eq<typename T::size_value_type, types::number<1> >,
	types::t_id<tuple<> >,
	types::t_id<shift_tuple<T> > >::type
{ };

template<>
struct tup_cdr<tuple<> > : t_id<tuple<> > { };

// ----------------------------------------------------------------------------

template<int N>
struct dm_add { };

template<class T>
struct maxd_map : types::number<0> { };

template<int N>
struct maxd_map<dm_add<N> > : types::number<N> { };

template<>
struct maxd_map<_class> : types::number<1> { };
template<>
struct maxd_map<const _class&> : types::number<1> { };
template<>
struct maxd_map<_class&> : types::number<1> { };

template<>
struct maxd_map<sep> : types::number<2> { };
template<>
struct maxd_map<sep&> : types::number<2> { };
template<>
struct maxd_map<const sep&> : types::number<2> { };

template<class T, int I>
struct arrl_map : types::t_if<types::t_eq<
		typename maxd_map<T>::type, types::number<0> >,
	types::number<I>, dm_add<maxd_map<T>::value> > { };

// ----------------------------------------------------------------------------

// case for ivl::array
template<class A, class T, int M>
struct arrj_el_imp
{
	typedef T e_t;
	typedef e_t type; // no data engine change
	static inline T make(T t) { return t; } // maybe reshape?
	// for 1d arrays?
};

// cases for non ivl::array

template<class T, int M>
struct arrj_el_imp<types::t_false, T, M>
{
	typedef T e_t;
	typedef const array_nd<e_t, data::ref_val_repeat<> > type; // data engine
	static inline type make(const T& t)
	{
		return type(array<size_t, data::fixed_val_repeat<size_t, 1> >(M + 1), t);
	}
};

template<class T, int M>
struct arrj_el_imp<types::t_false, const T&, M>
{
	typedef T e_t;
	typedef const array_nd<e_t, data::ref_val_repeat<> > type; // data engine
	static inline type make(const T& t)
	{
		return type(array<size_t, data::fixed_val_repeat<size_t, 1> >(M + 1), t);
	}
};

template<class T, int M>
struct arrj_el_imp<types::t_false, T&, M>
{
	typedef T e_t;
	typedef array_nd<e_t, data::rw_link> type; // data engine
	static inline type make(T& t)
	{
		return type(array<size_t, data::fixed_val_repeat<size_t, 1> >(M + 1), &t);
	}
};

template<class T>
struct arrj_el_imp<types::t_false, T, 0>
{
	typedef T e_t;
	typedef const array<e_t, data::ref_val_repeat<> > type; // data engine
	static inline type make(const T& t)
	{
		return type(1, t); // TODO:fix
	}
};

template<class T>
struct arrj_el_imp<types::t_false, const T&, 0>
{
	typedef T e_t;
	typedef const array<e_t, data::ref_val_repeat<> > type; // data engine
	static inline type make(const T& t)
	{
		return type(1, t); // TODO:fix
	}
};

template<class T>
struct arrj_el_imp<types::t_false, T&, 0>
{
	typedef T e_t;
	typedef array<e_t, data::rw_link> type; // data engine
	static inline type make(T& t)
	{
		return type(1, &t);
	}
};


// ----------------------------------------------------------------------------

template<class E, class TP, int M>
struct arrj_el
{
	typedef typename TP::template val_t<E::value>::type e_t;
	typedef arrj_el_imp<typename types::is_ivl_array<
		typename types::bare_type<e_t>::type>::type, e_t, M> gen_type;

	typedef typename gen_type::type type;

	template<class S>
	static inline type make(const S& t)
	{
		return gen_type::make(t.val(E()));
	}
	/*
	typedef array<e_t, data::ref_val_repeat<> > type; // all magic is here
	template<class S>
	type make(const S& t)
	{
		return type(1, t.val(E()));
	}
	*/
};

template<class A1, class A2, int D, int M>
struct concj
{
	enum { d_v = (M != 0 && D < 2) ? (1 - D) : D };
	typedef concat<typename A1::type, typename A2::type, d_v> type;
	template<class S>
	static inline type make(const S& t)
	{
		return type(A1::make(t), A2::make(t));
	}

};

// ----------------------------------------------------------------------------

using ivl::types::null_node;

template<class S, class T, int D, class TP, int M>
struct arrj { };

template<class S, class E, class ES, int D, class TP, int M>
struct arrj<S, node<E, ES>, D, TP, M> : arrj<
	typename l_concat<S, node<E, null_node> >::type, ES, D, TP, M> { };

template<class S, int D, class ES, class TP, int M>
struct arrj<S, node<dm_add<D>, ES>, D, TP, M> : concj<
	arrj<null_node, S, D-1, TP, M>,
	arrj<null_node, ES, D, TP, M>, D, M> { };

template<class S, int D, class TP, int M>
struct arrj<S, null_node, D, TP, M> : arrj<null_node, S, D-1, TP, M> { };

template<class E, class ES, class TP, int M>
struct arrj<null_node, node<E, ES>, 0, TP, M> : concj<arrj_el<E, TP, M>,
	arrj<null_node, ES, 0, TP, M>, 0, M> { };

template<class E, class TP, int M>
struct arrj<null_node, node<E, null_node>, 0, TP, M> : arrj_el<E, TP, M> { };

// ----------------------------------------------------------------------------

template<class T, int I>
struct arr_tup_to_list : types::node<
	typename arrl_map<typename tup_car<T>::type, I>::type,
	typename arr_tup_to_list<typename tup_cdr<T>::type, I + 1>::type>
{ };

template<int I>
struct arr_tup_to_list<tuple<>, I> : types::null_node { };

// ----------------------------------------------------------------------------

template<class T>
struct maxd : types::t_max<typename maxd_map<typename l_car<T>::type>::type,
	typename maxd<typename l_cdr<T>::type>::type> { };

template<>
struct maxd<null_node> : types::number<0> { };

template<class T>
struct arr_res_tup1
{
	typedef typename arr_tup_to_list<T, 1>::type l_t;
	typedef typename maxd<l_t>::type max_t;
	typedef arrj<types::null_node, l_t, max_t::value, T, max_t::value> gen_type;
	typedef typename gen_type::type type;

	template<class TPL>
	static inline type make(const TPL& s) { return gen_type::make(s); }
};

// : arrj_start<T, maxd<T>::type::value, types::t_true> { };

// TODO: define in another way.
struct arr_res_empty
{
	typedef array<double> type;
	template<class T>
	static inline array<double> make(T) { return array<double>(); }
};

template<class T>
struct arr_res_tup
{
	typedef typename types::t_if<tup_empty<T>,
		arr_res_empty, arr_res_tup1<T> >::type gen_type;
	typedef typename gen_type::type type;
	static inline type make(const T& t) { return gen_type::make(t); }
};

// ----------------------------------------------------------------------------

template<class S, class T>
struct arr_res_type : types::t_id<S> { };

template<class T>
struct arr_res_type<types::skip, T> : types::t_id<T> { };


template<class S = types::skip>
struct arr_impl_core : ivl_func<arr_impl_core<S> >
{
	//! Create an array with one element
	template <class T>
	array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<1> > operator()(const T& p1) const
	{
		return array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<1> >(1, p1);
	}

	//! Create an array with two elements
	template <class T, class T1>
	array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<2> > operator()(const T& p1,
																	const T1& p2) const
	{
		array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<2> > a(2);
		a[0] = p1; a[1] = p2;
		return a;
	}

	//! Create an array with three elements
	template <class T, class T1, class T2>
	array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<3> > operator()(const T& p1,
														const T1& p2, const T2& p3) const
	{
		array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<3> > a(3);
		a[0] = p1; a[1] = p2; a[2] = p3;
		return a;
	}

	//! Create an array with four elements
	template <class T, class T1, class T2, class T3>
	array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<4> > operator()(const T& p1,
										const T1& p2, const T2& p3, const T3& p4) const
	{
		array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<4> > a(4);
		a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4;
		return a;
	}

	//! Create an array with five elements
	template <class T, class T1, class T2, class T3, class T4>
	array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<5> > operator()(const T& p1,
							const T1& p2, const T2& p3, const T3& p4, const T4& p5) const
	{
		array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<5> > a(5);
		a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5;
		return a;
	}

	//! Create an array with six elements
	template <class T, class T1, class T2, class T3, class T4, class T5>
	array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<6> > operator()(const T& p1,
			const T1& p2, const T2& p3, const T3& p4, const T4& p5, const T5& p6) const
	{
		array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<6> > a(6);
		a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5; a[5] = p6;
		return a;
	}

	//! Create an array with seven elements
	template <class T, class T1, class T2, class T3, class T4, class T5, class T6>
	array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<7> > operator()(const T& p1,
						const T1& p2, const T2& p3, const T3& p4, const T4& p5,
														const T5& p6, const T6& p7) const
	{
		array<typename types::create_new<typename arr_res_type<S, T>::type>::type, fixed<7> > a(7);
		a[0] = p1; a[1] = p2; a[2] = p3; a[3] = p4; a[4] = p5; a[5] = p6; a[6] = p7;
		return a;
	}

	//template<class T, int N>
	//operator


	template<class T>
	arr_impl_core<T> _() { return arr_impl_core<T>(); }


	template<class T, int N>
	typename arr_res_tup<typename tuple_base<N, T>::derived_type>::type
		operator[](const tuple_base<N, T>& t)
	{
		return arr_res_tup<typename tuple_base<N, T>::derived_type>::make(t.derived());
	}


	/*
	template<class T, class S>
	arr_impl_core<T> operator[](types::node<T, S>) { return arr_impl_core<T>(); }
	*/

};

} // namespace arr_details

} // namespace core_details

//-----------------------------------------------------------------------------

namespace fun     { typedef core_details::arr_details::arr_impl_core <> arr; }
namespace key_fun { typedef key_fun <key::arr, fun::arr> arr; }

static __attribute__ ((unused)) key_fun::arr arr;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_FUNC_ARR_HPP
