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
class array_nd<T, data::wrap_array<A, ATTR, DERIVED_INFO> >:
	public
	array_common_base<array_nd<T,
		data::wrap_array<A, ATTR, DERIVED_INFO> > >
{
private:
	typedef array_nd prv_this_type;
	typedef typename prv_this_type::common_base_class common_base_class;

	typedef typename A::this_array_nd_type a_t;

	typedef typename types::best_iterator<a_t>::type best_iter_t;
	typedef typename types::best_iterator<a_t>::type::reference reference_t;
	typedef typename a_t::const_iterator::reference const_reference_t;

	typename A::derived_type& a_d() { return this->a_ptr->derived(); }
	const typename A::derived_type& a_d() const
		{ return this->a_ptr->derived(); }
	a_t& a_nd() { return static_cast<a_t&>(a_d()); }
	const a_t& a_nd() const { return static_cast<const a_t&>(a_d()); }

public:
	typedef array_nd this_type;

	typedef this_type this_array_nd_type;

	typedef typename types::derive<this_type>::type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef typename a_t::size_type size_type;

	//! return type of size_nd in that data-specific class
	typedef typename a_t::size_nd_ref_type size_nd_ref_type;

	//! return type of size_nd in that data-specific class
	typedef typename a_t::stride_ref_type stride_ref_type;

	//! types that specify the defined parenthesis operators for this class
	/*
	typedef typename a_t::has_1d_parenthesis has_1d_parenthesis;
	typedef typename a_t::has_2d_parenthesis has_2d_parenthesis;
	typedef typename a_t::has_3d_parenthesis has_3d_parenthesis;
	typedef typename a_t::has_nd_parenthesis has_nd_parenthesis;
	*/

	using base_class::derived;

	//! get base class
	base_class& base() { return *this; }
	const base_class& base() const { return *this; }


/** @name iterator_nd's
@{*/
	typedef typename array_nd::const_iterator const_iterator;

	typedef typename types::best_iterator_nd<a_t>::type best_iterator_nd;
	typedef typename types::best_iterator_nd<a_t, 0, false>
		::type best_fast_iterator_nd;
	typedef typename types::best_reverse_iterator_nd<a_t>::type
		best_reverse_iterator_nd;

	typedef typename types::t_if<types::t_not<typename a_t::is_writeable>,
		types::not_a_type, best_iterator_nd>::type iterator_nd;
	typedef typename types::t_if<types::t_not<typename a_t::is_writeable>,
		types::not_a_type, best_fast_iterator_nd>::type _fast_iterator_nd;
	typedef typename types::t_if<types::t_not<typename a_t::is_writeable>,
		types::not_a_type, best_reverse_iterator_nd>::type reverse_iterator_nd;

	typedef typename a_t::const_iterator_nd const_iterator_nd;
	typedef typename a_t::_fast_const_iterator_nd _fast_const_iterator_nd;
	typedef typename a_t::const_reverse_iterator_nd const_reverse_iterator_nd;

	// best
	best_iterator_nd _begin(size_t d) { return a_d()._begin(d); }
	best_iterator_nd _begin(size_t d, const best_iterator_nd& it_nd)
		{ return a_d()._begin(d, it_nd); }
	best_iterator_nd _iter(size_t d, const best_iter_t& it)
		{ return a_d()._iter(d, it); }
	template<class S>
	best_iterator_nd _iter(size_t d, array<size_t, S> ind)
		{ return a_d()._iter(d, ind); }
	best_iterator_nd _next(size_t d, const best_iterator_nd& it_nd)
		{ return a_d()._next(d, it_nd); }
	best_iterator_nd _end(size_t d) { return a_d()._end(d); }
	best_iterator_nd _last(size_t d) { return a_d()._last(d); }
	// const
	const_iterator_nd _begin(size_t d) const { return a_d()._begin(d); }
	const_iterator_nd _begin(size_t d, const const_iterator_nd& it_nd) const
		{ return a_d()._begin(d, it_nd); }
	const_iterator_nd _iter(size_t d, const const_iterator& it) const
		{ return a_d()._iter(d, it); }
	template<class S>
	const_iterator_nd _iter(size_t d, array<size_t, S> ind) const
		{ return a_d()._iter(d, ind); }
	const_iterator_nd _next(size_t d, const const_iterator_nd& it_nd) const
		{ return a_d()._next(d, it_nd); }
	const_iterator_nd _end(size_t d) const { return a_d()._end(d); }
	const_iterator_nd _last(size_t d) const { return a_d()._last(d); }

	// r-best
	best_reverse_iterator_nd _rbegin(size_t d) { return a_d()._rbegin(d); }
	best_reverse_iterator_nd _rbegin(size_t d,
			const best_reverse_iterator_nd& it_nd)
		{ return a_d()._rbegin(d, it_nd); }
	best_reverse_iterator_nd _riter(size_t d, const best_iter_t& it)
		{ return a_d()._riter(d, it); }
	template<class S>
	best_reverse_iterator_nd  _riter(size_t d, array<size_t, S> ind)
		{ return a_d()._riter(d, ind); }
	best_reverse_iterator_nd _rnext(size_t d,
			const best_reverse_iterator_nd& it_nd)
		{ return a_d()._rnext(d, it_nd); }
	best_iterator_nd _rend(size_t d) { return a_d()._rend(d); }
	best_iterator_nd _rlast(size_t d) { return a_d()._rlast(d); }
	// r-const
	const_reverse_iterator_nd _rbegin(size_t d) const
		{ return a_d()._rbegin(d); }
	const_reverse_iterator_nd _rbegin(size_t d,
			const const_reverse_iterator_nd& it_nd) const
		{ return a_d()._rbegin(d, it_nd); }
	const_reverse_iterator_nd _riter(size_t d, const const_iterator& it) const
		{ return a_d()._riter(d, it); }
	template<class S>
	const_reverse_iterator_nd _riter(size_t d, array<size_t, S> ind) const
		{ return a_d()._riter(d, ind); }
	const_reverse_iterator_nd _rnext(size_t d, const
			const_reverse_iterator_nd& it_nd) const
		{ return a_d()._rnext(d, it_nd); }
	const_reverse_iterator_nd _rend(size_t d) const { return a_d()._rend(d); }
	const_reverse_iterator_nd _rlast(size_t d) const { return a_d()._rlast(d); }
	// fast
	best_fast_iterator_nd _fast_begin(size_t d) { return a_d()._fast_begin(d); }
	best_fast_iterator_nd _fast_last(size_t d) { return a_d()._fast_last(d); }
	_fast_const_iterator_nd _fast_begin(size_t d) const
		{ return a_d()._fast_begin(d); }
	_fast_const_iterator_nd _fast_last(size_t d) const
		{ return a_d()._fast_last(d); }

	using common_base_class::first_to_last;
	using common_base_class::begin_to_end;

	typedef typename a_t::iter_nd_border_walker iter_nd_border_walker;

	iter_nd_border_walker first_to_last(size_t d)
		{ return a_d().first_to_last(d); }
	iter_nd_border_walker begin_to_end(size_t d)
		{ return a_d().begin_to_end(d); }
/**@}*/


/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	using base_class::operator[];
	using base_class::length;
	using base_class::numel;
/**@}*/

	/** @name Element access (multidimensional)
	 * Elements can be accessed by specifying the
	 */
	//@{

	//todo: add extension overloaded operator ()
	using common_base_class::operator();

	template<class S>
	reference_t operator()(const array<size_t, S>& indx)
		{ return derived().operator()[indx]; }
	//! Selects a single, mutable element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	const_reference_t operator()(const array<size_t, S>& indx) const
		{ return derived()[sub2ind(derived(), indx)]; }
/*
	const T& operator()(size_t s1) const;
	const T& operator()(size_t s1, size_t s2) const;
	const T& operator()(size_t s1, size_t s2, size_t s3) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5, size_t s6) const;
	//! Selects a single, const element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	typename array_nd::const_iterator::reference operator()
		(const array<size_t, S>& indx) const
		{ return derived()[sub2ind(derived(), indx)]; }
*/
	//@}

/** @name Size functions (multidimensional)
@{*/

	//! Get the size for each dimension
	size_nd_ref_type size_nd() const { return a_nd().size_nd(); }

	//! Get the size for a specific dimension
	size_t size_nd(size_t d) const { return a_nd().size_nd(d); }

	//! Get the stride for each dimension
	stride_ref_type stride() const { return a_nd().stride(); }

	//! Get the stride for a particular dimension
	size_t stride(size_t dim) const { return a_nd().stride(dim); }

	//! Get the size for each dimension
	size_type size() const { return a_nd().size(); }

	//! Get the size for a specific dimension
	size_t size(size_t d) const { return a_nd().size(d); }

	//! Get the number of dimensions
	size_t ndims() const { return a_nd().ndims(); }
/**@}*/

/** @name Resize Functions
@{*/
	//! resize (n-dim)
	template <class S>
	void resize(const array<size_t, S>& newsize, const T& s)
	{
		if(array_details::
			wrap_array_resize_details<typename array_nd::is_resizeable>
			::resize(a_nd(), newsize, s)) {
				this->a_begin = a_nd()->begin(); this->len = a_nd()->length();
			}
	}

	//! resize (n-dim) without padding
	template <class S>
	void resize(const array<size_t, S>& newsize)
	{
		if(array_details::
			wrap_array_resize_details<typename array_nd::is_resizeable>
			::resize(a_nd(), newsize)) {
				this->a_begin = a_nd()->begin(); this->len = a_nd()->length();
			}
	}
//

	//! reshape (n-dim)
	template <class S>
	void reshape(const array<size_t, S>& newsize, const T& s)
	{
		if(array_details::
			wrap_array_resize_details<typename array_nd::is_resizeable>
			::reshape(a_nd(), newsize, s)) {
				this->a_begin = a_nd()->begin(); this->len = a_nd()->length();
			}
	}

	//! reshape (n-dim) without padding
	template <class S>
	void reshape(const array<size_t, S>& newsize)
	{
		if(array_details::
			wrap_array_resize_details<typename array_nd::is_resizeable>
			::reshape(a_nd(), newsize)) {
				this->a_begin = a_nd()->begin(); this->len = a_nd()->length();
			}
	}

/**@}*/


/** @name constructors */
/**@{*/
	//! Default constructor
	array_nd() { }

	//! construction from the reference arrays
	array_nd(A& a1) { this->setref(a1); }

	//! Copy constructor
	array_nd(const array_nd& a) : common_base_class(a) { }
/**@}*/

/** @name filler constructors */
/**@{*/

	// Construct by defining an element count.
	explicit array_nd(size_t count) { }

	// Construct by defining an element count and a sigle default value
	array_nd(size_t count, const T& s) { }

	// Construct by defining an element count and a pointer to data.
	array_nd(size_t count, const T *data) { }

	// Construct from a size_array containing the dimension sizes
	template<class S>
	array_nd(const array<size_t, S>& sz) { }

	// construct from a size_array containing the dimension sizes and scalar
	template<class S>
	array_nd(const array<size_t, S>& sz, const T& s) { }

	//Construct from a size_array and pointer
	template<class S>
	array_nd(const array<size_t, S>& sz, const T* ptr) { }

	//Construct from a size_array and an array with the values.
	template<class S, class J, class D>
	array_nd(const array<size_t, S>& sz, const array<J, D>& a) { }

	// Constructor using another form of array_nd
	template<class J, class S>
	array_nd(const array_nd<J, S>& a) : common_base_class(a) { }

	//! (special for ref_iterator) Construct from array_nd
	template <class J, class S>
	array_nd(array_nd<J, S>& a) : common_base_class(a) {}

/**@}*/

/**
 * @name Assignment Operators
@{*/
	using common_base_class::operator=;

	//! C++ copy-constructor
	this_type& operator=(const this_type& in)
	{ common_base_class::operator=(in); return *this; }

/**@}*/

};
