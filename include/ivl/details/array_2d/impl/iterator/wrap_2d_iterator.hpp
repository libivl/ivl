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

#ifndef IVL_ARRAY_2D_DETAILS_ITERATOR_WRAP_2D_ITERATOR_HPP
#define IVL_ARRAY_2D_DETAILS_ITERATOR_WRAP_2D_ITERATOR_HPP

namespace ivl {

namespace data {

namespace data_details {

template <class A>
struct wrap_2d_elem
{
	typedef ivl::array<typename A::elem_type,
		data::ref_iterator<
		typename types::best_iterator_nd<A>::type,
		typename A::const_iterator_nd> > type;
};

} /* namespace data_details */


template <class A, int OUT_D = 1, int IN_D = 0>
class wrap_2d_iterator
{
	typedef typename types::best_iterator_nd<A>::type iter_nd;

	typedef typename data_details::wrap_2d_elem<A>::type elem_type;

	// may be not necessary
	typedef typename types::best_iterator_nd<A>::is_writeable is_writeable;
	typedef typename types::t_not<is_writeable>::type is_const;

/*
	friend class data_details::rnd_iter_operator_expander<
		wrap_2d_iterator<A>, typename data_details::wrap_2d_elem<A>::type,
		false, typename data_details::wrap_2d_elem<A>::type>;
*/
	A* a;
	iter_nd it;

public:
	typedef wrap_2d_iterator this_type;

	// iterator_traits
    typedef std::random_access_iterator_tag iterator_category;
    typedef elem_type value_type;
	typedef ptrdiff_t difference_type;
	typedef elem_type* pointer;
	typedef elem_type reference;

	// constructors
	wrap_2d_iterator() { }
	wrap_2d_iterator(A& a) : a(&a), it(a._begin(OUT_D)) { }
	wrap_2d_iterator(const wrap_2d_iterator& o) : a(o.a), it(o.it) { }

	// members

	elem_type operator *() const
		{ return elem_type(a->_begin(IN_D, it), a->size(IN_D)); }

	elem_type operator [](size_t j) const
		{ return elem_type(a->_begin(IN_D, it + j), a->size(IN_D)); }

	// increment-decrement
	this_type& operator++() { ++it; return *this; }
	this_type& operator--() { --it; return *this; }

	this_type operator++(int) { this_type tmp(*this); it++; return tmp; }
	this_type operator--(int) { this_type tmp(*this); it--; return tmp; }

	// random access
	this_type operator +(const size_t j) const
		{ this_type tmp(*this); tmp.it += j; return tmp; }

	this_type operator -(const size_t j) const
		{ this_type tmp(*this); tmp.it -= j; return tmp; }

	this_type& operator +=(const size_t j) { it += j; return *this; }
	this_type& operator -=(const size_t j) { it -= j; return *this; }

	// difference
	difference_type operator -(const this_type& a) const {
		return difference_type(it - a.it);
	}

	//copy same type iterator
	this_type& operator=(const this_type& o)
		{ a = o->a; it = o->it; return *this; }

	bool operator==(const this_type& o) const
		{ return (it == o.it); }

	bool operator!=(const this_type& o) const
		{ return (it != o.it); }
};


#if 0
//note: some parts of this below might remain useful for the nd impl
template <class A>
class wrap_2d_iterator
	: public data_details::rnd_iter_operator_expander<
		wrap_2d_iterator<A>, typename A::elem_type,
		types::t_not<types::best_iterator_nd<A>::is_writeable>::value,
		typename types::best_iterator_nd<A>::type::reference>
{
	typedef typename types::best_iterator_nd<A>::type iter_nd;

	typedef typename types::best_iterator_nd<A>::is_writeable is_writeable;

	typedef typename types::t_not<is_writeable>::type is_const;

	typedef typename iter_nd::reference ref;

	friend class data_details::iter_operator_expander
		<wrap_2d_iterator<A>, typename A::elem_type, is_const, ref>;

	typedef typename types::apply_const<T, is_const>::type best_value_type;

	typedef ref best_ref_type;

	// this struct is used to disable specific specialization members
	struct not_a_type { operator size_t() { return 0; } };

	typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
		types::code_word<> >::type invalid_if_const;

	A* o;
	iter_nd i;
#endif


} /* namespace data */

} /* namespace ivl */

#endif // IVL_ARRAY_2D_DETAILS_ITERATOR_WRAP_2D_ITERATOR_HPP
