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
class array<T, data::row_elem_func_nd<F, A>, DERIVED_INFO> :

public array_common_base<array<T, data::row_elem_func_nd<F, A>, DERIVED_INFO> >
{

private:
	typedef array_common_base<array<T,
		data::row_elem_func_nd<F, A>, DERIVED_INFO> > common_base_class;

protected:
	const A* in;

public:

	typedef data::row_elem_func_nd<F, A> data_type;

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

/*
	template<class ITER_1, class ITER_2>
	class const_iter
	{
	private:
		typedef ITER_1 iter_1;
		typedef ITER_2 iter_2;

		iter_1 i1;
		iter_2 i2;

		typedef typename tool::template
			rnd_it<const_iter<ITER_1, ITER_2> >::type rnd_iter;

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
		const_iter() { }

		const_iter(const iter_1& i1, const iter_2& i2) : i1(i1), i2(i2) { }

		const_iter(const const_iter& it) : i1(it.i1), i2(it.i2) { }

		// members
		T operator *() const
		{
			return array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename iter_1::value_type,
						typename iter_2::value_type> >::
				from(*i1, *i2);
		}

		// optional random access in iterator
		typename tool::brackets_ret_type operator[]
			(typename tool::brackets_arg j) const
		{
			return array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename iter_1::value_type,
						typename iter_2::value_type> >::
				from(typename tool::brackets(i1, j),
					typename tool::brackets(i2, j));
		}

		// increment-decrement
		const_iter& operator++()
		{
			++i1;
			++i2;
			return *this;
		}
		const_iter& operator--()
		{
			--i1;
			--i2;
			return *this;
		}

		const_iter operator++(int) { const_iter tmp(*this); ++(*this); return tmp; }
		const_iter operator--(int) { const_iter tmp(*this); --(*this); return tmp; }

		// random access. enabled only if 'has_random_access'
		const_iter& operator +=(typename tool::brackets_arg j)
		{
			tool::add_asgn(i1, j);
			tool::add_asgn(i2, j);
			return *this;
		}
		const_iter& operator -=(typename tool::brackets_arg j)
		{
			tool::sub_asgn(i1, j);
			tool::sub_asgn(i2, j);
			return *this;
		}
		inline rnd_iter operator +(typename tool::brackets_arg j) const
		{
			return rnd_iter(tool::add_op(i1, j), tool::add_op(i2, j));
		}
		inline rnd_iter operator -(typename tool::brackets_arg j) const
		{
			return rnd_iter(tool::sub_op(i1, j), tool::sub_op(i2, j));
		}

		// difference
		difference_type operator -(const rnd_iter& a) const
		{
			return tool::dif_op(*this, a);
		}

		//copy same type iterator
		const_iter& operator=(const const_iter& o)
		{
			i1 = o.i1;
			i2 = o.i2;
			return *this;
		}

		bool operator==(const const_iter& o) const { return (i1 == o.i1); }
		bool operator!=(const const_iter& o) const { return (i1 != o.i1); }
	};

	typedef const_iter<typename A1::const_iterator,
		typename A2::const_iterator> const_iterator;

CARE	typedef const_iter<typename A1::const_reverse_iterator,
		typename A2::const_reverse_iterator> const_reverse_iterator;

	//added later
	typedef typename const_iterator::reference const_reference;
	typedef const_reference best_reference;
	typedef const_iterator best_iterator;


	const_iterator begin() const { return const_iterator(in1->begin(), in2->begin()); }
	const_iterator end() const { return const_iterator(in1->end(), in2->end()); }

	const_reverse_iterator rbegin() const { return const_reverse_iterator(in1->rbegin(), in2->rbegin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(in1->rend(), in2->rend()); }
*/
#if 0
/** @name Size functions
@{*/
	//! Get the length of the element sequence
	//! Optional length property
	size_t length(typename tool::brackets_arg
		enable = typename tool::brackets_arg()) const
	{
		return tool::len_op(in1->derived());
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

		return array_details::elem_func_swap_op<SWAP_ARGS,
			T, F<T, typename A1::elem_type, typename A2::elem_type> >::
		from(tool::brackets(in1->derived(), i),
			tool::brackets(in2->derived(), i));
	}
/**@}*/


/** @name Constructors
@{*/
	//! default constructor
	array() { }

	//! copy constructor
	array(const array& o)
		{ in1 = o.in1; in2 = o.in2; }

	//! validate function called externally when an elem-func array is constructed.
	void validate()
	{
		CHECK(tool::len_valid(in1->derived(), in2->derived()), erange);
	}

/**@}*/

    //! destructor
	~array() { }

#endif
};
#endif
