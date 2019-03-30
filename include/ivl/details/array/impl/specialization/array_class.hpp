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


// data::normal is defined in data_base.hpp

/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T, class OPTS = data::mem<> >
class array:

	public array_common_base<array<T, OPTS> >,

	public std::vector<T>
{
private:
	typedef array_common_base<array<T, OPTS> > common_base_class;

public:
	typedef typename types::t_not<types::is_bool<T> >::type has_c_ptr;

	typedef typename common_base_class::data_type data_type;

	typedef array <T, OPTS> this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename this_type::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	//! difference type of iterators
	typedef ptrdiff_t diff_type;

	using base_class::derived;

	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;
	typedef typename std::vector<T>::reverse_iterator reverse_iterator;
	typedef typename std::vector<T>::
		const_reverse_iterator const_reverse_iterator;
	using std::vector<T>::begin;
	using std::vector<T>::end;
	using std::vector<T>::rbegin;
	using std::vector<T>::rend;

	using std::vector<T>::empty;

	typedef iterator best_iterator;
	typedef typename const_iterator::reference const_reference;
	typedef typename iterator::reference reference;
	typedef reference best_reference;

	using common_base_class::assign; // vector assign is not used
	// left here along with array.assign() for now, however might be removed.
	using std::vector<T>::assign;

	void clear()
	{
		std::vector<T>().swap(static_cast<std::vector<T>&>(*this));
	}

	void swap(std::vector<T>& v)
	{
		std::vector<T>::swap(v);
	}

	//TODO: fix
	template<class J, class D>
	void swap(array<J, D>& a)
	{
		this->derived() = a.derived();
	}
	/*template <class J, class D, class P>
	void swap(array_nd<J, D, P>& a)
	{
		// error: can't swap array with array_nd.
		throw(ecomp);
	}*/

	//TODO: what happens with resize? with base members. do resolve.
	//in need, create resize function here that does the right thing.
	using std::vector<T>::resize;

	//! Reshape is same as resize for 1-d arrays
	void reshape(size_t len) { resize(len); }
	void reshape(size_t len, const T& s) { resize(len, s); }


/** @name init member function
@{*/
	//! Init is behaves exactly like the constructor. See constructor reference.
	void init() { this->clear(); }

	//! Init is behaves exactly like the constructor. See constructor reference.
	void init(size_t count) { this->resize(count); /* does not need to keep data */ }

	//! Init is behaves exactly like the constructor. See constructor reference.
	void init(int count) { this->init(size_t(count)); }

	//! Init is behaves exactly like the constructor. See constructor reference.
	void init(long int count) { this->init(size_t(count)); }

	//! Init is behaves exactly like the constructor. See constructor reference.
	void init(size_t count, const T& s) { std::vector<T>::assign(count, s); }

	//! Init is behaves exactly like the constructor. See constructor reference.
	void init(size_t count, const T *ptr) { std::vector<T>::assign(ptr, ptr + count); }

	//! Init is behaves exactly like the constructor. See constructor reference.
	template <class J>
	void init(const tuple_rvalue<J>& r)
		{ this->clear(); r.tuple_output(reftpl(*this)); }

	//! Init is behaves exactly like the constructor. See constructor reference.
	void init(const array& a) { std::vector<T>::assign(a.begin(), a.end()); }

	//! Init is behaves exactly like the constructor. See constructor reference.
	template <class J, class S>
	void init(const array<J, S>& a, size_t n)
	{
		std::vector<T>::resize(n > 0 ? n : a.length());
		ivl::copy_out(*this, a);
	}

	//! Init is behaves exactly like the constructor. See constructor reference.
	template <class J, class S>
	void init(const array<J, S>& a)
	{
		// This implementation needs us to be careful.
		// while  : std::vector<T>(a.begin(), a.end()) { } is always valid,
		// it consumes double time of iteration for non-random-access arrays.
		// so we will have to specialize it.
		std::vector<T>::resize(0);
		array_details::
			vector_initializer<array<T, S>::has_random_access::value>
			::operate(static_cast<std::vector<T>&>(*this), a);
	}

	//! Init is behaves exactly like the constructor. See constructor reference.
	template <class J, class S>
	void init(size_t count, const array<J, S>& a)
	{
		std::vector<T>::resize(count);
		this->init_size_with(a);
	}

/**@}*/

	/*
	void resize(size_t sz)
	{
		if(sz == 0)
			std::vector<T>().swap(static_cast<std::vector<T>&>(*this));
		else
			std::vector<T>::resize(sz);
	}

	void resize(size_t sz, const T& s)
	{
		if(sz == 0)
			std::vector<T>().swap(static_cast<std::vector<T>&>(*this));
		else
			std::vector<T>::resize(sz, s);
	}
	*/
	/*
	void reset(size_t sz, const T s = T())
	{
		if(sz == 0 || sz > std::vector<T>::capacity()
			|| sz < std::vector<T>::capacity() / 2)
			std::vector<T>().swap(static_cast<std::vector<T>&>(*this));
		else
			std::vector<T>::resize(0);

		std::vector<T>::resize(sz, s);
	}
	*/

	typedef ptrdiff_t iter_border_walker;

	// TODO:
	// warning: since bit vector does not return an actual pointer
	// this function is deceiving cause it doesn't return an actual c_ptr!
	// the solution to remove c_ptr from vector is not an option.
	// to remove it from bool vector is an option, or another option
	// is to get the bitmap data some way.
	// also would we need to have the pseudo pointer in some occasions?
	// by let's say another function, ptr(). ?
	typename std::vector<T>::pointer c_ptr()
		{ return &(std::vector<T>::operator[](0)); }
	typename std::vector<T>::const_pointer c_ptr() const
		{ return &(std::vector<T>::operator[](0)); }

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return std::vector<T>::size(); }
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/

	iter_border_walker first_to_last() const { return this->length() - 1; }
	iter_border_walker begin_to_end() const { return this->length(); }

