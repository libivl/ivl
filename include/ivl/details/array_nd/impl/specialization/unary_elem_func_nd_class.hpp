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




template <class T,
		 template <typename, typename> class F,
		 class A,
		 class DERIVED_INFO
	     >
class array_nd<T,
		data::unary_elem_func<F, A, DERIVED_INFO> > :

	public
	array_common_base<array_nd<T,
		data::unary_elem_func<F, A, DERIVED_INFO> > >,

	public
	array_nd_details::basic_iterator_nd_interface<array_nd<T,
		data::unary_elem_func<F, A, DERIVED_INFO> > >
{
private:
	typedef array_nd prv_this_type;
	typedef typename prv_this_type::common_base_class common_base_class;
	typedef typename prv_this_type::iter_nd_interface_class iter_nd_interface;

	class not_a_type {};

protected:
	typedef typename common_base_class::tool tool;

	typedef typename tool::brackets_arg tool_brackets_arg;

public:
	typedef array_nd this_type;

	typedef this_type this_array_nd_type;

	typedef typename types::derive<this_type>::type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! return type of size_nd in that data-specific class
	typedef typename A::size_nd_ref_type size_nd_ref_type;

	//! return type of stride in that data-specific class
	typedef typename A::stride_ref_type stride_ref_type;

#if 0
// unstable feature
	//! types that specify the defined parenthesis operators for this class
	typedef typename A::has_1d_parenthesis has_1d_parenthesis;

	typedef typename A::has_2d_parenthesis has_2d_parenthesis;

	typedef typename A::has_3d_parenthesis has_3d_parenthesis;

	typedef typename A::has_nd_parenthesis has_nd_parenthesis;
#endif

	template<bool PAST_END_CAPABLE = true>
	struct const_iterator_nd_class
	{//////////////////HERE////////////////
	private:
		typedef typename types::t_if<types::t_expr<PAST_END_CAPABLE>,
			typename A::const_iterator_nd,
			typename A::_fast_const_iterator_nd>::type iter_nd;

		iter_nd it;

	public:

		// TODO: check others types iterator_traits for nd.
		// probably wrong or missing.
		// esspecially the default iterator nd which
		// for some reason (??) questions random access.
		// iterator_traits

		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		//typedef const T* pointer;
		//typedef const T reference;
		typedef internal::pointer_face<const T> pointer;
		// using this to comply with std:: iterators. if it is not optimized-out
		// by the compiler, consider using
		// `const internal::reference_face<const T, types::skip>'
		typedef const internal::reference_face<const T, const_iterator_nd_class>
			reference;

		typedef const_iterator_nd_class this_type;

		typedef types::t_false has_base_iterator;

		struct iter_nd_border_walker
		{
			typedef typename iter_nd::iter_nd_border_walker iw_t;
			iw_t iw;

			iter_nd_border_walker() {}
			iter_nd_border_walker(ptrdiff_t x) : iw(x) { }
			iter_nd_border_walker(const iw_t& iw) : iw(iw) { }
		};

		struct iter_nd_dir_type
		{
			typedef typename iter_nd::iter_nd_dir_type id_t;
			id_t id;
			iter_nd_dir_type(const id_t& id1) : id(id1) { }
		};

		// constructors
		const_iterator_nd_class() { }
		const_iterator_nd_class(const iter_nd& it) : it(it) { }
		const_iterator_nd_class(const const_iterator_nd_class& o) : it(o.it) { }

		// members
		pointer operator ->() const
		{
			return pointer(array_details::elem_func_unary_op<
			T, F<T, typename iter_nd::value_type> >::
			from(*it));
		}

		reference operator *() const
		{
			return reference(array_details::elem_func_unary_op<
				T, F<T, typename iter_nd::value_type> >::
				from(*it), *this);
		}

		reference operator[] (ptrdiff_t j) const
		{
			return reference(array_details::elem_func_unary_op<
				T, F<T, typename iter_nd::value_type> >::
				from(it[j]),
			// hope that the below line will be optimized-out when using T.
			// or disregard the `tight' std:: standard that &(*iter) == &(*iter)
				const_iterator_nd_class(it + j));
		}

		// increment-decrement
		this_type& operator++() { ++it; return *this; }
		this_type& operator--() { --it; return *this; }

		this_type operator++(int)
			{ this_type tmp(*this); ++it; return tmp; }

		this_type operator--(int)
			{ this_type tmp(*this); --it; return tmp; }

		// random access
		this_type operator +(const ptrdiff_t j) const
			{ this_type tmp(it + j); return tmp; }

		this_type operator -(const ptrdiff_t j) const
			{ this_type tmp(it - j); return tmp; }

		this_type& operator +=(const size_t j)
			{ it += j; return *this; }

		this_type& operator -=(const size_t j)
			{ it -= j; return *this; }

		// border walker
		this_type operator +(const iter_nd_border_walker& z)
			{ this_type tmp(it + z.iw); return tmp; }

		this_type operator -(const iter_nd_border_walker& z)
			{ this_type tmp(it - z.iw); return tmp; }

		this_type& operator +=(const iter_nd_border_walker& z)
			{ it += z.iw; return *this; }

		this_type& operator -=(const iter_nd_border_walker& z)
			{ it -= z.iw; return *this; }


		iter_nd_dir_type dir() const
			{ return iter_nd_dir_type(it.dir()); }

		iter_nd_dir_type dir(ptrdiff_t x) const
			{ return iter_nd_dir_type(it.dir(x)); }

		void inc_along_other_dim_at_begin(const this_type& y)
			{ it += y.it.dir(); }

		void dec_along_other_dim_at_begin(const this_type& y)
			{ it -= y.it.dir(); }

		void move_along(const this_type& y, ptrdiff_t x)
			{ it += y.it.dir(x); }

		// difference
		ptrdiff_t operator -(const this_type& a) const
			{ return it - a.it; }

	};

	typedef const_iterator_nd_class<true> const_iterator_nd;
	typedef const_iterator_nd_class<false> _fast_const_iterator_nd;

	typedef std::reverse_iterator<const_iterator_nd> const_reverse_iterator_nd;

//YOU ARE HERE
	using base_class::derived;

	//! get base class
	base_class& base() { return *this; }
	const base_class& base() const { return *this; }

#if 0
// todo: enable when 'has *d parenthesis is implemented
// for now disable this feature for elem_funcs

	const T& operator()(size_t s1) const;
	const T& operator()(size_t s1, size_t s2) const;
	const T& operator()(size_t s1, size_t s2, size_t s3) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5) const;
	const T& operator()(size_t s1, size_t s2, size_t s3, size_t s4, size_t s5, size_t s6) const;
