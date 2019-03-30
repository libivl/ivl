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

#ifndef IVL_CORE_DETAILS_LOOPS_HPP
#define IVL_CORE_DETAILS_LOOPS_HPP

namespace ivl {
namespace loops {

static const int cpu_intensive = 1000000000;
static const int intensive = 1000000000;

/**
 * @name array loops
@{*/

template <class F, class T, class S, class J, class D>
void loop(ivl::array<T, S>& out, const ivl::array<J, D>& in)
{
	typedef ivl::array<T, S> out_t;
	typedef const ivl::array<J, D> in_t;

	//TODO:
	//typename data::reduce_access_tag_to_1d<in_t::optimal_access_tag>::type
	//for copying array_nd to arrays
	loop_base<1, F, out_t, in_t,
		typename out_t::optimal_access_tag,
		typename in_t::optimal_access_tag,
		typename out_t::has_specialized_iter,
		typename in_t::has_specialized_iter>::exec(out, in);

}

template <class F, class T, class S, class J, class D>
void loop_ww(ivl::array<T, S>& out, ivl::array<J, D>& in_out)
{
	typedef ivl::array<T, S> out_t;
	typedef ivl::array<J, D> in_t;

	//TODO:
	//typename data::reduce_access_tag_to_1d<in_t::optimal_access_tag>::type
	//for copying array_nd to arrays
	loop_base<1, F, out_t, in_t,
		typename out_t::optimal_access_tag,
		typename in_t::optimal_access_tag,
		typename out_t::has_specialized_iter,
		typename in_t::has_specialized_iter>::exec(out, in_out);

}

/**@}*/


//! sequential *= sequential, or any with sequential
template<class F, class A1, class A2,
class O_ITER_1, class I_ITER_1>
inline
void loop_base<3, F, A1, A2,
	ivl::data::seq_optimal_tag, ivl::data::seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, types::term>
	::
	exec(A1& out, A2& in_out)
{
	O_ITER_1 o = out.begin();
	I_ITER_1 i = in_out.begin();
	I_ITER_1 e = in_out.end();
	while(i != e) {
		F::elem_op(*o, *i);
		++o;
		++i;
	}
}


template<class F, class A1, class A2>
struct mt_loop_rnd_op
{
	static void* op(void* ptr)
	{
#if defined(_MSC_VER) || defined(WIN32)

#else
		A1* a1;
		A2* a2;
		size_t start;
		size_t end;
		((tuple<A1*, A2*, size_t, size_t>*)ptr)->
			get(a1, a2, start, end);
		for(; start != end; start++)
			F::elem_op((*a1)[start], (*a2)[start]);
		pthread_exit(0);
#endif
	}
};

template<class F, class A1, class A2,
class O_ITER_1, class I_ITER_1>
inline void mt_loop_rnd(A1& out, A2& in_out)
{
#if defined(_MSC_VER) || defined(WIN32)
	size_t len = in_out.length();
	for(size_t i = 0; i < len; i++) {
		F::elem_op(out[i], in_out[i]);
	}
#else
	typedef tuple<A1*, A2*, size_t, size_t> tpl_t;

	size_t n = in_out.length() / 2;
	if(n > 10) n = 10;
	size_t step = in_out.length() / n;

	size_t start = 0;
	size_t end = step;
	tpl_t* dt = new tpl_t[n];
	pthread_t* th = new pthread_t[n];

	for(size_t i = 0; i < n; i++)
	{
		dt[i].v1 = &out;
		dt[i].v2 = &in_out;
		dt[i].v3 = start;
		dt[i].v4 = end;
		pthread_create(&(th[i]), NULL, mt_loop_rnd_op<F, A1, A2>::op, &(dt[i]));

		start = end;
		end += step;
	}
	for(size_t i = 0; i < n; i++)
		pthread_join(th[i], NULL);

	delete[] dt;
	delete[] th;
#endif
}

//! random *= random
template<class F, class A1, class A2,
class O_ITER_1, class I_ITER_1>
inline
void loop_base<3, F, A1, A2,
	ivl::data::random_optimal_tag, ivl::data::random_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, types::term>
	::
	exec(A1& out, A2& in_out)
{
	#define IVL_MT
	#ifdef IVL_MT
	if(A1::optimal_access_cost::value + A2::optimal_access_cost::value > 20)
	{
		size_t c = A1::optimal_access_cost::value
			+ A2::optimal_access_cost::value;
		if(c * in_out.length() > 2000 && in_out.length() > 1) {
			mt_loop_rnd<F, A1, A2, O_ITER_1, I_ITER_1>(out, in_out);
			return;
		}
	}
	#endif
	size_t len = in_out.length();
	for(size_t i = 0; i < len; i++) {
		F::elem_op(out[i], in_out[i]);
	}
}


} /* namespace loops */

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_LOOPS_HPP
