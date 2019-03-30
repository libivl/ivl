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

template<bool IS_CONTENT_RESIZEABLE>
struct indirect_tools
{
	template<class A>
	static void shrink(A& a, size_t j) { }

	template<class A_IT, class B>
	static size_t cut(A_IT a, const B& b, size_t len) { return 0; }
};

template<>
struct indirect_tools<true>
{
	template<class A>
	static void shrink(A& a, size_t j)
	{
		 a.resize(j);
	}

	template<class A_IT, class B>
	static size_t cut(A_IT a, const B& b, size_t len);
};

template<class A_IT, class B>
size_t indirect_tools<true>::cut(A_IT a, const B& b, size_t len)
{
	// len: length of a before cut. different meaning in other specializations.
	array<size_t, mem> c(b);
	if(c.length() == 0)
		return len;
	std::sort(c.begin(), c.end());

	size_t i = 0;
	size_t j = 0;

	for(size_t i = 0; i < len && i != c[0]; ++i, ++a) { ++j; }

	array<size_t, mem>::const_iterator cp = c.begin();
	array<size_t, mem>::const_iterator cp_e = c.end();

	++cp;
	while(*cp == *(cp - 1) && cp != cp_e)
		++cp;

	A_IT wa = a;

	for(++i, ++a; i < len; ++i, ++a) {
		if(i != *cp) {
			*wa = *a;
			++wa;
			++j;
		}
		else {
			++cp;
			while(*cp == *(cp - 1) && cp != cp_e) {
				++cp;
			}
		}
	}

	return j;
}

} /* namespace array_details */

/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 class A,
		 class B,
		 class DERIVED_INFO
	     >
