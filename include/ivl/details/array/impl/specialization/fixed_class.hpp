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
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 class DERIVED_INFO,
		 int N,
		 class NAMING
	     >
class array<T, data::fixed<N, NAMING, DERIVED_INFO> >
	:
	public array_common_base<
		array<T, data::fixed<N, NAMING, DERIVED_INFO> > >,

	public array_details::fixed_storage<T, N, NAMING>
{

private:
	typedef array_common_base<array<T,
			data::fixed<N, NAMING, DERIVED_INFO> > > common_base_class;

	void try_size(size_t count) { if(count != N) throw erange(); }

	using array_details::fixed_storage<T, N, NAMING>::base_ptr;

public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef T& reference;
	typedef const T& const_reference;
	typedef reference best_reference;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	//! difference type of iterators
	typedef ptrdiff_t diff_type;

	using base_class::derived;

	// iterators
	typedef data::ptr_iterator<T, false> iterator;
	typedef data::ptr_iterator<T, true> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef iterator best_iterator;

	typedef ptrdiff_t iter_border_walker;

	iterator begin() { return iterator(base_ptr); }
	iterator end() { return iterator(base_ptr + N); }
	const_iterator begin() const { return const_iterator(base_ptr); }
	const_iterator end() const { return const_iterator(base_ptr + N); }
	reverse_iterator rbegin()
		{ return reverse_iterator(iterator(base_ptr + N)); }
	reverse_iterator rend()
		{ return reverse_iterator(iterator(base_ptr)); }
	const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(const_iterator(base_ptr + N)); }
	const_reverse_iterator rend() const
		{ return const_reverse_iterator(const_iterator(base_ptr)); }

	T* c_ptr() { return base_ptr; }
	const T* c_ptr() const { return base_ptr; }

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return N; }
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/

/** @name Resize functions
@{*/
	//! Resize does not actually resize but only assert in fixed arrays
	void resize(size_t len) { CHECK(len == length(), ecomp); }
	//! Resize does not actually resize but only assert in fixed arrays
	void resize(size_t len, const T& s) { CHECK(len == length(), ecomp); }
	//! Reshape is same as resize for 1-d arrays
	void reshape(size_t len) { resize(len); }
	void reshape(size_t len, const T& s) { resize(len, s); }
/**@}*/

	iter_border_walker first_to_last() { return this->length() - 1; }
	iter_border_walker begin_to_end() { return this->length(); }

/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	using common_base_class::operator[];

	//! Returns the const element found at position offset
	const T& operator[](size_t offset) const {
		CHECK(offset >= 0 && offset < length(), erange);
		return base_ptr[offset];
	}
	//! Returns the element found at position offset
	T& operator[](size_t offset) {
		CHECK(offset >= 0 && offset < length(), erange);
		return base_ptr[offset];
	}
/**@}*/


/** @name Constructors
@{*/
	//! Default constructor
	array() { }

	//! Construnct by defining an initial number of elements.
	explicit array(size_t count) { try_size(count); }

	//! Construnct by defining an initial number of elements.
	explicit array(int count) { try_size(count); }

	//! Construnct by defining an initial number of elements.
	explicit array(long int count) { try_size(count); }

	/** \brief Construnct by defining an initial number of elements and a
	 * default value
	 *
	 * @param count Length of the %array
	 * @param s Default value for all elements
	 */
	array(size_t count, const T& s)
		{ try_size(count); ivl::copy(*this, s, types::term()); }

	/**
	 * \brief Construct by using a C %array.
	 *
	 * @param count Length of the %array
	 * @param ptr The C %array
	 */
	array(size_t count, const T *ptr) { try_size(count); ivl::copy(*this, ptr); }

	/** \brief Construct array with rvalue */
	template <class J>
	array(const tuple_rvalue<J>& r)
		{ r.tuple_output(reftpl(*this)); }

	//! Copy-constructor
	array(const this_type& a) { ivl::copy(*this, a); }

    /** \brief construct from classes derived from array, using N elements
     *
     * Developper's note: You cannot remove the defined constructor
     * even though it is a subset of this. This is because the copy
     * constructor has a specific declaration, and should be declared
     * to override the C++ default copy-constructor which is wrong and
     * causes heap corruption.
     */
	template <class J, class S>
	array(const array<J, S>& a, size_t n)
	{
		try_size(n);
		ivl::copy_out(*this, a);
	}

	/** \brief construct from an existing array of any type.
	 */
	template <class J, class S>
	array(const array<J, S>& a)
	{
		try_size(a.length());
		ivl::copy(*this, a);
	}

    /**
     * \brief Construct from array of the same type, using (shape, array)
     *
     * This constructor has the same functionality as the (array, n)
     * constructor, but fulfills a standard construction template that
     * defines that all kinds of arrays (2d, nd etc) can be constructed with
     * derived.size(), array<..> pair
     * A difference is that this function can also accept zero length
     */
	template <class J, class S>
	array(size_t count, const array<J, S>& a)
	{
		try_size(count);
		init_size_with(a);
		//
	}


#ifdef IVL_MATLAB
	/**
	 * \brief Construct with Matlab's mxArray
	 *
	 * \warning If the mxArray contains elements of different class
	 * than the type of the %array elements, an exception will occur
	 */
	explicit array(const mxArray* mx);
#endif

/**@}*/

    //! destructor
	~array() { }


/** @name Assignement Operators
@{*/

	/**
	 * \brief Copy-Assign another array of identical type
	 *
	 * eg:
	 * \code ivl::array<int> a(10, 0);
	 * ivl::array<int> b;
	 * b = a; \endcode
	 */

	using base_class::operator=;

	this_type& operator=(const this_type& a)
	{
		common_base_class::operator=(a);
		return *this;
	}
	 /*
	this_type& operator=(const this_type& a) // LEFT IN THE CONST MODE FOR A COPY CONSTRUCTOR!
	{
		// if(this != &a) TODO: make this a rule: make clear that ...
		// Note: the data class handles the check: if(this != &a),
		// and only IF needed, so there is no case of cpu waste
		if(this == &a) return *this;
		ivl::copy(*this, a);
		return *this;
	}

	template<class S, class K>
	derived_type& operator=(const ivl::array<T, S, K>& a)
	{
		try_size(a.length());
		ivl::copy(*this, a);
		return derived();
	}
	*/
	/* operator =(const T& s) unsupported */

};

