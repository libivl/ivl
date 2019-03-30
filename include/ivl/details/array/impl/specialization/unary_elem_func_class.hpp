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

template <class T, class J> struct force_class;

namespace array_details {

template <template <typename, typename> class F>
struct is_not_force_elem_class : public types::t_true { };

template <>
struct is_not_force_elem_class <force_class> : public types::t_false { };

} /* namespace array_details */


/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 template <typename, typename> class F, class A,
		 class DERIVED_INFO
	     >
class array<T, data::unary_elem_func<F, A, DERIVED_INFO> > :

public array_common_base<array<T,
	data::unary_elem_func<F, A, DERIVED_INFO> > >
{

private:
	typedef array_common_base<array<T,
		data::unary_elem_func<F, A, DERIVED_INFO> > > common_base_class;

protected:
	typedef typename array::has_random_access prv_has_random_access;

	typedef array_details::elem_func_tools<typename A::elem_type,
		prv_has_random_access::value> tool;

	friend class tool::not_a_type; // allow disabled types only in our class

	typedef typename types::t_or_3<
		types::t_eq<typename A::data_type, val_repeat>,
		types::t_eq<typename A::data_type, ref_val_repeat>,
		types::is_base<data::ice_wrap_array_attr_base_identifier, 
			typename A::data_type>
		//types::is_base<data::member_identifier, typename A1::data_type>
		>::type
			in_is_scalar;

	typedef typename types::t_if<in_is_scalar,
		internal::pointer_face<A>, const A*>::type in_t;


	in_t in1;

public:

	// grant special treatment for the force_class as about the
	// is_referencing_array tag.
	// TODO: force wont be elem func any more. Act accordingly.
	typedef typename array_details::is_not_force_elem_class<F>::type
		is_referencing_array;

	typedef array this_type;

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

	typedef typename array::has_random_access has_random_access;

	class const_iterator
	{
	private:
		typedef typename A::const_iterator iter_1;

		iter_1 i1;

		typedef typename tool::template rnd_it<const_iterator>::type rnd_iter;

	public:

		// iterator_traits
		typedef typename types::t_if<has_random_access,
			std::random_access_iterator_tag,
			std::bidirectional_iterator_tag>::type iterator_category;

		typedef T value_type;
		typedef ptrdiff_t difference_type;
		//typedef const T* pointer;
		//typedef const T reference;
		typedef internal::pointer_face<const T> pointer;
		// using this to comply with std:: iterators. if it is not optimized-out
		// by the compiler, consider using
		// `const internal::reference_face<const T, types::skip>'
		typedef const internal::reference_face<const T, const_iterator>
			reference;

		// TODO: A::iter_border_walker, and correct place for this
		typedef ptrdiff_t iter_border_walker;

		// constructors
		const_iterator() { }

		const_iterator(const iter_1& i1) : i1(i1) { }

		const_iterator(const const_iterator& it) : i1(it.i1) { }

		pointer operator ->() const
		{
			return pointer(array_details::elem_func_unary_op<
			T, F<T, typename std::iterator_traits<iter_1>::value_type> >::
			from(*i1));
		}

		// members
		reference operator *() const
		{
			return reference(array_details::elem_func_unary_op<
				T, F<T, typename std::iterator_traits<iter_1>::value_type> >::
				from(*i1), *this);
		}

		// optional random access in iterator
		reference operator[]
			(typename tool::brackets_arg j) const
		{
			return reference(array_details::elem_func_unary_op<
				T, F<T, typename std::iterator_traits<iter_1>::value_type> >::
				from(tool::brackets(i1, j)),
			// hope that the below line will be optimized-out when using T.
			// or disregard the `tight' std:: standard that &(*iter) == &(*iter)
				rnd_iter(tool::add_op(i1, j)));
		}

		// increment-decrement
		const_iterator& operator++()
		{
			++i1;
			return *this;
		}
		const_iterator& operator--()
		{
			--i1;
			return *this;
		}

		const_iterator operator++(int)
			{ const_iterator tmp(*this); ++(*this); return tmp; }

		const_iterator operator--(int)
			{ const_iterator tmp(*this); --(*this); return tmp; }

		// random access. enabled only if 'has_random_access'
		const_iterator& operator +=(typename tool::brackets_arg j)
		{
			tool::add_asgn(i1, j);
			return *this;
		}
		const_iterator& operator -=(typename tool::brackets_arg j)
		{
			tool::sub_asgn(i1, j);
			return *this;
		}
		inline rnd_iter operator +(typename tool::brackets_arg j) const
		{
			return rnd_iter(tool::add_op(i1, j));
		}
		inline rnd_iter operator -(typename tool::brackets_arg j) const
		{
			return rnd_iter(tool::sub_op(i1, j));
		}

		// difference
		difference_type operator -(const rnd_iter& a) const
		{
			return tool::dif_op(i1, a.i1);
		}

		//copy same type iterator
		const_iterator& operator=(const const_iterator& o)
		{
			i1 = o.i1;
			return *this;
		}

		bool operator==(const const_iterator& o) const { return (i1 == o.i1); }
		bool operator!=(const const_iterator& o) const { return (i1 != o.i1); }
		bool operator<(const const_iterator& o) const { return (i1 < o.i1); }
		bool operator<=(const const_iterator& o) const { return (i1 <= o.i1); }
		bool operator>(const const_iterator& o) const { return (i1 > o.i1); }
		bool operator>=(const const_iterator& o) const { return (i1 >= o.i1); }
	};

	typedef typename const_iterator::reference const_reference;
	typedef const_reference best_reference;
	typedef const_iterator best_iterator;

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename const_iterator::iter_border_walker iter_border_walker;
	// TODO: correct place, same for binary elem_func, A::iter_border_walker, etc.
	iter_border_walker first_to_last() const { return this->length() - 1; }
	iter_border_walker begin_to_end() const { return this->length(); }


	const_iterator begin() const { return const_iterator(in1->begin()); }
	const_iterator end() const { return const_iterator(in1->end()); }

	const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(in1->end()); }
	const_reverse_iterator rend() const
		{ return const_reverse_iterator(in1->begin()); }


