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
		 template <typename, typename, typename> class F,
		 class A1, class A2, bool SWAP_ARGS,
		 class DERIVED_INFO
	     >
class array_nd<T,
		data::binary_elem_func_ptr<F, A1, A2, SWAP_ARGS, DERIVED_INFO> > :

	public
	array_common_base<array_nd<T,
		data::binary_elem_func_ptr<F, A1, A2, SWAP_ARGS, DERIVED_INFO> > >,

	public
	array_nd_details::basic_iterator_nd_interface<array_nd<T,
		data::binary_elem_func_ptr<F, A1, A2, SWAP_ARGS, DERIVED_INFO > > >
{
private:
	typedef array_nd prv_this_type;
	typedef typename prv_this_type::common_base_class common_base_class;
	typedef typename prv_this_type::iter_nd_interface_class iter_nd_interface;

	class not_a_type {};

protected:
	typedef typename common_base_class::tool1 tool1;
	typedef typename common_base_class::tool2 tool2;

	typedef typename common_base_class::in1_s in1_s;
	typedef typename common_base_class::in2_s in2_s;

	typedef typename common_base_class::ptr_t ptr_t;

public:
	typedef array_nd this_type;

	typedef this_type this_array_nd_type;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type array_type;

	//! parameter of resize, in each class of the hierarchy
	typedef array<size_t, tiny> size_type;

	//! return type of size_nd in that data-specific class
	typedef typename A1::size_nd_ref_type size_nd_ref_type;

	//! return type of stride in that data-specific class
	typedef typename A1::stride_ref_type stride_ref_type;
	//typedef typename tool::template
	//	meta_nd<A1>::stride_ref_type stride_ref_type;

#if 0
// unstable feature
	//! types that specify the defined parenthesis operators for this class
	typedef typename types::t_and<
		typename A1::has_1d_parenthesis,
		typename A2::has_1d_parenthesis
		>::type has_1d_parenthesis;

	typedef typename types::t_and<
		typename A1::has_2d_parenthesis,
		typename A2::has_2d_parenthesis
		>::type has_2d_parenthesis;

	typedef typename types::t_and<
		typename A1::has_3d_parenthesis,
		typename A2::has_3d_parenthesis
		>::type has_3d_parenthesis;

	typedef typename types::t_and<
		typename A1::has_nd_parenthesis,
		typename A2::has_nd_parenthesis
		>::type has_nd_parenthesis;
#endif

	template<bool PAST_END_CAPABLE = true>
	struct const_iterator_nd_class
	{//////////////////HERE////////////////
	private:
		typedef typename types::t_if<types::t_expr<PAST_END_CAPABLE>,
			typename A1::const_iterator_nd,
			typename A1::_fast_const_iterator_nd>::type iter_nd_1;

		typedef typename types::t_if<types::t_expr<PAST_END_CAPABLE>,
			typename A2::const_iterator_nd,
			typename A2::_fast_const_iterator_nd>::type iter_nd_2;

		//typedef typename A1::const_iterator_nd iter_nd_1;
		//typedef typename A2::const_iterator_nd iter_nd_2;

		ptr_t ptr1;
		iter_nd_1 i1;
		iter_nd_2 i2;

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
			typedef typename iter_nd_1::iter_nd_border_walker iw_t_1;
			typedef typename iter_nd_2::iter_nd_border_walker iw_t_2;
			iw_t_1 iw1;
			iw_t_2 iw2;

			iter_nd_border_walker() {}
			iter_nd_border_walker(ptrdiff_t x) : iw1(x), iw2(x) { }
			iter_nd_border_walker(const iw_t_1& iw1, const iw_t_2& iw2)
				: iw1(iw1), iw2(iw2) { }
		};

		struct iter_nd_dir_type
		{
			typedef typename iter_nd_1::iter_nd_dir_type id_t_1;
			typedef typename iter_nd_1::iter_nd_dir_type id_t_2;
			id_t_1 id1;
			id_t_2 id2;
			iter_nd_dir_type(const id_t_1& id1, const id_t_2& id2)
				: id1(id1), id2(id2) { }
		};

		// constructors
		const_iterator_nd_class() { }
		const_iterator_nd_class(ptr_t p1, const iter_nd_1& i1, const iter_nd_2& i2)
			: ptr1(p1), i1(i1), i2(i2) { }
		const_iterator_nd_class(const const_iterator_nd_class& o)
			: ptr1(o.ptr1), i1(o.i1), i2(o.i2) { }

		// members
		pointer operator ->() const
		{
			return pointer(*this, array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename iter_nd_1::value_type,
						typename iter_nd_2::value_type>, in1_s, in2_s>::
				from(ptr1, *i1, *i2));
		}

 		reference operator *() const
		{
			return reference(array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename iter_nd_1::value_type,
						typename iter_nd_2::value_type>, in1_s, in2_s>::
				from(ptr1, *i1, *i2), *this);
		}

		reference operator [] (ptrdiff_t j) const
		{
			return reference(array_details::elem_func_swap_op<SWAP_ARGS,
				T, F<T, typename iter_nd_1::value_type,
						typename iter_nd_2::value_type>, in1_s, in2_s>::
				from(ptr1, i1[j], i2[j]),
				// hope that the below line will be optimized-out when using T.
				const_iterator_nd_class(ptr1, i1 + j, i2 + j));
		}

		// increment-decrement
		this_type& operator++() { ++i1; ++i2; return *this; }
		this_type& operator--() { --i1; --i2; return *this; }

		this_type operator++(int)
			{ this_type tmp(*this); ++i1; ++i2; return tmp; }

		this_type operator--(int)
			{ this_type tmp(*this); --i1; --i2; return tmp; }

		// random access
		this_type operator +(const ptrdiff_t j) const
			{ this_type tmp(i1 + j, i2 + j); return tmp; }

		this_type operator -(const ptrdiff_t j) const
			{ this_type tmp(i1 - j, i2 - j); return tmp; }

		this_type& operator +=(const size_t j)
			{ i1 += j; i2 += j; return *this; }

		this_type& operator -=(const size_t j)
			{ i1 -= j; i2 -= j; return *this; }

		// border walker
		this_type operator +(const iter_nd_border_walker& z)
			{ this_type tmp(z.ptr1, i1 + z.iw1, i2 + z.iw2); return tmp; }

		this_type operator -(const iter_nd_border_walker& z)
			{ this_type tmp(z.ptr1, i1 - z.iw1, i2 - z.iw2); return tmp; }

		this_type& operator +=(const iter_nd_border_walker& z)
			{ i1 += z.iw1; i2 += z.iw2; return *this; }

		this_type& operator -=(const iter_nd_border_walker& z)
			{ i1 -= z.iw1; i2 -= z.iw2; return *this; }


		iter_nd_dir_type dir() const
			{ return iter_nd_dir_type(i1.dir(), i2.dir()); }

		iter_nd_dir_type dir(ptrdiff_t x) const
			{ return iter_nd_dir_type(i1.dir(x), i2.dir(x)); }

		void inc_along_other_dim_at_begin(const this_type& y)
			{ i1 += y.i1.dir(); i2 += y.i2.dir(); }

		void dec_along_other_dim_at_begin(const this_type& y)
			{ i1 -= y.i1.dir(); i2 -= y.i2.dir(); }

		void move_along(const this_type& y, ptrdiff_t x)
			{ i1 += y.i1.dir(x); i2 += y.i2.dir(x); }

		// difference
		ptrdiff_t operator -(const this_type& a) const
			{ return i1 - a.i1; }

	};

	typedef const_iterator_nd_class<true> const_iterator_nd;
	typedef const_iterator_nd_class<false> _fast_const_iterator_nd;

	typedef std::reverse_iterator<const_iterator_nd>
			const_reverse_iterator_nd;

