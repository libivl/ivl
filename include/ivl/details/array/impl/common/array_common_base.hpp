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

#ifndef IVL_ARRAY_DETAILS_ARRAY_COMMON_BASE_HPP
#define IVL_ARRAY_DETAILS_ARRAY_COMMON_BASE_HPP

namespace ivl {

namespace array_details {

template <bool IS_ELEMENT, bool IS_POINTER>
struct resolve_assign_tool { };

template <>
struct resolve_assign_tool<true, false>
{
	template<class O, class A>
	static void assign(O& o, const A& a) { o.derived().assign_element(a); }
	template<class O, class A>
	static void init_size_with(O& o, const A& a)
		{ o.derived().init_size_with_element(a); }
};

template <>
struct resolve_assign_tool<false, false>
{
	template<class O, class A>
	/*
	Developper Notice: an error here could mean that you are trying to assign
	to a read-only array.
	*/
	static void assign(O& o, const A& a) { o.derived().assign_array(a); }
	template<class O, class A>
	static void init_size_with(O& o, const A& a)
		{ o.derived().init_size_with_array(a); }
};

template <bool D>
struct resolve_assign_tool<D, true>
{
	template<class O, class A>
	static void assign(O& o, const A* a)
	{
		o.derived().assign_array(
			array<A, typename data::ref_iterator<const A*>::type>
				(a, o.derived().length()));
	}
	template<class O, class A>
	static void init_size_with(O& o, const A* a)
	{
		o.derived().init_size_with_array(
			array<A, typename data::ref_iterator<const A*>::type>
				(a, o.derived().length()));
	}
};

template <class IS_REFERENCING_ARRAY, class DATA_TYPE, class ARE_RELATED>
struct overlap_tool { };

template <class DATA_TYPE, class ARE_RELATED>
struct overlap_tool<types::t_true, DATA_TYPE, ARE_RELATED>
{
	template <class O, class A>
	static inline bool operate(const O& o, const A& a)
	{
		//TODO: important: this was changed blindly. Please CHECK. !!!@@@@@
		return a.self_overlap(o);
		// <- was like above
		//
		//return o.overlap(a);
	}
};

template <class C, class D, int E>
struct overlap_tool<types::t_false, data::ref_iterator<C, D, E>, types::t_false>
{
	template <class O, class A>
	static inline bool operate(const O& o, const A& a)
	{
		return a.self_overlap(o);
	}
};

template <class C, class D, int E>
struct overlap_tool<types::t_false, data::ref_iterator<C, D, E>, types::t_true>
{
	template <class O, class A>
	static inline bool operate(const O& o, const A& a)
	{
		return a.self_overlap(o);
	}
};

template <class DATA_TYPE>
struct overlap_tool<types::t_false, DATA_TYPE, types::t_true>
{
	// same classes
	template <class O, class A>
	static inline bool operate(const O& o, const A& a)
	{
		return (&o == &a);
	}
};

template <class DATA_TYPE>
struct overlap_tool<types::t_false, DATA_TYPE, types::t_false>
{
	// different classes
	template <class O, class A> static inline
	bool operate(const O& o, const A& a) { return false; }
};

template <class IS_IVL_ARRAY>
struct overlap_resolve_tool { };

template <>
struct overlap_resolve_tool<types::t_false>
{
	template <class O, class A> static inline
	bool operate(const O& o, const A& a)
		{ return o.overlap_element(a); }
};

template <>
struct overlap_resolve_tool<types::t_true>
{
	template <class O, class A> static inline
	bool operate(const O& o, const A& a)
		{ return o.overlap_array(a) || o.overlap_element(a); }
};

} /* namespace array_details */

// ----------------------------------------------------------------------------

namespace array_details {

template<class T>
struct conv
{
	T& c;
	conv(T& c) : c(c) { }
};

} /* namespace array_details */

template <class T, class A>
class array_common_base<common_container_base<T, A> >
{
private:
	typedef array_common_base prv_this_type;
	typedef A current_type;
	typedef A t;
	t& to_current() { return static_cast<t&>(*this); }
	const t& to_current() const { return static_cast<const t&>(*this); }
	typedef typename types::get_inner_value<T>::type prv_inner_type;
	typedef prv_inner_type lt;
	typedef const prv_inner_type& l;
	/*typedef typename types::t_if<
		types::is_num_value<prv_inner_type, prv_inner_type, types::term>
		::type l_op;*/

public:
	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }
	typedef t to_array_type;

