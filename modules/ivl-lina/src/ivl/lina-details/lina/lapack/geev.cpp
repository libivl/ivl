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

#include "ivl_lapack.hpp"
#include "geev.hpp"
#include "geev_impl.hpp"

namespace ivl {
namespace lina_details {

using namespace clapack;


template<>
int lapack_geev<real>::lapack_exec(char *jobvl, char *jobvr, integer *n,
			const real *a, integer *lda, std::complex<real>* w, real *vl,
			integer *ldvl, real *vr, integer *ldvr, real *work,
			integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return sgeev_(jobvl, jobvr, n,
			const_cast<real *>(a), lda, NULL, NULL, vl, ldvl,
			vr, ldvr, work, lwork, info);
	else {
		array<real> wr(*n);
		array<real> wi(*n);

		int ret = sgeev_(jobvl, jobvr, n,
				const_cast<real *>(a), lda, wr.c_ptr(), wi.c_ptr(), vl,
				ldvl, vr, ldvr, work, lwork, info);

		for(int i = 0; i < *n; i++)
			w[i] = std::complex<real>(wr[i], wi[i]);

		return ret;
	}
}

template<>
int lapack_geev<doublereal>::lapack_exec(char *jobvl, char *jobvr, integer *n,
			const doublereal *a, integer *lda,
			std::complex<doublereal>* w, doublereal *vl,
			integer *ldvl, doublereal *vr, integer *ldvr,
			doublereal *work, integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return dgeev_(jobvl, jobvr, n,
				const_cast<doublereal *> (a), lda, NULL, NULL, vl, ldvl,
				vr, ldvr, work, lwork, info);
	else {
		array<doublereal> wr(*n);
		array<doublereal> wi(*n);

		int ret = dgeev_(jobvl, jobvr, n,
				const_cast<doublereal *> (a), lda, wr.c_ptr(), wi.c_ptr(), vl,
				ldvl, vr, ldvr, work, lwork, info);

		for(int i = 0; i < *n; i++)
			w[i] = std::complex<doublereal>(wr[i], wi[i]);

		return ret;
	}
}

template<>
int lapack_geev<complex>::lapack_exec(char *jobvl, char *jobvr, integer *n,
			const complex *a, integer *lda,
			std::complex<real>* w, complex *vl,
			integer *ldvl, complex *vr, integer *ldvr,
			complex *work, integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return cgeev_(jobvl, jobvr, n,
			const_cast<complex *>(a), lda, NULL, vl, ldvl,
			vr, ldvr, work, lwork, NULL, info);
	else {
		lapack_from_std_out<std::complex<real> > w_lapack(w, *n);

		array<real> rwork(2 * (*n));

		int ret = cgeev_(jobvl, jobvr, n,
				const_cast<complex *>(a), lda, w_lapack.ptr, vl, ldvl, vr,
				ldvr, work, lwork, rwork.c_ptr(), info);

		return ret;
	}
}

template<>
int lapack_geev<doublecomplex>::lapack_exec(char *jobvl, char *jobvr, integer *n,
			const doublecomplex *a, integer *lda,
			std::complex<doublereal>* w, doublecomplex *vl,
			integer *ldvl, doublecomplex *vr, integer *ldvr,
			doublecomplex *work, integer *lwork, integer *info) throw()
{
	if(*lwork == -1)
		return zgeev_(jobvl, jobvr, n,
			const_cast<doublecomplex *>(a), lda, NULL, vl, ldvl,
			vr, ldvr, work, lwork, NULL, info);
	else {
		lapack_from_std_out<std::complex<doublereal> > w_lapack(w, *n);

		array<doublereal> rwork(2 * (*n));

		int ret = zgeev_(jobvl, jobvr, n,
				const_cast<doublecomplex *>(a), lda, w_lapack.ptr, vl, ldvl, vr,
				ldvr, work, lwork, rwork.c_ptr(), info);

		return ret;
	}
}

//explicit instantiation
template class lapack_geev<real>;
template class lapack_geev<doublereal>;
template class lapack_geev<complex>;
template class lapack_geev<doublecomplex>;

} // namespace lina_details
} // namespace  ivl

