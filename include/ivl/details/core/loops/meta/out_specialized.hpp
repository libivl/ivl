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

#ifndef IVL_CORE_DETAILS_LOOPS_META_OUT_SPECIALIZED_HPP
#define IVL_CORE_DETAILS_LOOPS_META_OUT_SPECIALIZED_HPP

// for loops_nd_meta

// -- specialized iterators

namespace ivl {
namespace loops {

// cancellation of all out_specialized. used for debugging or
// desperation purposes
#if 0
// case (cancellation) of seq_nd being specialized
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED
>
struct loop_base_nd<1, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
:
public loop_base_nd<2, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	typename A1::_fast_iterator_nd, types::term,
	typename A1::_fast_iterator_nd, types::term>
{ };

// case (cancellation) of seq being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED
>
struct loop_base_nd<1, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
:
public loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	typename A1::iterator, types::term,
	types::term, types::term>
{ };

#else

// --- first case : not nd ---------------------------------------

// case of output seq iterator being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED
>
struct loop_base_nd<1, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(out.iter_specialization() == O_SPECIALIZED) {
			loop_base_nd<2, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				t_false, I_SPECIALIZED,
				typename A1::
					template s_iterator<O_SPECIALIZED>::type, term,
				term, term>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<1, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				number<O_SPECIALIZED - 1>, I_SPECIALIZED,
				term, term, term, term>::
					exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};

// case (post-specialization) of output seq iterator being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	class I_SPECIALIZED
>
struct loop_base_nd<1, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ivl::types::number<0>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
:
public loop_base_nd<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	typename A1::iterator, types::term,
	types::term, types::term>
{ };

// --- seq_nd -----------------------------------------------------

// case (detection) of output seq_nd iterator being specialized

// subcase 1: both iterators still unknown
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED
>
struct loop_base_nd<11, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(out.iter_specialization_nd(inner_dim_1) == O_SPECIALIZED
		&& out.iter_specialization_nd(inner_dim_2) == O_SPECIALIZED) {
			loop_base_nd<2, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				t_false, I_SPECIALIZED,
				typename A1::
					template _fast_s_iterator_nd<O_SPECIALIZED>::type, term,
				typename A1::
					template _fast_s_iterator_nd<O_SPECIALIZED>::type, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else if(out.iter_specialization_nd(inner_dim_1) == O_SPECIALIZED
		&& out.iter_specialization_nd(inner_dim_2) != O_SPECIALIZED) {
			loop_base_nd<11, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				number<O_SPECIALIZED - 1>, I_SPECIALIZED,
				typename A1::
					template _fast_s_iterator_nd<O_SPECIALIZED>::type, term,
				term, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else if(out.iter_specialization_nd(inner_dim_1) != O_SPECIALIZED
		&& out.iter_specialization_nd(inner_dim_2) == O_SPECIALIZED) {
			loop_base_nd<11, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				number<O_SPECIALIZED - 1>, I_SPECIALIZED,
				term, term,
				typename A1::
					template _fast_s_iterator_nd<O_SPECIALIZED>::type, term
				>::exec(out, in,inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<11, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				number<O_SPECIALIZED - 1>, I_SPECIALIZED,
				term, term, term, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};

// subcase 2: iterator 1 still unknown
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED,
	class O_ITER_2
>
struct loop_base_nd<11, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	O_ITER_2, types::term>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(out.iter_specialization_nd(inner_dim_1) == O_SPECIALIZED) {
			loop_base_nd<2, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				types::t_false, I_SPECIALIZED,
				typename A1::
					template _fast_s_iterator_nd<O_SPECIALIZED>::type, term,
				O_ITER_2, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<11, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				number<O_SPECIALIZED - 1>, I_SPECIALIZED,
				term, term, O_ITER_2, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};

// subcase 3: iterator 2 still unknown
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED,
	class O_ITER_1
>
struct loop_base_nd<11, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	O_ITER_1, types::term,
	types::term, types::term>
{
	static
	inline
	void exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
	{
		using namespace ivl::types;

		if(out.iter_specialization_nd(inner_dim_2) == O_SPECIALIZED) {
			loop_base_nd<2, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				types::t_false, I_SPECIALIZED,
				O_ITER_1, term,
				typename A1::
					template _fast_s_iterator_nd<O_SPECIALIZED>::type, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
		else {
			loop_base_nd<11, F, A1, A2,
				ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
				number<O_SPECIALIZED - 1>, I_SPECIALIZED,
				O_ITER_1, term, term, term
				>::exec(out, in, inner_dim_1, inner_dim_2);
		}
	}
};

// post-specialization fill-up of unspecialized nd_iterators with default

template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	class I_SPECIALIZED,
	class O_ITER_2
>
struct loop_base_nd<11, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<0>, I_SPECIALIZED,
	types::term, types::term,
	O_ITER_2, types::term>
:
public loop_base_nd<2, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	typename A1::_fast_iterator_nd, types::term,
	O_ITER_2, types::term>
{ };


template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	class I_SPECIALIZED,
	class O_ITER_1
>
struct loop_base_nd<11, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<0>, I_SPECIALIZED,
	O_ITER_1, types::term,
	types::term, types::term>
:
public loop_base_nd<2, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	O_ITER_1, types::term,
	typename A1::_fast_iterator_nd, types::term>
{ };


template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	class I_SPECIALIZED
>
struct loop_base_nd<11, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<0>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
:
public loop_base_nd<2, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	typename A1::_fast_iterator_nd, types::term,
	typename A1::_fast_iterator_nd, types::term>
{ };

// case (initialization) of output seq_nd iterator being specialized
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED
>
struct loop_base_nd<1, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
:
public loop_base_nd<11, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
{ };

#endif // end of cancellation selection branch

} /* namespace loops */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_LOOPS_META_OUT_SPECIALIZED_HPP
