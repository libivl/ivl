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


namespace data {

template<int N>
struct get_channels
{
	template<class A>
	inline static size_t from (const A& a) { return N; }
};

template<>
struct get_channels<0>
{
	template<class A>
	inline static size_t from (const A& a) { return a[2]; }
};

template<int N>
struct image_stride_2
{
	size_t s;
	image_stride_2(size_t sz0, size_t sz1) : s(sz0 * sz1) { }
	inline const size_t& get() const { return s; }
};

template<>
struct image_stride_2<1>
{
	image_stride_2(size_t sz0, size_t sz1) { }
	inline size_t get() const { return 0; }
};


}; //namespace data


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
		 int N,
		 class DERIVED_INFO
	     >

class array_nd<T, data::normal_image<N, DERIVED_INFO> >
	:
	public
	array_common_base<array_nd<T,
		data::normal_image<N, DERIVED_INFO> > >,

	public
	array_nd_details::basic_iterator_nd_interface<array_nd<T,
		data::normal_image<N, DERIVED_INFO> > >
{
private:
	typedef array_nd prv_this_type;
	typedef typename prv_this_type::common_base_class common_base_class;
	typedef typename prv_this_type::iter_nd_interface_class iter_nd_interface;

	//! The size of each dimension.
	size_dims<3> sizes;

	data::image_stride_2<N> stride_2;

	// disable 1-dim resize functions for this type of array

	//! resize (1-dim)
	void resize(const size_t newsize, const T& s);

	//! resize (1-dim) without padding
	void resize(const size_t newsize);

protected:

	// faster access to specific members
	inline size_t get_channels() const { return data::get_channels<N>(sizes); }

	inline size_t get_stride2() const { return stride_2.get(); }

public:
	typedef array_nd this_type;

	typedef this_type this_array_nd_type;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! return type of size_nd in that data-specific class
	typedef const size_dims<3>& size_nd_ref_type;

	//! return type of size_nd in that data-specific class
	typedef array<size_t, tiny> stride_ref_type;

	//! types that specify the defined parenthesis operators for this class
	typedef types::t_false has_1d_parenthesis;
	typedef types::t_false has_2d_parenthesis;
	typedef types::t_true has_3d_parenthesis;
	typedef types::t_false has_nd_parenthesis;

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
	T& operator()(size_t s1, size_t s2, size_t s3 = 0)
	{
		CHECK(s3 < data::get_channels<N>::from(sizes), erange);
		CHECK(s2 < sizes[1], erange);
		CHECK(s1 < sizes[0], erange);
		return derived()[s1 + sizes[0] * s2 + get_stride2() * s3];
	}

	//! Selects a single, mutable element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	T& operator()(const array<size_t, S>& indx)
	{
		CHECK(indx.length() == 2 + (N != 1) || indx.length() == 3, edims);
		CHECK(indx.length() == 2 ||
			indx[2] < data::get_channels<N>::from(sizes), erange);
		CHECK(indx[1] < sizes[1], erange);
		CHECK(indx[0] < sizes[0], erange);

		return derived()[indx[0] + sizes[0] * indx[1] +
			get_stride2() * indx[2]];
	}

	const T& operator()(size_t s1, size_t s2, size_t s3 = 0) const
	{
		CHECK(s3 < data::get_channels<N>::from(sizes), erange);
		CHECK(s2 < sizes[1], erange);
		CHECK(s1 < sizes[0], erange);
		return derived()[s1 + sizes[0] * s2 + get_stride2() * s3];
	}

	//! Selects a single, const element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	const T& operator()(const array<size_t, S>& indx) const
	{
		CHECK(indx.length() == 2 + (N != 1) || indx.length() == 3, edims);
		CHECK(indx.length() == 2 ||
			indx[2] < data::get_channels<N>::from(sizes), erange);
		CHECK(indx[1] < sizes[1], erange);
		CHECK(indx[0] < sizes[0], erange);

		return derived()[indx[0] + sizes[0] * indx[1] +
			get_stride2() * indx[2]];
	}
	//@}


/** @name Single-dimensional constructors */
/**@{*/

	//! Default constructor
	array_nd() : sizes(0, 0, 0), stride_2(0, 0) {};

/** @name Multi-dimensional constructors */
/**@{*/
	//! Construct from a size_array containing the dimension sizes
	template<class S>
	array_nd(const array<size_t, S>& sz) :
		common_base_class(sz[0] * sz[1] * data::get_channels<N>::from(sz)),
		sizes(sz[0], sz[1], data::get_channels<N>::from(sz)),
		stride_2(sz[0], sz[1])
		{ CHECK((sz.length() == 2 + (N != 1)) ||
			((N == 1) && sz.length() == 3 && sz[2] == 1), edims); }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and assign scalar
	template<class S>
	array_nd(const array<size_t, S>& sz, const T& s) :
		common_base_class(sz[0] * sz[1] * data::get_channels<N>::from(sz), s),
		sizes(sz[0], sz[1], data::get_channels<N>::from(sz)),
		stride_2(sz[0], sz[1])
		{ CHECK((sz.length() == 2 + (N != 1)) ||
			((N == 1) && sz.length() == 3 && sz[2] == 1), edims); }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and assign values from an one-dimensional C array
	template<class S>
	array_nd(const array<size_t, S>& sz, const T* ptr) :
		common_base_class(sz[0] * sz[1] * data::get_channels<N>::from(sz), ptr),
		sizes(sz[0], sz[1], data::get_channels<N>::from(sz)),
		stride_2(sz[0], sz[1])
		{ CHECK((sz.length() == 2 + (N != 1)) ||
			((N == 1) && sz.length() == 3 && sz[2] == 1), edims); }

	//! \brief Construct from a size_array containing the dimension sizes
	//! and an array with the values, or a value for the elements.
	template<class S, class J, class D>
	array_nd(const array<size_t, S>& sz, const array<J, D>& a) :
		common_base_class(sz[0] * sz[1] * data::get_channels<N>::from(sz), a),
		sizes(sz[0], sz[1], data::get_channels<N>::from(sz)),
		stride_2(sz[0], sz[1])
		{ CHECK((sz.length() == 2 + (N != 1)) ||
			((N == 1) && sz.length() == 3 && sz[2] == 1), edims); }

	//! Copy constructor
	array_nd(const this_type& a) :
		common_base_class(a), sizes(a.sizes), stride_2(a.stride_2) {};

	//! Constructor using another form of array_nd
	template<class J, class S>
	array_nd(const array_nd<J, S>& a) :
		common_base_class(a),
		sizes(a.size_nd()[0], a.size_nd()[1],
			data::get_channels<N>::from(a.size_nd())),
		stride_2(a.size_nd()[0], a.size_nd()[1])
		{ CHECK((a.size_nd().length() == 2 + (N != 1)) || ((N == 1)
			&& a.size_nd().length() == 3 && a.size_nd()[2] == 1), edims); }

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
	size_t size_nd(size_t d) const
	{
		return sizes[d];
	}

	//! Get the stride for each dimension
	stride_ref_type stride() const
	{
		return size_dims<3>(1, sizes[0], get_stride2());
	}

	//! Get the stride for a particular dimension
	size_t stride(size_t dim) const
	{
		return (dim == 0 ? 1 : (dim == 1 ? sizes[0] : get_stride2()));
	}

	//! Get the size for each dimension
	size_type size() const { return size_nd(); }
	//! Get the size for a specific dimension
	size_t size(size_t d) const { return sizes[d]; }

	//! Get the number of dimensions
	size_t ndims() const { return 3; }
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
/**@}*/

	// Operators

/**
 * @name Assignment Operators
@{*/

	using common_base_class::operator=;
	//! C++ copy-constructor
	this_type& operator=(const this_type& in)
	{ common_base_class::operator=(in); return *this; }

/**@}*/



};


