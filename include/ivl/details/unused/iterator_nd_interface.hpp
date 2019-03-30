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

#ifndef ARRAY_ND_DETAILS_ARRAY_ND_ITERATOR_ND_INTERFACE_HPP
#define ARRAY_ND_DETAILS_ARRAY_ND_ITERATOR_ND_INTERFACE_HPP

namespace ivl {

namespace array_nd_details {

template <class T, class DATA, class DERIVED_INFO>
class basic_iterator_nd_interface
{
private:
	typedef array_nd<T, DATA, DERIVED_INFO> C;
	typedef typename types::derive<C>::type derived_type;
	typedef array<T, DATA, derived_type> base_class;

	typedef typename base_class::iterator iterator;
	typedef typename base_class::const_iterator const_iterator;
	typedef typename base_class::reverse_iterator reverse_iterator;
	typedef typename base_class::const_reverse_iterator const_reverse_iterator;

	C& nd() { return static_cast<C&>(*this); }
	const C& nd() const { return static_cast<const C&>(*this); }

public:
	typedef data::basic_iterator_nd<iterator> iterator_nd;
	typedef data::basic_iterator_nd<const_iterator> const_iterator_nd;
	typedef std::reverse_iterator<iterator_nd> reverse_iterator_nd;
	typedef std::reverse_iterator<const_iterator_nd> const_reverse_iterator_nd;

	size_t begin_pos(size_t d, size_t pos)
	{
		size_t mod = pos % nd().stride(d);
		if(d == nd().ndim() - 1) return mod;
		return pos - pos % nd().stride(d + 1) + mod;
	}

	size_t end_pos(size_t d, size_t pos)
	{
		size_t mod = pos % nd().stride(d);
		if(d == nd().ndim() - 1) return mod + nd().length();
		return pos - pos % nd().stride(d + 1) + mod +
			nd().stride(d + 1);
	}

	// non-const iterator

	iterator_nd iter(size_t d)
		{ return iterator_nd(nd().stride(d), nd().begin()); }

	iterator_nd iter(size_t d, size_t pos)
		{ return iterator_nd(nd().stride(d), nd().begin() + pos); }

	iterator_nd iter(size_t d, const size_array& idx)
		{ return iterator_nd(nd().stride(d), nd().begin() + nd().sub2ind(nd(), idx) ); }

	iterator_nd iter(size_t d, const iterator_nd& it)
		{ return iterator_nd(nd().stride(d), it); }

	iterator_nd iter(size_t d, const iterator& it, int offset)
	{
		size_t s = nd().stride(d);
		return iterator_nd(s, it + offset * s);
	}

	iterator_nd begin(size_t d)
		{ return iterator_nd(nd().stride(d), nd().begin()); }

	iterator_nd begin(size_t d, size_t pos)
		{ return iterator_nd(nd().stride(d), nd().begin() + begin_pos(d, pos)); }

	iterator_nd begin(size_t d, const size_array& idx)
		{ return iterator_nd(nd().stride(d), nd().begin() + begin_pos(d, sub2ind(nd(), idx) )); }

	iterator_nd begin(size_t d, const iterator& it)
		{ return iterator_nd(nd().stride(d), nd().begin() + begin_pos(d, it - nd().begin())); }

	iterator_nd begin(size_t d, const iterator& it, int offset)
	{
		size_t s = nd().stride(d);
		return iterator_nd(s, nd().begin() + begin_pos(d, it - nd.begin() + offset * s));
	}

	iterator_nd end(size_t d, size_t pos)
		{ return iterator_nd(nd().stride(d), nd().begin() + end_pos(d, pos)); }

	iterator_nd end(size_t d, const size_array& idx)
		{ return iterator_nd(nd().stride(d), nd().begin() + end_pos(d, sub2ind(nd(), idx) )); }

	iterator_nd end(size_t d, const iterator& it)
		{ return iterator_nd(nd().stride(d), nd().begin() + end_pos(d, it - nd().begin())); }

	iterator_nd end(size_t d, const iterator& it, int offset)
	{
		size_t s = nd().stride(d);
		return iterator_nd(s, nd().begin() + end_pos(d, it - nd.begin() + offset * s));
	}

	// const iterator

	const_iterator_nd iter(size_t d) const
		{ return const_iterator_nd(nd().stride(d), nd().begin()); }

	const_iterator_nd iter(size_t d, size_t pos) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + pos); }