#endif
	//! Selects a single, const element of the array,
	//! using a size_array for the coordinates.
	template<class S>
	const T operator()(const array<size_t, S>& indx) const
	{
		return array_details::elem_func_unary_op<
			T, F<T, typename A::elem_type> >::
			from((this->in1->derived())(indx));
	}
	//@}


/** @name constructors */
/**@{*/
	//! Default constructor
	array_nd() { }

	//! construction from the reference arrays
	array_nd(const A& a1) { this->setref(a1); }

	//! Copy constructor
	array_nd(const array_nd& a) : common_base_class(a) { }
/**@}*/

/** @name filler constructors */
/**@{*/

	// Construct by defining an element count.
	explicit array_nd(size_t count) { }

	// Construct by defining an element count and a sigle default value
	array_nd(size_t count, const T& s) { }

	// Construct by defining an element count and a pointer to data.
	array_nd(size_t count, const T *data) { }

	// Construct from a size_array containing the dimension sizes
	template<class S>
	array_nd(const array<size_t, S>& sz) { }

	// construct from a size_array containing the dimension sizes and scalar
	template<class S>
	array_nd(const array<size_t, S>& sz, const T& s) { }

	//Construct from a size_array and pointer
	template<class S>
	array_nd(const array<size_t, S>& sz, const T* ptr) { }

	//Construct from a size_array and an array with the values.
	template<class S, class J, class D>
	array_nd(const array<size_t, S>& sz, const array<J, D>& a) { }

	// Constructor using another form of array_nd
	template<class J, class S>
	array_nd(const array_nd<J, S>& a) { }

/**@}*/


/** @name Size functions (multidimensional)
@{*/
	//! Get the size for each dimension
	size_nd_ref_type size_nd() const { return this->in1->size_nd(); }

	//! Get the size for a specific dimension
	size_t size_nd(size_t d) const { return this->in1->size_nd(d); }

	// todo fix this and use a tool::stride
	//! Get the stride for each dimension
	stride_ref_type stride() const
	{ return this->in1->stride(); }

	//! Get the stride for a particular
	size_t stride(size_t dim) const
	{ return this->in1->stride(dim); }

	//! Get the size for each dimension
	size_type size() const { return this->in1->size(); }

	//! Get the number of dimensions
	size_t ndims() const { return this->in1->ndims(); }
/**@}*/


};


