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

/*
image_functions_impl

This file has no include-guards and it should not be included by
the user. The code in this library is compiled into the project .lib file

todo: use the extern template macro, and allow the inclusion of
this file for further class extension
*/
#ifndef IMFI_HPP
#define IMFI_HPP

//#include "../../../image.hpp"

//#ifdef min
//#undef min
//#endif
//#ifdef max
//#undef max
//#endif

namespace ivl {

/* IMAGE PROCESSING FUNCTIONS */

//! Horizontal and vertical flipping
template <class T, class D>
typename image<T, D>::create_similar flipud(const image<T, D>& a)
{
	return flipdim(a, 0);
}

template <class T, class D>
typename image<T, D>::create_similar fliplr(const image<T, D>& a)
{
	return flipdim(a, 1);
}

//! Grayscale
template <class T, class D>
typename image<T, D>::create_similar grayscale(const image<T, D>& a)
{
	size_t ch = a.channels();
	CHECK(ch > 1, erange());
	size_t w = a.width();
	size_t h = a.height();
	typename types::promote<T>::type acc;
	typename image<T, D>::create_similar r(h, w, 1, 0);
	for(size_t i = 0; i < h; i++) {
		for(size_t j = 0; j < w; j++) {
			acc = a(i, j, 0);
			for(size_t col = 1; col < ch; col++)
				acc += a(i, j, col);
			acc /= typename types::promote<T>::type(ch);
			r(i, j) = T(acc);
		}
	}
	return r;
}

} // namespace ivl
#endif
