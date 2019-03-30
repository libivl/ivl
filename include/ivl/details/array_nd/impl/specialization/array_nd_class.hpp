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
 *
 * This is the normal specialization. It also applies to unspecialized
 * data_class_sets, however they have to be resizable, creatable and writable.
 *
 */
template <class T, class OPTS = mem>
class array_nd:
	public
	array_common_base<array_nd<T, OPTS> >,

	public
	array_nd_details::
		basic_iterator_nd_interface<array_nd<T, OPTS> >
{
private:
	typedef array_nd prv_this_type;
	typedef typename prv_this_type::common_base_class common_base_class;
	typedef typename prv_this_type::iter_nd_interface_class iter_nd_interface;

	//! The number of dimensions.
	size_t ndim;
	//! The size of each dimension.
	array<size_t, tiny> sizes;
	//! The stride for each dimension.
	array<size_t, tiny> strides;

public:
	/*
	TODO: wipe these?
	operator common_base_class&() { return *this; }
	operator const common_base_class&() const { return *this; }
	operator common_base_class() { return *this; }
	operator const common_base_class() const { return *this; }
	*/

	typedef array_nd this_type;

	typedef this_type this_array_nd_type;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! return type of size_nd in that data-specific class
	typedef const array<size_t, tiny>& size_nd_ref_type;

	//! return type of size_nd in that data-specific class
	typedef const array<size_t, tiny>& stride_ref_type;

	//! types that specify the defined parenthesis operators for this class
	typedef types::t_true has_1d_parenthesis;
	typedef types::t_true has_2d_parenthesis;
	typedef types::t_true has_3d_parenthesis;
	typedef types::t_true has_nd_parenthesis;

	typedef typename this_type::best_reference best_reference;
	typedef typename this_type::const_reference const_reference;

	// use _arg_base instead of _arg to solve weird msvc2005 bug
    typedef typename this_type::all_init_arg_base all_init_arg;
    typedef typename this_type::data_init_arg_base data_init_arg;

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

	/** @name Element access (multidimensional)
	 * Elements can be accessed by specifying the
	 */
	//@{
	best_reference operator()(size_t s1)
		{ return (*this)[s1]; }
	best_reference operator()(size_t s1, size_t s2)
		{ return (*this)[s1 + s2 * strides[1]]; }
	best_reference operator()(size_t s1, size_t s2, size_t s3)
		{ return (*this)[s1 + s2 * strides[1] + s3 * strides[2]]; }
	best_reference operator()(size_t s1, size_t s2, size_t s3, size_t s4)
		{ 	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3]]; }
	best_reference operator()(size_t s1, size_t s2, size_t s3, size_t s4,
		size_t s5)
		{ 	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3] + s5 * strides[4]]; }
	best_reference operator()(size_t s1, size_t s2, size_t s3, size_t s4,
		size_t s5, size_t s6)
		{ 	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3] + s5 * strides[4] + s6 * strides[5]]; }
	//! Selects a single, mutable element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	best_reference operator()(const array<size_t, S>& indx)
		{ return derived()[sub2ind(derived(), indx)]; }

	const_reference operator()(size_t s1) const
		{ return (*this)[s1]; }
	const_reference operator()(size_t s1, size_t s2) const
		{ return (*this)[s1 + s2 * strides[1]]; }
	const_reference operator()(size_t s1, size_t s2, size_t s3) const
		{ return (*this)[s1 + s2 * strides[1] + s3 * strides[2]]; }
	const_reference operator()(size_t s1, size_t s2, size_t s3,
		size_t s4) const
		{ 	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3]]; }
	const_reference operator()(size_t s1, size_t s2, size_t s3, size_t s4,
		size_t s5) const
		{ 	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3] + s5 * strides[4]]; }
	const_reference operator()(size_t s1, size_t s2, size_t s3, size_t s4,
		size_t s5, size_t s6) const
		{ 	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3] + s5 * strides[4] + s6 * strides[5]]; }
	//! Selects a single, const element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	const_reference operator()(const array<size_t, S>& indx) const
		{ return derived()[sub2ind(derived(), indx)]; }
	//@}



