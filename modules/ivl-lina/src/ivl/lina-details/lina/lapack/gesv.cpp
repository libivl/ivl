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

#include "gesv_impl.hpp"
#include "ivl_lapack.hpp"

namespace ivl {
namespace lina_details {

using namespace clapack;

template<>
int lapack_gesv<real>::lapack_exec(integer *n, integer *nrhs, real *a,
		integer *lda, integer *ipiv, real *b, integer *ldb,
		integer *info)
{
	return sgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
}

template<>
void lapack_gesv<real>::not_solvable(real* b, integer n, integer nrhs)
{
	throw ecomp();
	/*
	size_t len = size_t(n * nrhs);
	for(size_t i = 0; i < len; i++) b[i] = ivl::inf<real>();
	*/
}

template<>
int lapack_gesv<doublereal>::lapack_exec(integer *n, integer *nrhs,
		doublereal *a, integer *lda, integer *ipiv, doublereal *b,
		integer *ldb, integer *info)
{
	return dgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
}

template<>
void lapack_gesv<doublereal>::not_solvable(doublereal* b,
		integer n, integer nrhs)
{
	throw ecomp();
	/*
	size_t len = size_t(n * nrhs);
	for(size_t i = 0; i < len; i++) b[i] = ivl::inf<doublereal>();
	*/
}

template<>
int lapack_gesv<complex>::lapack_exec(integer *n, integer *nrhs, complex *a,
		integer *lda, integer *ipiv, complex *b, integer *ldb,
		integer *info)
{
	return cgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
}

template<>
void lapack_gesv<complex>::not_solvable(complex* b, integer n, integer nrhs)
{
	throw ecomp();
	/* infinity, like matlab, is set to be Re(inf) = inf, Im(inf) = 0 */
	complex infty;
	infty.r = ivl::inf<real>();
	infty.i = 0;

	size_t len = size_t(n * nrhs);
	for(size_t i = 0; i < len; i++) b[i] = infty;
}

template<>
int lapack_gesv<doublecomplex>::lapack_exec(integer *n, integer *nrhs,
		doublecomplex *a, integer *lda, integer *ipiv,
		doublecomplex *b, integer *ldb, integer *info)
{
	return zgesv_(n, nrhs, a, lda, ipiv, b, ldb, info);
}

template<>
void lapack_gesv<doublecomplex>::not_solvable(doublecomplex* b,
		integer n, integer nrhs)
{
	/* infinity, like matlab, is set to be Re(inf) = inf, Im(inf) = 0 */
	doublecomplex infty;
	infty.r = ivl::inf<doublereal>();
	infty.i = 0;

	size_t len = size_t(n * nrhs);
	for(size_t i = 0; i < len; i++) b[i] = infty;
	//throw ecomp();
}

//explicite instantiation
template class lapack_gesv<real>;
template class lapack_gesv<doublereal>;
template class lapack_gesv<complex>;
template class lapack_gesv<doublecomplex>;

} // namespace lina_details
} // namespace  ivl
