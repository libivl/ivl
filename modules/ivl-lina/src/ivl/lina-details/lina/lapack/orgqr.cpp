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

#include "orgqr_impl.hpp"
#include "ivl_lapack.hpp"

namespace ivl {
namespace lina_details {

using namespace clapack;

template<>
int lapack_orgqr<real>::lapack_exec(integer *m, integer *n, integer *k,
				float *a, integer *lda, float *tau, float *work,
				integer *lwork, integer *info) throw()
{
	return sorgqr_(m, n, k, a, lda, tau, work, lwork, info);
}

template<>
int lapack_orgqr<doublereal>::lapack_exec(integer *m, integer *n, integer *k,
				doublereal *a, integer *lda, doublereal *tau,
				doublereal *work, integer *lwork, integer *info) throw()
{
	return dorgqr_(m, n, k, a, lda, tau, work, lwork, info);
}

template<>
int lapack_orgqr<complex>::lapack_exec(integer *m, integer *n, integer *k,
				complex *a, integer *lda, complex *tau, complex *work,
				integer *lwork, integer *info) throw()
{
	return cungqr_(m, n, k, a, lda, tau, work, lwork, info);
}

template<>
int lapack_orgqr<doublecomplex>::lapack_exec(integer *m, integer *n, integer *k,
				doublecomplex *a, integer *lda, doublecomplex *tau,
				doublecomplex *work, integer *lwork, integer *info) throw()
{
	return zungqr_(m, n, k, a, lda, tau, work, lwork, info);
}

//explicite instantiation
template class lapack_orgqr<real>;
template class lapack_orgqr<doublereal>;
template class lapack_orgqr<complex>;
template class lapack_orgqr<doublecomplex>;

} // namespace lina_details
} // namespace  ivl

