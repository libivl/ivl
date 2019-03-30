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

/*! \file array_nd_functions.hpp
    \brief Functions associated with array_nd structure

*/

#ifndef IVL_ARRAY_ND_DETAILS_ARRAY_ND_FUNCTIONS_HPP
#define IVL_ARRAY_ND_DETAILS_ARRAY_ND_FUNCTIONS_HPP

#include <limits>

namespace ivl {

//--------------------------------------------------------------
// array_nd MEMBER FUNCTIONS

namespace array_nd_details {


} /* namespace array_nd_details */

//--------------------------------------------------------------
// array_nd NON-MEMBER FUNCTIONS

/**
 * @name Array_nd non-member functions
 * \relates array_nd
 *
@{*/

#if 0 // this find is now implemented as an ivl function:

/**
 * \brief Find elements in an array_nd
 *
 * @return Array of index vectors for found elements
 */
template<class T, class S>
inline
array<array<size_t, stack<3> > > find(
	const array_nd<T, S>& a, const T& what)
{
	array<array<size_t, stack<3> > > b(0);
	size_t n = 0;

	for (size_t i = 0; i < a.length(); i++)
		if (a[i] == what)
			b.push_back(ind2sub(a, i));

	return b;
}
#endif

//! \brief returns index vector from single-dimension index
template<class T, class S>
inline
array<size_t, stack<3> > ind2sub(const array_nd<T, S>& a, size_t s)
{
	CHECK (s <= a.length(), erange());

	array<size_t, stack<3> > b(a.ndims());

	for (size_t i = 0; i < b.length(); i++) {
		b[b.length() - i - 1] = s / a.stride()[b.length() - i - 1];
		s %= a.stride()[b.length() - i - 1];
	}

	return b;
}

// iavr: vectorized version
//! \brief returns index vector from single-dimension index
template<class T1, class S1, class T2, class S2>
inline
array<array<size_t, stack<3> > > ind2sub(const array_nd<T1, S1>& a, const array<T2, S2> s)
{
	//CHECK (s <= a.length(), erange());

	array<array<size_t, stack<3> > > b(s.length());

	for (size_t n = 0; n < s.length(); n++)
		b[n] = ind2sub(a, s[n]);

	return b;
}

/**
 * \brief Permute %array dimensions
 *
 * This function rearranges the dimensions of array_nd so that they are in
 * the order specified by \e sz.
 */
template<class T, class S, class D>
typename array_nd<T, S>::create_new permute(
	const array_nd<T, S>& a, const array<size_t, D>& sz)
{
	CHECK (a.ndims() == sz.length(), eshape());

	array<size_t, stack<3> > newsz(a.ndims());

	for (size_t i = 0; i < a.ndims(); i++)
		newsz[i] = a.size_nd()[sz[i] - 1];

	return reshape(a, newsz);

}


/**
 * \brief Reshape a matrix
 *
 * Create a new array_nd whith dimensions appointed by size_array \e sz and
 * whose elements are taken columnwise from \e src
 *
 * @param src Input %array
 * @param sz Dimensions of output array
 */
template<class T, class S, class D>
typename array_nd<T, S>::create_new reshape(
	const array_nd<T, S>& src, const array<size_t, D>& sz)
{
	CHECK (src.length() == prod(sz), eshape());

	return typename array_nd<T, S>::create_new(sz, src);
}

#if 0
//! Split matrix at single point along dimension dim
template<class T, class S>
array<typename array_nd<T, S>::create_new> split(
	const array_nd<T, S>& a, size_t spoint, size_t dim)
{
	return split(a, idx(spoint), dim);
}

//! Split matrix at specific points along dimension dim
template<class T, class S, class D>
array<typename array_nd<T, S>::create_new> split(
	const array_nd<T, S>& a, const array<size_t, D>& spoint , size_t dim)
{
	CHECK (dim < a.ndims(), edims());
	CHECK (dim >= 0, edims());

	array<typename array_nd<T, S>::create_new> result(spoint.length() + 1);

	for (size_t j = 0; j < spoint.length(); j++)
		CHECK(spoint[j] <= a.size_nd()[dim], erange());

	for (size_t j = 0; j < spoint.length() + 1; j++) {
		array<index_array, tiny> indx(a.ndims());
		for (size_t i = 0; i < a.ndims(); i++) {
			if(i != dim)
				indx[i] = size_array(
					size_range(0, a.size_nd()[i] - 1));
			else
				indx[i] = size_array(size_range((j == 0 ? 0 : spoint[j - 1]),
					(j == (spoint.length()) ?
						a.size_nd()[i] - 1 : spoint[j] - 1) ));
		}
		result[j] = a(indx);
	}
	return result;
}
#endif

//! converts index vector to single-dim index
template<class T, class S, class D>
inline
size_t sub2ind(const array_nd<T, S>& a, const array<size_t, D>& b)
{
	size_t offs = b[0];
	size_t ndims = a.ndims();

	for(size_t i = 1; i < ndims; i++)
		offs += a.stride()[i] * b[i];

	CHECK (offs < a.length(), erange());

	return offs;
}

/**
 * \brief Create an array_nd of all Ones
 *
 * @param sz Contains the dimensions of the array_nd that will be created.
 */
template <class T, class D>
inline
array_nd<T> ones(const array<size_t, D>& sz)
{
	return array_nd<T>(sz, T(1));
}

/**
 * \brief Create an array_nd of all zeros
 *
 * @param sz Contains the dimensions of the array_nd that will be created.
 */
template <class T, class D>
inline
array_nd<T> zeros(const array<size_t, D>& sz)
{
	return array_nd<T>(sz, T(0));
}

/**
 * \brief Create array_nd of all inf.
 *
 * @param sz Contains the dimensions of the array_nd that will be created.
 * \warning Be Infinity is only defined for float, double, long double
 */
template <class T, class D>
inline
array_nd<T> inf(const array<size_t, D>& sz)
{
	return array_nd<T>(sz, std::numeric_limits<T>::infinity());
}


#if 0
// creates a mesh grid of the two arrays.
template <class T> inline
array<array_2d<T> > meshgrid(const index_array& a, const index_array& b)
{
	array<array_nd<T> > c(2);
	c[0] = repmat(array_nd<T>(idx(1,a.length()),a.cast()), idx(b.length() - 1,0));
	c[1] = repmat(array_nd<T>(idx(b.length(),1),b.cast()), idx(0,a.length() - 1));
	return c;
}

template <class T> inline
array_2d<T> meshgrid(const index_array& a)
{
	return meshgrid(a, a);
}
#endif

//!@}

//--------------------------------------------------------------
// Template functions for array_nd / image etc.

//! flips array along dimth dimension
template<class T, class S>
typename array_nd<T, S>::create_similar flipdim(
	const array_nd<T, S>& a, size_t dim)
{
	CHECK (dim < a.ndims(), edims());
	CHECK (dim >= 0, edims());
	array<index_array> indx(a.ndims());
	for (size_t i = 0; i < a.ndims(); i++)
		indx[i] = index_array(); // Select all.

	indx[dim] = size_range(a.size_nd()[dim] - 1, -1, 0);
	return typename array_nd<T, S>::create_similar(a(indx));
}

//--------------------------------------------------------------

//! Concatenates arrays along dimension dim
template <class T, class S>
inline
typename array_nd<T, S>::create_new cat(
	size_t dim, const array<array_nd<T, S> >& a)
{
	for (size_t i = 0; i < a.length() - 1; i++) {
		CHECK (a[i].ndims() == a[i + 1].ndims(), eshape());
		for (size_t j = 0; j < a[i].ndims(); j++)
			if (j != dim) {
				CHECK(a[i].size_nd()[j] == a[i + 1].size_nd()[j], eshape());
			}
	}
	CHECK(dim < a[0].ndims(), edims());
	CHECK(dim >= 0, edims());
	size_array sz(a[0].ndims());

	for (size_t i = 0; i < a[0].ndims(); i++)
		sz[i] = a[0].size_nd()[i];
	sz[dim] = 0;
	for (size_t j = 0; j < a.length(); j++)
		sz[dim] += a[j].size_nd()[dim];
	typename array_nd<T, S>::create_new c(sz);

	size_t offs = 0;
	for (size_t j = 0; j < a.length(); j++) {
		array<index_array> indx(a[j].ndims());

		for (size_t i = 0; i < a[j].ndims(); i++)
			indx[i] = size_range((i == dim) ? offs : 0,
					a[j].size_nd()[i] - 1 + ((i == dim) ? offs : 0));

		offs += a[j].size_nd()[dim];
		c(indx) = a[j];
	}
	return c;
}

template <class T, class S1, class S2>
inline
array_nd<T> cat(size_t dim,
	const array_nd<T, S1>& a1, const array_nd<T, S2>& a2)
{
	CHECK(dim < a1.ndims(), edims());
	CHECK(dim >= 0, edims());
	CHECK (a1.ndims() == a2.ndims(), eshape());

	for (size_t j = 0; j < a1.ndims(); j++)
		if (j != dim) {
			CHECK(a1.size_nd()[j] == a2.size_nd()[j], eshape());
		}

	size_array sz(a1.size());
	sz[dim] = a1.size_nd(dim);
	sz[dim] += a2.size_nd(dim);
	array_nd<T> c(sz);

	array<index_array> indx(a1.ndims(), index_all());
	indx[dim] = size_range(0, a1.size_nd(dim) - 1);
	c(indx).base() = a1;
	indx[dim] = size_range(a1.size_nd(dim), indx[dim].last + a2.size_nd(dim));
	c(indx) = a2;
	return c;
}


template <class T, class S1, class S2, class S3>
inline
array_nd<T> cat(size_t dim, const array_nd<T, S1>& a1,
				const array_nd<T, S2>& a2, const array_nd<T, S3>& a3)
{
	CHECK(dim < a1.ndims(), edims());
	CHECK(dim >= 0, edims());
	CHECK (a1.ndims() == a2.ndims(), eshape());
	CHECK (a2.ndims() == a3.ndims(), eshape());
	for (size_t j = 0; j < a1.ndims(); j++)
		if (j != dim) {
			CHECK(a1.size_nd()[j] == a2.size_nd()[j], eshape());
			CHECK(a2.size_nd()[j] == a3.size_nd()[j], eshape());
		}

	size_array sz(a1.size());
	sz[dim] = a1.size_nd(dim);
	sz[dim] += a2.size_nd(dim);
	sz[dim] += a3.size_nd(dim);
	array_nd<T> c(sz);

	array<index_array> indx(a1.ndims(), index_all());
	indx[dim] = size_range(0, a1.size_nd(dim) - 1);
	c(indx) = a1;
	indx[dim] = size_range(indx[dim].last + 1,
							indx[dim].last + a2.size_nd(dim));
	c(indx) = a2;
	indx[dim] = size_range(indx[dim].last + 1,
							indx[dim].last + a3.size_nd(dim));
	c(indx) = a3;
	return c;
}

template <class T, class S1, class S2, class S3, class S4>
inline
array_nd<T> cat(size_t dim, const array_nd<T, S1>& a1,
				const array_nd<T, S2>& a2, const array_nd<T, S3>& a3,
				const array_nd<T, S4>& a4)
{
	CHECK(dim < a1.ndims(), edims());
	CHECK(dim >= 0, edims());
	CHECK (a1.ndims() == a2.ndims(), eshape());
	CHECK (a2.ndims() == a3.ndims(), eshape());
	CHECK (a3.ndims() == a4.ndims(), eshape());
	for (size_t j = 0; j < a1.ndims(); j++)
		if (j != dim) {
			CHECK(a1.size_nd()[j] == a2.size_nd()[j], eshape());
			CHECK(a2.size_nd()[j] == a3.size_nd()[j], eshape());
			CHECK(a3.size_nd()[j] == a4.size_nd()[j], eshape());
		}

	size_array sz(a1.size());
	sz[dim] = a1.size_nd(dim);
	sz[dim] += a2.size_nd(dim);
	sz[dim] += a3.size_nd(dim);
	sz[dim] += a4.size_nd(dim);
	array_nd<T> c(sz);

	array<index_array> indx(a1.ndims(), index_all());
	indx[dim] = size_range(0, a1.size_nd(dim) - 1);
	c(indx) = a1;
	indx[dim] = size_range(indx[dim].last + 1,
							indx[dim].last + a2.size_nd(dim));
	c(indx) = a2;
	indx[dim] = size_range(indx[dim].last + 1,
							indx[dim].last + a3.size_nd(dim));
	c(indx) = a3;
	indx[dim] = size_range(indx[dim].last + 1,
							indx[dim].last + a4.size_nd(dim));
	c(indx) = a4;
	return c;
}

/**
 * \brief Replicate and tile an %array
 *
 * Replicates array_nd by the number of times and along the dimensions
 * specified by sz. For exmaple: \code repmat(a, [3 2]) \endcode
 * will replicate \e a 3 times along the first dimension and 2 times along the
 * second.
 */
template<class T>
array_nd<T> repmat(const array_nd<T>& a, const size_array& sz)
{
	CHECK (sz.length() <= a.ndims(), eshape());

	array_nd<T> c(a);

	for (size_t i = 0; i < sz.length(); i++) {
		array_nd<T> tmp(c);
		for (size_t j = 0; j < sz[i]; j++)
			c = cat<T>(i, c, tmp);
	}
	return c;
}

//--------------------------------------------------------------
// Auxiliary functions for array<index_array> construction
// (for sub_array indexing)

inline
array<index_array> idxn(const index_array& p1)
{
	return array_data<index_array>(p1);
}

inline
array<index_array> idxn(const index_array& p1, const index_array& p2)
{
	return array_data<index_array>(p1, p2);
}

inline
array<index_array> idxn(const index_array& p1, const index_array& p2,
		const index_array& p3)
{
	return array_data<index_array>(p1, p2, p3);
}

inline
array<index_array> idxn(const index_array& p1, const index_array& p2,
		const index_array& p3, const index_array& p4)
{
	return array_data<index_array>(p1, p2, p3, p4);
}

inline
array<index_array> idxn(const index_array& p1, const index_array& p2,
		const index_array& p3, const index_array& p4,
		const index_array& p5)
{
	return array_data<index_array>(p1, p2, p3, p4, p5);
}

inline
array<index_array> idxn(const index_array& p1, const index_array& p2,
		const index_array& p3, const index_array& p4,
		const index_array& p5, const index_array& p6)
{
	return array_data<index_array>(p1, p2, p3, p4, p5, p6);
}

} // namespace ivl

#endif // IVL_ARRAY_ND_DETAILS_ARRAY_ND_FUNCTIONS_HPP
