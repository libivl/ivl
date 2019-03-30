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

#include "gesv.hpp"

namespace ivl {
namespace lina_details {

template<class T>
void lapack_gesv<T>::operator()(
		clapack::integer n,
		clapack::integer nrhs,
		T* a,
		T* b)
{
	array<clapack::integer> ipiv(n);

	(*this)(n, nrhs, a, b, ipiv.c_ptr());
}


template<class T>
void lapack_gesv<T>::operator()(
		clapack::integer n,
		clapack::integer nrhs,
		T* a_ptr, T* b_ptr,
		clapack::integer* ipiv_ptr)
{
	/*
	if(dim_check(a, b, ipiv) == false)
		throw eshape();
	*/

	clapack::integer info;

	lapack_exec(&n, &nrhs, a_ptr, &n, ipiv_ptr, b_ptr, &n, &info);
	if(info < 0) {
		// illegal value of one or more arguments -- no computation
		// performed. The program will abord unless a non-standard
		// version of lapack's XERBLA is used.
		return;
	}
	if(info > 0) {
		// failure in the course of computation
		// This means the linear equation is not solvable
		not_solvable(b_ptr, n, nrhs);
	}
}

} /* namespace lina_details */
} /* namespace ivl */

