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

#ifndef IVL_ARRAY_DETAILS_RADIXSORT_HPP
#define IVL_ARRAY_DETAILS_RADIXSORT_HPP

//-------------------------------------------------------------------------------------
namespace ivl {

namespace array_details {

//!sort the source array based on b-th byte and store the result in dest array
//!and keeping index (how to go from the sorted array to the un-sorted)
template<class T> inline
void radix (size_t b, ivl::array<T> &source, ivl::array<T> &dest, ivl::size_array &ind)
{
	ivl::size_array t_ind(ind);
	size_t N = source.size();
	T count[256];
	T index[256];
	for(size_t i=0;i<256;i++) count[i]=0;

	for ( size_t i=0; i<(size_t)N; i++ )   //count occurences of  each possible element
		count[((source[i])>>(b*8))&0xff]++;

	index[0]=0;
	for ( size_t i=1; i<256; i++ )  //build a index-list for each possible element
		index[i]=index[i-1]+count[i-1];
	for ( size_t i=0; i<(size_t)N; i++ )  //place elements in another array with the sorted order
	{
		size_t pos = (size_t)( ((source[i])>>(b*8))&0xff);
		dest[(size_t)index[pos]] = (T)source[i];
		ind[(size_t)index[pos]] = t_ind[i];
		index[pos]++;
	}
}

}; // namespace array_details

//-------------------------------------------------------------------------------------
//!sort an array of positive numbers using the radix sort algorithm
//!and keeping index (how to go from the sorted array to the un-sorted)
template<class T> inline
void radixsort(ivl::array<T> &source, ivl::size_array &ind)
{
	using namespace array_details;

	ind = ivl::size_range(0,source.size()-1);
	size_t nb = sizeof(source[0]) / sizeof(char);  //number of bytes used
	ivl::array<T> temp(source.size()); //temporary array

	for(size_t i=0; i<nb/2; i++) // sort based on each byte starting from the LSD
	{
		radix (i*2, source, temp, ind);
		radix (i*2+1, temp, source, ind);
	}
}

namespace array_details {

//-------------------------------------------------------------------------------------
//!sort the source array based on b-th byte and store the result in dest array
template<class T> inline
void radix (size_t b, ivl::array<T> &source, ivl::array<T> &dest)
{
	size_t N = source.size();
	T count[256];
	T index[256];
	for (size_t i=0; i<256; i++) count[i] = 0;

	for ( size_t i=0; i<(size_t)N; i++ )   //count occurences of  each possible element
		count[((source[i])>>(b*8))&0xff]++;

	index[0]=0;
	for ( size_t i=1; i<256; i++ )  //build a index-list for each possible element
		index[i]=index[i-1]+count[i-1];
	for ( size_t i=0; i<(size_t)N; i++ )  //place elements in another array with the sorted order
	{
		size_t pos = ((source[i])>>(b*8))&0xff;
		dest[index[pos]++] = source[i];
	}
}

}; // namespace array_details

//-------------------------------------------------------------------------------------
//!sort an array of positive numbers using the radix sort algorithm
template<class T> inline
void radixsort(ivl::array<T> &source)
{
	using namespace array_details;

	size_t nb = sizeof(source[0]) / sizeof(char);  //number of bytes used
	ivl::array<T> temp(source.size()); //temporary array

	for(size_t i=0; i<nb/2; i++) // sort based on each byte starting from the LSD
	{
		radix (i*2, source, temp);
		radix (i*2+1, temp, source);
	}
}

namespace array_details {

//-------------------------------------------------------------------------------------
//!sort the source array based on b-th byte and store the result in dest array
template<class T> inline
void radix(size_t b, ivl::array<ivl::array<T> > &source, ivl::array<ivl::array<T> > &dest, size_t n)
{
	size_t N = source.size();
	T count[256];
	T index[256];
	for(size_t i=0;i<256;i++) count[i]=0;

	for ( size_t i=0; i<(size_t)N; i++ )   //count occurences of  each possible element
		count[((source[i][n])>>(b*8))&0xff]++;

	index[0]=0;
	for ( size_t i=1; i<256; i++ )  //build a index-list for each possible element
		index[i]=index[i-1]+count[i-1];
	for ( size_t i=0; i<(size_t)N; i++ )  //place elements in another array with the sorted order
	{
		size_t pos = ((source[i][n])>>(b*8))&0xff;
		dest[index[pos]++] = source[i];
	}
}

}; //namespace array_details

//-------------------------------------------------------------------------------------
//!sort an array of positive numbers using the radix sort algorithm
template<class T> inline
void radixsort(ivl::array<ivl::array<T> > &source)
{
	using namespace array_details;

	size_t nb = sizeof(source[0][0]) / sizeof(char);  //number of bytes used
	ivl::array<ivl::array<T> > temp(source.size()); //temporary array

	size_t s = source[0].size();
	for(int j=(int)s-1; j>-1; j--)
		for(size_t i=0; i<nb/2; i++) // sort based on each byte starting from the LSD
		{
			radix (i*2, source, temp,(size_t)j);
			radix (i*2+1, temp, source,(size_t)j);
		}
}

namespace array_details {

//-------------------------------------------------------------------------------------
//!sort the source array based on b-th byte and store the result in dest array
template<class T> inline
void radix(size_t b, ivl::array<ivl::array<T> > &source, ivl::array<ivl::array<T> > &dest, size_t n,  ivl::size_array& ind)
{
	ivl::size_array t_ind(ind);
	size_t N = source.size();
	T count[256];
	T index[256];
	for(size_t i=0;i<256;i++) count[i]=0;

	for ( size_t i=0; i<(size_t)N; i++ )   //count occurences of  each possible element
		count[((source[i][n])>>(b*8))&0xff]++;

	index[0]=0;
	for ( size_t i=1; i<256; i++ )  //build a index-list for each possible element
		index[i]=index[i-1]+count[i-1];
	for ( size_t i=0; i<(size_t)N; i++ )  //place elements in another array with the sorted order
	{
		size_t pos = ((source[i][n])>>(b*8))&0xff;
		dest[index[pos]] = source[i];
		ind[index[pos]] = t_ind[i];
		index[pos]++;
	}
}

}; // namespace array_details

//-------------------------------------------------------------------------------------
//!sort an array of positive numbers using the radix sort algorithm
template<class T> inline
void radixsort(ivl::array<ivl::array<T> > &source, ivl::size_array& ind)
{
	using namespace array_details;

	ind = ivl::size_range(0,source.size()-1);
	size_t nb = sizeof(source[0][0]) / sizeof(char);  //number of bytes used
	ivl::array<ivl::array<T> > temp(source.size()); //temporary array

	size_t s = source[0].size();
	for(int j=(int)s-1; j>-1; j--)
		for(size_t i=0; i<nb/2; i++) // sort based on each byte starting from the LSD
		{
			radix (i*2, source, temp,(size_t)j, ind);
			radix (i*2+1, temp, source,(size_t)j, ind);
		}
}

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_RADIXSORT_HPP
