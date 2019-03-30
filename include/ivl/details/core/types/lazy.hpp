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

#ifndef IVL_CORE_DETAILS_TYPES_LAZY_HPP
#define IVL_CORE_DETAILS_TYPES_LAZY_HPP

namespace ivl {
namespace types {

// ----------------------------------------------------------------

// definition types

// This struct is inherited by all expression classes which are lazy.
// A lazy expression E is computed with typename E::type but is written as E.
struct lazy_expr { };

// used to detect lazy variables
struct lazy_var_identifier { };

// argument (N) in a lazy expression
template <int N>
struct arg { };

// `stop' symbol, below which, lazy is not evaluated. each 
// first (in terms of depth) `stop' is removed per evaluation
template <class T>
struct lazy_stop { };

// `skip' symbol, below which, lazy does substitutions but is not evaluated. 
// each first (in terms of depth) `skip' is removed per evaluation
template <class T>
struct lazy_skip { };

// `next' symbol, below which, the outer-most template is not evaluated. 
// must be right before the symbol with no intermediate `lazy_*' tags.
// each first (in terms of depth) `next' is removed per evaluation
template <class T>
struct lazy_next { };

// ----------------------------------------------------------------

// helper types

template <class T>
struct t_lazy_skip
{
	typedef lazy_skip<T> type;
};





// ----------------------------------------------------------------

// op-execution (determination) mechanism

namespace types_details {

template <class C>
struct lazy_check
{
	typedef C type;
};
/*
template <class T, class IS_LAZY_EXPR>
struct lazy_run_op
{
	typedef T type;
};

template <class T>
struct lazy_run_op<T, t_true>
{
	typedef typename T::type type;
};
*/
// USE SFINAE to determine lazy expressions
template <class T, class IS_LAZY_EXPR>
struct lazy_run_op
{
	typedef T type;
};
/*
template <class T>
struct lazy_run_op<T, types::t_false>
{
	typedef T type;
};
*/
template <class T>
struct lazy_run_op<T, types::t_true>
{
	//typedef T type;
	typedef typename T::type type;
};

} /* namespace types_details */

template <class T>
struct lazy_run
{
	//typedef typename lazy_run_op<T, typename is_base<lazy_expr, T>::type>::type
	//	type;
	// USE SFINAE
	typedef typename types_details::lazy_run_op<T, 
		typename has_typedef_type<T>::type>
	::type type;
	
	//typedef typename types_details::lazy_run_op<T, types::t_true>::type type;
	#if 0
	typedef typename types_details::lazy_run_op<T, 
		typename types::t_not<
			types::t_or<
				types::t_or_3<
					types::is_builtin<T>,
					types::is_ref<T>,
					types::is_ptr<T>
				>,
				types::is_c_array<T>
			>
		>::type		
		//types::t_true
	>::type type;
	#endif
};

// ----------------------------------------------------------------

// not useful if all ::type-having expressions are converted
// to lazy with SFINAE

/*
//
template <class T>
struct lazy_type : public lazy_expr { };

template <class T>
struct lazy_run<lazy_type<T> >
{
	typedef typename T::type type;
};
*/

// ----------------------------------------------------------------

// running mechanism

// This type is used to define a lazy expression
template <class E>
struct lazy
{
	template <class T>
	struct eval
	{
		typedef typename lazy_run<E>::type type;
	};
	template <class T>
	struct skipeval { typedef E type; };
	
	// seq
	template <template<class> class A, template<class> class F>
	struct seq
	{
		typedef typename A<E>::type type;
	};
	template <template<class> class A, template<class, class> class F>
	struct reduce
	{
		typedef typename A<E>::type type;
	};
};

template <class T1>
struct lazy<lazy_stop<T1> >
{
	template <class T>
	struct eval
	{
		typedef T1 type;
	};
	template <class T>
	struct skipeval { typedef T1 type; };
	
	// seq
	template <template<class> class A, template<class> class F>
	struct seq
	{
		typedef T1 type;
	};
	template <template<class> class A, template<class, class> class F>
	struct reduce
	{
		typedef T1 type;
	};
};

template <class T1>
struct lazy<lazy_skip<T1> >
{
	template <class T>
	struct eval
	{
		typedef typename lazy<T1>::template skipeval<T>::type type;
	};
	template <class T>
	struct skipeval
	{
		typedef lazy_skip<typename lazy<T1>::template skipeval<T>::type> type;
	};
	
