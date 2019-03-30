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

#ifndef IVL_ARRAY_ND_DETAILS_ARRAY_ND_COMMON_BASE_HPP
#define IVL_ARRAY_ND_DETAILS_ARRAY_ND_COMMON_BASE_HPP

namespace ivl {

template<class T, class OPTS>
class array_common_base<array_nd<T, OPTS> >
	:
	public array<T, typename types::derive_opts<
		array_nd<T, OPTS> >::type>,

	public array_common_base<common_container_base<T,
		array_nd<T, OPTS> > >
{
private:
	typedef array_nd<T, OPTS> t;

	typedef array<T, typename types::
		derive_opts<array_nd<T, OPTS> >::type> prv_base_class;

	typedef array_common_base<common_container_base<T,
		array_nd<T, OPTS> > > prv_common;

	typedef array_common_base this_type;

protected:
	typedef this_type common_base_class;

public:
	typedef t array_nd_type;
	typedef t current_type;
	typedef t container_type;
	typedef t array_nd_or_2d_type;
	typedef typename this_type::elem_type elem_type;
	typedef prv_base_class base_class;
	typedef typename this_type::derived_type derived_type;

	// define _arg_base to solve weird msvc2005 bug
	typedef typename prv_base_class::all_init_arg all_init_arg_base;
	typedef typename prv_base_class::data_init_arg data_init_arg_base;
	typedef all_init_arg_base all_init_arg;
	typedef data_init_arg_base data_init_arg;

	t& to_array_nd() { return static_cast<t&>(*this); }
	const t& to_array_nd() const { return static_cast<const t&>(*this); }
	t& to_current() { return static_cast<t&>(*this); }
	const t& to_current() const { return static_cast<const t&>(*this); }


	t& derived() { return static_cast<derived_type&>(to_array_nd()); }
	const t& derived() const { return static_cast<const derived_type&>(to_array_nd()); }


	//! default constructor
	array_common_base() { }

	//! copy constructor
	array_common_base(const array_common_base& a) : base_class(a) { }

	//! chain constructor with all_init_arg (for special array types)
	array_common_base(all_init_arg y) : base_class(y) { }

	//! chain constructor with size_type
	array_common_base(size_t x) : base_class(x) { }

	//! chain constructor with size_type and T&
	array_common_base(size_t x, const T& y) : base_class(x, y) { }

	//! chain constructor with size_type and const T*
	array_common_base(size_t x, const T* y) : base_class(x, y) { }

	//! chain constructor with size_type and data_init_arg (special arg)
	array_common_base(size_t x, data_init_arg y) : base_class(x, y) { }

	//! chain constructor with size_t and other array or element
	template<class J, class S>
	array_common_base(size_t x, const array<J, S>& y)
		: base_class(x, y) { }

	//! chain constructor with size_t and other array or element
	//
	template<class J, class S>
	array_common_base(size_t x, array<J, S>& y)
		: base_class(x, y) { }

	//! chain constructor with other array
	template<class J, class S>
	array_common_base(const array<J, S>& x) : base_class(x) { }

	//! (special for ref_iterator) chain constructor with other array
	template<class J, class S>
	array_common_base(array<J, S>& x) : base_class(x) { }

	// Basic array_nd functions

	/*template <class S, class K>
	bool isequal(const array_nd<T, S, K>& o)
	{
		return ivl::isequal(to_array_nd(), o);
	}*/

	// indexing with an array of int instead of size_t!
	template<class S>
	typename std::iterator_traits<typename types::best_iterator<array_common_base>::type>::reference operator()(
			const array<int, S>& indx)
	{
		return derived()(cast<size_t>(indx));
	}
	template<class S>
	typename std::iterator_traits<typename array_common_base::const_iterator>::reference operator() (
			const array<int, S>& indx) const
	{
		return derived()(cast<size_t>(indx));
	}


	// group of const subarrays :)
	template <class S>
	ivl::subarray<const t, array<index_array, S> > operator()
		(const array<index_array, S>& indx) const
	{
		return ivl::subarray<const t, array<index_array, S> >(to_array_nd(), indx);
	}

	ivl::subarray<const t, array<index_array, fixed<2> > > operator()
		(const index_array& idxn, const index_array& idx2) const
	{
		return ivl::subarray<const t, array<index_array, fixed<2> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2));
	}

	ivl::subarray<const t, array<index_array, fixed<3> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3) const
	{
		return ivl::subarray<const t, array<index_array, fixed<3> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3));
	}

	ivl::subarray<const t, array<index_array, fixed<4> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4) const
	{
		return ivl::subarray<const t, array<index_array, fixed<4> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3, idx4));
	}

	ivl::subarray<const t, array<index_array, fixed<5> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4,
			const index_array& idx5) const
	{
		return ivl::subarray<const t, array<index_array, fixed<5> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3, idx4, idx5));
	}

	ivl::subarray<const t, array<index_array, fixed<6> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4,
			const index_array& idx5, const index_array& idx6) const
	{
		return ivl::subarray<const t, array<index_array, fixed<6> > >(
			to_array_nd(),
				ivl::array_data<index_array>(idxn, idx2, idx3, idx4, idx5, idx6));
	}

	ivl::subarray<const t, array<index_array, fixed<7> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4,
			const index_array& idx5, const index_array& idx6,
			const index_array& idx7) const
	{
		return ivl::subarray<const t, array<index_array, fixed<7> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3, idx4, idx5,
												 idx6, idx7));
	}


	// group of non-const subarrays !

	template <class S>
	ivl::subarray<t, array<index_array, S> > operator()
		(const array<index_array, S>& indx)
	{
		return ivl::subarray<t, array<index_array, S> >(to_array_nd(), indx);
	}

	ivl::subarray<t, array<index_array, fixed<2> > > operator()
		(const index_array& idxn, const index_array& idx2)
	{
		return ivl::subarray<t, array<index_array, fixed<2> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2));
	}

	ivl::subarray<t, array<index_array, fixed<3> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3)
	{
		return ivl::subarray<t, array<index_array, fixed<3> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3));
	}

	ivl::subarray<t, array<index_array, fixed<4> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4)
	{
		return ivl::subarray<t, array<index_array, fixed<4> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3, idx4));
	}

	ivl::subarray<t, array<index_array, fixed<5> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4,
			const index_array& idx5)
	{
		return ivl::subarray<t, array<index_array, fixed<5> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3, idx4, idx5));
	}

	ivl::subarray<t, array<index_array, fixed<6> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4,
			const index_array& idx5, const index_array& idx6)
	{
		return ivl::subarray<t, array<index_array, fixed<6> > >(
			to_array_nd(),
				ivl::array_data<index_array>(idxn, idx2, idx3, idx4, idx5, idx6));
	}

	ivl::subarray<t, array<index_array, fixed<7> > > operator()
		(const index_array& idxn, const index_array& idx2,
			const index_array& idx3, const index_array& idx4,
			const index_array& idx5, const index_array& idx6,
			const index_array& idx7)
	{
		return ivl::subarray<t, array<index_array, fixed<7> > >(
			to_array_nd(), ivl::array_data<index_array>(idxn, idx2, idx3, idx4, idx5,
												 idx6, idx7));
	}
	// end of group of subarrays

	// TODO: deprecated
	typedef ivl::subarray<t, array<index_array, data::stack<3> > > subarray_type;
	typedef ivl::subarray<const t, array<index_array, data::stack<3> > > const_subarray_type;

	typedef subarray_type subbox_type;
	typedef const_subarray_type const_subbox_type;

	//
	typedef ivl::subarray<t, array<index_array, data::stack<3> > > subarray;
	typedef ivl::subarray<const t, array<index_array, data::stack<3> > > const_subarray;

	typedef subarray_type box;
	typedef const_subarray_type const_box;
	//


	// -----------------------------------------------------------------------
