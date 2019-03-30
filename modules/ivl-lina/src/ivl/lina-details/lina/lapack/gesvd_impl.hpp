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

#include "gesvd.hpp"

namespace ivl {
namespace lina_details {

template<class T>
void lapack_gesvd<T>::operator()(
					clapack::integer m,
					clapack::integer n,
					T* x_ptr,
					typename type_map<T>::type* s_ptr)
{
	clapack::integer minus_one = -1;
	clapack::integer info;
	T optimal_lwork;

	char jobu = 'N';
	clapack::integer ldu = 1;
	char jobvt = 'N';
	clapack::integer ldvt = 1;

	lapack_exec(&jobu, &jobvt, &m, &n, x_ptr, &m, s_ptr, NULL, &ldu, NULL,
			&ldvt, &optimal_lwork, &minus_one, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();

	clapack::integer lwork = lwork_cast(optimal_lwork);
	array<T> workspace = array<T>(lwork);

	lapack_exec(&jobu, &jobvt, &m, &n, x_ptr, &m, s_ptr, NULL, &ldu, NULL,
			&ldvt, workspace.c_ptr(), &lwork, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();
}

template<class T>
void lapack_gesvd<T>::operator()(
					clapack::integer m,
					clapack::integer n,
					T* x_ptr, T* u_ptr,
				    typename type_map<T>::type* s_ptr,
				    T* vt_ptr, bool econ)
{
	clapack::integer minus_one = -1;
	clapack::integer info;
	T optimal_lwork;

	char jobu = (econ ? 'S' : 'A');
	clapack::integer ldu = m;

	char jobvt;
	clapack::integer ldvt;

	if(vt_ptr == NULL) {
		jobvt = 'N';
		ldvt = 1;
	} else {
		jobvt = (econ ? 'S' : 'A');
		ldvt = n;
	}

	lapack_exec(&jobu, &jobvt, &m, &n, x_ptr, &m, s_ptr, u_ptr, &ldu,
			vt_ptr, &ldvt, &optimal_lwork, &minus_one, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();

	clapack::integer lwork = lwork_cast(optimal_lwork);
	array<T> workspace = array<T>(lwork);

	lapack_exec(&jobu, &jobvt, &m, &n, x_ptr, &m, s_ptr, u_ptr, &ldu,
			vt_ptr, &ldvt, workspace.c_ptr(), &lwork, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();
}

} /* namespace lina_details */
} /* namespace ivl */

