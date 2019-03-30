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
struct slice_tools
{
	template<class A>
	static void shrink(A& a, size_t j) { }

	template<class A_IT>
	static size_t cut(A_IT a, size_t, ptrdiff_t, size_t) { return 0; }
};

template<>
struct slice_tools<true>
{
	template<class A>
	static void shrink(A& a, size_t j)
	{
		 a.resize(j);
	}

	template<class A_IT>
	static size_t cut(A_IT a, size_t first, ptrdiff_t step, size_t len);
};

template<class A_IT>
size_t slice_tools<true>::cut(A_IT a, size_t first, ptrdiff_t step, size_t len)
{
	// len:length after cut. these specs are not same across specializations.
	size_t i = 0;
	size_t j = 0;

	for(size_t i = 0; j < len && i != first; ++i, ++a) { ++j; }
	first += step;

	A_IT wa = a;

	for(++i, ++a; j < len; ++i, ++a) {
		if(i != first) {
			*wa = *a;
			++wa;
			++j;
		}
		else {
			first += step;
		}
	}

	return len;
}

} /* namespace array_details */

/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 class A,
		 class DERIVED_INFO
	     >
class array<T, data::slice<A, DERIVED_INFO> >
	:
	public array_common_base<array<T,
		data::slice<A, DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::slice<A, DERIVED_INFO> > >::type>
{

private:
	typedef array_common_base<array<T,
		data::slice<A, DERIVED_INFO> > > common_base_class;

	typedef typename types::t_if<typename array::is_writeable,
		typename A::iterator,
		typename A::const_iterator>::type a_best_iterator;

	// used to disable some types. TODO: test that not_a_type actually throws an error and
	// consider explicitly making the default constructor private.
	class not_a_type { };

	typedef typename types::t_and_3<
			types::t_not<types::is_const<A> >,
			typename A::is_writeable,
			typename A::is_resizeable>
			::type is_content_resizeable;

	typedef typename array_details::
		slice_tools<array::is_content_resizeable::value> slice_tool;

	A* a;
	ivl::slice b;
	size_t end_el;

protected:
	template <class J, class D>
	void copy_or_cut(const array<J, D>& o)
	{
		if(is_content_resizeable::value &&
			o.begin() == o.end() && b.length > 0) {

			size_t newlen_a;

			if(b.stride < 0)
				newlen_a = slice_tool::cut(a->begin(),
					end_el, -b.stride, a->length() - b.length);
			else
				newlen_a = slice_tool::cut(a->begin(),
					b.start, b.stride, a->length() - b.length);

			slice_tool::shrink(*a, newlen_a);

			b.length = 0;
			end_el = b.start;

		} else {
			static_cast<common_base_class&>(*this).assign_array(o);
		}
	}
public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename a_best_iterator::reference reference;
	typedef typename A::const_reference const_reference;
	typedef reference best_reference;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	using base_class::derived;

	//! declared as t_true if the array = empty operation (cut) is allowed.
	typename types::t_and_3<
		types::t_not<types::is_const<A> >,
		typename A::is_writeable,
		typename A::is_resizeable>
		::type is_cuttable;


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
			typename A::const_iterator, typename A::iterator>::type a_iterator;

		a_iterator a;
		ptrdiff_t step;

	protected:
		inline typename types::apply_const<best_ref_type>::type base(
			types::code_word<> ok = types::code_word<>()) const
			{ return (*a); }
//TODO!!!! make it random access only if b is random access
// otherwise make it non-random access.
// make it complain if a is non-random access.
		inline best_ref_type base(
			invalid_if_const disable = invalid_if_const())
			{ return (*a); }

		inline typename types::apply_const<best_ref_type>::type base(size_t j,
			types::code_word<> ok = types::code_word<>()) const
			{ return (a[j * step]); }

		inline best_ref_type base(size_t j,
			invalid_if_const disable = invalid_if_const())
			{ return (a[j * step]); }

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
		: a(it.a), step(it.step) { }
		template <bool C>
		iterator_type(const iterator_type<C>& it)
		: a(it.a), step(it.step) { }
		iterator_type(const a_iterator& a, ptrdiff_t step)
			: a(a), step(step) { }

		// members

		// increment-decrement
		this_type& operator++() { a += step; return *this; }
		this_type& operator--() { a -= step; return *this; }

		this_type operator++(int) { this_type t(*this); ++(*this); return t; }
		this_type operator--(int) { this_type t(*this); --(*this); return t; }

		// random access.

		// X can be either size_t or B::iter_bound_mover
		template<class X>
		this_type& operator +=(X j) { a += j * step; return *this; }

		template<class X>
		this_type& operator -=(X j) { a -= j * step; return *this; }

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
		ptrdiff_t operator-(const this_type& it)
		{
			return (a - it.a) / step;
		}

		//copy same type iterator
		this_type& operator=(const this_type& it)
		{
			a = it.a; step = it.step;
			return *this;
		}
		//copy relevant type iterator
		template<bool C>
		this_type& operator=(const iterator_type<C>& it)
		{
			a = it.a; step = it.step;
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

	typedef std::reverse_iterator<iterator> reverse_iterator;

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef ptrdiff_t iter_border_walker;

	iterator begin()
		{ return best_iterator(a->begin() + b.start, b.stride); }

	iterator end()
		{ return best_iterator(a->begin() + end_el, b.stride); }

	const_iterator begin() const
		{ return const_iterator(a->begin() + b.start, b.stride); }

	const_iterator end() const
		{ return const_iterator(a->begin() + end_el, b.stride); }

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
		return (*a)[b.start + j * b.stride];
	}
	typename const_iterator::reference operator[](size_t j) const
	{
		return (*a)[b.start + j * b.stride];
	}

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return b.length; }
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/

	iter_border_walker first_to_last() { return b.length - 1; }
	iter_border_walker begin_to_end() { return b.length; }

	void init(A& a0, const slice& b0)
	{
		a = &a0;
		b = b0;
		end_el = b0.start + b0.stride * b0.length;
	}

	void init(const array& o)
	{
		a = o.a;
		b = o.b;
		end_el = o.end_el;
	}

/** @name Constructors
@{*/
	//! The only constructor
	array(A& a, const ivl::slice& b)
		: a(&a), b(b), end_el(b.start + b.stride * b.length) { }

	//! Copy constructor
	array(const this_type& o) : a(o.a), b(o.b), end_el(o.end_el) {}

/**@}*/

    //! destructor
	~array() { }


/** @name Special Members
@{*/

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

	template <class D>
	bool overlap(const D& d) const
	{
		return a->overlap(d);
	}

	template <class D>
	bool self_overlap(const D& d) const
	{
		return d.overlap(*a);
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

