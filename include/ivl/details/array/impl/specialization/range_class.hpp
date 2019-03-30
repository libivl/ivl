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

template<bool IS_INTEGER>
struct range_tool
{
};

template<>
struct range_tool<true>
{
	template <class T>
	class const_iterator {
	private:
		typedef typename types::to_signed<T>::type step_type;
		T val;
		step_type step;

	public:
		// iterator_traits
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename types::remove_const<T>::type value_type;
		typedef ptrdiff_t difference_type;
		typedef const value_type pointer;
		typedef const T reference;

		const_iterator() { }
		const_iterator(const const_iterator& it)
			: val(it.val), step(it.step) { }
		// for begin
		const_iterator(T val, step_type step) : val(val), step(step) { }
		// for end
		const_iterator(T val, step_type step, T begin)
			: val(val), step(step)
		{
			this->val -= step_type(val - begin) % step;
		}

		const_iterator& operator++() { val+=step; return *this; }
		const_iterator& operator--() { val-=step; return *this; }

		const_iterator operator++(int)
			{ const_iterator tmp(*this); val+=step; return tmp; }
		const_iterator operator--(int)
			{ const_iterator tmp(*this); val-=step; return tmp; }

		// random access
		const_iterator operator +(const difference_type i) const
			{ const_iterator tmp(val + T(i) * step, step); return tmp; }
		const_iterator operator -(const difference_type i) const
			{ const_iterator tmp(val - T(i) * step, step); return tmp; }
		const_iterator& operator +=(const difference_type i)
			{ val+=T(i) * step; return *this; }
		const_iterator& operator -=(const difference_type i)
			{ val-=T(i) * step; return *this; }

		const T operator *() const { return val; }

		//TODO: make use of pointer face or something
		//const T* operator ->() const { return &val; }

		const T operator [](size_t j) const { return val + T(j) * step; }

		const_iterator& operator=(const const_iterator& it)
			{ this->val = it.val; this->step = it.step; return *this; }

		difference_type operator-(const const_iterator& it) const
			{ return (val - it.val) / step; }

		bool operator==(const const_iterator& it) const
			{ return this->val == it.val; }
		bool operator!=(const const_iterator& it) const
			{ return this->val != it.val; }
		bool operator<(const const_iterator& o) const
			{ return (step > 0) ? (val < o.val) : (val > o.val); }
		bool operator<=(const const_iterator& o) const
			{ return (step > 0) ? (val <= o.val) : (val >= o.val); }
		bool operator>(const const_iterator& o) const
			{ return (step > 0) ? (val > o.val) : (val < o.val); }
		bool operator>=(const const_iterator& o) const
			{ return (step > 0) ? (val >= o.val) : (val <= o.val); }

	};

};

template<>
struct range_tool<false>
{
	template <class T>
	class const_iterator {
	private:
		typedef typename types::to_signed<T>::type step_type;
		T first;
		step_type step;
		size_t i;

		// constructor for internal use
		explicit const_iterator(T first, step_type step, ptrdiff_t i, int)
			: first(first), step(step), i(i) { }

	public:
		// iterator_traits
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename types::remove_const<T>::type value_type;
		typedef ptrdiff_t difference_type;
		typedef const value_type* pointer;
		typedef const T reference;

		const_iterator() { }
		const_iterator(const const_iterator& it)
			: first(it.first), step(it.step), i(it.i) { }
		// for begin
		const_iterator(T val, T step) : first(val), step(step), i(0) { }
		// for end
		const_iterator(T val, T step, T begin) : first(begin), step(step),
			i(size_t(step_type(val - begin) / step)) { }

		const_iterator& operator++() { ++i; return *this; }
		const_iterator& operator--() { --i; return *this; }

		const_iterator operator++(int)
			{ const_iterator tmp(*this); i++; return tmp; }
		const_iterator operator--(int)
			{ const_iterator tmp(*this); i--; return tmp; }

		// random access
		const_iterator operator +(const difference_type off) const
			{ const_iterator tmp(first, step, i + off, 0); return tmp; }
		const_iterator operator -(const difference_type off) const
			{ const_iterator tmp(first, step, i - off, 0); return tmp; }
		const_iterator& operator +=(const difference_type off)
			{ i += off; return *this; }
		const_iterator& operator -=(const difference_type off)
			{ i -= off; return *this; }

		const T operator *() const { return first + step_type(i) * step; }

		// TODO: make use of a pointer face or something similar here...
		// TODO: fix this issue for all non-pointer iterators making correct
		// definition of iterator::pointer
		// const T* operator ->() const { return &(val + step_type(i) * step); }
		// this could mean that operator T[] may return an object that can
		// have & on it and return a pointer, and can be convertible to T. ouch!