class array<T, data::indirect<A, B, DERIVED_INFO> >
	:

	public array_common_base<
		array<T, data::indirect<A, B, DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::indirect<A, B, DERIVED_INFO> > >::type>
{

private:
	typedef array_common_base<array<T,
		data::indirect<A, B, DERIVED_INFO> > > common_base_class;

	typedef typename types::is_ref<B>::type prv_b_ref;
	typedef typename types::bare_type<B>::type prv_b;
	typedef typename types::t_if<prv_b_ref, 
		const typename types::bare_type<B>::type*, 
		internal::relaxed_pointer_face<
			typename types::bare_type<B>::type> >
			::type prv_b_type;


	typedef typename types::t_if<typename array::is_writeable,
		typename A::best_iterator,
		typename A::const_iterator>::type a_best_iterator;

	typedef typename prv_b::const_iterator b_iterator;

	// used to disable some types. TODO: test that not_a_type actually throws an error
	// and consider explicitly making the default constructor private.
	class not_a_type {};
	struct skip_assign { template<class X> void assign_array(X t) const {} };

	typedef typename types::t_if<types::is_const<A>, 
		typename types::remove_const<A>::type, not_a_type>::type prv_second_init_a;

	typedef typename types::t_and_3<
			types::t_not<types::is_const<A> >,
			typename A::is_writeable,
			typename A::is_resizeable>
			::type is_content_resizeable;

	typedef typename array_details::
		indirect_tools<array::is_content_resizeable::value> indirect_tool;

	A* a;
	prv_b_type b;
	size_t len; //used to allow cut modify the length.

protected:
	template <class J, class D>
	void copy_or_cut_impl(const array<J, D>& o)
	{
		if(is_content_resizeable::value && o.begin() == o.end() && len != 0) {

			indirect_tool::shrink(*a,
				indirect_tool::cut(a->begin(), *b, a->length()));

			len = 0;

		} else {
			// for non-const: do not do nothing!
			types::r_if<typename this_type::is_writeable>(
				static_cast<common_base_class&>(*this), skip_assign()).assign_array(o);
		}
	}
	template <class J, class D>
	void copy_or_cut(const array<J, D>& o)
	{
		copy_or_cut_impl(o);
	}
	template <class J, class P2, class D>
	void copy_or_cut(const array<J, data::indirect<A, P2, D> >& o)
	{
		if(!a)
			this->init(o.get_ref_1(), o.get_ref_2());
		else
			copy_or_cut_impl(o);
	}
	template <class J, class P2, class D>
	void copy_or_cut(const array<J, data::indirect<
		prv_second_init_a, P2, D> >& o)
	{
		if(!a)
			this->init(o.get_ref_1(), o.get_ref_2());
		else
			copy_or_cut_impl(o);
	}


public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	using base_class::derived;

	//! declared as t_true if the array = empty operation (cut) is allowed.
	typedef is_content_resizeable is_cuttable;

	// special to this type
	typedef tuple<A&, const prv_b&> data_init_arg;
	//typedef tuple<A&, B> data_init_arg;


	template <bool CONST>
	class iterator_type
	: public data::data_details::
		rnd_iter_operator_expander<iterator_type<CONST>, T, CONST,
			typename types::remove_const<
				typename a_best_iterator::reference>::type>
	{
	private:
		template <bool C> friend class iterator_type;

		template <class X, class Y, bool C, class Z>
		friend class data::data_details::rnd_iter_operator_expander;

		template <class X, class Y, bool C, class Z>
		friend class data::data_details::iter_operator_expander;

		typedef typename types::apply_const<T, types::t_expr<CONST> >
			::type best_value_type;

		typedef typename types::apply_const<
			typename a_best_iterator::reference, types::t_expr<CONST> >
			::type best_ref_type;

		// this class is used to disable specific specialization members
		class not_a_type { };

		typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
			types::code_word<> >::type invalid_if_const;

		typedef typename types::t_if<types::t_expr<CONST>,
			typename A::const_iterator, a_best_iterator>::type a_iterator;

		a_iterator a;
		b_iterator b;

	protected:
		inline typename types::apply_const<best_ref_type>::type base(
			types::code_word<> ok = types::code_word<>()) const
			{ return (a[*b]); }
//TODO!!!! make it random access only if b is random access
// otherwise make it non-random access.
// make it complain if a is non-random access.
		inline best_ref_type base(
			invalid_if_const disable = invalid_if_const())
			{ return (a[*b]); }

		inline typename types::apply_const<best_ref_type>::type base(size_t j,
			types::code_word<> ok = types::code_word<>()) const
			{ return (a[*(b + j)]); }

		inline best_ref_type base(size_t j,
			invalid_if_const disable = invalid_if_const())
			{ return (a[*(b + j)]); }

	public:
		typedef iterator_type<CONST> this_type;

		// iterator_traits
		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef best_value_type* pointer;
		typedef best_ref_type reference;

		// constructors
		iterator_type() { }
		iterator_type(const this_type& it)
		: a(it.a), b(it.b) { }
		template <bool C>
		iterator_type(const iterator_type<C>& it)
		: a(it.a), b(it.b) { }
		iterator_type(const a_iterator& a, const b_iterator& b)
			: a(a), b(b) { }

		// members

		// increment-decrement
		this_type& operator++() { ++b; return *this; }
		this_type& operator--() { --b; return *this; }

		this_type operator++(int) { this_type t(*this); ++(*this); return t; }
		this_type operator--(int) { this_type t(*this); --(*this); return t; }

		// random access.

		// X can be either size_t or B::iter_bound_mover
		template<class X>
		this_type& operator +=(X j) { b += j; return *this; }

		template<class X>
		this_type& operator -=(X j) { b -= j; return *this; }

		template<class X>
		inline this_type operator +(X j) const
		{
			this_type tmp(*this);
			tmp += j;
			return tmp;
		}
		template<class X>
		inline this_type operator -(size_t j) const // TODO: @@@ cant i X? wrap iter has prob in 'code'.
		{
			this_type tmp(*this);
			tmp -= j;
			return tmp;
		}

		// difference.
		ptrdiff_t operator-(const this_type& it) const
		{
			return b - it.b;
		}

		//copy same type iterator
		this_type& operator=(const this_type& it)
		{
			a = it.a; b = it.b;
			return *this;
		}
		//copy relevant type iterator
		template<bool C>
		this_type& operator=(const iterator_type<C>& it)
		{
			a = it.a; b = it.b;
			return *this;
		}

		bool operator==(const this_type& it) const { return (b == it.b); }
		bool operator!=(const this_type& it) const { return (b != it.b); }
		bool operator<(const this_type& it) const { return (b < it.b); }
		bool operator<=(const this_type& it) const { return (b <= it.b); }
		bool operator>(const this_type& it) const { return (b > it.b); }
		bool operator>=(const this_type& it) const { return (b >= it.b); }

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

	typedef ptrdiff_t iter_border_walker;

	best_iterator begin()
		{ if(is_cuttable::value && len == 0)
				return best_iterator(a->begin(), b->end());
			else return best_iterator(a->begin(), b->begin()); }

	best_iterator end()
		{ return best_iterator(a->begin(), b->end()); }

	const_iterator begin() const
		{ if(is_cuttable::value && len == 0)
				return const_iterator(a->begin(), b->end());
			else return const_iterator(a->begin(), b->begin()); }

	const_iterator end() const
		{ return const_iterator(a->begin(), b->end()); }

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
		return (*a)[(*b)[j]];
	}
	typename const_iterator::reference operator[](size_t j) const
	{
		return (*a)[(*b)[j]];
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

	void resize(size_t l) { CHECK(length() == l, ecomp); }

	iter_border_walker first_to_last() { return b.length() - 1; }
	iter_border_walker begin_to_end() { return b.length(); }


	/*
	void init(A& a0, const B& b0)
	{
		a = &a0;
		b = &b0;
		len = b0.length();
	}
	*/
	template<class I>
	void init(A& a0, const I& b0)
	{
		a = &a0;
		b = &b0;
		len = b0.length();
	}

	void init(size_t sz, data_init_arg d)
	{
		a = &d.v1;
		b = &d.v2;
		len = d.v2.length();
	}

	void init(const array& o)
	{
		a = o.a;
		b = o.b;
		len = o.len;
	}

	template <class J, class P2, class D>
	void init(const array<J, data::indirect<A, P2, D> >& o)
	{
		a = &o.get_ref_1();
		b = &o.get_ref_1();
		len = o.length();
	}

	template <class J, class P2, class D>
	void init(const array<J, data::indirect<prv_second_init_a, P2, D> >& o)
	{
		a = &o.get_ref_1();
		b = &o.get_ref_1();
		len = o.length();
	}



/** @name Constructors
@{*/
	array() { a = NULL; }

	//! Constructor with full array, TODO: only available when b is createable, non reference!
	array(A& a) : a(&a), b(rng(0, a.length()-1)), len(a.length()) { }
	
	//! The only constructor
	array(A& a, const prv_b& b) : a(&a), b(&b), len(b.length()) { }

	//The same with data init arg
	array(size_t sz, data_init_arg d) : a(&d.v1), b(&d.v2), len(d.v2.length()) { }
	
	//The same constructor with template
	template<class I>
	array(A& a, const I& b) : a(&a), b(&b), len(b.length()) { }

	//! Copy constructor
	array(const this_type& o) : a(o.a), b(o.b), len(o.len) {}

	// Constructor from another indirect array
	template <class J, class P2, class D>
	array(const array<J, data::indirect<A, P2, D> >& o)
		: a(&o.get_ref_1()), b(&o.get_ref_2()), len(o.length()) { }

	template <class J, class P2, class D>
	array(const array<J, data::indirect<prv_second_init_a, P2, D> >& o)
		: a(&o.get_ref_1()), b(&o.get_ref_2()), len(o.length()) { }

/**@}*/

    //! destructor
	~array() { }

/** @name Special Members
@{*/
	// exclusive to indirect array
	A& get_ref_1() const { return *a; }
	const prv_b& get_ref_2() const { return *b; }
	//TODO: may be better or just possible is several cases as elem func.
	//return value could also be templated.
	template <class J, class P>
	size_array merge_idx(const array<J, P>& idx) const
	{
		size_array sz(idx.length());
		for(size_t i=0;i<sz.length();i++)
			sz[i] = (*b)[idx[i]];
		return sz;
	}
	//

	template <class D>
	bool overlap(const D& d) const
	{
		return a->overlap(d);
	}

	template <class D>
	bool self_overlap(const D& d) const
	{
		return d.overlap(*a) || d.overlap(*b);
	}

	/*
	TODO: wipe this completely. Cannot detect anything here anyway.
	template <class J, class P>
	derived_type& assign_array(const array<J, data::empty<P> >& o)
	{
		copy_or_cut(o); // will always fallback to cut
		return this->derived();
	}
	*/

	template<class D>
	derived_type& assign_array(const D& o)
	{
		copy_or_cut(o);
		return this->derived();
	}
/**@}*/


/** @name Assignement Operators
@{*/

	//using common_base_class::operator=;
	template<class K>
	derived_type& operator=(const K& o)
	{
		// avoid the safety check when we just need to assign
		// TODO: check about this all, espec. const K&. and what happens
		// when we derive to higher class, e.g. image, what is called. 
		// (esp. for subarray).
		if(!a) 
			this->assign(o);
		else 
			common_base_class::operator=(o);
		return this->derived();
	}

	this_type& operator=(const this_type& o) // copy operator
	{
		copy_or_cut(o);
		return *this;
	}

/**@}*/

	//todo: either make this (rvalue) a rule or not at all
	//this_type& rvalue() const { return *const_cast<this_type*>(this); }


};

