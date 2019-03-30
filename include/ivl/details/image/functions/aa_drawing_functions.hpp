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

#ifndef IVL_IMAGE_DETAILS_FUNCTIONS_AA_DRAWING_FUNCTIONS_HPP
#define IVL_IMAGE_DETAILS_FUNCTIONS_AA_DRAWING_FUNCTIONS_HPP

namespace ivl {

namespace image_details {

inline bool cw(double_point<2> a, double_point<2> b, double_point<2> p)
// returns true if a, b, c are clockwise
{
	return (b.y - a.y) * (p.x - a.x) >= (b.x - a.x) * (p.y - a.y);
}

inline double cwd(double_point<2> a, double_point<2> b, double_point<2> p)
// returns > 0 if a, b, c are clockwise, 0 if they are in line, < 0 counter clockwise
{
	return (b.y - a.y) * (p.x - a.x) - (b.x - a.x) * (p.y - a.y);
}

inline bool intrig(double_point<2> a, double_point<2> b, double_point<2> c, double_point<2> p)
// returns true if the point p lies in the triangle a, b, c (demands: a, b, c clockwise)
{
	return cw(a, b, p) && cw(b, c, p) && cw(c, a, p);
}

inline bool inquad(double_point<2> a, double_point<2> b, double_point<2> c, double_point<2> d, double_point<2> p)
// returns true if the point p is in the quad, and demands a, b, c, d clockwise
{
	return cw(a, b, p) && cw(b, c, p) && cw(c, d, p) && cw(d, a, p);
}

inline bool crossinter(double_point<2> a1, double_point<2> a2, double_point<2> b1, double_point<2> b2)
// returns true if the line segments (a1, a2) and (b1, b2) intersect
{
	return (cwd(a1, a2, b1) * cwd(a1, a2, b2) < 0 ) && (cwd(b1, b2, a1) * cwd(b1, b2, a2) < 0 );
}

inline bool incirc(double_point<2> a, double sqrradius, double_point<2> p)
// returns true if the point is in the circle (a, square_root(sqrradius) )
{
	double dy = a.y - p.y;
	double dx = a.x - p.x;
	return dx * dx + dy * dy <= sqrradius;
}

inline bool inellipse(double_point<2>::base_class a, double_point<2>::base_class b,
					double sqrradius, double_point<2>::base_class p)
// returns true if the point is in the circle (a, square_root(sqrradius) )
{
	double dy1 = a.y - p.y;
	double dx1 = a.x - p.x;
	double dy2 = b.y - p.y;
	double dx2 = b.x - p.x;

	return dx1 * dx1 + dy1 * dy1 + dx2 * dx2 + dy2 * dy2 +
		2 * std::sqrt((dx1 * dx1 + dy1 * dy1)*(dx2 * dx2 + dy2 * dy2)) <= sqrradius;
}

inline bool inellipse2(double_point<2>::base_class a, double_point<2>::base_class b,
					double sqrradius, double thickness,
					double_point<2>::base_class p)
// returns true if the point is in the circle (a, square_root(sqrradius) )
{
	if(thickness < 0 && inellipse(a, b, sqrradius, p)) return true;
	if(thickness > 0) {
		double dy = p.y - (a.y + b.y) / 2.;
		double dx = p.x - (a.x + b.x) / 2.;

		double theta = std::atan2(dy, dx);
		double_point<2> thickvec(std::sin(theta) * thickness,
						   std::cos(theta) * thickness);

		if(!inellipse(a, b, sqrradius, p + thickvec)) return false;
	}
	double dy1 = p.y - a.y;
	double dx1 = p.x - a.x;
	double dy2 = p.y - b.y;
	double dx2 = p.x - b.x;

	double theta1 = std::atan2(dy1, dx1);
	double theta2 = std::atan2(dy2, dx2);

	double_point<2> normvec((std::sin(theta1) + std::sin(theta2)),
						  (std::cos(theta1) + std::cos(theta2)));

	theta1 = std::atan2(normvec.y, normvec.x);

	double_point<2> thickvec(std::sin(theta1) * thickness,
						   std::cos(theta1) * thickness);

/*	double prevdy1 = dy1;
	double prevdy2 = dy2;
	double prevdx1 = dx1;
	double prevdx2 = dx2; */

	p = p + thickvec;

	return inellipse(a, b, sqrradius, p);

/*	TODO: check if overextending inner thickness goes out of boundary of ellipse
	dy1  += normvec.y;
	dy2 += normvec.y;
	dx1 += normvec.x;
	dx2 += normvec.x;

	if(dy1 * prevdy1 < 0) dy1 = 0;
	if(dy2 * prevdy2 < 0) dy2 = 0;
	if(dx1 * prevdx1 < 0) dx1 = 0;
	if(dx2 * prevdx2 < 0) dx2 = 0;
*/

}



template <class T, class D>
void AA_trig_artsy_impl(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, color<T, D::Ch> col, int multisample = 32, double opacity = 1.)
{
	if(!cw(a, b, c)) std::swap(b, c);

	int y0 = int(min(arr._<double>()(a.y, b.y, c.y))) - 1;
	int x0 = int(min(arr._<double>()(a.x, b.x, c.x))) - 1;
	int y1 = int(ivl::max(arr._<double>()(a.y, b.y, c.y))) + 1;
	int x1 = int(max(arr._<double>()(a.x, b.x, c.x))) + 1;

	y0 = std::max(y0, 0);
	x0 = std::max(x0, 0);
	y1 = std::min(y1, int(im.rows() - 1));
	x1 = std::min(x1, int(im.cols() - 1));

	double coveradd = opacity / double(multisample * multisample);
	double pixeladd = 1. / double(multisample - 1);
	array<double> colord = cast<double>(col);

	int y, x, i, j;

	for(y = y0; y < y1; y++) {

		for(x = x0; x < x1; x++) {

			double_point<2> px1(double(y) - .5, double(x) - .5);
			double_point<2> px2(double(y) + .5, double(x) - .5);
			double_point<2> px3(double(y) + .5, double(x) + .5);
			double_point<2> px4(double(y) - .5, double(x) + .5);

			bool pin1 = intrig(a, b, c, px1);
			bool pin2 = intrig(a, b, c, px2);
			bool pin3 = intrig(a, b, c, px3);
			bool pin4 = intrig(a, b, c, px4);

			bool allin = pin1 && pin2 && pin3 && pin4;
			bool partin = pin1 || pin2 || pin3 || pin4;

			if(!partin) partin =
				crossinter(px1, px2, a, b) || crossinter(px1, px2, b, c) || crossinter(px1, px2, c, a) ||
				crossinter(px2, px3, a, b) || crossinter(px2, px3, b, c) || crossinter(px2, px3, c, a) ||
				crossinter(px3, px4, a, b) || crossinter(px3, px4, b, c) || crossinter(px3, px4, c, a) ||
				crossinter(px4, px1, a, b) || crossinter(px4, px1, b, c) || crossinter(px4, px1, c, a);

			array<double> interp;
			double cover = 0.0;

			if(0 && allin) im.col(y, x) = col;
			else if(1 || partin) { // AA
				interp = cast<double>(im.col(y, x));

				for(i = 0; i < multisample; i++) {

					for(j = 0; j < multisample; j++) {

						if(intrig(a, b, c, px1)) cover += coveradd;

						px1.x += pixeladd;
					}
					px1.y += pixeladd;
				}

				interp *= (double(1.) - cover);
				interp += colord * cover;

				im.col(y, x) = cast<T>(interp);
			}
		}
	}
}


template <class T, class D>
void AA_trig_impl(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, color<T, D::Ch> col, int multisample = 8, double opacity = 1.)
{
	// ensures that points in triangle are given in clockwise order
	if(!cw(a, b, c)) std::swap(b, c);

	// bounding box
	int y0 = int(min(arr._<double>()(a.y, b.y, c.y))) - 1;
	int x0 = int(min(arr._<double>()(a.x, b.x, c.x))) - 1;
	int y1 = int(max(arr._<double>()(a.y, b.y, c.y))) + 1;
	int x1 = int(max(arr._<double>()(a.x, b.x, c.x))) + 1;

	// clipping!
	y0 = std::max(y0, 0);
	x0 = std::max(x0, 0);
	y1 = std::min(y1, int(im.rows() - 1));
	x1 = std::min(x1, int(im.cols() - 1));

	// for multisampling
	double coveradd = opacity / double(multisample * multisample);
	double pixeladd = 1. / double(multisample + 1);

	// the color, in array format due to incompatibility issues. TODO: fix
	array<double> colord = cast<double>(col);

	int y, x, i, j;

	for(y = y0; y < y1; y++) {

		for(x = x0; x < x1; x++) {

			// the four corners that enclose the pixel
			double_point<2> px1(double(y) - .5, double(x) - .5);
			double_point<2> px2(double(y) + .5, double(x) - .5);
			double_point<2> px3(double(y) + .5, double(x) + .5);
			double_point<2> px4(double(y) - .5, double(x) + .5);

			// checks if each of the four corners are in the shape
			bool pin1 = intrig(a, b, c, px1);
			bool pin2 = intrig(a, b, c, px2);
			bool pin3 = intrig(a, b, c, px3);
			bool pin4 = intrig(a, b, c, px4);

			bool allin = pin1 && pin2 && pin3 && pin4;
			bool partin = pin1 || pin2 || pin3 || pin4;

			// if no point is in the shape we need to assure that
			// also the shape is not in the pixel box
			// the test for a tiny shape that lies fully in the pixel is omitted for speed (not very useful)
			if(!partin) partin =
				crossinter(px1, px2, a, b) || crossinter(px1, px2, b, c) || crossinter(px1, px2, c, a) ||
				crossinter(px2, px3, a, b) || crossinter(px2, px3, b, c) || crossinter(px2, px3, c, a) ||
				crossinter(px3, px4, a, b) || crossinter(px3, px4, b, c) || crossinter(px3, px4, c, a) ||
				crossinter(px4, px1, a, b) || crossinter(px4, px1, b, c) || crossinter(px4, px1, c, a);

			array<double> interp;
			double cover = 0.0;

			if(allin) {
				if(opacity == 1.) im.col(y, x) = col;
				else {
					interp = cast<double>(im.col(y, x));
					interp *= (double(1.) - opacity);
					interp += colord * opacity;

					im.col(y, x) = cast<T>(interp);
				}
			} else if(partin) { // AA
				interp = cast<double>(im.col(y, x));

				px1.x += pixeladd;
				px1.y += pixeladd;

				for(i = 0; i < multisample; i++) {

					for(j = 0; j < multisample; j++) {

						// tests a grid of (multisample x multisample) points
						// in the pixel box and counts how many are in the shape
						if(intrig(a, b, c, px1)) cover += coveradd;

						px1.x += pixeladd;
					}
					px1.x = px2.x + pixeladd;
					px1.y += pixeladd;
				}

				// perform transparency with cover as a parameter
				interp *= (double(1.) - cover);
				interp += colord * cover;

				im.col(y, x) = cast<T>(interp);
			}
		}
	}
}


template <class T, class D>
void AA_quad_impl(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, double_point<2> d,
    color<T, D::Ch> col, int multisample = 8, double opacity = 1.)
{
	// tries to put the points in the quad in clockwise order
	if(!cw(a, b, c)) std::swap(b, d);

	CHECK(cw(a, b, c), eshape()); // TODO: needs egeometry, but dont do it in this branch
	CHECK(cw(b, c, d), eshape()); // TODO: needs egeometry, but dont do it in this branch
	CHECK(cw(c, d, a), eshape()); // TODO: needs egeometry, but dont do it in this branch
	// "Quad is not cw"

	// bounding box
	int y0 = int(min(arr._<double>()(a.y, b.y, c.y, d.y))) - 1;
	int x0 = int(min(arr._<double>()(a.x, b.x, c.x, d.x))) - 1;
	int y1 = int(max(arr._<double>()(a.y, b.y, c.y, d.y))) + 1;
	int x1 = int(max(arr._<double>()(a.x, b.x, c.x, d.x))) + 1;

	// clipping!
	y0 = std::max(y0, 0);
	x0 = std::max(x0, 0);
	y1 = std::min(y1, int(im.rows() - 1));
	x1 = std::min(x1, int(im.cols() - 1));

	// for multisampling
	double coveradd = opacity / double(multisample * multisample);
	double pixeladd = 1. / double(multisample + 1);

	// the color, in array format due to incompatibility issues. TODO: fix
	array<double> colord = ivl::cast<double>(col);

	int y, x, i, j;

	for(y = y0; y < y1; y++) {

		for(x = x0; x < x1; x++) {

			// the four corners that enclose the pixel
			double_point<2> px1(double(y) - .5, double(x) - .5);
			double_point<2> px2(double(y) + .5, double(x) - .5);
			double_point<2> px3(double(y) + .5, double(x) + .5);
			double_point<2> px4(double(y) - .5, double(x) + .5);

			// checks if each of the four corners are in the shape
			bool pin1 = inquad(a, b, c, d, px1);
			bool pin2 = inquad(a, b, c, d, px2);
			bool pin3 = inquad(a, b, c, d, px3);
			bool pin4 = inquad(a, b, c, d, px4);

			bool allin = pin1 && pin2 && pin3 && pin4;
			bool partin = pin1 || pin2 || pin3 || pin4;

			// if no point is in the shape we need to assure that
			// also the shape is not in the pixel box
			// the test for a tiny shape that lies fully in the pixel is omitted for speed (not very useful)
			if(!partin) partin =
				crossinter(px1, px2, a, b) || crossinter(px1, px2, b, c) || crossinter(px1, px2, c, d) ||
				crossinter(px2, px3, a, b) || crossinter(px2, px3, b, c) || crossinter(px2, px3, c, d) ||
				crossinter(px3, px4, a, b) || crossinter(px3, px4, b, c) || crossinter(px3, px4, c, d) ||
				crossinter(px4, px1, a, b) || crossinter(px4, px1, b, c) || crossinter(px4, px1, c, d);

			// interpolated color for opacity
			array<double> interp;
			// pixel coverage accumulator 0.0 - 1.0
			double cover = 0.0;

			if(allin) {
				if(opacity == 1.) im.col(y, x) = col;
				else {
					interp = cast<double>(im.col(y, x));
					interp *= (double(1.) - opacity);
					interp += colord * opacity;

					im.col(y, x) = cast<T>(interp);
				}
			} else if(partin) { // AA
				interp = cast<double>(im.col(y, x));

				px1.x += pixeladd;
				px1.y += pixeladd;

				for(i = 0; i < multisample; i++) {

					for(j = 0; j < multisample; j++) {
						// tests a grid of (multisample x multisample) points
						// in the pixel box and counts how many are in the shape
						if(inquad(a, b, c, d, px1)) cover += coveradd;

						px1.x += pixeladd;
					}
					px1.x = px2.x + pixeladd;
					px1.y += pixeladd;
				}

				// perform transparency with cover as a parameter
				interp *= (double(1.) - cover);
				interp += colord * cover;

				im.col(y, x) = cast<T>(interp);
			}
		}
	}
}


template <class T, class D>
void AA_circ_impl(image<T, D>& im, double_point<2> a, double radius, color<T, D::Ch> col, int multisample = 8, double opacity = 1.)
{
	// bounding box
	int y0 = int(a.y - radius) - 1;
	int x0 = int(a.x - radius) - 1;
	int y1 = int(a.y + radius) + 1;
	int x1 = int(a.x + radius) + 1;

	// clipping!
	y0 = std::max(y0, 0);
	x0 = std::max(x0, 0);
	y1 = std::min(y1, int(im.rows() - 1));
	x1 = std::min(x1, int(im.cols() - 1));

	double sqrradius = radius * radius;

	// for multisampling
	double coveradd = opacity / double(multisample * multisample);
	double pixeladd = 1. / double(multisample + 1);

	// the color, in array format due to incompatibility issues. TODO: fix
	array<double> colord = cast<double>(col);

	int y, x, i, j;

	for(y = y0; y < y1; y++) {

		for(x = x0; x < x1; x++) {

			// the four corners that enclose the pixel
			double_point<2> px1(double(y) - .5, double(x) - .5);
			double_point<2> px2(double(y) + .5, double(x) - .5);
			double_point<2> px3(double(y) + .5, double(x) + .5);
			double_point<2> px4(double(y) - .5, double(x) + .5);

			// checks if each of the four corners are in the shape
			bool pin1 = incirc(a, sqrradius, px1);
			bool pin2 = incirc(a, sqrradius, px2);
			bool pin3 = incirc(a, sqrradius, px3);
			bool pin4 = incirc(a, sqrradius, px4);

			bool allin = pin1 && pin2 && pin3 && pin4;
			bool partin = pin1 || pin2 || pin3 || pin4;

			// if no point is in the shape we need to assure that
			// also the shape is not in the pixel box
			// the test for a circle that intersects the box is omitted for speed (very little quality loss)
			if(!partin) partin = a.x > px1.x && a.x < px3.x && a.y > px1.y && a.y < px3.y;

			// interpolated color for opacity
			array<double> interp;
			// pixel coverage accumulator 0.0 - 1.0
			double cover = 0.0;

			if(allin) {
				if(opacity == 1.) im.col(y, x) = col;
				else {
					interp = cast<double>(im.col(y, x));
					interp *= (double(1.) - opacity);
					interp += colord * opacity;

					im.col(y, x) = cast<T>(interp);
				}
			} else if(partin) { // AA
				interp = cast<double>(im.col(y, x));

				px1.x += pixeladd;
				px1.y += pixeladd;

				for(i = 0; i < multisample; i++) {

					for(j = 0; j < multisample; j++) {
						// tests a grid of (multisample x multisample) points
						// in the pixel box and counts how many are in the shape
						if(incirc(a, sqrradius, px1)) cover += coveradd;

						px1.x += pixeladd;
					}
					px1.x = px2.x + pixeladd;
					px1.y += pixeladd;
				}

				// perform transparency with cover as a parameter
				interp *= (double(1.) - cover);
				interp += colord * cover;

				im.col(y, x) = cast<T>(interp);
			}
		}
	}
}


template <class T, class D>
void AA_circle_impl(image<T, D>& im, double_point<2> a, double outradius, double inradius, color<T, D::Ch> col, int multisample = 8, double opacity = 1.)
{
	// bounding box
	int y0 = int(a.y - outradius) - 1;
	int x0 = int(a.x - outradius) - 1;
	int y1 = int(a.y + outradius) + 1;
	int x1 = int(a.x + outradius) + 1;

	// clipping!
	y0 = std::max(y0, 0);
	x0 = std::max(x0, 0);
	y1 = std::min(y1, int(im.rows() - 1));
	x1 = std::min(x1, int(im.cols() - 1));

	double outsqrradius = outradius * outradius;
	double insqrradius = inradius * inradius;

	// for multisampling
	double coveradd = opacity / double(multisample * multisample);
	double pixeladd = 1. / double(multisample + 1);

	// the color, in array format due to incompatibility issues. TODO: fix
	array<double> colord = cast<double>(col);

	int y, x, i, j;

	for(y = y0; y < y1; y++) {

		for(x = x0; x < x1; x++) {

			// the four corners that enclose the pixel
			double_point<2> px1(double(y) - .5, double(x) - .5);
			double_point<2> px2(double(y) + .5, double(x) - .5);
			double_point<2> px3(double(y) + .5, double(x) + .5);
			double_point<2> px4(double(y) - .5, double(x) + .5);

			// checks if each of the four corners are in the shape
			bool pin1 = incirc(a, outsqrradius, px1);
			bool pin2 = incirc(a, outsqrradius, px2);
			bool pin3 = incirc(a, outsqrradius, px3);
			bool pin4 = incirc(a, outsqrradius, px4);

			bool allin = pin1 && pin2 && pin3 && pin4;
			bool partin = pin1 || pin2 || pin3 || pin4;

			// if no point is in the shape we need to assure that
			// also the shape is not in the pixel box
			// the test for a circle that intersects the box is omitted for speed (very little quality loss)
			if(!partin) partin = a.x > px1.x && a.x < px3.x && a.y > px1.y && a.y < px3.y;
			else {
				pin1 = incirc(a, insqrradius, px1);
				pin2 = incirc(a, insqrradius, px2);
				pin3 = incirc(a, insqrradius, px3);
				pin4 = incirc(a, insqrradius, px4);
				if(pin1 || pin2 || pin3 || pin4) allin = false;
				if(pin1 && pin2 && pin3 && pin4) partin = false;
			}

			// interpolated color for opacity
			array<double> interp;
			// pixel coverage accumulator 0.0 - 1.0
			double cover = 0.0;

			if(allin) {
				if(opacity == 1.) im.col(y, x) = col;
				else {
					interp = cast<double>(im.col(y, x));
					interp *= (double(1.) - opacity);
					interp += colord * opacity;

					im.col(y, x) = cast<T>(interp);
				}
			} else if(partin) { // AA
				interp = cast<double>(im.col(y, x));

				px1.x += pixeladd;
				px1.y += pixeladd;

				for(i = 0; i < multisample; i++) {

					for(j = 0; j < multisample; j++) {
						// tests a grid of (multisample x multisample) points
						// in the pixel box and counts how many are in the shape
						if(incirc(a, outsqrradius, px1) && !incirc(a, insqrradius, px1)) cover += coveradd;

						px1.x += pixeladd;
					}
					px1.x = px2.x + pixeladd;
					px1.y += pixeladd;
				}

				// perform transparency with cover as a parameter
				interp *= (double(1.) - cover);
				interp += colord * cover;

				im.col(y, x) = cast<T>(interp);
			}
		}
	}
}

template <class T, class D>
void AA_fillellipse_impl(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, color<T, D::Ch> col, int multisample = 8, double opacity = 1.)
{
	// bounding box
	int y0 = int(std::min(a.y, b.y) - radius) - 1;
	int x0 = int(std::min(a.x, b.x) - radius) - 1;
	int y1 = int(std::max(a.y, b.y) + radius) + 1;
	int x1 = int(std::max(a.x, b.x) + radius) + 1;

	// clipping!
	y0 = std::max(y0, 0);
	x0 = std::max(x0, 0);
	y1 = std::min(y1, int(im.rows() - 1));
	x1 = std::min(x1, int(im.cols() - 1));

	double sqrradius = radius * radius;

	// for multisampling
	double coveradd = opacity / double(multisample * multisample);
	double pixeladd = 1. / double(multisample + 1);

	// the color, in array format due to incompatibility issues. TODO: fix
	array<double> colord = cast<double>(col);

	int y, x, i, j;

	for(y = y0; y < y1; y++) {

		for(x = x0; x < x1; x++) {

			// the four corners that enclose the pixel
			double_point<2> px1(double(y) - .5, double(x) - .5);
			double_point<2> px2(double(y) + .5, double(x) - .5);
			double_point<2> px3(double(y) + .5, double(x) + .5);
			double_point<2> px4(double(y) - .5, double(x) + .5);

			// checks if each of the four corners are in the shape
			bool pin1 = inellipse(a, b, sqrradius, px1);
			bool pin2 = inellipse(a, b, sqrradius, px2);
			bool pin3 = inellipse(a, b, sqrradius, px3);
			bool pin4 = inellipse(a, b, sqrradius, px4);

			bool allin = pin1 && pin2 && pin3 && pin4;
			bool partin = pin1 || pin2 || pin3 || pin4;

			// if no point is in the shape we need to assure that
			// also the shape is not in the pixel box
			// the test for a circle that intersects the box is omitted for speed (very little quality loss)
			if(!partin) partin = a.x > px1.x && a.x < px3.x && a.y > px1.y && a.y < px3.y;

			// interpolated color for opacity
			array<double> interp;
			// pixel coverage accumulator 0.0 - 1.0
			double cover = 0.0;

			if(allin) {
				if(opacity == 1.) im.col(y, x) = col;
				else {
					interp = cast<double>(im.col(y, x));
					interp *= (double(1.) - opacity);
					interp += colord * opacity;

					im.col(y, x) = cast<T>(interp);
				}
			} else if(partin) { // AA
				interp = cast<double>(im.col(y, x));

				px1.x += pixeladd;
				px1.y += pixeladd;

				for(i = 0; i < multisample; i++) {

					for(j = 0; j < multisample; j++) {
						// tests a grid of (multisample x multisample) points
						// in the pixel box and counts how many are in the shape
						if(inellipse(a, b, sqrradius, px1)) cover += coveradd;

						px1.x += pixeladd;
					}
					px1.x = px2.x + pixeladd;
					px1.y += pixeladd;
				}

				// perform transparency with cover as a parameter
				interp *= (double(1.) - cover);
				interp += colord * cover;

				im.col(y, x) = cast<T>(interp);
			}
		}
	}
}


template <class T, class D>
void AA_ellipse_impl(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, double thickness, color<T, D::Ch> col, int multisample = 8, double opacity = 1.)
{
	// bounding box
	int y0 = int(std::min(a.y, b.y) - radius) - 1;
	int x0 = int(std::min(a.x, b.x) - radius) - 1;
	int y1 = int(std::max(a.y, b.y) + radius) + 1;
	int x1 = int(std::max(a.x, b.x) + radius) + 1;

	double sqrradius = radius * radius;

	// clipping!
	y0 = std::max(y0, 0);
	x0 = std::max(x0, 0);
	y1 = std::min(y1, int(im.rows() - 1));
	x1 = std::min(x1, int(im.cols() - 1));

	// for multisampling
	double coveradd = opacity / double(multisample * multisample);
	double pixeladd = 1. / double(multisample + 1);

	// the color, in array format due to incompatibility issues. TODO: fix
	array<double> colord = cast<double>(col);

	int y, x, i, j;

	for(y = y0; y < y1; y++) {

		for(x = x0; x < x1; x++) {

			// the four corners that enclose the pixel
			double_point<2> px1(double(y) - .5, double(x) - .5);
			double_point<2> px2(double(y) + .5, double(x) - .5);
			double_point<2> px3(double(y) + .5, double(x) + .5);
			double_point<2> px4(double(y) - .5, double(x) + .5);

			// checks if each of the four corners are in the shape
			bool pin1 = inellipse2(a, b, sqrradius, -thickness, px1);
			bool pin2 = inellipse2(a, b, sqrradius, -thickness, px2);
			bool pin3 = inellipse2(a, b, sqrradius, -thickness, px3);
			bool pin4 = inellipse2(a, b, sqrradius, -thickness, px4);

			bool allin = pin1 && pin2 && pin3 && pin4;
			bool partin = pin1 || pin2 || pin3 || pin4;

			// if no point is in the shape we need to assure that
			// also the shape is not in the pixel box
			// the test for a circle that intersects the box is omitted for speed (very little quality loss)
			if(!partin) partin = a.x > px1.x && a.x < px3.x && a.y > px1.y && a.y < px3.y;
			else {
				pin1 = inellipse2(a, b, sqrradius, thickness, px1);
				pin2 = inellipse2(a, b, sqrradius, thickness, px2);
				pin3 = inellipse2(a, b, sqrradius, thickness, px3);
				pin4 = inellipse2(a, b, sqrradius, thickness, px4);
				if(pin1 || pin2 || pin3 || pin4) allin = false;
				if(pin1 && pin2 && pin3 && pin4) partin = false;
			}

			// interpolated color for opacity
			array<double> interp;
			// pixel coverage accumulator 0.0 - 1.0
			double cover = 0.0;

			if(allin) {
				if(opacity == 1.) im.col(y, x) = col;
				else {
					interp = cast<double>(im.col(y, x));
					interp *= (double(1.) - opacity);
					interp += colord * opacity;

					im.col(y, x) = cast<T>(interp);
				}
			} else if(partin) { // AA
				interp = cast<double>(im.col(y, x));

				px1.x += pixeladd;
				px1.y += pixeladd;

				for(i = 0; i < multisample; i++) {

					for(j = 0; j < multisample; j++) {
						// tests a grid of (multisample x multisample) points
						// in the pixel box and counts how many are in the shape
						if(inellipse2(a, b, sqrradius, -thickness, px1) && !inellipse2(a, b, sqrradius, thickness, px1)) cover += coveradd;

						px1.x += pixeladd;
					}
					px1.x = px2.x + pixeladd;
					px1.y += pixeladd;
				}

				// perform transparency with cover as a parameter
				interp *= (double(1.) - cover);
				interp += colord * cover;

				im.col(y, x) = cast<T>(interp);
			}
		}
	}
}


};//namespace image_details

template <class T, class D>
void AA_trig_artsy(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, color<T, D::Ch> col, int multisample, double opacity)
{
	image_details::AA_trig_artsy_impl(im, a, b, c, col, multisample, opacity);
}

template <class T, class D>
void AA_trig(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, color<T, D::Ch> col, int multisample, double opacity)
{
	image_details::AA_trig_impl(im, a, b, c, col, multisample, opacity);
}

template <class T, class D>
void AA_quad(image<T, D>& im, double_point<2> a, double_point<2> b, double_point<2> c, double_point<2> d,
    color<T, D::Ch> col, int multisample, double opacity)
{
	image_details::AA_quad_impl(im, a, b, c, d, col, multisample, opacity);
}

template <class T, class D>
void AA_circ(image<T, D>& im, double_point<2> a, double radius, color<T, D::Ch> col, int multisample, double opacity)
{
	image_details::AA_circ_impl(im, a, radius, col, multisample, opacity);
}

template <class T, class D>
void AA_circle(image<T, D>& im, double_point<2> a, double outradius, double inradius, color<T, D::Ch> col, int multisample, double opacity)
{
	image_details::AA_circle_impl(im, a, outradius, inradius, col, multisample, opacity);
}

template <class T, class D>
void AA_fillellipse(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, color<T, D::Ch> col, int multisample, double opacity)
{
	image_details::AA_fillellipse_impl(im, a, b, radius, col, multisample, opacity);
}

template <class T, class D>
void AA_ellipse(image<T, D>& im, double_point<2> a, double_point<2> b, double radius, double thickness, color<T, D::Ch> col, int multisample, double opacity)
{
	image_details::AA_ellipse_impl(im, a, b, radius, thickness, col, multisample, opacity);
}

};//namespace ivl

#endif // IVL_IMAGE_DETAILS_FUNCTIONS_AA_DRAWING_FUNCTIONS_HPP