/** @name Single-dimensional constructors */
/**@{*/
	//! Default constructor
	array_nd() : ndim(0), sizes(0), strides(0) { }

	//! Construct by defining an element count.
	explicit array_nd(size_t count)
	: common_base_class(count), ndim(1),
		sizes(size_array(1, count)), strides(size_array(1,1)) { }

	//! \brief Construct by defining an element count and a sigle default
	//! value for all elements
	array_nd(size_t count, const T& s) :
		common_base_class(count, s), ndim(1),
		sizes(size_array(1, count)), strides(size_array(1,1)) { }

	//! \brief Construct by defining an element count and a sigle default
	//! value for all elements or an ivl::array to copy the elements from.
	template <class J, class D>
	array_nd(size_t count, const array<J, D>& s) :
		common_base_class(count, s), ndim(1),
		sizes(size_array(1, count)), strides(size_array(1,1)) { }

	/**
	 * \brief Construct by defining an element count and a pointer to data.
	 *
	 * \warning The constructor will try to read
	 * <em>count*size_of(T)</em> bytes from the memory pointed by \e data,
	 * without performing any kind of check. The user is responsible of
	 * making sure the memory is accessible and properly initialized.
	 */
	array_nd(size_t count, const T *data) :
		common_base_class(count, data), ndim(1),
		sizes(size_array(1,count)), strides(size_array(1,1)) { }

	//! \brief Construct from a size_t and a data_init_arg
	//! used for arrays of special types only
	// iavr: parameter S unused
	// template<class S>
	array_nd(size_t count, const data_init_arg& y) :
		common_base_class(count, y), ndim(1),
		sizes(size_array(1,count)), strides(size_array(1,1)) { }

/**@}*/

/** @name Multi-dimensional constructors */
/**@{*/
	//! Construct from a size_array containing the dimension sizes
	template<class S>
	array_nd(const array<size_t, S>& sz) :
		common_base_class(size_t(prod(sz))), ndim(sz.length()),
		sizes(sz), strides(cumprod(shift(sz, 1, size_t(1)))) { }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and assign scalar
	template<class S>
	array_nd(const array<size_t, S>& sz, const T& s) :
		common_base_class(prod(sz), s), ndim(sz.length()), sizes(sz),
		strides(cumprod(shift(sz, 1, size_t(1)))) { }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and assign values from an one-dimensional C array
	template<class S>
	array_nd(const array<size_t, S>& sz, const T* ptr) :
		common_base_class(prod(sz), ptr), ndim(sz.length()),
		sizes(sz), strides(cumprod(shift(sz, 1, size_t(1)))) { }

    //! \brief Construct from a size_array and a data_init_arg
    //! used for arrays of special types only
	template<class S>
	array_nd(const array<size_t, S>& sz, const data_init_arg& y) :
		common_base_class(prod(sz), y), ndim(sz.length()),
		sizes(sz), strides(cumprod(shift(sz, 1, size_t(1)))) { }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and an array with the values.
	template<class S, class J, class D>
	array_nd(const array<size_t, S>& sz, const array<J, D>& a) :
		common_base_class(prod(sz), a),
		ndim(sz.length()), sizes(sz),
		strides(cumprod(shift(sz, 1, size_t(1)))) { }

	// specific for the case that we have ref iterator and we need non-const
	// array
	//! \brief Construct from a size_array containing the dimension sizes
	//! and an array with the values.
	template<class S, class J, class D>
	array_nd(const array<size_t, S>& sz, array<J, D>& a) :
		common_base_class(prod(sz), a),
		ndim(sz.length()), sizes(sz),
		strides(cumprod(shift(sz, 1, size_t(1)))) { }

	//! Copy constructor
	array_nd(const this_type& a) :
		common_base_class(a),
		ndim(a.ndims()), sizes(a.size_nd()), strides(a.stride()) { }

	//! Constructor using another form of array_nd
	template<class J, class S>
	array_nd(const array_nd<J, S>& a) :
		common_base_class(a),
		ndim(a.ndims()), sizes(a.size_nd()),
		strides(a.stride()) { }

	//! (special for ref_iterator) Constructor using another form of array_nd
	template<class J, class S>
	array_nd(array_nd<J, S>& a) :
		common_base_class(a),
		ndim(a.ndims()), sizes(a.size_nd()),
		strides(a.stride()) { }

#ifdef IVL_MATLAB
	/**
	 * \brief Construct from an existing Matlab mxArray
	 *
	 * eg:
	 * \code ivl::array_nd<int> a = lrhs[0]; \endcode
	 *
	 * If the mxArray contains elements of different class
	 * than the type of the %array elements, an exception will occur
	 */
	array_nd(const mxArray* mx);
#endif


/**@}*/



/** @name Size functions (multidimensional)
@{*/

	//! Get the size for each dimension
	size_nd_ref_type size_nd() const { return sizes; }

	//! Get the size for a specific dimension
	size_t size_nd(size_t d) const { return sizes[d]; }

	//! Get the stride for each dimension
	stride_ref_type stride() const { return strides; }

	//! Get the stride for a particular dimension
	size_t stride(size_t dim) const { return strides[dim]; }

	//! Get the size for each dimension
	size_type size() const { return size_nd(); }

	//! Get the size for a specific dimension
	size_t size(size_t d) const { return sizes[d]; }

	//! Get the number of dimensions
	size_t ndims() const { return ndim; }
