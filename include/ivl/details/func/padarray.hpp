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

//-----------------------------------------------------------------------------

#ifndef IVL_FUNC_PADARRAY
#define IVL_FUNC_PADARRAY

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

//------ padarray function stuff

//! padenum \todo document
enum padarray_direction
{
	pre,   // pad before the array elements
	post,  // pad after the
	both   // pad both sides
};

enum padarray_method {
	circular,
	replicate,
	symmetric
};

//! pad array \todo move to correct place, document, etc
template<class T, class D>
typename array_nd<T, D>::NewDerived padarray(const array_nd<T, D>& in, size_array sz,
		 T padval = 0, padarray_direction dir = both)
{
	// Constant pad
	size_t ndims = in.ndims();
	if(sz.length() < ndims) // \todo fix this. resize does not keep contents...
		sz.resize(ndims, 0);

	array<index_array> indx(ndims);
	size_array size_b(ndims);

	for(size_t k = 0; k < ndims; k++) {

		size_t m = in.size()[k];

		switch(dir) {

		case pre:
			indx[k] = size_range(sz[k], sz[k] + m - 1);
			size_b[k] = m + sz[k];
			break;

		case post:
			indx[k] = size_range(0, m - 1);
			size_b[k] = m + sz[k];
			break;

		case both:
			indx[k] = size_range(sz[k], sz[k] + m - 1);
			size_b[k] = m + 2 * sz[k];

		} // switch(dir)
	} //for

	typename array_nd<T, D>::NewDerived b(size_b, padval);
	b(indx) = in;
	return b;
}

//---- padarray helper functions

namespace array_nd_details {

template <class T, class D>
typename array_nd<T, D>::create_new circular_pad(
			const array_nd<T, D>& in, size_array sz,
			padarray_direction dir = both)
{
	size_t ndims = in.ndims();
	if(sz.length() < ndims)
		sz.resize(ndims, 0);

	array<index_array> indx(ndims);
	size_t k;

	for(k = 0; k < ndims; k++) {

		size_t m = in.size()[k];
		size_t p = sz[k];

		switch(dir) {

		case pre:
			indx[k] = ivl::cast<size_t>(ivl::mod(array<int>(
				range<int>(-int(p), int(m) - 1)), int(m)));
			break;

		case post:
			indx[k] = ivl::mod(size_array(ivl::rng(0, m + p - 1)), m);
			break;

		case both:
			indx[k] = ivl::cast<size_t>(ivl::mod(array<int>(
				range<int>(-int(p), int(m) + int(p) - 1)),
				int(m)));

		} //switch
	} //for

	return typename array_nd<T, D>::create_new(in(indx));
}

// Does symmetric pad for padarray
template <class T, class D>
typename array_nd<T, D>::create_new symmetric_pad(
	const array_nd<T, D>& in, size_array sz,
	padarray_direction dir = both)
{
	size_t ndims = in.ndims();
	if(sz.length() < ndims)
		sz.resize(ndims, 0);

	array<index_array> indx(ndims);
	size_t k;

	for(k = 0; k < ndims; k++) {

		size_t m = in.size()[k];
		size_t p = sz[k];

		switch(dir) {

		case pre:
			indx[k] = ivl::cast<size_t>(ivl::mod(array<int>(
				range<int>(-int(p), int(m) - 1)), 2 * int(m)));
			break;

		case post:
			indx[k] = ivl::mod(size_array(rng(0, m + p - 1)), 2 * m);
			break;

		case both:
			indx[k] = ivl::cast<size_t>(ivl::mod(array<int>(
				range<int>(-int(p), int(m) + int(p) - 1)),
				2 * int(m)));

		} //switch

		size_t idx_len = indx[k].length();
		index_array& ia(indx[k]);

		for(size_t j = 0; j < idx_len; j++) {
			if(ia[j] >= m)
				ia[j] = 2 * m - ia[j] - 1;
		}
	} //for

	return typename array_nd<T, D>::create_new(in(indx));
}

template <class T, class D>
typename array_nd<T, D>::create_new replicate_pad(
			const array_nd<T, D>& in, size_array sz,
		      padarray_direction dir = both)
{
	size_t ndims = in.ndims();
	if(sz.length() < ndims)
		sz.resize(ndims, 0);

	array<index_array> indx(ndims);
	size_t k;

	for(k = 0; k < ndims; k++) {

		size_t m = in.size()[k];
		size_t p = sz[k];
		index_array& ia(indx[k]);

		switch(dir) {

		case pre:
			indx[k] = size_array(p + m, size_t(0));
			for(size_t j = 0; j < m; j++)
				ia[j + p] = j;
			break;

		case post:
			indx[k] = size_array(p + m, m - 1);
			for(size_t j = 0; j < m; j++)
				ia[j] = j;
			break;

		case both:
			indx[k] = size_array(2 * p + m, m - 1);
			for(size_t j = 0; j < p; j++)
				ia[j] = 0;
			for(size_t j = 0; j < m; j++)
				ia[j + p] = j;
		} //switch
	} //for

	return typename array_nd<T, D>::create_new(in(indx));
}

}; //namespace array_nd_details

//! pad array \todo move to correct place, document, etc
template <class T, class D>
typename array_nd<T, D>::create_new padarray(
	const array_nd<T, D>& in, size_array sz,
	padarray_method mthd, padarray_direction dir = both)
{
	using namespace array_nd_details;

	switch(mthd)
	{
	case circular:
		return circular_pad(in, sz, dir);

	case replicate:
		return replicate_pad(in, sz, dir);

	case symmetric:
		return symmetric_pad(in, sz, dir);
	} //switch

	CHECK(1, etype);
	return typename array_nd<T, D>::create_new(in);// used only for compiler
}

//-----------------------------------------------------------------------------

} // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_PADARRAY
