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

#ifndef IVL_ARRAY_DETAILS_INDIRECT_ARRAY_HPP
#define IVL_ARRAY_DETAILS_INDIRECT_ARRAY_HPP

namespace ivl {

template<class A, class B> class indirect_array; // fwd

namespace array_details {

// check if the array is already indirect
template <class A, class D>
struct indirect_ref_type_2
{
	typedef A type;
	typedef types::term idref_type;
};

template <class A, class AR, class B, class D>
struct indirect_ref_type_2<A, data::indirect<AR, B, D> >
{
//	typedef typename types::apply_const<AR, 
//		typename types::is_const<A>::type>::type type;
	typedef AR type;
	typedef types::term idref_type;
};

template <class A, class IS_ARRAY>
struct indirect_ref_type_1
{
	typedef A type;
	typedef types::term idref_type;
};

template <class A>
struct indirect_ref_type_1<A, types::t_true>
	: public indirect_ref_type_2<A, typename A::data_type>
{
};

template <class A>
struct indirect_ref_type
	: public indirect_ref_type_1<A, typename
		types::is_ivl_array<A>::type>
{
};

template <class A, class B, class BASE_PLAIN>
struct rebase_indirect_1
{
	typedef typename types::bare_type<B>::type b_t;

	//typedef typename b_t::create_new n_t;
	typedef typename types::normal_type<b_t>::type n_t;

	typedef typename types::change_elem_type<typename A::elem_type, n_t>::type t1;

	typedef typename types::change_data_class_set<data::indirect<A, B>, t1>::type type;
	//typedef array<typename A::elem_type, data::indirect<A, B> > type;

	typedef tuple<A&, const b_t&> data_init_arg;

	static inline A& correct(A& a) { return a; }
	static inline const b_t& merge(A& a, const b_t& b) { return b; }
};

template <class A, class B>
struct rebase_indirect_1<A, B, types::t_false>
{
	// This is the case where indices need to be merged.

	typedef typename types::bare_type<B>::type b_t;
	// B is either going to be an elem type or a mem type,
	// in our case a mem type.
	/*
	typedef typename types::t_if<types::is_ref<B>,
		typename types::create_similar<b_t>::type, B>
			::type new_b_t;
		*/
	typedef typename types::create_similar<b_t>::type new_b_t;



	typedef typename types::normal_type<b_t>::type n_t;
	typedef typename types::change_elem_type<typename A::elem_type, n_t>::type t1;
	typedef typename types::change_data_class_set<data::indirect<typename indirect_ref_type<A>::type, new_b_t>, t1>::type type;

	//typedef indirect_array<typename indirect_ref_type<A>::type, new_b_t> type;



	static inline
		typename indirect_ref_type<A>::type& correct(A& a)
	{
		return a.get_ref_1();
	}
	// TODO: (more likely than below)
	// instead of elem- solution for merge, differentiate
	// indirect<indirect based on whether B is reference.
	// when B is stored, use the rebasing and merging approach.
	// when B is reference, do not rebase at all, use the original
	// data::indirect<data::indirect class that automatically inherits
	// and solves merging, even if slower.
	// The latter may have its own valid uses, e.g. the indices of
	// parent change and the child is dynamically affected.
	//
	// TODO: should be (in implementation and return type) 
	// an elem func to avoid copy
	// something like idxmap(b, _[a.get_ref_2()])
	// the _[] scalar conversion is to make the second arg scalar.
	// maybe when the B type is mem we need mem and when the B type
	// is reference we need that elem_func approach.
	typedef tuple<typename indirect_ref_type<A>::type&, new_b_t> data_init_arg;

	static inline new_b_t merge(A& a, const b_t& b)
		{ return a.merge_idx(b); }       
};

template <class A, class B>
struct rebase_indirect
	: public rebase_indirect_1<A, B, 
		typename types::t_eq<A, typename indirect_ref_type<A>::type>
		 ::type>
{
};

} /* namespace array_details */

template<class A, class B>
class indirect_array
//: public array<typename A::elem_type, data::indirect<
//	typename array_details::indirect_ref_type<A>::type, B> >
: public array_details::rebase_indirect<A, B>::type
{
	typedef typename array_details::indirect_ref_type<A>::type prv_ref_t;
	typedef typename array_details::rebase_indirect<A, B>::type prv_base;
	typedef typename array_details::rebase_indirect<A, B>::data_init_arg prv_arg;
	typedef typename types::bare_type<B>::type b_t;
	prv_base& get_prv_base() { return static_cast<prv_base&>(*this); }
	const prv_base& get_prv_base() const 
		{ return static_cast<const prv_base&>(*this); }
	typedef typename types::bare_type<B>::type prv_b;
public:
	typedef indirect_array this_type;
	typedef typename this_type::array_type base_class;

	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// convert temporary object to non-const reference
	this_type& ref() { return *this; }

	indirect_array() { }
	//indirect_array(const this_type& o) : base_class(o.base()) { }
	indirect_array(const this_type& o) : prv_base(o.get_prv_base()) { }

	//indirect_array(const tuple<prv_ref_t&, const B&>& t)
	//	: base_class(t.v1, t.v2) { }

	/* nd-spec
	template<class I>
	indirect_array(const tuple<A&, const I&>& t)
		: prv_base(t.v2.size(), prv_arg(array_details::rebase_indirect<A, B>
				::correct(t.v1), 
			array_details::rebase_indirect<A, B>
				::merge(t.v1, t.v2))) { }
	template<class SZ, class K>
	indirect_array(SZ sz, K t) 
		: prv_base(t.v2.size(), prv_arg(array_details::rebase_indirect<A, B>
				::correct(t.v1), 
			array_details::rebase_indirect<A, B>
				::merge(t.v1, t.v2))) { }

	*/



	template<class I>
	indirect_array(const tuple<A&, I&>& t)
		: prv_base(t.v2.size(), prv_arg(array_details::rebase_indirect<A, B>
				::correct(t.v1), 
			array_details::rebase_indirect<A, B>
				::merge(t.v1, t.v2))) { }


	/* old-spec works*/
	/*
	template<class I>
	indirect_array(const tuple<A&, const I&>& t)
		: prv_base(array_details::rebase_indirect<A, B>
				::correct(t.v1), 
			array_details::rebase_indirect<A, B>
				::merge(t.v1, t.v2)) { }

	indirect_array(A& a, const b_t& b)
		: prv_base(array_details::rebase_indirect<A, B>
				::correct(a),
			array_details::rebase_indirect<A, B>
				::merge(a, b)) { }
		*/
	/**/



	//template<class P1, class P2>
	//template<class T, class I, class J>
	//indirect_array(const array<T, data::indirect<A, I, J> >& o)
	//	: prv_base(o) { }

	template<class T, class I>
	explicit indirect_array(array<T, I>& o) : prv_base(o.derived()) { }

	template<class T, class I>
	explicit indirect_array(const array<T, I>& o) : prv_base(o.derived()) { }


	//indirect_array(A& a)
	//	: prv_base(A, 


	//using base_class::operator=;
	this_type& operator=(const this_type& o)
	{
		base_class::operator=(o);
		return *this;
	}
	template<class K>
	this_type& operator=(const K& o)
	{
		base_class::operator=(o);
		return *this;
	}
};

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_INDIRECT_ARRAY_HPP
