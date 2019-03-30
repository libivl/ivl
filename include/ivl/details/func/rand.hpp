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

//-----------------------------------------------------------------------------

#ifndef IVL_FUNC_RAND
#define IVL_FUNC_RAND

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace core_details {

//-----------------------------------------------------------------------------

template <class J, class J1, class J2>
struct rand_
{
	typedef types::number<0> cost;
	static inline double elem_op(double min, double max)
	{
		return ivl::math::rand(min, max);
	}
};

} // namespace core_details

static __attribute__ ((unused)) struct rand_impl : public ivl_func<rand_impl>,
	public binary_elem_base<double, double, double, core_details::rand_>
{
	typedef binary_elem_base<double, double, double, core_details::rand_> rand_base;

	using rand_base::operator[];
	//using randb::operator();


	//! return array of \e s random numbers, uniformly distributed from 0.0 to 1.0
	array<double> operator()(size_t s)
	{
		array<double> c(s);
		for (size_t i = 0; i < c.length(); i++)
			c[i] = std::rand() / (double)RAND_MAX;
		return c;
	}

	//! return array of \e s random numbers, uniformly distributed between \e from and \e to
	template<class T>
	array<T> operator()(size_t s, const T& from, const T& to)
	{
		CHECK(to >= from, ecomp); // TODO: different kind of exception here...

		array<T> c(s);
		for (size_t i = 0; i < c.length(); ++i)
			c[i] = ivl::math::rand(from, to);
		return c;
	}

	//! return array of random numbers, with each element uniformly distributed
	//! between the corresponding element of array \e from and scalar \e to
	template<class T, class D>
	array<T> operator()(const array<T, D>& from, const T& to)
	{
		CHECK(all(to >= from), ecomp); // TODO: different kind of exception here...

		array<T> c(from.length());
		for (size_t i = 0; i < c.length(); ++i)
			c[i] = ivl::math::rand(T(from[i]), to);
		return c;
	}

	//! return array of random numbers, with each element uniformly distributed
	//! between scalar \e from and the corresponding element of array \e to
	template<class T, class D>
	array<T> operator()(const T& from, const array<T, D>& to)
	{
		CHECK(all(to >= from), ecomp); // TODO: different kind of exception here...

		array<T> c(to.length());
		for (size_t i = 0; i < c.length(); ++i)
			c[i] = ivl::math::rand(from, T(to[i]));
		return c;
	}

	//! return array of random numbers, with each element uniformly distributed
	//! between the corresponding elements of arrays \e from and \e to
	template<class T, class D>
	array<T> operator()(const array<T, D>& from, const array<T, D>& to)
	{
		CHECK(all(to >= from), ecomp); // TODO: different kind of exception here...

		array<T> c(from.length());
		for (size_t i = 0; i < c.length(); ++i)
			c[i] = ivl::math::rand(T(from[i]), T(to[i]));
		return c;
	}

	//! return a single random number, uniformly distributed between \e from and \e to
	T operator()(const T& from, const T& to)
	{
		return ivl::math::rand(from, to);
	}

	/**
	 * \brief Create an array_nd of random numbers.
	 *
	 * The numbers will be uniformly distributed between 0 to RAND_MAX
	 *
	 * @param sz Contains the dimensions of the array_nd that will be created.
	 */
	template <class T, class D>
	inline
	array_nd<T> type(const array<size_t, D>& sz)
	{
		array_nd<T> a(sz);
		for (size_t i = 0; i < a.length(); i++)
			a[i] = std::rand();
		return a;
	}

	/**
	 * \brief Create an array_nd of random numbers of given dimensions.
	 *
	 * The numbers will be uniformly distributed between 0 to RAND_MAX
	 *
	 * @param sz Contains the dimensions of the array_nd that will be created.
	 */
	template <class T, class D>
	inline
	array_nd<T> operator()(const array<size_t, D>& sz)
	{
		array_nd<T> a(sz);
		for (size_t i = 0; i < a.length(); i++)
			a[i] = std::rand();
		return a;
	}

	/**
	 * \brief Create an array_nd of random numbers of given dimensions.
	 *
	 * The numbers will be uniformly distributed between 0 to RAND_MAX
	 *
	 * @param sz Contains the dimensions of the array_nd that will be created.
	 */
	template <class T, class D>
	inline
	array_nd<T> operator()(const array<size_t, D>& sz, const T& from, const T& to)
	{
		CHECK(to >= from, ecomp); // TODO: different kind of exception here...

		array_nd<T> a(sz);
		for (size_t i = 0; i < a.length(); i++)
			a[i] = ivl::math::rand(from, to);
		return a;
	}

} rand, rnd, random;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_RAND
