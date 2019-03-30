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

#ifndef IVL_CORE_DETAILS_RVALUE_HPP
#define IVL_CORE_DETAILS_RVALUE_HPP

namespace ivl {

template<class DERIVED>
class rvalue_base
: public types::rvalue_identifier
{
private:
	typedef DERIVED derived_type;

public:
	const derived_type& derived() const
		{ return static_cast<const derived_type&>(*this); }

	derived_type& derived()
		{ return static_cast<derived_type&>(*this); }
};

namespace core_details {

template <class A, class IS_LINEAR>
struct rval_tool {};

template <class A>
struct rval_tool<A, types::t_false>
{
	typedef typename A::create_similar type;
	static inline type operate(const A& a) { return type(a); }
};

template <class A>
struct rval_tool<A, types::t_true>
{
	typedef const A& type;
	static inline const A& operate(const A& a) { a; }
};

template <class A>
struct resolve_rval
: public rval_tool<A, typename A::is_linear>
{
	typedef typename resolve_rval::type type;
};

/*
template <class A>
struct resolve_is_subreference
: public rval_tool<A, typename types::t_and<typename A::is_writeable,
	types::is_base<types::subreference_identifier, A> >::type>
{
	typedef typename resolve_rval::type type;
};
*/

} /* namespace core_details */

///! normalize an input function argument.
///! makes sure that an array or function result can be passed to a function
///! as an argument, making a possible copy of the input array.
///! also it allows a subarray of the same object to be used as input and
///! output without invalid data due to overlapping (by making a copy).
///  Any arrays that are not default array objects (dont have a c pointer
///  with their data, or more precisely are not is_linear) will be copied.
///  Note: that, in cases that the array is valid, this could decrease
///  performance because of the copy, however, in some cases it could
///  also increase performance. This is because some arrays like element
///  function arrays do complicated stuff to retrieve every element.
///  The easy but not absolute rule is that we use rval when the function
///  will use each element of the array more than once.
///  Of course rval must be used when, the program won't compile without it
///  i.e. the array is not valid, or when the array is not safe, i.e. it is
///  used as input and output simultaneously.
///  Safety: the safety rule is to always use rval even if you don't have to.
///  Note: If the input array is exactly the same as the output array, but
///  it is a normal array, rval won't make a copy and safety will not be
///  guarranteed. This by-reference array C++ inherent problem is simply
///  solved by the r-value ivl mechanism by checking to see if the input-
///  output arguments are the same, and hence you don't have to do
///  anything when the function you are calling is a well-defined rvalue
///  function.
///  Warning: feature maybe not implemented yet!
template<class A>
typename core_details::resolve_rval<A>::type rval(const A& a)
{
	return core_details::resolve_rval<A>::operate(a);
}

///! normalize an output function argument.
///! allows subarrays and all other referencing arrays to be passed by
///! reference as output variables in functions.
/// This is actually a simple const-cast. Can't be avoided since
/// subarrays are normally temporary objects, and declaring them as
/// variables would be not good since the type of a subarray is too
/// complicated.
template <class A>
inline A& by_ref(const A& a) { return const_cast<A&>(a); }



namespace core_details {

template <class R, class A>
class lval_wrapper : public A
{
	const R& r;
public:
	template <class X>
	lval_wrapper(const R& r, const X& x) : r(r), A(r) { }
	lval_wrapper(const lval_wrapper& x) : r(x.r), A(x) { }

	lval_wrapper& operator=(const lval_wrapper& x)
	{ A::operator=(x); return *this; }
	using A::operator=;

	~lval_wrapper()
	{
		const_cast<typename types::remove_const<R>::type&>(r).assign(*this);
	}
};

template <class A, class IS_LINEAR>
struct lval_tool {};

template <class A>
struct lval_tool<A, types::t_false>
{
	typedef lval_wrapper<A, typename A::create_similar> type;
	static inline type operate(const A& a) { return type(a); }
};

template <class A>
struct lval_tool<A, types::t_true>
{
	typedef const A& type;
	static inline const A& operate(const A& a) { a; }
};

template <class A>
struct resolve_lval
: public lval_tool<A, typename A::is_linear>
{
	typedef typename resolve_lval::type type;
};

} /* namespace core_details */

///! normalize an output function argument.
///! makes sure that an array can be passed to a function
///! as an argument, making a possible copy of the output array.
///! that is, it has random access.
template <class A>
inline
typename core_details::resolve_lval<A>::type lval(const A& a)
{
	return core_details::resolve_lval<A>::operate(a);
}

}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_RVALUE_HPP
