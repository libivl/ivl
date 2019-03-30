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

#ifndef IVL_CORE_DETAILS_TYPES_OVERLOAD_HPP
#define IVL_CORE_DETAILS_TYPES_OVERLOAD_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace overload {
namespace details {

//-----------------------------------------------------------------------------

class fail
{
	enum { size = 31 };
	char pool[size];
};

//-----------------------------------------------------------------------------

template <
	typename F, int L,
	typename T1 = term, typename T2 = term, typename T3 = term,
	typename T4 = term, typename T5 = term, typename T6 = term
>
struct size
{
	enum { value = F::template size <L, T1, T2, T3, T4, T5, T6>::value };
};

template <
	typename F, int L,
	typename T1, typename T2, typename T3, typename T4, typename T5
>
struct size <F, L, T1, T2, T3, T4, T5>
{
	enum { value = F::template size <L, T1, T2, T3, T4, T5>::value };
};

template <
	typename F, int L,
	typename T1, typename T2, typename T3, typename T4
>
struct size <F, L, T1, T2, T3, T4>
{
	enum { value = F::template size <L, T1, T2, T3, T4>::value };
};

template <typename F, int L, typename T1, typename T2, typename T3>
struct size <F, L, T1, T2, T3>
{
	enum { value = F::template size <L, T1, T2, T3>::value };
};

template <typename F, int L, typename T1, typename T2>
struct size <F, L, T1, T2>
{
	enum { value = F::template size <L, T1, T2>::value };
};

template <typename F, int L, typename T1>
struct size <F, L, T1> { enum { value = F::template size <L, T1>::value }; };

template <typename F, int L>
struct size <F, L> { enum { value = F::template size <L>::value }; };

//-----------------------------------------------------------------------------

template <typename T>
struct conv { T operator+() const; };

template <typename T>
struct convert { typedef conv <T> type; };

template <>
struct convert <term> { typedef term type; };

//-----------------------------------------------------------------------------

template <
	typename F, int L,
	typename T1 = term, typename T2 = term, typename T3 = term,
	typename T4 = term, typename T5 = term, typename T6 = term
>
struct match
{
	typedef typename t_expr <size <F, L,
		typename convert <T1>::type,
		typename convert <T2>::type,
		typename convert <T3>::type,
		typename convert <T4>::type,
		typename convert <T5>::type,
		typename convert <T6>::type
	>::value != sizeof(fail)>::type type;
};

//-----------------------------------------------------------------------------

enum { low = -1, common = 0, mid = 1, high = 2 };

//-----------------------------------------------------------------------------

template <
	typename F, int L,
	typename T1 = term, typename T2 = term, typename T3 = term,
	typename T4 = term, typename T5 = term, typename T6 = term
>
class find_rec
{
	typedef typename t_if <
		match <F, L, T1, T2, T3, T4, T5, T6>,
		number <L>, find_rec <F, L - 1, T1, T2, T3, T4, T5, T6>
	>::type result;

public:
	enum { value = result::value };
};

template <
	typename F,
	typename T1, typename T2, typename T3,
	typename T4, typename T5, typename T6
>
struct find_rec <F, low, T1, T2, T3, T4, T5, T6> { enum { value = low }; };

//-----------------------------------------------------------------------------

template <
	typename F,
	typename T1 = term, typename T2 = term, typename T3 = term,
	typename T4 = term, typename T5 = term, typename T6 = term
>
struct find : public find_rec <F, high, T1, T2, T3, T4, T5, T6> { };

//-----------------------------------------------------------------------------

template <typename F, typename R>
R call()
{
	typedef number <find <F>::value> L;
	return F::template call <R>(L());
}

template <typename F, typename R, typename T1>
R call(T1 a1)
{
	typedef number <find <F, T1>::value> L;
	return F::template call <R, T1>(L(), a1);
}

template <typename F, typename R, typename T1, typename T2>
R call(T1 a1, T2 a2)
{
	typedef number <find <F, T1, T2>::value> L;
	return F::template call <R, T1, T2>(L(), a1, a2);
}

template <typename F, typename R, typename T1, typename T2, typename T3>
R call(T1 a1, T2 a2, T3 a3)
{
	typedef number <find <F, T1, T2, T3>::value> L;
	return F::template call <R, T1, T2, T3>(L(), a1, a2, a3);
}

template <
	typename F, typename R,
	typename T1, typename T2, typename T3, typename T4
>
R call(T1 a1, T2 a2, T3 a3, T4 a4)
{
	typedef number <find <F, T1, T2, T3, T4>::value> L;
	return F::template call <R, T1, T2, T3, T4> (L(), a1, a2, a3, a4);
}

template <
	typename F, typename R,
	typename T1, typename T2, typename T3, typename T4, typename T5
>
R call(T1 a1, T2 a2, T3 a3, T4 a4, T5 a5)
{
	typedef number <find <F, T1, T2, T3, T4, T5>::value> L;
	return F::template call <R, T1, T2, T3, T4, T5> (L(), a1, a2, a3, a4, a5);
}

template <
	typename F, typename R,
	typename T1, typename T2, typename T3, typename T4, typename T5, typename T6
>
R call(T1 a1, T2 a2, T3 a3, T4 a4, T5 a5, T6 a6)
{
	typedef number <find <F, T1, T2, T3, T4, T5, T6>::value> L;
	return F::template call <R, T1, T2, T3, T4, T5, T6>
		(L(), a1, a2, a3, a4, a5, a6);
}

//-----------------------------------------------------------------------------

}  // namespace details

typedef number <details::high>    high;
typedef number <details::mid>     mid;
typedef number <details::common>  common;
typedef number <details::low>     low;

using details::fail;
using details::find;
using details::call;

//-----------------------------------------------------------------------------

}  // namespace overload

// ----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_TYPES_OVERLOAD_HPP
