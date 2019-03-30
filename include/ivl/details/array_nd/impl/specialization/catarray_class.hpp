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

#if 0

/**
 * \brief Multi-dimensional %array of type T
 *
 * This structure is used to define a multidimensional %array of type T. The
 * number of dimensions can be specified when constructing an object and can be
 * altered anytime by using methods like resize(const size_array &, const T).
 *
 * The simpliest way to access an array_nd element is by using operator() and
 * specifying the offset on each dimension, like this:
 * \code int i = a(2, 3, 2) \endcode
 *
 * An array_nd inherites all the functionality the array class provides, which
 * means that it can also be indexed as an one-dimensional %array using
 * the %array subscript operator: \link operator[](size_t) []\endlink.
 * Keep in mind that in array_nd the elements are stored in column-major order
 * like Fortran and Matlab and not like C. So, the offset is computed like this:
 * \verbatim offset = row + column*NUMROWS \endverbatim
 */
template <class T,
		 class A1,
		 class A2,
		 int CATDIM,
		 class DERIVED_INFO
	     >
class array_nd<T, data::catarray<A1, A2, CATDIM, DERIVED_INFO> >
	:
	public
		array_common_base<array_nd<T,
			data::catarray<A1, A2, CATDIM, DERIVED_INFO> > >

{
private:
	typedef array_nd prv_this_type;
	typedef typename prv_this_type::common_base_class common_base_class;

	typedef typename common_base_class::base_class prv_base_class;

	class not_a_type { typedef not_a_type reference; };

	typedef array_nd_details::catarray_common_tools::sub_type sub_type;
	static inline sub_type type_from_indtype(ivl::index_array::
		index_array_type y)
	{
		return array_nd_details::catarray_common_tools::
			type_from_indtype(y);
	}

protected:
	typedef typename array_nd::best_reference_iterator
		best_reference_iterator;

	typedef typename array_nd::const_reference_iterator
		const_reference_iterator;

	typedef typename array_nd::tool tool;

	using prv_base_class::in;
	using prv_base_class::idx;

	using prv_base_class::all_sizes;
	using prv_base_class::all_len;
	using prv_base_class::diffs_ar;
	using prv_base_class::diffs;
	using prv_base_class::sizes;
	using prv_base_class::steps;
	using prv_base_class::iter;
	using prv_base_class::back_diffs;
	using prv_base_class::begin_to_ends;
	using prv_base_class::first_to_lasts;

	using prv_base_class::nonsing_map;
	using prv_base_class::nonsing_rmap;
	using prv_base_class::idx_ar_map;
	using prv_base_class::idx_ar_rmap;

	using prv_base_class::get_iter;

public:
	typedef array_nd this_type;

	typedef this_type this_array_nd_type;

	typedef typename this_type::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! return type of size_nd in that data-specific class
	typedef const array<size_t, tiny>& size_nd_ref_type;

	//! return type of stride in that data-specific class
	//note: why should a non-ra array have stride anyway????
	typedef array<size_t, tiny> stride_ref_type;

	//! types that specify the defined parenthesis operators for this class
	typedef types::t_true has_1d_parenthesis;
	typedef types::t_true has_2d_parenthesis;
	typedef types::t_true has_3d_parenthesis;
	typedef types::t_true has_nd_parenthesis;



	// typedefs for class iterators
	typedef typename types::t_if<typename array_nd::is_writeable,
		data::catarray_nd_iterator<T,
			typename base_class::best_reference_iterator,
			typename base_class::const_reference_iterator,
			base_class::reference_iterator_is_nd::value, false>,
		not_a_type>::type iterator_nd;

	typedef data::catarray_nd_iterator<T,
			typename base_class::const_reference_iterator,
			typename base_class::const_reference_iterator,
		base_class::reference_iterator_is_nd::value, true> const_iterator_nd;

	typedef typename types::t_if<typename array_nd::is_writeable,
		data::catarray_nd_iterator<T,
			typename base_class::best_reference_iterator,
			typename base_class::const_reference_iterator,
			base_class::reference_iterator_is_nd::value, false, 0, false>,
		not_a_type>::type _fast_iterator_nd;

	typedef data::catarray_nd_iterator<T,
			typename base_class::const_reference_iterator,
			typename base_class::const_reference_iterator,
		base_class::reference_iterator_is_nd::value, true, 0, false>
			_fast_const_iterator_nd;

	typedef std::reverse_iterator<iterator_nd> reverse_iterator_nd;

	typedef std::reverse_iterator<const_iterator_nd>
		const_reverse_iterator_nd;

	template<int SPC>
	struct s_iterator_nd
	{
		typedef typename types::t_if<typename array_nd::is_writeable,
		data::catarray_nd_iterator<T,
			typename base_class::best_reference_iterator,
			typename base_class::const_reference_iterator,
			base_class::reference_iterator_is_nd::value, false, SPC>,
		not_a_type>::type type;
	};
	template<int SPC>
	struct const_s_iterator_nd
	{
		typedef data::catarray_nd_iterator<T,
				typename base_class::const_reference_iterator,
				typename base_class::const_reference_iterator,
			base_class::reference_iterator_is_nd::value, true, SPC> type;
	};

	template<int SPC>
	struct _fast_s_iterator_nd
	{
		typedef typename types::t_if<typename array_nd::is_writeable,
		data::catarray_nd_iterator<T,
			typename base_class::best_reference_iterator,
			typename base_class::const_reference_iterator,
			base_class::reference_iterator_is_nd::value, false, SPC, false>,
		not_a_type>::type type;
	};
	template<int SPC>
	struct _fast_const_s_iterator_nd
	{
		typedef data::catarray_nd_iterator<T,
				typename base_class::const_reference_iterator,
				typename base_class::const_reference_iterator,
			base_class::reference_iterator_is_nd::value, true, SPC, false> type;
	};

	template<int SPC>
	struct reverse_s_iterator_nd
	{
		typedef std::reverse_iterator<s_iterator_nd<SPC> > type;
	};
	template<int SPC>
	struct const_reverse_s_iterator
	{
		typedef std::reverse_iterator<const_s_iterator_nd<SPC> > type;
	};
	int iter_specialization_nd(size_t dim) const
	{
		return ((*idx)[dim].is_array()) ? 2 : 1;
	}

	typedef typename const_iterator_nd::
		iter_nd_border_walker iter_nd_border_walker;



/*
	size_t begin_pos(size_t d, size_t pos)
	{
		size_t mod = pos % nd().stride(d);
		if(d == nd().ndim() - 1) return mod;
		return pos - pos % nd().stride(d + 1) + mod;
	}

	size_t end_pos(size_t d, size_t pos)
	{
		size_t mod = pos % nd().stride(d);
		if(d == nd().ndim() - 1) return mod + nd().length();
		return pos - pos % nd().stride(d + 1) + mod +
			nd().stride(d + 1);
	}
*/

	// friend declarations for subarray iterator helper construction functions.
	template<class IT, class X>
	friend IT catarray_iter_create::_begin(X& a, size_t d);
	template <class IT, class X>
	friend IT catarray_iter_create::_begin(X& a, size_t d, const IT& it);
	template <class IT, class ITS, class X>
	friend IT catarray_iter_create::_iter(X& a, size_t d, const ITS& it);
	template <class IT, class S, class X>
	friend IT catarray_iter_create::_iter(X& a, size_t d,
		const array<size_t, S>& ind);
	template <class IT, class X>
	friend IT catarray_iter_create::_next(X& a, size_t d, const IT& it);
	template <class IT, class X>
	friend IT catarray_iter_create::_end(X& a, size_t d);
	template <class IT, class X>
	friend IT catarray_iter_create::_last(X& a, size_t d);

	// non-const iterator
	iterator_nd _begin(size_t d)
	{ return catarray_iter_create::_begin<iterator_nd>(*this, d); }

	iterator_nd _begin(size_t d, const iterator_nd& it)
	{ return catarray_iter_create::_begin<iterator_nd>(*this, d, it); }

	iterator_nd _iter(size_t d, const typename
		array_nd::best_iterator& it)
	{ return catarray_iter_create::_iter<iterator_nd>(*this, d, it); }

	template <class S>
	iterator_nd _iter(size_t d, const array<size_t, S>& ind)
	{ return catarray_iter_create::_iter<iterator_nd>(*this, d, ind); }

	iterator_nd _next(size_t d, const iterator_nd& it)
	{ return catarray_iter_create::_next<iterator_nd>(*this, d, it); }

	iterator_nd _end(size_t d)
	{ return catarray_iter_create::_end<iterator_nd>(*this, d); }

	iterator_nd _last(size_t d)
	{ return catarray_iter_create::_last<iterator_nd>(*this, d); }

	// const iterator
	const_iterator_nd _begin(size_t d) const
	{ return catarray_iter_create::_begin<const_iterator_nd>(*this, d); }

	const_iterator_nd _begin(size_t d, const const_iterator_nd& it) const
	{ return catarray_iter_create::_begin<const_iterator_nd>(*this, d, it); }

	const_iterator_nd _iter(size_t d, const typename
		array_nd::const_iterator& it) const
	{ return catarray_iter_create::_iter<const_iterator_nd>(*this, d, it); }

	template <class S>
	const_iterator_nd _iter(size_t d, const array<size_t, S>& ind) const
	{ return catarray_iter_create::_iter<const_iterator_nd>(*this, d, ind); }

	const_iterator_nd _next(size_t d, const const_iterator_nd& it) const
	{ return catarray_iter_create::_next<const_iterator_nd>(*this, d, it); }

	const_iterator_nd _end(size_t d) const
	{ return catarray_iter_create::_end<const_iterator_nd>(*this, d); }

	const_iterator_nd _last(size_t d) const
	{ return catarray_iter_create::_last<const_iterator_nd>(*this, d); }

	// fast
	_fast_iterator_nd _fast_begin(size_t d)
	{ return catarray_iter_create::_begin<_fast_iterator_nd>(*this, d); }
	_fast_iterator_nd _fast_last(size_t d)
	{ return catarray_iter_create::_last<_fast_iterator_nd>(*this, d); }
	_fast_const_iterator_nd _fast_begin(size_t d) const
	{ return catarray_iter_create::_begin<_fast_const_iterator_nd>(*this, d); }
	_fast_const_iterator_nd _fast_last(size_t d) const
	{ return catarray_iter_create::_last<_fast_const_iterator_nd>(*this, d); }

#if 0
	// non-const reverse iterator
	reverse_iterator_nd _rbegin(size_t d);
	reverse_iterator_nd _rbegin(size_t d, const reverse_iterator_nd& itr);
	reverse_iterator_nd _riter(size_t d, const
				typename array_nd::best_iterator& it);
	template <class S>
	reverse_iterator_nd _riter(size_t d, array<size_t, S> ind);
	reverse_iterator_nd _rnext(size_t d, const reverse_iterator_nd& itr);
	reverse_iterator_nd _rend(size_t d);
	reverse_iterator_nd _rlast(size_t d);
	// const reverse reverse_iterator
	const_reverse_iterator_nd _rbegin(size_t d) const;
	const_reverse_iterator_nd _rbegin(size_t d,
		const const_reverse_iterator_nd& itr) const;
	const_reverse_iterator_nd _riter(size_t d,
			const typename array_nd::const_iterator& it) const;
	template <class S>
	const_reverse_iterator_nd _riter(size_t d, array<size_t, S> ind) const;
	const_reverse_iterator_nd _rnext(size_t d,
		const const_reverse_iterator_nd& itr) const;
	const_reverse_iterator_nd _rend(size_t d) const;
	const_reverse_iterator_nd _rlast(size_t d) const;
#endif

	// iter_nd_border_walker functions
	iter_nd_border_walker first_to_last(size_t d) const
	{
	    size_t j = nonsing_rmap[d];
	    ptrdiff_t k = idx_ar_rmap[d];
	    return iter_nd_border_walker(iter[j], first_to_lasts[j],
			sizes[j] - 1, k);
	}

	iter_nd_border_walker begin_to_end(size_t d) const
	{
	    size_t j = nonsing_rmap[d];
	    ptrdiff_t k = idx_ar_rmap[d];
	    return iter_nd_border_walker(iter[j], begin_to_ends[j],
			sizes[j], k);
	}



	using base_class::derived;





	//! get base class
	base_class& base() { return *this; }
	const base_class& base() const { return *this; }


/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/

	using base_class::operator[];
	using base_class::length;
	using base_class::numel;

	using common_base_class::operator();

/**@}*/


#if 0
// TODO: have to implement
	/** @name Element access (multidimensional)
	 * Elements can be accessed by specifying the
	 */

	T& operator()(size_t s1);
	T& operator()(size_t s1, size_t s2);
	T& operator()(size_t s1, size_t s2, size_t s3);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5, size_t s6);
