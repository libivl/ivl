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

#ifndef IVL_CORE_DETAILS_SAFETY_CHECK_SAFE_LOOP_HPP
#define IVL_CORE_DETAILS_SAFETY_CHECK_SAFE_LOOP_HPP

namespace ivl {

template<template <typename, typename> class F, class A, class B>
inline
void safe_loop_on(A& a, const B& b) //! might call threads (not for now)!
{
	if(a.overlap(b)) {
		 // is this derived_type redundancy?
		typename A::derived_type::create_new tmp;
		tmp.assign(a.derived());
		ivl::loop_on<F>(tmp, b);
		//ivl::copy(a, tmp);
		//loop_on<ivl::loops::assign_copy_class>(a, tmp);
		a.derived().assign(tmp);
	} else {
		ivl::loop_on<F>(a, b);
	}
}

template <class A, class B>
inline
void safe_assign(A& a, const B& b)
{
	using namespace types;
	// this is complementary to resolve_assign so that
	// this_type = scalar<derived_type> is allowed.
	// TODO: minor. it would be preferred this to be done somehow only once.
	typedef typename t_and<
		is_base<types::scalar_identifier, B>,
		is_base<A, B> >::type descalarize_t;

	if(a.overlap(types::r_descalarize<descalarize_t>(b))) {
		typename A::create_new tmp;
		tmp.assign(types::r_descalarize<descalarize_t>(b));
		a.assign(tmp);
	} else {
		a.assign(b);
	}
}

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_SAFETY_CHECK_SAFE_LOOP_HPP