/**@}*/

	using iter_nd_interface::first_to_last;
	using common_base_class::first_to_last;

	using iter_nd_interface::begin_to_end;
	using common_base_class::begin_to_end;

/** @name Resize Functions
@{*/
	//! init (1-dim)
	//! The array is resized according to the new shape and new length.
	//! The old data that fits into the new shape is kept from the portion
	//! of the same shape that was common to the new and the old shape.
	//! In other words, the array-level data is moved, so that the rectangle,
	//! cube, or n-dim shape of data remains intact, and it is optionally
	//! padded with new values if it grows.
	void init(const size_t newsize, const T& s);

	//! init (1-dim) without padding
	void init(const size_t newsize);

	//! init (n-dim)
	template <class S>
	void init(const array<size_t, S>& newsize, const T& s);

	//! init (n-dim) without padding
	template <class S>
	void init(const array<size_t, S>& newsize);
	//
	//! resize (1-dim)
	//! The array is resized according to the new shape and new length.
	//! The old data that fits into the new shape is kept from the portion
	//! of the same shape that was common to the new and the old shape.
	//! In other words, the array-level data is moved, so that the rectangle,
	//! cube, or n-dim shape of data remains intact, and it is optionally
	//! padded with new values if it grows.
	void resize(const size_t newsize, const T& s);

	//! resize (1-dim) without padding
	void resize(const size_t newsize);

	//! resize (n-dim)
	template <class S>
	void resize(const array<size_t, S>& newsize, const T& s);

	//! resize (n-dim) without padding
	template <class S>
	void resize(const array<size_t, S>& newsize);
//
	//! reshape (1-dim).
	//! resizes and keeps the underlying array contents. changes shape,
	//! and discards the old data shape. faster than resize.
	//! The array is resized. The data that fits in the new length is not
	//! affected. It will be the same as the old if viewed as an array,
	//! and it will be folded into the dimensions of the array_nd according
	//! to the new shape. Padding is applied at the end of the data.
	void reshape(const size_t newsize, const T& s);

	//! reshape (1-dim) without padding
	void reshape(const size_t newsize);

	//! reshape (n-dim)
	template <class S>
	void reshape(const array<size_t, S>& newsize, const T& s);

	//! reshape (n-dim) without padding
	template <class S>
	void reshape(const array<size_t, S>& newsize);
/**@}*/

	// Operators

/*
TODO: do something for this. you need to disable this operator for the array_nd,
since it is forbidden to resize the underlying array, that would cause data corruption.
this might possibly be handled with the derived mechanism and promote the return
value of this function to a non-resizable type when the Derived type is an
array_nd......

	static_indirect_array<T, false> operator[](const size_array& idx)
		{ return static_indirect_array<T, false>(idx, this->base_ptr); }

	static_mask_array<T, false> operator[](const bool_array& idx)
		{ return static_mask_array<T, false>(idx, this->get_base_ptr()); }
*/


/**
 * @name Assignment Operators
@{*/
	//using common_base_class::operator=;
	template<class K>
	derived_type& operator=(const K& k)
	{ common_base_class::operator=(k); return derived(); }

	//! C++ copy-constructor
	this_type& operator=(const this_type& in)
	{ common_base_class::operator=(in); return *this; }

/**@}*/

};


// init

template <class T, class D>
void array_nd<T, D>::init(size_t newsize)
// override the base data init because it will be now invalid.
{
	// call array data class init first
	base_class::init(newsize);

	ndim = 1;
	sizes.init(1, newsize);
	strides.init(1, 1);
}

template <class T, class D>
void array_nd<T, D>::init(size_t newsize, const T& s)
// override the base data init because it will be now invalid.
{
	// call array data class init first
	base_class::init(newsize, s);

	ndim = 1;
	sizes.init(1, newsize);
	strides.init(1, 1);
}

template <class T, class D>
template<class S>
void array_nd<T, D>::init(const array<size_t, S>& newsize)
{
	// call array data class init first
	base_class::init(prod(newsize));

	ndim = newsize.length();
	sizes = newsize;
	strides = cumprod<size_t>(shift(sizes, 1, size_t(1)));
}

template <class T, class D>
template<class S>
void array_nd<T, D>::init(const array<size_t, S>& newsize, const T& s)
{
	// call array data class init first
	base_class::init(prod(newsize), s);

	ndim = newsize.length();
	sizes = newsize;
	strides = cumprod<size_t>(shift(sizes, 1, size_t(1)));
}

// reshape

template <class T, class D>
void array_nd<T, D>::reshape(size_t newsize)
// override the base data resize because it will be now invalid.
{
	// call array data class resize first
	base_class::resize(newsize);

	ndim = 1;
	sizes.resize(1, newsize);
	strides.resize(1, 1);
}

