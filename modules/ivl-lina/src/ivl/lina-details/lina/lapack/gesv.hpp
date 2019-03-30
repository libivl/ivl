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

#ifndef LINA_DETAILS_LAPACK_GESV_HPP
#define LINA_DETAILS_LAPACK_GESV_HPP

#include "lapack_utils.hpp"

namespace ivl {
namespace lina_details {

template<class T>
class lapack_gesv
{
	/*
	 * Computes the solution to a real system of linear equations
	 * A * X = B, where A is an N-by-N matrix and X and B are N-by-NRHS
	 * matrices. The LU decomposition with partial pivoting and row
	 * interchanges is used to factor A as A = P * L * U, where P is a
	 * permutation matrix, L is unit lower triangular, and U is upper
	 * triangular.  The factored form of A is then used to solve the
	 * system of equations A * X = B.
	 */

private:
	int lapack_exec(clapack::integer *, clapack::integer *, T *,
			clapack::integer *, clapack::integer *, T *,
			clapack::integer *, clapack::integer *);
	void not_solvable(T* b, clapack::integer, clapack::integer);
public:
	void operator()(clapack::integer n, clapack::integer nrhs,
			T* a, T* b);
	void operator()(clapack::integer n, clapack::integer nrhs,
			T* a, T* b, clapack::integer* ipiv);
};


} /* namespace lina_details */
} /* namespace ivl */

#endif // LINA_DETAILS_LAPACK_GESV_HPP

