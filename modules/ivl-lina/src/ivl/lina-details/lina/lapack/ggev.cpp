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

#include "ggev.hpp"
#include "ggev_impl.hpp"
#include "ivl_lapack.hpp"

namespace ivl {
namespace lina_details {

using namespace clapack;

template<>
int lapack_ggev<real>::lapack_exec(char *jobvl, char *jobvr, integer *n,
			const real *a, integer *lda,
			const real *b, integer *ldb,
			std::complex<real> *alpha, real* beta_ptr,
			real *vl, integer *ldvl, real *vr, integer *ldvr, real *work,
			integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return sggev_(jobvl, jobvr, n, const_cast<real*>(a), lda,
			const_cast<real*>(b), ldb,
			NULL, NULL, NULL, vl, ldvl, vr, ldvr, work, lwork, info);
	else {
		array<real> alpha_r(*n);
		array<real> alpha_i(*n);

		int ret = sggev_(jobvl, jobvr, n, const_cast<real*>(a), lda,
				const_cast<real*>(b), ldb,
				alpha_r.c_ptr(), alpha_i.c_ptr(), beta_ptr, vl,
				ldvl, vr, ldvr, work, lwork, info);

		for(int i = 0; i < *n; i++)
			alpha[i] = std::complex<real>(alpha_r[i], alpha_i[i]);

		return ret;
	}
}

template<>
int lapack_ggev<doublereal>::lapack_exec(char *jobvl, char *jobvr, integer *n,
			const doublereal *a, integer *lda,
			const doublereal *b, integer *ldb,
			std::complex<doublereal> *alpha, doublereal *beta_ptr,
			doublereal *vl, integer *ldvl, doublereal *vr, integer *ldvr,
			doublereal *work, integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return dggev_(jobvl, jobvr, n, const_cast<doublereal*>(a), lda,
				const_cast<doublereal*>(b), ldb,
				NULL, NULL, NULL, vl, ldvl, vr, ldvr, work, lwork, info);
	else {
		array<doublereal> alpha_r(*n);
		array<doublereal> alpha_i(*n);

		int ret = dggev_(jobvl, jobvr, n, const_cast<doublereal*>(a), lda,
				const_cast<doublereal*>(b), ldb,
				alpha_r.c_ptr(), alpha_i.c_ptr(), beta_ptr, vl,
				ldvl, vr, ldvr, work, lwork, info);

		for(int i = 0; i < *n; i++)
			alpha[i] = std::complex<doublereal>(alpha_r[i], alpha_i[i]);

		return ret;
	}
}

template<>
int lapack_ggev<complex>::lapack_exec(char *jobvl, char *jobvr, integer *n,
			const complex *a, integer *lda,
			const complex *b, integer *ldb,
			std::complex<real> *alpha, complex *beta_ptr,
			complex *vl, integer *ldvl, complex *vr, integer *ldvr,
			complex *work, integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return cggev_(jobvl, jobvr, n, const_cast<complex*>(a), lda,
			const_cast<complex*>(b), ldb,
			NULL, NULL, vl, ldvl, vr, ldvr, work, lwork, NULL, info);
	else {
		lapack_from_std_out<std::complex<real> > alpha_lapack(alpha, *n);

		array<real> rwork(8*(*n));

		int ret = cggev_(jobvl, jobvr, n, const_cast<complex*>(a), lda,
				const_cast<complex*>(b), ldb,
				alpha_lapack.ptr, beta_ptr, vl, ldvl, vr,
				ldvr, work, lwork, rwork.c_ptr(), info);

		return ret;
	}
}

template<>
int lapack_ggev<doublecomplex>::lapack_exec(char *jobvl, char *jobvr,
			integer *n,
			const doublecomplex *a, integer *lda,
			const doublecomplex *b, integer *ldb,
			std::complex<doublereal> *alpha, doublecomplex *beta_ptr,
			doublecomplex *vl, integer *ldvl, doublecomplex *vr, integer *ldvr,
			doublecomplex *work, integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return zggev_(jobvl, jobvr, n, const_cast<doublecomplex*>(a), lda,
			const_cast<doublecomplex*>(b), ldb,
			NULL, NULL, vl, ldvl, vr, ldvr, work, lwork, NULL, info);
	else {
		lapack_from_std_out<std::complex<doublereal> > alpha_lapack(alpha, *n);

		array<doublereal> rwork(8*(*n));

		int ret = zggev_(jobvl, jobvr, n, const_cast<doublecomplex*>(a), lda,
				const_cast<doublecomplex*>(b), ldb, alpha_lapack.ptr, beta_ptr,
				vl, ldvl, vr, ldvr, work, lwork, rwork.c_ptr(), info);

		return ret;
	}
}

//explicit instantiation
template class lapack_ggev<real>;
template class lapack_ggev<doublereal>;
template class lapack_ggev<complex>;
template class lapack_ggev<doublecomplex>;

} // namespace lina_details
} // namespace  ivl

