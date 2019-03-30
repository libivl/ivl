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
struct mask_tools
{
	template<class A>
	static void shrink(A& a, size_t j) { }

	template<class A_IT, class B_IT>
	static size_t cut(A_IT a, B_IT b, B_IT b_end) { return 0; }
};

template<>
struct mask_tools<true>
{
	template<class A>
	static void shrink(A& a, size_t j)
	{
		 a.resize(a.length() - j);
	}

	template<class A_IT, class B_IT>
	static size_t cut(A_IT a, B_IT b, B_IT b_end);
};

template<class A_IT, class B_IT>
size_t mask_tools<true>::cut(A_IT a, B_IT b, B_IT b_end)
{
	size_t cut_size = 0;

	while(!*b && b != b_end) {
		++b;
		++a;
	}
	A_IT wa = a;

	while(1) {
		while(b != b_end && *b) {
			++b;
			++a;
			cut_size++;
		}
		if(b != b_end) {
			*wa = *a;
			++wa;
			++a;
		}
		else
			break;
	}
	return cut_size;
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
class array<T, data::mask<A, B, DERIVED_INFO> >
	:
	public array_common_base<
		array<T, data::mask<A, B, DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::mask<A, B, DERIVED_INFO> > >::type>
{

private:
	typedef array_common_base<array<T,
		data::mask<A, B, DERIVED_INFO> > > common_base_class;

	typedef typename types::best_iterator<A>::type a_best_iterator;

	//TODO: need a simple redesign::
	//make b_begin iterator to point to the first EXISTANT element,
	//and then, do not allow before-begin access.
	//that was, past_end_capable will probably be unnecessary,
	//and if the access is precomputed on array creation,
	//it will (probably) be good. otherwise compute on any begin() call.
	//in any case it will not be slower and may be faster.

	//TODO: check if this is the best design::
	typedef auto_past_end_capable_iterator<
		typename B::const_iterator> b_iterator;
	//typedef typename B::const_iterator b_iterator;

	// used to disable some types. TODO: test that not_a_type actually throws an error and
	// consider explicitly making the default constructor private.
	struct not_a_type { template<class X, class Y, class Z> not_a_type(X x, Y y, Z z); };

	typedef typename types::t_and_3<
			types::t_not<types::is_const<A> >,
			typename A::is_writeable,
			typename A::is_resizeable>
			::type is_content_resizeable;

	typedef typename array_details::
		mask_tools<array::is_content_resizeable::value> mask_tool;

	A* a;
	const B* b;
	a_best_iterator a_end;
	b_iterator b_end;
	ptrdiff_t len;

protected:
	template <class J, class D>
	void copy_or_cut(const array<J, D>& o)
	{
		if(is_content_resizeable::value && o.begin() == o.end() && len != 0) {

			mask_tool::shrink(*a,
				mask_tool::cut(a->begin(), b->begin(), b_end));
			b_end = b->begin();
			len = 0;

		} else {
			static_cast<common_base_class&>(*this).assign_array(o);
		}
	}

public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename a_best_iterator::reference best_reference;
	typedef typename a_best_iterator::reference reference;
	typedef typename A::const_iterator::reference const_reference;

	typedef typename types::derive<this_type>::type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	using base_class::derived;

	struct iter_border_walker
	{
		typename A::iter_border_walker iba;
		typename B::iter_border_walker ibb;
		bool first_to_last;

		iter_border_walker() {}
		iter_border_walker(ptrdiff_t) : iba(0), ibb(0), first_to_last(false) { }
		template <class IT>
		iter_border_walker(const IT& beg_it, const IT& end_it)
		:
		iba(data::iterator_extended_traits<typename IT::a_iterator>::
				get_iter_border_walker(beg_it.a, end_it.a)),
		ibb(data::iterator_extended_traits<typename IT::b_iterator>::
				get_iter_border_walker(beg_it.b, end_it.b)),
		first_to_last(false) { }
	};

	template <bool CONST>
	class iterator_type
	: public data::data_details::
		iter_operator_expander<iterator_type<CONST>, T, CONST,
			typename types::remove_const<
				typename a_best_iterator::reference>::type >,
		public types::border_walker_iterator_identifier
	{
	private:
		template <bool C> friend class iterator_type;
		friend class array;

		friend class iter_border_walker;

		template <class X, class Y, bool C, class Z> 
		friend class data::data_details::iter_operator_expander;

		//friend class data::data_details::iter_operator_expander
		//	<iterator_type<CONST>, T, CONST>;

		typedef typename types::apply_const<T, types::t_expr<CONST> >
			::type best_value_type;

		// this class is used to disable specific specialization members
		class not_a_type { };

		typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
			types::code_word<> >::type invalid_if_const;

		typedef typename types::t_if<types::t_expr<CONST>,
			typename A::const_iterator, typename 
				types::best_iterator<A>::type>::type a_iterator;

		typedef typename a_iterator::reference prv_reference;

		a_iterator a;
		b_iterator b;
		b_iterator b_end;
		b_iterator b_rend;

	protected:
		inline const_reference base(
			types::code_word<> ok = types::code_word<>()) const
			{ return (*a); }

		inline prv_reference base(
			invalid_if_const disable = invalid_if_const())
			{ return (*a); }

	public:
		typedef iterator_type<CONST> this_type;

		// iterator_traits
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef typename types::apply_const<T, types::t_expr<CONST> >
			::type access_value_type;
		typedef ptrdiff_t difference_type;
		typedef access_value_type* pointer;
		typedef typename a_iterator::reference reference;

		// border walker
		typedef typename array::iter_border_walker iter_border_walker;

		// constructors
		iterator_type() { }

		iterator_type(const this_type& it)
		: a(it.a), b(it.b), b_end(it.b_end), b_rend(it.b_rend) { }

		template <bool C>
		iterator_type(const iterator_type<C>& it)
		: a(it.a), b(it.b), b_end(it.b_end), b_rend(it.b_rend) { }

		iterator_type(const a_iterator& a, const b_iterator& b,
			const b_iterator& b_end, const b_iterator& b_rend)
			: a(a), b(b), b_end(b_end), b_rend(b_rend) { }

		// members

		// increment-decrement
		this_type& operator++()
		{
			difference_type cnt = 1;
			++b;
			while(b != b_end && !*b) { ++b; ++cnt; }
			a += cnt;
			return *this;
		}
		this_type& operator--()
		{
			difference_type cnt = 1;
			--b;
			while(b != b_rend && !*b) { --b; ++cnt; }
			a -= cnt;
			return *this;
		}

		this_type operator++(int) { this_type t(*this); ++(*this); return t; }
		this_type operator--(int) { this_type t(*this); --(*this); return t; }

		// += operator w/o random access. implemented only for (iterator + 1)
		this_type& operator +=(size_t j)
		{
			CHECK(j == 1, ecomp);
			++(*this);
			return *this;
		}
		this_type& operator -=(size_t j)
		{
			CHECK(j == 1, ecomp);
			--(*this);
			return *this;
		}
		inline this_type operator +(size_t j) const
		{
			CHECK(j == 1, ecomp);
			this_type tmp(*this);
			++(*this);
			return tmp;
		}
		inline this_type operator -(size_t j) const
		{
			CHECK(j == 1, ecomp);
			this_type tmp(*this);
			--(*this);
			return tmp;
		}

		this_type& operator +=(iter_border_walker ib)
		{
			a += ib.iba;
			b += ib.ibb;
			if(ib.first_to_last) --(*this);
			return *this;
		}
		this_type& operator -=(iter_border_walker ib)
		{
			a -= ib.iba;
			b -= ib.ibb;
			if(ib.first_to_last) ++(*this);
			return *this;
		}
		inline this_type operator +(iter_border_walker j) const
		{
			this_type tmp(*this);
			tmp += j;
			return tmp;
		}
		inline this_type operator -(iter_border_walker j) const
		{
			this_type tmp(*this);
			tmp -= j;
			return tmp;
		}

		// difference is not implemented.
		// this iterator is not random_access.

		//copy same type iterator
		this_type& operator=(const this_type& it)
		{
			a = it.a; b = it.b; b_end = it.b_end; b_rend = it.b_rend;
			return *this;
		}
		//copy relevant type iterator
		template<bool C>
		this_type& operator=(const iterator_type<C>& it)
		{
			a = it.a; b = it.b; b_end = it.b_end; b_rend = it.b_rend;
			return *this;
		}

		bool operator==(const this_type& it) const { return (b == it.b); }
		bool operator!=(const this_type& it) const { return (b != it.b); }
		bool operator<(const this_type& it) const { return (b < it.b); }
		bool operator<=(const this_type& it) const { return (b <= it.b); }
		bool operator>(const this_type& it) const { return (b > it.b); }
		bool operator>=(const this_type& it) const { return (b >= it.b); }

		//mask-specific. moves the iterator to the first valid position
		this_type& stepfw()
		{
			difference_type cnt = 0;
			while(b != b_end && !*b) { ++b; ++cnt; }
			a += cnt;
			return *this;
		}
		//meant to return reverse iterator
		this_type& stepbk()
		{
			difference_type cnt = 0;
			while(b != b_rend && !*b) { --b; ++cnt; }
			a -= cnt;
			return *this;
		}

	};

	// typedefs for class iterators
	typedef typename types::t_if<typename array::is_writeable,
		iterator_type<false>, not_a_type>::type iterator;

	typedef iterator_type<true> const_iterator;

	typedef typename types::t_if<typename array::is_writeable,
		iterator, const_iterator>::type best_iterator;

	typedef typename types::t_if<typename array::is_writeable,
		std::reverse_iterator<iterator>, not_a_type>::
			type reverse_iterator;

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;


	iterator begin()
		{ return iterator(a->begin(), b->begin(),
							b_end, b_iterator(b->begin()) - 1).stepfw(); }

	iterator end()
		{ return iterator(a_end, b_end, b_end, b_iterator(b->begin()) - 1); }

	const_iterator begin() const
		{ return const_iterator(a->begin(), b->begin(),
								b_end, b_iterator(b->begin()) - 1).stepfw(); }

	const_iterator end() const
		{ return const_iterator(a_end, b_end, b_end, 
			b_iterator(b->begin()) - 1); }

	// reverse iterator defs
	reverse_iterator rbegin() { return reverse_iterator(end()); }

	reverse_iterator rend() { return reverse_iterator(begin()); }

	const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(end()); }

	const_reverse_iterator rend() const
		{ return const_reverse_iterator(begin()); }

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	//! in a non random-access array, length well might be slow.
	size_t length() const
	{
		if(this->len != -1)
			return this->len;

		size_t len = 0;
		for(b_iterator bit = b->begin(); bit != b_end; bit++)
			if(*bit)
				len++;

		return len;
	}
	size_t length()
	{
		if(this->len != -1)
			return this->len;

		size_t len = 0;
		for(b_iterator bit = b->begin(); bit != b_end; bit++)
			if(*bit)
				len++;

		this->len = len;
		return len;
	}
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	size_type size() { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
	size_t numel() { return length(); }

	void resize(size_t l)
	{
		calc_length();
		if(l == 0)
			copy_or_cut(array<T, data::empty<> >());
		else
			CHECK(length() == l, ecomp);
	}


	//! Calculates and stores the length of this array in a "cache" variable.
	//! It is not pre-calculated by default cause this could halve the
	//! mask-array's performance in some single operations, like copying
	//! from-to the mask-array, since length is not needed there (iterators
	//! are used).
	this_type& calc_length() { len = length(); return *this; }
/**@}*/


	iter_border_walker first_to_last() const
	{
		iter_border_walker ib;
		ib.iba = a->begin_to_end();
		ib.ibb = b->begin_to_end();
		ib.first_to_last = true;
		return ib;
	}
	iter_border_walker begin_to_end() const
	{
		iter_border_walker ib;
		ib.iba = a->begin_to_end();
		ib.ibb = b->begin_to_end();
		ib.first_to_last = false;
		return ib;
	}

	void init(A& a0, const B& b0)
	{
		a = &a0;
		b = &b0;
		a_end = a0.end();
		b_end = b0.end();
	}

	void init(const array& o)
	{
		a = o.a;
		b = o.b;
		a_end = o.a_end;
		b_end = o.b_end;
	}

/** @name Constructors
@{*/
	//! The only constructor
	array(A& a, const B& b) : a(&a), b(&b), a_end(a.end()), b_end(b.end()),
		len(-1)
	{
	}

	//! Copy constructor
	array(const this_type& o) : a(o.a), b(o.b), a_end(o.a_end), b_end(o.b_end),
		len(o.len)
	{
	}

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

	template <class D>
	bool self_overlap(const D& d) const
	{
		return d.overlap(*a) || d.overlap(*b);
	}

	template <class J, class P>
	derived_type& assign_array(const array<J, data::empty<P> >& o)
	{
		copy_or_cut(o); // will always fallback to cut
		return this->derived();
	}

	template<class D>
	derived_type& assign_array(const D& o)
	{
		copy_or_cut(o);
		return this->derived();
	}

/**@}*/


/** @name Assignement Operators
@{*/
	using common_base_class::operator=;

	this_type& operator=(const this_type& o) // copy operator
	{
		copy_or_cut(o);
		return *this;
	}


/**@}*/

};

