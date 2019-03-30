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
image_functions_impl_cv

This file has no include-guards and it should not be included by
the user. The code in this library is compiled into the project .lib file

todo: use the extern template macro, and allow the inclusion of
this file for further class extension
*/
#ifndef IMFI_CV_HPP
#define IMFI_CV_HPP

//#include "../../../image.hpp"
/*
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
*/

namespace ivl {

// Misc function declarations
//! quickview, View ivl::image(s) into titled window(s)
template <class T>
void show(const image<T>& img, const char* title)
{
	IplImage* ipl1 = img.ipl();
	cvNamedWindow(title, 1);
	cvShowImage(title, ipl1);
	cvWaitKey(0); // very important, contains event processing loop inside
	cvDestroyWindow(title);
	cvReleaseImage(&ipl1);
}

template <
	class T1, class D1, class T2, class D2, 
	class T3, class D3, class T4, class D4,
	class T5, class D5>
void imshow_impl(
	const image<T1, D1>& im1, const char* title1,
	const image<T2, D2>& im2, const char* title2,
	const image<T3, D3>& im3, const char* title3,
	const image<T4, D4>& im4, const char* title4,
	const image<T5, D5>& im5, const char* title5)
{
	IplImage* ipl1;
	IplImage* ipl2;
	IplImage* ipl3;
	IplImage* ipl4;
	IplImage* ipl5;

	ipl1 = im1.ipl();
	cvNamedWindow(title1, 1);
	cvShowImage(title1, ipl1);

	if(title2) {
		ipl2 = im2.ipl();
		cvNamedWindow(title2, 2);
		cvShowImage(title2, ipl2);
	}

	if(title3) {
		ipl3 = im3.ipl();
		cvNamedWindow(title3, 3);
		cvShowImage(title3, ipl3);
	}

	if(title4) {
		ipl4 = im4.ipl();
		cvNamedWindow(title4, 4);
		cvShowImage(title4, ipl4);
	}

	if(title5) {
		ipl5 = im5.ipl();
		cvNamedWindow(title5, 5);
		cvShowImage(title5, ipl5);
	}

	cvWaitKey(0); // very important, contains event processing loop inside

	cvDestroyWindow(title1);
	if(title2) cvDestroyWindow(title2);
	if(title3) cvDestroyWindow(title3);
	if(title4) cvDestroyWindow(title4);
	if(title5) cvDestroyWindow(title5);

	cvReleaseImage(&ipl1);
	if(title2) cvReleaseImage(&ipl2);
	if(title3) cvReleaseImage(&ipl3);
	if(title4) cvReleaseImage(&ipl4);
	if(title5) cvReleaseImage(&ipl5);
}


template <class T, class D>
void show(
	const image<T, D>& im1, const char* title1,
	const image<T, D>& im2, const char* title2,
	const image<T, D>& im3, const char* title3,
	const image<T, D>& im4, const char* title4,
	const image<T, D>& im5, const char* title5)
{
	IplImage* ipl1;
	IplImage* ipl2;
	IplImage* ipl3;
	IplImage* ipl4;
	IplImage* ipl5;

	ipl1 = im1.ipl();
	cvNamedWindow(title1, 1);
	cvShowImage(title1, ipl1);

	if(title2) {
		ipl2 = im2.ipl();
		cvNamedWindow(title2, 2);
		cvShowImage(title2, ipl2);
	}

	if(title3) {
		ipl3 = im3.ipl();
		cvNamedWindow(title3, 3);
		cvShowImage(title3, ipl3);
	}

	if(title4) {
		ipl4 = im4.ipl();
		cvNamedWindow(title4, 4);
		cvShowImage(title4, ipl4);
	}

	if(title5) {
		ipl5 = im5.ipl();
		cvNamedWindow(title5, 5);
		cvShowImage(title5, ipl5);
	}

	cvWaitKey(0); // very important, contains event processing loop inside

	cvDestroyWindow(title1);
	if(title2) cvDestroyWindow(title2);
	if(title3) cvDestroyWindow(title3);
	if(title4) cvDestroyWindow(title4);
	if(title5) cvDestroyWindow(title5);

	cvReleaseImage(&ipl1);
	if(title2) cvReleaseImage(&ipl2);
	if(title3) cvReleaseImage(&ipl3);
	if(title4) cvReleaseImage(&ipl4);
	if(title5) cvReleaseImage(&ipl5);
}

//! Sobel operator
template <class T, class D>
typename image<T, D>::create_new sobel(const image<T, D>& a,
	int y_order, int x_order, int aperture_size)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), (int)a.channels());
	cvSobel(src, dst, x_order, y_order, aperture_size);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

//! Laplace
template <class T, class D>
typename image<T, D>::create_new laplace(const image<T, D>& a,
	int aperture_size)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvLaplace(src, dst, aperture_size);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

//! Canny edge detection
template <class T, class D>
typename image<T, D>::create_new edges(const image<T, D>& a,
	double threshold1, double threshold2, int aperture_size)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), 1);
	cvCanny(src, dst, threshold1, threshold2, aperture_size);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

