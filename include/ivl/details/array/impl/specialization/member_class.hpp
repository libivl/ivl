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
struct member_array_resize_details { };

template <class HAS_REF, class TP>
struct member_tool
{
	template<class T, class Y>
	static inline TP get_reference(T& x, Y& y) { return x; }
};
template <class TP>
struct member_tool<types::t_false, TP>
{
	template<class T, class Y>
	static inline TP get_reference(T& x, Y& y) { return TP(x, y); }
};

} /* namespace array_details */

/**
 * Member array is a wrapper that creates a virtual array containing
 * a certain member of a struct from the members of the original array.
 */
template <class T,
		 class A,
		 class DERIVED_INFO
	     >
class array<T, data::member<A, T, DERIVED_INFO> >
	:
	public array_common_base<
		array<T, data::member<A, T, DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::member<A, T, DERIVED_INFO> > >::type>
{

private:
	typedef array_common_base<array<T,
		data::member<A, T, DERIVED_INFO> > > common_base_class;

	typedef typename types::t_if<typename array::is_writeable,
			typename types::best_iterator<A>::type,
			typename A::const_iterator>::type a_best_iterator;

	typedef typename types::t_if<typename array::is_writeable,
			typename types::best_reverse_iterator<A>::type,
			typename A::const_reverse_iterator>::type a_best_reverse_iterator;

	typedef typename A::this_array_type a_t;

	typedef typename A::elem_type a_elem_t;

	typedef T a_elem_t::* m_type;

	// check if the source iterator gives reference or value
	typedef typename types::
		is_ref<typename a_best_iterator::reference>::type has_src_ref;

	// TODO: should wrap the a_best_iterator::reference or do something clever, also should mind const
	typedef typename types::t_if<has_src_ref, T&, T>::type best_base_ref_type;

protected:
	typedef typename array::has_random_access prv_has_random_access;

	typedef array_details::elem_func_tools<T,
		prv_has_random_access::value> tool;

	//friend class tool::not_a_type; // allow disabled types only in our class
	class not_a_type {};

	A* a;
	m_type m;

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


	//

	template <bool CONST>
	class iterator_type
	: public data::data_details::
		rnd_iter_operator_expander<iterator_type<CONST>, T, CONST, best_base_ref_type>
	{
	private:
		template <bool C> friend class iterator_type;

		template <class X, class Y, bool C, class Z>
		friend class data::data_details::rnd_iter_operator_expander;

		template <class X, class Y, bool C, class Z>
		friend class data::data_details::iter_operator_expander;

		typedef typename types::apply_const<T, types::t_expr<CONST> >
			::type best_value_type;

		// TODO: should wrap the a_best_iterator::reference or do something clever, also should mind const
		typedef typename types::t_if<has_src_ref,
			typename types::apply_const<T&, types::t_expr<CONST> >::type,
			const internal::reference_face<const T, iterator_type<CONST> > >
				::type best_ref_type;

		// TODO: same as above
		typedef typename types::t_if<has_src_ref,
			typename types::apply_const<T*, types::t_expr<CONST> >::type,
			const internal::pointer_face<const T> > 
				::type best_ptr_type;
	
		// this class is used to disable specific specialization members
		class not_a_type { };

		typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
			types::code_word<> >::type invalid_if_const;

		typedef typename types::t_if<types::t_expr<CONST>,
			typename A::const_iterator, a_best_iterator>::type a_iterator;

		a_iterator a;
		m_type m;

	protected:
		inline typename types::apply_const<best_ref_type>::type base(
			types::code_word<> ok = types::code_word<>()) const
			{ 
				return array_details::member_tool<has_src_ref,
					typename types::apply_const<best_ref_type>::type>::
						get_reference(((*a).*m), *this); 
			}
//TODO!!!! make it random access only if b is random access
// otherwise make it non-random access.
// make it complain if a is non-random access.
		inline best_ref_type base(
			invalid_if_const disable = invalid_if_const())
			{ 
				return array_details::member_tool<has_src_ref,
					best_ref_type>::
						get_reference(((*a).*m), *this); 
			}

		inline typename types::apply_const<best_ref_type>::type base(size_t j,
			types::code_word<> ok = types::code_word<>()) const
			{ 
				return array_details::member_tool<has_src_ref,
					typename types::apply_const<best_ref_type>::type>::
						get_reference((a[j].*m), *this); 
			}

		inline best_ref_type base(size_t j,
			invalid_if_const disable = invalid_if_const())
			{ 
				return array_details::member_tool<has_src_ref,
					best_ref_type>::
						get_reference((a[j].*m), *this); 
			}

	public:
		typedef iterator_type<CONST> this_type;

		// iterator_traits
		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef best_ptr_type pointer;
		typedef best_ref_type reference;

		// constructors
		iterator_type() { }
		iterator_type(const this_type& it)
		: a(it.a), m(it.m) { }
		template <bool C>
		iterator_type(const iterator_type<C>& it)
		: a(it.a), m(it.m) { }
		iterator_type(const a_iterator& a, const m_type& m)
			: a(a), m(m) { }

		// members

		// increment-decrement
		this_type& operator++() { ++a; return *this; }
		this_type& operator--() { --a; return *this; }

		this_type operator++(int) { this_type t(*this); ++(*this); return t; }
		this_type operator--(int) { this_type t(*this); --(*this); return t; }

		// random access.

		// X can be either size_t or B::iter_bound_mover
		template<class X>
		this_type& operator +=(X j) { a += j; return *this; }

		template<class X>
		this_type& operator -=(X j) { a -= j; return *this; }

		template<class X>
		inline this_type operator +(X j) const
		{
			this_type tmp(*this);
			tmp += j;
			return tmp;
		}
		template<class X>
		inline this_type operator -(X j) const
		{
			this_type tmp(*this);
			tmp -= j;
			return tmp;
		}

		// difference.
		ptrdiff_t operator-(const this_type& it) const
		{
			return a - it.a;
		}

		//copy same type iterator
		this_type& operator=(const this_type& it)
		{
			a = it.a; m = it.m;
			return *this;
		}
		//copy relevant type iterator
		template<bool C>
		this_type& operator=(const iterator_type<C>& it)
		{
			a = it.a; m = it.m;
			return *this;
		}

		bool operator==(const this_type& it) const { return (a == it.a); }
		bool operator!=(const this_type& it) const { return (a != it.a); }
		bool operator<(const this_type& it) const { return (a < it.a); }
		bool operator<=(const this_type& it) const { return (a <= it.a); }
		bool operator>(const this_type& it) const { return (a > it.a); }
		bool operator>=(const this_type& it) const { return (a >= it.a); }

	};

	// typedefs for class iterators
	typedef typename types::t_if<typename array::is_writeable,
		iterator_type<false>, not_a_type>::type iterator;

	typedef iterator_type<true> const_iterator;

	typedef typename types::t_if<types::t_eq<iterator, not_a_type>,
		const_iterator, iterator>::type best_iterator;

	typedef typename best_iterator::reference best_reference;
	typedef best_reference reference;
	typedef typename const_iterator::reference const_reference;

	typedef std::reverse_iterator<iterator> reverse_iterator;

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename data::iterator_extended_traits<a_best_iterator>
		::iter_border_walker iter_border_walker;

	best_iterator begin() { return best_iterator(a->begin(), m); }
	best_iterator end() { return best_iterator(a->end(), m); }

	const_iterator begin() const 
		{ return const_iterator(a->begin(), m); }

	const_iterator end() const
		{ return const_iterator(a->end(), m); }

	// reverse iterator defs
	reverse_iterator rbegin() { return reverse_iterator(end()); }

	reverse_iterator rend() { return reverse_iterator(begin()); }

	const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(end()); }

	const_reverse_iterator rend() const
		{ return const_reverse_iterator(begin()); }


	using common_base_class::operator[];

	// todo: resolve when b has no random access
	typename best_iterator::reference operator[](size_t j)
	{
		return (*a)[j].*m;
	}
	typename const_iterator::reference operator[](size_t j) const
	{
		return (*a)[j].*m;
	}

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return a->length(); }
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/
	void resize(size_t len)
	{
		array_details::
			member_array_resize_details<typename array::is_resizeable>
			::resize(m, a, len);
	}

	void resize(size_t len, const T& s) // with padding
	{
		array_details::
			member_array_resize_details<typename array::is_resizeable>
			::resize(m, static_cast<a_t*>(a), len, s);
	}

	//! Reshape is same as resize for 1-d arrays
	void reshape(size_t len) { resize(len); }
	void reshape(size_t len, const T& s) { resize(len, s); }

	void clear() { resize(0); }


	iter_border_walker first_to_last() { return a->first_to_last(); }
	iter_border_walker begin_to_end() { return a->begin_to_end(); }


	void init(A& a0, m_type m0)
	{
		a = &a0;
		m = m0;
	}

	void init(const array& o)
	{
		a = o.a;
		m = o.m;
	}