//YOU ARE HERE


	using base_class::derived;

	//! get base class
	base_class& base() { return *this; }
	const base_class& base() const { return *this; }

	/** @name Element access (multidimensional)
	 * Elements can be accessed by specifying the
	 */
	//@{
#if 0 //enable them when you make the has_?d_parenthesis feature
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
	T operator()(const array<size_t, S>& indx) const
	{
		return array_details::elem_func_swap_op<SWAP_ARGS,
			T, F<T, typename A1::elem_type, typename A2::elem_type>,
				in1_s, in2_s>::
		from((this->in1->derived())(indx), (this->in2->derived())(indx));
	}
	//@}


	// TODO: place properly
	void init(ptr_t p1, const A1& a1, const A2& a2) { this->setref(p1, a1, a2); }

	void init(const array_nd& a) { base().init(a); }


/** @name constructors */
/**@{*/
	//! Default constructor
	array_nd() { }

	//! construction from the reference arrays
	array_nd(ptr_t p1, const A1& a1, const A2& a2) { this->setref(p1, a1, a2); }

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
	size_t size(size_t d) const { return this->in1->size(d); }

	//! Get the size for each dimension
	size_type size() const { return this->in1->size(); }

	//! Get the number of dimensions
	size_t ndims() const { return this->in1->ndims(); }
/**@}*/


};


