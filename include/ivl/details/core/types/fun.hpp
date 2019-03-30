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

#ifndef IVL_CORE_DETAILS_TYPES_FUN_HPP
#define IVL_CORE_DETAILS_TYPES_FUN_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace fun {

// TODO: remove when integrating with ivl_func (only for doc)
template <typename T>
struct function : public types::streamable_identifier { };

//-----------------------------------------------------------------------------
// unary identity functor

struct id
{
	template <class T>
	const T& operator()(const T& x) const { return x; }
};

//-----------------------------------------------------------------------------
// logical operator functors

struct lt : public function <lt>
{
	template <class A1, class A2>
	bool operator()(const A1& a1, const A2& a2) const { return a1 < a2; }
};

struct gt : public function <gt>
{
	template <class A1, class A2>
	bool operator()(const A1& a1, const A2& a2) const { return a1 > a2; }
};

//-----------------------------------------------------------------------------
// void binary no-operation

struct nop2
{
	template <typename T1, typename T2>
	void operator()(T1& a1, T2& a2) { }
};

//-----------------------------------------------------------------------------
// swap two items with std::swap

struct swap
{
	template <typename T>
	void operator()(T& a, T& b) { std::swap(a, b); }
};

//-----------------------------------------------------------------------------
// dereference a pointer

struct deref
{
	template <typename T>
	T& operator()(T* p) { return *p; }
};

struct deref_const
{
	template <typename T>
	const T& operator()(const T* p) { return *p; }
};

//-----------------------------------------------------------------------------
// return first item of a tuple

struct tup_first
{
	template <typename T>
	typename T::t1& operator()(T& t) { return t.v1; }
};

struct tup_first_const
{
	template <typename T>
	const typename T::t1& operator()(const T& t) { return t.v1; }
};

//-----------------------------------------------------------------------------
// return second item of a tuple

struct tup_second
{
	template <typename T>
	typename T::t2& operator()(T& t) { return t.v2; }
};

//-----------------------------------------------------------------------------

template <typename F, typename RET = void, bool INV = true>
struct inv
{
	template <typename A, typename B>
	RET operator()(A a, B b) { return F()(b, a); }
};

template <typename F, typename RET>
struct inv <F, RET, false>
{
	template <typename A, typename B>
	RET operator()(A a, B b) { return F()(a, b); }
};

//-----------------------------------------------------------------------------
// apply O as a unary operator to F, where F is a unary function and O is
// a binary function with fixed return type RET

template <typename O, typename F, typename RET = void>
struct un_21
{
	template <typename A, typename B>
	RET operator()(A& a, B& b) { return O()(F()(a), F()(b)); }
};

template <typename O, typename F>
struct un_21 <O, F, void>
{
	template <typename A, typename B>
	void operator()(A& a, B& b) { O()(F()(a), F()(b)); }
};

//-----------------------------------------------------------------------------
// combine binary functions F1, F2 of fixed return types R1, R2 into a pair.
// R1, R2 must be both either void or non-void, in which case the generated
// pair of functions returns a tuple.

template <typename F1, typename F2, typename R1 = void, typename R2 = void>
struct pair_2
{
	template <typename T1, typename T2>
	tuple <R1, R2> operator()(T1& a1, T2& a2)
	{
		return tuple <R1, R2> (F1()(a1, a2), F2()(a1, a2));
	}
};

template <typename F1, typename F2>
struct pair_2 <F1, F2, void, void>
{
	template <typename T1, typename T2>
	void operator()(T1& a1, T2& a2) { F1()(a1, a2); F2()(a1, a2); }
};

//-----------------------------------------------------------------------------
// apply O as a unary operator to both F1 and F2, where F1, F2 are unary
// functions and O is a binary function with fixed return type R

template <typename O, typename F1, typename F2, typename R = void>
struct un2_21 : pair_2 <un_21 <O, F1, R>, un_21 <O, F2, R>, R, R> { };

//-----------------------------------------------------------------------------
// apply binary operator to first items of two tuples

template <typename OP, typename RET = void>
struct tup_first2_const : un_21 <OP, tup_first_const, RET> { };

//-----------------------------------------------------------------------------
// apply binary operator to both items in a tuple

template <typename OP, typename RET = void>
struct tup_both2 : un2_21 <OP, tup_first, tup_second, RET> { };

//-----------------------------------------------------------------------------
// dereference two items before invoking binary operator

template <typename OP, typename RET = void>
struct deref2 : un_21 <OP, deref, RET> { };

template <typename OP, typename RET = void>
struct deref2_const : un_21 <OP, deref_const, RET> { };

//-----------------------------------------------------------------------------
// add state to binary operator. state is set each time an operator is invoked,
// or set/reset manually

template <typename OP>
class state2
{
	bool state;

public:
	state2() : state(false) { }

	void set()   { state = true; }
	void reset() { state = false; }
	bool on()    { return state; }
	bool off()   { return !state; }

	template <typename T>
	void operator()(T& a, T& b) { OP()(a, b); set(); }
};

//-----------------------------------------------------------------------------
// put two items in order: swap them if 1st is not less than 2nd

template <typename COMP, typename SWAP>
struct order
{
	COMP comp;
	SWAP swap;

	template <typename T>
	void operator()(T& a, T& b) { if (comp(b, a)) swap(a, b); }
};

//-----------------------------------------------------------------------------
// 'fun' to 'op' conversion: 'op' are non-template structs with template,
// non-static operation (used by seq)

