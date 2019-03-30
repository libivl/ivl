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

#ifndef IVL_CORE_DETAILS_LOOPS_LOOP_ON_HPP
#define IVL_CORE_DETAILS_LOOPS_LOOP_ON_HPP

namespace ivl {

namespace loops {

template <
	template <typename, typename> class F,
	class A,
	class B,
	class A_IS_ARRAY,
	class B_IS_ARRAY,
	class OP_IS_WW
>
struct loop_on_resolve { };

template <
	template <typename, typename> class F,
	class A,
	class B
>
struct loop_on_resolve<F, A, B, types::t_true, types::t_true, types::t_false>
{
	static inline void operate(A& a, const B& b)
	{
		loops::loop<F<typename A::reference,
			typename B::const_reference> >(a, b);
	}
};

template <
	template <typename, typename> class F,
	class A,
	class B
>
struct loop_on_resolve<F, A, B, types::t_true, types::t_true, types::t_true>
{
	static inline void operate(A& a, const B& b)
	{
		loops::loop_ww<F<typename A::reference, typename B::reference> >(a, b);
	}
};

template <
	template <typename, typename> class F,
	class A,
	class B
>
struct loop_on_resolve<F, A, B, types::t_true, types::t_false, types::t_false>
{
	static inline void operate(A& a, const B& b)
	{
		typename array_details::scalar_to_array<B, A>::
			type v(a.size(), b); // must be derived() as
			// scalar_to_array works this way (at least for now).
		loops::loop<F<typename A::reference, const B&> >(a, v);
	}
};


template <
	template <typename, typename> class F,
	class A,
	class B
>
struct loop_on_resolve<F, A, B, types::t_false, types::t_false, types::t_false>
{
	static inline void operate(A& a, const B& b)
	{
		// trivial loop element = element. ...
		// allowed.
		a = b;
	}
};

template <
	template <typename, typename> class F,
	class A,
	class B
>
struct loop_on_resolve<F, A, B, types::t_false, types::t_true, types::t_false>
{
	// loop element = array.
	// not allowed.
	/*static inline void operate(A& a, const B& b)
	{
		a.unsupported_method();
		CHECK(false, ecomp());
	}*/
};

} /* namespace loops */

template<template <typename, typename> class F, class A, class B>
void loop_on(A& a, const B& b) //! might call threads (not for now)!
{
	loops::loop_on_resolve<F, A, B,
		typename types::is_ivl_array<A>::type,
		typename types::is_ivl_array<B>::type,
		typename types::is_base<types::loop_ww_identifier,
			F<typename types::get_value<A>::type,
				typename types::get_value<B>::type>
			>::type
	>::operate(a, b);
}

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_LOOPS_LOOP_ON_HPP
