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

#include "geqrf.hpp"

namespace ivl {
namespace lina_details {

template<class T>
void lapack_geqrf<T>::operator() (
		clapack::integer m,
		clapack::integer n,
		T* a_ptr) throw(ecomp)
{
	int min_nm = (m < n) ? m : n;

	array<T> tau(min_nm);

	(*this)(m, n, a_ptr, tau.c_ptr());
}


template<class T>
void lapack_geqrf<T>::operator() (
		clapack::integer m,
		clapack::integer n,
		T* a_ptr, T* tau_ptr) throw(ecomp)
{
	clapack::integer info;
	clapack::integer minus_one = -1;

	T optimal_lwork;

	lapack_exec(&m, &n, a_ptr, &m, tau_ptr, &optimal_lwork, &minus_one, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();

	clapack::integer lwork = lwork_cast(optimal_lwork);
	array<T> workspace(lwork);

	lapack_exec(&m, &n, a_ptr, &m, tau_ptr, workspace.c_ptr(), &lwork, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();
}

} /* namespace lina_details */
} /* namespace ivl */