	// ------------------------------------------------------------------------
	// elem func operators

	unary_elem_func<ivl::uminus_unary_class, current_type> operator-() const
		{ return to_current(); }

	unary_elem_func<ivl::uplus_unary_class, current_type> operator+() const
		{ return to_current(); }

	unary_elem_func<ivl::bitcmp_unary_class, current_type> operator~() const
		{ return to_current(); }

	unary_elem_func<ivl::cnot_unary_class, current_type> operator!() const
		{ return to_current(); }

	unary_elem_func<ivl::dereference_unary_class, current_type> operator*()
		const
		{ return to_current(); }

	// ------------------------------------------------------------------------
	template<class J>
	binary_elem_func<ivl::plus_class, t, J> operator+(const J& j) const
	{
		return reftpl(to_current(), j);
	}
	friend
	binary_elem_func<ivl::plus_class, lt, t> operator+(l j, const t& a)
	{
		return reftpl(j, a);
	}

	// ------------------------------------------------------------------------
/*	template<class J>
	binary_elem_func<ivl::rdivide_class, t, J> operator/(const J& j) const
	{
		return reftpl(to_current(), j);
	}
	friend
	binary_elem_func<ivl::rdivide_class, lt, t> operator/(l j, const t& a)
	{
		return reftpl(j, a);
	}
	*/


	//--
	/*template<class J>
	binary_elem_func<ivl::minus_class, t, J> operator-(const J& j) const
	{
		return reftpl(to_current(), j);
	}*/
	template<class J>
	typename types::t_if<types::is_ptr<J>,
	ivl::concat<const current_type, const typename types::deref_ptr<J>::type, 0>,
	binary_elem_func<ivl::minus_class, t, J>
	>::type operator-(const J& j) const
	{
		return reftpl(to_current(), j);
	}

	friend
	binary_elem_func<ivl::minus_class, lt, t> operator-(l j, const t& a)
	{
		return reftpl(j, a);
	}
	//--
	template<class J>
	typename types::t_if<types::is_ptr<J>,
	ivl::concat<const current_type, const typename types::deref_ptr<J>::type, 1>,
	binary_elem_func<ivl::cbitor_class, t, J>
	>::type operator|(const J& j) const
	{
		return reftpl(to_current(), j);
	}

	friend
	binary_elem_func<ivl::cbitor_class, lt, t> operator|(l j, const t& a)
	{
		return reftpl(j, a);
	}
	//--
	template<class A2>
	ivl::concat<const current_type, const A2, 1>
	operator|(const A2*& r)
	{
		return ivl::concat<const current_type, const A2, 1>
		(to_current(), *r);
	}

	template<class A2>
	ivl::concat<const current_type, const A2, 0>
	operator-(const A2*& r)
	{
		return ivl::concat<const current_type, const A2, 0>
		(to_current(), *r);
	}

	template<class J>
	binary_elem_func<ivl::power_class, t, J> operator->*(const J& j) const
	{
		return reftpl(to_current(), j);
	}
	friend
	binary_elem_func<ivl::power_class, lt, t> operator->*(l j, const t& a)
	{
		return reftpl(j, a);
	}


};

// ----------------------------------------------------------------------------