/*	template<class T2, class S2>
	ivl::concat<const derived_type, const array_nd<T2, S2>, 1>
	operator|(const array_nd<T2, S2>* r)
	{
		return ivl::concat<const derived_type, const array_nd<T2, S2>, 1>
		(derived(), *r);
	}
*/
#if 0
	template<class A2>
	ivl::concat<const derived_type, const A2, 1>
	operator|(const A2* r)
	{
		return ivl::concat<const derived_type, const A2, 1>
		(derived(), *r);
	}

	template<class A2>
	ivl::concat<const derived_type, const A2, 0>
	operator-(const A2* r)
	{
		return ivl::concat<const derived_type, const A2, 0>
		(derived(), *r);
	}
#endif
	/*
	template<class T2, class S2>
	ivl::concat<const derived_type, const array_nd<T2, S2>, 0>
	operator-(const array_nd<T2, S2>* r)
	{
		return ivl::concat<const derived_type, const array_nd<T2, S2>, 0>
		(derived(), *r);
	}*/

	//propagation of operator =
	using base_class::operator=;
	array_common_base& operator=(const array_common_base& a)
	{
		base_class::operator=(a);
		return *this;
	}

	using prv_common::operator-;
	using prv_common::operator+;
	using prv_common::operator|;
	using prv_common::operator~;
	using prv_common::operator!;
	using prv_common::operator*;
	using prv_common::operator->*;

	//note: should not really be implemented for readonly arrays...
	template<class S>
	void swap(array_nd<T, S>& a)
	{
		typedef typename array_nd<T, S>::derived_type::size_type sz_t;
		sz_t sz = a.derived().size_nd();
		types::r_resize(a.derived(), to_array_nd().derived().size_nd());
		types::r_resize(to_array_nd().derived(), sz);
	}

#if 0
// TODO: have to implement

	NewDerived operator()(const gslice& gsl) const;
	gslice_array<T> operator()(const gslice& gsl);

	NewDerived operator()(const array<slice>& as) const;
	gslice_array<T> operator()(const array<slice>& as);
#endif


#ifdef IVL_MATLAB
	/**
	 * \brief Assign an existing Matlab mxArray
	 *
	 * eg:
	 * \code ivl::array_nd<int> a;
	 * a = lrhs[0]; \endcode
	 *
	 * If the mxArray contains elements of different class
	 * than the type of the %array elements, an exception will occur
	 */
	derived_type& operator=(const mxArray* mx);
#endif

/**@}*/


/** @name Print Functions
@{*/
	std::ostream& print(std::ostream& os) const;
/**@}*/



#ifdef IVL_MATLAB
	//! \copydoc array#mx()
	mxArray* mx() const;
#endif

};

} /* namespace ivl */

#endif // IVL_ARRAY_ND_DETAILS_ARRAY_ND_COMMON_BASE_HPP
