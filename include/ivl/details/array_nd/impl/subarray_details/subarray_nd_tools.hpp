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

#ifndef IVL_ARRAY_ND_SPECIALIZATION_DETAILS_SUBARRAY_ND_TOOLS_HPP
#define IVL_ARRAY_ND_SPECIALIZATION_DETAILS_SUBARRAY_ND_TOOLS_HPP

namespace ivl {

namespace array_nd_details {

template <class REF_ITER_IS_ND>
struct subarray_tools
{
};

template <>
struct subarray_tools<types::t_true>
{
	template <class IT, class SIT>
	static inline void inc_along(IT& it, const SIT& sit)
	{
		it.ptr.move_along(sit.ptr, sit.step);
	}

	template <class IT, class SIT>
	static inline void dec_along(IT& it, const SIT& sit)
	{
		it.ptr.move_along(sit.ptr, sit.step);
	}

	template <class IT, class SIT>
	static inline void move_along(IT& it, const SIT& sit, ptrdiff_t dist)
	{
		it.ptr.move_along(sit.ptr, sit.step * dist);
	}

	template <class PTR, class S_PTR>
	static inline void move_ref_along(PTR& it, const S_PTR& sit, ptrdiff_t step, ptrdiff_t dist)
	{
		it.move_along(sit, step * dist);
	}
	template <class PTR, class S_PTR>
	static inline void move_ref_along(ptrdiff_t& np, PTR& it, const S_PTR& sit, ptrdiff_t step, ptrdiff_t dist)
	{
		it.move_along(sit, step * dist);
	}
	template <class PTR>
	static inline void add_to_ref(ptrdiff_t& np, PTR& it, ptrdiff_t dist)
	{
		it += dist;
	}
	template <class S1, class S2>
	static inline ptrdiff_t wrapper_creation_index_diff(const S1& ir1, const S2& ir2) { return 0; }
	template <class S1, class S2>
	static inline S1& wrapper_creation_index_base(S1& ir1, S2& ir2) { return ir1; }

	template <class IT>
	struct iter_nd_border_walker
	{
		ptrdiff_t step;
		ptrdiff_t len;
		ptrdiff_t cur_pos;
		IT it;

		iter_nd_border_walker() {}
		iter_nd_border_walker(ptrdiff_t x) : len(0), cur_pos(-1), step(0) { }
		template<class SIT>
		iter_nd_border_walker(const SIT& it,
			size_t step, size_t len = 0, ptrdiff_t cur_pos = -1
			) : step(step), len(len), cur_pos(cur_pos), it(it) { }
	};

};

template <>
struct subarray_tools<types::t_false>
{
	template <class IT, class SIT>
	static inline void inc_along(IT& it, const SIT& sit)
	{
		it.ptr += sit.step;
	}

	template <class IT, class SIT>
	static inline void dec_along(IT& it, const SIT& sit)
	{
		it.ptr -= sit.step;
	}

	template <class IT, class SIT>
	static inline void move_along(IT& it, const SIT& sit, ptrdiff_t dist)
	{
		it.ptr += sit.step * dist;
	}

	template <class PTR, class S_PTR>
	static inline void move_ref_along(PTR& it, const S_PTR& sit, ptrdiff_t step,
								ptrdiff_t dist)
	{
		it += step * dist;
	}
	template <class PTR, class S_PTR>
	static inline void move_ref_along(ptrdiff_t& np, PTR& it, const S_PTR& sit, ptrdiff_t step,
								ptrdiff_t dist)
	{
		np += step * dist;
	}
	template <class PTR>
	static inline void add_to_ref(ptrdiff_t& np, PTR& it, ptrdiff_t dist)
	{
		np += dist;
	}
	template <class S1, class S2>
	static inline ptrdiff_t wrapper_creation_index_diff(const S1& ir1, const S2& ir2) { return ir1 - ir2; }
	template <class S1, class S2>
	static inline S1& wrapper_creation_index_base(S1& ir1, S2& ir2) { return ir2; }

	template <class IT>
	struct iter_nd_border_walker
	{
		ptrdiff_t len;
		ptrdiff_t cur_pos;
		ptrdiff_t step;
		types::code_word<> it;

		iter_nd_border_walker() {}
		iter_nd_border_walker(ptrdiff_t x) : len(0), cur_pos(-1), step(0) { }
		template<class SIT>
		iter_nd_border_walker(const SIT& it,
			size_t step, size_t len = 0, ptrdiff_t cur_pos = -1
			) : len(len), cur_pos(cur_pos), step(step) { }
	};

};

struct subarray_common_tools
{
	struct add_op
	{
		template<class X, class Y>
		static inline void operate(X& a, const Y& b) { a += b; }
	};
	struct sub_op
	{
		template<class X, class Y>
		static inline void operate(X& a, const Y& b) { a -= b; }
	};

	template<class OP, class IT>
	static inline void inc_along(IT& ir, const IT& d,
		const ptrdiff_t* diff, size_t pos, size_t str)
	{
		if(diff)
			ir.inc_along(d, diff[pos]);
		else
			ir.inc_along(d, str);
	}

	template<class OP, class IT>
	static inline void dec_along(IT& ir, const IT& d,
		const ptrdiff_t* diff, size_t pos, size_t str)
	{
		if(diff)
			ir.dec_along(d, diff[pos]);
		else
			ir.dec_along(d, str);
	}

	// TODO:: possible speed improvement is:
	// do not use pos0 at all in the array specialized case, and
	// use a ptrdiff_t + length as barrier.
	// make also a specialized function that controls the pos0++ and
	// the ending condition.
	// However, when copying from an iterator<2> to an iterator<0>
	// it will be needed to generate pos0 from diff0 - start_diff0_border
	// and to reset diff0 = start_diff0_border, and
	// when copying from an iterator<0> to an iterator<2> do:
	// diff0 += pos

	template<int SP = 0> // generic case operator. slower
	struct inner_dim_adder
	{
		template<class OP, class IT>
		static inline void operate(IT& ir, const ptrdiff_t* diff0,
			size_t pos, size_t str)
		{
			if(diff0)
				OP::operate(ir, diff0[pos]);
			else
				OP::operate(ir, str);
		}
	};

	// iterator_nd type
	enum sub_type
	{
		step_it = 0,
		array_it = 1
	};

	// get iterator_nd type from index_array indtype
	static inline sub_type type_from_indtype(ivl::index_array::
		index_array_type y)
	{
		return (y == ivl::index_array::ARRAY ? array_it : step_it);
	}

};

template<>
struct subarray_common_tools::inner_dim_adder<1> // special case 1: index 0 is all or range.
{
	template<class OP, class IT>
	static inline void operate(IT& ir, const ptrdiff_t* diff0,
		size_t pos, size_t str)
	{
		OP::operate(ir, str);
	}
};
template<>
struct subarray_common_tools::inner_dim_adder<2> // special case 2: index 0 is array.
{
	template<class OP, class IT>
	static inline void operate(IT& ir, const ptrdiff_t* diff0,
		size_t pos, size_t str)
	{
		OP::operate(ir, diff0[pos]);
	}
};

}; /*namespace array_nd_details*/

}; /*namespace ivl*/


#endif // IVL_ARRAY_ND_SPECIALIZATION_DETAILS_SUBARRAY_ND_TOOLS_HPP
