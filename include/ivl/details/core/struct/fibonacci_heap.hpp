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

#ifndef IVL_CORE_DETAILS_STRUCT_FIBONACCI_HEAP_HPP
#define IVL_CORE_DETAILS_STRUCT_FIBONACCI_HEAP_HPP

namespace ivl {

//-----------------------------------------------------------------------------

template <
	typename T,
	typename COMP = fun::lt
>
class fibonacci_heap
{
	typedef size_t ptr;

	size_t null() { return size_t(-1); }

	bool comp(ptr x, ptr y) { return COMP()(a[x].key, a[y].key); }

//-----------------------------------------------------------------------------

	struct list_node
	{
		ptr prev;
		ptr next;
	};

//-----------------------------------------------------------------------------

	bool alone(ptr x) { return a[x].next == x; }

	void list_link(ptr x, ptr y)  // x, y are not null
	{
		a[x].next = y;
		a[y].prev = x;
	}

	void list_insert(ptr& h, ptr x)  // x is not null
	{
		if (h == null())
			a[x].prev = a[x].next = x;
		else
		{
			ptr t = a[h].prev;
			list_link(x, h);
			list_link(t, x);
		}
		h = x;
	}

	void list_remove(ptr& h, ptr x)  // h, x are not null
	{
		if (alone(x))
		{
			h = null();
			return;
		}
		if (h == x)
			h = a[x].next;
		list_link(a[x].prev, a[x].next);
	}

//-----------------------------------------------------------------------------

	struct node : public list_node
	{
		T key;
		ptr parent;
		ptr child;
		size_t degree;
		bool mark;
		node(const T& key) : key(key) { }
	};

//-----------------------------------------------------------------------------

	void insert(ptr x)  // x is not null
	{
		a[x].parent = a[x].child = null();
		a[x].degree = 0;
		a[x].mark = false;
		root_insert(x);
		heap_size++;
	}

	ptr extract()  // heap is not null
	{
		ptr z = first;
		ptr y = a[z].child;
		ptr last = y == null() ? null() : a[y].prev;
		while (y != null())
		{
			ptr x = y;
			y = y == last ? null() : a[y].next;
			list_insert(root, x);
			a[x].parent = null();
		}
		list_remove(root, z);
		if (alone(z))
			first = root = null();
		else
		{
			first = a[z].next;
			consolidate();
		}
		heap_size--;
		return z;
	}

//-----------------------------------------------------------------------------

	double golden() { return (1 + sqrt(5.)) / 2; }

	void consolidate()
	{
		// TODO: remove math::, (double)
		size_t D = 1 + math::log_base(golden(), (double)heap_size);
		array <ptr> A(D, null());
		ptr z = root;
		ptr last = z == null() ? null() : a[z].prev;
		while (z != null())
		{
			ptr y = z;
			z = z == last ? null() : a[z].next;
			size_t d = a[y].degree;
			while (A[d] != null())
			{
				ptr x = A[d];
				if (comp(x, y))
					std::swap(x, y);
				link(x, y);
				A[d++] = null();
			}
			A[d] = y;
		}
		first = root = null();
		for (size_t d = 0; d < D; d++)
			if (A[d] != null())
				root_insert(A[d]);
	}

//-----------------------------------------------------------------------------

	void advance(ptr x)  // x is not null
	{
		ptr y = a[x].parent;
		if (y != null() && comp(x, y))
			cascade_cut(x, y);
		if (comp(x, first))
			first = x;
	}

//-----------------------------------------------------------------------------

	void link(ptr x, ptr y)  // x, y are not null
	{
		list_remove(root, x);
		list_insert(a[y].child, x);
		a[y].degree++;
		a[x].parent = y;
		a[x].mark = false;
	}

	void cut(ptr x, ptr y)  // x, y are not null; x is a child of y
	{
		list_remove(a[y].child, x);
		list_insert(root, x);
		a[y].degree--;
		a[x].parent = null();
		a[x].mark = false;
	}

	void cascade(ptr y)  // y is not null
	{
		ptr z = a[y].parent;
		if (z == null())
			return;
		if (!a[y].mark)
			a[y].mark = true;
		else
			cascade_cut(y, z);
	}

	void cascade_cut(ptr x, ptr y)  // x, y are not null; x is a child of y
	{
		cut(x, y);
		cascade(y);
	}

	void root_insert(ptr x)  // x is not null
	{
		list_insert(root, x);
		if (first == null() || comp(x, first))
			first = x;
	}

//-----------------------------------------------------------------------------

protected:

	array <node> a;
	size_t heap_size;
	ptr root;
	ptr first;

//-----------------------------------------------------------------------------

public:

	fibonacci_heap() { init(); }

	void init() { a.init(); heap_size = 0; root = first = null(); }

	void init(const array <T>& a)
	{
		init();
		for (size_t n = 0; n < a.length(); n++)
			push(a[n]);
	}

	bool empty() { return heap_size == 0; }

	size_t size() { return heap_size; }

	size_t length() { return heap_size; }

	void reserve(const size_t len) { a.reserve(len); }

	const T& top()
	{
		CHECK (heap_size != 0, eshape());
		return a[first].key;
	}

	T pop()
	{
		CHECK (heap_size != 0, eshape());
		return a[extract()].key;
	}

	size_t up(size_t x, const T& key)
	{
		CHECK (x < a.length(), erange());
		CHECK (!COMP()(key, a[x].key), ecomp());
		a[x].key = key;
		advance(x);
		return x;
	}

	size_t push(const T& key)
	{
		node n(key);
		a.push_back(n);
		insert(a.length() - 1);
		return a.length() - 1;
	}

};

//--------------------------------------------------------------------------

}  // namespace ivl

#endif // IVL_CORE_DETAILS_STRUCT_FIBONACCI_HEAP_HPP
