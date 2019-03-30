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

#include "lapack_utils.hpp"


namespace ivl {
namespace lina_details {

using namespace clapack;

namespace defs {
const clapack::complex cmpl_1 = {1, 0};
const clapack::complex cmpl_0 = {0, 0};
const clapack::doublecomplex dcmpl_1 = {1, 0};
const clapack::doublecomplex dcmpl_0 = {0, 0};

const clapack::complex value<clapack::complex>::zero = cmpl_0;
const clapack::complex value<clapack::complex>::one = cmpl_1;
const clapack::doublecomplex value<clapack::doublecomplex>::zero = dcmpl_0;
const clapack::doublecomplex value<clapack::doublecomplex>::one = dcmpl_1;
const clapack::real value<clapack::real>::zero = 0.0;
const clapack::real value<clapack::real>::one = 1.0;
const clapack::doublereal value<clapack::doublereal>::zero = 0.0;
const clapack::doublereal value<clapack::doublereal>::one = 1.0;

} //namespace clapack_defs

/*
template<class FROM1, class TO1, class FROM2, class TO2>
inline
void lapack_to_std_tmpl(const array_base<FROM1,FROM2> &src, array_base<std::complex<TO1>, TO2> &dst)
{
	const size_t n = src.derived().length();

	// we do not check the dimensions, since we cannot resize correctly if
	// the input is not an array but an array_2d, array_nd, etc

	for(int i = 0; i < n; i++)
		dst.derived()[i] = std::complex<TO1>(src.derived()[i].r, src.derived()[i].i);
}

template<class FROM1, class TO1, class FROM2, class TO2>
inline
void std_to_lapack_tmpl(const array_base<std::complex<FROM1>, FROM2> &src, array_base<TO1, TO2> &dst)
{
	const size_t n = src.derived().length();

	for(size_t i = 0; i < n; i++) {
		dst.derived()[i].r = src.derived()[i].real();
		dst.derived()[i].i = src.derived()[i].imag();
	}
}


void lapack_to_std(const array_2d<complex> &src, array_2d<std::complex<real> > &dst)
{
	lapack_to_std_tmpl(src, dst);
}

void lapack_to_std(const array_2d<doublecomplex> &src, array_2d<std::complex<doublereal> > &dst)
{
	lapack_to_std_tmpl(src, dst);
}

void std_to_lapack(const array_2d<std::complex<real> > &src, array_2d<complex> &dst)
{
	std_to_lapack_tmpl(src, dst);
}

void std_to_lapack(const array_2d<std::complex<doublereal> > &src, array_2d<doublecomplex> &dst)
{
	std_to_lapack_tmpl(src, dst);
}



void lapack_to_std(const array<complex> &src, array<std::complex<real> > &dst)
{
	lapack_to_std_tmpl(src, dst);
}

void lapack_to_std(const array<doublecomplex> &src, array<std::complex<doublereal> > &dst)
{
	lapack_to_std_tmpl(src, dst);
}

void std_to_lapack(const array<std::complex<real> > &src, array<complex> &dst)
{
	std_to_lapack_tmpl(src, dst);
}

void std_to_lapack(const array<std::complex<doublereal> > &src, array<doublecomplex> &dst)
{
	std_to_lapack_tmpl(src, dst);
}



template class unroll<clapack::real>;
template class unroll<clapack::doublereal>;
*/

} // lina_details
} //ivl
