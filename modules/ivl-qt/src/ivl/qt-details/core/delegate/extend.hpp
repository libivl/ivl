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

#ifndef IVL_QT_CORE_EXTEND_HPP
#define IVL_QT_CORE_EXTEND_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

template <typename S>
class delegate;

template <typename S>
struct extend;

//-----------------------------------------------------------------------------

template <typename R, typename A1>
class extend <R (A1)>
{
	typedef delegate <R (A1)> D;
	D& d() { return static_cast <D&>(*this); }

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1)>
	D& bind() { return d().bind <F, term>(); }

	template <typename T, R (T::*M)(A1)>
	D& bind(T* obj) { return d().bind <T, M, term>(obj); }

	template <typename T, R (T::*M)(A1) const>
	D& bind(T const* obj) { return d().bind <T, M, term>(obj); }

	template <typename F>
	D& bind(F* obj) { return d().bind <F, term>(obj); }

	template <typename F>
	D& bind(F const* obj) { return d().bind <F, term>(obj); }
};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2>
class extend <R (A1, A2)>
{
	typedef delegate <R (A1, A2)> D;
	D& d() { return static_cast <D&>(*this); }

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2), typename D2>
	D& bind() { return d().bind <F, D2, term>(); }

	template <typename T, R (T::*M)(A1, A2), typename D2>
	D& bind(T* obj) { return d().bind <T, M, D2, term>(obj); }

	template <typename T, R (T::*M)(A1, A2) const, typename D2>
	D& bind(T const* obj) { return d().bind <T, M, D2, term>(obj); }

	template <typename F, typename D2>
	D& bind(F* obj) { return d().bind <F, D2, term>(obj); }

	template <typename F, typename D2>
	D& bind(F const* obj) { return d().bind <F, D2, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2)>
	D& bind() { return d().bind <F, term>(); }

	template <typename T, R (T::*M)(A1, A2)>
	D& bind(T* obj) { return d().bind <T, M, term>(obj); }

	template <typename T, R (T::*M)(A1, A2) const>
	D& bind(T const* obj) { return d().bind <T, M, term>(obj); }

	template <typename F>
	D& bind(F* obj) { return d().bind <F, term>(obj); }

	template <typename F>
	D& bind(F const* obj) { return d().bind <F, term>(obj); }

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3>
class extend <R (A1, A2, A3)>
{
	typedef delegate <R (A1, A2, A3)> D;
	D& d() { return static_cast <D&>(*this); }

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3), typename D2, typename D3>
	D& bind() { return d().bind <F, D2, D3, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3), typename D2, typename D3>
	D& bind(T* obj) { return d().bind <T, M, D2, D3, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3) const, typename D2, typename D3>
	D& bind(T const* obj) { return d().bind <T, M, D2, D3, term>(obj); }

	template <typename F, typename D2, typename D3>
	D& bind(F* obj) { return d().bind <F, D2, D3, term>(obj); }

	template <typename F, typename D2, typename D3>
	D& bind(F const* obj) { return d().bind <F, D2, D3, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3), typename D3>
	D& bind() { return d().bind <F, D3, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3), typename D3>
	D& bind(T* obj) { return d().bind <T, M, D3, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3) const, typename D3>
	D& bind(T const* obj) { return d().bind <T, M, D3, term>(obj); }

	template <typename F, typename D3>
	D& bind(F* obj) { return d().bind <F, D3, term>(obj); }

	template <typename F, typename D3>
	D& bind(F const* obj) { return d().bind <F, D3, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3)>
	D& bind() { return d().bind <F, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3)>
	D& bind(T* obj) { return d().bind <T, M, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3) const>
	D& bind(T const* obj) { return d().bind <T, M, term>(obj); }

	template <typename F>
	D& bind(F* obj) { return d().bind <F, term>(obj); }

	template <typename F>
	D& bind(F const* obj) { return d().bind <F, term>(obj); }

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3, typename A4>
class extend <R (A1, A2, A3, A4)>
{
	typedef delegate <R (A1, A2, A3, A4)> D;
	D& d() { return static_cast <D&>(*this); }

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4), typename D2, typename D3, typename D4>
	D& bind() { return d().bind <F, D2, D3, D4, term>(); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4),
		typename D2, typename D3, typename D4
	>
	D& bind(T* obj) { return d().bind <T, M, D2, D3, D4, term>(obj); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4) const,
		typename D2, typename D3, typename D4
	>
	D& bind(T const* obj) { return d().bind <T, M, D2, D3, D4, term>(obj); }

	template <typename F, typename D2, typename D3, typename D4>
	D& bind(F* obj) { return d().bind <F, D2, D3, D4, term>(obj); }

	template <typename F, typename D2, typename D3, typename D4>
	D& bind(F const* obj) { return d().bind <F, D2, D3, D4, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4), typename D3, typename D4>
	D& bind() { return d().bind <F, D3, D4, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3, A4), typename D3, typename D4>
	D& bind(T* obj) { return d().bind <T, M, D3, D4, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3, A4) const, typename D3, typename D4>
	D& bind(T const* obj) { return d().bind <T, M, D3, D4, term>(obj); }

	template <typename F, typename D3, typename D4>
	D& bind(F* obj) { return d().bind <F, D3, D4, term>(obj); }

	template <typename F, typename D3, typename D4>
	D& bind(F const* obj) { return d().bind <F, D3, D4, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4), typename D4>
	D& bind() { return d().bind <F, D4, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3, A4), typename D4>
	D& bind(T* obj) { return d().bind <T, M, D4, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3, A4) const, typename D4>
	D& bind(T const* obj) { return d().bind <T, M, D4, term>(obj); }

	template <typename F, typename D4>
	D& bind(F* obj) { return d().bind <F, D4, term>(obj); }

	template <typename F, typename D4>
	D& bind(F const* obj) { return d().bind <F, D4, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4)>
	D& bind() { return d().bind <F, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3, A4)>
	D& bind(T* obj) { return d().bind <T, M, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3, A4) const>
	D& bind(T const* obj) { return d().bind <T, M, term>(obj); }

	template <typename F>
	D& bind(F* obj) { return d().bind <F, term>(obj); }

	template <typename F>
	D& bind(F const* obj) { return d().bind <F, term>(obj); }

};

