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

template<class T, class S>
array<size_t, data::fixed<2> > dims_for_2d(const array<T, S>& sz)
{
	if(sz.length() == 2) return sz;
	array<size_t, data::fixed<2> > r;
	if(sz.length() == 1) { r[0] = sz[0]; r[1] = 1; return r; }
	if(sz.length() == 0) { r[0] = r[1] = 0; return r; }
	size_t l = sz.length();
	while (l && sz[l-1]==1) l--;
	r[0] = sz[0];
	r[1] = sz[1];
	CHECK(l <= 2, erange);
	return r;
}

} // namespace array_details

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
 * like Fortr
 an and Matlab and not like C. So, the offset is computed like this:
 * \verbatim offset = row + column*NUMROWS \endverbatim
 */
template <class T,
		 class DERIVED_INFO
	     >
class array_nd<T, data::normal_2d<DERIVED_INFO> >:
	public
		array_common_base<array_nd<T,
			data::normal_2d<DERIVED_INFO> > >,

	public
	array_nd_details::
		basic_iterator_nd_interface<
			array_nd<T, data::normal_2d<DERIVED_INFO> > >
{
private:
	typedef array_nd prv_this_type;

	typedef typename prv_this_type::common_base_class common_base_class;

	//! The size of each dimension.
	size_dims<2> sizes;

public:
	typedef array_nd this_type;

	typedef this_type this_array_nd_type;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! return type of size_nd in that data-specific class
	typedef const size_dims<2>& size_nd_ref_type;

	//! return type of size_nd in that data-specific class
	typedef size_dims<2> stride_ref_type;

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
	T& operator()(size_t s1, size_t s2)
	{
		return derived()[s1 + sizes[0] * s2];
	}

	//! Selects a single, mutable element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	T& operator()(const array<size_t, S>& indx)
	{
		CHECK(indx.length() == 2, edims);
		return derived()[indx[0] + sizes[0] * indx[1]];
	}

	const T& operator()(size_t s1, size_t s2) const
	{
		return derived()[s1 + sizes[0] * s2];
	}

	//! Selects a single, const element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	const T& operator()(const array<size_t, S>& indx) const
	{
		CHECK(indx.length() == 2, edims);
		return derived()[indx[0] + sizes[0] * indx[1]];
	}
	//@}



/** @name Single-dimensional constructors */
/**@{*/

	//! Default constructor
	array_nd() : sizes(0, 0) {};

/** @name Multi-dimensional constructors */
/**@{*/
	//! Construct from a size_array containing the dimension sizes
	template<class S>
	array_nd(const array<size_t, S>& sz) :
		common_base_class(size_t(sz[0] * sz[1])), sizes(sz)
		{ CHECK(sz.length() == 2, edims); }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and assign scalar
	template<class S>
	array_nd(const array<size_t, S>& sz, const T& s) :
		common_base_class(size_t(sz[0] * sz[1]), s), sizes(sz)
		{ CHECK(sz.length() == 2, edims); }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and assign values from an one-dimensional C array
	template<class S>
	array_nd(const array<size_t, S>& sz, const T* ptr) :
		common_base_class(size_t(sz[0] * sz[1]), ptr), sizes(sz)
		{ CHECK(sz.length() == 2, edims); }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and an array with the values.
	template<class S, class J, class D>
	array_nd(const array<size_t, S>& sz, const array<J, D>& a) :
		common_base_class(size_t(sz[0] * sz[1]), a), sizes(sz)
		{ CHECK(sz.length() == 2, edims); }

	//! Copy constructor
	array_nd(const this_type& a) :
		common_base_class(a), sizes(a.sizes) { };

	//! Constructor using another form of array_nd
	template<class J, class S>
	array_nd(const array_nd<J, S>& a) :
		common_base_class(a), sizes(array_details::dims_for_2d(a.size()))
		{
		}

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
	size_nd_ref_type size_nd() const
	{
	 	return sizes;
	}

	//! Get the size for a specific dimension
	size_t size_nd(size_t dim) const
	{
		return sizes[dim];
	}

	//! Get the stride for each dimension
	stride_ref_type stride() const
	{
		return size_dims<2>(1, sizes[0]);
	}

	size_t stride(size_t dim) const { return (dim == 0 ? 1 : sizes[0]); }

	//! Get the size for each dimension
	size_type size() const { return size_nd(); }

	//! Get the size for a specific dimension
	size_t size(size_t dim) const
	{
		return sizes[dim];
	}

	//! Get the number of dimensions
	size_t ndims() const { return 2; }
/**@}*/

/** @name Resize Functions
@{*/
	//! resize (n-dim)
	template <class S>
	void resize(const array<size_t, S>& newsize, const T& s);

	//! resize (n-dim) without padding
	template <class S>
	void resize(const array<size_t, S>& newsize);

	//! reshape (n-dim)
	template <class S>
	void reshape(const array<size_t, S>& newsize, const T& s);

	//! reshape (n-dim) without padding
	template <class S>
	void reshape(const array<size_t, S>& newsize);


	//! init (n-dim)
	template <class S>
	void init(const array<size_t, S>& newsize, const T& s);

	//! init (n-dim) without padding
	template <class S>
	void init(const array<size_t, S>& newsize);

	void init(const this_type& a)
	{
		sizes = a.sizes;
		base_class::init(sizes[0] * sizes[1], a);
	}
/**@}*/

	// Operators

/*
TODO: do something for this

	static_indirect_array<T, false> operator[](const size_array& idx)
		{ return static_indirect_array<T, false>(idx, this->base_ptr); }

	static_mask_array<T, false> operator[](const bool_array& idx)
		{ return static_mask_array<T, false>(idx, this->get_base_ptr()); }
*/



#if 0
// TODO: have to implement

	T& operator()(size_t s1);
	T& operator()(size_t s1, size_t s2);
	T& operator()(size_t s1, size_t s2, size_t s3);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5);
	T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5, size_t s6);

	//! Selects a single, mutable element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	typename types::best_iterator<array_nd>::type::reference operator()(
			const array<size_t, S>& indx)
		{ return derived()[sub2ind(derived(), indx)]; }

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

