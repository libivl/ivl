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



//! 2-dimensional %array of type T
template <class T,
		 class OPTS = data::normal_2d<>
	     >
class array_2d :
	public
	array_common_base<array_2d<T, OPTS> >
{
private:
	typedef array_common_base<array_2d<T, OPTS> > common_base_class;

public:
	typedef array_2d this_type;

	typedef this_type this_array_2d_type;

	typedef typename this_type::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	typedef typename this_type::size_type size_type;

	using base_class::derived;

	typedef typename this_type::is_resizeable is_resizeable;

	typedef typename this_type::all_init_arg_base all_init_arg;
	typedef typename this_type::data_init_arg_base data_init_arg;

	//! get base class
	base_class& base() { return *this; }
	const base_class& base() const { return *this; }

	//! get rows
	size_t rows() const { return this->size_nd()[0]; }

	//! get columns
	size_t columns() const { return this->size_nd()[1]; }
	//! get columns, synonym
	size_t cols() const { return this->size_nd()[1]; }

	//! Check if the matrix is square
	bool is_square() const { return rows() == columns(); }

/** @name Resize Functions
@{*/
	//! resize (n-dim)
	template <class S>
	void resize(const array<size_t, S>& newsize, const T& s,
		types::static_enable_if<is_resizeable> = 0)
	{
		CHECK(newsize.length() == 2, eshape());
		base_class::resize(newsize, s);
	}

	//! resize (n-dim) without padding
	template <class S>
	void resize(const array<size_t, S>& newsize)
	{
		CHECK(newsize.length() == 2, eshape());
		base_class::resize(newsize);
	}

	//! resize (2-dim)
	void resize(size_t rows, size_t cols, const T& s,
		types::static_enable_if<is_resizeable> = 0)
	{
		base_class::resize(size_dims<2>(rows, cols), s);
	}

	//! resize (2-dim) without padding
	void resize(size_t rows, size_t cols,
		types::static_enable_if<is_resizeable> = 0)
	{
		data::call_if<is_resizeable>::
			resize(base(), size_dims<2>(rows, cols));
	}
/**@}*/

/**
 * @name Constructors
@{*/


	/**
	 * \brief Construct an empty array_2d
	 * Default constructor. Construct an empty array_2d
	 */
	array_2d() { }

	/**
	 * \brief Construct by defining rows & columns
	 *
	 * @param r Rows
	 * @param c Columns
	 */
	array_2d(size_t r, size_t c) :
		common_base_class(size_dims<2>(r, c)) {} ;

	/**
	 * \brief Construct with dimensions (rows and columns) specified in a
	 * size_dims<2> or in a size_array
	 *
	 * \warning The length of \e sz must be 2
	 *
	 * @param r Rows
	 * @param c Columns
	 */
	template <class D>
	array_2d(const array<size_t, D>& sz) :
		common_base_class(sz) {}


	/**
	 * \brief Construct by defining rows & columns and by using a single
	 * initial value for all elements.
	 *
	 * @param r Rows
	 * @param c Columns
	 * @param s Default value for all elements
	 */
	array_2d(size_t r, size_t c, const T& s) :
		common_base_class(size_dims<2>(r, c), s) {}

	/**
	 * \brief Construct with rows, columns & pointer to data
	 *
	 * @param r Rows
	 * @param c Columns
	 * @param data Pointer to the data
	 *
	 * \warning The constructor will try to read
	 * <em>r*c*size_of(T)</em> bytes from the memory pointed by \e data,
	 * without performing any kind of check. The user is responsible of
	 * making sure the memory is accessible and properly initialized.
	 */
	array_2d(size_t r, size_t c, const T* data) :
		common_base_class(size_dims<2>(r, c), data) {}


	/**
	 * \brief Construct with rows, columns & initialization argument
	 *
	 * @param r Rows
	 * @param c Columns
	 * @param data Initialization argument, used for special types of arrays
	 */
	array_2d(size_t r, size_t c, const data_init_arg& data) :
		common_base_class(size_dims<2>(r, c), data) {}


	/**
	 * \brief Construct with rows, columns & array of data
	 *
	 * @param r Rows
	 * @param c Columns
	 * @param data Array to copy the element values from
	 *
	 * \warning The size of \e data array must be at least <em>r*c</em>
	 */
	template <class J, class D>
	array_2d(size_t r, size_t c, const array<J, D>& data) :
		common_base_class(size_dims<2>(r, c), data)
		{ }



	/**
	 * \brief Construct by defining size and by using a single
	 * initial value for all elements.
	 *
	 * \warning The length of \e sz must be 2
	 *
	 * @param r Rows
	 * @param c Columns
	 * @param s Default value for all elements
	 */
	template <class D>
	array_2d(const array<size_t, D>& sz, const T& s) :
		common_base_class(sz, s) {}


	/**
	 * \brief Construct with size & pointer to data
	 *
	 * @param r Rows
	 * @param c Columns
	 * @param data Pointer to the data
	 *
	 * \warning The length of \e sz must be 2
	 *
	 * \warning The constructor will try to read
	 * <em>r*c*size_of(T)</em> bytes from the memory pointed by \e data,
	 * without performing any kind of check. The user is responsible of
	 * making sure the memory is accessible and properly initialized.
	 */
	template <class D>
	array_2d(const array<size_t, D>& sz, const T* data) :
		common_base_class(sz, data) {}

     /**
         * \brief Construct with size & initialization argument
         *
         * @param r Rows
         * @param c Columns
         * @param data Pointer to the data
         *
         */
        template <class D>
        array_2d(const array<size_t, D>& sz, const data_init_arg& data) :
                common_base_class(sz, data) {}


	/**
	 * \brief Construct with size & array of data
	 *
	 * @param r Rows
	 * @param c Columns
	 * @param data Array to copy the element values from
	 *
	 * \warning The length of \e sz must be 2
	 *
	 * \warning The size of \e data array must be at least <em>r*c</em>
	 */
	template <class D, class J, class S>
	array_2d(const array<size_t, D>& sz, const array<J, S>& data) :
		common_base_class(sz, data)
	{
		CHECK(sz.length() == 2, edims);
		CHECK(data.length() >= sz[0] * sz[1], erange);
	}

	/**
	 * \brief Construct with array_nd
	 *
	 * @param a Input data
	 * Copies data from an array_nd
	 *
	 * \warning The size_nd of the array_nd must be 2
	 */
	template <class J, class D>
	array_2d(const array_nd<J, D>& a) :
		common_base_class(a)
		{
			// code to assert 2 dimensions
			if(a.ndims() != 2) this->reshape(array_details::dims_for_2d(a.size()));
		}

	/**
	 * \brief (special for ref_iterator) Construct with non-const array_nd
	 */
	template <class J, class D>
	array_2d(array_nd<J, D>& a) :
		common_base_class(a)
		{
			// code to assert 2 dimensions
			if(a.ndims() != 2) this->reshape(array_details::dims_for_2d(a.size()));
		}


	// ----------------------

	template <class J, class D>
	array_2d(const array_2d<J, D>& a) :
		common_base_class(a)
		{ }

	//(special for ref_iterator)
	template <class J, class D>
	array_2d(array_2d<J, D>& a) :
		common_base_class(a)
		{ }

	// ----------------------

	//! Copy Constructor
	array_2d(const this_type& a) :
		common_base_class(a) {} ;



#ifdef IVL_MATLAB
	/**
	 * \brief Construct from an existing Matlab mxArray
	 *
	 * eg:
	 * \code ivl::array_2d<int> a = lrhs[0]; \endcode
	 *
	 * If the mxArray contains elements of different class
	 * than the type of the %array elements, an exception will occur
	 */
	array_2d(const mxArray* mx);
#endif



/**@}*/

/**
 * @name Assignment Operators
@{*/

	//using base_class::operator=;

	using common_base_class::operator ();

	template <class K>
	derived_type& operator=(const K& a)
	{ common_base_class::operator=(a); return derived(); }

	this_type& operator=(const this_type& a)
	{ common_base_class::operator=(a); return *this; }

	//array_2d <T, DerivedInfo>& operator=(const array_2d<T, DerivedInfo>& a)
	//	{ base_class::operator=(a); return *this; /*TODO: assure check for self assignment (in all classes!)*/ };

//
//	template<class S>
//	Derived& operator=(const array_2d<T, S>& a)
//		{ return base_class::operator=(a); /*TODO: assure check for self assignment*/ };

#ifdef IVL_MATLAB
	/**
	 * \brief Assign an existing Matlab mxArray
	 *
	 * eg:
	 * \code ivl::array_2d<int> a;
	 * a = lrhs[0]; \endcode
	 *
	 * If the mxArray contains elements of different class
	 * than the type of the %array elements, an exception will occur
	 */
	array_2d<T>& operator=(const mxArray* mx);
#endif
/**@}*/

/*
	std::ostream& print_me(std::ostream& os) const
		{ return ivl::print(os, *this); }
*/

#ifdef IVL_MATLAB
	//! \copydoc array#mx()
	mxArray* mx();
#endif

};

