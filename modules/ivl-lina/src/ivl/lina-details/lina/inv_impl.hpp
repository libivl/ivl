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

#ifndef IVL_LINA_DETAILS_INV_MEMBERS_HPP
#define IVL_LINA_DETAILS_INV_MEMBERS_HPP

namespace ivl {
namespace lina_details {

template<class T>
void inv<T>::output(array_2d<T>& dst) const
{
	// Invert X by solving the linear eq. X * X^-1 = I
	// Linear Eq. is solved by clapack's xGESV
	dst.init(x.size());
	try {
		lapack_interface<T>::call_lapack_gesv(dst, x);
	} catch(ecomp& ) {
		// The system is not solvable
		dst[ivl::all()] = T(ivl::inf<T>());
	}
}

} /* namespace lina_details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_INV_MEMBERS_HPP