//! Corner detection, various algorithms
template <class T, class D>
typename image<T, D>::create_new pre_corner_detect(
	const image<T, D>& a, int aperture_size)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), 1);
	cvPreCornerDetect(src, dst, aperture_size);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new corner_eigenvals(
	const image<T, D>& a, int block_size, int aperture_size)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(
		image_details::cv_size(a.width() * 6, a.height()),
		image_details::ipl_depth<T>(), 1);
	cvCornerEigenValsAndVecs(src, dst, block_size, aperture_size);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new corner_min_eigenval(
	const image<T, D>& a, int block_size, int aperture_size)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), 1);
	cvCornerMinEigenVal(src, dst, block_size, aperture_size);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new corner_harris(const image<T, D>& a, int block_size,
	int aperture_size, double k)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), 1);
	cvCornerHarris(src, dst, block_size, aperture_size, k);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

//! Pyramid algorithm
template <class T, class D>
typename image<T, D>::create_new pyramid_up(const image<T, D>& a)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(
		image_details::cv_size(a.width() * 2, a.height() * 2),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvPyrUp(src, dst);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new pyramid_down(const image<T, D>& a)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(
		image_details::cv_size(a.width() / 2, a.height() / 2),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvPyrDown(src, dst);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

//! Resize
template <class T, class D>
typename image<T, D>::create_new resample(const image<T, D>& a, size_t rows, size_t cols,
	interpolation interp)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(
		image_details::cv_size(cols, rows),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvResize(src, dst, image_details::interpolation_map[interp]);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

//! Blur algorithms
template <class T, class D>
typename image<T, D>::create_new blur_no_scale(const image<T, D>& a, int neighbourhood_rows,
	int neighbourhood_cols)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvSmooth(src, dst, CV_BLUR_NO_SCALE, neighbourhood_cols, neighbourhood_rows);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new blur(const image<T, D>& a, int neighbourhood_rows,
	int neighbourhood_cols)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvSmooth(src, dst, CV_BLUR, neighbourhood_cols, neighbourhood_rows);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new gaussian_blur(const image<T, D>& a, int neighbourhood_rows,
	int neighbourhood_cols, int vertical_sigma, int horizontal_sigma)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src), image_details::ipl_depth<T>(),
		int(a.channels()));
	cvSmooth(src, dst, CV_GAUSSIAN, neighbourhood_cols, neighbourhood_rows,
		horizontal_sigma, vertical_sigma);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new median_blur(const image<T, D>& a, int neighbourhood)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvSmooth(src, dst, CV_MEDIAN, neighbourhood);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new bilateral_blur(const image<T, D>& a, int color_sigma,
	int space_sigma)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), int(a.channels()));
	cvSmooth(src, dst, CV_BILATERAL, color_sigma, space_sigma);
	typename image<T, D>::create_new r(dst);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new rotate(const image<T, D>& a, double angle,
	const float_point<2>& center, double scale, interpolation interp,
	warp_method warp_m, color<T, D::Ch> fill_color)
{
	IplImage* src = a.ipl();
	IplImage* dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), int(a.channels()));
	CvPoint2D32f cvcenter;
	cvcenter.x = center.x;
	cvcenter.y = center.y;
	CvMat* map_matrix = cvCreateMat(2, 3, image_details::cv_type<double>());
	cv2DRotationMatrix(cvcenter, angle, scale, map_matrix );
	cvWarpAffine(src, dst, map_matrix,
		image_details::interpolation_map[interp]+
		image_details::warp_map[warp_m] ,
		image_details::to_cvscalar(fill_color));
	typename image<T, D>::create_new r(dst);
	cvReleaseMat(&map_matrix);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

template <class T, class D>
typename image<T, D>::create_new get_quadrange_sub_pix(const image<T, D>& a,
		const array_2d<double>& map_matrix, const size_array& dst_size)
{
	IplImage* src = a.ipl();
	IplImage* dst;

	if(dst_size[0] == 0 && dst_size[1] == 0) {
		dst = cvCreateImage(cvGetSize(src),
		image_details::ipl_depth<T>(), int(a.channels()));
	} else {
		dst = cvCreateImage(cvSize(dst_size[1], dst_size[0]),
		image_details::ipl_depth<T>(), int(a.channels()));
	}

	CHECK(map_matrix.rows() == 2, eshape);
	CHECK(map_matrix.columns() == 2, eshape);

	CvMat* cvmap_matrix = cvCreateMat(2, 3, image_details::cv_type<double>());
	cvmSet(cvmap_matrix, 0, 0, map_matrix(0, 0));
	cvmSet(cvmap_matrix, 0, 1, map_matrix(0, 1));
	cvmSet(cvmap_matrix, 0, 2, map_matrix(0, 2));
	cvmSet(cvmap_matrix, 1, 0, map_matrix(1, 0));
	cvmSet(cvmap_matrix, 1, 1, map_matrix(1, 1));
	cvmSet(cvmap_matrix, 1, 2, map_matrix(1, 2));

	/*cvmap_matrix->data.db[0] = map_matrix(0, 0);
	cvmap_matrix->data.db[1] = map_matrix(0, 1);
	cvmap_matrix->data.db[2] = map_matrix(0, 2);
	cvmap_matrix->data.db[3] = map_matrix(1, 0);
	cvmap_matrix->data.db[4] = map_matrix(1, 1);
	cvmap_matrix->data.db[5] = map_matrix(1, 2);*/

	cvGetQuadrangleSubPix(src, dst, cvmap_matrix);

	typename image<T, D>::create_new r(dst);

	cvReleaseMat(&cvmap_matrix);
	cvReleaseImage(&src);
	cvReleaseImage(&dst);
	return r;
}

} // namespace ivl
#endif
