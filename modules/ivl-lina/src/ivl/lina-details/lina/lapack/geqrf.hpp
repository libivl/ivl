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

#ifndef IVL_LINA_DETAILS_LAPACK_GEQRF_HPP
#define IVL_LINA_DETAILS_LAPACK_GEQRF_HPP

#include "lapack_utils.hpp"

namespace ivl {
namespace lina_details {

template<class T>
class lapack_geqrf
{
	/*
	 * The routine forms the QR factorization of a general m-by-n matrix A:
	 * A = Q * R. No pivoting is performed. The routine does not form the
	 * matrix Q explicitly. Instead, Q is represented as a product of
	 * min(m, n) elementary reflectors. Routines are provided to work with
	 * Q in this representation.
	 */
private:
	int lapack_exec(clapack::integer *, clapack::integer *, T *,
			clapack::integer *, T *, T *, clapack::integer *,
			clapack::integer *) throw();
public:
	void operator()(clapack::integer m, clapack::integer n,
			T* a_ptr, T* tau_ptr) throw(ecomp);
	void operator()(clapack::integer m, clapack::integer n,
			T* a_ptr) throw(ecomp);
};

} /* namespace lina_details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_LAPACK_GEQRF_HPP

