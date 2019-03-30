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
		 template <typename, typename, typename> class F,
		 class A1, class A2, bool SWAP_ARGS,
		 class DERIVED_INFO
	     >
class array<T,
	data::binary_elem_func<F, A1, A2, SWAP_ARGS, DERIVED_INFO> > :

public array_common_base<array<T, data::
		binary_elem_func<F, A1, A2, SWAP_ARGS, DERIVED_INFO> > >

{

private:
	typedef array_common_base<array<T, data::binary_elem_func<
		F, A1, A2, SWAP_ARGS, DERIVED_INFO> > > common_base_class;

protected:
	typedef typename array::has_random_access prv_has_random_access;

	typedef typename array_details::elem_func_tools<typename A1::elem_type,
		prv_has_random_access::value> tool1;
	typedef typename array_details::elem_func_tools<typename A2::elem_type,
		prv_has_random_access::value> tool2;

	friend class tool1::not_a_type; // allow disabled types only in our class
	friend class tool2::not_a_type; // allow disabled types only in our class

	typedef typename types::t_or_3<
		types::t_eq<typename A1::data_type, val_repeat>,
		types::t_eq<typename A1::data_type, ref_val_repeat>,
		types::is_base<data::ice_wrap_array_attr_base_identifier,
			typename A1::data_type>
		//types::is_base<data::member_identifier, typename A1::data_type>
		>::type
			in1_is_scalar;

	typedef typename types::t_or_3<
		types::t_eq<typename A2::data_type, val_repeat>,
		types::t_eq<typename A2::data_type, ref_val_repeat>,
		types::is_base<data::ice_wrap_array_attr_base_identifier,
			typename A2::data_type>
		//types::is_base<data::member_identifier, typename A2::data_type>
		>::type
			in2_is_scalar;

	// we have to mask the val_repeat and ref_val_repeat types with a
	// "internal::pointer_face" class and keep them stored in the binary_elem_func_class
	// instead of referencing them (copy), because they might be created at the
	// constructor of the binary_elem_func class and thus they may be
	// destroyed before the expression is evaluated.
	// Practically this means that when one operand of the binary elem func
	// array is a single element then it is copied rather than referenced.
	// (a pseudo array with this element is also created).
	typedef typename types::t_if<in1_is_scalar,
		internal::pointer_face<A1>, const A1*>::type in1_t;

	typedef typename types::t_if<in2_is_scalar,
		internal::pointer_face<A2>, const A2*>::type in2_t;

	in1_t in1;
	in2_t in2;

	// template arguments for the elem_func_swap_op tool,
	// Note: 4/3/2013, changed. was: in1_is_scalar, in1_t, ...
	typedef typename types::t_if<in1_is_scalar, A1, types::term>::type in1_s;
	typedef typename types::t_if<in2_is_scalar, A2, types::term>::type in2_s;

	// allows swapping the arguments that are given in direct order
	template<class X, class Y>
	static inline
	const A1& ref1(const X& q1, const Y& q2)
	{ return types::r_if<types::t_expr<SWAP_ARGS> >(q2, q1); }

	template<class X, class Y>
	static inline
	const A2& ref2(const X& q1, const Y& q2)
	{ return types::r_if<types::t_expr<SWAP_ARGS> >(q1, q2); }



public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

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
		typedef typename A1::const_iterator iter_1;
		typedef typename A2::const_iterator iter_2;

		iter_1 i1;
		iter_2 i2;

		typedef typename tool1::template
			rnd_it<const_iterator>::type rnd_iter;

	public:

		// iterator_traits
		typedef typename types::t_if<has_random_access,
			std::random_access_iterator_tag,
			std::bidirectional_iterator_tag>::type iterator_category;

		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef internal::pointer_face<const T> pointer;
		// using this to comply with std:: iterators. if it is not optimized-out
		// by the compiler, consider using
		// `const internal::reference_face<const T, types::skip>'
		typedef const internal::reference_face<const T, const_iterator>
			reference;

		// constructors
		const_iterator() { }

		const_iterator(const iter_1& i1, const iter_2& i2) : i1(i1), i2(i2) { }

		const_iterator(const const_iterator& it) : i1(it.i1), i2(it.i2) { }

		// pointer
		pointer operator ->() const
		{
			return pointer(*this, array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename std::iterator_traits<iter_1>::value_type,
						typename std::iterator_traits<iter_2>::value_type>,
						in1_s, in2_s>::
				from(*i1, *i2));
		}

		// members
		reference operator *() const
		{
			return reference(array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename std::iterator_traits<iter_1>::value_type,
						typename std::iterator_traits<iter_2>::value_type>,
						in1_s, in2_s>::
				from(*i1, *i2), *this);
		}

		// optional random access in iterator
		//typename tool::brackets_ret_type

		reference operator[]
			(typename tool1::brackets_arg j) const
		{
			return reference(array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename std::iterator_traits<iter_1>::value_type,
						typename std::iterator_traits<iter_2>::value_type>,
						in1_s, in2_s>::
				from(tool1::brackets(i1, j),
					 tool2::brackets(i2, j)),
				// hope that the below line will be optimized-out when using T.
				rnd_iter(tool1::add_op(i1, j), tool2::add_op(i2, j)));
		}

		// increment-decrement
		const_iterator& operator++()
		{
			++i1;
			++i2;
			return *this;
		}
		const_iterator& operator--()
		{
			--i1;
			--i2;
			return *this;
		}

		const_iterator operator++(int)
			{ const_iterator tmp(*this); ++(*this); return tmp; }

		const_iterator operator--(int)
			{ const_iterator tmp(*this); --(*this); return tmp; }

		// random access. enabled only if 'has_random_access'
		const_iterator& operator +=(typename tool1::brackets_arg j)
		{
			tool1::add_asgn(i1, j);
			tool2::add_asgn(i2, j);
			return *this;
		}
		const_iterator& operator -=(typename tool1::brackets_arg j)
		{
			tool1::sub_asgn(i1, j);
			tool2::sub_asgn(i2, j);
			return *this;
		}
		inline rnd_iter operator +(typename tool1::brackets_arg j) const
		{
			return rnd_iter(tool1::add_op(i1, j), tool2::add_op(i2, j));
		}
		inline rnd_iter operator -(typename tool1::brackets_arg j) const
		{
			return rnd_iter(tool1::sub_op(i1, j), tool2::sub_op(i2, j));
		}

		// difference
		difference_type operator -(const rnd_iter& a) const
		{
			return tool1::dif_op(i1, a.i1);
		}

		//copy same type iterator
		const_iterator& operator=(const const_iterator& o)
		{
			i1 = o.i1;
			i2 = o.i2;
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
	typedef const_iterator best_iterator;
	typedef const_reference best_reference;


	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef ptrdiff_t iter_border_walker;

	const_iterator begin() const
		{ return const_iterator(in1->begin(), in2->begin()); }
	const_iterator end() const
		{ return const_iterator(in1->end(), in2->end()); }

	const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(in1->rbegin(), in2->rbegin()); }
	const_reverse_iterator rend() const
		{ return const_reverse_iterator(in1->rend(), in2->rend()); }

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

	iter_border_walker first_to_last() { return this->length() - 1; }
	iter_border_walker begin_to_end() { return this->length(); }


	using common_base_class::operator [];

/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	//! Returns the const element found at position offset
	//! Optional random access operator []
	/*
	T operator[](
		typename tool1::brackets_arg i) const
	{
		CHECK(i >= 0 && i < length(), erange);

		return array_details::elem_func_swap_op<SWAP_ARGS,
			T, F<T, typename A1::elem_type, typename A2::elem_type>,
				in1_s, in2_s>::
		from(tool1::brackets(in1->derived(), i),
			tool2::brackets(in2->derived(), i));
	}*/
	const_reference operator[](
		typename tool1::brackets_arg i) const
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
	//! validate function called externally when an elem-func array is constructed.
	void validate()
	{
		CHECK(in1->length() == in2->length(), eshape);
	}

	//! set the reference arrays. needs to be called exactly once right
	//! after the construction except from the corresponding constructor
	//! or the copy constructor.
	void setref(const A1& a1, const A2& a2)
	{
		in1 = &a1;
		in2 = &a2;
		validate();
	}

	template <class A>
	bool self_overlap(const A& a) const
	{
		return a.overlap(*in1) || a.overlap(*in2);
	}
/**@}*/

	// TODO: proper place
	void init(const A1& a1, const A2& a2) { setref(a1, a2); }

	void init(const array& o) { setref(*o.in1, *o.in2); }


/** @name Constructors
@{*/
	//! default constructor. setref needs to be called to complete construction.
	array() {}

	//! construction from the reference arrays
	array(const A1& a1, const A2& a2) { setref(a1, a2); }

	//! copy constructor
	array(const array& o) { setref(*o.in1, *o.in2); }

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

    //! destructor
	~array() { }

};

