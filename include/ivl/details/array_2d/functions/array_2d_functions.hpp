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

#ifndef IVL_ARRAY_2D_DETAILS_ARRAY_2D_FUNCTIONS_HPP
#define IVL_ARRAY_2D_DETAILS_ARRAY_2D_FUNCTIONS_HPP


namespace ivl {


// TODO: this is not good :p
// TODO: put this somewhere!

// ----------
// concat

template<class T, class T2, class S2>
ivl::concat<
	//TODO: used to need const. investigate
	const typename core_details::matrix_based<T>::base_class,
	const array_2d<T2, S2>, 1> operator ,(
		const core_details::matrix_based<T>& l, const array_2d<T2, S2>& r)
{
	const array_2d<T2, S2>* ptr = &r;
	return reftpl(l.base(), ptr);
}

/*
todo: GREAT PROBLEMS
template<class T, class T2, class S2>
ivl::concat<
	//TODO: used to need const. investigate
	const typename core_details::matrix_based<T>::base_class,
	const array_2d<T2, S2>, 0> operator ,(
		const core_details::matrix_based<T>& l, const array_2d<T2, S2>* r)
{
	return reftpl(l.base(), r);
}
*/

template<class T, class T2, class S2>
inline
array_nd<typename core_details::matrix_based<T>::base_class::elem_type,
	data::catarray<
		const typename core_details::matrix_based<T>::base_class::base_class,
		const array_nd<T2, S2>, 1> > operator ,(
		const core_details::matrix_based<T>& l, const array_2d<T2, S2>* r)
{
	array_nd<typename core_details::matrix_based<T>::base_class::elem_type,
	data::catarray<
		const typename core_details::matrix_based<T>::base_class::base_class,
		const array_nd<T2, S2>, 1> > rv;
	const array_2d<T2, S2>* ptr = &r;
	rv.init(l, r);
	return rv;
}

// ---------

template<class T, class T2, class S2>
ret<array_2d<typename T::elem_type> > operator *(const core_details::matrix_based<T>& l,
											const array_2d<T2, S2>& r)
{
	return mtimes(l.t, r);
}

template<class T, class K>
core_details::matrix_based<array_2d<typename T::elem_type> > operator *(
	const core_details::matrix_based<T>& l, const core_details::matrix_based<K>& r)
{
	return mtimes(l.t, r.t);
}


//! flip matrix upside down
template <class T, class D>
inline
typename array_2d<T, D>::create_similar flipud(const array_2d<T, D>& a)
{ return flipdim(a, 0); }

//! flip matrix right to left
template <class T, class D>
inline
typename array_2d<T, D>::create_similar fliplr(const array_2d<T, D>& a)
{ return flipdim(a, 1); }

//! diagonal of the matrix
template <class T, class S>
inline
array<T> diag(const array_2d<T, S>& a, int k = 0)
{
	CHECK(size_t(std::abs(k)) <= std::min(a.rows(), a.columns()), erange);

	size_t end = std::min(a.rows(), a.columns()) - std::abs(k);
	size_t step = a.rows() + 1;
	size_t j = (k < 0 ? -k * a.rows() : k);
	array<T> c(end);

	for (size_t i = 0; i < end; i++, j+=step)
		c[i] = a[j];
	return c;
}

//! create diagonal matrix
template <class T, class S>
inline
array_2d<T> diag(const array<T, S>& a, int k = 0)
{
	size_t n = a.length() + std::abs(k);
	array_2d<T> r(n, n);
	size_t i;
	size_t len = n * n;
	for(i = 0; i < len; i++) r[i] = 0;

	size_t pos = 0;
	if(k <= 0) pos -= k; else pos += n * k;

	for(i = 0; i < n; i++) {
		r[pos] = a[i];
		pos += n + 1;
	}

	return r;
}

//! identity matrix
template <class T>
inline
array_2d<T> eye(size_t s, const T& zero = 0, const T& one = 1)
{
	array_2d<T> c(s,s);

	for (size_t i = 0; i < s; i++)
		for (size_t j = 0; j < s; j++)
			c(i, j) = (i == j) ? one : zero;

	return c;
}

//! identity matrix of arbitrary shape
template <class T, class D>
inline
array_2d<T> eye(const array<size_t, D>& indx,
				const T& zero = 0, const T& one = 1)
{
	CHECK(indx.length() == 2, eshape);

	size_t rows = indx[0];
	size_t cols = indx[1];
	array_2d<T> c(rows, cols);

	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			c(i, j) = (i == j) ? one : zero;

	return c;
}

//! lower triangular part of matrix
template <class T, class S>
inline
typename
array_2d<T, S>::create_similar tril(const array_2d<T, S>& a, int k = 0)
{
	typename array_2d<T, S>::create_similar c(a.size());

	for (size_t i = 0; i < a.columns(); i++)
		for (size_t j = 0; j < a.rows(); j++)
			c[i * a.rows() + j] = ((int)j < (int)(i - k) ?
			0 : a[i * a.rows() + j]);
	return c;
}

//! upper triangular part of matrix
template <class T, class S>
inline
typename
array_2d<T, S>::create_similar triu(const array_2d<T, S>& a, int k = 0)
{
	typename array_2d<T, S>::create_similar c(a.size());

	for (size_t i = 0; i < a.columns(); i++)
		for (size_t j = 0; j < a.rows(); j++)
			c[i * a.rows() + j] = ((int)j > (int)(i - k) ?
			0 : a[i * a.rows() + j]);
	return c;
}

//! rotate matrix
template <class T, class S>
inline
typename
array_2d<T, S>::create_new rot90(const array_2d<T, S>& a, int k = 1)
{
	if (k < 0) k = 4 - (-k % 4);
	else k = k % 4;
	typename array_2d<T, S>::create_new c(a);

	for (size_t repeat = 0; (int)repeat < k; repeat++)
		c = transpose(fliplr(c));
	return c;
}


//! transpose matrix
template <class T, class S>
inline
typename
array_2d<T, S>::create_new transpose(const array_2d<T, S>& a)
{
	typename array_2d<T, S>::create_new c(a.columns(), a.rows());

	for (size_t i = 0; i < c.columns(); i++)
		for (size_t j = 0; j < c.rows(); j++)
		c[i * c.rows() + j] = a[j * a.rows() + i];
	return c;
}

//todo place this somewhere
template<class T, class S>
array_2d<T, normal_2d> array_common_base<array_2d<T, S> >::operator()(
	const core_details::transpose_arg& c) const
{
	return transpose(this->to_current());
}

//todo: consistency!
template <class T>
inline
array_2d<T> ones(size_t r, size_t c)
{
	return array_2d<T>(r, c, T(1));
}

//! horizontal concatenation with another matrix
template <class T, class S, class D>
inline
typename
array_2d<T, S>::create_new horzcat(
	const array_2d<T, S>& a, const array_2d<T, D>& b)
{
	return cat<T>(1, a, b);
}

//! vertical concatenation with another matrix
template <class T, class S, class D>
inline
typename
array_2d<T, S>::create_new vertcat(
	const array_2d<T, S>& a, const array_2d<T, D>& b)
{
	return cat<T>(0, a, b);
}

template <class T>
inline
array_2d<T> inf(const size_t m, const size_t n)
{
	return array_2d<T>(m, n, std::numeric_limits<T>::infinity());
}

template <class T>
inline
array_2d<T> inf(const size_t m)
{
	return array_2d<T>(m, m, std::numeric_limits<T>::infinity());
}

//! Unwrap an array_2d to an array of arrays
template <class T> inline
array<array<T> > unwrap(const array_2d<T>& a)
{
	array<array<T> > c(a.rows());

	for(size_t i = 0; i < a.rows(); i++)
		c[i] = a(i, all());

	return c;
}

// iavr: disable until it is made an ivl_func
#if 0
//! Wrap an array of arrays to an array_2d
template <class T>
inline
array_2d<T> wrap(const array<array<T> > a)
{
	array_2d<T> c(a.size(), a[0].size());

	for(size_t i = 0; i < a.size(); i++)
		c(i, all()) = a[i];

	return c;
}
#endif

//! Matrix multiplication algorithm
template<class T, class S, class D>
inline
typename ivl::array_2d<T, S>::create_new
	mtimes(const ivl::array_2d<T, S> &x, const ivl::array_2d<T, D> &y)
{
	ivl::size_array xsize = x.size(); // get size of x
	ivl::size_array ysize = y.size(); // get size of y

	CHECK(xsize[1] == ysize[0], eshape);

	ivl::array_2d<T> m(xsize[0], ysize[1]);
	for(size_t row = 0;row < xsize[0]; row++)
		for(size_t col = 0;col < ysize[1]; col++)
		{
			m(row, col)=0;
			for(size_t i=0;i < xsize[1]; i++)
			m(row, col) += x(row, i) * y(i, col);
		}
      return m;
}

//-----------------------------------------------------------------------------

template <typename T1, typename S1, typename T2, typename S2>
array_2d <typename types::maps::max <T1, T2>::type,
	data::outersp<times_class, array<T1, S1>, array<T2, S2> > >
	outer(const array <T1, S1>& a1, const array <T2, S2>& a2)
{
		typedef array_2d <typename types::maps::max <T1, T2>::type,
			data::outersp<times_class, array<T1, S1>, array<T2, S2> > > ar_t;
		ar_t a(a1.length(), a2.length());
		a.setref(a1, a2);
		return a;
}

template <typename T1, typename S1, typename T2, typename S2>
array_2d <typename types::maps::max <T1, T2>::type,
	data::outersp<minus_class, array<T1, S1>, array<T2, S2> > >
	outer_minus(const array <T1, S1>& a1, const array <T2, S2>& a2)
{
		typedef array_2d <typename types::maps::max <T1, T2>::type,
			data::outersp<minus_class, array<T1, S1>, array<T2, S2> > > ar_t;
		ar_t a(a1.length(), a2.length());
		a.setref(a1, a2);
		return a;
}

} // namespace ivl

#endif // IVL_ARRAY_2D_DETAILS_ARRAY_2D_FUNCTIONS_HPP

