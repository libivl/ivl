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

#ifndef IVL_FUNC_SET_FUNCTIONS_HPP
#define IVL_FUNC_SET_FUNCTIONS_HPP

#undef min

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------
//!intersection of array<T>, returns number of intesections
template<class T> inline
size_t intersect(const ivl::array<T>& a, const ivl::array<T>& b)
{
	ivl::size_array fa,fb;
	ivl::array<ivl::size_array> inda,indb;
	ivl::array<T> a_us = unique_count(a,fa,inda);
	ivl::array<T> b_us = unique_count(b,fb,indb);
	size_t intersections  = intersect_us(a_us,b_us,fa,fb);

return intersections;
}

//-----------------------------------------------------------------------------
//!intersection of array<T>, returns number of intesections
//!common are the common values <T> in both a and b
//!ia, ib are the indices of the common values to both a and b (how to go from intersection back to single arrays)
template<class T> inline
size_t intersect(const ivl::array<T>& a, const ivl::array<T>& b, ivl::array<T>& common,
				 ivl::array<ivl::size_array>& ia, ivl::array<ivl::size_array>& ib)
{
	ivl::size_array fa,fb;
	ivl::array<ivl::size_array> inda,indb;
	ivl::array<T> a_us = unique_count(a,fa,inda);
	ivl::array<T> b_us = unique_count(b,fb,indb);

	ivl::size_array iia,iib;
	size_t intersections  = intersect_us(a_us,b_us,fa,fb, common, iia, iib);

	ia.resize(iia.size());
	ib.resize(iib.size());

	for(size_t i=0;i<ia.size();i++) //find index to the initial non-unique arrays
	{
		ia[i] = inda[iia[i]];
		ib[i] = indb[iib[i]];
	}

return intersections;
}

//-----------------------------------------------------------------------------
//!intersection of array<T>, returns number of intesections
//!common are the common values <T> in both a and b
//!ia, ib are the indices of the common values to both a and b (how to go from intersection back to single arrays)
template<class T> inline
size_t intersect_s(const ivl::array<T>& a, const ivl::array<T>& b, ivl::array<T>& common,
				 ivl::array<ivl::size_array>& ia, ivl::array<ivl::size_array>& ib)
{
	ivl::size_array fa,fb;
	ivl::array<ivl::size_array> inda,indb;
	ivl::array<T> a_us = unique_count_s(a,fa,inda);
	ivl::array<T> b_us = unique_count_s(b,fb,indb);

	ivl::size_array iia,iib;
	size_t intersections  = intersect_us(a_us,b_us,fa,fb, common, iia, iib);

	ia.resize(iia.size());
	ib.resize(iib.size());

	for(size_t i=0;i<ia.size();i++) //find index to the initial non-unique arrays
	{
		ia[i] = inda[iia[i]];
		ib[i] = indb[iib[i]];
	}

return intersections;
}

//-----------------------------------------------------------------------------
//!intersection of array<T> which are both unique and sorted, returns number of intesections
//!calculates intersection assuming that frequencies are 1 for each element of a, b
template<class T> inline
size_t intersect_us(const ivl::array<T>& a,	 const ivl::array<T>& b)
{
	size_t i,j;
	i=j=0;

	size_t c = 0;
	while(i<a.size() && j<b.size())
	{
		int t = ivl::compare( a[i] , b[j] );
		if( t == 0 ) //add a correspondce
		{
			i++;
			j++;
			c++;
		}
		else if( t == 1) //increase the index of b, because the current element of a is higher than the current element of b
			j++;
		else
			i++; //increase the index of a
	}

return c;
}


