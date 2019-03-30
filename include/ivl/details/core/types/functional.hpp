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

#ifndef IVL_CORE_DETAILS_TYPES_FUNCTIONAL_HPP
#define IVL_CORE_DETAILS_TYPES_FUNCTIONAL_HPP

namespace ivl {

namespace types {

// ---------------------------------------------------

// functional

namespace types_details {

	template <class COND>
	struct r_if_result { };

	template<>
	struct r_if_result<t_true>
	{
		template <class THEN, class ELSE>
		static inline THEN& operate(THEN& t, ELSE& e) { return t; }
	};

	template<>
	struct r_if_result<t_false>
	{
		template <class THEN, class ELSE>
		static inline ELSE& operate(THEN& t, ELSE& e) { return e; }
	};

} /* namespace types_details */

//-----------------------------------------------------------------------------

// r_if returns the requested type
template <class COND, class THEN, class ELSE>
inline
typename t_if<COND, THEN&, ELSE&>::type r_if(THEN& t, ELSE& e)
{
	return types_details::r_if_result<typename COND::type>::operate(t, e);
}

template <class COND, class THEN, class ELSE>
inline
typename t_if<COND, const THEN&, ELSE&>::type r_if(const THEN& t, ELSE& e)
{
	return types_details::r_if_result<typename COND::type>
		::template operate<const THEN, ELSE>(t, e);
}

template <class COND, class THEN, class ELSE>
inline
typename t_if<COND, THEN&, const ELSE&>::type r_if(THEN& t, const ELSE& e)
{
	return types_details::r_if_result<typename COND::type>
		::template operate<THEN, const ELSE>(t, e);
}

template <class COND, class THEN, class ELSE>
inline
typename t_if<COND, const THEN&, const ELSE&>::
	type r_if(const THEN& t, const ELSE& e)
{
	return types_details::r_if_result<typename COND::type>
		::template operate<const THEN, const ELSE>(t, e);
}
//-----------------------------------------------------------------------------

template <bool COND, class THEN, class ELSE>
inline
typename t_if_b<COND, THEN&, ELSE&>::type r_if_b(THEN& t, ELSE& e)
{
	return types_details::r_if_result<typename t_expr<COND>::type>
		::operate(t, e);
}

template <bool COND, class THEN, class ELSE>
inline
typename t_if_b<COND, const THEN&, ELSE&>::type r_if_b(const THEN& t, ELSE& e)
{
	return types_details::r_if_result<typename t_expr<COND>::type>
		::template operate<const THEN, ELSE>(t, e);
}

template <bool COND, class THEN, class ELSE>
inline
typename t_if_b<COND, THEN&, const ELSE&>::type r_if_b(THEN& t, const ELSE& e)
{
	return types_details::r_if_result<typename t_expr<COND>::type>
		::template operate<THEN, const ELSE>(t, e);
}

template <bool COND, class THEN, class ELSE>
inline
typename t_if_b<COND, const THEN&, const ELSE&>::
	type r_if_b(const THEN& t, const ELSE& e)
{
	return types_details::r_if_result<typename t_expr<COND>::type>
		::template operate<const THEN, const ELSE>(t, e);
}

//-----------------------------------------------------------------------------

namespace types_details {

template <class A, class IS_RESIZEABLE>
class r_resize_details { };

template <class A>
class r_resize_details<A, t_true>
{
	template <class SZ>
	static inline bool operate(A& a, const SZ& l)
	{
		a.resize(l);
		return true;
	}
	template <class SZ, class T>
	static inline bool operate(A& a, const SZ& l, const T& s)
	{
		a.resize(l, s);
		return true;
	}
	template <class SZ>
	static inline bool reshape(A& a, const SZ& s)
	{
		a.reshape(s);
		return true;
	}
};

template <class A>
class r_resize_details<A, t_false>
{
	template <class SZ>
	static inline bool operate(A& a, const SZ& l)
	{
		return (a.size() == l);
	}
	template <class SZ, class T>
	static inline bool operate(A& a, const SZ& l, const T& s)
	{
		return (a.size() == l);
	}
	template <class SZ>
	static inline bool reshape(A& a, const SZ& s)
	{
		return (a.size() == s);
	}
};

} /* namespace types_details */

///r_resize resizes array and returns true if resizeable or if length is same.
template <class A, class SZ>
bool r_resize(A& a, const SZ& sz)
{
	return types_details::r_resize_details<A,
		t_and<typename A::is_resizeable, t_not<is_const<A> > >
	>::operate(a, sz);
}

template <class A, class SZ, class T>
bool r_resize(A& a, const SZ& sz, const T& s)
{
	return types_details::r_resize_details<A,
		t_and<typename A::is_resizeable, t_not<is_const<A> > >
	>::operate(a, sz, s);
}

template <class A, class SZ, class T>
bool r_reshape(A& a, const SZ& sz, const T& s)
{
	return types_details::r_resize_details<A,
		t_and<typename A::is_resizeable, t_not<is_const<A> > >
	>::reshape(a, sz, s);
}

//-----------------------------------------------------------------------------

// SFINAE

namespace types_details {

struct blocking_type { };

} // namespace types_details

template<class C, class R = int, class IGN = int>
struct enable_if : t_if<C, t_id<R>,
	types_details::blocking_type>::type { };

template<class C, class R = int, class IGN = int>
struct disable_if : t_if<C,
	types_details::blocking_type, t_id<R> >::type { };

template<bool B, class R = int, class IGN = int>
struct enable_if_b : t_if<t_expr<B>, t_id<R>,
	types_details::blocking_type>::type { };

template<bool B, class R = int, class IGN = int>
struct disable_if_b : t_if<t_expr<B>,
	types_details::blocking_type, t_id<R> >::type { };

//-----------------------------------------------------------------------------

}; /*namespace types*/

}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_TYPES_FUNCTIONAL_HPP
