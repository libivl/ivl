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

#ifndef IVL_CORE_DETAILS_ELEM_PTR_HPP
#define IVL_CORE_DETAILS_ELEM_PTR_HPP

namespace ivl {


template <class RT, class X1, class X2, int COST=0 >
struct binary_elem_ptr
{
	typedef typename types::bare_type<RT>::type T;
	typedef RT(*ptr_type)(X1, X2);

	ptr_type val;
	binary_elem_ptr() {}
	binary_elem_ptr(ptr_type val) : val(val) {}
	binary_elem_ptr(const binary_elem_ptr& o) : val(o.val) {}
	binary_elem_ptr& operator=(const binary_elem_ptr& o) { val = o.val; return *this; }

	typedef core_details::elem_details et;

	template <class J, class J1, class J2>
	struct functor
	{
		typedef ptr_type ptr_t;
		typedef types::number<COST> cost;
		static inline RT elem_op(ptr_t f, X1 x1, X2 x2)
		{
			return f(x1, x2);
		}
	};
	/*
	template <class A1, class A2>
	typename binary_elem_func_result<T, functor, A1, A2>
		::type operator()(const A1& a1, const A2& a2)
	{
		return binary_elem_func_result<T, functor, A1, A2>
			::from(a1, a2);
	}
	*/

	// tuple
	template <class TPL>
	typename binary_elem_func_result_ptr<T, functor,
		typename TPL::t1, typename TPL::t2>
		::type operator[](const tuple_base<2, TPL>& tpl)
	{
		return binary_elem_func_result_ptr<T, functor,
			typename TPL::t1, typename TPL::t2>
			::from(val, tpl.derived().v1, tpl.derived().v2);
	}
	// suppose array of tuples

	//TODO: do something more correct like a combination
	// of ice2 and an elem function doing a
	// replacer_cast<X1, scalar<X1>
	// this will reach inner_type of an array as well.

	template <class J, class S>
	typename binary_elem_func_result_ptr<T, functor,

		array<typename et::check<typename J::t1, X1>::type,
		data::wrap_array<
		member_array<const array<J, S>, typename J::t1>,
		typename et::check<typename J::t1, X1>::attr> >,

		array<typename et::check<typename J::t2, X2>::type,
		data::wrap_array<
		member_array<const array<J, S>, typename J::t2>,
		typename et::check<typename J::t2, X2>::attr> >

		>

		::type operator[](const array<J, S>& a)
	{

		return binary_elem_func_result_ptr<T, functor,

			array<typename et::check<typename J::t1, X1>::type,
			data::wrap_array<
			member_array<const array<J, S>, typename J::t1>,
			typename et::check<typename J::t1, X1>::attr> >,

			array<typename et::check<typename J::t2, X2>::type,
			data::wrap_array<
			member_array<const array<J, S>, typename J::t2>,
			typename et::check<typename J::t2, X2>::attr> >

			>::from(val,
			member_array<const array<J, S>, typename J::t1>(a.in(&J::v1)),
			member_array<const array<J, S>, typename J::t2>(a.in(&J::v2)));
	}

	template <class A1, class A2>
	typename binary_elem_func_result_ptr<T, functor,
		typename et::check_2<A1, X1>::type,
		typename et::check_2<A2, X2>::type
	>
		::type operator()(const A1& a1, const A2& a2)
	{
		return
			binary_elem_func_result_ptr<T, functor,
			typename et::check_2<A1, X1>::type,
			typename et::check_2<A2, X2>::type
		>
			::from(val, a1, a2);
	}

};


} /*namespace ivl*/

#endif // IVL_CORE_DETAILS_ELEM_HPP
