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

#ifndef IVL_LINA_DETAILS_EIG_HPP
#define IVL_LINA_DETAILS_EIG_HPP

namespace ivl {
namespace lina_details {


template<class T>
class eig :
	public rvalue_output_converter<conversions::normal, eig<T> >
{
private:
	typedef typename types::to_complex<T>::type complex_type;

	array_2d<T, data::storable_link> x;
	array_2d<T, data::storable_link> y; // not null: eig of two matrices
	const size_t n;

public:
	template<class S>
	eig(const array_2d<T, S>& src);

	template<class S, class D>
	eig(const array_2d<T, S>& src1, const array_2d<T, D>& src2);

	// e = eig(...
	void output(array<complex_type>& e) const;

	// [v,d] = eig(...
	void output(array_2d<complex_type>& v,
		array_2d<complex_type>& d) const;
};

/* implementation of class eig */

template<class T>
template<class S>
eig<T>::eig(const array_2d<T, S>& src)
	: x(ivl::storable_link(src)), n(src.columns())
{
	if(x.columns() == 0)
		throw eshape();

	if(!x.is_square())
		throw eshape();
	y.set_null();
}

template<class T>
template<class S, class D>
eig<T>::eig(
	const array_2d<T, S>& src1,
	const array_2d<T, D>& src2
	)
	: x(ivl::storable_link(src1)),
		y(ivl::storable_link(src2)), n(src1.columns())
{
	if(x.columns() == 0)
		throw eshape();

	if(!x.is_square())
		throw eshape();

	if(y.columns() != x.columns())
		throw eshape();

	if(!y.is_square())
		throw eshape();
}


template<class T>
void eig<T>::output(array<typename types::to_complex<T>::type>& e) const
{
	typedef array<complex_type> out_array;

	e.init(n);

	// convert the arrays to pointers, or use the existing pointers
	if(y.is_null()) {
		lapack_interface<T>::call_lapack_geev(e, x);

	} else {
		// eig of two matrices
		lapack_interface<T>::call_lapack_ggev(e, x, y);
	}
}

template<class T>
void eig<T>::output(
	array_2d<typename types::to_complex<T>::type>& v,
		array_2d<typename types::to_complex<T>::type>& d) const
{
	array<complex_type> e(n);

	v.init(idx(n, n));

	if(y.is_null()) {
		lapack_interface<T>::call_lapack_geev(v, e, x);

	} else {
		// eig of two matrices
		lapack_interface<T>::call_lapack_ggev(v, e, x, y);
	}

	// now create d out of e
	d.init(idx(n, n));

	typename array<complex_type>::iterator it = d.begin();
	complex_type* e_ptr = e.c_ptr();
	size_t next = 0;
	size_t len = n * n;

	// quickly create diagonal matrix with elements of e
	for(size_t i = 0; i < len; i++) {
		if(i == next) {
			next += n + 1;
			*it++ = *e_ptr++;
		}
		else *it++ = complex_type(0, 0);
	}
}

} /* namespace lina_details */
/*
static struct eig_impl : public ivl_func<eig_impl>
{
	template<class O, class I1>
	void operate(O& o, sep, const I1& i)
	{
		_(o) = lina_details::eig<T>(i);
	}
	template<class O1, class O2, class I1>
	void operate(O1& o1, O2& o2, sep, const I1& i)
	{
		_(o1, o2) = lina_details::eig<T>(i);
	}
	template<class O, class I1, class I2>
	void operate(O& o, sep, const I1& i1, const I2& i2)
	{
		_(o) = lina_details::eig<T>(i1, i2);
	}
	template<class O1, class O2, class I1, class I2>
	void operate(O1& o1, O2& o2, sep, const I1& i1, const I2& i2)
	{
		_(o1, o2) = lina_details::eig<T>(i1, i2);
	}
} eig;*/

// ivl user functions
static __attribute__((unused)) struct eig_impl
{
	struct plus
	{
		template<class T, class S>
		lina_details::eig<T> operator()(const array_2d<T, S>& x)
		{
			return lina_details::eig<T>(x);
		}

		template<class T, class S, class D>
		lina_details::eig<T> operator()(
			const array_2d<T, S>& a, const array_2d<T, D>& b)
		{
			return lina_details::eig<T>(a, b);
		}
	};
	plus operator++(int) { return plus(); }
} eig;

} /* namespace ivl */





#if 0
template<class T,
	class S, class K,
	class D = ivl::data::empty, class P = ivl::types::term
>
class eig
//this should be rvalue base. should probly be same for oper type too,
//when simply oper type has predefined output that call operate on mid?
//yes, probably. however that type rvalue is diferent, has some templates
//in and so has a tuple. same idea but little different name of class.

//then, since storage is manual, conversion should also be manual
//and out types should in our case be linked in the definitions here, x, and y.
//however conversion for output has an attr that is implicit in lvalue oper=
// and so conversion type for output needs to be customized through template.
// in a to-normal output conversion we will be using attr implicitly in op=.

// in the same manner attr should be causing conversions as usual, however,
// should be cleverly using swap. So, similarly to having a function with
// return<array>, return<array>, sep, array<link>, array<link>,
// we have a function with
// array&, array&, array<c_link>, array<c_link> and the ref will either be
// direct or converted to a temporary via attr which is then going to be
// copied via swap, like in the return<array> case.

// all this is necessary since rw-link wouldnt have resize. rw-link for this
// reason, meaning no resize, and now, the swap substitute, seems to
// be probably unpopular as argument and so the name link could probably be
// given to the const link, and even if no probably it wont be kept for rw-link
// but instead will take something else. e.g. rw_link. or wo_link, w_link.

// on constlink and link, also provide a method 'unlinked()'.
// This should check begin() against it() which should be NULL and eventually
// can take use for unused parameters.

{
	//Eigenvalues and eigenvectors
private:
	typedef std::complex<typename type_map<T>::type> complex_type;

	const size_t n;
	const array_2d<T, S, K> &x;
	const array_2d<T, D, P> *y; // eig of two matrices

public:
	eig(const array_2d<T, S, K>& src);

	eig(const array_2d<T, S, K>& src1, const array_2d<T, D, P>& src2);

	// e = eig(...
	template<class L, class F>
	void output(array<complex_type, L, F>& e) const;

	// [v,d] = eig(...
	template<class L, class F, class M, class N>
	void output(array_2d<complex_type, L, F>& v,
		array_2d<complex_type, M, N>& d) const;
};
#endif

#endif // IVL_LINA_DETAILS_EIG_HPP
