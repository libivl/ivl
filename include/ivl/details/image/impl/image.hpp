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

#ifndef IVL_IMAGE_DETAILS_IMAGE_HPP
#define IVL_IMAGE_DETAILS_IMAGE_HPP

namespace ivl {

//template <class T, class Derived> class pixel;

// print an image
template<class T, class S>
std::ostream& print(std::ostream& os, const image<T, S>& a);

/* Enum types used for image */
enum interpolation {
	nn = 0,
	linear = 1,
	area = 2,
	cubic = 3
};
enum warp_method {
	fill_outliers = 0,
	inverse_map = 1
};
enum image_channels {
    ic_auto = 0,
    ic_mono = 1,
    ic_color = 2
};

#include "specialization/opencv_impl_false.hpp"
#include "specialization/image_class.hpp"

// ---------------------------------------------------------------------------
//  Implementation
// ---------------------------------------------------------------------------


//#ifndef IVL_NO_OPENCV
//! Construct from filename
// channels: ic_auto, ic_mono or ic_color
template <class T, class S>
image<T, S>::image(const std::string& filename, image_channels channels)
{
	// load the image file into a temporary IplImage
	load(filename, channels);
}

//! Construct from IplImage
template <class T, class S>
image<T, S>::image(const iplimage_t* ipl)
{
	(*this) = ipl;
}
//#endif //IVL_NO_OPENCV

#if 0


template <class T, class D>
inline pixel<T, D> image<T, D>::col(size_t row, size_t col)
{
	return pixel<T, D> (*this, row, col);
}
#endif


} /* namespace ivl */

#endif // IVL_IMAGE_DETAILS_IMAGE_HPP
