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

#ifndef IVL_CORE_DETAILS_TYPES_ARRAY_ITERATOR_HPP
#define IVL_CORE_DETAILS_TYPES_ARRAY_ITERATOR_HPP

namespace ivl {
namespace types {


namespace types_details {

template <class A, class WRITEABLE, int SPECIALIZATION>
struct best_iterator { };

template <class A>
struct best_iterator<A, types::t_true, 0>
{
	typedef typename A::iterator type;
};

template <class A>
struct best_iterator<A, types::t_false, 0>
{
	typedef typename A::const_iterator type;
};

template <class A, int SPC>
struct best_iterator<A, types::t_true, SPC>
{
	typedef typename A::template s_iterator<SPC>::type type;
};

template <class A, int SPC>
struct best_iterator<A, types::t_false, SPC>
{
	typedef typename A::template const_s_iterator<SPC>::type type;
};

template <class A, class WRITEABLE, int SPECIALIZATION>
struct best_reverse_iterator { };

template <class A>
struct best_reverse_iterator<A, types::t_true, 0>
{
	typedef typename A::reverse_iterator type;
};

template <class A>
struct best_reverse_iterator<A, types::t_false, 0>
{
	typedef typename A::const_reverse_iterator type;
};

// -------------------------------------------------

template <
class A,
class WRITEABLE,
int SPECIALIZATION = 0,
bool PAST_END_CAPABLE = true
>
struct best_iterator_nd { };

template <class A>
struct best_iterator_nd<A, types::t_true, 0, true>
{
	typedef typename A::iterator_nd type;
};

template <class A>
struct best_iterator_nd<A, types::t_false, 0, true>
{
	typedef typename A::const_iterator_nd type;
};

template <class A, int SPC>
struct best_iterator_nd<A, types::t_true, SPC, true>
{
	typedef typename A::template s_iterator_nd<SPC>::type type;
};

template <class A, int SPC>
struct best_iterator_nd<A, types::t_false, SPC, true>
{
	typedef typename A::template const_s_iterator_nd<SPC>::type type;
};

// --- not pastend capable nd
template <class A>
struct best_iterator_nd<A, types::t_true, 0, false>
{
	typedef typename A::_fast_iterator_nd type;
};

template <class A>
struct best_iterator_nd<A, types::t_false, 0, false>
{
	typedef typename A::_fast_const_iterator_nd type;
};

template <class A, int SPC>
struct best_iterator_nd<A, types::t_true, SPC, false>
{
	typedef typename A::template _fast_s_iterator_nd<SPC>::type type;
};

template <class A, int SPC>
struct best_iterator_nd<A, types::t_false, SPC, false>
{
	typedef typename A::template _fast_const_s_iterator_nd<SPC>::type type;
};

// --- reverse nd

template <class A, class WRITEABLE, int SPECIALIZATION = 0, int PAST_END = true>
struct best_reverse_iterator_nd { };

template <class A>
struct best_reverse_iterator_nd<A, types::t_true, 0, true>
{
	typedef typename A::reverse_iterator_nd type;
};

template <class A>
struct best_reverse_iterator_nd<A, types::t_false, 0, true>
{
	typedef typename A::const_reverse_iterator_nd type;
};

} /* namespace types_details */

template <class A, int SPECIALIZATION = 0>
struct best_iterator
{
	typedef t_and<t_not<is_const<A> >, typename A::is_writeable> is_writeable;

	typedef typename types_details::best_iterator<A,
		typename is_writeable::type, SPECIALIZATION>::type type;
	/*
	typedef typename t_if<is_writeable,
		typename
		types_details::best_iterator<A, typename A::is_writeable,
			SPECIALIZATION>::type,
		typename
		types_details::best_iterator<A, types::t_false, SPECIALIZATION>::type
		>::type type;*/
};

template <int S>
struct best_iterator<types::term, S> { typedef types::term type; };

template <class A, int SPECIALIZATION = 0>
struct best_reverse_iterator
{
	typedef t_and<t_not<is_const<A> >, typename A::is_writeable> is_writeable;

	typedef typename types_details::best_reverse_iterator<A,
		typename is_writeable::type, SPECIALIZATION>::type type;

	/*
	typedef typename t_if<is_writeable,
		typename
		types_details::best_reverse_iterator<A, typename A::is_writeable,
			SPECIALIZATION>::type,
		typename
		types_details::best_reverse_iterator<A, types::t_false,
			SPECIALIZATION>::type
		>::type type;*/
};

template <int S>
struct best_reverse_iterator<types::term, S> { typedef types::term type; };

template <class A, int SPECIALIZATION = 0, bool PAST_END_CAPABLE = true>
struct best_iterator_nd
{
	typedef t_and<t_not<is_const<A> >, typename A::is_writeable> is_writeable;

	typedef typename types_details::best_iterator_nd<A,
		typename is_writeable::type, SPECIALIZATION, PAST_END_CAPABLE>
		::type type;
		/*
	typedef typename t_if<is_writeable,
		typename
		types_details::best_iterator_nd<A, typename A::is_writeable,
			SPECIALIZATION>::type,
		typename
		types_details::best_iterator_nd<A, types::t_false, SPECIALIZATION>::type
		>::type type;*/
};

template <int S, bool P>
struct best_iterator_nd<types::term, S, P> { typedef types::term type; };

template <class A, int SPECIALIZATION = 0>
struct best_fast_iterator_nd
: public best_iterator_nd<A, SPECIALIZATION, false>
{
};

template <class A, int SPECIALIZATION = 0, bool PAST_END_CAPABLE = true>
struct best_reverse_iterator_nd
{
	typedef t_and<t_not<is_const<A> >, typename A::is_writeable> is_writeable;

	typedef typename types_details::best_reverse_iterator_nd<A,
		typename is_writeable::type, SPECIALIZATION, PAST_END_CAPABLE>
		::type type;
/*
	typedef t_and<t_not<is_const<A> >, typename A::is_writeable> is_writeable;
	typedef typename t_if<is_writeable,
		typename
		types_details::best_reverse_iterator_nd<A, typename A::is_writeable,
			SPECIALIZATION>::type,
		typename
		types_details::best_reverse_iterator_nd<A, types::t_false,
			SPECIALIZATION>::type
		>::type type;*/
};

template <int S, bool P>
struct best_reverse_iterator_nd<types::term, S, P>
{ typedef types::term type; };

/*
template <class A>
struct best_iterator_nd
{
	typedef t_and<t_not<is_const<A> >, typename A::is_writeable> is_writeable;
	typedef typename t_if<t_and<t_not<is_const<A> >, typename A::is_writeable>,
		typename
		types_details::best_iterator_nd<A, typename A::is_writeable>::type,
		typename A::const_iterator_nd>::type type;
};

template <class A>
struct best_reverse_iterator_nd
{
	typedef t_and<t_not<is_const<A> >, typename A::is_writeable> is_writeable;
	typedef typename t_if<t_and<t_not<is_const<A> >, typename A::is_writeable>,
		typename types_details::
			best_reverse_iterator_nd<A, typename A::is_writeable>::type,
		typename A::const_reverse_iterator_nd>::type type;
};
*/

} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_ARRAY_ITERATOR_HPP
