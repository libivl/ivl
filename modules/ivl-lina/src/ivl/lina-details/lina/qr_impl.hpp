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

#ifndef IVL_LINA_DETAILS_QR_MEMBERS_HPP
#define IVL_LINA_DETAILS_QR_MEMBERS_HPP

namespace ivl {
namespace lina_details {

template<class T>
void qr<T>::output(array_2d<T>& x) const
{
	if(x.rows() != m || x.columns() != n)
		x.resize(idx(m, n));

	lapack_interface<T>::call_lapack_geqrf(x, a);
}

template<class T>
void qr<T>::output(array_2d<T>& q, array_2d<T>& r) const
{
	array<T> tau(min_nm);

	if(r.rows() != m || r.columns() != n)
		r.resize(idx(m, n));

	lapack_interface<T>::call_lapack_geqrf(r, tau, a);

	//Now construct Q
	//Q should be a MxM matrix
	if(q.rows() != m || q.columns() != m)
		q.resize(idx(m, m));

	if(n <= m) {
		//Q can hold the MxN values of R needed by lapack's xORGQR routines
		for(size_t i = 0; i < m; i++)
			for(size_t j = 0; j < n; j++)
				q[m*j + i] = r(i,j);

		lapack_interface<T>::call_lapack_orgqr(q, tau);

	} else {
		//create a new array and do a copy since
		//Q cannot hold the MxN values of R as needed by lapack's xORGQR routines
		array_2d<T> temp_q(r(all(), size_range(0, m - 1)));

		lapack_interface<T>::call_lapack_orgqr(temp_q, tau);

		//copy the Q values from temp
		for(size_t i = 0; i < m; i++)
			for(size_t j = 0; j < m; j++)
				q[m*j + i] = temp_q[m*j + i];
	}

	// R is upper triangular
	for(size_t i = 0; i < m; i++)
		for(size_t j = 0; j < n; j++)
			if(i > j)
				r(i,j) = 0;
}

} /* namespace lina_details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_QR_MEMBERS_HPP
