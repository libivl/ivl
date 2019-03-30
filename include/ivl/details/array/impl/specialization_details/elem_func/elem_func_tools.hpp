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

#ifndef IVL_ARRAY_SPECIALIZATION_DETAILS_ELEM_FUNC_TOOLS_HPP
#define IVL_ARRAY_SPECIALIZATION_DETAILS_ELEM_FUNC_TOOLS_HPP

namespace ivl {
namespace array_details {

template<class T, bool HAS_RANDOM_ACCESS = false>
struct elem_func_tools
{
};

template <class T>
struct elem_func_tools_common
{

	typedef T brackets_ret_type;

	// TODO : these specs are not for binary elem_func.
	// the whole class is generic so it can be renamed and placed in
	// data/ member control.hpp
	//?????
	typedef const T& const_ref_brackets_type;
	typedef T& ref_brackets_type;
};

template <class T>
struct elem_func_tools <T, false>
: public elem_func_tools_common<T>
{
	class not_a_type : public std::complex<int> { }; // for <, >=

	/*typedef int brackets_ret_type;

	// TODO : these specs are not for binary elem_func.
	// the whole class is generic so it can be renamed and placed in
	// data/ member control.hpp
	typedef int const_ref_brackets_type;
	typedef int ref_brackets_type;
	*/
	typedef typename elem_func_tools::brackets_ret_type brackets_ret_type;
	typedef typename elem_func_tools::ref_brackets_type ref_brackets_type;
	typedef typename elem_func_tools::const_ref_brackets_type
		const_ref_brackets_type;


	typedef not_a_type brackets_arg;

	template <class C>
	struct rnd_it
	{
		struct foo {
			foo() {}
			template<class T1> foo(T1) {}
			template<class T1, class T2> foo(T1,T2) {}
			template<class T1, class T2, class T3> foo(T1,T2,T3) {}
		};
		typedef foo type;
		//typedef std::complex<int> type; // because it has 0 and (0, 0) constr.
	};

	// NOTE: 2013: brackets_ret_type is wrong. Right behavior is mapped from A
	// TODO: eliminate brackets_ret_type and change it to mapped struct,
	// for those who use it
	//template<class A>
	//static inline
	//brackets_ret_type brackets(const A& a, brackets_arg j) { return *a; }
	//SFINAE
	template<class A>
	static inline
	typename A::const_reference brackets(const A& a, brackets_arg j) { return *a; }
	template<class A>
	static inline
	typename types::apply_const<typename A::reference>::type brackets(const A& a, brackets_arg j) { return *a; }



	// TODO : these specs are not for binary elem_func.
	// the whole class is generic so it can be renamed and placed in
	// data/ member control.hpp
	template<class A>
	static inline
	ref_brackets_type ref_brackets(const A& a, brackets_arg j) { return *a; }

	template<class R>
	struct brackets_c
	{
		template<class A>
		static inline R f(A& a, brackets_arg j) { return *a; }
	};
	//

	template<class A>
	static inline int add_op(const A& a, brackets_arg j) { return 0; }

	template<class A>
	static inline A add_op_void(const A& a, brackets_arg j) { return a; }

	template<class A>
	static inline int sub_op(const A& a, brackets_arg j) { return 0; }

	template<class A>
	static inline ptrdiff_t dif_op(const A& a, const A& b) { return 0; }

	template<class A>
	static inline void add_asgn(const A& a, brackets_arg j) { }

	template<class A>
	static inline void sub_asgn(const A& a, brackets_arg j) { }

	// ---------------
	// nd usefull tools
	template <class A>
	struct meta_nd
	{
		typedef typename A::stride_type stride_type;
		//	typedef not_a_type stride_type;

	};

};

template<class T>
struct elem_func_tools<T, true>
: public elem_func_tools_common<T>
{

	class not_a_type { };
/*
	typedef T brackets_ret_type;

	// TODO : these specs are not for binary elem_func.
	// the whole class is generic so it can be renamed and placed in
	// data/ member control.hpp
	typedef const T& const_ref_brackets_type;
	typedef T& ref_brackets_type;
*/
	typedef typename elem_func_tools::brackets_ret_type brackets_ret_type;
	typedef typename elem_func_tools::ref_brackets_type ref_brackets_type;
	typedef typename elem_func_tools::const_ref_brackets_type
		const_ref_brackets_type;


	typedef size_t brackets_arg;

	template <class C>
	struct rnd_it
	{
		typedef C type;
	};

	// NOTE: 2013: brackets_ret_type is wrong. Right behavior is mapped from A
	// TODO: eliminate brackets_ret_type and change it to mapped struct,
	// for those who use it
	//template<class A>
	//static inline
	//brackets_ret_type brackets(const A& a, brackets_arg j) { return a[j]; }

	//SFINAE
	template<class A>
	static inline
	typename A::const_reference brackets(const A& a, brackets_arg j) { return a[j]; }

	//2nd SFINAE
	template<class A>
	static inline
	typename types::apply_const<typename A::reference>::type brackets(const A& a,
		typename types::enable_if<typename types::t_not<types::has_typedef_const_reference<A> >,
			brackets_arg>::type j) { return a[j]; }
	//3rd SFINAE
	template<class A>
	static inline
	typename A::reference brackets(A& a, 
		typename types::enable_if<typename types::t_not<types::has_typedef_const_reference<A> >,
			brackets_arg>::type j) { return a[j]; }

	// TODO : these specs are not for binary elem_func.
	// the whole class is generic so it can be renamed and placed in
	// data/ member control.hpp
	template<class A>
	static inline
	const_ref_brackets_type ref_brackets(const A& a,
		brackets_arg j) { return a[j]; }

	template<class A>
	static inline
	ref_brackets_type ref_brackets(A& a, brackets_arg j) { return a[j]; }

	template<class R>
	struct brackets_c
	{
		template<class A>
		static inline R f(A& a, brackets_arg j) { return a[j]; }
	};
	//

	template<class A>
	static inline A add_op(const A& a, brackets_arg j) { return a + j; }

	template<class A>
	static inline A add_op_void(const A& a, brackets_arg j) { return a + j; }

	template<class A>
	static inline A sub_op(const A& a, brackets_arg j) { return a - j; }

	template<class A>
	static inline ptrdiff_t dif_op(const A& a0, const A& a1)
	{
		return a0 - a1;
	}

	template<class A>
	static inline void add_asgn(A& a, brackets_arg j) { a += j; }

	template<class A>
	static inline void sub_asgn(A& a, brackets_arg j) { a -= j; }

	// ---------------
	// nd usefull tools
	template <class A>
	struct meta_nd
	{
		typedef typename A::stride_type stride_type;

	};

};


// ----------------------
// is_elem_array

template <class D>
struct is_elem_data_type : public types::t_false { };

template <template <typename, typename, typename> class F,
			class A1, class A2, bool SWAP_ARGS >
struct is_elem_data_type<data::binary_elem_func<F, A1, A2, SWAP_ARGS> >
: public types::t_true { };

template <template <typename, typename> class F, class A>
struct is_elem_data_type<data::unary_elem_func<F, A> >
: public types::t_true { };

template <class A, class IS_IVL_ARRAY>
struct is_elem_array_tool : public types::t_false { };

template <class A>
struct is_elem_array_tool<A, types::t_true> : public
	is_elem_data_type<typename A::data_type>
{ };

template <class A>
struct is_elem_array
: public is_elem_array_tool<A, typename types::is_ivl_array<A>::type> { };

// ----------------------


template <bool SWAP_ARGS, class T, class F>
struct elem_func_swap_op_val
{
	template<class J, class K>
	static inline T from(const J& j, const K& k) { return F::elem_op(j, k); }
	// TODO: for _ptr
	template<class J, class K, class L>
	static inline T from(const L& l, const J& j, const K& k) { return F::elem_op(l, j, k); }
};

template <class T, class F>
struct elem_func_swap_op_val<true, T, F>
{
	template<class J, class K>
	static inline T from(const J& j, const K& k) { return F::elem_op(k, j); }
	// TODO: for _ptr
	template<class J, class K, class L>
	static inline T from(const L& l, const J& j, const K& k) { return F::elem_op(l, k, j); }
};

// swap in and out types too
template <class T, template<typename, typename, typename> class N, class R, class S, class P>
struct elem_func_swap_op_val<true, T, N<R, S, P> >
{
	typedef N<R, P, S> F;
	template<class J, class K>
	static inline T from(const J& j, const K& k) { return F::elem_op(k, j); }
	// TODO: for _ptr
	template<class J, class K, class L>
	static inline T from(const L& l, const J& j, const K& k) { return F::elem_op(l, k, j); }
};

template <bool SWAP_ARGS, class T, class F, class A1_SCALAR, class A2_SCALAR>
struct elem_func_swap_op_arr { };
/*
template <class T, class F>
struct elem_func_swap_op_arr<false, T, F, types::term, types::term>
{
	template<class J, class K>
	static inline T from(const J& j, const K& k)
		{ T x; x.setref(j, k); return x; }
};

template <class T, class F>
struct elem_func_swap_op_arr<true, T, F, types::term, types::term>
{
	template<class J, class K>
	static inline T from(const J& j, const K& k)
		{ T x; x.setref(k, j); return x; }
};
*/
template <bool SWAP_ARGS, class T, class F>
struct elem_func_swap_op_arr<SWAP_ARGS, T, F, types::term, types::term>
{
	template<class J, class K>
	static inline T from(const J& j, const K& k)
		{ T x; x.setref(j, k); return x; }
};

template <bool SWAP_ARGS, class T, class F, class SCALAR1>
struct elem_func_swap_op_arr<SWAP_ARGS, T, F, SCALAR1, types::term>
{
	template<class J, class K>
	static inline T from(const J& j, const K& k)
	{
		SCALAR1 j_s(k.derived().size());
		j_s.setval(j);
		T x; x.setref(j_s, k); return x;
	}
};

template <bool SWAP_ARGS, class T, class F, class SCALAR2>
struct elem_func_swap_op_arr<SWAP_ARGS, T, F, types::term, SCALAR2>
{
	template<class J, class K>
	static inline T from(const J& j, const K& k)
	{
		SCALAR2 k_s(j.derived().size());
		k_s.setval(k);
		T x; x.setref(j, k_s); return x;
	}
};

template <bool SWAP_ARGS, class T, class F, class A1_SCALAR, class A2_SCALAR>
struct elem_func_swap_op
: public
types::t_if<is_elem_array<T>,
	elem_func_swap_op_arr<SWAP_ARGS, T, F, A1_SCALAR, A2_SCALAR>,
	elem_func_swap_op_val<SWAP_ARGS, T, F> >::type
{
};

template <class T, class F, class IS_ELEM_ARRAY>
struct elem_func_unary_op_tool { };

template <class T, class F>
struct elem_func_unary_op_tool<T, F, types::t_false>
{
	template <class J>
	static inline T from(const J& j) { return F::elem_op(j); }
};

template <class T, class F>
struct elem_func_unary_op_tool<T, F, types::t_true>
{
	template <class J>
	static inline T from(const J& j) {
		// TODO: this needs some focus: the implementation below
		// is like this provided that the used class (T) is an ivl::array.
		// however, if T is the elem_func class that is derived from that
		// ??? array then the code below is changed, that's why i comment out:
		T x; x.setref(j); return x;
			//TODO:REMOVE:std::cout << "dbg: " << T(j) << std::endl;
		//return T(j); // (T constructed from j).
	}
};

template <class T, class F>
struct elem_func_unary_op
: public
	elem_func_unary_op_tool<T, F, typename is_elem_array<T>::type>
{
};

//-------------------------------------------------------------
// tools useful for higher elem_func classes


template <
	class T,
	class A1,
	class A2,
	class D1,
	class D2
>
struct binary_operator_result
{
	typedef typename A1::derived_type a1;
	typedef typename A2::derived_type a2;

