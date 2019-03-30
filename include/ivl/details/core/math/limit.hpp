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

#ifndef IVL_CORE_DETAILS_MATH_LIMIT_HPP
#define IVL_CORE_DETAILS_MATH_LIMIT_HPP

namespace ivl {

//-----------------------------------------------------------------------------

//! infinity<T>
template<class T>
inline T inf()
{
	return std::numeric_limits<typename types::to_real<T>::type>::infinity();
}

//! NaN<T>
template<class T>
inline T nan()
{
	return std::numeric_limits<typename types::to_real<T>::type>::quiet_NaN();
}

// TODO: remove this?
//! NaN<T>
template<class T>
inline T NaN()
{
	return std::numeric_limits<typename types::to_real<T>::type>::quiet_NaN();
}

//-----------------------------------------------------------------------------

namespace lim {

template <class T>
T min()
{
	return std::numeric_limits<typename types::to_real<T>::type>::min();
}

template <class T>
T max()
{
	return std::numeric_limits<typename types::to_real<T>::type>::max();
}

}  // namespace lim

//-----------------------------------------------------------------------------

namespace lim_details {

	// infinity if available, max otherwise
	template <class T, bool HAS_INF>
	struct inf_max1 { };

	template <class T>
	struct inf_max1 <T, true>
	{
		static T val() { return std::numeric_limits<T>::infinity(); }
	};

	template <class T>
	struct inf_max1 <T, false>
	{
		static T val() { return lim::max<T>(); }
	};

	template <class T>
	struct inf_max2 : public inf_max1 <T, std::numeric_limits<T>::has_infinity>
		{ };

//-----------------------------------------------------------------------------

	// minus infinity if available, max otherwise
	template <class T, bool HAS_INF>
	struct inf_min1 { };

	template <class T>
	struct inf_min1 <T, true>
	{
		static T val() { return -std::numeric_limits<T>::infinity(); }
	};

	template <class T>
	struct inf_min1 <T, false>
	{
		static T val() { return lim::min<T>(); }
	};

	template <class T>
	struct inf_min2 : public inf_min1 <T, std::numeric_limits<T>::has_infinity>
		{ };

}  // namespace lim_details

//-----------------------------------------------------------------------------

template <class T>
T inf_max()
{
	return lim_details::inf_max2 <typename types::to_real<T>::type>::val();
}

template <class T>
T inf_min()
{
	return lim_details::inf_min2 <typename types::to_real<T>::type>::val();
}

//-----------------------------------------------------------------------------

namespace fun {

struct inf
{
	template<class T>
	T operator()(const T&) const { return ivl::inf <T> (); }
};

struct nan
{
	template<class T>
	T operator()(const T&) const { return ivl::nan <T> (); }
};

namespace lim {

struct min
{
	template<class T>
	T operator()(const T&) const { return ivl::lim::min <T> (); }
};

struct max
{
	template<class T>
	T operator()(const T&) const { return ivl::lim::max <T> (); }
};

}  // namespace lim

struct inf_max
{
	template<class T>
	T operator()(const T&) const { return ivl::inf_max <T> (); }
};

struct inf_min
{
	template<class T>
	T operator()(const T&) const { return ivl::inf_min <T> (); }
};

}  // namespace fun

//-----------------------------------------------------------------------------

namespace fn {

static __attribute__ ((unused))
fun::inf inf;

static __attribute__ ((unused))
fun::nan nan;

namespace lim {

static __attribute__ ((unused))
fun::lim::min min;

static __attribute__ ((unused))
fun::lim::max max;

}  // namespace lim

static __attribute__ ((unused))
fun::inf_max inf_max;

static __attribute__ ((unused))
fun::inf_min inf_min;

}  // namespace fun

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_MATH_LIMIT_HPP