/** @name Constructors
@{*/
	//! The only constructor
	array(A& a, m_type m) : a(&a), m(m) { }

	//! Copy constructor
	array(const this_type& o) : a(o.a), m(o.m) {}

/**@}*/

/** @name filler constructors
@{*/
	array() {}

	//! unused constructor with size_type
	array(size_t) {}

	//! unused constructor with size_type and T& or A&
	template <class J, class D>
	array(size_t, const array<J, D>&) {}

	//! unused constructor with size_type and T*
	array(size_t, const T*) {}

	//! unused constructor with other type array
	template<class J, class S>
	array(const array<J, S>& a) {}

/**@}*/


    //! destructor
	~array() { }

/** @name Special Members
@{*/
	template <class D>
	bool overlap(const D& d) const
	{
		return a->overlap(d);
	}

	// TODO: ensure correctness.
	template <class D>
	bool self_overlap(const D& d) const
	{
		return d.overlap(*a);
	}

/**@}*/


/** @name Assignement Operators
@{*/

	using common_base_class::operator=;

	this_type& operator=(const this_type& a)
	{
		common_base_class::operator=(a);
		return *this;
	}

/**@}*/


};


namespace array_details {

template<>
struct member_array_resize_details<types::t_false>
{
	template <class T0, class E0, class A, class S>
	static inline
	bool resize(T0 E0::* pv, A* a, const S& l) { return false; }

	template <class T0, class E0, class A, class S, class T>
	static inline
	bool resize(T0 E0::* pv, A* a, const S& l, const T& t) { return false; }
};

template<>
struct member_array_resize_details<types::t_true>
{
	template <class T0, class E0, class A, class S>
	static inline
	bool resize(T0 E0::* pv, A* a, const S& l) { a->resize(l); return true; }

	template <class T0, class E0, class A, class S, class T>
	static inline
	bool resize(T0 E0::* pv, A* a, const S& l, const T& t) { 
		E0 tv;
		tv.*pv = t;
		a->resize(l, tv); 
		return true; 
	}
};

} /* namespace array_details */

