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

#ifndef IVL_CORE_DETAILS_LOOPS_META_IN_SPECIALIZED_HPP
#define IVL_CORE_DETAILS_LOOPS_META_IN_SPECIALIZED_HPP

namespace ivl {
namespace loops {

// cancellation of all in_specialized. used for debugging or
// desperation purposes
#if 0
// case (cancellation) of seq_nd being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	int I_SPECIALIZED, class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, typename types::best_fast_iterator_nd<A2>::type,
	O_ITER_2, typename types::best_fast_iterator_nd<A2>::type>
{ };

// case (cancellation) of seq being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	int I_SPECIALIZED, class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, typename A2::types::best_iterator<A2>::type,
	O_ITER_2, types::term>
{ };

#else

// --- first case : not nd ---------------------------------------

// case of input seq iterator being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	int I_SPECIALIZED, class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(in.iter_specialization() == I_SPECIALIZED) {
			loop_base_nd<3, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				t_false, t_false,
				O_ITER_1, typename
					types::best_fast_iterator_nd<A2, I_SPECIALIZED>::type,
				term, term>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<2, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				t_false, number<I_SPECIALIZED - 1>,
				O_ITER_1, term, term, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};

// case (post-specialization) of input seq iterator being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::number<0>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, typename types::best_iterator<A2>::type,
	O_ITER_2, types::term>
{ };

// --- seq_nd -----------------------------------------------------

// case (detection) of input seq_nd iterator being specialized

// subcase 1: both iterators still unknown
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	int I_SPECIALIZED,
	class O_ITER_1,
	class O_ITER_2
>
struct loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(in.iter_specialization_nd(inner_dim_1) == I_SPECIALIZED
		&& in.iter_specialization_nd(inner_dim_2) == I_SPECIALIZED) {
			loop_base_nd<3, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, t_false,
				O_ITER_1, typename
					types::best_fast_iterator_nd<A2, I_SPECIALIZED>::type,
				O_ITER_2, typename
					types::best_fast_iterator_nd<A2, I_SPECIALIZED>::type
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else if(in.iter_specialization_nd(inner_dim_1) == I_SPECIALIZED
		&& in.iter_specialization_nd(inner_dim_2) != I_SPECIALIZED) {
			loop_base_nd<21, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, number<I_SPECIALIZED - 1>,
				O_ITER_1, typename
					types::best_fast_iterator_nd<A2, I_SPECIALIZED>::type,
				O_ITER_2, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else if(in.iter_specialization_nd(inner_dim_1) != I_SPECIALIZED
		&& in.iter_specialization_nd(inner_dim_2) == I_SPECIALIZED) {
			loop_base_nd<21, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, number<I_SPECIALIZED - 1>,
				O_ITER_1, term,
				O_ITER_2, typename
					types::best_fast_iterator_nd<A2, I_SPECIALIZED>::type
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<21, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, number<I_SPECIALIZED - 1>,
				O_ITER_1, term, O_ITER_2, term>::
					exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};

// subcase 2: iterator 1 still unknown
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	int I_SPECIALIZED,
	class O_ITER_1,
	class O_ITER_2, class I_ITER_2
>
struct loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	O_ITER_2, I_ITER_2>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(in.iter_specialization_nd(inner_dim_1) == I_SPECIALIZED) {
			loop_base_nd<3, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, t_false,
				O_ITER_1, typename
					types::best_fast_iterator_nd<A2, I_SPECIALIZED>::type,
				O_ITER_2, I_ITER_2
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<21, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, number<I_SPECIALIZED - 1>,
				O_ITER_1, term, O_ITER_2, I_ITER_2>::
					exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};

// subcase 2: iterator 2 still unknown
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	int I_SPECIALIZED,
	class O_ITER_1, class I_ITER_1,
	class O_ITER_2
>
struct loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<I_SPECIALIZED>,
	O_ITER_1, I_ITER_1,
	O_ITER_2, types::term>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(in.iter_specialization_nd(inner_dim_2) == I_SPECIALIZED) {
			loop_base_nd<3, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, t_false,
				O_ITER_1, I_ITER_1,
				O_ITER_2, typename
					types::best_fast_iterator_nd<A2, I_SPECIALIZED>::type
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<21, F, A1, A2,
				O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
				t_false, number<I_SPECIALIZED - 1>,
				O_ITER_1, I_ITER_1, O_ITER_2, term>::
					exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};


// post-specialization fill-up of unspecialized nd_iterators with default

template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	class O_ITER_1,
	class O_ITER_2, class I_ITER_2
>
struct loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<0>,
	O_ITER_1, types::term,
	O_ITER_2, I_ITER_2>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, typename types::best_fast_iterator_nd<A2>::type,
	O_ITER_2, I_ITER_2>
{ };

template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	class O_ITER_1, class I_ITER_1,
	class O_ITER_2
>
struct loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<0>,
	O_ITER_1, I_ITER_1,
	O_ITER_2, types::term>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1,
	O_ITER_2, typename types::best_fast_iterator_nd<A2>::type
>
{ };

template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	class O_ITER_1,
	class O_ITER_2
>
struct loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<0>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, typename types::best_fast_iterator_nd<A2>::type,
	O_ITER_2, typename types::best_fast_iterator_nd<A2>::type>
{ };

// case (initialization) of input seq_nd iterator being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	int I_SPECIALIZED,
	class O_ITER_1, class O_ITER_2
>
struct loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<21, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, ivl::types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	O_ITER_2, types::term>
{ };

#endif // end of cancellation selection branch

} /* namespace loops */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_LOOPS_META_IN_SPECIALIZED_HPP