template <class T, class D>
void array_nd<T, D>::reshape(size_t newsize, const T& s)
// override the base data resize because it will be now invalid.
{
	// call array data class resize first
	base_class::resize(newsize, s);

	ndim = 1;
	sizes.resize(1, newsize);
	strides.resize(1, 1);
}

template <class T, class D>
template<class S>
void array_nd<T, D>::reshape(const array<size_t, S>& newsize)
{
	// call array data class resize first
	base_class::resize(prod(newsize));

	ndim = newsize.length();
	sizes = newsize;
	strides = cumprod<size_t>(shift(sizes, 1, size_t(1)));
}

template <class T, class D>
template<class S>
void array_nd<T, D>::reshape(const array<size_t, S>& newsize, const T& s)
{
	// call array data class resize first
	base_class::resize(prod(newsize), s);

	ndim = newsize.length();
	sizes = newsize;
	strides = cumprod<size_t>(shift(sizes, 1, size_t(1)));
}


// resize

template <class T, class D>
void array_nd<T, D>::resize(size_t newsize)
// override the base data resize because it will be now invalid.
{
	// call array data class resize first
	array_nd_details::shrink_rearrange(*this, idx(newsize), idx(1));
	base_class::resize(newsize);
	array_nd_details::enlarge_rearrange(*this, idx(newsize), idx(1));

	ndim = 1;
	sizes.resize(1, newsize);
	strides.resize(1, 1);

}

template <class T, class D>
void array_nd<T, D>::resize(size_t newsize, const T& s)
// override the base data resize because it will be now invalid.
{
	// call array data class resize first
	array_nd_details::shrink_rearrange(*this, idx(newsize), idx(1), s);
	base_class::resize(newsize/*, s*/);
	array_nd_details::enlarge_rearrange(*this, idx(newsize), idx(1), s);

	ndim = 1;
	sizes.resize(1, newsize);
	strides.resize(1, 1);
}

template <class T, class D>
template<class S>
void array_nd<T, D>::resize(const array<size_t, S>& newsize)
{
	array<size_t, tiny> new_stride =
		cumprod<size_t>(shift(newsize, 1, size_t(1)));

	// call array data class resize first
	array_nd_details::shrink_rearrange(*this, newsize, new_stride);
	base_class::resize(prod(newsize));
	array_nd_details::enlarge_rearrange(*this, newsize, new_stride);

	ndim = newsize.length();
	sizes = newsize;
	strides = new_stride;
}

template <class T, class D>
template<class S>
void array_nd<T, D>::resize(const array<size_t, S>& newsize, const T& s)
{
	array<size_t, tiny> new_stride =
		cumprod<size_t>(shift(newsize, 1, size_t(1)));

	// call array data class resize first
	array_nd_details::shrink_rearrange(*this, newsize, new_stride, s);
	base_class::resize(prod(newsize) /*, s*/);
	array_nd_details::enlarge_rearrange(*this, newsize, new_stride, s);

	ndim = newsize.length();
	sizes = newsize;
	strides = new_stride;
}

// -------------------------------------------------------------
#if 0
//VC2005 Crashes with this! OMG......

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::best_reference
	array_nd<T, D, P>::operator()(size_t s1)
{
	return (*this)[s1];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::best_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2)
{
	return (*this)[s1 + s2 * strides[1]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::best_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3)
{
	return (*this)[s1 + s2 * strides[1] + s3 * strides[2]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::best_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3, size_t s4)
{
	return (*this)[s1 + s2 * strides[1] +
					s3 * strides[2] + s4 * strides[3]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::best_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3,
							size_t s4, size_t s5)
{
	return (*this)[s1 + s2 * strides[1] + s3 * strides[2]
					+ s4 * strides[3] + s5 * strides[4]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::best_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3, size_t s4,
							size_t s5, size_t s6)
{
	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3] + s5 * strides[4] + s6 * strides[5]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::const_reference
	array_nd<T, D, P>::operator()(size_t s1) const
{
	return (*this)[s1];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::const_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2) const
{
	return (*this)[s1 + s2 * strides[1]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::const_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3) const
{
	return (*this)[s1 + s2 * strides[1] + s3 * strides[2]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::const_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3,
							size_t s4) const
{
	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
							s4 * strides[3]];
}
template<class T, class D, class P>
inline
typename array_nd<T, D, P>::const_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3,
						size_t s4, size_t s5) const
{
	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
					s4 * strides[3] + s5 * strides[4]];
}

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::const_reference
	array_nd<T, D, P>::operator()(size_t s1, size_t s2, size_t s3,
					size_t s4, size_t s5, size_t s6) const
{
	return (*this)[s1 + s2 * strides[1] + s3 * strides[2] +
			s4 * strides[3] + s5 * strides[4] + s6 * strides[5]];
}

#endif