//-----------------------------------------------------------------------------
//!intersection of array<T> which are both unique and sorted, returns number of intesections
//!calculates intersection assuming that fa, fb are the frequencies for each element of a, b
template<class T> inline
size_t intersect_us(const ivl::array<T>& a,	 const ivl::array<T>& b,
					const ivl::size_array& fa, const ivl::size_array& fb)
{
	size_t i,j;
	i=j=0;

	if( ( fa.size() != a.size() ) || ( fb.size() != b.size() ) )
	{
		std::cout << "Input array and the corresponding frequency array should have the same dimension" << std::endl;
		return 0;
	}
	size_t c = 0;
	while(i<a.size() && j<b.size())
	{
		int t = ivl::compare( a[i] , b[j] );
		if( t == 0 ) //add a correspondce
		{
			c += std::min( fa[i], fb[j] );
			i++;
			j++;
			//c++;
		}
		else if( t == 1) //increase the index of b, because the current element of a is higher than the current element of b
			j++;
		else
			i++; //increase the index of a
	}

return c;
}




//-----------------------------------------------------------------------------
//!intersection of array<T> which are both unique and sorted, returns number of intesections
//!common are the common values <T> in both a and b
//!ia, ib are the indices of the common values to both a and b (how to go from intersection back to single arrays)
//!calculates intersection assuming that frequencies are 1 for each element of a, b
template<class T> inline
size_t intersect_us(const ivl::array<T>& a, const ivl::array<T>& b,
					ivl::array<T>& common, ivl::size_array& ia, ivl::size_array &ib)
{
	//! TODO, add also frequencies to the intersection
	size_t size_a = a.size();
	size_t size_b = b.size();

	size_t i,j;
	i=j=0;

	std::vector<size_t> iav,ibv;

	while(i<size_a && j<size_b)
	{
		int t = ivl::compare( a[i] , b[j] );
		if( t == 0 ) //add a correspondce
		{
			iav.push_back(i);
			ibv.push_back(j);
			i++;
			j++;
		}
		else if( t == 1) //increase the index of b, because the current element of a is higher than the current element of b
			j++;
		else
			i++; //increase the index of a
	}

	size_t n_c = iav.size();
	common.resize(n_c);
	ia.resize(n_c);
	ib.resize(n_c);

	for(size_t k=0;k<n_c;k++)
	{
		ia[k] = iav[k];
		ib[k] = ibv[k];
		common[k] = a[ia[k]];
	}

	return ia.size();
}


//-----------------------------------------------------------------------------
//!intersection of array<T> which are both unique and sorted, returns number of intesections
//!common are the common values <T> in both a and b
//!ia, ib are the indices of the common values to both a and b (how to go from intersection back to single arrays)
//!calculates intersection assuming that fa, fb are the frequencies for each element of a, b
template<class T> inline
size_t intersect_us(const ivl::array<T>& a, const ivl::array<T>& b,
					const ivl::size_array& fa, const ivl::size_array& fb,
					ivl::array<T>& common, ivl::size_array& ia, ivl::size_array &ib)
{
	intersect_us(a,b,common,ia,ib);
	size_t in =0;
	for(size_t i =0;i<ia.size();i++)
		in+= std::min( fa[ia[i]], fb[ib[i]] );

return in;
}


//-----------------------------------------------------------------------------
//!returns the unique elements <T> of an array ( output is sorted )
//!f counts how many times each unique elements appears in a
//!index keeps the new order of elements (how to go from unique back to non-unique)
template<class T> inline
ivl::array<T> unique_count(const ivl::array<T>& a, ivl::size_array& f, ivl::array<ivl::size_array>& index)
{
	ivl::size_array ind;
	ivl::array<T> s_a(a);
	radixsort(s_a,ind); //sort the array

	ivl::array<ivl::size_array> ind_temp;
	ivl::array<T> un_a =  unique_count_core(s_a,f,ind_temp); //unique_count to the sorted array

	index.resize(ind_temp.size());  //find index from the final unique array to the initial non_unique and non_sorted array
	for(size_t i =0;i<ind_temp.size();i++)
	{
		index[i].resize(ind_temp[i].size());
		for(size_t j=0;j<ind_temp[i].size();j++)
			index[i][j] = ind[ind_temp[i][j]];
	}

return un_a;
}

