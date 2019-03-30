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

#ifndef IVL_ARRAY_ND_DETAILS_GSLICE_ARRAY_HPP
#define IVL_ARRAY_ND_DETAILS_GSLICE_ARRAY_HPP

#if 0
namespace ivl {

//--------------------------------------------------------------
// CLASS gslice

//! defines a generalized (multidimensional) slice of a array
class gslice
{
protected:
	template<class T, class S> friend class array;
	size_t start;		//!< the starting offset
	size_array sizes;	//!< array of numbers of elements
	size_array strides;	//!< array of distances between elements

	template<class T, class S> friend class array_nd;

public:
	//! construct with all zeros
	inline gslice() : start(0) { }

	//! construct from starting offset, arrays of sizes and strides
	inline gslice(size_t off, const size_array& length_array, const size_array& stride_array)
		: start(off), sizes(length_array), strides(stride_array) { }

	//! construct from array of slices
	inline gslice(const array<slice>& as, size_array sz); // defined below

	//! return offset for an array of indexes, then increment
	inline size_t offset(size_array& index_array) const;
	// return total length of generalized slice
	inline size_t length() const;

};


//--------------------------------------------------------------
// TEMPLATE CLASS gslice_array

//! define a generalized slice of a array
template<class T> class gslice_array : public gslice
{

private:
	template<class X,class Y> friend class array_nd;

	//! construct from gslice and pointer to array contents
	gslice_array(const gslice& gsl, T *ptr) : gslice(gsl), base_ptr(ptr) { }

	//! construct from array<slice> and reference to original array_nd
	template <class S>
	gslice_array(const array<slice>& as, array_nd<T,S>& a) : gslice(as, a.sizes), base_ptr(a.base_ptr) { }

	//! pointer to array contents
	T *base_ptr;

public:
	gslice_array();	// not defined
	gslice_array(const gslice_array&);	// not defined
	gslice_array& operator=(const gslice_array&);	// not defined

	void operator=(const array<T>& a) const;	//! assign an array to a generalized slice
	void operator=(const T& s) const;			//! assign a scalar to elements of a generalized slice

	void operator+=(const T& s) const;			//! add scalar to slice array
	void operator-=(const T& s) const;			//! subtract scalar from slice array
	void operator*=(const T& s) const;			//! multiply slice array by scalar
	void operator/=(const T& s) const;			//! divide slice array by scalar
	void operator%=(const T& s) const;			//! remainder slice array by scalar
	void operator^=(const T& s) const;			//! XOR scalar into slice array
	void operator&=(const T& s) const;			//! AND scalar into slice array
	void operator|=(const T& s) const;			//! OR scalar into slice array
	void operator<<=(const T& s) const;			//! left shift slice array by scalar
	void operator>>=(const T& s) const;			//! right shift slice array by scalar

	void operator+=(const array_nd<T>& a) const;	//! add array_nd to generalized slice
	void operator-=(const array_nd<T>& a) const;	//! subtract array_nd from generalized slice
	void operator*=(const array_nd<T>& a) const;	//! multiply generalized slice by array_nd
	void operator/=(const array_nd<T>& a) const;	//! divide generalized slice by array_nd
	void operator%=(const array_nd<T>& a) const;	//! remainder generalized slice by array_nd
	void operator^=(const array_nd<T>& a) const;	//! XOR array_nd into generalized slice
	void operator&=(const array_nd<T>& a) const;	//! AND array_nd into generalized slice
	void operator|=(const array_nd<T>& a) const;	//! OR array_nd into generalized slice
	void operator<<=(const array_nd<T>& a) const;	//! left shift generalized slice by array_nd
	void operator>>=(const array_nd<T>& a) const;	//! right shift generalized slice by array_nd
};


//--------------------------------------------------------------
// array_nd/glice_array MEMBER FUNCTIONS


//! subscript nonmutable array by generalized slice
template<class T, class D>
inline
typename array_nd<T, D>::NewDerived array_nd<T, D>::operator()(const gslice& gsl) const
{
	return array_nd<T, D>::NewDerived(gslice_array<T>(gsl, this->c_ptr()));
}

//! subscript mutable array by generalized slice
template<class T, class D>
inline
gslice_array<T> array_nd<T, D>::operator()(const gslice& gsl)
{
	return gslice_array<T>(gsl, this->c_ptr());
}

//! assign generalized slice array to array_nd
template<class T, class D>
inline
typename array_nd<T, D>::Derived& array_nd<T, D>::operator=(const gslice_array<T>& ga)
{
	this->tidy(true);
	grow(ga.length());
	ndim = ga.strides.size();
	sizes = ga.sizes;
	strides = cumprod(shift(sizes, 1, size_t(1)));
	size_array index_array(ga.sizes.size(), (size_t)0); // to index_array einai to voh8htiko array (000,001,010,011 klp.)

	for (size_t i = 0; i < this->length(); ++i)
		(*this)[i] = ga.base_ptr[ga.offset(index_array)];

	return derived();
}


//--------------------------------------------------------------
// array_nd/array<slice> MEMBER FUNCTIONS

//! subscript nonmutable array by generalized slice \todo: const cast is ok? fix!
template<class T, class D>
inline
typename array_nd<T, D>::NewDerived array_nd<T, D>::operator()(const array<slice>& a) const
{
	return typename array_nd<T, D>::NewDerived(gslice_array<T>(a,
		*const_cast<array_nd<T, D>* >(this)));
}

//! subscript mutable array by generalized slice
template<class T, class D>
inline
gslice_array<T> array_nd<T, D>::operator()(const array<slice>& a)
{
	return gslice_array<T>(a, *this);
}


// --------------------------------------------------------------
// GSLICE MEMBER FUNCTIONS

gslice::gslice(const array<slice>& as, size_array sz)
{
	size_t a_len = as.length();

	size_array offsets(a_len);
	sizes   = size_array(a_len);
	strides = size_array(a_len);

	for (size_t i = 0; i < a_len; i++) {
		offsets[i] = as[i].start;
		sizes[i]   = as[i].length;
		strides[i] = as[i].stride;
	}

	size_array strd(cumprod(shift(sz,1, size_t(1))));

	size_array tmp = offsets * strd;

	start = sum(tmp);
}

//! return offset for an array of indexes, then increment
size_t gslice::offset(size_array& index_array) const
{
	size_t i, offs = start;

	for (i = 0; i < index_array.size(); ++i)
		offs += index_array[i] * strides[i];	// compute offset

	i = 0;
	while (i < index_array.size())
		if (++index_array[i] < sizes[i]) break;	// increment done, quit
		else index_array[i++] = 0;	// carry to more-significant index
	return (offs);
}

//! return total length of generalized slice
size_t gslice::length() const
{
	if (sizes.size() == 0)
		return 0;

	return prod(sizes);
}

// --------------------------------------------------------------
// GSLICE_ARRAY MEMBER FUNCTIONS & OPERATORS

//! assign an array to a generalized slice
template <class T>
void gslice_array<T>::operator=(const array<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] = a[i];
}