// common functions and types for all arrays
template<class T, class SPEC>
class array_common_base<ivl::array<T, SPEC> >
: public array_details::dependable_array_common<T, SPEC,
	array_base<T, typename types::derive_opts<ivl::array<T, SPEC> >::type>,
	typename array_base<T, typename
		types::derive_opts<ivl::array<T, SPEC> >::type>::is_writeable,
	typename array_base<T, typename
		types::derive_opts<ivl::array<T, SPEC> >::type>::is_resizeable
	>,

	public array_common_base<common_container_base<T, array<T, SPEC> > >
{
private:
	typedef array_common_base prv_this_type;

	// dependable_array_common
	typedef typename prv_this_type::direct_base direct_base;

	typedef array<T, SPEC> t;

	typedef t current_type;

	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }
	t& to_current() { return static_cast<t&>(*this); }
	const t& to_current() const { return static_cast<const t&>(*this); }

	typedef typename prv_this_type::derived_type prv_derived_type;

	//prv_derived_type& prv_derived()
	//	{ return static_cast<prv_derived_type&>(to_array()); }
	//const prv_derived_type& prv_derived() const
	//	{ return static_cast<const prv_derived_type&>(to_array()); }

	template <bool B, bool C> friend class array_details::resolve_assign_tool;

	template <class A>
	struct resolve_assign_pointer
	{
		// I wished ;| using namespace types;
		typedef typename types::t_and<
			types::t_or<types::is_ptr<typename types::bare_type<A>::type>,
				types::is_c_array<typename types::bare_type<A>::type> >,
			types::t_or<types::t_eq<T, typename
					types::deref_ptr<typename types::bare_type<A>::type>::type>,
				types::t_not<types::is_ptr<T> >
			> >::type is_pointer;
	};

	template <class A>
	void resolve_assign(const A& a)
	{
		using namespace types;
		typedef typename t_not<is_ivl_array<A> >::type is_element;
		// this is so that we can do *this = scalar<derived_type> as non elem.
		typedef typename t_and<
			is_base<types::scalar_identifier, A>,
			is_base<prv_this_type, A> >::type non_elem_scalar;
		typedef typename t_and<is_element, t_not<non_elem_scalar> >
			::type final_is_element;

		typedef typename resolve_assign_pointer<A>::is_pointer is_pointer;

		//nonlin_report(
		//	types::r_descalarize<non_elem_scalar>(a));

		array_details::resolve_assign_tool<
				final_is_element::value, is_pointer::value>
			::assign(this->derived(),
			types::r_descalarize<non_elem_scalar>(a));
	}
	template <class A>
	void resolve_init_size_with(const A& a)
	{
		using namespace types;

		// TODO: interesting enough, could be checked as method for resolve_assign.
		typedef typename t_not<t_or<
			is_kind_base_eq_recurse<prv_derived_type, A>,
			is_kind_base_eq_recurse<A, prv_derived_type> > >::type is_element;
		// this is so that we can do *this = scalar<derived_type> as non elem.
		// TODO: minor. this code would look better in one place.
		typedef typename t_and<
			is_base<types::scalar_identifier, A>,
			is_base<prv_this_type, A> >::type non_elem_scalar;
		typedef typename t_and<is_element, t_not<non_elem_scalar> >
			::type final_is_element;

		typedef typename resolve_assign_pointer<A>::is_pointer is_pointer;

		array_details::resolve_assign_tool<
			final_is_element::value, is_pointer::value>
			::init_size_with(this->derived(),
			types::r_descalarize<non_elem_scalar>(a));
	}

protected:
	typedef prv_this_type common_base_class;

	template <class A>
	void init_size_with(const A& a)
	{
		resolve_init_size_with(a);
	}

public:
	typedef t array_type;
	typedef t container_type;

	typedef array_base<T, typename
		types::derive_opts<ivl::array<T, SPEC> >::type> base_class;

	typedef typename array_common_base::data_type data_type;

	typedef typename array_common_base::derived_type derived_type;

	typedef T elem_type;


	//Default constructor
	array_common_base() {}

/*
	template<class T, class S, class K>
	t& operator=(types::t_if<typename t::has_random_access,
		const array<T, S, K>&, not_a_type
*/

/** @name Basic array functions
@{*/
	// is supposedly called by ovelap(),
	// however may be called on its own.
	// overlap(a,b) does overlap(a,b) (which is same as overlap (b,a) )
	//				and also overlap_element(a,b);
	// so a complete overlap check would be:
	// ovelap(a,b) || overlap_element(b,a)
	//
	// note that: overlap_element when called in a loop per element, does
	// return a complete overlap check.
	template <class J>
	inline
	bool overlap_element(const J& s) const
	{
		// for now do nothing.
		return false;
	}

	template <class A>
	inline
	bool overlap_array(const A& a) const
	{
		return array_details::overlap_tool<typename
			A::is_referencing_array, typename A::data_type,
			typename types::is_related<derived_type, A>::type>
		::operate(this->derived(), a.derived());
	}

	template <class A>
	inline
	bool overlap(const A& a) const
	{
		return array_details::overlap_resolve_tool<typename
			types::is_ivl_array<A>::type>
			::operate(this->derived(), a);
	}

	template <class S>
	bool isequal(const array<T, S>& o)
	{
		return ivl::isequal(to_array().derived(), o.derived());
	}

	typename types::create_new<T>::type max() const;
	typename types::create_new<T>::type min() const;

	//TODO: not Derived! array<T,S>!!!
