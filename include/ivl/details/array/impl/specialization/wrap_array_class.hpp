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

namespace array_details {

template <class RESIZEABLE>
struct wrap_array_resize_details { };

template <class HAS_C_PTR, class T>
struct wrap_array_ptr_details { };

template <class D, class IS_FORCE>
struct wrap_array_overlap_impl { };

template <class A>
struct wrap_ices_iterator : public A
{
	A& base() { return static_cast<A&>(*this); }
	const A& base() const { return static_cast<const A&>(*this); }	
	typedef typename A::value_type prv_vt;
	typedef ivl::scalar<prv_vt> value_type;
	typedef ivl::scalar<prv_vt> reference;
	value_type operator*() const { return A::operator*(); }
	template<class I>
	value_type operator[](I i) const { return A::operator[](i); }
	wrap_ices_iterator() {}
	template <class O>
	wrap_ices_iterator(const O& a) : A(a) { }
	wrap_ices_iterator(const wrap_ices_iterator& a) : A(a) { }

	using A::operator -;
	ptrdiff_t operator-(const wrap_ices_iterator&o)
	{
		return base() - o.base();
	}


	wrap_ices_iterator& operator=(const wrap_ices_iterator& o)
		{ A::operator=(o.base()); return *this; }
	template<class K>
	wrap_ices_iterator& operator=(const K& o)
	{
		A::operator=(o);
		return *this;
	}
	//using A::operator=;
};

template <class ICES, class A>
struct wrap_ices_it
{
	typedef A type;
};
template<class A>
struct wrap_ices_it<types::t_true, A>
{
	typedef wrap_ices_iterator<A> type;
};

} /* namespace array_details */

/**
 * Wrap array is a superset for force class.
 * Force class is a wrapper of another normal array that is writeable and
 * possibly resizeable. The only action of this class is that it hides
 * the wrapped class and pointer from the rest of ivl, and it has some
 * special behavior so that overlap always returns false in any
 * circumstances. So this array won't detect data overlapping with
 * other arrays, allowing the experienced user to force an array to not
 * be copied when it is input and output at the same time when upon request.
 */
template <class T,
		 class A,
		 class ATTR,
		 class DERIVED_INFO
	     >
