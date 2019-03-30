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

#ifndef IVL_ARRAY_ND_DETAILS_ARRAY_ND_ITERATOR_ND_INTERFACE_HPP
#define IVL_ARRAY_ND_DETAILS_ARRAY_ND_ITERATOR_ND_INTERFACE_HPP

namespace ivl {
namespace array_nd_details {

// an interface for basic_iterator_nd which has random access
template <class C>
class basic_iterator_nd_interface
{
};

template <class T, class OPTS>
class basic_iterator_nd_interface<array_nd<T, OPTS> >
{
private:
	typedef ivl::array_nd<T, OPTS> C;

	typedef array<T, typename types::derive_opts<
		array_nd<T, OPTS> >::type> base_class;

	typedef typename base_class::derived_type derived_type;

	struct not_a_type { };

	typedef typename
		types::t_if<typename base_class::is_writeable,
		typename types::best_iterator<base_class>::type, not_a_type>::type
			iter;

	typedef typename
		types::t_if<typename base_class::is_writeable,
		typename types::best_reverse_iterator<base_class>::type,
			not_a_type>::type reverse_iter;

	typedef typename base_class::const_iterator const_iter;
	typedef typename base_class::const_reverse_iterator const_reverse_iter;

	C& nd() { return static_cast<C&>(*this); }
	const C& nd() const { return static_cast<const C&>(*this); }

protected:
	typedef basic_iterator_nd_interface iter_nd_interface_class;

public:
	typedef ivl::basic_iterator_nd<iter, true> iterator_nd;
	typedef basic_iterator_nd<const_iter, true> const_iterator_nd;
	typedef std::reverse_iterator<iterator_nd> reverse_iterator_nd;
	typedef std::reverse_iterator<const_iterator_nd> const_reverse_iterator_nd;

	typedef ivl::basic_iterator_nd<iter, false> _fast_iterator_nd;
	typedef basic_iterator_nd<const_iter, false> _fast_const_iterator_nd;
	//typedef std::reverse_iterator<iterator_nd, false> reverse_iterator_nd;
	//typedef std::reverse_iterator<const_iterator_nd, false> const_reverse_iterator_nd;

	typedef typename ivl::basic_iterator_nd<const_iter, true>::
		iter_nd_border_walker iter_nd_border_walker;


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
	iterator_nd _begin(size_t d)
		{ return iterator_nd(types::code_word<>(), nd().stride(d), nd().begin()); }

	iterator_nd _begin(size_t d, const iterator_nd& it)
		{ return iterator_nd(nd().stride(d), it); }

	iterator_nd _iter(size_t d, const iter& it)
		{ return iterator_nd(nd().stride(d), it, nd().begin()); }

	template<class S>
	iterator_nd _iter(size_t d, array<size_t, S> ind)
		{ return iterator_nd(nd().stride(d), nd().begin(),
			ivl::sub2ind(nd().stride(), ind)); }

	iterator_nd _next(size_t d, const iterator_nd& it)
		{ return iterator_nd(nd().stride(d), it,
			(d == nd().ndims() -1 ? nd().length() : nd().stride(d + 1))); }

	iterator_nd _end(size_t d)
		{ return iterator_nd(nd().stride(d), nd().begin(),
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))); }

	iterator_nd _last(size_t d)
		{ return iterator_nd(nd().stride(d), nd().begin(),
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))
			- nd().stride(d)); }

	// const iterator

	const_iterator_nd _begin(size_t d) const
		{ return const_iterator_nd(types::code_word<>(), nd().stride(d), nd().begin()); }

	const_iterator_nd _begin(size_t d, const const_iterator_nd& it) const
		{ return const_iterator_nd(nd().stride(d), it); }

	const_iterator_nd _iter(size_t d, const const_iter& it) const
		{ return const_iterator_nd(nd().stride(d), it, nd().begin()); }

	template<class S>
	const_iterator_nd _iter(size_t d, array<size_t, S> ind) const
		{ return const_iterator_nd(nd().stride(d), nd().begin(),
			sub2ind(nd().stride(), ind)); }

	const_iterator_nd _next(size_t d, const const_iterator_nd& it) const
		{ return const_iterator_nd(nd().stride(d), it,
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))); }

	const_iterator_nd _end(size_t d) const
		{ return const_iterator_nd(nd().stride(d), nd().begin(),
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))); }

	const_iterator_nd _last(size_t d) const
		{ return const_iterator_nd(nd().stride(d), nd().begin(),
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))
			- nd().stride(d)); }

	// non-const reverse iterator
