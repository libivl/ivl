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

#include "gesvd_impl.hpp"
#include "ivl_lapack.hpp"

namespace ivl {
namespace lina_details {

using namespace clapack;

template<>
int lapack_gesvd<real>::lapack_exec(char *jobu, char *jobvt, integer *m,
		integer *n, real *a, integer *lda, real *s, real *u,
		integer *ldu, real *vt, integer *ldvt, real *work,
		integer *lwork, integer *info)
{
	return sgesvd_(jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, work,
			lwork, info);
}

template<>
int lapack_gesvd<doublereal>::lapack_exec(char *jobu, char *jobvt, integer *m,
		integer *n, doublereal *a, integer *lda, doublereal *s,
		doublereal *u, integer *ldu, doublereal *vt, integer *ldvt,
		doublereal *work, integer *lwork, integer *info)
{
	return dgesvd_(jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, work,
			lwork, info);
}

template<>
int lapack_gesvd<complex>::lapack_exec(char *jobu, char *jobvt, integer *m,
		integer *n, complex *a, integer *lda, real *s, complex *u,
		integer *ldu, complex *vt, integer *ldvt, complex *work,
		integer *lwork, integer *info)
{
	const size_t min_mn = (size_t) (*m < *n) ? *m : *n;
	array<real> rwork(5 * min_mn);
	return cgesvd_(jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, work,
			lwork, rwork.c_ptr(), info);
}

template<>
int lapack_gesvd<doublecomplex>::lapack_exec(char *jobu, char *jobvt, integer *m,
		integer *n, doublecomplex *a, integer *lda, doublereal *s,
		doublecomplex *u, integer *ldu, doublecomplex *vt, integer *ldvt,
		doublecomplex *work, integer *lwork, integer *info)
{
	const size_t min_mn = (size_t) (*m < *n) ? *m : *n;
	array<doublereal> rwork(5 * min_mn);
	return zgesvd_(jobu, jobvt, m, n, a, lda, s, u, ldu, vt, ldvt, work,
			lwork, rwork.c_ptr(), info);
}

//explicite instantiation
template class lapack_gesvd<real>;
template class lapack_gesvd<doublereal>;
template class lapack_gesvd<complex>;
template class lapack_gesvd<doublecomplex>;

} // namespace lina_details
} // namespace  ivl

