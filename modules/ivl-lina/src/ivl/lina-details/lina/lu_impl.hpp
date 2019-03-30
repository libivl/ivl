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

#ifndef IVL_LINA_DETAILS_LU_MEMBERS_HPP
#define IVL_LINA_DETAILS_LU_MEMBERS_HPP

namespace ivl {
namespace lina_details {

template<class T>
void lu<T>::output(array_2d<T>& l, array_2d<T>& u) const
{
	array_2d<T> r(a.size());

	lapack_interface<T>::call_lapack_getrf(r, a);

	//Now construct L, R
	//should be a MxM matrixes
	if(l.rows() != m || l.columns() != m)
		l.resize(idx(m, m));
	if(r.rows() != m || r.columns() != m)
		r.resize(idx(m, m));

	l = r;
	u = r;

	// U is upper triangular
	for(size_t i = 0; i < m; i++)
		for(size_t j = 0; j < n; j++)
			if(i > j)
				u(i, j) = 0;

	// L is lower triangular
	for(size_t i = 0; i < m; i++)
		for(size_t j = 0; j < n; j++)
			if(i < j)
				l(i, j) = 0;

	// L has (1, 1, .., 1) diagonal
	for(size_t i = 0; i < m; i++)
				l(i, i) = 1;
}

template<class T, class S>
T det(const array_2d<T, S>& x)
{
	array_2d<T> l;
	array_2d<T> u;
	array_2d<T, data::storable_link> x_l(ivl::storable_link(x));
	lu<T> lu_decomp(x_l);
	lu_decomp.output(l, u);

	T prod = 1;
	size_t len = u.rows();
	for(size_t i = 0; i < len; i++)
		prod *= u(i, i);

	return prod;
}

} /* namespace lina_details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_LU_MEMBERS_HPP
