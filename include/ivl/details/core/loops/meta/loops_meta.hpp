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

#ifndef IVL_CORE_DETAILS_LOOPS_META_LOOPS_META_HPP
#define IVL_CORE_DETAILS_LOOPS_META_LOOPS_META_HPP

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
struct loop_base { };

// find the output iterator
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	class I_SPECIALIZED
>
struct loop_base<1, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
:
public loop_base<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, I_SPECIALIZED,
	typename A1::iterator, types::term,
	types::term, types::term>
{ };

// find the input iterator
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS, class O_ITER_1
>
struct loop_base<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, types::term,
	types::term, types::term>
:
public loop_base<3, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, typename types::best_iterator<A2>::type,
	types::term, types::term>
{ };

// -- specialized iterators


// case of output iterator being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	int O_SPECIALIZED, class I_SPECIALIZED
>
struct loop_base<1, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	ivl::types::number<O_SPECIALIZED>, I_SPECIALIZED,
	types::term, types::term,
	types::term, types::term>
{
	static
	inline
	void exec(A1& out, A2& in)
	{
		using namespace ivl::types;

		if(out.iter_specialization() == O_SPECIALIZED) {
			loop_base<2, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				t_false, I_SPECIALIZED,
				typename types::best_iterator<A1, O_SPECIALIZED>::type, term,
				term, term>::exec(out, in);
		}
		else {
			loop_base<1, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				typename t_if<t_expr<O_SPECIALIZED == 1>,
					t_false, number<O_SPECIALIZED - 1> >::type, I_SPECIALIZED,
				term, term, term, term>::exec(out, in);
		}
	}
};

// case of input iterator being specialized
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	int I_SPECIALIZED, class O_ITER_1
>
struct loop_base<2, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::number<I_SPECIALIZED>,
	O_ITER_1, types::term,
	types::term, types::term>
{
	static
	inline
	void exec(A1& out, A2& in)
	{
		using namespace ivl::types;

		if(in.iter_specialization() == I_SPECIALIZED) {
			loop_base<3, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				t_false, t_false,
				O_ITER_1, typename types::
					best_iterator<A2, I_SPECIALIZED>::type,
				term, term>::exec(out, in);
		}
		else {
			loop_base<2, F, A1, A2,
				O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
				t_false, typename t_if<t_expr<I_SPECIALIZED == 1>,
					t_false, number<I_SPECIALIZED - 1> >::type,
				O_ITER_1, term, term, term>::exec(out, in);
		}
	}
};

// cases depending on optimal access

template<
	class F, class A1, class A2,
	class O_ITER_1, class I_ITER_1
>
struct loop_base<3,F, A1, A2,
	ivl::data::seq_optimal_tag, ivl::data::seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, types::term>
{
	static inline
	void exec(A1& out, A2& in);
};

template<
	class F, class A1, class A2,
	class O_ITER_1, class I_ITER_1
>
struct loop_base<3, F, A1, A2,
	ivl::data::random_optimal_tag, ivl::data::random_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, types::term>
{
	static inline
	void exec(A1& out, A2& in);
};

template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS, class I_OPTIMAL_ACCESS,
	class O_ITER_1, class I_ITER_1
>
struct loop_base<3, F, A1, A2,
	O_OPTIMAL_ACCESS, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, types::term>
: public
	loop_base<3, F, A1, A2,
	ivl::data::seq_optimal_tag, ivl::data::seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, types::term>
{ };

} /* namespace loops */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_LOOPS_META_LOOPS_META_HPP
