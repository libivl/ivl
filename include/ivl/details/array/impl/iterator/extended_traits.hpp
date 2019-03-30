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

#ifndef IVL_ARRAY_DETAILS_ITERATOR_EXTENDED_TRAITS_HPP
#define IVL_ARRAY_DETAILS_ITERATOR_EXTENDED_TRAITS_HPP

namespace ivl {
namespace data {

namespace data_details {

template <class IT>
struct is_vector_iterator
{
	typedef typename std::iterator_traits<IT>::value_type v;
	typedef typename types::t_or<
		types::t_eq<IT, typename std::vector<v>::iterator>,
		types::t_eq<IT, typename std::vector<v>::const_iterator> >::type type;
};

template <class IT, class HAS_BORDER_WALKER>
struct border_walker_details
{
	typedef ptrdiff_t iter_border_walker;
	static inline iter_border_walker from(const IT& a, const IT& b)
	{
		return b - a;
	}
};

template <class IT>
struct border_walker_details<IT, types::t_true>
{
	typedef typename IT::iter_border_walker iter_border_walker;
	static inline iter_border_walker from(const IT& a, const IT& b)
	{
		return iter_border_walker(a, b);
	}
};

template <class IT, class HAS_BORDER_WALKER>
struct nd_border_walker_details
{
	typedef ptrdiff_t iter_nd_border_walker;
	static inline iter_nd_border_walker from(const IT& a, const IT& b)
	{
		return b - a;
	}
};

template <class IT>
struct nd_border_walker_details<IT, types::t_true>
{
	typedef typename IT::iter_nd_border_walker iter_nd_border_walker;
	static inline iter_nd_border_walker from(const IT& a, const IT& b)
	{
		return iter_nd_border_walker(a, b);
	}
};

} /* namespace data_details */

template <class IT>
struct iterator_extended_traits_bw
{
	typedef typename types::bare_type<IT>::type it;

	// border walker types

	// iterator nd's shouldn't have the border_walker tag
	// no_border_walker_iterator_identifier is a tag to explicitly
	// disable the inherited border walker for that reason.
	typedef typename
		types::t_and_3<
			types::t_not<
				types::is_base<types::no_border_walker_iterator_identifier, it>
			>,
			types::t_not<
				types::is_base<types::nd_border_walker_iterator_identifier, it>
			>,
			types::is_base<types::border_walker_iterator_identifier, it>
		>::type has_border_walker;

	typedef typename
		data_details::border_walker_details<it, has_border_walker>
			::iter_border_walker iter_border_walker;

	static inline
	iter_border_walker get_iter_border_walker(const it& a, const it& b)
	{
		return data_details::border_walker_details<it, has_border_walker>
			::from(a, b);
	}

	typedef typename
		types::is_base<types::nd_border_walker_iterator_identifier, it>
			::type has_nd_border_walker;

	typedef typename
		data_details::nd_border_walker_details<it, has_nd_border_walker>
			::iter_nd_border_walker iter_nd_border_walker;

	static inline
	iter_nd_border_walker get_iter_nd_border_walker(const it& a, const it& b)
	{
		return data_details::nd_border_walker_details<it, has_nd_border_walker>
			::from(a, b);
	}
};

template <class IT>
struct iterator_extended_traits
: public iterator_extended_traits_bw<IT>
{
	typedef typename types::bare_type<IT>::type it;
	typedef typename types::t_or_3<
		data_details::is_vector_iterator<it>,
		types::is_base<types::pointer_based_iterator_identifier, it>,
		types::is_base<types::pointer_range_based_iterator_identifier, it> >
			::type is_pointer_based;

	// pointer_capable is the same as pointer_based with a small difference:
	// we are not always capable to get pointers from vector iterators, since
	// some times they are not dereferencable.
	// pointer_capable means that you can always do &(*it) to get a pointer.
	typedef typename types::t_or<
		types::is_base<types::pointer_based_iterator_identifier, it>,
		types::is_base<types::pointer_range_based_iterator_identifier, it> >
			::type is_pointer_capable;

	typedef typename
		types::is_base<types::pointer_range_based_iterator_identifier, it>
			::type is_pointer_range_based;

	typedef typename
		types::t_and<is_pointer_based, types::t_not<is_pointer_range_based> >
			::type is_pointer_based_and_contiguous;

	typedef typename
		types::is_base<types::ivl_array_reference_based_iterator_identifier, it>
			::type is_array_reference_based;

	typedef typename
		types::is_base<types::past_end_capable_iterator_identifier, it>
			::type is_past_end_capable;
};

template <class IT>
struct iterator_extended_traits<IT*>
: public iterator_extended_traits_bw<IT*>
{
	typedef types::t_true is_pointer_based;
	typedef types::t_true is_pointer_capable;
	typedef types::t_false is_pointer_range_based;
	typedef types::t_true is_pointer_based_and_contiguous;
	typedef types::t_false is_array_reference_based;
	typedef types::t_true is_past_end_capable;
};

} /* namespace data */
} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_ITERATOR_EXTENDED_TRAITS_HPP
