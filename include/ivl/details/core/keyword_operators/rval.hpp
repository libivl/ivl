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

#ifndef IVL_CORE_DETAILS_OPERATION_RVAL_HPP
#define IVL_CORE_DETAILS_OPERATION_RVAL_HPP

namespace ivl {

namespace core_details {

template <class A, class DST>
struct rval_tool
{
	typedef DST type;
	static inline type operate(const A& a) { return type(a); }
};

template <class A>
struct rval_tool<A, A>
{
	typedef const A& type;
	static inline const A& operate(const A& a) { return a; }
};

template <class A>
struct resolve_rval
: public rval_tool<A,
//typename types::
//	change_data_class_set_rec<data::normal, A>::type
	typename A::create_new
>
{
	typedef typename resolve_rval::type type;
};

/*
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
	static inline const A& operate(const A& a) { return a; }
};

template <class A>
struct resolve_rval
: public rval_tool<A, typename A::is_linear>
{
	typedef typename resolve_rval::type type;
};
*/
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

}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_OPERATION_RVAL_HPP
