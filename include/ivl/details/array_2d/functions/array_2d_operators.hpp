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

#ifndef IVL_ARRAY_2D_DETAILS_ARRAY_2D_OPERATORS_HPP
#define IVL_ARRAY_2D_DETAILS_ARRAY_2D_OPERATORS_HPP

#if 0
namespace ivl {
/*
template<class T1, class S1, class T2, class S2>
inline
array_nd<T1> operator |(
	const array<T1, S1>& l, const array<T1, S1>* r)
{

}

template<class T1, class S1, class T2, class S2>
inline
array_nd<T1> operator |(
	const array_nd<T1, S1>& l, const array<T1, S1>* r)
{

}

template<class T1, class S1, class T2, class S2>
inline
array_nd<T1> operator |(
	const array<T1, S1>& l, const array_nd<T1, S1>* r)
{

}
*/


template<class T1, class S1, class T2, class S2>
inline
array_nd<T1, data::catarray<
	const array_nd<T1, S1>, const array_nd<T2, S2>, 1> > operator |(
	const array_nd<T1, S1>& l, const array_nd<T1, S1>* r)
{
	array_nd<T1, data::catarray<
	const array_nd<T1, S1>, const array_nd<T2, S2>, 1> > rv;
	rv.init(l, r);
	return rv;
}
// ----------------------------------------------------------------------------
/*

template<class T1, class S1, class T2, class S2>
inline
array_nd<T1> operator -(
	const array<T1, S1>& l, const array<T1, S1>* r)
{

}

template<class T1, class S1, class T2, class S2>
inline
array_nd<T1> operator -(
	const array_nd<T1, S1>& l, const array<T1, S1>* r)
{

}

template<class T1, class S1, class T2, class S2>
inline
array_nd<T1> operator -(
	const array<T1, S1>& l, const array_nd<T1, S1>* r)
{

}
*/

template<class T1, class S1, class T2, class S2>
inline
array_nd<T1, data::catarray<
	const array_nd<T1, S1>, const array_nd<T2, S2>, 0> > operator -(
	const array_nd<T1, S1>& l, const array_nd<T1, S1>* r)
{
	array_nd<T1, data::catarray<
	const array_nd<T1, S1>, const array_nd<T2, S2>, 0> > rv;
	rv.init(l, r);
	return rv;
}
/*
template<class T1, class S1, class T2, class S2>
inline
array_nd<T1> operator -(
	const array_nd<T1, S1>& l, const array_nd<T1, S1>* r)
{

}*/


} /* namespace ivl */

// TODO: please remove this file. or not.
#if 0

namespace ivl {

//--------------------------------------------------------------
// array_nd SUBSCRIPTION OPERATORS

template<class T, class D, class P>
inline
typename array_nd<T, D, P>::derived_type& array_nd<T, D, P>::operator=(const T& s)
{
	this->assign(s);
/*
	array<T, D, P>::operator=(s);
	ndim = 1;
	sizes = size_array(1, 1);
	strides = size_array(1,1);
*/
	return derived();
}

template<class T, class D, class P>
inline
array_nd<T, D, P>& array_nd<T, D, P>::operator=(const array_nd<T, D, P>& a)
{
	this->assign(a);
/*
	base_class::operator=(a);

	ndim = a.ndims();
	sizes = a.size_nd();
	strides = a.stride();
*/
	return *this;
}

template<class T, class D, class P>
template<class S, class K>
inline
typename array_nd<T, D, P>::derived_type& array_nd<T, D, P>::operator=(const array_nd<T, S, K>& a)
{
	this->assign(a);
/*
	array<T, D>::operator=(a);

	ndim = a.ndims();
	sizes = a.size_nd();
	strides = a.stride();
*/
	return derived();
}

} // namespace ivl

#endif

#endif

#endif // IVL_ARRAY_2D_DETAILS_ARRAY_2D_OPERATORS_HPP
