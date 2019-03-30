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

#ifndef IVL_QT_CORE_DEFAULT_HPP
#define IVL_QT_CORE_DEFAULT_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

template <
	typename S,
	typename D1 = term, typename D2 = term, typename D3 = term,
	typename D4 = term, typename D5 = term
> struct defaults { typedef S signature_type; };

//-----------------------------------------------------------------------------

template <typename S>
struct signature { typedef S type; };

template <
	typename S,
	typename D1, typename D2, typename D3, typename D4, typename D5
>
struct signature <defaults <S, D1, D2, D3, D4, D5> > { typedef S type; };

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename D1>
struct delegate <defaults <R (A1), D1> > : delegate <R (A1)>
{
	using delegate <R (A1)>::operator();
	R operator()() const { return (*this)(D1()()); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename D2>
struct delegate <defaults <R (A1, A2), D2> > : delegate <R (A1, A2)>
{
	using delegate <R (A1, A2)>::operator();
	R operator()(A1 a1) const { return (*this)(a1, D2()()); }
};

template <typename R, typename A1, typename A2, typename D1, typename D2>
struct delegate <defaults <R (A1, A2), D1, D2> > :
	delegate <defaults <R (A1, A2), D2> >
{
	using delegate <defaults <R (A1, A2), D2> >::operator();
	R operator()() const { return (*this)(D1()(), D2()()); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3, typename D3>
struct delegate <defaults <R (A1, A2, A3), D3> > : delegate <R (A1, A2, A3)>
{
	using delegate <R (A1, A2, A3)>::operator();
	R operator()(A1 a1, A2 a2) const { return (*this)(a1, a2, D3()()); }
};

template <typename R, typename A1, typename A2, typename A3,
	typename D2, typename D3
>
struct delegate <defaults <R (A1, A2, A3), D2, D3> > :
	delegate <defaults <R (A1, A2, A3), D3> >
{
	using delegate <defaults <R (A1, A2, A3), D3> >::operator();
	R operator()(A1 a1) const { return (*this)(a1, D2()(), D3()()); }
};

template <typename R, typename A1, typename A2, typename A3,
	typename D1, typename D2, typename D3
>
struct delegate <defaults <R (A1, A2, A3), D1, D2, D3> > :
	delegate <defaults <R (A1, A2, A3), D2, D3> >
{
	using delegate <defaults <R (A1, A2, A3), D2, D3> >::operator();
	R operator()() const { return (*this)(D1()(), D2()(), D3()()); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3, typename A4,
	typename D4
>
struct delegate <defaults <R (A1, A2, A3, A4), D4> > :
	delegate <R (A1, A2, A3, A4)>
{
	using delegate <R (A1, A2, A3, A4)>::operator();
	R operator()(A1 a1, A2 a2, A3 a3) const
		{ return (*this)(a1, a2, a3, D4()()); }
};

template <typename R, typename A1, typename A2, typename A3, typename A4,
	typename D3, typename D4
>
struct delegate <defaults <R (A1, A2, A3, A4), D3, D4> > :
	delegate <defaults <R (A1, A2, A3, A4), D4> >
{
	using delegate <defaults <R (A1, A2, A3, A4), D4> >::operator();
	R operator()(A1 a1, A2 a2) const
		{ return (*this)(a1, a2, D3()(), D4()()); }
};

template <typename R, typename A1, typename A2, typename A3, typename A4,
	typename D2, typename D3, typename D4
>
struct delegate <defaults <R (A1, A2, A3, A4), D2, D3, D4> > :
	delegate <defaults <R (A1, A2, A3, A4), D3, D4> >
{
	using delegate <defaults <R (A1, A2, A3, A4), D3, D4> >::operator();
	R operator()(A1 a1) const { return (*this)(a1, D2()(), D3()(), D4()()); }
};

template <typename R, typename A1, typename A2, typename A3, typename A4,
	typename D1, typename D2, typename D3, typename D4
>
struct delegate <defaults <R (A1, A2, A3, A4), D1, D2, D3, D4> > :
	delegate <defaults <R (A1, A2, A3, A4), D2, D3, D4> >
{
	using delegate <defaults <R (A1, A2, A3, A4), D2, D3, D4> >::operator();
	R operator()() const { return (*this)(D1()(), D2()(), D3()(), D4()()); }
};

//-----------------------------------------------------------------------------

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename D5
>
struct delegate <defaults <R (A1, A2, A3, A4, A5), D5> > :
	delegate <R (A1, A2, A3, A4, A5)>
{
	using delegate <R (A1, A2, A3, A4, A5)>::operator();
	R operator()(A1 a1, A2 a2, A3 a3, A4 a4) const
		{ return (*this)(a1, a2, a3, a4, D5()()); }
};

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename D4, typename D5
>
struct delegate <defaults <R (A1, A2, A3, A4, A5), D4, D5> > :
	delegate <defaults <R (A1, A2, A3, A4, A5), D5> >
{
	using delegate <defaults <R (A1, A2, A3, A4, A5), D5> >::operator();
	R operator()(A1 a1, A2 a2, A3 a3) const
		{ return (*this)(a1, a2, a3, D4()(), D5()()); }
};

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename D3, typename D4, typename D5
>
struct delegate <defaults <R (A1, A2, A3, A4, A5), D3, D4, D5> > :
	delegate <defaults <R (A1, A2, A3, A4, A5), D4, D5> >
{
	using delegate <defaults <R (A1, A2, A3, A4, A5), D4, D5> >::operator();
	R operator()(A1 a1, A2 a2) const
		{ return (*this)(a1, a2, D3()(), D4()(), D5()()); }
};

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename D2, typename D3, typename D4, typename D5
>
struct delegate <defaults <R (A1, A2, A3, A4, A5), D2, D3, D4, D5> > :
	delegate <defaults <R (A1, A2, A3, A4, A5), D3, D4, D5> >
{
	using delegate <defaults <R (A1, A2, A3, A4, A5), D3, D4, D5> >
		::operator();
	R operator()(A1 a1) const
		{ return (*this)(a1, D2()(), D3()(), D4()(), D5()()); }
};

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename D1, typename D2, typename D3, typename D4, typename D5
>
struct delegate <defaults <R (A1, A2, A3, A4, A5), D1, D2, D3, D4, D5> > :
	delegate <defaults <R (A1, A2, A3, A4, A5), D2, D3, D4, D5> >
{
	using delegate <defaults <R (A1, A2, A3, A4, A5), D2, D3, D4, D5> >
		::operator();
	R operator()() const
		{ return (*this)(D1()(), D2()(), D3()(), D4()(), D5()()); }
};

//-----------------------------------------------------------------------------

}  // namespace delegate_details

using delegate_details::defaults;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_DEFAULT_HPP