#if 0 // disable completely the reverse ones, for now TODO: some time enable
	reverse_iterator_nd _rbegin(size_t d)
		{ return reverse_iterator_nd(types::code_word<>(), iterator_nd(
			nd().stride(d), nd().rbegin().base())); }

	reverse_iterator_nd _rbegin(size_t d, const reverse_iterator_nd& it)
		{ return reverse_iterator_nd(iterator_nd(nd().stride(d),
				it.base().base())); }

	reverse_iterator_nd _riter(size_t d, const reverse_iter& it)
		{ return reverse_iterator_nd(iterator_nd(nd().stride(d), it.base())); }

	// TODO: BIG QUESTION WHETHER IT IS LIKE THIS OR FROM END
	template<class S>
	reverse_iterator_nd _riter(size_t d, array<size_t, S> ind)
		{ return reverse_iterator_nd(iterator_nd(nd().stride(d), nd().begin() +
			sub2ind(nd().stride(), ind))); }

	reverse_iterator_nd _rnext(size_t d, const reverse_iter& it)
		{ return reverse_iterator_nd(iterator_nd(nd().stride(d), (it +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1)))
			.base())); }

	reverse_iterator_nd _rend(size_t d)
		{ return reverse_iterator_nd(iterator_nd(
			nd().stride(d), (nd().rbegin() +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1)))
			.base())); }

	reverse_iterator_nd _rlast(size_t d)
		{ return reverse_iterator_nd(iterator_nd(
			nd().stride(d), (nd().rbegin() +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))
			- nd().stride(d)).base())); }

	// const reverse reverse_iterator

	const_reverse_iterator_nd _rbegin(size_t d) const
		{ return const_reverse_iterator_nd(types::code_word<>(), const_iterator_nd(
			nd().stride(d), nd().rbegin().base())); }

	const_reverse_iterator_nd _rbegin(size_t d, const
		const_reverse_iterator_nd& it) const
		{ return const_reverse_iterator_nd(const_iterator_nd(
			nd().stride(d), it.base().base())); }

	const_reverse_iterator_nd _riter(size_t d, const
		const_reverse_iter& it) const
		{ return const_reverse_iterator_nd(const_iterator_nd(
			nd().stride(d), it.base())); }

	// TODO: BIG QUESTION WHETHER IT IS LIKE THIS OR FROM END
	template<class S>
	const_reverse_iterator_nd _riter(size_t d, array<size_t, S> ind) const
		{ return const_reverse_iterator_nd(const_iterator_nd(
			nd().stride(d), (nd().begin() +
			sub2ind(nd().stride(), ind)).base())); }

	const_reverse_iterator_nd _rnext(size_t d, const
		const_reverse_iter& it) const
		{ return const_reverse_iterator_nd(const_iterator_nd(
			nd().stride(d), (it +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1)))
			.base())); }

	const_reverse_iterator_nd _rend(size_t d) const
		{ return const_reverse_iterator_nd(const_iterator_nd(
			nd().stride(d), (nd().rbegin() +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1)))
			.base())); }

	const_reverse_iterator_nd _rlast(size_t d) const
		{ return const_reverse_iterator_nd(const_iterator_nd(
			nd().stride(d), (nd().rbegin() +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))
			- nd().stride(d)).base())); }
#endif
	// ----------

	// faster non past end capable minimal methods

	// non-const iterator
	_fast_iterator_nd _fast_begin(size_t d)
		{ return _fast_iterator_nd(nd().stride(d), nd().begin()); }

	_fast_iterator_nd _fast_last(size_t d)
		{ return _fast_iterator_nd(nd().stride(d), nd().begin() +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))
			- nd().stride(d)); }

	// const iterator

	_fast_const_iterator_nd _fast_begin(size_t d) const
		{ return _fast_const_iterator_nd(nd().stride(d), nd().begin()); }

	_fast_const_iterator_nd _fast_last(size_t d) const
		{ return _fast_const_iterator_nd(nd().stride(d), nd().begin() +
			(d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1))
			- nd().stride(d)); }


	// ----------

	// iter_nd_border_walker functions
	iter_nd_border_walker first_to_last(size_t d) const
		{ return (d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1)) -
			nd().stride(d); }

	iter_nd_border_walker begin_to_end(size_t d) const
		{ return (d == nd().ndims() - 1 ? nd().length() : nd().stride(d + 1)); }

};

} /* namespace array_nd_details */
} /* namespace ivl */



#endif // IVL_ARRAY_ND_DETAILS_ARRAY_ND_ITERATOR_ND_INTERFACE_HPP
