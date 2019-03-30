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

#include "getrf.hpp"

namespace ivl {
namespace lina_details {

template<class T>
void lapack_getrf<T>::operator()(
		clapack::integer m,
		clapack::integer n,
		T* a_ptr) throw(ecomp)
{
	array<clapack::integer> ipiv(m);

	(*this)(m, n, a_ptr, ipiv.c_ptr());
}


template<class T>
void lapack_getrf<T>::operator()(
		clapack::integer m,
		clapack::integer n,
		T* a_ptr, clapack::integer* ipiv_ptr) throw(ecomp)
{
	clapack::integer info;

	lapack_exec(&m, &n, a_ptr, &m, ipiv_ptr, &info);
	if(info < 0)
		return;
	if(info > 0)
		throw ecomp();
}

} /* namespace lina_details */
} /* namespace ivl */

