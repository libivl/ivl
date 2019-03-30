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
//TODO: rewrite, correct and then include
/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 class F,
		 class A,
		 class DERIVED_INFO
	     >
class array<T, data::row_elem_func_2d<F, A, DERIVED_INFO> > :

public array_base<T, typename data::row_elem_func_2d<F, A>,
		typename types::derive <array <T, data::row_elem_func_2d<F, A>,
			DERIVED_INFO> >::type>,

public array_common_base<array<T, data::row_elem_func_2d<F, A>, DERIVED_INFO> >

{

private:
	typedef array_common_base<array<T,
		data::row_elem_func_2d<F, A>, DERIVED_INFO> > common_base_class;

	typedef typename array_details::elem_func_tools<T,
		array::has_random_access::value> tool;

	friend class tool::not_a_type; // allow disabled types only in our class

protected:

	const A* in;
	size_t in_dim;
	size_t len;

	void set_input(const A* in_a, size_t d)
	{
		in = in_a;
		in_dim = d;
		len = in->size(1 - in_dim);
	}

public:

	typedef data::row_elem_func_2d<F, A> data_type;

	typedef array <T, data_type, DERIVED_INFO> this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename types::derive<this_type>::type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	//! difference type of iterators
	typedef ptrdiff_t diff_type;

	using base_class::derived;

	typedef typename array::has_random_access has_random_access;


	class const_iterator
	{
	private:
		typedef typename A::const_iterator iter;
		iter it;
		const A* in;
		size_t in_dim;

		typedef typename tool::template
			rnd_it<const_iterator>::type rnd_iter;

	public:

		// iterator_traits
		typedef typename types::t_if<has_random_access,
			std::random_access_iterator_tag,
			std::bidirectional_iterator_tag>::type iterator_category;

		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;

		// constructors
		const_iterator() { }

		const_iterator(const iter& it, const A* in, size_t in_dim)
			: it(it), in(in), in_dim(in_dim) { }

		const_iterator(const const_iterator& it)
			: it(it.it), in(it.in), in_dim(it.in_dim) { }

		// members
		T operator *() const
		{
			return F::calculate(const_iter_array(in->_iter(in_dim, it)));
		}

		// optional random access in iterator
		typename tool::brackets_ret_type operator[]
			(typename tool::brackets_arg j) const
		{
			return F::calculate(const_iter_array(in->_iter(in_dim,
				tool::add_op_void(it, j))));
		}

		// increment-decrement
		const_iterator& operator++()
		{
			++it;
			return *this;
		}
		const_iterator& operator--()
		{
			--it;
			return *this;
		}

		const_iterator operator++(int)
			{ const_iterator tmp(*this); ++(*this); return tmp; }

		const_iterator operator--(int)
			{ const_iterator tmp(*this); --(*this); return tmp; }

		// random access. enabled only if 'has_random_access'
		const_iterator& operator +=(typename tool::brackets_arg j)
		{
			tool::add_asgn(it, j);
			return *this;
		}
		const_iterator& operator -=(typename tool::brackets_arg j)
		{
			tool::sub_asgn(it, j);
			return *this;
		}
		inline rnd_iter operator +(typename tool::brackets_arg j) const
		{
			return rnd_iter(tool::add_op(it, j), in, in_dim);
		}
		inline rnd_iter operator -(typename tool::brackets_arg j) const
		{
			return rnd_iter(tool::sub_op(it, j), in, in_dim);
		}

		// difference
		difference_type operator -(const rnd_iter& a) const
		{
			return tool::dif_op_it(*this, a);
		}

		//copy same type iterator
		const_iterator& operator=(const const_iterator& o)
		{
			it = o.it;
			in = o.in;
			in_dim = o.in_dim;
			return *this;
		}

		bool operator==(const const_iterator& o) const { return (it == o.it); }
		bool operator!=(const const_iterator& o) const { return (it != o.it); }
	};

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename const_iterator::reference const_reference;
	typedef const_reference best_reference;
	typedef const_iterator best_iterator;

	const_iterator begin() const
	{
		return const_iterator(in->_begin(1 - in_dim), in, in_dim);
	}
	const_iterator end() const
	{
		return const_iterator(in->_end(1 - in_dim), in, in_dim);
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(in->_rbegin(), in, in_dim);
	}
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(in->_rend(), in, in_dim);
	}


/** @name Size functions
@{*/
	//! Get the length of the element sequence
	//! Optional length property
	size_t length() const
	{
		return len;
	}

	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/


/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	//! Returns the const element found at position offset
	//! Optional random access operator []
	T operator[](
		typename tool::brackets_arg i) const
	{
		CHECK(i >= 0 && i < length(), erange);

		return tool::brackets(in->_begin(), i);
	}
/**@}*/


/** @name Constructors
@{*/
	//! default constructor
	array() { }

	//! copy constructor
	array(const array& o)
		{ in = o.in; in_dim = o.in_dim; len = o.len; }

/**@}*/

    //! destructor
	~array() { }


};

#endif
