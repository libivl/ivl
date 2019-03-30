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

#ifndef IVL_CORE_DETAILS_TOOL_LITTLE_ARRAYLING_HPP
#define IVL_CORE_DETAILS_TOOL_LITTLE_ARRAYLING_HPP

/*
* Description:
*
* ivl contains a type array<T, data::little<N> > with pre-allocated memory
* for N cells in the struct itself, as a normal C array.
* this array can have any variable length, however if the length is less
* or equal to N, the local storage is used avoiding the malloc overhead.
*
* This kind of array is useful also in some low-level parts of the
* implementation of ivl, like the subarray iterator.
*
* In order to avoid a bad design we want to avoid using the actual
* array struct in a such low-level part of the library. This
* would yield complicated and unjustified #includes and forward
* declarations. So we rewrite a very simple array called little_arrayling.
* - it is named little after the data type that uses N cells.
* This class implements only the very basic functionality that is needed.
*
* The reason this class is used over the stl vector is the possible
* speed-up that it offers when used to store small data.
*
*/

namespace ivl {
namespace internal {

template <class T, int N = 4>
class little_arrayling
{
private:
	size_t len;
	T* ptr;
	T data[N];

	void _setsize(size_t x) { if(x > N) ptr = new T[x]; len = x; }
	void _resetsize(size_t x) {
		if(len == x) return;
		if(len > N) delete[] ptr; ptr = data; _setsize(x);
	}

	template<class A>
	void _copy_from(const A& ar)
	{
		T* dst = ptr;
		for(typename A::const_iterator it = ar.begin(); it != ar.end(); it++)
			*dst++ = *it++;
	}
	void _copy_from_ptr(const T* p, const T* p_end)
	{
		T* dst = ptr;
		while(p != p_end) *(dst++) = *(p++);
	}

public:
	little_arrayling() { ptr = data; len = 0; }; // should call setsize

	little_arrayling(size_t sz) { ptr = data; _setsize(sz); };

	little_arrayling(const little_arrayling& ar)
		{ ptr = data; _setsize(ar.len); _copy_from_ptr(ar.ptr, ar.ptr + len); }

	template<class A>
	little_arrayling(A& ar)
		{ ptr = data; _setsize(ar.length()); _copy_from(ar); }

	~little_arrayling() { if(len > N) delete[] ptr; }

	little_arrayling& operator=(const little_arrayling& o)
		{ _resetsize(o.len); _copy_from_ptr(o.ptr, o.ptr + len); return *this; }

	void setsize(size_t sz) { _setsize(sz); } // should only be called once

	template<class A>
	void copy_from(const A& ar) { _copy_from(ar); }

	T& operator[](size_t x) { return ptr[x]; }

	const T& operator[](size_t x) const { return ptr[x]; }

	size_t length() const { return len; }

	T* c_ptr() { return ptr; }

	const T* c_ptr() const { return ptr; }
};

} /* namespace internal */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TOOL_LITTLE_ARRAYLING_HPP
