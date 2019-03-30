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


//--------------------------------------------------------------
// CLASS image

namespace data {

template <class HAS_RANDOM_ACCESS, class IS_2D>
struct get_pixel { };

template <>
struct get_pixel<types::t_true, types::t_false>
{
	template<class A>
	static inline
	typename A::pixel from(A& a, size_t row, size_t col)
	{
		return typename A::pixel(
			a._iter(2, a.begin() + (col * a.rows() + row)), a.channels());
	}
	template<class A>
	static inline
	typename A::const_pixel from(const A& a, size_t row, size_t col)
	{
		return typename A::const_pixel(
			a._iter(2, a.begin() + (col * a.rows() + row)), a.channels());
	}
};

template <>
struct get_pixel<types::t_false, types::t_false>
{
	template<class A>
	static inline
	typename A::pixel from(A& a, size_t row, size_t col)
	{
		return typename A::pixel(
			a._iter(2,
				array<size_t, data::fixed<2> >(row, col)), a.channels());
	}
	template<class A>
	static inline
	typename A::const_pixel from(const A& a, size_t row, size_t col)
	{
		return typename A::const_pixel(
			a._iter(2,
				array<size_t, data::fixed<2> >(row, col)), a.channels());
	}
	/*
	typename A::pixel from(A& a, size_t row, size_t col)
	{
		return typename A::pixel(a._iter(2, a._begin(0) + row, col));
	}
	template<class A>
	static inline
	typename A::const_pixel from(const A& a, size_t row, size_t col)
	{
		return typename A::const_pixel(a._iter(2, a._begin(0) + row, col));
	}
	*/
};

template <class ANY>
struct get_pixel<ANY, types::t_true>
{
	template<class A>
	static inline
	typename A::pixel from(A& a, size_t row, size_t col)
	{
		return a(row, col);
	}
	template<class A>
	static inline
	typename A::const_pixel from(const A& a, size_t row, size_t col)
	{
		return a(row, col);
	}
};


} /* namespace data */

/**
 * \brief A single or multi channel image of type T based on %array
 *
 * This class defines an image based on an %array.
 */
template <class T,
		 class OPTS = data::normal_image<0>
	     >
