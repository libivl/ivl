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

#ifndef IVL_LINA_DETAILS_LAPACK_INTERFACE_HPP
#define IVL_LINA_DETAILS_LAPACK_INTERFACE_HPP

namespace ivl {
namespace lina_details {

/*
A class that calls lapack's functions using a lapack independant interface.
has four seperate specializations using std::complex<>, so it has types
compatible with the floating point C++ ivl types.
It is responsible for the communication between the methods in the lapack/
directory which are aware of the lapack include files and the lapack types,
and the lina/ implementations which do not include lapack types.
the type matching between C float/double and lapack real/doublereal
is done at linkage to lapack_interface so that types are matched correctly
by size, independant to the lapack implementation.
The conversion between std::complex<real>/std::complex<doublereal> and
lapack complex/doublecomplex is done in the compiled code lapack_interface.cpp
and the corresponding lapack_exec function is called.
is some cases few complex parameters remain std::complex at lapack_exec
to avoid the possible run-time complex conversion.
*/

template<class T>
class lapack_interface
{
private:
	typedef typename types::to_complex<T>::type complex_type;
	typedef typename types::to_real<T>::type real_type;

public:
	static void call_lapack_geev(array<complex_type, rw_link> e,
				array_2d<T, const_link> x);

	static void call_lapack_geev(array_2d<complex_type, rw_link> v,
		array<complex_type, rw_link> e,
		array_2d<T, const_link> x);

	static void call_lapack_ggev(array<complex_type, rw_link> e,
			array_2d<T, const_link> x,
			array_2d<T, const_link> y);

	static void call_lapack_ggev(array_2d<complex_type, rw_link> v,
		array<complex_type, rw_link> e,
		array_2d<T, const_link> x,
		array_2d<T, const_link> y);

	//lu
	static void call_lapack_getrf(array_2d<T, rw_link> dst,
			array_2d<T, const_link> x);

	static void call_lapack_getrf(array_2d<T, rw_link> r,
			array<int, rw_link> ipiv,
			array_2d<T, const_link> x);

	//qr
	static void call_lapack_geqrf(array_2d<T, rw_link> x,
			array_2d<T, const_link> a);

	static void call_lapack_geqrf(
			array_2d<T, rw_link> r,
			array<T, rw_link> tau,
			array_2d<T, const_link> a);

	static void call_lapack_orgqr(
			array_2d<T, rw_link> q,
			array<T, const_link> tau);

	//svd
	static void call_lapack_gesvd(
			array<real_type, rw_link> s,
			array_2d<T, const_link> x);

	static void call_lapack_gesvd(
			array_2d<T, rw_link> u,
			array_2d<real_type, rw_link> s,
			array_2d<T, rw_link> v,
			array_2d<T, const_link> x, bool econ);

	//inv
	static void call_lapack_gesv(
			array_2d<T, rw_link> x,
			array_2d<T, const_link> a);

	static void call_lapack_gesv(
			array_2d<T, rw_link> x,
			array_2d<T, const_link> a,
			array_2d<T, const_link> b);

};


} /* namespace lina_details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_LAPACK_INTERFACE_HPP
