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

#include "getrf_impl.hpp"
#include "ivl_lapack.hpp"

namespace ivl {
namespace lina_details {

using namespace clapack;

template<>
int lapack_getrf<real>::lapack_exec(integer *m, integer *n, real *a,
		integer *lda, integer *ipiv, integer *info)
{
	return sgetrf_(m, n, a, lda, ipiv, info);
}

template<>
int lapack_getrf<doublereal>::lapack_exec(integer *m, integer *n, doublereal *a,
		integer *lda, integer *ipiv, integer *info)
{
	return dgetrf_(m, n, a, lda, ipiv, info);
}

template<>
int lapack_getrf<complex>::lapack_exec(integer *m, integer *n, complex *a,
		integer *lda, integer *ipiv, integer *info)
{
	return cgetrf_(m, n, a, lda, ipiv, info);
}

template<>
int lapack_getrf<doublecomplex>::lapack_exec(integer *m, integer *n, doublecomplex *a,
		integer *lda, integer *ipiv, integer *info)
{
	return zgetrf_(m, n, a, lda, ipiv, info);
}

//explicite instantiation
template class lapack_getrf<real>;
template class lapack_getrf<doublereal>;
template class lapack_getrf<complex>;
template class lapack_getrf<doublecomplex>;

} // namespace lina_details
} // namespace  ivl