	// seq
	template <template<class> class A, template<class> class F>
	struct seq
	{
		typedef T1 type;
	};
	template <template<class> class A, template<class, class> class F>
	struct reduce
	{
		typedef T1 type;
	};	
};

template <class T1>
struct lazy<lazy_next<T1> >
{
	template <class T>
	struct eval
	{
		typedef typename lazy<T1>::template nexteval<T>::type type;
	};
	template <class T>
	struct skipeval
	{
		typedef lazy_next<typename lazy<T1>::template skipeval<T>::type> type;
	};
	template <class T>
	struct nexteval
	{
		typedef lazy_next<typename lazy<T1>::template nexteval<T>::type> type;
	};
};

//-----------------------------------------------------------------------------

// extremely special cases first
/*
template <template <template<typename> > class C, template<typename> class CT1, class T1>
struct lazy<C<CT1>, T1>
{
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<typename lazy<T1>::template eval<T>::type> >::
			type type;
	};
};
*/



//-----------------------------------------------------------------------------

template <template <typename> class C, class T1>
struct lazy<C<T1> >
{
	template <class T>
	struct skipeval
	{
		typedef C<typename lazy<T1>::template skipeval<T>::type> type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<typename lazy<T1>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<typename lazy<T1>::template eval<T>::type> type;
	};
	
	// seq
	template <template<class> class A, template<class> class F>
	struct seq
	{
		typedef typename F<C<
			typename lazy<T1>::template seq<A, F>::type
		> >::type type;
	};
	template <template<class> class A, template<class, class> class F>
	struct reduce
	{
		typedef typename lazy<T1>::template reduce<A, F>::type type;
	};	
};

template <template <typename, typename> class C, class T1, class T2>
struct lazy<C<T1, T2> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type>
			type;
	};
	
	// seq
	template <template<class> class A, template<class> class F>
	struct seq
	{
		typedef typename F<C<
			typename lazy<T1>::template seq<A, F>::type,
			typename lazy<T2>::template seq<A, F>::type>
		>::type type;
	};
	template <template<class> class A, template<class, class> class F>
	struct reduce
	{
		typedef typename F<
			typename lazy<T1>::template reduce<A, F>::type,
			typename lazy<T2>::template reduce<A, F>::type
		>::type type;
	};	
	
};

template <template <typename, typename, typename> class C,
	class T1, class T2, class T3>
struct lazy<C<T1, T2, T3> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type>
			type;
	};
	
	// seq
	template <template<class> class A, template<class> class F>
	struct seq
	{
		typedef typename F<C<
			typename lazy<T1>::template seq<A, F>::type,
			typename lazy<T2>::template seq<A, F>::type,
			typename lazy<T3>::template seq<A, F>::type>
		>::type type;
	};
	template <template<class> class A, template<class, class> class F>
	struct reduce
	{
		typedef typename F<
			typename lazy<T1>::template reduce<A, F>::type,
			typename lazy<T2>::template reduce<A, F>::type
		>::type r1_t;
		typedef typename F<
			r1_t,
			typename lazy<T3>::template reduce<A, F>::type
		>::type type;
	};	
	
};

template <template <typename, typename, typename, typename> class C,
	class T1, class T2, class T3, class T4>
struct lazy<C<T1, T2, T3, T4> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type,
			typename lazy<T4>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type>
			type;
	};
	
	// seq
	template <template<class> class A, template<class> class F>
	struct seq
	{
		typedef typename F<C<
			typename lazy<T1>::template seq<A, F>::type,
			typename lazy<T2>::template seq<A, F>::type,
			typename lazy<T3>::template seq<A, F>::type,
			typename lazy<T4>::template seq<A, F>::type>
		>::type type;
	};
	template <template<class> class A, template<class, class> class F>
	struct reduce
	{
		typedef typename F<
			typename lazy<T1>::template reduce<A, F>::type,
			typename lazy<T2>::template reduce<A, F>::type
		>::type r1_t;
		typedef typename F<
			r1_t,
			typename lazy<T3>::template reduce<A, F>::type
		>::type r2_t;
		typedef typename F<
			r2_t,
			typename lazy<T4>::template reduce<A, F>::type
		>::type type;
	};	
		
};

template <template <typename, typename, typename, typename, typename> class C,
	class T1, class T2, class T3, class T4, class T5>
struct lazy<C<T1, T2, T3, T4, T5> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type,
			typename lazy<T4>::template skipeval<T>::type,
			typename lazy<T5>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type>
			type;
	};
};

template <template <typename, typename, typename, typename, typename, typename> class C,
	class T1, class T2, class T3, class T4, class T5, class T6>
struct lazy<C<T1, T2, T3, T4, T5, T6> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type,
			typename lazy<T4>::template skipeval<T>::type,
			typename lazy<T5>::template skipeval<T>::type,
			typename lazy<T6>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type>
			type;
	};
};

template <template <typename, typename, typename, typename, typename, typename, typename> class C,
	class T1, class T2, class T3, class T4, class T5, class T6, class T7>
struct lazy<C<T1, T2, T3, T4, T5, T6, T7> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type,
			typename lazy<T4>::template skipeval<T>::type,
			typename lazy<T5>::template skipeval<T>::type,
			typename lazy<T6>::template skipeval<T>::type,
			typename lazy<T7>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type>
			type;
	};
};

