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

#ifndef IVL_LINA_DETAILS_LAPACK_ORGQR_HPP
#define IVL_LINA_DETAILS_LAPACK_ORGQR_HPP

#include "lapack_utils.hpp"

namespace ivl {
namespace lina_details {

template<class T>
class lapack_orgqr
{
	/*
	 * Generates an M-by-N matrix Q with orthonormal columns, which is
	 * defined as the first N columns of a product of K elementary
	 * reflectors of order M.
	 */
private:
	int lapack_exec(clapack::integer *, clapack::integer *,
		clapack::integer *, T *, clapack::integer *, T *, T *,
		clapack::integer *, clapack::integer *) throw();
public:
	void operator()(clapack::integer, clapack::integer, clapack::integer,
		T* a_ptr, const T* tau_ptr) throw(ecomp);
};

} /* namespace lina_details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_LAPACK_ORGQR_HPP