#endif

	//! Selects a single, mutable element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	typename types::best_iterator<array_nd>::type::reference operator()(
			const array<size_t, S>& indx)
	{
		iterator_nd p(_begin(0) + indx[0]);
		for(size_t i = 1; i < indx.length(); i++)
			p.move_along(_begin(i), indx[i]);
		return *p;
	}

#if 0
	const T& operator()(size_t s1) const;
	const T& operator()(size_t s1, size_t s2) const;
	const T& operator()(size_t s1, size_t s2, size_t s3) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5, size_t s6) const;
#endif

	//! Selects a single, const element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	typename array_nd::const_iterator::reference operator()
		(const array<size_t, S>& indx) const
	{
		const_iterator_nd p(_begin(0) + indx[0]);

		for(size_t i = 1; i < indx.length(); i++)
			p.move_along(_begin(i), indx[i]);

		return *p;
	}


/** @name constructors */
/**@{*/
	//! Default constructor
	array_nd() { }

	//! Construct by defining original array and index array references.
	array_nd(A& a, const I& idx) { this->setref(a, idx); }

	//! Copy constructor
	array_nd(const this_type& a) :
		common_base_class(a) {};
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
	array_nd(const array_nd<J, S>& a) { }

/**@}*/

/** @name Size functions (multidimensional)
@{*/

	//! Get the size for each dimension
	size_nd_ref_type size_nd() const { return all_sizes; }

	//! Get the size for a specific dimension
	size_t size_nd(size_t d) const { return all_sizes[d]; }

	stride_ref_type stride() const
	{
		// no stored stride information because catarray has no random access
		return cumprod(shift(all_sizes, 1, size_t(1)));
	}

	//! Get the size for each dimension
	size_type size() const { return all_sizes; }

	//! Get the size for a specific dimension
	size_t size(size_t d) const { return all_sizes[d]; }

	//! Get the number of dimensions
	size_t ndims() const { return all_sizes.length(); }
/**@}*/


/** @name Resize Functions
@{*/
	// TODO: need to perform cut on resize(0) for special index_array values
/**@}*/


/**
 * @name Assignment Operators
@{*/
	template<class K>
	derived_type& operator=(const K& k)
	{ common_base_class::operator=(k); return derived(); }
	//using common_base_class::operator=;

	//! C++ copy-constructor
	this_type& operator=(const this_type& in)
	{ common_base_class::operator=(in); return *this; }
/*
	//! @copydoc array::operator=(const T&)
	derived_type& operator=(const T& s)
	{
		base_class::operator=(array<T,
			data::ref_val_repeat, types::term>(this->length(), s));
		return this->derived();
	}

	//! Assign the content of another form of array_nd
	template<class S, class K>
	derived_type& operator=(const array_nd<T, S, K>& a)
	{ base_class::operator=(a); return *this; }
*/
/**@}*/

};

#endif
