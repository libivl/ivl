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

#ifndef IVL_DETAILS_ARRAY_2D_MXARRAY_FUNCTIONS_HPP
#define IVL_DETAILS_ARRAY_2D_MXARRAY_FUNCTIONS_HPP

namespace ivl {

#ifndef IVL_MATLAB
/*
template<class T>
array_2d<T>::array_2d(const mxArray* mx) : array<T>()
{
	throw esystem();
}

template<class T>
mxArray* array_2d<T>::mx()
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
void assign(array_2d<T>& a, const mxArray* mx)
{
	if(mx::type_class<T>() == mxUNKNOWN_CLASS) throw etype();
	if(mxGetClassID(mx) != mx::type_class<T>()) throw etype();
	if(mxGetNumberOfDimensions(mx) != 2) throw eshape();

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
void assign(array_2d<array_2d<T> >& a, const mxArray* mx)
{
	if(mx::type_class<T>() == mxUNKNOWN_CLASS) throw etype();
	if(mxGetClassID(mx) != mx::type_class<T>()) throw etype();
	if(mxGetNumberOfDimensions(mx) != 2) throw eshape();

	size_array sz(mxGetNumberOfDimensions(mx),
		reinterpret_cast<const size_t*>(mxGetDimensions(mx)));
	a.resize(sz);

	size_t len = a.length();

	for(size_t i = 0; i < len; i++) {
		assign(a[i], mxGetCell(mx, mwIndex(i)));
	}
}

template <class T>
inline
void assign(array_2d<array<T> >& a, const mxArray* mx)
{
	if(mx::type_class<T>() == mxUNKNOWN_CLASS) throw etype();
	if(mxGetClassID(mx) != mx::type_class<T>()) throw etype();
	if(mxGetNumberOfDimensions(mx) != 2) throw eshape();

	size_array sz(mxGetNumberOfDimensions(mx),
		reinterpret_cast<const size_t*>(mxGetDimensions(mx)));
	a.resize(sz);

	size_t len = a.length();

	for(size_t i = 0; i < len; i++) {
		assign(a[i], mxGetCell(mx, mwIndex(i)));
	}
}

template <class T>
inline
void assign(array<array_2d<T> >& a, const mxArray* mx)
{
	if(mxGetClassID(mx) != mxCELL_CLASS) throw etype();
	size_array sz(mxGetNumberOfDimensions(mx),
		reinterpret_cast<const size_t*>(mxGetDimensions(mx)));

	size_t len;
	if(sz.length() == 2) {
		if(sz[0] == 1) len = sz[1];
		else if(sz[1] == 1) len = sz[0];
		else throw eshape();
	} else if(sz.length() == 1) len = sz[0];
	else throw eshape();

	a.resize(len);
	for(size_t i = 0; i < len; i++) {
		assign(a[i], mxGetCell(mx, mwIndex(i)));
	}
}

// Convert to mxarray

template <class T>
inline
mxArray* to_mxarray(const array_2d<T>& a)
{
	mxArray* mx = mxCreateNumericMatrix(a.rows(), a.columns(),
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
mxArray* to_mxarray(const array_2d<array_2d<T> >& a)
{
	mxArray* mx = mxCreateCellMatrix(a.rows(), a.columns(),
		mx::type_class<T>(), mxREAL);

	size_t len = a.length();
	for(size_t i = 0; i < len; i++) {
		mxSetCell(mx, mwIndex(i), to_mxarray(a[i]));
	}

	return mx;
}

template <class T>
inline
mxArray* to_mxarray(const array_2d<array<T> >& a)
{
	mxArray* mx = mxCreateCellMatrix(a.rows(), a.columns(),
		mx::type_class<T>(), mxREAL);

	size_t len = a.length();
	for(size_t i = 0; i < len; i++) {
		mxSetCell(mx, mwIndex(i), to_mxarray(a[i]));
	}

	return mx;
}

template <class T>
inline
mxArray* to_mxarray(const array<array_2d<T> >& a)
{
	size_array sz(1, a.length());
	mxArray* mx = mxCreateCellArray(1,
		reinterpret_cast<const mwSize*>(sz.get_base_ptr()));
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
array_2d<T>::array_2d(const mxArray* mx) :
	array_2d<T, array_2d<T> >(0, 0)
{
	*this = mx;
}

template <class T>
inline
array_2d<T>& array_2d<T>::operator=(const mxArray* mx)
{
	assign(*this, mx);
	return *this;
}

// convert to Matlab mxArray
template <class T>
inline
mxArray* array_2d<T>::mx()
{
	return to_mxarray(*this);
}

#endif //#ifndef IVL_MATLAB

} //namespace ivl
#endif // IVL_DETAILS_ARRAY_2D_MXARRAY_FUNCTIONS_HPP
