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

#ifndef IVL_CORE_DETAILS_LOOPS_META_LOOPS_ND_META_HPP
#define IVL_CORE_DETAILS_LOOPS_META_LOOPS_ND_META_HPP

/*
* This file contains the various template structs which lead to compile-time
* decision of the right loop::exec() function to be called for the requested
* operands, among the available exec loops. There is also run-time decision
* when SPECIALIZED ITERATORS are involved which does a recursive loop from
* 1 to max specialization to check which is the correct int template argument
* to provide to the loop function.
* Please you are notified that the below code is not readable but complicated.
* There is no essence of time wasting in the below code except from the little
* overhead of the specialized iterator decision and the lost compiled time, so
* no optimizations or changes are predicted for that code.
* A little hint for the code wanna understander for that code is that the
* number which is the first template argument of loop_base is the step in
* which the decision process is at. step 1 resolves the left-side (output)
* iterator, step 2 the right-side (input) iterator and step 3 is ready to
* find the correct specialization of loop_base to call the corresponding ::exec.
*/

/* Todo:
Missing cases! are specialized_nd x specialized_1d which are treated
as specialized_nd x non_specialized_1d or they just dont work (not checked).
*/

namespace ivl {
namespace loops {

template<
	int STEP,
	class F,
	class OUT,
	class IN,
	class O_OPTIMAL_ACCESS,
	class I_OPTIMAL_ACCESS,
	class O_SPECIALIZED,
	class I_SPECIALIZED,
	class O_ITER_1 = types::term,
	class I_ITER_1 = types::term,
	class O_ITER_2 = types::term,
	class I_ITER_2 = types::term
>
struct loop_base_nd { };

// retrieve type for the output iterator if no specialization
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS, class ANY
>
struct loop_base_nd<1, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, ANY,
	types::term, types::term,
	types::term, types::term>
:
public loop_base_nd<2, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, ANY,
	typename A1::_fast_iterator_nd, types::term,
	typename A1::_fast_iterator_nd, types::term>
{ };

template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS, class ANY
>
struct loop_base_nd<1, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, ANY,
	types::term, types::term,
	types::term, types::term>
:
public loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, ANY,
	typename A1::iterator, types::term,
	types::term, types::term>
{ };
/*
// state proceed after specialization has completed.
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS, class ANY,
	class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<11, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, ANY,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, ANY,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
{ };
*/

// retrieve type for the input iterator if no specialization
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class ANY,
	class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	ANY, types::t_false,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	ANY, types::t_false,
	O_ITER_1, typename types::best_fast_iterator_nd<A2>::type,
	O_ITER_2, typename types::best_fast_iterator_nd<A2>::type>
{ };

template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS, class ANY,
	class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ANY, types::t_false,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ANY, types::t_false,
	O_ITER_1, typename types::best_iterator<A2>::type,
	O_ITER_2, types::term>
{
};
/*
// state proceed after specialization has succeeded
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS, class ANY,
	class O_ITER_1, class O_ITER_2,
	class I_ITER_1, class I_ITER_2
>
struct loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ANY, types::t_false,
	O_ITER_1, I_ITER_1,
	O_ITER_2, I_ITER_2>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ANY, types::t_false,
	O_ITER_1, I_ITER_1,
	O_ITER_2, I_ITER_2>
{ };
*/
// specialization cases are included in files in_specialized.hpp and
// out_specialized.hpp

// cases depending on optimal access

//! seq_nd * seq_nd
template<
	class F, class A1, class A2,
	class O_ITER_1, class I_ITER_1, class O_ITER_2, class I_ITER_2
>
struct loop_base_nd<3, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, O_ITER_2, I_ITER_2>
{
	static inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2);
};

//! anything * seq_nd
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	class O_ITER_1, class I_ITER_1, class I_ITER_2
>
struct loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, I_ITER_2>
{
	static inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2);
};

//! seq_nd * anything
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	class O_ITER_1, class I_ITER_1, class O_ITER_2
>
struct loop_base_nd<3, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, O_ITER_2, types::term>
{
	static inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2);
};

//! seq * seq
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	class O_ITER_1, class I_ITER_1
>
struct loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, types::term>
{
	static inline
	void exec(A1& out, const A2& in,
		int inner_dim_1, int inner_dim_2)
		{
			ivl::loops::loop<F>(out.base(), in.base());
		}
};


} /* namespace loops */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_LOOPS_META_LOOPS_ND_META_HPP