template <class T, int N, class P>
template <class S>
void array_nd<T, data::normal_image<N, P> >
::resize(const array<size_t, S>& sz)
{
	CHECK((sz.length() == 2 + (N != 1)) ||
		((N == 1) && sz.length() == 3 && sz[2] == 1), edims);
	// call array data class resize first
	base_class::resize(sz[0] * sz[1] * data::get_channels<N>::from(sz));

	sizes[0] = sz[0];
	sizes[1] = sz[1];
	sizes[2] = data::get_channels<N>::from(sz);
	stride_2 = data::image_stride_2<N>(sizes[0], sizes[1]);
}

template <class T, int N, class P>
template <class S>
void array_nd<T, data::normal_image<N, P> >
::resize(const array<size_t, S>& sz, const T& s)
{
	CHECK((sz.length() == 2 + (N != 1)) ||
		((N == 1) && sz.length() == 3 && sz[2] == 1), edims);
	// call array data class resize first
	base_class::resize(sz[0] * sz[1] * data::get_channels<N>::from(sz), s);

	sizes[0] = sz[0];
	sizes[1] = sz[1];
	sizes[2] = data::get_channels<N>::from(sz);
	stride_2 = data::image_stride_2<N>(sizes[0], sizes[1]);
}


template <class T, int N, class P>
template <class S>
void array_nd<T, data::normal_image<N, P> >
::reshape(const array<size_t, S>& sz)
{
	CHECK((sz.length() == 2 + (N != 1)) ||
		((N == 1) && sz.length() == 3 && sz[2] == 1), edims);
	// call array data class resize first
	base_class::reshape(sz[0] * sz[1] * data::get_channels<N>::from(sz));

	sizes[0] = sz[0];
	sizes[1] = sz[1];
	sizes[2] = data::get_channels<N>::from(sz);
	stride_2 = data::image_stride_2<N>(sizes[0], sizes[1]);
}

template <class T, int N, class P>
template <class S>
void array_nd<T, data::normal_image<N, P> >
::reshape(const array<size_t, S>& sz, const T& s)
{
	CHECK((sz.length() == 2 + (N != 1)) ||
		((N == 1) && sz.length() == 3 && sz[2] == 1), edims);
	// call array data class resize first
	base_class::reshape(sz[0] * sz[1] * data::get_channels<N>::from(sz), s);

	sizes[0] = sz[0];
	sizes[1] = sz[1];
	sizes[2] = data::get_channels<N>::from(sz);
	stride_2 = data::image_stride_2<N>(sizes[0], sizes[1]);
}
