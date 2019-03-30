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

#ifndef IVL_ARRAY_SPECIALIZATION_DETAILS_SUBARRAY_TOOLS_HPP
#define IVL_ARRAY_SPECIALIZATION_DETAILS_SUBARRAY_TOOLS_HPP

namespace ivl {

namespace array_details {

template <class REF_ITER_IS_ND, class IT>
struct subarray_tools
{
};

template <class IT>
struct subarray_tools<types::t_true, IT>
{
	template <class A, class IDX>
	static IT begin(A& a, size_t dim, const IDX& i)
			{ return a._iter(dim, i); }

	template <class A>
	static IT rend_base(A& a, size_t dim) { return a._rend(dim).base(); }

	template <class A>
	static IT end(A& a, size_t dim) { return a._end(dim); }

	template <class A>
	static IT last(A& a, size_t dim) { return a._last(dim); }

	template <class A>
	static IT //todo names..
		iter(A& a, size_t dim, const IT& x)
			{ return a._begin(dim, x); }

	template <class A>
	static inline size_t stride(A& a, size_t dim) { return 1; }

};

template <class IT>
struct subarray_tools<types::t_false, IT>
{
	template <class A, class IDX>
	static IT begin(A& a, size_t dim, const IDX& i)
			{ return a.begin() + sub2ind(a, i); }

	template <class A>
	static IT rend_base(A& a, size_t dim) { return a.rend().base(); }

	template <class A>
	static IT end(A& a, size_t dim) { return a.end(); }

	template <class A>
	static IT iter(A& a, size_t dim, const IT& x) { return x; }

	template <class A>
	static inline size_t stride(A& a, size_t dim) { return a.stride(dim); }

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

	template<class IT>
	static inline void inc_along(IT& ir, const IT& d,
		const ptrdiff_t* diff, size_t pos, size_t str)
	{
		if(diff)
			ir.move_along(d, diff[pos]);
		else
			ir.move_along(d, str);
	}

	template<class IT>
	static inline void dec_along(IT& ir, const IT& d,
		const ptrdiff_t* diff, size_t pos, size_t str)
	{
		if(diff)
			ir.move_along(d, -diff[pos]);
		else
			ir.move_along(d, -str);
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

}; /*namespace array_details*/

}; /*namespace ivl*/


#endif // IVL_ARRAY_SPECIALIZATION_DETAILS_SUBARRAY_TOOLS_HPP