class array<T, data::wrap_array<A, ATTR, DERIVED_INFO> >
	:
	public array_common_base<
		array<T, data::wrap_array<A, ATTR, DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::wrap_array<A, ATTR, DERIVED_INFO> > >::type>,

	public array_details::wrap_array_overlap_impl<
		array<T, data::wrap_array<A, ATTR, DERIVED_INFO> >,
		typename types::t_eq<ATTR, data::force_wrap_array_attr>::type>,
		
	public data::wrap_identifier<ATTR>
{

private:
	typedef array_common_base<array<T,
		data::wrap_array<A, ATTR, DERIVED_INFO> > > common_base_class;

	typedef typename
		types::is_base<data::ice_wrap_array_attr_base_identifier, ATTR>
		::type	prv_is_ice;
	typedef typename types::t_or<
			//types::t_eq<ATTR, data::ices_wrap_array_attr>,
			prv_is_ice, // @@@ test
			types::t_eq<ATTR, data::icers_wrap_array_attr<T> >
		>
		::type prv_is_ices;
	typedef typename types::t_not<prv_is_ice>::type prv_is_nice;

	typedef typename types::t_if<typename array::is_writeable,
			typename types::best_iterator<A>::type,
			typename A::const_iterator>::type ref_a_best_iterator;

	typedef typename types::t_if<typename array::is_writeable,
			typename types::best_reverse_iterator<A>::type,
			typename A::const_reverse_iterator>
				::type ref_a_best_reverse_iterator;
	
	typedef typename array_details::
		wrap_ices_it<prv_is_ices, ref_a_best_iterator>
		::type a_best_iterator;
	typedef typename array_details::
		wrap_ices_it<prv_is_ices, ref_a_best_reverse_iterator>
		::type a_best_reverse_iterator;
	typedef typename array_details::
		wrap_ices_it<prv_is_ices, typename A::const_iterator>
		::type a_const_iterator;
	typedef typename array_details::
		wrap_ices_it<prv_is_ices, 
		typename A::const_reverse_iterator>::type a_const_reverse_iterator;

	typedef typename A::this_array_type a_t;

protected:
	typedef typename array::has_random_access prv_has_random_access;

	typedef array_details::elem_func_tools<T,
		prv_has_random_access::value> tool;

	typedef typename types::t_if<prv_is_ice, 
		internal::relinit_pointer_face<A>, A*>
		::type prv_a_store_t;
		
	friend class tool::not_a_type; // allow disabled types only in our class

	typedef typename types::t_if<prv_is_ice, typename tool::not_a_type, array>
		::type nice_this_type;
	typedef typename types::t_if<prv_is_ice, array, typename tool::not_a_type>
		::type ice_this_type;
	typedef typename types::t_if<types::t_and<prv_is_ice, types::t_not<types::is_const<A> > >, const A&, 
		typename tool::not_a_type>::type prv_const_ice_a;

	prv_a_store_t a_ptr;
	a_best_iterator a_begin;
	size_t len;

public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	//! difference type of iterators
	typedef ptrdiff_t diff_type;

	using base_class::derived;

	template <class O>
	void assign(const O& o)
	{
		a_ptr->assign(o);
	}
	template <class O>
	void assign_array(const O& o)
	{
		a_ptr->assign_array(o);
	}
	template <class O>
	void assign_element(const O& o)
	{
		a_ptr->assign_element(o);
	}

	void resize(size_t len)
	{
		if(array_details::
			wrap_array_resize_details<typename array::is_resizeable>
			::resize(a_ptr, len)) {
				a_begin = a_ptr->begin();
				len = a_ptr->length();
			}
	}

	void resize(size_t len, const T& s) // with padding
	{
		if(array_details::
			wrap_array_resize_details<typename array::is_resizeable>
			::resize(static_cast<a_t*>(a_ptr), len, s)) {
				a_begin = a_ptr->begin();
				len = a_ptr->length();
			}
	}

	//! Reshape is same as resize for 1-d arrays
	void reshape(size_t len) { resize(len); }
	void reshape(size_t len, const T& s) { resize(len, s); }

	void clear() { resize(0); }

	typedef typename types::t_if<typename array::is_writeable,
		a_best_iterator, types::not_a_type>::type iterator;

	typedef a_const_iterator const_iterator;

	typedef typename types::t_if<typename array::is_writeable,
		a_best_reverse_iterator,
		types::not_a_type>::type reverse_iterator;

	typedef a_const_reverse_iterator const_reverse_iterator;

	typedef typename A::iter_border_walker iter_border_walker;

	typedef a_best_iterator best_iterator;
	typedef typename std::iterator_traits<best_iterator>::
		reference best_reference;
	typedef typename std::iterator_traits<const_iterator>::
		reference const_reference;
	typedef best_reference reference;

	best_iterator begin() { return a_begin; }
	best_iterator end() { return a_ptr->end(); }
	const_iterator begin() const { return const_iterator(a_begin); }
	const_iterator end() const { return a_ptr->end(); }

	a_best_reverse_iterator rbegin() { return a_ptr->rbegin(); }
	a_best_reverse_iterator rend() { return a_ptr->rend(); }
	const_reverse_iterator rbegin() const { return a_ptr->rbegin(); }
	const_reverse_iterator rend() const { return a_ptr->rend(); }

	typename types::apply_const<T, types::is_const<A> >::type c_ptr()
	{
		return array_details::
			wrap_array_ptr_details<typename array::has_c_ptr, T>
			::c_ptr(a_ptr);
	}

	const T* c_ptr() const
	{
		return array_details::
			wrap_array_ptr_details<typename array::has_c_ptr, T>
			::const_c_ptr(a_ptr);
	}

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return len; }
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/

	iter_border_walker first_to_last() const { return a_ptr->first_to_last(); }
	iter_border_walker begin_to_end() const { return a_ptr->begin_to_end(); }

/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	//! Returns the const element found at position offset
	best_reference operator[]
		(typename tool::brackets_arg i)
	{
		CHECK(i >= 0 && i < length(), erange);
		typedef typename tool::template brackets_c<best_reference> toolf;
		return toolf::f(a_begin, i);
	}

	//! Returns the element found at position offset
	const_reference operator[]
		(typename tool::brackets_arg i) const
	{
		CHECK(i >= 0 && i < length(), erange);
		typedef typename tool::template brackets_c<best_reference> toolf;
		return toolf::f(a_begin, i);
	}
/**@}*/

