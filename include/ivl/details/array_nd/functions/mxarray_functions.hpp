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

#ifndef IVL_DETAILS_ARRAY_ND_MXARRAY_FUNCTIONS_HPP
#define IVL_DETAILS_ARRAY_ND_MXARRAY_FUNCTIONS_HPP

namespace ivl {

#ifndef IVL_MATLAB
/*
template<class T>
array_nd<T>::array_nd(const mxArray* mx) : array<T>()
{
	throw esystem();
}

template<class T>
mxArray* array_nd<T>::mx()
{
	throw esystem();
	return 0;
}
*/
#else

namespace mx {

// Assign from mxArray
template <class T>
inline
void assign(array_nd<T>& a, const mxArray* mx)
{
	if(mx::type_class<T>() == mxUNKNOWN_CLASS)
		throw etype();
	if(mxGetClassID(mx) != mx::type_class<T>())
		throw etype();

	size_array sz(mxGetNumberOfDimensions(mx),
		reinterpret_cast<const size_t*>(mxGetDimensions(mx)));
	a.resize(sz);

	size_t len = a.length();

	const T* ptr = mxGetData(mx);
	for(size_t i = 0; i < len; i++) {
		a[i] = ptr[i];
	}
}

template <class T>
inline
void assign(array_nd<array<T> >& a, const mxArray* mx)
{
	if(mx::type_class<T>() == mxUNKNOWN_CLASS)
		throw etype();
	if(mxGetClassID(mx) != mx::type_class<T>())
		throw etype();

	size_array sz(mxGetNumberOfDimensions(mx),
		reinterpret_cast<const size_t*>(mxGetDimensions(mx)));
	a.resize(sz);

	size_t len = a.length();

	for(size_t i = 0; i < len; i++) {
		assign(a[i], mxGetCell(mx, mwIndex(i)));
	}
}

// Convert to mxarray

template <class T>
inline
mxArray* to_mxarray(const array_nd<T>& a)
{
	/*
	 *
	 */
	const mwSize *a_sizes =
		reinterpret_cast<const mwSize*>(a.sizes().get_base_ptr());

	mxArray* mx = mxCreateNumericArray(a.ndims(), a_sizes,
						mx::type_class<T>(), mxREAL);

	size_t len = a.length();
	T* ptr = mxGetData(mx);
	for(size_t i = 0; i < len; i++) {
		ptr[i] = a[i];
	}

	return mx;
}

template <class T>
inline
mxArray* to_mxarray(const array_nd<array_nd<T> >& a)
{
	mxArray* mx = mxCreateCellArray(a.ndims(),
		reinterpret_cast<const mwSize*>(a.sizes().get_base_ptr()));

	size_t len = a.length();
	for(size_t i = 0; i < len; i++) {
		mxSetCell(mx, mwIndex(i), to_mxarray(a[i]));
	}

	return mx;
}

} // namespace mx

// construct from Matlab mxArray
template <class T>
inline
array_nd<T>::array_nd(const mxArray* mx) :
	array_nd<T, array_nd<T> >(0)
{
	*this = mx;
}

template <class T>
inline
array_nd<T>& array_nd<T>::operator=(const mxArray* mx)
{
	assign(*this, mx);
	return *this;
}

// convert to Matlab mxArray
template <class T>
inline
mxArray* array_nd<T>::mx()
{
	return to_mxarray(*this);
}

#endif

} //namespace ivl
#endif // IVL_DETAILS_ARRAY_ND_MXARRAY_FUNCTIONS_HPP
