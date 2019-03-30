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

#ifndef IVL_IMAGE_DETAILS_IMAGE_FUNCTIONS_HPP
#define IVL_IMAGE_DETAILS_IMAGE_FUNCTIONS_HPP

namespace ivl {

template <class T>
inline
std::ostream& print(std::ostream& os, const image<T>& in)
{
	return print_array_nd(os, in);
}


/**
 * @name Image non-member functions
 * \relates image
@{*/

// Misc function declarations
//! quickview, View ivl::image(s) into titled window(s)
//template<class T, class D>
//void show(const image<T, D>& img, const char* title);

//! quickview
template <class T, class D>
void show(
	const image<T, D>& im1, const char* title1,
	const image<T, D>& im2 = image<T, D>(), const char* title2 = NULL,
	const image<T, D>& im3 = image<T, D>(), const char* title3 = NULL,
	const image<T, D>& im4 = image<T, D>(), const char* title4 = NULL,
	const image<T, D>& im5 = image<T, D>(), const char* title5 = NULL);


template <
	class T1, class D1, class T2, class D2, 
	class T3, class D3, class T4, class D4,
	class T5, class D5>
void imshow_impl(
	const image<T1, D1>& im1, const char* title1,
	const image<T2, D2>& im2, const char* title2,
	const image<T3, D3>& im3, const char* title3,
	const image<T4, D4>& im4, const char* title4,
	const image<T5, D5>& im5, const char* title5);

template <class T, class D>
void imshow(
	const image<T, D>& im1, const char* title1 = "")
{
	ivl::imshow_impl(im1, title1, 
		image<T, D>(), NULL, image<T, D>(), NULL, image<T, D>(), NULL, 
		image<T, D>(), NULL);
}
// ---------------------------------------------------

template <class T, class D, class T2, class D2>
void imshow(
	const image<T, D>& im1, const char* title1,
	const image<T2, D2>& im2, const char* title2 = ""
	)
{
	ivl::imshow_impl(im1, title1, im2, title2, 
		image<T, D>(), NULL, image<T, D>(), 
		NULL, image<T, D>(), NULL);
}
template <class T, class D, class T2, class D2>
void imshow(
	const image<T, D>& im1,	const image<T2, D2>& im2)
{
	ivl::imshow_impl(im1, "", im2, "", 
		image<T, D>(), NULL, image<T, D>(), NULL, 
		image<T, D>(), NULL);
}
// ---------------------------------------------------
template <class T, class D, class T2, class D2, class T3, class D3>
void imshow(
	const image<T, D>& im1, const char* title1,
	const image<T2, D2>& im2, const char* title2,
	const image<T3, D3>& im3, const char* title3 = ""
	)
{
	ivl::imshow_impl(im1, title1, im2, title2, im3, title3,
		image<T, D>(), NULL, image<T, D>(), NULL);
}
template <class T, class D, class T2, class D2, class T3, class D3>
void imshow(
	const image<T, D>& im1,	const image<T2, D2>& im2,	
	const image<T3, D3>& im3)
{
	ivl::imshow_impl(im1, "", im2, "", im3, "",
		image<T, D>(), NULL, image<T, D>(), NULL);
}


// Misc function declarations
//! quickview, View ivl::image(s) into titled window(s)
template<class T, class D>
void view(const image<T, D>& img, const char* title);

/* IMAGE PROCESSING FUNCTIONS */

//! Horizontal and vertical flipping
template <class T, class D>
typename image<T, D>::create_similar flipud(const image<T, D>& a);

template <class T, class D>
typename image<T, D>::create_similar fliplr(const image<T, D>& a);

//! Grayscale
template <class T, class D>
typename image<T, D>::create_similar grayscale(const image<T, D>& a);

//! Sobel operator
template <class T, class D>
typename image<T, D>::create_new sobel(const image<T, D>& a, int y_order, int x_order,
	       int aperture_size = 3);

//! Laplace
template <class T, class D>
typename image<T, D>::create_new laplace(const image<T, D>& a, int aperture_size = 3);

//! Canny edge detection
template <class T, class D>
typename image<T, D>::create_new edges(const image<T, D>& a, double threshold1,
	double threshold2, int aperture_size = 3);

//! Corner detection, various algorithms
template <class T, class D>
typename image<T, D>::create_new pre_corner_detect(const image<T, D>& a, int aperture_size = 3);

template <class T, class D>
typename image<T, D>::create_new corner_eigenvals(const image<T, D>& a, int block_size,
	int aperture_size = 3);

template <class T, class D>
typename image<T, D>::create_new corner_min_eigenval(const image<T, D>& a, int block_size,
	int aperture_size = 3);

template <class T, class D>
typename image<T, D>::create_new corner_harris(const image<T, D>& a, int block_size,
	int aperture_size = 3, double k = 0.04);

//! Pyramid algorithm
template <class T, class D>
typename image<T, D>::create_new pyramid_up(const image<T, D>& a);

template <class T, class D>
typename image<T, D>::create_new pyramid_down(const image<T, D>& a);

//! Resize
template <class T, class D>
typename image<T, D>::create_new resample(const image<T, D>& a, size_t rows, size_t cols,
	interpolation interp = linear);

//! Blur algorithms
template <class T, class D>
typename image<T, D>::create_new blur_no_scale(const image<T, D>& a, int neighbourhood_rows = 0,
	int neighbourhood_cols = 3);

template <class T, class D>
typename image<T, D>::create_new blur(const image<T, D>& a, int neighbourhood_rows = 0,
	int neighbourhood_cols = 3);

template <class T, class D>
typename image<T, D>::create_new gaussian_blur(const image<T, D>& a, int neighbourhood_rows = 0,
	int neighbourhood_cols = 3, int vertical_sigma = 0, int horizontal_sigma = 0);

template <class T, class D>
typename image<T, D>::create_new median_blur(const image<T, D>& a, int neighbourhood = 3);

template <class T, class D>
typename image<T, D>::create_new bilateral_blur(const image<T, D>& a, int color_sigma = 3,
	int space_sigma = 3);

//! Image Rotation
template <class T, class D>
typename image<T, D>::create_new rotate(const image<T, D>& a, double angle, const float_point<2>& center,
	double scale = 1.0, interpolation interp = linear,
	warp_method warp_m = fill_outliers,
    color<T, D::Ch> fill_color = ivl::colors::black(colors::color_type<T, colors::rgb>()));

//! get_quadrange_sub_pix OpenCV wrapper.
template <class T, class D>
typename image<T, D>::create_new get_quadrange_sub_pix(const image<T, D>& a,
		const array_2d<double>& map_matrix, const size_array& dst_size = idx(0, 0));
//@}


// -------------------- TODO coding style
/*
template<class T, class D>
void AA_trig_artsy(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, color<T, D::Ch> col, int multisample = 32, double opacity = 1.);


template<class T, class D>
void AA_trig(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, color<T, D::Ch> col, int multisample = 8, double opacity = 1.);


template<class T, class D>
void AA_quad(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, double_point<2> d,
			 typename image<T, D>::color_type col, int multisample = 8, double opacity = 1.);

template<class T, class D>
void AA_circ(image<T, D>& im, double_point<2> a, double radius, color<T, D::Ch> col, int multisample = 8, double opacity = 1.);

template<class T, class D>
void AA_circle(image<T, D>& im, double_point<2> a, double outradius, double inradius, color<T, D::Ch> col, int multisample = 8, double opacity = 1.);

template<class T, class D>
void AA_fillellipse(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, color<T, D::Ch> col, int multisample = 8, double opacity = 1.);

template<class T, class D>
void AA_ellipse(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, double thickness, color<T, D::Ch> col, int multisample = 8, double opacity = 1.);
*/
// ------------------------------

template <class T, class D>
void line_on(image<T, D>& im, double_point<2> a, double_point<2> b, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double thickness = 1.5, double opacity = 1.)
{
	double_point<2> vec(b.y - a.y, b.x - a.x);
	double theta = std::atan2(vec.y, vec.x);
	double rtheta = theta + 3.141592653589793 / 2; // TODO: do something with pi
	thickness /= 2;
	double_point<2> edge(std::sin(rtheta) * thickness, std::cos(rtheta) * thickness);

	ivl::AA_quad(im,
		double_point<2>(1),
		double_point<2>(1),
		double_point<2>(1),
		double_point<2>(1),
				col, 8, opacity);
}

template <class T, class D>
typename image<T, D>::derived_type& circle_on(image<T, D>& im, double_point<2> a, double radius, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double thickness = 1.5, double opacity = 1.)
{
	thickness /= 2;
	AA_circle(im, a, radius + thickness, radius - thickness, col, 8, opacity);
	return im.derived();
}

template <class T, class D>
typename image<T, D>::derived_type& rect_on(image<T, D>& im, double_point<2> a, double_point<2> b, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double thickness = 1.5, double opacity = 1.)
{
	double_point<2> c(a.y, b.x);
	double_point<2> d(b.y, a.x);

	im.line(a, c, col, thickness, opacity);
	im.line(c, b, col, thickness, opacity);
	im.line(b, d, col, thickness, opacity);
	return line_on(im, d, a, col, thickness, opacity);
}

template <class T, class D>
typename image<T, D>::derived_type& ellipse_on(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double thickness = 1.5, double opacity = 1.)
{
	thickness /= 2;
	AA_ellipse(im, a, b, 2 * radius, thickness, col, 8, opacity);
	return im.derived();
}

template <class T, class D>
typename image<T, D>::derived_type& ellipse_on(image<T, D>& im, double_point<2> c, double radius1, double radius2, double angle, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double thickness = 1.5, double opacity = 1.)
{
	double pi = 3.141592653589793; // todo: ivl::pi
	if(radius1 < radius2) {
		std::swap(radius1, radius2);
		angle += pi / 2;
		if(angle > 2 * pi) angle -= 2 * pi;
	}

	double displace = std::sqrt(radius1 * radius1 - radius2 * radius2);
	double_point<2> displ(std::sin(angle) * displace, std::cos(angle) * displace);

	AA_ellipse(im, double_point<2>(c + displ), double_point<2>(c - displ), 2 * radius1,
				thickness, col, 8, opacity);
	return im.derived();
}

template <class T, class D>
typename image<T, D>::derived_type& fill_circle_on(image<T, D>& im, double_point<2> a, double radius, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double opacity = 1.)
{
	AA_circ(im, a, radius, col, 8, opacity);
	return im.derived();
}

template <class T, class D>
typename image<T, D>::derived_type& fill_rect_on(image<T, D>& im, double_point<2> a, double_point<2> b, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double opacity = 1.)
{
	a = double_point<2>(std::min(a.y, b.y), std::min(a.x, b.x));
	b = double_point<2>(std::max(a.y, b.y), std::max(a.x, b.x));

	double_point<2> c(a.y, b.x);
	double_point<2> d(b.y, a.x);

	AA_quad(im, a, c, b, d, col, 8, opacity);
	return im.derived();
}

template <class T, class D>
typename image<T, D>::derived_type& fill_ellipse_on(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double opacity = 1.)
{
	AA_fillellipse(im, a, b, 2 * radius, col, 8, opacity);
	return im.derived();
}

template <class T, class D>
typename image<T, D>::derived_type& fill_ellipse_on(image<T, D>& im, double_point<2> c, double radius1, double radius2, double angle, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double opacity = 1.)
{
	double pi = 3.141592653589793; // todo: ivl::pi
	if(radius1 < radius2) {
		std::swap(radius1, radius2);
		angle += pi / 2;
		if(angle > 2 * pi) angle -= 2 * pi;
	}

	double displace = std::sqrt(radius1 * radius1 - radius2 * radius2);
	double_point<2> displ(std::sin(angle) * displace, std::cos(angle) * displace);

	AA_fillellipse(im, double_point<2>(c + displ), double_point<2>(c - displ),
					2 * radius1, col, 8, opacity);
	return im.derived();
}


template <class T, class D>
typename image<T, D>::derived_type& fill_triangle_on(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double opacity = 1.)
{
	AA_trig(im, a, b, c, col, 8, opacity);
	return im.derived();
}

template <class T, class D>
typename image<T, D>::derived_type& fill_quad_on(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, double_point<2> d, color<T, D::Ch> col = colors::white(colors::color_type<T, colors::rgb>()), double opacity = 1.)
{
	AA_quad(im, a, b, c, d, col, 8, opacity);
	return im.derived();
}


//

template<class T>
image<T> imread(const char* str)
{
	image<T> im;
	im.load(str);
	return im;
}

//


} /* namespace ivl */

#endif // IVL_IMAGE_DETAILS_IMAGE_FUNCTIONS_HPP
