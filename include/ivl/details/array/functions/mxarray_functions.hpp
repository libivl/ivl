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

#ifndef IVL_DETAILS_ARRAY_MXARRAY_FUNCTIONS_HPP
#define IVL_DETAILS_ARRAY_MXARRAY_FUNCTIONS_HPP

namespace ivl {

#ifndef IVL_MATLAB
/*
template<class T>
array<T>::array(const mxArray* mx) : array<T>()
{
	throw esystem();
}

template<class T>
mxArray* array<T>::mx()
{
	throw esystem();
	return 0;
}
*/
#else

namespace mx {

template <class T>
inline
void assign(array<T>& a, const mxArray* mx)
{
	if(mx::type_class<T>() == mxUNKNOWN_CLASS) throw etype();
	if(mxGetClassID(mx) != mx::type_class<T>()) throw etype();
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
	const T* ptr = mxGetData(mx);
	for(size_t i = 0; i < len; i++) {
		a[i] = ptr[i];
	}
}

template <class T>
inline
void assign(array<array<T> >& a, const mxArray* mx)
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

template <class T>
inline
mxArray* to_mxarray(const array<T>& a)
{
	size_array sz(1, a.length());
	mxArray* mx = mxCreateNumericArray(1,
		reinterpret_cast<const mwSize*>(sz.get_base_ptr()),
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
mxArray* to_mxarray(const array<array<T> >& a)
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

} // namespaace mx

// construct from Matlab mxArray
template <class T>
inline
array<T>::array(const mxArray* mx)
{
	*this = mx;
}

template<class T>
inline
array<T>& array<T>::operator=(const mxArray* mx)
{
	mx::assign_array<T>(*this, mx);

	return *this;
}

// convert to Matlab mxArray
template <class T>
inline
mxArray* array<T>::mx()
{
	return mx::to_mxarray(*this);
}

#endif //#ifndef IVL_MATLAB

} //namespace ivl
#endif // IVL_DETAILS_ARRAY_MXARRAY_FUNCTIONS_HPP
