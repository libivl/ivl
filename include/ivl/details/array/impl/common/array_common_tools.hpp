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

#ifndef IVL_ARRAY_DETAILS_COMMON_ARRAY_COMMON_TOOLS_HPP
#define IVL_ARRAY_DETAILS_COMMON_ARRAY_COMMON_TOOLS_HPP

namespace ivl {
namespace array_details {

/*
classes for unary_element_functions that add 1 or subtract 1,
needed for the result of the operator++(int), and operator--(int).
*/
template<class T, class J>
struct plus1_class
{
	typedef types::number<5> cost;
	static inline T elem_op(const J& elem1) { return elem1 + 1; };
};

template<class T, class J>
struct minus1_class
{
	typedef types::number<5> cost;
	static inline T elem_op(const J& elem1) { return elem1 - 1; };
};

/*
initializer class for the std::vector
*/
template <bool HAS_RANDOM_ACCESS>
struct vector_initializer
{
};

template <>
struct vector_initializer<true>
{
	template <class T, class AR>
	static void operate(std::vector<T>& v, const AR& a)
	{
		v.assign(a.begin(), a.end());
	}
};

template <>
struct vector_initializer<false>
{
	template <class T, class IT>
	static void loop(std::vector<T>& v, IT first, IT last)
	{
		while(first != last) {
			v.push_back(*first);
			++first;
		}
	}

	template <class T, class AR>
	static void operate(std::vector<T>& v, const AR& a)
	{
		v.reserve(a.length());
		// the reason?
		// I was using vector<T>(begin(), end()) constructor but:
		// In the case of non-random-access arrays, if I use the vector way,
		// one loop will be made to determine the source array length for the
		// vector resize, and one second loop to copy the elements.
		// however the length is probably known at O(1) time with a.length().
		// drawbacks: not that I know of, because seq_access is always faster
		// or equal to index based random access and, normally, faster than
		// seq_nd access. A small possibility that seq_nd access would be
		// faster and '*this' is an array_nd, and therefore loop_on after
		// vector resize would be faster than calling the base constructor
		// of the one dimensional array (in the array_nd level) seems too much
		// but could be investigated. Cause the flaw of this implementation
		// I'm using is that the preferred seq_nd access tags are ignored.
		// Also! if multithreading is used it wont benefit from here!!
		// consider elem-functions as well! So:
		// TODO: could fix this to use something clever.
		// take care because the solution:
		//
		// vector<T>.resize()
		// wrap vector with iter_array x;
		// loop_on(x, a);
		//
		// has a cpu leak on resize cause resize uses default value that is
		// T()
		// so it will initialize all elements!
		// investigate this as well! (and see if it is true).
		//
		// another long solution would be to write a custom loop
		// (or a few custom loops, for nd etc), for the array situation
		//
		// or even a "deceiptful" vector iterator that uses push back on
		// the vector. bah.......
		//
		// take examples always using weird situations like array<array<T> >
		//
		//
		//
		loop(v, a.begin(), a.end());
	}
};

} /* namespace array_details */
} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_COMMON_ARRAY_COMMON_TOOLS_HPP