/** @name Special members
@{*/
	void setref(A& a)
	{
		a_ptr = &a;
		//a_begin = a.begin();
		a_begin = a_ptr->begin();
		len = a.length();
	}
	A& getref() { return *a_ptr; }

	void init(A& a)
	{
		setref(a);
	}
	void init(const array& o)
	{
		a_ptr = o.a_ptr;
		//a_begin = o.a_begin;
		a_begin = a_ptr->begin();
		len = o.len;
	}
	template<class J>
	void init(J& a) // TODO: const weirdness in ice requires this
	{
		a_ptr = &a;
		//a_begin = a.begin();
		a_begin = a_ptr->begin();
		len = a.length();
	}


	template <class X, class Y>
	friend struct array_details::wrap_array_overlap_impl;

	using array_details::wrap_array_overlap_impl<
		this_type,
		typename types::t_eq<ATTR, data::force_wrap_array_attr>::type>::overlap;

	operator A&() { return *a_ptr; }
	operator typename types::apply_const<A>::type&() const { return *a_ptr; }
/**@}*/

/** @name Constructors
@{*/
	//! Default constructor
	array() { types::r_if<prv_is_nice>(a_ptr, types::skip()) = 0; len = 0; }

	//! construction from the reference arrays
	array(A& a) : a_ptr(&a) {
		a_begin = a_ptr->begin(); 
		len = a.length(); 
	}

	// construction from const reference arrays for ice
	array(prv_const_ice_a a) : a_ptr(&a) {
		a_begin = a_ptr->begin(); 
		len = a.length(); 
	}

	//! copy constructor
	array(const array& o) 
		: a_ptr(o.a_ptr) { a_begin = a_ptr->begin(); len = o.len; }
/**@}*/


/** @name filler constructors
@{*/
	//! unused constructor with size_type
	array(size_t) {}

	//! unused constructor with size_type and T& or A&
	template <class J, class D>
	array(size_t, const array<J, D>&) {}

	//! unused constructor with size_type and T*
	array(size_t, const T*) {}

	//! unused constructor with other type array
	template<class J, class S>
	array(const array<J, S>& a) { init(a.derived()); }
	//! unused constructor with other type array
	template<class J, class S>
	array(array<J, S>& a) { init(a.derived()); }

/**@}*/

/** @name Assignement Operators
@{*/
	/**
	 * \brief Copy-Assign another array of identical type
	 *
	 * eg:
	 * \code ivl::array<int> a(10, 0);
	 * ivl::array<int> b;
	 * b = a; \endcode
	 */
	using base_class::operator=;

	this_type& operator=(const nice_this_type& a)
	{
		common_base_class::operator=(a);
		return *this;
	}
	this_type& operator=(const ice_this_type& a)
	{
		init(a);
		return *this;
	}

/**@}*/

	//! destructor
	~array() { }

};

namespace array_details {

template <>
struct wrap_array_resize_details<types::t_false>
{
	template <class A, class S>
	static inline
	bool resize(A* a, const S& l) { return false; }

	template <class A, class S, class T>
	static inline
	bool resize(A* a, const S& l, const T& t) { return false; }
};

template <>
struct wrap_array_resize_details<types::t_true>
{
	template <class A, class S>
	static inline
	bool resize(A* a, const S& l) { a->resize(l); return true; }

	template <class A, class S, class T>
	static inline
	bool resize(A* a, const S& l, const T& t) { a->resize(l, t); return true; }
};

template <class T>
struct wrap_array_ptr_details <types::t_false, T>
{
	template <class A>
	static inline T* c_ptr(A* a) { return 0; }
	template <class A>
	static inline const T* c_ptr(const A* a) { return 0; }
};

template <class T>
struct wrap_array_ptr_details <types::t_true, T>
{
	template <class A>
	static inline T* c_ptr(A* a) { return a->c_ptr(); }
	template <class A>
	static inline const T* c_ptr(const A* a) { return a->c_ptr(); }
};

template <class D>
struct wrap_array_overlap_impl<D, types::t_true>
{
	template <class A>
	bool overlap(const A& a) const { return false; }
	template <class A>
	bool self_overlap(const A& a) const { return false; }

};

template <class D>
struct wrap_array_overlap_impl<D, types::t_false>
{
private:
	const D& d() const { return static_cast<const D&>(*this); }
public:
	template <class A>
	bool overlap(const A& a) const { return d().a_ptr->overlap(a); }
	template <class A>
	bool self_overlap(const A& a) const { return d().a_ptr->overlap(a); } //TODO: @@@@!!! check!
};

} /* namespace array_details */
