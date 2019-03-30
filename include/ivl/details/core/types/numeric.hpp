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

#ifndef IVL_CORE_DETAILS_TYPES_NUMERIC_HPP
#define IVL_CORE_DETAILS_TYPES_NUMERIC_HPP

//-----------------------------------------------------------------------------

namespace ivl {
namespace types {

//-----------------------------------------------------------------------------

template <int N>
struct number
{
	typedef number<N> type;
	enum { value = N };
};

//-----------------------------------------------------------------------------

template <class N1, class N2>
struct t_add
{
	typedef number<N1::value + N2::value> type;
	enum { value = type::value };
};

template <class N1, class N2, class N3>
struct t_add_3
{
	typedef number<N1::value + N2::value + N3::value> type;
	enum { value = type::value };
};

template <class N1, class N2>
struct t_sub
{
	typedef number<N1::value - N2::value> type;
	enum { value = type::value };
};

template <class N>
struct t_neg
{
	typedef number< - N::value> type;
	enum { value = type::value };
};

template <class N1, class N2>
struct t_mul
{
	typedef number<N1::value * N2::value> type;
	enum { value = type::value };
};

template <class N1, class N2>
struct t_quot
{
	typedef number<N1::value / N2::value> type;
	enum { value = type::value };
};

template <class N1, class N2>
struct t_rem
{
	typedef number<N1::value % N2::value> type;
	enum { value = type::value };
};

template <class N1, class N2>
struct t_max
{
	enum { n1 = (int(N1::value) > int(N2::value)) };
	typedef typename t_if<t_expr<n1>, N1, N2>::type type;
	enum { value = type::value };
};

template <class N1, class N2>
struct t_min
{
	enum { n1 = (int(N1::value) < int(N2::value)) };
	typedef typename t_if<t_expr<n1>, N1, N2>::type type;
	enum { value = type::value };
};

template <class N>
struct t_abs : public t_max <N, typename t_neg <N>::type> { };

//-----------------------------------------------------------------------------
// relational

template <class N1, class N2>
struct t_gt
{
	enum { n1 = (int(N1::value) > int(N2::value)) };
	typedef typename t_expr<n1>::type type;
};

template <class N1, class N2>
struct t_ge
{
	enum { n1 = (int(N1::value) >= int(N2::value)) };
	typedef typename t_expr<n1>::type type;
};

template <class N1, class N2>
struct t_lt
{
	enum { n1 = (int(N1::value) < int(N2::value)) };
	typedef typename t_expr<n1>::type type;
};

template <class N1, class N2>
struct t_le
{
	enum { n1 = (int(N1::value) <= int(N2::value)) };
	typedef typename t_expr<n1>::type type;
};

//-----------------------------------------------------------------------------

}  // namespace types
}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_TYPES_NUMERIC_HPP
