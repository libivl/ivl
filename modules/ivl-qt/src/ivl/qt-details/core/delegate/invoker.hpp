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

#ifndef IVL_QT_CORE_INVOKER_HPP
#define IVL_QT_CORE_INVOKER_HPP

namespace ivl {

//-----------------------------------------------------------------------------
// based on code by Sergey Ryazanov
// http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

template <typename R>
class invoker <R ()>
{
public:
	invoker() { }

	template <class D>
	R operator()(const D& d) const { return d(); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1>
class invoker <R (A1)>
{
	A1 a1;

public:
	invoker(A1 a1) : a1(a1) { }

	template <class D>
	R operator()(const D& d) const { return d(a1); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2>
class invoker <R (A1, A2)>
{
	A1 a1; A2 a2;

public:
	invoker(A1 a1, A2 a2) : a1(a1), a2(a2) { }

	template <class D>
	R operator()(const D& d) const { return d(a1, a2); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3>
class invoker <R (A1, A2, A3)>
{
	A1 a1; A2 a2; A3 a3;

public:
	invoker(A1 a1, A2 a2, A3 a3) : a1(a1), a2(a2), a3(a3) { }

	template <class D>
	R operator()(const D& d) const { return d(a1, a2, a3); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3, typename A4>
class invoker <R (A1, A2, A3, A4)>
{
	A1 a1; A2 a2; A3 a3; A4 a4;

public:
	invoker(A1 a1, A2 a2, A3 a3, A4 a4) : a1(a1), a2(a2), a3(a3), a4(a4) { }

	template <class D>
	R operator()(const D& d) const { return d(a1, a2, a3, a4); }
};

//-----------------------------------------------------------------------------

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5
>
class invoker <R (A1, A2, A3, A4, A5)>
{
	A1 a1; A2 a2; A3 a3; A4 a4; A5 a5;

public:
	invoker(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) :
		a1(a1), a2(a2), a3(a3), a4(a4), a5(a5) { }

	template <class D>
	R operator()(const D& d) const { return d(a1, a2, a3, a4, a5); }
};

//-----------------------------------------------------------------------------

}  // namespace delegate_details

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_INVOKER_HPP
