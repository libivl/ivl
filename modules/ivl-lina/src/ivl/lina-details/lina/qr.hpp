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

#ifndef IVL_LINA_DETAILS_QR_HPP
#define IVL_LINA_DETAILS_QR_HPP

#include "ivl/details/array_2d.hpp"

namespace ivl {
namespace lina_details {

template<class T>
class qr :
	public rvalue_output_converter<conversions::normal, qr<T> >
{
	// Orthogonal-triangular decomposition
private:
	array_2d<T, data::storable_link> a;
	const size_t m;
	const size_t n;
	const size_t min_nm;

public:
	template<class S>
	qr(const array_2d<T, S>& src);

	// x = qr(a)
	void output(array_2d<T>& x) const;

	// [q,r] = qr(a)
	void output(array_2d<T>& q, array_2d<T>& r) const;
};

template<class T>
template<class S>
qr<T>::qr(const array_2d<T, S>& src):
		a(ivl::storable_link(src)), m(a.rows()), n(a.columns()),
		min_nm((m < n) ? m : n)
{
	if(src.columns() == 0)
		throw eshape();
}

} /* namespace lina_details */

template<class T, class S>
lina_details::qr<T> qr(const array_2d<T, S>& x)
{
	return lina_details::qr<T>(x);
}

} /* namespace ivl */

#endif // IVL_LINA_DETAILS_QR_HPP
