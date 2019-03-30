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

#ifndef IVL_CORE_DETAILS_OPERATION_LVAL_HPP
#define IVL_CORE_DETAILS_OPERATION_LVAL_HPP

namespace ivl {


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

#endif // IVL_CORE_DETAILS_OPERATION_LVAL_HPP