//-----------------------------------------------------------------------------
//!returns the unique elements <T> of an array ( output is sorted )
//!f counts how many times each unique elements appears in a
template<class T> inline
ivl::array<T> unique_count(const ivl::array<T>& a, ivl::size_array &f)
{
	ivl::array<ivl::size_array> ind2;
	ivl::size_array ind;
	ivl::array<T> s_a(a);
	radixsort(s_a,ind); //sort the array

return unique_count_core(s_a,f,ind2, false); //unique_count to the sorted array
}

//-----------------------------------------------------------------------------
//!returns the unique elements <T> of an array ( output is sorted )
template<class T> inline
ivl::array<T> unique(const ivl::array<T>& a)
{
	ivl::size_array f;
	ivl::array<ivl::size_array> ind;
	ivl::array<T> s_a(a);
	radixsort(s_a); //sort the array

return unique_count_core(s_a,f,ind, false); //unique_count to the sorted array
}

//-----------------------------------------------------------------------------
//!returns the unique elements <T> of an already SORTED array ( output is still sorted )
//!f counts how many times each unique elements appears in a
//!index keeps the new order of elements (how to go from unique back to non-unique)
template<class T> inline
ivl::array<T> unique_count_s(const ivl::array<T>& a, ivl::size_array& f, ivl::array<ivl::size_array>& index)
{
	ivl::array<T> b = unique_count_core(a,f,index, true);
	return b;
}

//-----------------------------------------------------------------------------
//!returns the unique elements <T> of an already SORTED array ( output is still sorted )
//!f counts how many times each unique elements appears in a
template<class T> inline
ivl::array<T> unique_count_s(const ivl::array<T>& a, ivl::size_array& f)
{
	ivl::size_array index;
	ivl::array<T> b = unique_count_core(a,f,index, false);
	return b;
}

//-----------------------------------------------------------------------------
//!returns the unique elements <T> of an already SORTED array ( output is still sorted )
template<class T> inline
ivl::array<T> unique_s(const ivl::array<T>& a)
{
	ivl::size_array f, index;
	ivl::array<T> b = unique_count_core(a,f,index, false);
	return b;
}

//-----------------------------------------------------------------------------
//!returns the unique elements of an already SORTED array ( output is still sorted )
//!f counts how many times each unique elements appears in a
//!index keeps the new order of elements (how to go from unique back to non-unique)
//!option - true: calculate index, false: do not calculate index
template<class T> inline
ivl::array<T> unique_count_core(const ivl::array<T>& s_a, ivl::size_array& f, ivl::array<ivl::size_array>& index, bool option = true)
{
	ivl::array<T> unique_a(0);
	if(s_a.size()==0)
		return unique_a;
	//create a mask to mark where there is a d-dimensional indice appearing for the first time, in order to keep only unique indices
	ivl::size_array mask(s_a.size(),(size_t)0);
	mask[0]=1;
	// fill in the mask for the unique indices, mask also includes the occurences
	size_t last = 0;
	for(size_t i=1; i<s_a.size(); i++)
		if( ivl::compare( s_a[i] , s_a[i-1]) == 1) // if a new element is found
		{
			mask[i]=1;  // then mark it and add 1
			last = i; // and keep its index
		}
		else
			mask[last]++; // if its not a new value then add one at its last occurence

	ivl::size_array unique = find(mask > size_t(0)); //index of unique elements
	unique_a =s_a[unique]; //get unique elements

	f = mask[unique]; //get frequencies for unique elements

	//keep index for the new array (how to go back to the non unique array
	if(option)
	{
		index.resize(unique_a.size());
		size_t k=0;
		size_t m=0;
		for(size_t i=0;i<index.size();i++)
		{
			index[i].resize(mask[unique[m]]);
			for(size_t j=0;j<index[i].size();j++)
			{
				index[i][j] = k++;
			}
			m++;
		}
	}
	else
		index.resize(0);

	return unique_a;
}

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_SET_FUNCTIONS_HPP
