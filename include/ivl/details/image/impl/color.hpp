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

#ifndef IVL_IMAGE_DETAILS_COLOR_HPP
#define IVL_IMAGE_DETAILS_COLOR_HPP

namespace ivl {

namespace colors {
/*
enum color_space_type
{
	other = 0, rgb = 3, rgba = 4
};*/
struct other {};
struct rgb { enum channel_num { value = 3 }; };
struct rgba { enum channel_num { value = 4 }; };
template<int N>
struct defctype { enum channel_num { value = N }; };


namespace image_details {

//template <enum color_space_type C>
template <class C>
struct col_channels : public types::number<0> { };

template <>
struct col_channels<rgb> : public types::number<3> { };

template <>
struct col_channels<rgba> : public types::number<4> { };

} /* namespace image_details */

template<class T>
struct color_values { };

template<>
struct color_values<unsigned char> {
	static unsigned char min()	{ return 0; }
	static unsigned char max()	{ return 255; }
};

template<>
struct color_values<char> {
	static char min()	{ return -128; }
	static char max()	{ return 127; }
};

template<>
struct color_values<short> {
	static short min()	{ return 0; }
	static short max()	{ return 255; }
};

template<>
struct color_values<int> {
	static int min()	{ return 0; }
	static int max()	{ return 255; }
};

template<>
struct color_values<double> {
	static double min()	{ return 0.0; }
	static double max()	{ return 1.0; }
};

template<>
struct color_values<float> {
	static double min()	{ return 0.0; }
	static double max()	{ return 1.0; }
};


} /* namespace colors */

//! CLASS color
//! Defines the base n-channel color type
template<class T, int N = 0>
class color
: public
	types::t_if<types::t_expr<N != 0>,
		array<T, data::fixed<N, data::color_naming> >,
		array<T, tiny> >
	::type
{
private:
	class not_a_type { };

	template <int CHAN>
	struct disable_chan
	{
		typedef typename types::t_if<types::t_expr<(N > CHAN || N == 0)>,
			types::code_word<>, not_a_type>::type type;


	};

	typedef typename types::t_if<types::t_expr<(N == 0)>,
		types::code_word<>, not_a_type>::type disableifn;

	typedef typename types::t_if<types::t_expr<(N != 0)>,
		types::code_word<>, not_a_type>::type disableif0;

	template<int N0, int K>
	struct try_resize
	{
		try_resize(color& c)
		{
			CHECK(N == 0 || K == N, erange);
		}
	};
	template<int K>
	struct try_resize<0, K>
	{
		try_resize(color& c)
		{
			c.resize(K);
		}
	};

	template <class K>
	struct disableift
	{
		typedef typename types::t_if<types::t_eq<T, K>,
		not_a_type, types::code_word<> >::type type;
	};

protected:

public:
	typedef typename
	types::t_if<types::t_expr<N != 0>,
		array<T, data::fixed<N, data::color_naming> >,
		array<T, tiny> >
	::type base_class;

	/*used to be: types::t_if<types::t_expr<N != 0>,
		fixed_array<T, N>, array<T, data::little > >
	::type base_class;*/

	typedef color<T, N> this_type;

    static inline T min_val() { return colors::color_values<T>::min(); }
    static inline T max_val() { return colors::color_values<T>::max(); }

	color() { }

	color(T c0) { try_resize<N, 1>(*this); (*this)[0] = c0; }

	color(T c0, T c1) { try_resize<N, 2>(*this);
		(*this)[0] = c0; (*this)[1] = c1; }

	color(T c0, T c1, T c2) { try_resize<N, 3>(*this);
		(*this)[0] = c0; (*this)[1] = c1; (*this)[2] = c2; }

	color(T c0, T c1, T c2, T c3) { try_resize<N, 4>(*this);
		(*this)[0] = c0; (*this)[1] = c1; (*this)[2] = c2; (*this)[3] = c3; }


	explicit color(size_t count,
	typename disableift<size_t>::type = typename disableift<size_t>::type())
	: base_class(count) { }

	explicit color(int count,
	typename disableift<int>::type = typename disableift<int>::type())
	: base_class(count) { }

	explicit color(long int count,
	typename disableift<long int>::type = typename disableift<long int>::type())
	: base_class(count) { }

	color(size_t count, const T& s,
	typename disableift<size_t>::type = typename disableift<size_t>::type())
	: base_class(count, s) { }

	template <class D>
	color(const array<size_t, D>& size, const T& s)
	: base_class(size[0], s) { }

	color(size_t count, const T* s)
	: base_class(count, s) { }

	color(const this_type& c) : base_class(c) { }

	template<class S>
	color(const array<T, S>& a, size_t n) : base_class(a, n) { }

	template<class S>
	color(const array<T, S>& a) : base_class(a) { }

	template<class S>
	color(size_t count, const array<T, S>& a) : base_class(count, a) { }


	const T& val(typename disable_chan<0>::type =
		typename disable_chan<0>::type()) const
		{ return (*this)[0]; }

	T& val(typename disable_chan<0>::type =
		typename disable_chan<0>::type())
		{ return (*this)[0]; }

};

namespace colors {

template <class T, int N>
color<T, 4> rgb2rgba(const color<T, N>& c)
{
	color<T, 4> r;
	r[0] = c[0];
	r[1] = c[1];
	r[2] = c[2];
	r[3] = color<T, 4>::max_val();
	return r;
}

template <class T, int N>
color<T, 3> rgba2rgb(const color<T, N>& c)
{
	color<T, 3> r;
	r[0] = c[0];
	r[1] = c[1];
	r[2] = c[2];
	return r;
}

template <class T, class C>
struct color_type
{
	color_type() {}
	template<class X>
	color_type(const X& x) {}
};

/*
template <class T, enum color_space_type C>
inline
color<T, N> white()
{
	return color<T, N>(fixed_array<size_t, 1>(N == 0 ? 3 : N),
		color<T, N>::max_val());
}*/

template <class T, class C>
inline
color<T, int(image_details::col_channels<C>::value)> white(
	color_type<T, C> = 0)
{
	enum { n = image_details::col_channels<C>::value };
	return color<T, n>(fixed_array<size_t, 1>(n == 0 ? 3 : n),
		color<T, n>::max_val());
}

template <class T, class C>
inline
color<T, image_details::col_channels<C>::value> black(
	color_type<T, C> = 0)
{
	enum { n = image_details::col_channels<C>::value };
	return color<T, n>(fixed_array<size_t, 1>(n == 0 ? 3 : n),
		color<T, n>::min_val());
}


/*TODO: why broken?
template <class T, enum color_space_type C>
inline
color<T, int(image_details::col_channels<C>::value)> white(
	color_type<T, C> = 0)
{
	enum { n = image_details::col_channels<C>::value };
	return color<T, n>(fixed_array<size_t, 1>(n == 0 ? 3 : n),
		color<T, n>::max_val());
}

template <class T, enum color_space_type C>
inline
color<T, image_details::col_channels<C>::value> black(
	color_type<T, C> = 0)
{
	enum { n = image_details::col_channels<C>::value };
	return color<T, n>(fixed_array<size_t, 1>(n == 0 ? 3 : n),
		color<T, n>::min_val());
}
*/

} /* namespace colors */

} /* namespace ivl */

#endif // IVL_IMAGE_DETAILS_COLOR_HPP
