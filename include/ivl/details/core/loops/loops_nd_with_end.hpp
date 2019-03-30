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

#ifndef IVL_CORE_DETAILS_LOOPS_LOOPS_ND_WITH_END_HPP
#define IVL_CORE_DETAILS_LOOPS_LOOPS_ND_WITH_END_HPP

namespace ivl {

namespace loops {

template <class F, class T, class S, class K, class J, class D, class P>
void loop(array_nd<T, S, K>& out, const array_nd<J, D, P>& in)
{
	typedef array_nd<T, S, K> out_t;
	typedef const array_nd<J, D, P> in_t;

	int id[2] = {0, 0};
	int j = 0;

	for(size_t i = 0; i < out.ndims() && j < 2; i++) {
		if(out.size(i) > 1) id[j++] = int(i);
	}

	loop_base_nd<1, F, out_t, in_t,
		typename out_t::optimal_access_tag,
		typename in_t::optimal_access_tag,
		typename out_t::has_specialized_iter,
		typename in_t::has_specialized_iter>::
			exec(out, in, id[0], id[1]);

}

template <class F, class T, class S, class K, class J, class D, class P>
void loop_ww(array_nd<T, S, K>& out, array_nd<J, D, P>& in)
{
	typedef array_nd<T, S, K> out_t;
	typedef array_nd<J, D, P> in_t;

	int id[2] = {0, 0};
	int j = 0;

	for(size_t i = 0; i < out.ndims() && j < 2; i++) {
		if(out.size(i) > 1) id[j++] = int(i);
	}

	loop_base_nd<1, F, out_t, in_t,
		typename out_t::optimal_access_tag,
		typename in_t::optimal_access_tag,
		typename out_t::has_specialized_iter,
		typename in_t::has_specialized_iter>::
			exec(out, in, id[0], id[1]);

}

//! seq_nd * anything experimental loop
template<
	class F, class A1, class A2,
	class I_OPTIMAL_ACCESS,
	class O_ITER_1, class I_ITER_1, class O_ITER_2
>
inline
void loop_base_nd<3, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, I_OPTIMAL_ACCESS,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, O_ITER_2, types::term>::
	exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
{
	// Remark: as a contradiction to the coding style, this function is
	// way more lengthy than expected. However this is because it was
	// decided by kimonas that this is the best and simplest design for that
	// particular function which induces complications to improve speed.

	// type definitions
	typedef A1 out_t;
	typedef A2 in_t;

	typedef typename out_t::iterator_nd iter_t;
	typedef typename iter_t::iter_nd_border_walker brd_t;

	// input iterator
	I_ITER_1 it_src = in.begin();

	// TODO:
	// assert that the dimensions are the same

	// quickly proceed for 1d arrays
	if(out.ndims() == 1) {
		O_ITER_1 it = out._begin(0);
		//todo:!!bug. out != in iterator???
		for(O_ITER_1 it_end = out._end(0); it != it_end; ++it) {
			F::elem_op(*it, *it_src);
			++it_src;
		}
		return;
	}

	// arrays with info about the dimensions
	internal::little_arrayling<iter_t> iters(out.ndims());
	internal::little_arrayling<brd_t> first_to_last(out.ndims());
	internal::little_arrayling<size_t> pos(out.ndims());
	internal::little_arrayling<size_t> length(out.ndims());
	internal::little_arrayling<size_t> dim_map(out.ndims());

	size_t i, j = 0; // j: the number of total dims after filtering
	length[1] = 1;

	// remove all singleton dims. in case all need removal, keep the last dim.
	for(i = 0; i < out.ndims(); i++) {
		if(out.size(i) > 1 || (j == 0 && i == out.ndims() - 1)) {
			iters[j] = out._begin(i);
			length[j] = out.size(i);
			first_to_last[j] = out.first_to_last(j);
			pos[j] = 0;
			dim_map[j] = i;
			j++;
		}
	}

	// sorting dim0 <-> dim1 for speed improvement.
	/* IS THIS POSSIBLE??? and how do i recognize to use ITER_1 or ITER_0 ??
	if(j > 1 && out.size(dim_map[1]) > 2 * out.size(dim_map[0])
			&& out.size(dim_map[0]) < 100) {
		std::swap(iters[0], iters[1]);
		std::swap(length[0], length[1]);
		std::swap(first_to_last[0], first_to_last[1]);
		std::swap(dim_map[0], dim_map[1]);
	}*/

	// local variables for the inner dimensions to improve speed.
	O_ITER_1 it0 = iters[0];
	O_ITER_1 it0_end;
	O_ITER_2 it1 = iters[1];
	brd_t first_to_last1 = first_to_last[1];
	brd_t begin_to_end0 = out.begin_to_end(dim_map[0]);
	size_t length1 = length[1];
	size_t pos1 = 0;

	// special loop for 1 or 2 dims (after filtering)
	if(j <= 2) {
		it0_end = out._end(dim_map[0]);
		for(; it0 != it0_end; ++it0) {
			F::elem_op(*it0, *it_src);
			++it_src;
		}
		//it0_end = out._end(dim_map[0]);
		while(++pos1 < length1) {
			it0 -= begin_to_end0;
			it0.inc_along_other_dim_at_begin(it1);

			for(it0_end = it0 + begin_to_end0; it0 != it0_end; ++it0) {
				F::elem_op(*it0, *it_src);
				++it_src;
			}
			//it0_end.inc_along(it1);
			// TODO: consider using this approach of it0_end
			// as a possible speed improvement in the generic loop. need bench.
		}
		return;
	}

	// loop for more than 2 dims.
	do {
		//it0 + begin_to_end0; wipe these two strange lines
		//it0 != it0_end;

		for(it0_end = it0 + begin_to_end0; it0 != it0_end; ++it0) {
			*it0;
			*it_src;
			F::elem_op(*it0, *it_src);
			++it_src;
		}

		it0 -= begin_to_end0;
		if(++pos1 < length1) {
			it0.inc_along_other_dim_at_begin(it1);
		}
		else {
			it0 -= first_to_last1;
			pos1 = 0;
			i = 2;
			while(++pos[i] >= length[i]) {
				pos[i] = 0;
				it0 -= first_to_last[i];
				i++;
				if(i >= j) return; // loop is broken here.
			}
			it0.inc_along_other_dim_at_begin(iters[i]);
		}
	} while(1);
}


//! anything * seq_nd experimental loop
template<
	class F, class A1, class A2,
	class O_OPTIMAL_ACCESS,
	class O_ITER_1, class I_ITER_1, class I_ITER_2
>
inline
void loop_base_nd<3, F, A1, A2,
	O_OPTIMAL_ACCESS, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, types::term, I_ITER_2>::
	exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
{
	// Remark: as a contradiction to the coding style, this function is
	// way more lengthy than expected. However this is because it was
	// decided by kimonas that this is the best and simplest design for that
	// particular function which induces complications to improve speed.

	// type definitions
	typedef A1 out_t;
	typedef A2 in_t;

	typedef typename in_t::const_iterator_nd iter_t;
	typedef typename iter_t::iter_nd_border_walker brd_t;

	// input iterator
	O_ITER_1 it_dst = out.begin();

	// TODO:
	// assert that the dimensions are the same

	// quickly proceed for 1d arrays
	// TODO: ????? why is here it_dst and in some other places it_src??
	if(in.ndims() == 1) {
		I_ITER_1 it = in._begin(0);
		for(I_ITER_1 it_end = in._end(0); it != it_end; ++it) {
			F::elem_op(*it_dst, *it);
			++it_dst;
		}
		return;
	}

	// arrays with info about the dimensions
	internal::little_arrayling<iter_t> iters(in.ndims());
	internal::little_arrayling<brd_t> first_to_last(in.ndims());
	internal::little_arrayling<size_t> pos(in.ndims());
	internal::little_arrayling<size_t> length(in.ndims());
	internal::little_arrayling<size_t> dim_map(in.ndims());

	size_t i, j = 0; // j: the number of total dims after filtering
	length[1] = 1;

	// remove all singleton dims. in case all need removal, keep the last dim.
	for(i = 0; i < in.ndims(); i++) {
		if(in.size(i) > 1 || (j == 0 && i == in.ndims() - 1)) {
			iters[j] = in._begin(i);
			length[j] = in.size(i);
			first_to_last[j] = in.first_to_last(j);
			pos[j] = 0;
			dim_map[j] = i;
			j++;
		}
	}

	// sorting dim0 <-> dim1 for speed improvement.
	// TODO: on all others!!!!!!
	/* IS THIS POSSIBLE??? and how do i recognize to use ITER_1 or ITER_0 ??
	if(j > 1 && in.size(dim_map[1]) > 2 * in.size(dim_map[0])
			&& in.size(dim_map[0]) < 100) {
		std::swap(iters[0], iters[1]);
		std::swap(length[0], length[1]);
		std::swap(first_to_last[0], first_to_last[1]);
		std::swap(dim_map[0], dim_map[1]);
	}*/

	// local variables for the inner dimensions to improve speed.
	I_ITER_1 it0 = iters[0];
	I_ITER_1 it0_end;
	I_ITER_2 it1 = iters[1];
	brd_t first_to_last1 = first_to_last[1];
	brd_t begin_to_end0 = in.begin_to_end(dim_map[0]);
	size_t length1 = length[1];
	size_t pos1 = 0;

	// special loop for 1 or 2 dims (after filtering)
	if(j <= 2) {
		it0_end = in._end(dim_map[0]);
		for(; it0 != it0_end; ++it0) {
			F::elem_op(*it_dst, *it0);
			++it_dst;
		}
		//it0_end = in._end(dim_map[0]);
		while(++pos1 < length1) {
			it0 -= begin_to_end0;
			it0.inc_along_other_dim_at_begin(it1);
			for(it0_end = it0 + begin_to_end0; it0 != it0_end; ++it0) {
				F::elem_op(*it_dst, *it0);
				++it_dst;
			}
			//it0_end.inc_along(it1);
			// TODO: consider using this approach of it0_end
			// as a possible speed improvement in the generic loop. need bench.
		}
		return;
	}

	// loop for more than 2 dims.
	do {
		for(it0_end = it0 + begin_to_end0; it0 != it0_end; ++it0) {
			F::elem_op(*it_dst, *it0);
			++it_dst;
		}
		it0 -= begin_to_end0;
		if(++pos1 < length1) {
			it0.inc_along_other_dim_at_begin(it1);
		}
		else {
			it0 -= first_to_last1;
			pos1 = 0;
			i = 2;
			while(++pos[i] >= length[i]) {
				pos[i] = 0;
				it0 -= first_to_last[i];
				i++;
				if(i >= j) return; // loop is broken here.
			}
			it0.inc_along_other_dim_at_begin(iters[i]);
		}
	} while(1);
}




//! seq_nd * seq_nd experimental loop
template<
	class F, class A1, class A2,
	class O_ITER_1, class I_ITER_1, class O_ITER_2, class I_ITER_2
>
inline
void loop_base_nd<3, F, A1, A2,
	ivl::data::nd_seq_optimal_tag, ivl::data::nd_seq_optimal_tag,
	types::t_false, types::t_false,
	O_ITER_1, I_ITER_1, O_ITER_2, I_ITER_2>::
	exec(A1& out, A2& in,
		int inner_dim_1, int inner_dim_2)
{
	// Remark: as a contradiction to the coding style, this function is
	// way more lengthy than expected. However this is because it was
	// decided by kimonas that this is the best and simplest design for that
	// particular function which induces complications to improve speed.

	// type definitions
	typedef A1 out_t;
	typedef A2 in_t;

	// Almost everything is doubled, one for src, one for dst

	//dst
	typedef typename out_t::iterator_nd iter_t;
	typedef typename iter_t::iter_nd_border_walker brd_t;
	//src
	typedef typename in_t::const_iterator_nd siter_t;
	typedef typename siter_t::iter_nd_border_walker sbrd_t;

	// TODO:
	// assert that the dimensions are the same.


	// quickly proceed for 1d arrays
	if(out.ndims() == 1) {
		O_ITER_1 it = out._begin(0);
		I_ITER_1 it_src = in._begin(0);
		for(O_ITER_1 it_end = out._end(0); it != it_end; ++it) {
			F::elem_op(*it, *it_src);
			++it_src;
		}
		return;
	}

	// arrays with info about the dimensions
	internal::little_arrayling<iter_t> iters(out.ndims());
	internal::little_arrayling<brd_t> first_to_last(out.ndims());
	internal::little_arrayling<size_t> pos(out.ndims());
	internal::little_arrayling<size_t> length(out.ndims());
	internal::little_arrayling<size_t> dim_map(out.ndims());
	//src
	internal::little_arrayling<siter_t> siters(out.ndims());
	internal::little_arrayling<sbrd_t> sfirst_to_last(out.ndims());

	size_t i, j = 0; // j: the number of total dims after filtering
	length[1] = 1;

	// remove all singleton dims. in case all need removal, keep the last dim.
	for(i = 0; i < out.ndims(); i++) {
		if(out.size(i) > 1 || (j == 0 && i == out.ndims() - 1)) {
			iters[j] = out._begin(i);
			length[j] = out.size(i);
			first_to_last[j] = out.first_to_last(i);
			pos[j] = 0;
			dim_map[j] = i;
			//src
			siters[j] = in._begin(i);
			sfirst_to_last[j] = in.first_to_last(i);

			j++;
		}
	}

	// sorting dim0 <-> dim1 for speed improvement.
	/* IS THIS POSSIBLE??? and how do i recognize to use ITER_1 or ITER_0 ??
	if(j > 1 && out.size(dim_map[1]) > 2 * out.size(dim_map[0])
			&& out.size(dim_map[0]) < 100) {
		std::swap(iters[0], iters[1]);
		std::swap(siters[0], siters[1]);
		std::swap(length[0], length[1]);
		std::swap(first_to_last[0], first_to_last[1]);
		std::swap(sfirst_to_last[0], sfirst_to_last[1]);
		std::swap(dim_map[0], dim_map[1]);
	}*/

	// local variables for the inner dimensions to improve speed.
	O_ITER_1 it0 = iters[0];
	O_ITER_1 it0_end;
	O_ITER_2 it1 = iters[1];
	brd_t first_to_last1 = first_to_last[1];
	brd_t begin_to_end0 = out.begin_to_end(dim_map[0]);
	size_t length1 = length[1];
	size_t pos1 = 0;
	//src
	I_ITER_1 it_src = siters[0];
	I_ITER_2 it_src1 = siters[1];
	sbrd_t sfirst_to_last1 = sfirst_to_last[1];
	sbrd_t sbegin_to_end0 = in.begin_to_end(dim_map[0]);

	// special loop for 1 or 2 dims (after filtering)
	if(j <= 2) {
		it0_end = out._end(dim_map[0]);
		for(; it0 != it0_end; ++it0) {
			F::elem_op(*it0, *it_src);
			++it_src;
		}
		//it0_end = out._end(dim_map[0]);
		while(++pos1 < length1) {
			it0 -= begin_to_end0;
			it0.inc_along_other_dim_at_begin(it1);

			//src
			it_src -= sbegin_to_end0;
			it_src.inc_along_other_dim_at_begin(it_src1);

			for(it0_end = it0 + begin_to_end0; it0 != it0_end; ++it0) {
				F::elem_op(*it0, *it_src);
				++it_src;
			}
			//it0_end.inc_along(it1);
			// TODO: consider using this approach of it0_end
			// as a possible speed improvement in the generic loop. need bench.
			// New Note: after testing:
			// this todo is bad idea.
			// this it_end approach was finally commented out
			// because it is moving out of the iterator valid locations... !!

		}
		return;
	}

	// loop for more than 2 dims.
	do {
		for(it0_end = it0 + begin_to_end0; it0 != it0_end; ++it0) {
			F::elem_op(*it0, *it_src);
			++it_src;
		}
		it0 -= begin_to_end0;
		it_src -= sbegin_to_end0;

		if(++pos1 < length1) {
			it0.inc_along_other_dim_at_begin(it1);
			it_src.inc_along_other_dim_at_begin(it_src1);
		}
		else {
			it0 -= first_to_last1;
			it_src -= sfirst_to_last1;
			pos1 = 0;
			i = 2;
			while(++pos[i] >= length[i]) {
				pos[i] = 0;
				it0 -= first_to_last[i];
				it_src -= sfirst_to_last[i];
				i++;
				if(i >= j) return; // loop is broken here.
			}
			it0.inc_along_other_dim_at_begin(iters[i]);
			it_src.inc_along_other_dim_at_begin(siters[i]);
		}
	} while(1);
}



}; /*namespace loops*/

}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_LOOPS_LOOPS_ND_WITH_END_HPP
