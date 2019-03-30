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

#include <ivl/array_2d.hpp>
#include "../../lina.hpp"
#include "lapack/lapack_utils.hpp"
#include "lapack/lapack_algorithms.hpp"
#include "lapack/geev.hpp"
#include "lapack/ggev.hpp"
#include "lapack/gesv.hpp"
#include "lapack/gesvd.hpp"
#include "lapack/getrf.hpp"
#include "lapack/geqrf.hpp"
#include "lapack/orgqr.hpp"
#include "lapack_interface_impl.hpp"
#include "eig_impl.hpp"
#include "inv_impl.hpp"
#include "lu_impl.hpp"
#include "qr_impl.hpp"
#include "svd_impl.hpp"

namespace ivl {
namespace lina_details {

using namespace clapack;

// explicit instantiations
template class _ivllina_export_ lapack_interface<clapack::real>;
template class _ivllina_export_ lapack_interface<clapack::doublereal>;
template class _ivllina_export_ lapack_interface<std::complex<clapack::real> >;
template class _ivllina_export_ lapack_interface<std::complex<clapack::doublereal> >;

// explicit instantiations
template class _ivllina_export_ eig<real>;
template class _ivllina_export_ eig<doublereal>;
template class _ivllina_export_ eig<std::complex<real> >;
template class _ivllina_export_ eig<std::complex<doublereal> >;

// explicit instantiations
template class _ivllina_export_ inv<clapack::real>;
template class _ivllina_export_ inv<clapack::doublereal>;
template class _ivllina_export_ inv<std::complex<clapack::real> >;
template class _ivllina_export_ inv<std::complex<clapack::doublereal> >;

// explicit instantiations
template class _ivllina_export_ lu<real>;
template class _ivllina_export_ lu<doublereal>;
template class _ivllina_export_ lu<std::complex<real> >;
template class _ivllina_export_ lu<std::complex<doublereal> >;

// explicit instantiations
template class _ivllina_export_ qr<real>;
template class _ivllina_export_ qr<doublereal>;
template class _ivllina_export_ qr<std::complex<real> >;
template class _ivllina_export_ qr<std::complex<doublereal> >;

// explicit instantiations
template class _ivllina_export_ svd<real>;
template class _ivllina_export_ svd<doublereal>;
template class _ivllina_export_ svd<std::complex<real> >;
template class _ivllina_export_ svd<std::complex<doublereal> >;

} /* namespace lina_details */
} /* namespace ivl */

