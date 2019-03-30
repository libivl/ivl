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

#ifndef IVL_ARRAY_DETAILS_ARRAY_FUNCTIONS_HPP
#define IVL_ARRAY_DETAILS_ARRAY_FUNCTIONS_HPP

namespace ivl {

//--------------------------------------------------------------
// array NON-MEMBER FUNCTIONS

/**
 * @name Array non-member functions
 * \relates array
@{*/

//----- functions returning scalar

//! Sum of elements of \e a
/* // Note: random access implementation should never be faster than
	// iterators and should not be necessary.
	// however it is kept here for a perfect solution that does the following:
	// if optimal_access_tag is random_access this is used else the other.
template<class T, class S>
typename types::promote<T>::type sum(const array<T, S>& a)
{
	typedef typename types::promote<T>::type return_type;
	return_type s = cast<return_type>(a[0]);
	size_t len = a.length();
	for (size_t i = 1; i < len; i++)
		s += cast<return_type>(a[i]);
	return s;
}
*/

//-----------------------------------------------------------------------------

template<class T, class S>
typename types::promote <typename types::create_similar <T>::type>::type
sum (const array <T, S>& a)
{
	typedef typename types::create_similar <T>::type N;
	typedef typename types::promote <N>::type return_type;
	typedef typename types::get_value <T>::type val_type;
	typedef typename array <T, S>::const_iterator cit_t;
	if(!a.length())
		return return_type();
	cit_t i = a.begin();
	return_type s = *i++;
	for(cit_t e = a.end(); i != e; i++)
// 		s += cast <val_type> (*i);  // TODO: is cast needed?
		s += *i;
	return s;
}

//-----------------------------------------------------------------------------

//!Average of all elements of \e a
template<class T, class S>
typename types::to_floating<T>::type mean(const array<T, S>& a)
{
	using namespace types;

	return cast<typename to_floating<T>::type>(ivl::sum(a)) /
		typename to_real_floating<T>::type(a.length());
}

namespace select_k_details {

template<class T, class S>
T quick_select(array<T, S>& arr, size_t k)
{
	//  This Quickselect routine is based on the algorithm described in
	//  "Numerical recipes in C", Second Edition,
	//  Cambridge University Press, 1992, Section 8.5, ISBN 0-521-43108-5
	//  This code by Nicolas Devillard - 1998. Public domain.
	size_t n = arr.size();

	size_t low, high;
	size_t median;
	size_t middle, ll, hh;

	low = 0 ; high = n - 1 ; median = k;
	for (;;) {
		if (high <= low) // One element only
			return arr[median];

		if (high == low + 1) {  // Two elements only
			if (arr[low] > arr[high])
				std::swap(arr[low], arr[high]);
			return arr[median];
		}

		// Find median of low, middle and high items; swap into position low
		middle = (low + high) / 2;
		if (arr[middle] > arr[high]) std::swap(arr[middle], arr[high]);
		if (arr[low] > arr[high])    std::swap(arr[low], arr[high]);
		if (arr[middle] > arr[low])  std::swap(arr[middle], arr[low]);

		// Swap low item (now in position middle) into position (low+1)
		std::swap(arr[middle], arr[low + 1]);

		// Nibble from each end towards middle, swapping items when stuck
		ll = low + 1;
		hh = high;
		for (;;) {
			do ll++; while (arr[low] > arr[ll]);
			do hh--; while (arr[hh]  > arr[low]);

			if (hh < ll)
			break;

			std::swap(arr[ll], arr[hh]);
		}

		// Swap middle item (in position low) back into correct position
		std::swap(arr[low], arr[hh]);

		// Re-set active partition
		if (hh <= median)
			low = ll;
		if (hh >= median)
			high = hh - 1;
	}
}

} // namespace select_k_details

//! Select the k-th element of an array \e a with comparable elements
template <class T, class S>
T select_k(const array<T, S>& a, size_t k)
{
	array<T> arr = a;
	return select_k_details::quick_select(arr, k);
}

/** \brief Median of array
 ** Returns the median value of an array \e a with comparable elements with divide operation
 ** the algorithm used is the quickest based on the algorithm described in "Numerical recipes in C"
 **/
template<class T, class S>
typename types::to_floating<T>::type median(const array<T, S>& a)
{
	using namespace select_k_details;
	typedef typename types::to_floating<T>::type return_type;

	CHECK(a.length() != 0, erange);

	array<T> arr = a;
	int k = (arr.length() - 1) / 2;

	if((arr.length() & 2) == 1)
		return cast<return_type>(quick_select(arr, k));
	else
		return (cast<return_type>(quick_select(arr, k))
			+ cast<return_type>(quick_select(arr, k + 1)))
			/ cast<return_type>(2.0);
}

/** \brief Lower median of array
 ** Returns the lower median value of an array \e a with comparable elements
 ** the algorithm used is the quickest based on the algorithm described in "Numerical recipes in C"
 **/
template <class T, class S>
T median_lower(const array<T, S>& a)
{
	array<T> arr = a;
	return select_k_details::quick_select(arr, (arr.length() - 1) / 2);
}

/** \brief Upper median of array
 ** Returns the upper median value of an array \e a with comparable elements
 ** the algorithm used is the quickest based on the algorithm described in "Numerical recipes in C"
 **/
template <class T, class S>
T median_upper(const array<T, S>& a)
{
	array<T> arr = a;
	return select_k_details::quick_select(arr, arr.length() / 2);
}

/* old method
//!Median of all elements
template<class T, class S>
typename types::to_floating<T>::type median(const array<T, S>& in)
{
	typedef typename types::to_floating<T>::type return_type;

	//TO not DO:!! think if it should be simply array. and what kind of array?
	// created type? why? not for image purpose. only remaining is sparse
	// is it needed? I think i need to make it: array<T> a = sort(in);
	typename array<T, S>::create_similar a = sort(in.derived());

	if(in.length() % 2 == 1) // if array contains an odd number of elements
		return cast<return_type>(a[a.length() / 2]);
	else
		return (
			cast<return_type>(a[a.length() / 2 - 1]) +
			cast<return_type>(a[a.length() / 2])
			) / cast<return_type>(2.0);
}
*/

#if 0
//redeclared as a corefunc

/**
 * \brief Smallest of all elements
 *
 * Note: In WIN32 targets you have to either #undef min or compile
 * with IVL_USE_MINMAX to be able to use this function
**/
template<class T, class S>
T min(const array<T, S>& a)
{
	T s = a[0];
	for (size_t i = 1; i < a.length(); i++)
		if (a[i] < s)
			s = a[i];
	return (s);
}
#endif

//TODO: wipe @ some time!

#if 0 // ivl fun
/**
 * \brief Largest of all elements
 *
 * Note: In WIN32 targets you have to either #undef max or compile
 * with IVL_USE_MINMAX to be able to use this function
 */
template<class T, class S>
T max(const array<T, S>& a)
{
	T s = a[0];
	for (size_t i = 1; i < a.length(); i++)
		if (a[i] > s)
			s = a[i];
	return (s);
}
#endif

#if 0 // this find is now implemented as an ivl func
/**
 * \brief Find an element value
 *
 * @return linear offsets of all occurences of the element in the array
 */
template <class T, class S>
size_array find(const array<T, S>& in, const T& what, size_t start = 0)
{
	size_array a(in.length());
	size_t n = 0;
	for (size_t i = start; i < in.length(); i++)
		if (in[i] == what)
			a[n++] = i;
	return n > 0 ? size_array(a, n) : size_array(0);
}
#endif

//! Count all non-zero elements
template <class T, class S>
size_t count(const array<T, S>& in)
{
	size_t count = 0;
	for (size_t i = 0; i < in.length(); i++)
		if(in[i])
			count++;
	return count;
}

//! Variance of elements \todo when array is removed, fix it
template<class T, class S>
typename types::to_real_floating<T>::type var(const array<T, S>& in)
{
	typedef typename types::to_real_floating<T>::type return_type;
	// kimon: the following line makes a redundant copy
	// it is because i cannot cast<T> from an array
	// kimon: fix for now, until array is wiped
	array<T> temporary = array<T>(in);
	array<typename types::to_floating<T>::type> a =
		cast<typename types::to_floating<T>::type>(temporary);

	array<typename types::to_floating<T>::type> b = power(a - mean(a), 2.);

	// kimon: moreover, there are lots of redundant copies, because
	// of elem-func design. also check if a = elem_func(a) is safe.
	// (it probably is)
	array<return_type> c = abs(b);

	return return_type(sum(c)) /
		return_type((a.length() == 1 ? 1 : a.length() - 1));

	// iavr: unreachable
	// return 0;
}

//! Standard deviation
template<class T, class S>
inline
typename types::to_real_floating<T>::type std(const array<T, S>& in)
{
	return std::sqrt(var(in));
}


//! Concatenates two arrays
template <class T, class S>
array<T> array_common_base<array<T, S> >::cat(const array<T>& a) const
{
	size_t len = to_array().length();
	array<T> c(len + a.length());

	for (size_t i = 0; i < len; i++)
		c[i] = to_array()[i];

	for (size_t i = 0; i < a.length(); i++)
		c[i + len] = a[i];

	return c;
}

/**
 * \brief Equality test
 *
 * Test if another object of the same type is equal with this one.
 *
 * @returns True if the two objects are equal
 */
inline bool isequal(const int& x, const int& y)
						{ return x == y; }
inline bool isequal(const short& x, const short& y)
						{ return x == y; }
inline bool isequal(const unsigned short& x, const unsigned short& y)
						{ return x == y; }
inline bool isequal(const uint8_t& x, const uint8_t& y)
						{ return x == y; }
inline bool isequal(const int8_t& x, const int8_t& y)
						{ return x == y; }
inline bool isequal(const long long& x, const long long & y)
						{ return x == y; }
#ifdef aa_MSC_VER

// Gcc

inline bool isequal(const unsigned long long& x,
	const unsigned long long & y) { return x == y; }

inline bool isequal(const unsigned int& x, const unsigned int& y)
						{ return x == y; }
inline bool isequal(const char& x, const char& y)
						{ return x == y; }
#else

#ifdef IVL64

inline bool isequal(const unsigned int& x, const unsigned int& y)
						{ return x == y; }
#else
inline bool isequal(const unsigned long long& x,
	const unsigned long long & y) { return x == y; }

#endif // IVL64

inline bool isequal(const size_t& x, const size_t& y)
						{ return x == y; }

#endif // _MSC_VER

inline bool isequal(const float& x, const float& y)
						{ return x == y; }
inline bool isequal(const double& x, const double& y)
						{ return x == y; }

template<class T>
bool isequal(const std::complex<T>& x, const std::complex<T>& y)
{
	return x == y;
}

/**
 * \brief Equality test
 *
 * Test if another object of the same type is equal with this one.
 *
 * @returns True if the two objects are equal
 */
template <class T, class S, class D>
bool isequal(const array<T, S>& a, const array<T, D>& b)
{
	size_t s = a.length();

	typedef typename array<T, S>::derived_type d_a;
	typedef typename array<T, D>::derived_type d_b;

	const typename types::highest_common<d_a, d_b>::type_a& _a(a.derived());
	const typename types::highest_common<d_a, d_b>::type_b& _b(b.derived());

	if(!isequal(_a.size(), _b.size()))
		return false;

	for (size_t i = 0; i < s; i++)
		if (a[i] != b[i])
			return false;

	return true;
}

//!compare two arrays of indices, returns 0 if equal, 1 if a>b and -1 if a<b
template <class T>
inline int compare(const ivl::array<T> &a, const ivl::array<T> &b)
{
	for(size_t i=0;i<a.size();i++)
		if(a[i]>b[i])
			return 1; //a higher than b
		else if(a[i]<b[i])
			return -1;//b higher than a

	return 0;//a and b are equal
}

//!compare two arrays of indices, returns 0 if equal, 1 if a>b and -1 if a<b
template <class T>
inline int compare(const T &a,const T &b)
{
	if(a>b)
		return 1; //a higher than b
	else if(a<b)
		return -1;//b higher than a

	return 0;//a and b are equal
}

//! returns cross product of 1-dim arrays (vectors) a and b.
//! length of a and b must be 3.
template <class T>
array<T> cross(const array<T>& a, const array<T>& b)
{
	CHECK (a.length() == 3 && b.length() == 3, eshape());

	return array_data<T>(a[1]*b[2] - a[2]*b[1], a[2]*b[0] - a[0]*b[2],
		a[0]*b[1] - a[1]*b[0]);
}

#if 0 //this find is now implemented as an ivl func
//! returns linear offsets of all occurences of element \todo Put this in a cpp file
//! \todo Put this in a cpp file
template <class D>
inline
size_array find(const array<bool, D>& ba)
{
	const size_t len = ba.length();
	size_array a(len);
	size_t n = 0;

	for (size_t i = 0; i < len; i++)
		if (ba[i])
			a[n++] = i;
	return (n > 0) ? size_array(a, n) : size_array(0);
}
#endif

//-----------------------------------------------------------------------------

//! return dot product of a and b
//! a and b must be vectors of same length.
template <typename T1, typename S1, typename T2, typename S2>
inline typename types::promote <typename types::maps::max <T1, T2>::type>::type
dot (const array <T1, S1>& a, const array <T2, S2>& b)
{
	CHECK (a.length() == b.length(), eshape());

	typedef typename types::maps::max <T1, T2>::type max_type;
	typedef typename types::promote <max_type>::type return_type;
	typedef typename array<T1, S1>::const_iterator cit_1;
	typedef typename array<T2, S2>::const_iterator cit_2;
	if(!a.length())
		return return_type();
	cit_1 i = a.begin();
	cit_2 j = b.begin();
	return_type s = *i * *j;
	i++, j++;
	for (cit_1 e = a.end(); i != e; i++, j++)
		s += *i * *j;
	return s;
}

//-----------------------------------------------------------------------------

//! returns a linearly spaced vector
template <class T>
array<T> linspace(const T& a, const T& b, size_t n = 100)
{
	CHECK (n >= 2, erange());

	return range<T>(a, (b - a) / (n - 1) , b);
}

//! returns a logarithmically spaced vector
template <class T>
array<T> logspace(double a, double b, size_t n = 50)
{
	CHECK (n >= 2, erange());

//??? std::pow(double(10.0), double(a)) ;

	array<double> c(n);
	for (size_t i = 0; i < n; i++)
		c[i] = std::pow(10, a) * std::pow(10, i * (b - a) / (n - 1) );

	return c;
}

//--------------------------------------------------------------
// EXTERNAL (TEMPLATE) FUNCTIONS

//! return array transformed by func
/*
template<class C>
C apply(C c, class C::value_type func(class C::value_type))
{
	for (size_t i = 0; i < c.length(); ++i)
		c[i] = func(c[i]);

	return c;
}
*/

//! return array left rotated
template<class T, class S>
typename array<T, S>::create_similar cshift(
	const array<T, S>& in, int count)
{
	typename array<T, S>::create_similar out(in.derived().size());
	size_t len = in.length();

	for (int i = 0; i < int(len); i++)
		out[i] = in[mod((i - count), int(len))];

	return out;
}

//! array of cumulative sum of elements
template<class T, class S>
typename array<T, S>::create_similar cumsum(const array<T, S>& in)
{
	typename array<T, S>::create_similar out(in.derived().size());
	size_t len = in.length();

	out[0] = in[0];
	for(size_t i = 1; i < len; i++)
		out[i] = in[i] + out[i-1];

	return out;
}

//! difference of consecutive elements
template<class T, class S>
typename array<typename types::to_signed <T>::type, S>::create_similar
diff(const array<T, S>& in)
{
/*	typename array<T, S>::create_similar out(in.derived().size());
	size_t len = in.length();

	out[0] = T(0);
	for(size_t i = 1; i < len; i++)
		out[i] = in[i] - in[i-1];

	return out;*/

	size_t len = in.length();
	if (len < 2) return typename array<T, S>::create_similar();
	return in[1,_,len-1] - in[0,_,len-2];
}

//! specialization of diff for index_array
//! In the case of a SIZE_RANGE array, this returns
//! a two-element array with the values 0 and step
//! instead of the full expanded form
array<int> diff(const index_array& a);

//-----------------------------------------------------------------------------

#if 0
//! remainder after division
template<class T, class S>
typename array<T, S>::create_similar rem(const array<T, S>& in,
											const T& s)
{
	typename array<T, S, K>::create_similar out(in.derived().size());
	size_t len = in.length();

	for (size_t i = 0; i < len; ++i)
		out[i] = in[i] - int(in[i] / s) * s;

	return out;
}

//! signed remainder after division
//TODO: elem func!!!
template<class T, class S>
typename array<T, S>::create_similar mod(const array<T, S>& in,
											const T& s)
{
	typename array<T, S>::create_similar out(in.derived().size());
	size_t len = in.length();
	T rem_result;	// remainder after division

	for (size_t i = 0; i < len; ++i) {
		rem_result = in[i] % s;
		out[i] = (rem_result >= 0) ? rem_result : (rem_result + s);
	}

	return out;
}

// specialization for mod with real types. different implementation
template<class S>
typename array<double, S>::create_similar mod(const array<double, S>& in,
											const double& s)
{
	typename array<double, S>::create_similar out(in.derived().size());
	size_t len = in.length();

	for (size_t i = 0; i < len; ++i)
		out[i] = in[i] - std::floor(in[i] / s) * s;

	return out;
}

template<class S>
typename array<float, S>::create_similar mod(const array<float, S>& in,
												const float& s)
{
	typename array<float, S>::create_similar out(in.derived().size());
	size_t len = in.length();

	for (size_t i = 0; i < len; ++i)
		out[i] = in[i] - std::floor(in[i]/s) * s;

	return out;
}
#endif
/**@}*/

//-----------------------------------------------------------------------------

template <typename T, typename S>
inline typename types::to_real_floating <T>::type
norm2 (const array <T, S>& a)
{
	return dot(a, a);
}

//-----------------------------------------------------------------------------

template <typename T, typename S>
inline typename types::to_real_floating <T>::type
norm (const array <T, S>& a)
{
	return sqrt(norm2(a));
}

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_ARRAY_FUNCTIONS_HPP
