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

#ifndef IVL_LINA_DETAILS_LAPACK_GGEV_HPP
#define IVL_LINA_DETAILS_LAPACK_GGEV_HPP

#include "lapack_utils.hpp"


namespace ivl {
namespace lina_details {

template<class T>
class lapack_ggev
{
	/*
	 * Computes the eigenvalues and, optionally, the left and/or right
	 * eigenvectors for an N-by-N matrix A.
	 */

private:
	void do_ggev(clapack::integer n, const T* a, const T* b,
		std::complex<typename type_map<T>::type> *d,
		T* beta_ptr, T *vr = NULL) throw(ecomp);

	int lapack_exec(char *, char *, clapack::integer *, const T *,
			clapack::integer *, const T *, clapack::integer *,
			std::complex<typename type_map<T>::type> *,
			T *, T *,
			clapack::integer *, T *, clapack::integer *, T *,
			clapack::integer *, clapack::integer *) throw();

public:
	void operator()(clapack::integer n, const T* a, const T* b,
			std::complex<typename type_map<T>::type> *w) throw(ecomp);

	void operator()(clapack::integer n, const T* a, const T* b,
			std::complex<typename type_map<T>::type> *w,
			std::complex<typename type_map<T>::type> *v) throw(ecomp);
};

} /* namespace lina_details */
} /* namespace ivl */

#endif // LINA_DETAILS_LAPACK_GGEV_HPP