	const_iterator_nd iter(size_t d, const size_array& idx) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + nd().sub2ind(nd(), idx) ); }

	const_iterator_nd iter(size_t d, const const_iterator_nd& it) const
		{ return const_iterator_nd(nd().stride(d), it); }

	const_iterator_nd iter(size_t d, const const_iterator& it, int offset) const
	{
		size_t s = nd().stride(d);
		return const_iterator_nd(s, it + offset * s);
	}

	const_iterator_nd begin(size_t d) const
		{ return const_iterator_nd(nd().stride(d), nd().begin()); }

	const_iterator_nd begin(size_t d, size_t pos) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + begin_pos(d, pos)); }

	const_iterator_nd begin(size_t d, const size_array& idx) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + begin_pos(d, sub2ind(nd(), idx) )); }

	const_iterator_nd begin(size_t d, const const_iterator& it) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + begin_pos(d, it - nd().begin())); }

	const_iterator_nd begin(size_t d, const const_iterator& it, int offset) const
	{
		size_t s = nd().stride(d);
		return const_iterator_nd(s, nd().begin() + begin_pos(d, it - nd.begin() + offset * s));
	}

	const_iterator_nd end(size_t d, size_t pos) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + end_pos(d, pos)); }

	const_iterator_nd end(size_t d, const size_array& idx) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + end_pos(d, sub2ind(nd(), idx) )); }

	const_iterator_nd end(size_t d, const const_iterator& it) const
		{ return const_iterator_nd(nd().stride(d), nd().begin() + end_pos(d, it - nd().begin())); }

	const_iterator_nd end(size_t d, const const_iterator& it, int offset) const
	{
		size_t s = nd().stride(d);
		return const_iterator_nd(s, nd().begin() + end_pos(d, it - nd().begin() + offset * s));
	}

	// non-const reverse iterator

	reverse_iterator_nd riter(size_t d)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin()); }

	reverse_iterator_nd riter(size_t d, size_t pos)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + pos); }

	reverse_iterator_nd riter(size_t d, const size_array& idx)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + nd().sub2ind(nd(), idx) ); }

	reverse_iterator_nd riter(size_t d, const reverse_iterator_nd& it)
		{ return reverse_iterator_nd(nd().stride(d), it); }

	reverse_iterator_nd riter(size_t d, const reverse_iterator& it, int offset)
	{
		size_t s = nd().stride(d);
		return reverse_iterator_nd(s, it + offset * s);
	}

	reverse_iterator_nd rbegin(size_t d)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin()); }

	reverse_iterator_nd rbegin(size_t d, size_t pos)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + begin_pos(d, pos)); }

	reverse_iterator_nd rbegin(size_t d, const size_array& idx)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + begin_pos(d, sub2ind(nd(), idx) )); }

	reverse_iterator_nd rbegin(size_t d, const reverse_iterator& it)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + begin_pos(d, it - nd.rbegin())); }

	reverse_iterator_nd rbegin(size_t d, const reverse_iterator& it, int offset)
	{
		size_t s = nd().stride(d);
		return reverse_iterator_nd(s, nd().rbegin() + begin_pos(d, it - nd().rbegin() + offset * s));
	}

	reverse_iterator_nd rend(size_t d, size_t pos)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + end_pos(d, pos)); }

	reverse_iterator_nd rend(size_t d, const size_array& idx)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + end_pos(d, sub2ind(nd(), idx) )); }

	reverse_iterator_nd rend(size_t d, const reverse_iterator& it)
		{ return reverse_iterator_nd(nd().stride(d), nd().rbegin() + end_pos(d, it - nd().rbegin())); }

	reverse_iterator_nd rend(size_t d, const reverse_iterator& it, int offset)
	{
		size_t s = nd().stride(d);
		return reverse_iterator_nd(s, nd().rbegin() + end_pos(d, it - nd().rbegin() + offset * s));
	}

	// const reverse reverse_iterator

	const_reverse_iterator_nd riter(size_t d) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin()); }

	const_reverse_iterator_nd riter(size_t d, size_t pos) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + pos); }

	const_reverse_iterator_nd riter(size_t d, const size_array& idx) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + nd().sub2ind(nd(), idx) ); }

	const_reverse_iterator_nd riter(size_t d, const const_reverse_iterator_nd& it) const
		{ return const_reverse_iterator_nd(nd().stride(d), it); }

	const_reverse_iterator_nd riter(size_t d, const const_reverse_iterator& it, int offset) const
	{
		size_t s = nd().stride(d);
		return const_reverse_iterator_nd(s, it + offset * s);
	}

	const_reverse_iterator_nd rbegin(size_t d) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin()); }

	const_reverse_iterator_nd rbegin(size_t d, size_t pos) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + begin_pos(d, pos)); }

	const_reverse_iterator_nd rbegin(size_t d, const size_array& idx) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + begin_pos(d, sub2ind(nd(), idx) )); }

	const_reverse_iterator_nd rbegin(size_t d, const const_reverse_iterator& it) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + begin_pos(d, it - nd().rbegin())); }

	const_reverse_iterator_nd rbegin(size_t d, const const_reverse_iterator& it, int offset) const
	{
		size_t s = nd().stride(d);
		return const_reverse_iterator_nd(s, nd().rbegin() + begin_pos(d, it - nd().rbegin() + offset * s));
	}

	const_reverse_iterator_nd rend(size_t d, size_t pos) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + end_pos(d, pos)); }

	const_reverse_iterator_nd rend(size_t d, const size_array& idx) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + end_pos(d, sub2ind(nd(), idx) )); }

	const_reverse_iterator_nd rend(size_t d, const const_reverse_iterator& it) const
		{ return const_reverse_iterator_nd(nd().stride(d), nd().rbegin() + end_pos(d, it - nd().rbegin())); }

	const_reverse_iterator_nd rend(size_t d, const const_reverse_iterator& it, int offset) const
	{
		size_t s = nd().stride(d);
		return const_reverse_iterator_nd(s, nd().rbegin() + end_pos(d, it - nd().rbegin() + offset * s));
	}

};

}; /* namespace array_nd_details */

}; /* namespace ivl */



#endif //ARRAY_ND_DETAILS_ARRAY_ND_ITERATOR_ND_INTERFACE_HPP
