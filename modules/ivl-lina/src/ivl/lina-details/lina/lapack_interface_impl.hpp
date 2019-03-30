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

namespace ivl {
namespace lina_details {

// ----------------------------------------------------------------------------
// geev

template<class T>
void lapack_interface<T>::call_lapack_geev(
			array<complex_type, rw_link> e,
			array_2d<T, const_link> x)
{
	typedef typename lapack_type<T>::type lapack_type;

	lapack_from_std_const<T> x_lapack(x.c_ptr(), x.length());

	lapack_geev<lapack_type> compute_eig;
	compute_eig(int(x.rows()), x_lapack.ptr, e.c_ptr());
}

template<class T>
void lapack_interface<T>::call_lapack_geev(
		array_2d<complex_type, rw_link> v,
		array<complex_type, rw_link> e,
		array_2d<T, const_link> x)
		//int n, const T* x_ptr,
	//complex_type* v, complex_type* e) const;
{
	typedef typename lapack_type<T>::type lapack_type;

	lapack_from_std_const<T> x_lapack(x.c_ptr(), x.length());

	lapack_geev<lapack_type> compute_eig;
	compute_eig(int(x.rows()), x_lapack.ptr, e.c_ptr(), v.c_ptr());
}

// ----------------------------------------------------------------------------
// ggev

template<class T>
void lapack_interface<T>::call_lapack_ggev(
			array<complex_type, rw_link> e,
			array_2d<T, const_link> x,
			array_2d<T, const_link> y)
{
	lapack_from_std_const<T> x_lapack(x.c_ptr(), x.length());
	lapack_from_std_const<T> y_lapack(y.c_ptr(), y.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_ggev<lapack_type> compute_eig;
	compute_eig(int(x.rows()), x_lapack.ptr, y_lapack.ptr, e.c_ptr());
}

template<class T>
void lapack_interface<T>::call_lapack_ggev(
		array_2d<complex_type, rw_link> v,
		array<complex_type, rw_link> e,
		array_2d<T, const_link> x,
		array_2d<T, const_link> y)
{
	lapack_from_std_const<T> x_lapack(x.c_ptr(), x.length());
	lapack_from_std_const<T> y_lapack(y.c_ptr(), y.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_ggev<lapack_type> compute_eig;
	compute_eig(int(x.rows()),
		x_lapack.ptr, y_lapack.ptr, e.c_ptr(), v.c_ptr());
}

// ----------------------------------------------------------------------------
// svd

template<class T>
void lapack_interface<T>::call_lapack_gesvd(
			array<real_type, rw_link> s,
			array_2d<T, const_link> x)
{
	//I need a copy because lapack will overwrite x too
	lapack_from_std_clone<T> x_lapack(x.c_ptr(), x.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_gesvd<lapack_type> compute_svd;

	compute_svd(int(x.rows()), int(x.columns()),
		x_lapack.ptr, s.c_ptr());
}

template<class T>
void lapack_interface<T>::call_lapack_gesvd(
				array_2d<T, rw_link> u,
				array_2d<real_type, rw_link> s,
				array_2d<T, rw_link> vt,
				array_2d<T, const_link> x,
				bool econ)
{
	//I need a copy because lapack will overwrite x too
	lapack_from_std_clone<T> x_lapack(x.c_ptr(), x.length());
	//array_2d<complex> x_cmpl(x.size());
	//std_to_lapack(x, x_cmpl);

	lapack_from_std_out<T> u_lapack(u.c_ptr(), u.length());
	lapack_from_std_out<T> vt_lapack(vt.c_ptr(), vt.length());
	//array_2d<lapack_type> u_cmpl(x.rows(), x.rows());
	//array_2d<lapack_type> vt_cmpl(vt.rows(), vt.columns());

	typedef typename lapack_type<T>::type lapack_type;

	lapack_gesvd<lapack_type> compute_svd;
	compute_svd(int(x.rows()), int(x.columns()),
		x_lapack.ptr, u_lapack.ptr, s.c_ptr(),
		(vt.length() != 0) ? vt_lapack.ptr : NULL, econ);

	//lapack_to_std(u_cmpl, u);
	//lapack_to_std(vt_cmpl, vt);
}

// ----------------------------------------------------------------------------
// lu (getrf)

template<class T>
void lapack_interface<T>::call_lapack_getrf(
				array_2d<T, rw_link> x,
				array_2d<T, const_link> a)
{
	// we will use directly x as the output, in lapack form
	x = a;

	lapack_from_std_in_out<T> x_lapack(x.c_ptr(), x.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_getrf<lapack_type> lu_decomp;
	lu_decomp(int(a.rows()), int(a.columns()), x_lapack.ptr);
}

template<class T>
void lapack_interface<T>::call_lapack_getrf(
				array_2d<T, rw_link> x,
				array<int, rw_link> ipiv,
				array_2d<T, const_link> a)
{
	// we will use directly x as the output, in lapack form
	x = a;

	lapack_from_std_in_out<T> x_lapack(x.c_ptr(), x.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_getrf<lapack_type> lu_decomp;
	lu_decomp(int(a.rows()), int(a.columns()), x_lapack.ptr,
		(clapack::integer*)ipiv.c_ptr());
}

// ----------------------------------------------------------------------------
// qr (geqrf)

template<class T>
void lapack_interface<T>::call_lapack_geqrf(
				array_2d<T, rw_link> r,
				array_2d<T, const_link> a)
{
	r = a;

	lapack_from_std_in_out<T> r_lapack(r.c_ptr(), r.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_geqrf<lapack_type> qr_decomp;
	qr_decomp(int(a.rows()), int(a.columns()), r_lapack.ptr);
}

template<class T>
void lapack_interface<T>::call_lapack_geqrf(
				array_2d<T, rw_link> r,
				array<T, rw_link> tau,
				array_2d<T, const_link> a)
{
	r = a;

	lapack_from_std_in_out<T> r_lapack(r.c_ptr(), r.length());
	lapack_from_std_out<T> tau_lapack(tau.c_ptr(), tau.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_geqrf<lapack_type> qr_decomp;
	// note: (kimon) latest version before that was corrected
	// to a.rows(), a.rows() but I don't know the reason.
	qr_decomp(int(a.rows()), int(a.columns()), r_lapack.ptr, tau_lapack.ptr);
}

// ----------------------------------------------------------------------------
// orgqr

template<class T>
void lapack_interface<T>::call_lapack_orgqr(
				array_2d<T, rw_link> q,
				array<T, const_link> tau)
{
	lapack_from_std_const<T> tau_lapack(tau.c_ptr(), tau.length());
	lapack_from_std_in_out<T> q_lapack(q.c_ptr(), q.length());

	typedef typename lapack_type<T>::type lapack_type;
	lapack_orgqr<lapack_type> generate_q;
	generate_q(int(q.rows()), int(q.columns()), int(tau.length()),
		q_lapack.ptr, tau_lapack.ptr);
}

// ----------------------------------------------------------------------------
// inv

template<class T>
void lapack_interface<T>::call_lapack_gesv(
				array_2d<T, rw_link> x,
				array_2d<T, const_link> a)
{
	typedef typename lapack_type<T>::type lapack_type;
	lapack_from_std_out<T> x_lapack(x.c_ptr(), x.length());
	// below: i set x = I. (after array is converted to lapack_type).
	iter_array_nd<lapack_type>(x_lapack.ptr, x.size()) =
		eye<lapack_type>(a.rows(), defs::value<lapack_type>::zero,
			defs::value<lapack_type>::one);

	lapack_from_std_clone<T> a_lapack(a.c_ptr(), a.length());

	lapack_gesv<lapack_type> gesv;
	gesv(int(a.rows()), int(a.rows()), a_lapack.ptr, x_lapack.ptr);
}

template<class T>
void lapack_interface<T>::call_lapack_gesv(
				array_2d<T, rw_link> x,
				array_2d<T, const_link> a,
				array_2d<T, const_link> b)
{
	typedef typename lapack_type<T>::type lapack_type;
	x = b;
	lapack_from_std_out<T> x_lapack(x.c_ptr(), x.length());
	lapack_from_std_clone<T> a_lapack(a.c_ptr(), a.length());

	lapack_gesv<lapack_type> gesv;
	gesv(int(a.rows()), int(b.columns()), a_lapack.ptr, x_lapack.ptr);
}


} /* namespace lina_details */
} /* namespace ivl */