template <template <typename> class FN>
struct fun2op1
{
	struct fun
	{
		template <class A>
		typename FN <A>::type
		operator()(const A& a) { return FN <A>()(a); }
	};
};

template <template <typename, typename> class FN>
struct fun2op2
{
	struct fun
	{
		template <class A1, class A2>
		typename FN <A1, A2>::type
		operator()(const A1& a1, const A2& a2)
		{
			return FN <A1, A2>()(a1, a2);
		}
	};
};

//-----------------------------------------------------------------------------
// conveniently convert a 'fun' type to an instance of an 'op' specifying only
// its the 'fun' type and not the number of arguments

template <template <typename> class FN>
typename fun2op1 <FN>::fun
fun2op() { return fun2op1 <FN>::fun(); }

template <template <typename, typename> class FN>
typename fun2op2 <FN>::fun
fun2op() { return fun2op2 <FN>::fun(); }

//-----------------------------------------------------------------------------
// binary 'compound' functor to 'compound' 'op' (e.g., a += b)

// template <template <typename, typename> class FN>
// struct comp_fun2op
// {
// 	struct fun
// 	{
// 		template <class A1, class A2>
// 		inline void operator()(A1& a1, const A2& a2)
// 		{
// 			FN <A1, A2> ()(a1, a2);
// 		}
// 	};
// };

//-----------------------------------------------------------------------------
// functor cost : leaving COST to -1 uses the cost specified in FN, if any

template <int N>
struct costs
{
	typedef typename types::number<N> cost;
};

template <class F>
struct costs_like : public costs <F::cost::value> { };

enum { default_cost = 12 };

namespace fun_details {

template <class FN, int COST>
struct cost1 : public costs <COST> { };

template <class FN, int COST>
struct cost2 : public costs <COST> { };

template <class FN>
struct cost1 <FN, -1> { typedef typename FN::cost cost; };

template <class FN>
struct cost2 <FN, -1> { typedef typename FN::cost cost; };

}  // fun_details

//-----------------------------------------------------------------------------
// 'op' to 'map' conversion: 'map' are template structs including type map
// and cost with non-static operator()


template <
	typename OP,
	template <typename> class MAP = types::maps::id,
	int COST = default_cost
>
struct op2map1
{
	template <typename A>
	struct fun : public MAP <A>, public ivl::fun::costs <COST> // kimon ivl::
	{
		typename fun::type
		operator()(const A& a) { return OP()(a); }
	};
};

template <
	typename OP,
	template <typename, typename> class MAP = types::maps::max,
	int COST = default_cost
>
struct op2map2
{
	template <typename A1, typename A2>
	struct fun : public MAP <A1, A2>, public ivl::fun::costs <COST> // kimon ivl::
	{
		typename fun::type
		operator()(const A1& a1, const A2& a2) { return OP()(a1, a2); }
	};
};

template <typename OP, typename RET, int COST = default_cost>
struct fixed_op2map1 :
public op2map1 <OP, types::maps::fixed <RET>::template map, COST> { };

template <typename OP, typename RET, int COST = default_cost>
struct fixed_op2map2 :
public op2map2 <OP, types::maps::fixed <RET, 2>::template map, COST> { };

//-----------------------------------------------------------------------------
// binary 'compound' 'op' to binary 'map' (e.g., a += b to c = a + b)

template <
	typename OP,
	template <typename, typename> class MAP = types::maps::max,
	int COST = default_cost
>
struct comp_op2map
{
	template <class A1, class A2>
	struct fun : public MAP <A1, A2>, public ivl::fun::costs <COST> // kimon ivl::
	{
		typename fun::type operator()(const A1& a1, const A2& a2)
		{
			typename fun::type r(a1);
			OP()(r, a2);
			return r;
		}
	};
};

//-----------------------------------------------------------------------------
// 'map' to 'elem' conversion: 'elem' are template structs with non-template,
// static operation (used by elem_func)

template <
	template <typename> class FN,
	int COST = -1
>
struct map2elem1
{
	template <class R, class A>
	struct fun : public fun_details::cost1 <FN <A>, COST>
	{
		typedef typename FN <A>::type default_ret_type;
		typedef typename types::maps::default_type <R, default_ret_type>::type
			func_ret_type;

		static inline func_ret_type
		elem_op(const A& a)
		{
			return FN <A> ()(a);
		}
	};
};

template <
	template <typename, typename> class FN,
	int COST = -1
>
struct map2elem2
{
	template <class R, class A1, class A2>
	struct fun : public fun_details::cost2 <FN <A1, A2>, COST>
	{
		typedef typename FN <A1, A2>::type default_ret_type;
		typedef typename types::maps::default_type <R, default_ret_type>::type
			func_ret_type;

		static inline func_ret_type
		elem_op(const A1& a1, const A2& a2)
		{
			return FN <A1, A2> ()(a1, a2);
		}
	};
};

//-----------------------------------------------------------------------------

}  // namespace fun

//-----------------------------------------------------------------------------

namespace fn {

static __attribute__ ((unused)) fun::lt      lt;
static __attribute__ ((unused)) fun::gt      gt;
static __attribute__ ((unused)) fun::swap    swap;
static __attribute__ ((unused)) fun::nop2    nop2;

}  // namespace fn

static __attribute__ ((unused)) fun::id      id;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_FUN_HPP