		const T operator [](size_t j) const
			{ return first + step_type(i + j) * step; }

		const_iterator& operator=(const const_iterator& it)
			{ this->first = it.first; this->step = it.step;
				this->i = it.i; return *this; }

		difference_type operator-(const const_iterator& it) const
			{ return ptrdiff_t(i) - ptrdiff_t(it.i); }

		bool operator==(const const_iterator& o) const { return i == o.i; }
		bool operator!=(const const_iterator& o) const { return i != o.i; }
		bool operator<(const const_iterator& o) const { return (i < o.i); }
		bool operator<=(const const_iterator& o) const { return (i <= o.i); }
		bool operator>(const const_iterator& o) const { return (i > o.i); }
		bool operator>=(const const_iterator& o) const { return (i >= o.i); }

	};
};

} /* namespace array_details */

/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 class DERIVED_INFO
	     >
class array<T, data::range<DERIVED_INFO> > :
	public array_common_base<array<T, data::range<DERIVED_INFO> > >
{
private:
	typedef array_common_base<array<T,
		data::range<DERIVED_INFO> > > common_base_class;

protected:

public:
	typedef typename types::to_signed<T>::type step_type;

	T first;	//!< the starting element
	T last;		//!< the ending element
	step_type step;		//!< the distance between elements

	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename this_type::derived_type derived_type;

	/* TODO: present derived_array_type which will be one type before e.g. range<T>, having DATA_TYPE and DERIVED_INFO,
		or otherwise, derived_creatable_type. because range in an array_nd should yield create_new = array_nd, however
		range in a range<T> should yield create_new = array. Temporarily fix with create_new = array cause range in
		array_nd is currently unsupported anyway.
	*/

	typedef typename common_base_class::base_class base_class;

	typedef size_t size_type;

	typedef ptrdiff_t diff_type;

	using base_class::derived;

	typedef typename array_details::range_tool<types::is_integer<T>::value>
		::template const_iterator<T> const_iterator;
	typedef std::reverse_iterator<T> const_reverse_iterator;

	typedef typename const_iterator::reference const_reference;

	typedef const_iterator best_iterator;
	typedef const_reference best_reference;

	const_iterator begin() const
	{
		return const_iterator(first, step);
	}
	const_iterator end() const
	{
		return const_iterator(last + step, step, first);
	}
	const_reverse_iterator rbegin() const
		{ return end(); }
	const_reverse_iterator rend() const
		{ return begin(); }

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const
	{
		return size_t(step_type(last - first) / step + 1);
	}
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/

	typedef ptrdiff_t iter_border_walker;
	iter_border_walker first_to_last() const { return this->length() - 1; }
	iter_border_walker begin_to_end() const { return this->length(); }

/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	//! Returns the element found at position offset
	const_reference operator[] (size_t i) const
	{
		CHECK(i >= 0 && i < length() ,erange);
		return first + step_type(i) * step;
	}

	using common_base_class::operator[];

/**@}*/


/** @name Constructors
@{*/
	//! Default constructor.
	array() { }

	//! Copy-constructor
	array(const this_type& a)
	{
		first = a.first;
		last = a.last;
		step = a.step;
	}

    //! destructor
	~array() { }


/** @name Assignment Operators
@{*/

	/**
	 * \brief Copy-Assign another array of identical type
	 *
	 * eg:
	 * \code ivl::array<int> a(10, 0);
	 * ivl::array<int> b;
	 * b = a; \endcode
	 */
	this_type& operator=(const this_type& a) // copy operator
	{
		// Note: if(this != &a) is checked here because the base operator
		// is ignored.
		if(this == &a) return *this;
		first = a.first;
		last = a.last;
		step = a.step;
		return *this;
	}
/**@}*/

	void init(const this_type& a)
	{
		first = a.first;
		last = a.last;
		step = a.step;
	}
/**
 * @name Print functions
@{*/
	//! Print an array of range type (specialized print function)
	std::ostream& print(std::ostream& os) const;
/**@}*/

	//array<T> cat(const array<T>& a) const;


};

template <class T, class P>
std::ostream& array<T, ivl::data::range<P> >::print(
		std::basic_ostream<char, std::char_traits<char> >& os) const
{
	if(last >= first && step == T(1))
		os << "(" << first << ":" << last << ")";
	else if(last < first && step == -1)
		os << "(" << first << ":" << last << ")";
	else
		os << "(" << first << ":" << step << ":" << last << ")";

	return os;
}

#if 0
template <class T>
class range
	: public array<T, data::range, ivl::range<T> >
{
public:
	range() {}

	range(T first, T last, T step)
	{
		this->first = first;
		this->last = last;
		this->step = step;
	}
};
#endif