/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	//! Returns the const element found at position offset
	typename std::vector<T>::const_reference operator[](size_t offset) const
	{
		CHECK(offset >= 0 && offset < length(), erange);
		return std::vector<T>::operator[](offset);
	}
	//! Returns the element found at position offset
	typename std::vector<T>::reference operator[](size_t offset)
	{
		CHECK(offset >= 0 && offset < length(), erange);
		return std::vector<T>::operator[](offset);
	}

	using common_base_class::operator[];

/**@}*/


/** @name Constructors
@{*/
	//! Default constructor
	array() { }

	//! Construct by defining an initial number of elements.
	explicit array(size_t count) : std::vector<T>(count) { }

	//! Construct by defining an initial number of elements.
	explicit array(int count) : std::vector<T>(size_t(count)) { }

	//! Construct by defining an initial number of elements.
	explicit array(long int count) : std::vector<T>(size_t(count)) { }

	/** \brief Construct by defining an initial number of elements and a
	 * default value
	 *
	 * @param count Length of the %array
	 * @param s Default value for all elements
	 */
	array(size_t count, const T& s) : std::vector<T>(count, s) { }

	/**
	 * \brief Construct by using a C %array.
	 *
	 * @param count Length of the %array
	 * @param ptr The C %array
	 */
	array(size_t count, const T *ptr) : std::vector<T>(ptr, ptr + count) { }


	/**
	 * \brief Construct by using a C %array.
	 *
	 * @param arr The C %array
	 */
	template<class S, int J>
	array(S (&arr)[J]) : std::vector<T>(arr, arr + J) { }


	/** \brief Construct array with rvalue */
	template <class J>
	array(const tuple_rvalue<J>& r)
		{ r.tuple_output(reftpl(*this)); }

	//! Copy-constructor
	array(const array& a) : std::vector<T>(a.begin(), a.end()) { }

    /** \brief construct from classes derived from array, using N elements
     *
     * Developer's note: You cannot remove the defined constructor (above)
     * even though it is a subset of this. This is because the copy
     * constructor has a specific declaration, and should be declared
     * to override the C++ default copy-constructor which is wrong and
     * causes heap corruption.
     */
	template <class J, class S>
	inline
	array(const array<J, S>& a, size_t n) :
		std::vector<T>(n > 0 ? n : a.length())
	{
		ivl::copy_out(*this, a);
	}


	/** \brief construct from an existing array of any type.
	 */
	template <class J, class S>
	array(const array<J, S>& a)
	{
		// This implementation needs us to be careful.
		// while  : std::vector<T>(a.begin(), a.end()) { } is always valid,
		// it consumes double time of iteration for non-random-access arrays.
		// so we will have to specialize it.
		array_details::
			vector_initializer<array<T, S>::has_random_access::value>
			::operate(static_cast<std::vector<T>&>(*this), a);
	}

    /**
     * \brief Construct from array of the same type, using (shape, array)
     *
     * This constructor has the same functionality as the (array, n)
     * constructor, but fulfills a standard construction template that
	 * defines that all kinds of arrays (2d, nd etc) can be constructed with
     * derived.size(), array<..> pair
     * A difference is that this function can also accept zero length
     * Also, if a is T or similar to the element type of the array
     * this constructor fills in the array with count copies of the element a.
     */
	template <class J, class S>
	array(size_t count, const array<J, S>& a) : std::vector<T>(count)
	{
		this->init_size_with(a);
	}




/**@}*/

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
	template<class K>
	derived_type& operator=(const K& k)
	{
		common_base_class::operator=(k);
		return derived();
	}
	//using common_base_class::operator=;
	this_type& operator=(const this_type& a) // LEFT IN THE CONST MODE FOR A COPY CONSTRUCTOR!
	{
		// if(this != &a) TODO: make this a rule: make clear that ...
		// Note: the data class handles the check: if(this != &a),
		// and only IF needed, so there is no case of cpu waste
		common_base_class::operator=(a);
		return *this;
	}


	/*
	template<class S, class K>
	derived_type& operator=(const ivl::array<T, S, K>& a)
	{
		common_base_class::operator=(a);
		return derived();
	}

	derived_type& operator=(const T& s)
	*/



};

