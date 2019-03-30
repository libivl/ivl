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
 * This class defines an always empty array that devours everything.
 */
template <class T,
		 class DERIVED_INFO
	     >
class array<T, data::blackhole<DERIVED_INFO> > :
	public array_common_base<array<T, data::blackhole<DERIVED_INFO> > >
{

private:
	typedef array_common_base<array<
		T, data::blackhole<DERIVED_INFO> > > common_base_class;

protected:

public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef T const_reference;
	typedef T reference;
	typedef reference best_reference;

	typedef typename this_type::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef size_t size_type;

	using base_class::derived;

	struct iter_border_walker {
		iter_border_walker() {}
		iter_border_walker(ptrdiff_t) {}
		template <class IT>
		iter_border_walker(const IT&, const IT&) {}
	};



	class iterator
	: public types::border_walker_iterator_identifier
	{
	public:
		// iterator_traits
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename types::remove_const<T>::type value_type;
		typedef ptrdiff_t difference_type;
		typedef value_type* pointer;
		typedef value_type reference;

		// border_walker
		// iavr: changes meaning of visible type
		// typedef typename array::iter_border_walker iter_border_walker;

		iterator() { }
		iterator(const iterator& it) { }

		iterator& operator++() { return *this; }
		iterator& operator--() { return *this; }

		iterator operator++(int) { return iterator(); }
		iterator operator--(int) { return iterator(); }

		// random access
		iterator operator +(const difference_type i) const
			{ return iterator(); }
		iterator operator -(const difference_type i) const
			{ return iterator(); }
		iterator& operator +=(const difference_type i) { return *this; }
		iterator& operator -=(const difference_type i) { return *this; }

		T operator *() const { return T(); }

		T* operator ->() const { return NULL; }

		T operator [] (size_t j) const { return T(); }

		iterator& operator=(const iterator& it) { return *this; }

		bool operator==(const iterator& it) const { return true; }
		bool operator!=(const iterator& it) const { return false; }

	};

	class const_iterator
	: public types::border_walker_iterator_identifier
	{
	public:
		// iterator_traits
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename types::remove_const<T>::type value_type;
		typedef ptrdiff_t difference_type;
		typedef const value_type* pointer;
		typedef const value_type& reference;

		// border_walker
		// iavr: changes meaning of visible type
		// typedef typename array::iter_border_walker iter_border_walker;

		const_iterator() { }
		const_iterator(const iterator& it) { }
		const_iterator(const const_iterator& it) { }

		const_iterator& operator++() { return *this; }
		const_iterator& operator--() { return *this; }

		const_iterator operator++(int) { return const_iterator(); }
		const_iterator operator--(int) { return const_iterator(); }

		// random access
		const_iterator operator +(const difference_type i) const
			{ return const_iterator(); }
		const_iterator operator -(const difference_type i) const
			{ return const_iterator(); }
		const_iterator& operator +=(const difference_type i) { return *this; }
		const_iterator& operator -=(const difference_type i) { return *this; }

		const T operator *() const { return T(); }

		const T* operator ->() const { return NULL; }

		const T operator [] (size_t j) const { return T(); }

		const_iterator& operator=(const const_iterator& it) { return *this; }

		bool operator==(const const_iterator& it) const { return true; }
		bool operator!=(const const_iterator& it) const { return false; }

	};


	typedef iterator best_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	iterator begin() { return iterator(); }
	iterator end() { return iterator(); }
	reverse_iterator rbegin() { return iterator(); }
	reverse_iterator rend() { return iterator(); }
	const_iterator begin() const { return const_iterator(); }
	const_iterator end() const { return const_iterator(); }
	const_reverse_iterator rbegin() const { return const_iterator(); }
	const_reverse_iterator rend() const { return const_iterator(); }

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return 0; }
	//! Get the size of the array. generic-class function.
	size_type size() const { return 0; }
	//! Get the length of the element sequence
	size_t numel() const { return 0; }
/**@}*/

	iter_border_walker first_to_last() { return iter_border_walker(); }
	iter_border_walker begin_to_end() { return iter_border_walker(); }

/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	//! Returns the element found at position offset
	//! does not do any range checking. so it is allowed to
	//! do read-only access to any element of a blackhole array
	//! though it will always be 0. this special feature might
	//! be of use for some special functions.
	T operator[] (size_t i) const { return T(); }
/**@}*/

	//static derived_type instance;


//-----------------------------------------------------------------------------
//init

	void init() { }

	void init(const this_type& ) { }

	//! unused constructor with size_type
	void init(size_t) {}

	//! unused constructor with size_type and T&
	void init(size_t, const T&) {}

	//! unused constructor with size_type and T& or A&
	template <class J, class S>
	void init(size_t, const array<J, S>&) {}

	//! unused constructor with size_type and T*
	void init(size_t, const T*) {}

	//! unused constructor with other type array
	template<class J, class S>
	void init(const array<J, S>& a) {}

//-----------------------------------------------------------------------------

/** @name Constructors
@{*/
	//! Default constructor.
	array() { }

	//! Copy-constructor
	array(const this_type& a) { }

    //! destructor
	~array() { }
/**@}*/


/** @name filler chain constructors
@{*/
	//! unused constructor with size_type
	array(size_t) {}

	//! unused constructor with size_type and T&
	array(size_t, const T&) {}

	//! unused constructor with size_type and T& or A&
	template <class J, class S>
	array(size_t, const array<J, S>&) {}

	//! unused constructor with size_type and T*
	array(size_t, const T*) {}

	//! unused constructor with other type array
	template<class J, class S>
	array(const array<J, S>& a) {}

/**@}*/


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
	this_type& operator=(const this_type& a) { return *this; }

	template<class X>
	derived_type& operator=(const X& t) { return this->derived(); }


};


