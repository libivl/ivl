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

#ifndef IVL_LINA_DETAILS_LU_HPP
#define IVL_LINA_DETAILS_LU_HPP

#include "ivl/details/array_2d.hpp"

namespace ivl {
namespace lina_details {

template<class T>
class lu:
	public rvalue_output_converter<conversions::normal, lu<T> >
{
	// Orthogonal-triangular decomposition
private:
	array_2d<T, data::storable_link> a;
	const size_t m;
	const size_t n;

public:
	template<class S>
	lu(const array_2d<T, S>& src);

	// [L,U] = lu(a)
	void output(array_2d<T>& l, array_2d<T>& u) const;
	// TODO: add the matlab variants, including the ipiv information
};

template<class T, class S>
T det(const array_2d<T, S> x);

template<class T>
template<class S>
lu<T>::lu(const array_2d<T, S>& src) :
	a(ivl::storable_link(src)), m(a.rows()), n(a.columns())
{
	if(src.columns() == 0)
		throw eshape();
	if(src.columns() != src.rows())
		throw eshape();
}

} /* namespace lina_details */

template<class T, class S>
lina_details::lu<T> lu(const array_2d<T, S>& x)
{
	return lina_details::lu<T>(x);
}

//! Determinant of square array_2d x
template<class T, class S>
T det(const array_2d<T, S>& x)
{
	return lina_details::det(x);
}

} /* namespace ivl */

#endif // IVL_LINA_DETAILS_LU_HPP