/** @name Size functions
@{*/
	//! Get the length of the element sequence
	//! Optional length property
	size_t length() const
	{
		return in1->derived().length();
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
	/*
	T operator[](
		typename tool::brackets_arg i) const
	{
		CHECK(i >= 0 && i < length(), erange);

		return array_details::elem_func_unary_op<
			T, F<T, typename A::elem_type> >::
			from(tool::brackets(in1->derived(), i));
	}*/

	const_reference operator[](
		typename tool::brackets_arg i) const
	{
		CHECK(i >= 0 && i < length(), erange);

		return (begin()[i]);
	}
/**@}*/


/** @name Special members
 *
 * class specialization specific members
 *
@{*/
	//! set the reference arrays. needs to be called exactly once right
	//! after the construction except from the corresponding constructor
	//! or the copy constructor.
	void setref(const A& a)
	{
		in1 = &a;
	}

	template <class D>
	inline bool self_overlap(const D& a) const
	{
		// Do we need to specialize this so that in1->overlap(a) call is
		// avoided? or is the inline mechanism adequate to cleverly
		// optimize it out. For now let's rely on the compiler,
		// since we've been doing this from the beginning.
		return types::r_if<is_referencing_array>(a.overlap(*in1), false);
	}

	// TODO: place
	void init(const A& a) { setref(a); }

	void init(const array& o) { setref(*o.in1); }

/**@}*/

/** @name Constructors
@{*/
	//! default constructor. setref needs to be called to complete construction.
	array() { }

	//! construction from the reference arrays
	array(const A& a) { setref(a); }

	//! copy constructor
	array(const array& o) { setref(*o.in1); }

/**@}*/

/** @name filler constructors
@{*/
	//! unused constructor with size_type
	array(size_t) {}

	//! unused constructor with size_type and T&
	array(size_t, const T&) {}

	//! unused constructor with size_type and T& or A&
	template <class J, class D>
	array(size_t, const array<J, D>&) {}

	//! unused constructor with size_type and T*
	array(size_t, const T*) {}

	//! unused constructor with other type array
	template<class J, class S>
	array(const array<J, S>& a) {}

/**@}*/
	array& operator=(const array& o)
	{
		setref(*o.in1);
		return *this;
		//TODO: check
	}

    //! destructor
	~array() { }


};

template <class T, class J>
struct force_class
{
	typedef types::number<1> cost;
	static inline T elem_op(const J& elem1)
	{
		return elem1;
	}
};