class image :
	public
		array_common_base<image<T, OPTS> >
{
private:
	typedef array_common_base<image<T, OPTS> > common_base_class;

	using common_base_class::Ch;
	enum { N = common_base_class::im_channels::value };

	typedef typename image_details::cv<true, T>::iplimage_t iplimage_t;

	void copy_from(const iplimage_t* src)
	{
		image_details::cv<true, T>::copy_from(*this, src);
	}

	void copy_to(iplimage_t* ipl) const
	{
		image_details::cv<true, T>::copy_to(*this, ipl);
	}

public:
	typedef image this_type;

	typedef typename this_type::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	typedef this_type this_image_type;

	typedef this_type array_type;

	typedef typename this_type::size_type size_type;

	using base_class::derived;

	typedef typename this_type::all_init_arg_base all_init_arg;
	typedef typename this_type::data_init_arg_base data_init_arg;


// image types
	typedef typename types::best_iterator<base_class>::type best_iterator;
	typedef typename base_class::const_iterator const_iterator;

	typedef typename types::best_iterator_nd<base_class>::type best_iterator_nd;
	typedef typename base_class::const_iterator_nd const_iterator_nd;

	//! const pixel type
	typedef typename types::t_if<types::t_expr<N != 1>,
		array<T,
			data::ref_iterator<const_iterator_nd, types::term, N> >,
		typename const_iterator::reference>::type
			const_pixel;

	typedef typename types::t_if<types::t_expr<N != 1>,
		array<T,
			data::ref_iterator<best_iterator_nd, const_iterator_nd, N> >,
		typename best_iterator::reference>::type pixel;

	//! color type
	typedef ivl::color<T, OPTS::Ch> color_type;

/**@name Constructors
@{*/
	//! Default constructor. always assign at least 1 channel to the image
	image() : common_base_class(size_dims<3>(0, 0, (!N ? 1 : N))) { }

	//! Create an empty image
	image(size_t rows, size_t cols, size_t channels = (!N ? 3 : N)) :
		common_base_class(size_dims<3>(rows, cols, channels))
		{ CHECK(!N || channels == N, edims); }

	//! Create an image with initial value
	image(size_t rows, size_t cols, size_t channels, const T& value) :
		common_base_class(size_dims<3>(rows, cols, channels), value)
		{ CHECK(!N || channels == N, edims); }

	//! Create an image with size and pointer to data
	/*image(size_t rows, size_t cols, size_t channels, const T* ptr) :
		common_base_class(size_dims<3>(rows, cols, channels), ptr)
		{ CHECK(!N || channels == N, edims); }*/

	//! Create an empty image with similar initial value or array
	template <class J, class D>
	image(size_t rows, size_t cols, size_t channels, const array<J, D>& a) :
		common_base_class(size_dims<3>(rows, cols, channels), a)
		{ CHECK(!N || channels == N, edims); }

	//! Create an image with size array
	template <class S>
	image(const array<size_t, S>& sz) :
		common_base_class(sz) {}

	//! Create an image with size array and initial value
	template <class S>
	image(const array<size_t, S>& sz, const T& value) :
		common_base_class(sz, value) {}

	//! Create an image with size array and pointer to data
	template <class S>
	image(const array<size_t, S>& sz, const T* ptr) :
		common_base_class(sz, ptr) {}

	//! Create an image with size array and a data_init_arg
	template <class S>
	image(const array<size_t, S>& sz, const data_init_arg& data) :
		common_base_class(sz, data) {}


	//! Create an image with size array and ivl::array or value
	template <class S, class J, class D>
	image(const array<size_t, S>& sz, const array<J, D>& a) :
		common_base_class(sz, a) {}

	//! Create an image from filename
	image(const std::string& filename, image_channels channels = ic_auto);

	//! Create an image from an IplImage
	image(const iplimage_t* ipl);

	//! Construct from array_nd
	template <class J, class S>
	image(const array_nd<J, S>& a) : common_base_class(a) {}

	//! (special for ref_iterator) Construct from array_nd
	template <class J, class S>
	image(array_nd<J, S>& a) : common_base_class(a) {}

	//! Copy constructor
	image(const this_type& a) : common_base_class(a) {}

/**@}*/

	// Destructor
	~image() {}


/**@name Assignment operators
@{*/
	//using common_base_class::operator=;
	template<class K>
	derived_type& operator=(const K& k)
	{ common_base_class::operator=(k); return derived(); }

	this_type& operator=(const this_type& a) // copy operator
	{ common_base_class::operator=(a); return *this; }

	//! assign from an OpenCV IplImage
	derived_type& operator=(const iplimage_t* src)
	{ copy_from(src); return this->derived(); }
	//! assign from an OpenCV IplImage
	// sorry, but that's the effect of free template argument
	derived_type& operator=(iplimage_t* src)
		{ return ((*this) = static_cast<const iplimage_t*>(src)); }
/*
	//! assign from a single element. creates 1 x 1 pixel x 1 channel image
	derived_type& operator=(const T& s)
		{ return base_class::operator=(s); };

	//! assign from array_nd (overrides the default behaviour, adds dims check)
	template<class S, class K>
	derived_type& operator=(const array_nd<T, S, K>& a)  { return base_class::operator=(a); }

	//! assign from other type image (needed?)
	template<int M, class S, class K>
	derived_type& operator=(const image<T, M, S, K>& a) { return base_class::operator=(a); }

	//! assign from image of the same type
 	this_type& operator=(const this_type& a) { return base_class::operator=(a); }
*/

/**@}*/


	// Member Accessors
	using base_class::size_nd;
	//! image rows
	size_t rows() const { return size_nd()[0]; }
	//! image columns
	size_t cols() const { return size_nd()[1]; }
	//! color channels
	size_t channels() const
		{ return data::get_channels<N>::from(this->size_nd()); }

	//! image width. same as columns
	size_t width() const { return cols(); }
	//! image height. same as rows
	size_t height() const { return rows(); }

	//! const pixel access
	inline const_pixel col(size_t row, size_t col) const
	{
		return data::get_pixel<
			typename this_type::data_type::has_random_access,
			typename types::t_expr<N == 1>::type>::
			from(*this, row, col);
	}
	//! pixel access
	inline pixel col(size_t row, size_t col)
	{
		return data::get_pixel<
			typename this_type::data_type::has_random_access,
			typename types::t_expr<N == 1>::type>::
			from(*this, row, col);
	}
	//! const pixel from iterator
	inline const_pixel col(const const_iterator& it) const { return pixel(it); }

	//! pixel from iterator
	inline pixel col(const best_iterator& it) { return pixel(it); }

	//! predefined colors
	color_type black() const
		{ return color_type(channels(), colors::color_values<T>::min()); }
	color_type white() const
		{ return color_type(channels(), colors::color_values<T>::max()); }

	//! Conversion to IplImage
	iplimage_t* ipl() const
	{
		return image_details::cv<true, T>::ipl(*this);
	}

	// OpenCV functions
	void load(const std::string& filename, image_channels channels = ic_auto)
	{
		image_details::cv<true, T>::load(*this, filename, channels);
	}
	void save(const std::string& filename) const
	{
		image_details::cv<true, T>::save(*this, filename);
	}

	// Image processing functions

/**@name Basic plotting (not fast implementations)
@{*/
	//! Draws a single pixel
	derived_type& put_pixel(double_point<2> a, color_type col
	  = ivl::colors::white<T>(colors::color_type<T, ivl::colors::rgb>()))
	  { this->col(a.y, a.x) = col; return this->derived(); }

	//! Retrieves the color of a single pixel
	color_type get_pixel(double_point<2> a) { return this->col(a.y, a.x); }

	//! Draws line from \e a => \e b, using the given color, thickness and opacity. anti-aliasing is performed
	derived_type& line(double_point<2> a, double_point<2> b, color_type col = ivl::colors::white<T>(colors::color_type<T, ivl::colors::rgb>()), double thickness = 1.5, double opacity = 1.)
	{ line_on(*this, a, b, col, thickness, opacity); return this->derived(); }
	//! Draws circle on \e a with given \e radius, using the given color, thickness and opacity. anti-aliasing is performed
	derived_type& circle(double_point<2> a, double radius, color_type col = ivl::colors::white<T>(colors::color_type<T, ivl::colors::rgb>()), double thickness = 1.5, double opacity = 1.)
	{ return circle_on(*this, a, radius, col, thickness, opacity); }
	//! Draws a rectangle from corner \e a to corner \e b, using the given color, thickness and opacity. anti-aliasing is performed
	derived_type& rect(double_point<2> a, double_point<2> b, color_type col = ivl::colors::white<T>(colors::color_type<T, ivl::colors::rgb>()), double thickness = 1.5, double opacity = 1.)
	{ return rect_on(*this, a, b, col, thickness, opacity); }
	//! Draws an ellipse using centers \a and \b and total radius \e radius, using the given color, thickness and opacity. anti-aliasing is performed
	derived_type& ellipse(double_point<2> a, double_point<2> b, double radius, color_type col = ivl::colors::white<T>(colors::color_type<T, ivl::colors::rgb>()), double thickness = 1.5, double opacity = 1.)
	{ return ellipse_on(*this, a, b, radius, col, thickness, opacity); }
	//! Draws an ellipse using center \a, a given \angle and \e radius1, \e radius2 of the two axis, horizontal and vertical.
	//! using the given color, thickness and opacity. anti-aliasing is performed
	derived_type& ellipse(double_point<2> c, double radius1, double radius2, double angle, color_type col = ivl::colors::white<T>(colors::color_type<T, ivl::colors::rgb>()), double thickness = 1.5, double opacity = 1.)
	{ return ellipse_on(*this, c, radius1, radius2, angle, col, thickness, opacity); }

	derived_type& fill_circle(double_point<2> a, double radius, color_type col = ivl::colors::white<T>(colors::color_type<T, ivl::colors::rgb>()), double opacity = 1.)
	{ return fill_circle_on(*this, a, radius, col, opacity); }
	//! Fills circle on \e a with given \e radius, using the given color and opacity. anti-aliasing is performed
	derived_type& fill_rect(double_point<2> a, double_point<2> b, color_type col = ivl::colors::white(ivl::colors::color_type<T, colors::rgb>()), double opacity = 1.)
	{ return fill_rect_on(*this, a, b, col, opacity); }
	//! Fills an ellipse using centers \a and \b and total radius \e radius, using the given color and opacity. anti-aliasing is performed
	derived_type& fill_ellipse(double_point<2> a, double_point<2> b, double radius, color_type col = ivl::colors::white(ivl::colors::color_type<T, colors::rgb>()), double opacity = 1.)
	{ return fill_ellipse_on(*this, a, b, radius, col, opacity); }
	//! Fills an ellipse using center \a, a given \angle and \e radius1, \e radius2 of the two axis, horizontal and vertical.
	//! using the given color and opacity. anti-aliasing is performed
	derived_type& fill_ellipse(double_point<2> c, double radius1, double radius2, double angle, color_type col = ivl::colors::white(ivl::colors::color_type<T, colors::rgb>()), double opacity = 1.)
	{ return fill_ellipse_on(*this, c, radius1, radius2, angle, col, opacity); }
	//! Fills a triangle (\e a, \e b, \e c) using the given color and opacity. anti-aliasing is performed
	derived_type& fill_triangle(double_point<2> a, double_point<2> b, double_point<2> c, color_type col = ivl::colors::white(ivl::colors::color_type<T, colors::rgb>()), double opacity = 1.)
	{ return fill_triangle_on(*this, a, b, c, col, opacity); }
	//! Fills a quad (\e a, \e b, \e c, \e d) using the given color and opacity. anti-aliasing is performed
	derived_type& fill_quad(double_point<2> a, double_point<2> b, double_point<2> c, double_point<2> d, color_type col = ivl::colors::white(ivl::colors::color_type<T, colors::rgb>()), double opacity = 1.)
	{ return fill_quad_on(*this, a, b, c, d, col, opacity); }
/**@}*/

};