	typedef typename types::change_data_class_set<D1, a1>::type n_a1;

	typedef typename types::change_data_class_set<D1, a2>::type n_a2;

	typedef typename types::to_type<T, n_a1>::type n1;
	typedef typename types::to_type<T, n_a2>::type n2;

	typedef typename types::change_data_class_set<data::normal, n1>::type nn1;
	typedef typename types::change_data_class_set<data::normal, n2>::type nn2;

	typedef typename types::highest_common<n1, n2>::type_a hc;

	typedef typename types::t_and<
			types::is_base_eq<ivl::array_nd<T, data::normal>, nn1>,
			types::t_not<
				types::is_base_eq<ivl::array_nd<T, data::normal>, nn2> >
		>::type a1_nd;

	typedef typename types::t_and<
			types::is_base_eq<ivl::array_nd<T, data::normal>, nn2>,
			types::t_not<
				types::is_base_eq<ivl::array_nd<T, data::normal>, nn1> >
		>::type a2_nd;

	typedef a2_nd swap;

	typedef typename types::t_if<a1_nd, n1,
		typename types::t_if<a2_nd,
			typename types::change_data_class_set<D2, n2>::type, hc>
			::type>::type type_elem;

	typedef typename types::change_elem_type<T, type_elem>::type type;

	typedef typename types::t_if<swap, const a2&, const a1&>::type in1_t;
	typedef typename types::t_if<swap, const a1&, const a2&>::type in2_t;

};

//! Converts a scalar to an array of type A with repeated value of the scalar.
//! However, if A is array<array<T> >
//! only the outer container is kept, making it an array<T>.
template <class T, class A>
class scalar_to_array
{
	// TODO: I would rather this would make an array of the provided level
	// type and not derived. However this would probably mean to revise
	// the whole ivl. and also I would need a tool to keep the class
	// template, without derived info (leaving term), or is there one ?! :)
	typedef typename types::normal_type<A>::type a_t;

	// this determines the storage type used for elem_func scalar types.
	// @@@@ typedef ref_val_repeat data_type; <-was like that

	//typedef val_repeat data_type;

	//TODO: Why scalars!?
	typedef typename types::t_if<
		types::t_or<
			types::is_base<types::copyscalar_identifier, T>,
			types::is_base<types::scalar_identifier, T>
		>, val_repeat, ref_val_repeat>::type data_type;

public:
	typedef typename types::change_elem_type<T, typename
		types::change_data_class_set<data_type, a_t>::type>::type type;

};


} /* namespace array_details */
} /* namespace ivl */

#endif // IVL_ARRAY_SPECIALIZATION_DETAILS_ELEM_FUNC_TOOLS_HPP