#endif

#if 0
	NewDerived operator()(const gslice& gsl) const;
	gslice_array<T> operator()(const gslice& gsl);

	NewDerived operator()(const array<slice>& as) const;
	gslice_array<T> operator()(const array<slice>& as);
#endif


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
/*
	//! @copydoc array::operator=(const T&)
	derived_type& operator=(const T& s);

	//! Assign the content of another form of array_nd
	template<class S, class K>
	derived_type& operator=(const array_nd<T, S, K>& a)
	{ common_base_class::operator=(a); return this->derived(); }
*/
/**@}*/


};


template <class T, class P>
template <class S>
void array_nd<T, data::normal_2d<P> >
	::resize(const array<size_t, S>& newsize)
{
	CHECK(newsize.length() == 2, edims);

	array<size_t, tiny> new_stride =
		cumprod<size_t>(shift(newsize, 1, size_t(1)));

	// call array data class resize first
	array_nd_details::shrink_rearrange(*this, newsize, new_stride);
	// call array data class resize first
	base_class::resize(newsize[0] * newsize[1]);
	array_nd_details::enlarge_rearrange(*this, newsize, new_stride);

	//static_cast<typename size_dims<2>::base_class::base_class&>
	//todo: there is some strange error somewhere here
	(sizes) = newsize;
}

template <class T, class P>
template <class S>
void array_nd<T, data::normal_2d<P> >
	::resize(const array<size_t, S>& newsize, const T& s)
{
	CHECK(newsize.length() == 2, edims);

	array<size_t, tiny> new_stride =
		cumprod<size_t>(shift(newsize, 1, size_t(1)));

	// call array data class resize first
	array_nd_details::shrink_rearrange(*this, newsize, new_stride);
	// call array data class resize first
	base_class::resize(newsize[0] * newsize[1], s);
	array_nd_details::enlarge_rearrange(*this, newsize, new_stride);

	sizes = newsize;
}


template <class T, class P>
template<class S>
void array_nd<T, data::normal_2d<P> >
	::reshape(const array<size_t, S>& newsize)
{
	CHECK(newsize.length() == 2, edims);

	// call array data class resize first
	base_class::resize(newsize[0] * newsize[1]);

	static_cast<typename size_dims<2>::base_class::base_class&> (sizes) = newsize;
}

template <class T, class P>
template<class S>
void array_nd<T, data::normal_2d<P> >
	::reshape(const array<size_t, S>& newsize, const T& s)
{
	CHECK(newsize.length() == 2, edims);

	// call array data class resize first
	base_class::resize(newsize[0] * newsize[1], s);

	sizes = newsize;
}


template <class T, class P>
template<class S>
void array_nd<T, data::normal_2d<P> >
	::init(const array<size_t, S>& newsize)
{
	CHECK(newsize.length() == 2, edims);

	// call array data class init first
	base_class::init(newsize[0] * newsize[1]);

	static_cast<typename size_dims<2>::base_class::base_class&> (sizes) = newsize;
}

template <class T, class P>
template<class S>
void array_nd<T, data::normal_2d<P> >
	::init(const array<size_t, S>& newsize, const T& s)
{
	CHECK(newsize.length() == 2, edims);

	// call array data class init first
	base_class::init(newsize[0] * newsize[1], s);

	sizes = newsize;
}
