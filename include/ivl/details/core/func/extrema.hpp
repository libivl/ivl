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

#ifndef IVL_CORE_DETAILS_FUNC_EXTREMA_HPP
#define IVL_CORE_DETAILS_FUNC_EXTREMA_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

using keys::key_val;

//-----------------------------------------------------------------------------

template <
	template <typename, typename, bool> class DER,
	class LT, class DEF, bool INV = false
>
struct extr_base : public vec_func <DER <LT, DEF, INV> >
{
	typedef vec_func <DER <LT, DEF, INV> > base;
	using base::operator[];

protected:
	const DEF def;

//-----------------------------------------------------------------------------

	struct op_off_impl
	{
		template <class A, class V>
		void operator()(A& s, const V& v, size_t n) {
			typedef fun::inv <LT, bool, INV> COMP;
			if (COMP()(v, s.v1)) s = (_, v, n);
		}
	} op_off;

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Least/greatest element + offset of an array
	 *
	 * @param a input array
	 *
	 * @return (_, m, p) where
	 * @param m value of min/max element of a (+/- infinity if empty)
	 * @param p offset of min/max element of a (-1 if a empty)
	 */
	template <class M, class P, class T, class S>
	void operate(M& m, P& p, sep, const array<T, S>& a)
	{
		typedef tuple <T, size_t> R;  // TODO: eliminate by lazy type in functor
		R d = (_, def(T()), -1);      // TODO: eliminate by tuple function
		(_, m, p) = reduce[R()][off] (op_off) (a, d);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Specify comparison functor (gt for min, lt for max)
	 *
	 * @param C (template) type of comparison functor
	 */
	template <class C>
	DER <C, DEF, INV> operator[](key_val <key::comp, C>)
	{
		return DER <C, DEF, INV> (base::dim, def);
	}

	/**
	 * \brief Specify default functor (inf_max for min, inf_min for max)
	 *
	 * @param k default functor, used when single input array is empty
	 */
	template <class D>
	DER <LT, D, INV> operator[](const key_val <key::def, D>& k)
	{
		return DER <LT, D, INV> (base::dim, *k);
	}

//-----------------------------------------------------------------------------

	extr_base(dimension d = _0, const DEF& def = DEF()) :
		base(d), def(def) { }

};

//-----------------------------------------------------------------------------

template <class LT, class DEF, bool INV = false>
struct arg_extr_impl :
	public extr_base <arg_extr_impl, LT, DEF, INV>
{
	typedef extr_base <func_details::arg_extr_impl, LT, DEF, INV> base;
	using base::operator[];
	using base::operate;
	using base::call;
	using base::vec;

//-----------------------------------------------------------------------------

	/**
	 * \brief Offset of least/greatest element of an array
	 *
	 * @param a input array
	 *
	 * @return offset of min/max element of a (-1 if empty)
	 */
	template<class P, class T, class S>
	void operate(P& p, sep, const array<T, S>& a)
	{
		T m;  // TODO: eliminate by (_, _, p) syntax
		(_, m, p) = (*this)++(a);
	}

	template<class T, class S>
	size_t operator()(const array<T, S>& a)
	{
		return typename base::template call <size_t> (this)(a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Dimension-wise offsets of least/greatest elements of an array_nd
	 *
	 * @param a input array_nd
	 *
	 * @return offset of min/max elements of a along specified dimension
	 */
	template <class P, class S1, class T, class S>
	void operate(array_nd <P, S1>& p, sep, const array_nd <T, S>& a)
	{
		vec((_, p), a);
	}

	template <class T, class S>
	array_nd <size_t> operator()(const array_nd <T, S>& a)
	{
		return typename base::template call <array_nd <size_t> > (this)(a);
	}

//-----------------------------------------------------------------------------

	arg_extr_impl(dimension d = _0, const DEF& def = DEF()) :
		base(d, def) { }
};

//-----------------------------------------------------------------------------

template <class LT, class DEF, bool INV = false>
struct extr_impl : public extr_base <extr_impl, LT, DEF, INV>
{
	typedef extr_base <func_details::extr_impl, LT, DEF, INV> base;
	using base::operator[];
	using base::operate;
	using base::def;
	using base::vec;

private:

//-----------------------------------------------------------------------------

	struct OP
	{
		template <class A, class B>
		void operator()(A& a, const B& b) {
			typedef fun::inv <LT, bool, INV> COMP;
			if (COMP()(b, a)) a = b;
		}
	} op;

	template <class A, class B>
	struct F : public fun::comp_op2map <OP>::template fun <A, B> { };

// 	TODO: Fix functor format. The following functor is automatically
// 	generated; kept here for reference.

// 	template <class A, class B>
// 	struct F : public types::maps::max <A, B>, public fun::costs <12>
// 	{
// 		typename F::type operator()(const A& a, const B& b) {
// 			typedef fun::inv <LT, bool, INV> COMP;
// 			return COMP()(b, a) ? b : a;
// 		}
// 	};

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Element-wise minimum/maximum of two arrays or scalars
	 *
	 * @param a first input array or scalar
	 * @param b second input array or scalar
	 *
	 * @return element-wise min/max of a and b
	 */
	template <class A, class B>
	typename binary_elem_call <F, A, B>::type
	operator()(const A& a, const B& b)
	{
		return binary_elem_call <F, A, B>::from(a, b);
	}

	template <class M, class A, class B>
	void operate(M& m, sep, const A& a, const B& b)
	{
		m = (*this)(a, b);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Least/greatest element of an array
	 *
	 * @param a input array
	 *
	 * @return value of min/max element of a (+/- infinity if empty)
	 */
	template <class M, class T, class S>
	void operate(M& m, sep, const array <T, S>& a)
	{
		m = reduce (op, def) (a);
	}

	template <class T, class S>
	T operator()(const array <T, S>& a)
	{
		return typename base::template call <T>(this)(a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Dimension-wise least/greatest elements of an array_nd
	 *
	 * @param a input array_nd
	 *
	 * @return value of min/max elements of a along specified dimension
	 */
	template <class M, class T, class S>
	void operate(M& m, sep, const array_nd<T, S>& a)
	{
		vec((_, m), a);
	}

	template <class T, class S>
	array_nd<T> operator()(const array_nd<T, S>& a)
	{
		return typename base::template call<array_nd<T> >(this)(a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Dimension-wise least/greatest elements + offsets of an array_nd
	 *
	 * @param a input array_nd
	 *
	 * @return (_, m, p) where
	 * @param m value of min/max elements of a along specified dimension
	 * @param p min/max element offset of a along specified dimension
	 */
	template <class M, class P, class T, class S>
	void operate(M& m, P& p, sep, const array_nd <T, S>& a)
	{
		vec((_, m, p), a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Switch to arg_min/max operation
	 */
	arg_extr_impl <LT, DEF, INV> operator[](key::arg)
	{
		return arg_extr_impl <LT, DEF, INV>(base::dim, def);
	}

//-----------------------------------------------------------------------------

	extr_impl(dimension d = _0, const DEF& def = DEF()) : base(d, def) { }
};

//-----------------------------------------------------------------------------

struct extrema_impl : public vec_func <extrema_impl>
{

private:

//-----------------------------------------------------------------------------

	struct op_impl {
		template <class A, class V>
		void operator()(A& s, const V& v) {
			if (s.v1 > v) s.v1 = v;
			if (s.v2 < v) s.v2 = v;
		}
	} op;

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Least + greatest element of an array
	 *
	 * @param a input array
	 *
	 * @return (_, min, max) where
	 * @param min least element of a (+ infinity if empty)
	 * @param max greatest element of a (- infinity if empty)
	 */
	template <class M1, class M2, class T, class S>
	void operate(M1& min, M2& max, sep, const array <T, S>& a)
	{
		// TODO: eliminate R by lazy type in functor
		// TODO: eliminate d by tuple function
		typedef tuple <M1, M2> R;
		R d = (_, inf_max <T>(), inf_min <T>());
		(_, min, max) = reduce[R()] (op) (a, d);
	}

	template<class T, class S>
	ret <T, T> operator()(const array<T, S>& a)
	{
		return call <T, T>(this)(a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Dimension-wise least + greatest elements of an array_nd
	 *
	 * @param a input array_nd
	 *
	 * @return (_, min, max) where
	 * @param min least elements of a along specified dimension
	 * @param max greatest elements of a along specified dimension
	 */
	template <class M1, class M2, class T, class S>
	void operate(M1& min, M2& max, sep, const array_nd <T, S>& a)
	{
		vec((_, min, max), a);
	}

	template<class T, class S>
	ret <array_nd <T>, array_nd <T> > operator()(const array_nd <T, S>& a)
	{
		return call <array_nd <T>, array_nd <T> >(this)(a);
	}

//-----------------------------------------------------------------------------

	extrema_impl(dimension d = _0) : vec_func <extrema_impl>(d) { }
};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun {

typedef func_details::extr_impl <fun::lt, fun::inf_max>       min;
typedef func_details::extr_impl <fun::lt, fun::inf_min, true> max;

typedef func_details::arg_extr_impl <fun::lt, fun::inf_max>       arg_min;
typedef func_details::arg_extr_impl <fun::lt, fun::inf_min, true> arg_max;

typedef func_details::extrema_impl extrema;

}  // namespace fun

//-----------------------------------------------------------------------------

namespace key_fun {

typedef key_fun <key::min, fun::min> min;
typedef key_fun <key::max, fun::max> max;

typedef key_fun <key::arg_min, fun::arg_min> arg_min;
typedef key_fun <key::arg_max, fun::arg_max> arg_max;

typedef key_fun <key::extrema, fun::extrema> extrema;

}  // namespace key_fun

//-----------------------------------------------------------------------------

/**
 * Note: In WIN32 targets, either #undef min, #undef max
 * or compile with IVL_USE_MINMAX to use these functions
 */

static __attribute__ ((unused)) key_fun::min        min;
static __attribute__ ((unused)) key_fun::max        max;
static __attribute__ ((unused)) key_fun::arg_min    arg_min;
static __attribute__ ((unused)) key_fun::arg_max    arg_max;
static __attribute__ ((unused)) key_fun::extrema    extrema;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif // IVL_CORE_DETAILS_FUNC_EXTREMA_HPP