/**@}*/

	typedef typename types::t_if<types::t_or_3<types::is_builtin<T>,
	       types::is_ptr<T>, types::is_ref<T> >,
	       types::not_a_type, T>::type struct_value_type;

	// ------------------
	template<class M, class Z>
	member_array<array_type, M> operator[](M Z::* m)
	{
		return reftpl(to_array(), m);
	}
	template<class M, class Z>
	member_array<const array_type, M> operator[](M Z::* m) const
	{
		return reftpl(to_array(), m);
	}
	// ------------------

	template<class R, class A1, class Z>
	memberfunc_constructor<array_type, tuple<Z, R, A1> > operator[](R (Z::*m)(A1))
	{
		return reftpl(to_array(), m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const array_type, tuple<Z, R, A1> > operator[](R (Z::*m)(A1)) const
	{
		return reftpl(to_array(), m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<array_type, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const)
	{
		return reftpl(to_array(), m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const array_type, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const) const
	{
		return reftpl(to_array(), m);
	}
	// x0
	template<class R, class Z>
	memberfunc_constructor<array_type, tuple<Z, R, types::term> > operator[](R (Z::*m)())
	{
		return reftpl(to_array(), m);
	}
	template<class R, class Z>
	memberfunc_constructor<const array_type, tuple<Z, R, types::term> > operator[](R (Z::*m)()) const
	{
		return reftpl(to_array(), m);
	}
//
	template<class R, class Z>
	memberfunc_constructor<array_type, tuple<const Z, R, types::term> > operator[](R (Z::*m)() const)
	{
		return reftpl(to_array(), m);
	}
	template<class R, class Z>
	memberfunc_constructor<const array_type, tuple<const Z, R, types::term
	> > operator[](R (Z::*m)() const) const
	{
		return reftpl(to_array(), m);
	}





	// -------------------------------------------
	// ------------------
	template<class M, class Z>
	member_array<array_type, M> in(M Z::* m)
	{
		return reftpl(to_array(), m);
	}
	template<class M, class Z>
	member_array<const array_type, M> in(M Z::* m) const
	{
		return reftpl(to_array(), m);
	}
	// ------------------

	template<class R, class A1, class Z>
	memberfunc_constructor<array_type, tuple<Z, R, A1> > in(R (Z::*m)(A1))
	{
		return reftpl(to_array(), m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const array_type, tuple<Z, R, A1> > in(R (Z::*m)(A1)) const
	{
		return reftpl(to_array(), m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<array_type, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const)
	{
		return reftpl(to_array(), m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const array_type, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const) const
	{
		return reftpl(to_array(), m);
	}


	// -------------------------------------------

	// creation of mask array
	template<class S>
	mask_array<array_type, array<bool, S> > operator[]
		(const array<bool, S>& ba)
	{
		return reftpl(to_array(), ba);
	}

	template<class S>
	mask_array<const array_type, array<bool, S> > operator[]
		(const array<bool, S>& ba) const
	{
		return reftpl(to_array(), ba);
	}

	// types
	typedef mask_array<array_type, array<bool, mem> > mask_array_type;
	typedef mask_array<const array_type, array<bool, mem> > const_mask_array_type;

//-----------------------------------------------------------------------------

	// creation of indirect array]
	// Note: advanced compared to others.
	// has reference mode and store mode.
	template<class I, class S>
	ivl::indirect_array<array_type, const typename array<I, S>::derived_type& > operator[]
		(const array<I, S>& sa)
	{
		return reftpl(to_array(), sa.derived());
	}

	template<class I, class S>
	ivl::indirect_array<const array_type, const typename array<I, S>::derived_type& > operator[]
		(const array<I, S>& sa) const
	{
		return reftpl(to_array(), sa.derived());
	}

	// types
	// TODO: deprecated
	typedef ivl::indirect_array<array_type, size_array> indirect_array_type;
	typedef ivl::indirect_array<const array_type, size_array> const_indirect_array_type;

	typedef ivl::indirect_array<array_type, size_array> indirect_array;
	typedef ivl::indirect_array<const array_type, size_array> const_indirect_array;


//-----------------------------------------------------------------------------

	// creation of slice array from slice
	slice_array<array_type> operator[](const slice& sl)
	{
		return reftpl(to_array(), sl);
	}

	slice_array<const array_type> operator[](const slice& sl) const
	{
		return reftpl(to_array(), sl);
	}

//-----------------------------------------------------------------------------

	// types
	typedef slice_array<array_type> slice_array_type;
	typedef slice_array<const array_type> const_slice_array_type;

	// creation of slice array from range
	slice_array<array_type> operator[](const ivl::range<size_t>& sl)
	{
		return reftpl(to_array(), sl);
	}

	slice_array<const array_type> operator[](
		const ivl::range<size_t>& sl) const
	{
		return reftpl(to_array(), sl);
	}

//-----------------------------------------------------------------------------

	template<class I>
	slice_array<array_type> operator[](const ivl::crange<size_t>& r)
	{
		return reftpl(to_array(), r);
	}

	template<class I>
	crange_array<const array_type> operator[](
		const ivl::crange<size_t>& r) const
	{
		return reftpl(to_array(), r);
	}

//-----------------------------------------------------------------------------

	/*
	array<T, typename data::
		with_type<data::slice<array_type> >::type> operator[](const slice& sl)
	{
		return array<T, typename data::slice<array_type>::type>(to_array(), sl);
	}
*//*
	array<T, typename data::
		with_type<data::slice<const array_type> >::type> operator[]
		(const slice& sl) const
	{
		return array<T, typename data::slice<const array_type>::type>
			(to_array(), sl);
	}*/

	// creation of slice array from range
	/*
	array<T, typename data::
		with_type<data::slice<array_type> >::type> operator[](
		const ivl::range<size_t>& sl)
	{
		return array<T, typename data::slice<array_type>::type>(to_array(), sl);
	}

	array<T, typename data::
		with_type<data::slice<const array_type> >::type> operator[]
		(const ivl::range<size_t>& sl) const
	{
		return array<T, typename data::slice<const array_type>::type>
			(to_array(), sl);
	}*/


//-----------------------------------------------------------------------------


	// creation of all_array
	all_array<array_type, types::t_not<typename array_common_base::is_writeable>
		::type::value> operator[](const index_array_all_type& all)
	{
		return all_array<array_type, types::t_not<typename
			array_common_base::is_writeable>::type::value>(to_array());
	}

	all_array<array_type, true> operator[](const index_array_all_type& all) const
	{
		return all_array<array_type, true>(to_array());
	}

	// -------------------------------------------

/*	template <class A>
	derived_type& operator=(const A& o)
	{
		direct_base::operator=(o);
		return to_array().derived();
	}
*/
	template <class A>
	derived_type& assign(const A& a)
	{
		resolve_assign(a);
		return to_array().derived();
	}

	// the copy operator. the this == &a is checked only here!
	array_common_base& operator=(const array_common_base& a)
	{
		//if(this != &a) resolve_assign(a);
		ivl::safe_assign(this->derived(), a);
		return *this;
	}

	template <class A>
	derived_type& operator=(const A& a)
	{
		ivl::safe_assign(this->derived(), a);
		return to_array().derived();
	}

	template <class J>
	derived_type& operator=(const tuple_rvalue<J>& r)
	{
		//TODO: safe output
		r.tuple_output(reftpl(to_array().derived()));

		//r.derived().safe_output(to_array().derived());
		//typename rvalue_base<J>::derived_type::safe_input
		//r.derived().output(to_array().derived());
		return to_array().derived();
	}


	bool empty() const { return static_cast<const t&>(*this).length() == 0; }

	t& ref() { return static_cast<t&>(*this); }

	// operators +=, -= etc., are defined in the readwrite_array_common level.

/*
	template <class S, class K>
	derived_type& operator=(const array<T, S, K>& o)
	{
		direct_base::operator=(o);
		return to_array().derived();
	}
*/







/**
 * @name Print functions
@{*/
	//! Print an array
	std::ostream& print(std::ostream& os) const
	{
		ivl::print(os, to_array().derived());
		return os;
	}
/**@}*/


	array<T, mem> cat(const array<T, mem>& a) const;

#ifdef IVL_MATLAB
	/**
	 * \brief Output the array contents to Matlab mxArray
	 *
	 * The resulting mxArray will have elements of the class of
	 * the existing array
	 */
	mxArray* mx() const;
#endif
};

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_ARRAY_COMMON_BASE_HPP
