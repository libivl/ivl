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

#ifndef IVL_ARRAY_DETAILS_TUPLE_HPP
#define IVL_ARRAY_DETAILS_TUPLE_HPP

namespace ivl {

template <class T, int N>
class fixed_array : public array<T, data::fixed<N, types::term> >
{
public:
	typedef fixed_array<T, N> this_type;
	typedef array<T, data::fixed<N, types::term> > base_class;

	fixed_array() { }

	fixed_array(const T* data) : base_class(data) { }

	fixed_array(const T& s) : base_class(N, s) { }

	fixed_array(const this_type& t) : base_class(t) { }

	template <class S>
	fixed_array(const array<T, S>& a) : base_class(a) { }

	fixed_array& operator=(const fixed_array<T, N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	fixed_array& operator=(const array<T, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <class T, int N = 2>
class point : public array<T, fixed<N, data::point_naming> >
{
public:
	typedef point<T, N> this_type;
	typedef array<T, fixed<N, data::point_naming> > base_class;

	point() { }

	point(const T* data) : base_class(data) { }

	point(const T& s) : base_class(N, s) { }

	point(const this_type& t) : base_class(t) { }

	template <class S>
	point(const array<T, S>& a) : base_class(a) { }

	point(T y, T x,
		typename types::t_if<types::t_expr<N == 2>, types::skip, T>::type z = 0)
	{
		(*this)[0] = y;
		(*this)[1] = x;
		types::r_if<types::t_expr<N == 2> >(types::skip(), (*this)[N - 1]) = z;
	}

	point& operator=(const point<T, N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	point& operator=(const array<T, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <class T, int N = 2>
class dims : public array<T, fixed<N, data::dims_naming> >
{
public:
	typedef point<T, N> this_type;
	typedef array<T, fixed<N, data::dims_naming> > base_class;

	dims() { }

	dims(const T* data) : base_class(data) { }

	dims(const T& s) : base_class(N, s) { }

	dims(const this_type& t) : base_class(t) { }

	template <class S>
	dims(const array<T, S>& a) : base_class(a) { }

	dims(T h, T w,
		typename types::t_if<types::t_expr<N == 2>, types::skip, T>::type d = 0)
	{
		(*this)[0] = h;
		(*this)[1] = w;
		types::r_if<types::t_expr<N == 2> >(types::skip(), (*this)[N - 1]) = d;
	}

	dims& operator=(const dims<T, N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	dims& operator=(const array<T, S>& o)
	{ base_class::operator=(o); return *this; }
};

// specializations for point

template <int N>
class int_point : public point<int, N>
{
public:
	typedef int_point this_type;

	typedef point<int, N> base_class;

	int_point() { }

	int_point(const int* data) : base_class(data) { }

	int_point(const int& s) : base_class(s) { }

	int_point(const this_type& t) : base_class(t) { }

	int_point(const typename this_type::array_type& a) : base_class(a) { }

	int_point(int y, int x, int z = 0) : base_class(y, x, z) { }

	int_point& operator=(const int_point<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	int_point& operator=(const array<int, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <int N>
class size_point : public point<size_t, N>
{
public:
	typedef size_point this_type;

	typedef point<size_t, N> base_class;

	size_point() { }

	size_point(const size_t* data) : base_class(data) { }

	size_point(const size_t& s) : base_class(s) { }

	size_point(const this_type& t) : base_class(t) { }

	size_point(const typename this_type::array_type& a) : base_class(a) { }

	size_point(size_t y, size_t x, size_t z = 0) : base_class(y, x, z) { }

	size_point& operator=(const size_point<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	size_point& operator=(const array<size_t, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <int N>
class float_point : public point<float, N>
{
public:
	typedef float_point this_type;

	typedef point<float, N> base_class;

	float_point() { }

	float_point(const float* data) : base_class(data) { }

	float_point(const float& s) : base_class(s) { }

	float_point(const this_type& t) : base_class(t) { }

	float_point(const typename this_type::array_type& a) : base_class(a) { }

	float_point(float y, float x, float z = 0) : base_class(y, x, z) { }

	float_point& operator=(const float_point<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	float_point& operator=(const array<float, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <int N>
class double_point : public point<double, N>
{
public:
	typedef double_point this_type;

	typedef point<double, N> base_class;

	double_point() { }

	double_point(const double* data) : base_class(data) { }

	double_point(const double& s) : base_class(s) { }

	double_point(const this_type& t) : base_class(t) { }

	double_point(const typename this_type::array_type& a) : base_class(a) { }

	double_point(double y, double x, double z = 0) : base_class(y, x, z) { }

	double_point& operator=(const double_point<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	double_point& operator=(const array<double, S>& o)
	{ base_class::operator=(o); return *this; }
};

// specializations for dims

template <int N>
class int_dims : public dims<int, N>
{
public:
	typedef int_dims this_type;

	typedef dims<int, N> base_class;

	int_dims() { }

	int_dims(const int* data) : base_class(data) { }

	int_dims(const int& s) : base_class(s) { }

	int_dims(const this_type& t) : base_class(t) { }

	int_dims(const typename this_type::array_type& a) : base_class(a) { }

	int_dims(int h, int w, int d = 0) : base_class(h, w, d) { }

	int_dims& operator=(const int_dims<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	int_dims& operator=(const array<int, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <int N>
class size_dims : public dims<size_t, N>
{
public:
	typedef size_dims this_type;

	typedef dims<size_t, N> base_class;

	size_dims() { }

	size_dims(const size_t* data) : base_class(data) { }

	size_dims(const size_t& s) : base_class(s) { }

	size_dims(const this_type& t) : base_class(t) { }

	size_dims(const typename this_type::array_type& a) : base_class(a) { }

	size_dims(size_t h, size_t w, size_t d = 0) : base_class(h, w, d) { }

	size_dims& operator=(const size_dims<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	size_dims& operator=(const array<size_t, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <int N>
class float_dims : public dims<float, N>
{
public:
	typedef float_dims this_type;

	typedef dims<float, N> base_class;

	float_dims() { }

	float_dims(const float* data) : base_class(data) { }

	float_dims(const float& s) : base_class(s) { }

	float_dims(const this_type& t) : base_class(t) { }

	float_dims(const typename this_type::array_type& a) : base_class(a) { }

	float_dims(float h, float w, float d = 0) : base_class(h, w, d) { }

	float_dims& operator=(const float_dims<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	float_dims& operator=(const array<float, S>& o)
	{ base_class::operator=(o); return *this; }
};

template <int N>
class double_dims : public dims<double, N>
{
public:
	typedef double_dims this_type;

	typedef dims<double, N> base_class;

	double_dims() { }

	double_dims(const double* data) : base_class(data) { }

	double_dims(const double& s) : base_class(s) { }

	double_dims(const this_type& t) : base_class(t) { }

	double_dims(const typename this_type::array_type& a) : base_class(a) { }

	double_dims(double h, double w, double d = 0) : base_class(h, w, d) { }

	double_dims& operator=(const double_dims<N>& o)
	{ base_class::operator=(o); return *this; }

	template<class S>
	double_dims& operator=(const array<double, S>& o)
	{ base_class::operator=(o); return *this; }
};


/*
template <class T>
class singleton : public fixed_array<T, 1>
{
public:
	typedef singleton this_type;
	typedef fixed_array<T, 1> base_class;

	singleton() { }

	singleton(const T* data) : base_class(data) { }

	singleton(const T& s) : base_class(s) { }

	singleton(const this_type& a) : base_class(a) {}

	template<class S> inline
	explicit singleton(const array<T, S>& a) : base_class(a) { }

	using base_class::operator=;

	this_type& operator=(const this_type& o){ return base_class::operator=(o); }
};

template <class T>
class pair : public fixed_array<T, 2>
{
public:
	typedef pair this_type;
	typedef fixed_array<T, 2> base_class;

	pair() { }

	pair(const T* data) : base_class(data) { }

	pair(const T& s) : base_class(s) { }

	pair(const T& s0, const T& s1) { (*this)[0] = s0; (*this)[1] = s1; }

	pair(const this_type& a) : base_class(a) {}

	// this constructor is explicit, because pair is a type
	// that needs to be matched exactly to provide type-correctness.
	template<class S> inline
	explicit pair(const array<T, S>& a) : base_class(a) { }

	using base_class::operator=;

	this_type& operator=(const this_type& o){ return base_class::operator=(o); }

	//const T& x() const { return (*this)[0]; }
	//T& x() { return (*this)[0]; }

	//const T& y() const { return (*this)[1]; }
	//T& y() { return (*this)[1]; }
};

template <class T>
class triplet : public fixed_array<T, 3>
{
public:
	typedef triplet <T> this_type;
	typedef fixed_array<T, 3> base_class;

	triplet() { }

	triplet(const T* data) : base_class(data) { }

	triplet(const T& s) : base_class(s) { }

	triplet(const T& s0, const T& s1, const T& s2)
		{ (*this)[0] = s0; (*this)[1] = s1; (*this)[2] = s2; }

	triplet(const this_type& a) : base_class(a) { }

	template<class S> inline
	explicit triplet(const array<T, S>& a) : base_class(a) { }

	using base_class::operator=;

	this_type& operator=(const this_type& o){ return base_class::operator=(o); }

	//const T& x() const { return (*this)[0]; }
	//T& x() { return (*this)[0]; }

	//const T& y() const { return (*this)[1]; }
	//T& y() { return (*this)[1]; }

	//const T& z() const { return (*this)[2]; }
	//T& z() { return (*this)[2]; }

};


typedef pair<size_t> size_pair;

typedef triplet<size_t> size_triplet;
*/



/*
template <class T>
point<T, 2> pnt(const T& x, const T& y)
{
	return point<T, 2>(x, y);
}

template <class T>
point<T, 3> pnt(const T& x, const T& y, const T& z)
{
	return point<T, 3>(x, y, z);
}
*/

}; /*namespace ivl*/

#endif // IVL_ARRAY_DETAILS_TUPLE_HPP