template <template <typename, typename, typename, typename, typename, typename, typename, typename> class C,
	class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
struct lazy<C<T1, T2, T3, T4, T5, T6, T7, T8> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type,
			typename lazy<T4>::template skipeval<T>::type,
			typename lazy<T5>::template skipeval<T>::type,
			typename lazy<T6>::template skipeval<T>::type,
			typename lazy<T7>::template skipeval<T>::type,
			typename lazy<T8>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type,
			typename lazy<T8>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type,
			typename lazy<T8>::template eval<T>::type>
			type;
	};
};

template <template <typename, typename, typename, typename, typename, typename, typename, typename, typename> class C,
	class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
struct lazy<C<T1, T2, T3, T4, T5, T6, T7, T8, T9> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type,
			typename lazy<T4>::template skipeval<T>::type,
			typename lazy<T5>::template skipeval<T>::type,
			typename lazy<T6>::template skipeval<T>::type,
			typename lazy<T7>::template skipeval<T>::type,
			typename lazy<T8>::template skipeval<T>::type,
			typename lazy<T9>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type,
			typename lazy<T8>::template eval<T>::type,
			typename lazy<T9>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type,
			typename lazy<T8>::template eval<T>::type,
			typename lazy<T9>::template eval<T>::type>
			type;
	};
};

template <template <typename, typename, typename, typename, typename, typename, typename, typename, typename, typename> class C,
	class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9, class T0>
struct lazy<C<T1, T2, T3, T4, T5, T6, T7, T8, T9, T0> >
{
	template <class T>
	struct skipeval
	{
		typedef C<
			typename lazy<T1>::template skipeval<T>::type,
			typename lazy<T2>::template skipeval<T>::type,
			typename lazy<T3>::template skipeval<T>::type,
			typename lazy<T4>::template skipeval<T>::type,
			typename lazy<T5>::template skipeval<T>::type,
			typename lazy<T6>::template skipeval<T>::type,
			typename lazy<T7>::template skipeval<T>::type,
			typename lazy<T8>::template skipeval<T>::type,
			typename lazy<T9>::template skipeval<T>::type,
			typename lazy<T0>::template skipeval<T>::type>
			type;
	};
	template <class T>
	struct eval
	{
		typedef typename lazy_run<C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type,
			typename lazy<T8>::template eval<T>::type,
			typename lazy<T9>::template eval<T>::type,
			typename lazy<T0>::template eval<T>::type> >::
			type type;
	};
	template <class T>
	struct nexteval 
	{ 
		typedef C<
			typename lazy<T1>::template eval<T>::type,
			typename lazy<T2>::template eval<T>::type,
			typename lazy<T3>::template eval<T>::type,
			typename lazy<T4>::template eval<T>::type,
			typename lazy<T5>::template eval<T>::type,
			typename lazy<T6>::template eval<T>::type,
			typename lazy<T7>::template eval<T>::type,
			typename lazy<T8>::template eval<T>::type,
			typename lazy<T9>::template eval<T>::type,
			typename lazy<T0>::template eval<T>::type>
			type;
	};
};

template <int N>
struct lazy<arg<N> >
{
	template <class TPL>
	struct skipeval
	{
		typedef typename TPL::template val_t<N>::type type;
	};
	template <class TPL>
	struct eval
	{
		typedef typename TPL::template val_t<N>::type type;
	};
};

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

template <class T1 = types::skip, class T2 = types::skip, class T3 = types::skip>
struct tuply
{
	template<int N>
	struct val_t
	{
		typedef typename t_if<
			t_expr<(N==1)>,
			T1,
				typename t_if<
					t_expr<(N==2)>,
					T2,
					T3
				>::type
		>::type type;
	};
};

template <class T>
struct lzml : public lazy<T>
{
	template <class L>
	struct map
	{
		typedef typename lazy<T>::template eval<L>::type type;
	};
};

template <class T>
struct lzm0 : public lazy<T>
{
	struct map
	{
		typedef typename lazy<T>::template eval<tuply<> >::type type;
	};
};

template <class T>
struct lzm1 : public lazy<T>
{
	template <class A>
	struct map
	{
		typedef typename lazy<T>::template eval<tuply<A> >::type type;
	};
};

template <class T>
struct lzm2 : public lazy<T>
{
	template <class A, class B>
	struct map
	{
		typedef typename lazy<T>::template eval<tuply<A, B> >::type type;
	};
};

template <class T>
struct lzm3 : public lazy<T>
{
	template <class A, class B, class C>
	struct map
	{
		typedef typename lazy<T>::template eval<tuply<A, B, C> >::type type;
	};
};

} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_LAZY_HPP