//-----------------------------------------------------------------------------

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5
>
class extend <R (A1, A2, A3, A4, A5)>
{
	typedef delegate <R (A1, A2, A3, A4, A5)> D;
	D& d() { return static_cast <D&>(*this); }

public:

//-----------------------------------------------------------------------------

	template <
		R (*F)(A1, A2, A3, A4, A5),
		typename D2, typename D3, typename D4, typename D5
	>
	D& bind() { return d().bind <F, D2, D3, D4, D5, term>(); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5),
		typename D2, typename D3, typename D4, typename D5
	>
	D& bind(T* obj) { return d().bind <T, M, D2, D3, D4, D5, term>(obj); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5) const,
		typename D2, typename D3, typename D4, typename D5
	>
	D& bind(T const* obj) { return d().bind <T, M, D2, D3, D4, D5, term>(obj); }

	template <typename F, typename D2, typename D3, typename D4, typename D5>
	D& bind(F* obj) { return d().bind <F, D2, D3, D4, D5, term>(obj); }

	template <typename F, typename D2, typename D3, typename D4, typename D5>
	D& bind(F const* obj) { return d().bind <F, D2, D3, D4, D5, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4, A5), typename D3, typename D4, typename D5>
	D& bind() { return d().bind <F, D3, D4, D5, term>(); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5),
		typename D3, typename D4, typename D5
	>
	D& bind(T* obj) { return d().bind <T, M, D3, D4, D5, term>(obj); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5) const,
		typename D3, typename D4, typename D5
	>
	D& bind(T const* obj) { return d().bind <T, M, D3, D4, D5, term>(obj); }

	template <typename F, typename D3, typename D4, typename D5>
	D& bind(F* obj) { return d().bind <F, D3, D4, D5, term>(obj); }

	template <typename F, typename D3, typename D4, typename D5>
	D& bind(F const* obj) { return d().bind <F, D3, D4, D5, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4, A5), typename D4, typename D5>
	D& bind() { return d().bind <F, D4, term>(); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5),
		typename D4, typename D5
	>
	D& bind(T* obj) { return d().bind <T, M, D4, D5, term>(obj); }

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5) const,
		typename D4, typename D5
	>
	D& bind(T const* obj) { return d().bind <T, M, D4, D5, term>(obj); }

	template <typename F, typename D4, typename D5>
	D& bind(F* obj) { return d().bind <F, D4, D5, term>(obj); }

	template <typename F, typename D4, typename D5>
	D& bind(F const* obj) { return d().bind <F, D4, D5, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4, A5), typename D5>
	D& bind() { return d().bind <F, D5, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3, A4, A5), typename D5>
	D& bind(T* obj) { return d().bind <T, M, D5, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3, A4, A5) const, typename D5>
	D& bind(T const* obj) { return d().bind <T, M, D5, term>(obj); }

	template <typename F, typename D5>
	D& bind(F* obj) { return d().bind <F, D5, term>(obj); }

	template <typename F, typename D5>
	D& bind(F const* obj) { return d().bind <F, D5, term>(obj); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4, A5)>
	D& bind() { return d().bind <F, term>(); }

	template <typename T, R (T::*M)(A1, A2, A3, A4, A5)>
	D& bind(T* obj) { return d().bind <T, M, term>(obj); }

	template <typename T, R (T::*M)(A1, A2, A3, A4, A5) const>
	D& bind(T const* obj) { return d().bind <T, M, term>(obj); }

	template <typename F>
	D& bind(F* obj) { return d().bind <F, term>(obj); }

	template <typename F>
	D& bind(F const* obj) { return d().bind <F, term>(obj); }

};

//-----------------------------------------------------------------------------

}  // namespace delegate_details

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_EXTEND_HPP
