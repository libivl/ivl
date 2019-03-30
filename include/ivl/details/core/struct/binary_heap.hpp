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

#ifndef IVL_CORE_DETAILS_STRUCT_BINARY_HEAP_HPP
#define IVL_CORE_DETAILS_STRUCT_BINARY_HEAP_HPP

namespace ivl {

//-----------------------------------------------------------------------------

template <
	typename T,
	typename ARRAY = array <T>,
	typename COMP = fun::lt,
	typename SWAP = fun::swap
>
class binary_heap_base
{
protected:

	ARRAY a;
	size_t heap_size;

	SWAP swap_def;
	SWAP* swap;

//-----------------------------------------------------------------------------

	// 1-based
	size_t parent(const size_t n) { return n / 2; }
	size_t left  (const size_t n) { return n * 2; }
	size_t right (const size_t n) { return n * 2 + 1; }

//-----------------------------------------------------------------------------

	// 1-based
	void heapify(const size_t n = 1)
	{
		T& x = a[n - 1];
		size_t l = left(n);
		size_t r = right(n);
		size_t select =
			(l <= heap_size && COMP()(x, a[l - 1])) ?
			l : n;
		if (r <= heap_size && COMP()(a[select - 1], a[r - 1]))
			select = r;
		if (select != n)
		{
			(*swap)(x, a[select - 1]);
			heapify(select);
		}
	}

//-----------------------------------------------------------------------------

	// 1-based
	void build()
	{
		heap_size = a.length();
		for (size_t n = heap_size / 2; n > 0; n--)
			heapify(n);
	}

//-----------------------------------------------------------------------------

	// 1-based
	size_t advance(const size_t k)
	{
		size_t n = k;
		while (n > 1)
		{
			size_t pn = parent(n);
			T& p = a[pn - 1];
			T& x = a[n - 1];
			if (!COMP()(p, x)) break;
			(*swap)(p, x);
			n = pn;
		}
		return n;
	}

//-----------------------------------------------------------------------------

public:

	binary_heap_base() { init(); set_swap(); }
	binary_heap_base(SWAP& s) { init(); set_swap(s); }

	binary_heap_base(const ARRAY& a) { init(a); set_swap(); }
	binary_heap_base(const ARRAY& a, SWAP& s) { init(a); set_swap(s); }

	void init() { a.init(); build(); }
	void init(const ARRAY& a) { this->a = a; build(); }

	void set_swap() { swap = &swap_def; }
	void set_swap(SWAP& s) { swap = &s; }

	bool empty() { return heap_size == 0; }

	size_t size() { return heap_size; }

	size_t length() { return heap_size; }

	void reserve(const size_t len) { a.reserve(len); }

	const T& top()
	{
		CHECK (heap_size != 0, eshape());
		return a[0];
	}

	T pop()
	{
		CHECK (heap_size != 0, eshape());
		T x = a[0];
		(*swap)(a[0], a[heap_size - 1]);
		heap_size--;
		heapify();
		return x;
	}

	// 0-based
	size_t up(size_t n, const T& x)
	{
		CHECK (n < heap_size, erange());
		CHECK (!COMP()(x, a[n]), ecomp());
		a[n] = x;
		return advance(n + 1) - 1;
	}

	// 0-based
	size_t push(const T& x)
	{
		if (heap_size == a.length())
			a.push_back(x);
		else
			a[heap_size] = x;
		return advance(++heap_size) - 1;
	}

};

//-----------------------------------------------------------------------------

template <
	typename T,
	typename ARRAY = array <T>,
	typename COMP = fun::lt,
	typename SWAP = fun::swap
>
class binary_heap : public binary_heap_base <T, ARRAY, COMP, SWAP>
{
	typedef binary_heap_base <T, ARRAY, COMP, SWAP> base;
	using base::a;

public:

	binary_heap() : base() { }
	binary_heap(SWAP& s) : base(s) { }

	binary_heap(const ARRAY& a) : base(a) { }
	binary_heap(const ARRAY& a, SWAP& s) : base(a, s) { }

};

//-----------------------------------------------------------------------------

template <typename T, typename ARRAY, typename COMP, typename SWAP>
class binary_heap <T, ARRAY&, COMP, SWAP> :
	public binary_heap_base <T, ARRAY&, COMP, SWAP>
{
	typedef binary_heap_base <T, ARRAY&, COMP, SWAP> base;
	using base::a;
	using base::heap_size;
	using base::swap;
	using base::heapify;
	using base::build;

public:

	binary_heap(ARRAY& a) : base(a) { }
	binary_heap(ARRAY& a, SWAP& s) : base(a, s) { }

	void sort()
	{
		if (heap_size == 0)
			return;
		for (size_t n = heap_size - 1; n != 0; n--)
		{
			(*swap)(a[0], a[n]);
			heap_size--;
			heapify();
		}
	}

};

//--------------------------------------------------------------------------

}  // namespace ivl

#endif // IVL_CORE_DETAILS_STRUCT_BINARY_HEAP_HPP