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

#ifndef IVL_LINA_DETAILS_SVD_MEMBERS_HPP
#define IVL_LINA_DETAILS_SVD_MEMBERS_HPP

namespace ivl {
namespace lina_details {

template<class T>
void svd<T>::output(array<typename svd<T>::real_type>& s) const
{
	if(s.length() != min_mn)
		s.resize(min_mn);

	lapack_interface<T>::call_lapack_gesvd(s, x);
}

template<class T>
void svd<T>::output(array_2d<T>& u,
			array_2d<typename svd<T>::real_type>& s) const
{
	array_2d<T> dummy_v;
	output(u, s, dummy_v);
}

template<class T>
void svd<T>::output(array_2d<T>& u,
			array_2d<typename svd<T>::real_type>& s,
			array_2d<T>& v) const
{
	if(u.rows() != m || u.columns() != m)
		u.resize(idx(m, m));

	if(s.rows() != m || s.columns() != n)
		s.resize(idx(m, n), 0);

	array_2d<T> vt;
	if(compute_v) // IF NOT COMPUTE_V VT=NULL; else VT=ARRAY(N,N) POINTER!
		vt.resize(idx(n, n));

	lapack_interface<T>::call_lapack_gesvd(u, s, vt, x, econ);

	diag_s(s);

	if(compute_v)
		v = transpose(vt);
}

template<class T>
void svd<T>::diag_s(array_2d<typename svd<T>::real_type>& s) const
{
	for(size_t i = 1; i < min_mn; i++) {
		s(i,i) = s(i,0);
		s(i,0) = 0;
	}
}

} /* namespace lina details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_SVD_MEMBERS_HPP