//! assign a scalar to elements of a generalized slice
template <class T>
void gslice_array<T>::operator=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] = s;
}

//! add scalar to gslice array
template <class T>
void gslice_array<T>::operator+=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] += s;
}

//! subtract scalar from gslice array
template <class T>
void gslice_array<T>::operator-=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] -= s;
}

//! multiply gslice array by scalar
template <class T>
void gslice_array<T>::operator*=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);
	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] *= s;
}

//! divide gslice array by scalar
template <class T>
void gslice_array<T>::operator/=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] /= s;
}

//! remainder gslice array by scalar
template <class T>
void gslice_array<T>::operator%=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] %= s;
}

//! XOR scalar into gslice array
template <class T>
void gslice_array<T>::operator^=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] ^= s;
}

//! AND scalar into gslice array
template <class T>
void gslice_array<T>::operator&=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] &= s;
}

//! OR scalar into gslice array
template <class T>
void gslice_array<T>::operator|=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] |= s;
}

//! left shift gslice array by scalar
template <class T>
void gslice_array<T>::operator<<=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);
	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] <<= s;
}

//! right shift gslice array by scalar
template <class T>
void gslice_array<T>::operator>>=(const T& s) const
{
	size_array index_array(sizes.size(), (size_t)0);
	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] >>= s;
}

//! multiply generalized slice by array_nd
template <class T>
void gslice_array<T>::operator*=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] *= a[i];
}

//! divide generalized slice by array_nd
template <class T>
void gslice_array<T>::operator/=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] /= a[i];
}

//! remainder generalized slice by array_nd
template <class T>
void gslice_array<T>::operator%=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] %= a[i];
}

//! add array_nd to generalized slice
template <class T>
void gslice_array<T>::operator+=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] += a[i];
}

//! subtract array_nd from generalized slice
template <class T>
void gslice_array<T>::operator-=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] -= a[i];
}

//! XOR array_nd into generalized slice
template <class T>
void gslice_array<T>::operator^=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] ^= a[i];
}

//! AND array_nd into generalized slice
template <class T>
void gslice_array<T>::operator&=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] &= a[i];
}

//! OR array_nd into generalized slice
template <class T>
void gslice_array<T>::operator|=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] |= a[i];
}

//! left shift generalized slice by array_nd
template <class T>
void gslice_array<T>::operator<<=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] <<= a[i];
}

//! right shift generalized slice by array_nd
template <class T>
void gslice_array<T>::operator>>=(const array_nd<T>& a) const
{
	size_array index_array(sizes.size(), (size_t)0);

	for (size_t i = 0; i < (size_t) length(); ++i )
		base_ptr[offset(index_array)] >>= a[i];
}

} // namespace ivl
#endif

#endif // IVL_ARRAY_ND_DETAILS_GSLICE_ARRAY_HPP

