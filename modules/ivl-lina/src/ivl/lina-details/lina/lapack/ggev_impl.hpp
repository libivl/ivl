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

namespace ivl {
namespace lina_details {


template<class T>
void lapack_ggev<T>::operator()(
			clapack::integer n,
			const T* a, const T* b,
			std::complex<typename type_map<T>::type> *w) throw(ecomp)
{
	array<T> beta(n);

	do_ggev(n, a, b, w, beta.c_ptr());

	for(int i = 0; i < n; i++)
		w[i] /= lapack_to_std(beta[i]);
}


template<class T>
void lapack_ggev<T>::operator()(
			clapack::integer n,
			const T* a, const T* b,
			std::complex<typename type_map<T>::type> *w,
			std::complex<typename type_map<T>::type> *v) throw(ecomp)
{
	array<T> beta(n);

	lapack_from_std_out_and_unroll<T> vr(v, w, n, n);

	do_ggev(n, a, b, w, beta.c_ptr(), vr.ptr);

	for(int i = 0; i < n; i++)
		w[i] /= lapack_to_std(beta[i]);
}


template<class T>
void lapack_ggev<T>::do_ggev(
			clapack::integer n,
			const T* a_ptr, const T* b_ptr,
			std::complex<typename type_map<T>::type> *alpha,
			T* beta_ptr, T *vr_ptr) throw(ecomp)
{
	clapack::integer minus_one = -1;
	clapack::integer info;

	char jobvl = 'N';
	clapack::integer ldvl = 1;

	char jobvr = (vr_ptr) ? 'V' : 'N';
	clapack::integer ldvr = (vr_ptr) ? n : 1;

	T optimal_lwork;

	lapack_exec(&jobvl, &jobvr, &n, a_ptr, &n, b_ptr, &n, alpha, beta_ptr, NULL, &ldvl,
			vr_ptr, &ldvr, &optimal_lwork, &minus_one, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();

	clapack::integer lwork = lwork_cast(optimal_lwork);
	array<T> workspace = array<T>(lwork);

	lapack_exec(&jobvl, &jobvr, &n, a_ptr, &n, b_ptr, &n, alpha, beta_ptr, NULL, &ldvl,
			vr_ptr, &ldvr, workspace.c_ptr(), &lwork, &info);
	if(info < 0) {
		// illegal value of one or more arguments -- no computation
		// performed. The program will abord unless a non-standard
		// version of lapack's XERBLA is used.
		return;
	}
	if(info > 0) {
		// failure in the course of computation
		// This means X is not invertable...
		throw ecomp();
	}
}

} /* namespace lina_details */
} /* namespace ivl */

