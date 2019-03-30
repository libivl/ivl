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

#if 0
#include "image_functions_impl.hpp"

#ifndef IVL_NO_OPENCV
#include <cv.h>
#endif //IVL_NO_OPENCV

/* todo: could create some autogeneration scripts */

namespace ivl {

//--------------------------------------------------------------
// image INSTANCIATIONS (TEMPLATES COMPILED IN THE .lib FILE)


/* NOTE: the following instanciations ignore the coding style line-80 */
/* rule because they are a simple list maintaining the compiled functions   */
/* and as an exception to the rule, this list is much better read as single */
/* item per line. */

//--------------------------------------------------------------
// instanciations of type: unsigned char

#ifndef IVL_NO_OPENCV

template void show(const image<unsigned char>&, const char*);
template image<unsigned char> sobel(const image<unsigned char>&, int, int, int);
template image<unsigned char> laplace(const image<unsigned char>&, int);
template image<unsigned char> edges(const image<unsigned char>&, double, double, int);
template image<unsigned char> pre_corner_detect(const image<unsigned char>&, int);
template image<unsigned char> corner_eigenvals(const image<unsigned char>&, int, int);
template image<unsigned char> corner_min_eigenval(const image<unsigned char>&, int, int);
template image<unsigned char> corner_harris(const image<unsigned char>&, int, int, double);
template image<unsigned char> pyramid_up(const image<unsigned char>&);
template image<unsigned char> pyramid_down(const image<unsigned char>&);
template image<unsigned char> resample(const image<unsigned char>&, size_t, size_t, interpolation);
template image<unsigned char> blur_no_scale(const image<unsigned char>&, int, int);
template image<unsigned char> blur(const image<unsigned char>&, int, int);
template image<unsigned char> gaussian_blur(const image<unsigned char>&, int, int, int, int);
template image<unsigned char> median_blur(const image<unsigned char>&, int);
template image<unsigned char> bilateral_blur(const image<unsigned char>&, int, int);
template image<unsigned char> rotate(const image<unsigned char>&, double, const point<float>&, double, interpolation, warp_method , color<unsigned char>);
template image<unsigned char> get_quadrange_sub_pix(const image<unsigned char>&, const array_2d<double>&, const size_array&);


template void AA_trig_artsy(image<unsigned char>& im, point<double> a, point <double> b, point<double> c, color<unsigned char> col, int multisample, double opacity);
template void AA_trig(image<unsigned char>& im, point<double> a, point <double> b, point<double> c, color<unsigned char> col, int multisample, double opacity);
template void AA_quad(image<unsigned char>& im, point<double> a, point <double> b, point<double> c, point<double> d, color<unsigned char> col, int multisample, double opacity);
template void AA_circ(image<unsigned char>& im, point<double> a, double radius, color<unsigned char> col, int multisample, double opacity);
template void AA_circle(image<unsigned char>& im, point<double> a, double outradius, double inradius, color<unsigned char> col, int multisample, double opacity);
template void AA_fillellipse(image<unsigned char>& im, point<double> a, point<double> b, double radius, color<unsigned char> col, int multisample, double opacity);
template void AA_ellipse(image<unsigned char>& im, point<double> a, point<double> b, double outradius, double inradius, color<unsigned char> col, int multisample, double opacity);


/* TODO: corrections

template void AA_trig_artsy(image<T>& im, point<double> a, point <double> b, point<double> c, color<T> col, int multisample = 32);
template void AA_trig(image<T>& im, point<double> a, point <double> b, point<double> c, color<T> col, int multisample = 8);
template void AA_quad(image<T>& im, point<double> a, point <double> b, point<double> c, point<double> d, color<T> col, int multisample = 8);
template void AA_circle(image<T>& im, point<double> a, double radius, color<T> col, int multisample = 8);
*/

#endif //IVL_NO_OPENCV

template image<unsigned char> flipud(const image<unsigned char>&);
template image<unsigned char> fliplr(const image<unsigned char>&);
template image<unsigned char> grayscale(const image<unsigned char>&);

//--------------------------------------------------------------
// instanciations of type: short

#ifndef IVL_NO_OPENCV

template void show(const image<short>&, const char*);
template image<short> sobel(const image<short>&, int, int, int);
template image<short> laplace(const image<short>&, int);
template image<short> edges(const image<short>&, double, double, int);
template image<short> pre_corner_detect(const image<short>&, int);
template image<short> corner_eigenvals(const image<short>&, int, int);
template image<short> corner_min_eigenval(const image<short>&, int, int);
template image<short> corner_harris(const image<short>&, int, int, double);
template image<short> pyramid_up(const image<short>&);
template image<short> pyramid_down(const image<short>&);
template image<short> resample(const image<short>&, size_t, size_t, interpolation);
template image<short> blur_no_scale(const image<short>&, int, int);
template image<short> blur(const image<short>&, int, int);
template image<short> gaussian_blur(const image<short>&, int, int, int, int);
template image<short> median_blur(const image<short>&, int);
template image<short> bilateral_blur(const image<short>&, int, int);
template image<short> rotate(const image<short>&, double, const point<float>&, double, interpolation, warp_method , color<short>);
template image<short> get_quadrange_sub_pix(const image<short>&, const array_2d<double>&, const size_array&);

#endif //IVL_NO_OPENCV

template image<short> flipud(const image<short>&);
template image<short> fliplr(const image<short>&);
template image<short> grayscale(const image<short>&);

template void AA_trig_artsy(image<short>& im, point<double> a, point <double> b, point<double> c, color<short> col, int multisample, double opacity);
template void AA_trig(image<short>& im, point<double> a, point <double> b, point<double> c, color<short> col, int multisample, double opacity);
template void AA_quad(image<short>& im, point<double> a, point <double> b, point<double> c, point<double> d, color<short> col, int multisample, double opacity);
template void AA_circ(image<short>& im, point<double> a, double radius, color<short> col, int multisample, double opacity);
template void AA_circle(image<short>& im, point<double> a, double outradius, double inradius, color<short> col, int multisample, double opacity);
template void AA_fillellipse(image<short>& im, point<double> a, point<double> b, double radius, color<short> col, int multisample, double opacity);
template void AA_ellipse(image<short>& im, point<double> a, point<double> b, double outradius, double inradius, color<short> col, int multisample, double opacity);

//--------------------------------------------------------------
// instanciations of type: int

#ifndef IVL_NO_OPENCV

template void show(const image<int>&, const char*);
template image<int> sobel(const image<int>&, int, int, int);
template image<int> laplace(const image<int>&, int);
template image<int> edges(const image<int>&, double, double, int);
template image<int> pre_corner_detect(const image<int>&, int);
template image<int> corner_eigenvals(const image<int>&, int, int);
template image<int> corner_min_eigenval(const image<int>&, int, int);
template image<int> corner_harris(const image<int>&, int, int, double);
template image<int> pyramid_up(const image<int>&);
template image<int> pyramid_down(const image<int>&);
template image<int> resample(const image<int>&, size_t, size_t, interpolation);
template image<int> blur_no_scale(const image<int>&, int, int);
template image<int> blur(const image<int>&, int, int);
template image<int> gaussian_blur(const image<int>&, int, int, int, int);
template image<int> median_blur(const image<int>&, int);
template image<int> bilateral_blur(const image<int>&, int, int);
template image<int> rotate(const image<int>&, double, const point<float>&, double, interpolation, warp_method , color<int>);
template image<int> get_quadrange_sub_pix(const image<int>&, const array_2d<double>&, const size_array&);

#endif //IVL_NO_OPENCV

template image<int> flipud(const image<int>&);
template image<int> fliplr(const image<int>&);
template image<int> grayscale(const image<int>&);

template void AA_trig_artsy(image<int>& im, point<double> a, point <double> b, point<double> c, color<int> col, int multisample, double opacity);
template void AA_trig(image<int>& im, point<double> a, point <double> b, point<double> c, color<int> col, int multisample, double opacity);
template void AA_quad(image<int>& im, point<double> a, point <double> b, point<double> c, point<double> d, color<int> col, int multisample, double opacity);
template void AA_circ(image<int>& im, point<double> a, double radius, color<int> col, int multisample, double opacity);
template void AA_circle(image<int>& im, point<double> a, double outradius, double inradius, color<int> col, int multisample, double opacity);
template void AA_fillellipse(image<int>& im, point<double> a, point<double> b, double radius, color<int> col, int multisample, double opacity);
template void AA_ellipse(image<int>& im, point<double> a, point<double> b, double outradius, double inradius, color<int> col, int multisample, double opacity);


//--------------------------------------------------------------
// instanciations of type: double

#ifndef IVL_NO_OPENCV

template void show(const image<double>&, const char*);
template image<double> sobel(const image<double>&, int, int, int);
template image<double> laplace(const image<double>&, int);
template image<double> edges(const image<double>&, double, double, int);
template image<double> pre_corner_detect(const image<double>&, int);
template image<double> corner_eigenvals(const image<double>&, int, int);
template image<double> corner_min_eigenval(const image<double>&, int, int);
template image<double> corner_harris(const image<double>&, int, int, double);
template image<double> pyramid_up(const image<double>&);
template image<double> pyramid_down(const image<double>&);
template image<double> resample(const image<double>&, size_t, size_t, interpolation);
template image<double> blur_no_scale(const image<double>&, int, int);
template image<double> blur(const image<double>&, int, int);
template image<double> gaussian_blur(const image<double>&, int, int, int, int);
template image<double> median_blur(const image<double>&, int);
template image<double> bilateral_blur(const image<double>&, int, int);
template image<double> rotate(const image<double>&, double, const point<float>&, double, interpolation, warp_method , color<double>);
template image<double> get_quadrange_sub_pix(const image<double>&, const array_2d<double>&, const size_array&);

#endif //IVL_NO_OPENCV

template image<double> flipud(const image<double>&);
template image<double> fliplr(const image<double>&);
template image<double> grayscale(const image<double>&);

template void AA_trig_artsy(image<double>& im, point<double> a, point <double> b, point<double> c, color<double> col, int multisample, double opacity);
template void AA_trig(image<double>& im, point<double> a, point <double> b, point<double> c, color<double> col, int multisample, double opacity);
template void AA_quad(image<double>& im, point<double> a, point <double> b, point<double> c, point<double> d, color<double> col, int multisample, double opacity);
template void AA_circ(image<double>& im, point<double> a, double radius, color<double> col, int multisample, double opacity);
template void AA_circle(image<double>& im, point<double> a, double outradius, double inradius, color<double> col, int multisample, double opacity);
template void AA_fillellipse(image<double>& im, point<double> a, point<double> b, double radius, color<double> col, int multisample, double opacity);
template void AA_ellipse(image<double>& im, point<double> a, point<double> b, double outradius, double inradius, color<double> col, int multisample, double opacity);

//--------------------------------------------------------------
// instanciations of type: T (to help the liv maintainer replace)
/* (not valid code)
#ifndef IVL_NO_OPENCV

template void show(const image<T>&, const char*);
template Derived sobel(const image<T, Derived>&, int, int, int);
template Derived laplace(const image<T, Derived>&, int);
template Derived edges(const image<T, Derived>&, double, double, int);
template Derived pre_corner_detect(const image<T, Derived>&, int);
template Derived corner_eigenvals(const image<T, Derived>&, int, int);
template Derived corner_min_eigenval(const image<T, Derived>&, int, int);
template Derived corner_harris(const image<T, Derived>&, int, int, double);
template Derived pyramid_up(const image<T, Derived>&);
template Derived pyramid_down(const image<T, Derived>&);
template Derived resample(const image<T, Derived>&, size_t, size_t, interpolation);
template Derived blur_no_scale(const image<T, Derived>&, int, int);
template Derived blur(const image<T, Derived>&, int, int);
template Derived gaussian_blur(const image<T, Derived>&, int, int, int, int);
template Derived median_blur(const image<T, Derived>&, int);
template Derived bilateral_blur(const image<T, Derived>&, int, int);
template Derived rotate(const image<T, Derived>&, double, const point<float>&, double, interpolation, warp_method , color<T>);

#endif //IVL_NO_OPENCV

template Derived flipud(const image<T, Derived>&);
template Derived fliplr(const image<T, Derived>&);
template Derived grayscale(const image<T, Derived>&);
*/


#if 0
image<UINT8> corner_detect(const image<float>& a, int aperture_size)
{
	IplImage* src = a.ipl();

	// assume that the image is floating-point
	IplImage* corners = cvCloneImage(src);
	IplImage* dilated_corners = cvCloneImage(src);
	IplImage* corner_mask = cvCreateImage( cvGetSize(src), 8, 1 );
	cvPreCornerDetect( src, corners, 3 );
	cvDilate( corners, dilated_corners, 0, 1 );
	cvSub( corners, dilated_corners, corners );
	cvCmpS( corners, 0, corner_mask, CV_CMP_GE );
	cvReleaseImage( &corners );
	cvReleaseImage( &dilated_corners );

	image<UINT8> r(corner_mask);
	cvReleaseImage(&src);
	return r;
}
#endif

} //namespace ivl
#endif
