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

#ifndef IVL_QT_CORE_BINDER_HPP
#define IVL_QT_CORE_BINDER_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

class no_direct { };
class no_base { };

//-----------------------------------------------------------------------------

template <typename T, typename P = no_direct, typename B = no_base>
class method_binder
{
	T* derived() { return static_cast <T*>(this); }
	T const* const_derived() const { return static_cast <T const*>(this); }

//-----------------------------------------------------------------------------

	template <typename S>
	class binder;

	template <typename S>
	class const_binder;

//-----------------------------------------------------------------------------

	template <typename R>
	class binder <R ()>
	{
		delegate <R ()>& del;
		T* obj;

	public:
		binder(delegate <R ()>& d, T* o) : del(d), obj(o) { }

		template <R (*F)   ()> void to() { del.bind <F>(); }
		template <R (T::*M)()> void to() { del.bind <T, M>(obj); }
		template <R (P::*M)()> void to() { del.bind <P, M>(obj); }
		template <R (B::*M)()> void to() { del.bind <B, M>(obj); }
		template <typename F>  void to() { del.bind <F>   (obj); }

		template <typename U, R (U::*M)()> void to() { del.bind <U, M>(obj); }
	};

	template <typename R>
	class const_binder <R ()>
	{
		delegate <R ()>& del;
		T const* obj;

	public:
		const_binder(delegate <R ()>& d, T const* o) : del(d), obj(o) { }

		template <R (*F)   ()>       void to() { del.bind <F>(); }
		template <R (T::*M)() const> void to() { del.bind <T, M>(obj); }
		template <R (P::*M)() const> void to() { del.bind <P, M>(obj); }
		template <R (B::*M)() const> void to() { del.bind <B, M>(obj); }
		template <typename F>        void to() { del.bind <F>   (obj); }

		template <typename U, R (U::*M)() const> void to() { del.bind <U, M>(obj); }
	};

//-----------------------------------------------------------------------------

	template <typename R, typename A1>
	class binder <R (A1)>
	{
		delegate <R (A1)>& del;
		T* obj;

	public:
		binder(delegate <R (A1)>& d, T* o) : del(d), obj(o) { }

		template <R (*F)   (A1)> void to() { to <F,    term>(); }
		template <R (T::*M)(A1)> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1)> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1)> void to() { to <B, M, term>(); }
		template <typename F>    void to() { to <F,    term>(); }

		template <R (*F)   (A1), typename D1> void to() { del.bind <F,    D1>(); }
		template <R (T::*M)(A1), typename D1> void to() { del.bind <T, M, D1>(obj); }
		template <R (P::*M)(A1), typename D1> void to() { del.bind <P, M, D1>(obj); }
		template <R (B::*M)(A1), typename D1> void to() { del.bind <B, M, D1>(obj); }
		template <typename F,    typename D1> void to() { del.bind <F,    D1>(obj); }

		template <typename U, R (U::*M)(A1)>              void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1), typename D1> void to() { del.bind <U, M, D1>(obj); }
	};

	template <typename R, typename A1>
	class const_binder <R (A1)>
	{
		delegate <R (A1)>& del;
		T const* obj;

	public:
		const_binder(delegate <R (A1)>& d, T const* o) : del(d), obj(o) { }

		template <R (*F)   (A1)>       void to() { to <F,    term>(); }
		template <R (T::*M)(A1) const> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1) const> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1) const> void to() { to <B, M, term>(); }
		template <typename F>          void to() { to <F,    term>(); }

		template <R (*F)   (A1),       typename D1> void to() { del.bind <F,    D1>(); }
		template <R (T::*M)(A1) const, typename D1> void to() { del.bind <T, M, D1>(obj); }
		template <R (P::*M)(A1) const, typename D1> void to() { del.bind <P, M, D1>(obj); }
		template <R (B::*M)(A1) const, typename D1> void to() { del.bind <B, M, D1>(obj); }
		template <typename F,          typename D1> void to() { del.bind <F,    D1>(obj); }

		template <typename U, R (U::*M)(A1) const>              void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1) const, typename D1> void to() { del.bind <U, M, D1>(obj); }
	};

//-----------------------------------------------------------------------------

	template <typename R, typename A1, typename A2>
	class binder <R (A1, A2)>
	{
		delegate <R (A1, A2)>& del;
		T* obj;

	public:
		binder(delegate <R (A1, A2)>& d, T* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2)> void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2)> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2)> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2)> void to() { to <B, M, term>(); }
		template <typename F>        void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2), typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2), typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2), typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2), typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,        typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2), typename D1, typename D2> void to() { del.bind <F,    D1, D2>(); }
		template <R (T::*M)(A1, A2), typename D1, typename D2> void to() { del.bind <T, M, D1, D2>(obj); }
		template <R (P::*M)(A1, A2), typename D1, typename D2> void to() { del.bind <P, M, D1, D2>(obj); }
		template <R (B::*M)(A1, A2), typename D1, typename D2> void to() { del.bind <B, M, D1, D2>(obj); }
		template <typename F,        typename D1, typename D2> void to() { del.bind <F,    D1, D2>(obj); }

		template <typename U, R (U::*M)(A1, A2)>                           void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2), typename D1>              void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2), typename D1, typename D2> void to() { del.bind <U, M, D1, D2>(obj); }
	};

	template <typename R, typename A1, typename A2>
	class const_binder <R (A1, A2)>
	{
		delegate <R (A1, A2)>& del;
		T const* obj;

	public:
		const_binder(delegate <R (A1, A2)>& d, T const* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2)>       void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2) const> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2) const> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2) const> void to() { to <B, M, term>(); }
		template <typename F>              void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2),       typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2) const, typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2) const, typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2) const, typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,              typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2),       typename D1, typename D2> void to() { del.bind <F,    D1, D2>(); }
		template <R (T::*M)(A1, A2) const, typename D1, typename D2> void to() { del.bind <T, M, D1, D2>(obj); }
		template <R (P::*M)(A1, A2) const, typename D1, typename D2> void to() { del.bind <P, M, D1, D2>(obj); }
		template <R (B::*M)(A1, A2) const, typename D1, typename D2> void to() { del.bind <B, M, D1, D2>(obj); }
		template <typename F,              typename D1, typename D2> void to() { del.bind <F,    D1, D2>(obj); }

		template <typename U, R (U::*M)(A1, A2) const>                           void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2) const, typename D1>              void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2) const, typename D1, typename D2> void to() { del.bind <U, M, D1, D2>(obj); }
	};

//-----------------------------------------------------------------------------

	template <typename R, typename A1, typename A2, typename A3>
	class binder <R (A1, A2, A3)>
	{
		delegate <R (A1, A2, A3)>& del;
		T* obj;

	public:
		binder(delegate <R (A1, A2, A3)>& d, T* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2, A3)> void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2, A3)> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2, A3)> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2, A3)> void to() { to <B, M, term>(); }
		template <typename F>            void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2, A3), typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2, A3), typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2, A3), typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2, A3), typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,            typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2, A3), typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }
		template <R (T::*M)(A1, A2, A3), typename D1, typename D2> void to() { to  <T, M, D1, D2, term>(); }
		template <R (P::*M)(A1, A2, A3), typename D1, typename D2> void to() { to  <P, M, D1, D2, term>(); }
		template <R (B::*M)(A1, A2, A3), typename D1, typename D2> void to() { to  <B, M, D1, D2, term>(); }
		template <typename F,            typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }

		template <R (*F)   (A1, A2, A3), typename D1, typename D2, typename D3> void to() { del.bind <F,    D1, D2, D3>(); }
		template <R (T::*M)(A1, A2, A3), typename D1, typename D2, typename D3> void to() { del.bind <T, M, D1, D2, D3>(obj); }
		template <R (P::*M)(A1, A2, A3), typename D1, typename D2, typename D3> void to() { del.bind <P, M, D1, D2, D3>(obj); }
		template <R (B::*M)(A1, A2, A3), typename D1, typename D2, typename D3> void to() { del.bind <B, M, D1, D2, D3>(obj); }
		template <typename F,            typename D1, typename D2, typename D3> void to() { del.bind <F,    D1, D2, D3>(obj); }

		template <typename U, R (U::*M)(A1, A2, A3)>                                        void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3), typename D1>                           void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3), typename D1, typename D2>              void to() { to <U, M, D1, D2, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3), typename D1, typename D2, typename D3> void to() { del.bind <U, M, D1, D2, D3>(obj); }
	};

	template <typename R, typename A1, typename A2, typename A3>
	class const_binder <R (A1, A2, A3)>
	{
		delegate <R (A1, A2, A3)>& del;
		T const* obj;

	public:
		const_binder(delegate <R (A1, A2, A3)>& d, T const* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2, A3)>       void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2, A3) const> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2, A3) const> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2, A3) const> void to() { to <B, M, term>(); }
		template <typename F>                  void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2, A3),       typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2, A3) const, typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2, A3) const, typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2, A3) const, typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,                  typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2, A3),       typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }
		template <R (T::*M)(A1, A2, A3) const, typename D1, typename D2> void to() { to  <T, M, D1, D2, term>(); }
		template <R (P::*M)(A1, A2, A3) const, typename D1, typename D2> void to() { to  <P, M, D1, D2, term>(); }
		template <R (B::*M)(A1, A2, A3) const, typename D1, typename D2> void to() { to  <B, M, D1, D2, term>(); }
		template <typename F,                  typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }

		template <R (*F)   (A1, A2, A3),       typename D1, typename D2, typename D3> void to() { del.bind <F,    D1, D2, D3>(); }
		template <R (T::*M)(A1, A2, A3) const, typename D1, typename D2, typename D3> void to() { del.bind <T, M, D1, D2, D3>(obj); }
		template <R (P::*M)(A1, A2, A3) const, typename D1, typename D2, typename D3> void to() { del.bind <P, M, D1, D2, D3>(obj); }
		template <R (B::*M)(A1, A2, A3) const, typename D1, typename D2, typename D3> void to() { del.bind <B, M, D1, D2, D3>(obj); }
		template <typename F,                  typename D1, typename D2, typename D3> void to() { del.bind <F,    D1, D2, D3>(obj); }

		template <typename U, R (U::*M)(A1, A2, A3) const>                                        void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3) const, typename D1>                           void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3) const, typename D1, typename D2>              void to() { to <U, M, D1, D2, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3) const, typename D1, typename D2, typename D3> void to() { del.bind <U, M, D1, D2, D3>(obj); }
	};

//-----------------------------------------------------------------------------

	template <typename R, typename A1, typename A2, typename A3, typename A4>
	class binder <R (A1, A2, A3, A4)>
	{
		delegate <R (A1, A2, A3, A4)>& del;
		T* obj;

	public:
		binder(delegate <R (A1, A2, A3, A4)>& d, T* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2, A3, A4)> void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2, A3, A4)> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2, A3, A4)> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2, A3, A4)> void to() { to <B, M, term>(); }
		template <typename F>                void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2, A3, A4), typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2, A3, A4), typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2, A3, A4), typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2, A3, A4), typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,                typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2, A3, A4), typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }
		template <R (T::*M)(A1, A2, A3, A4), typename D1, typename D2> void to() { to  <T, M, D1, D2, term>(); }
		template <R (P::*M)(A1, A2, A3, A4), typename D1, typename D2> void to() { to  <P, M, D1, D2, term>(); }
		template <R (B::*M)(A1, A2, A3, A4), typename D1, typename D2> void to() { to  <B, M, D1, D2, term>(); }
		template <typename F,                typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }

		template <R (*F)   (A1, A2, A3, A4), typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }
		template <R (T::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3> void to() { to <T, M, D1, D2, D3, term>(); }
		template <R (P::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3> void to() { to <P, M, D1, D2, D3, term>(); }
		template <R (B::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3> void to() { to <B, M, D1, D2, D3, term>(); }
		template <typename F,                typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }

		template <R (*F)   (A1, A2, A3, A4), typename D1, typename D2, typename D3, typename D4> void to() { del.bind <F,    D1, D2, D3, D4>(); }
		template <R (T::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3, typename D4> void to() { del.bind <T, M, D1, D2, D3, D4>(obj); }
		template <R (P::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3, typename D4> void to() { del.bind <P, M, D1, D2, D3, D4>(obj); }
		template <R (B::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3, typename D4> void to() { del.bind <B, M, D1, D2, D3, D4>(obj); }
		template <typename F,                typename D1, typename D2, typename D3, typename D4> void to() { del.bind <F,    D1, D2, D3, D4>(obj); }

		template <typename U, R (U::*M)(A1, A2, A3, A4)>                                                     void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4), typename D1>                                        void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4), typename D1, typename D2>                           void to() { to <U, M, D1, D2, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3>              void to() { to <U, M, D1, D2, D3, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4), typename D1, typename D2, typename D3, typename D4> void to() { del.bind <U, M, D1, D2, D3, D4>(obj); }
	};

	template <typename R, typename A1, typename A2, typename A3, typename A4>
	class const_binder <R (A1, A2, A3, A4)>
	{
		delegate <R (A1, A2, A3, A4)>& del;
		T const* obj;

	public:
		const_binder(delegate <R (A1, A2, A3, A4)>& d, T const* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2, A3, A4)>       void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2, A3, A4) const> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2, A3, A4) const> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2, A3, A4) const> void to() { to <B, M, term>(); }
		template <typename F>                      void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2, A3, A4),       typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2, A3, A4) const, typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2, A3, A4) const, typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2, A3, A4) const, typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,                      typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2, A3, A4),       typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }
		template <R (T::*M)(A1, A2, A3, A4) const, typename D1, typename D2> void to() { to  <T, M, D1, D2, term>(); }
		template <R (P::*M)(A1, A2, A3, A4) const, typename D1, typename D2> void to() { to  <P, M, D1, D2, term>(); }
		template <R (B::*M)(A1, A2, A3, A4) const, typename D1, typename D2> void to() { to  <B, M, D1, D2, term>(); }
		template <typename F,                      typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }

		template <R (*F)   (A1, A2, A3, A4),       typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }
		template <R (T::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3> void to() { to <T, M, D1, D2, D3, term>(); }
		template <R (P::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3> void to() { to <P, M, D1, D2, D3, term>(); }
		template <R (B::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3> void to() { to <B, M, D1, D2, D3, term>(); }
		template <typename F,                      typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }

		template <R (*F)   (A1, A2, A3, A4),       typename D1, typename D2, typename D3, typename D4> void to() { del.bind <F,    D1, D2, D3, D4>(); }
		template <R (T::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3, typename D4> void to() { del.bind <T, M, D1, D2, D3, D4>(obj); }
		template <R (P::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3, typename D4> void to() { del.bind <P, M, D1, D2, D3, D4>(obj); }
		template <R (B::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3, typename D4> void to() { del.bind <B, M, D1, D2, D3, D4>(obj); }
		template <typename F,                      typename D1, typename D2, typename D3, typename D4> void to() { del.bind <F,    D1, D2, D3, D4>(obj); }

		template <typename U, R (U::*M)(A1, A2, A3, A4) const>                                                     void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4) const, typename D1>                                        void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4) const, typename D1, typename D2>                           void to() { to <U, M, D1, D2, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3>              void to() { to <U, M, D1, D2, D3, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4) const, typename D1, typename D2, typename D3, typename D4> void to() { del.bind <U, M, D1, D2, D3, D4>(obj); }
	};

//-----------------------------------------------------------------------------

	template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
	class binder <R (A1, A2, A3, A4, A5)>
	{
		delegate <R (A1, A2, A3, A4, A5)>& del;
		T* obj;

	public:
		binder(delegate <R (A1, A2, A3, A4, A5)>& d, T* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2, A3, A4, A5)> void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5)> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5)> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5)> void to() { to <B, M, term>(); }
		template <typename F>                    void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5), typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5), typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5), typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5), typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,                    typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5), typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5), typename D1, typename D2> void to() { to  <T, M, D1, D2, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5), typename D1, typename D2> void to() { to  <P, M, D1, D2, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5), typename D1, typename D2> void to() { to  <B, M, D1, D2, term>(); }
		template <typename F,                    typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5), typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3> void to() { to <T, M, D1, D2, D3, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3> void to() { to <P, M, D1, D2, D3, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3> void to() { to <B, M, D1, D2, D3, term>(); }
		template <typename F,                    typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4> void to() { to <F,    D1, D2, D3, D4, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4> void to() { to <T, M, D1, D2, D3, D4, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4> void to() { to <P, M, D1, D2, D3, D4, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4> void to() { to <B, M, D1, D2, D3, D4, term>(); }
		template <typename F,                    typename D1, typename D2, typename D3, typename D4> void to() { to <F,    D1, D2, D3, D4, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <F,    D1, D2, D3, D4, D5>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <T, M, D1, D2, D3, D4, D5>(obj); }
		template <R (P::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <P, M, D1, D2, D3, D4, D5>(obj); }
		template <R (B::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <B, M, D1, D2, D3, D4, D5>(obj); }
		template <typename F,                    typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <F,    D1, D2, D3, D4, D5>(obj); }

		template <typename U, R (U::*M)(A1, A2, A3, A4, A5)>                                                                  void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5), typename D1>                                                     void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5), typename D1, typename D2>                                        void to() { to <U, M, D1, D2, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3>                           void to() { to <U, M, D1, D2, D3, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4>              void to() { to <U, M, D1, D2, D3, D4, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5), typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <U, M, D1, D2, D3, D4, D5>(obj); }
	};

	template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
	class const_binder <R (A1, A2, A3, A4, A5)>
	{
		delegate <R (A1, A2, A3, A4, A5)>& del;
		T const* obj;

	public:
		const_binder(delegate <R (A1, A2, A3, A4, A5)>& d, T const* o) : del(d), obj(o) { }

		template <R (*F)   (A1, A2, A3, A4, A5)>       void to() { to <F,    term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5) const> void to() { to <T, M, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5) const> void to() { to <P, M, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5) const> void to() { to <B, M, term>(); }
		template <typename F>                          void to() { to <F,    term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5),       typename D1> void to() { to <F,    D1, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5) const, typename D1> void to() { to <T, M, D1, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5) const, typename D1> void to() { to <P, M, D1, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5) const, typename D1> void to() { to <B, M, D1, term>(); }
		template <typename F,                          typename D1> void to() { to <F,    D1, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5),       typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2> void to() { to  <T, M, D1, D2, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2> void to() { to  <P, M, D1, D2, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2> void to() { to  <B, M, D1, D2, term>(); }
		template <typename F,                          typename D1, typename D2> void to() { to  <F,    D1, D2, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5),       typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3> void to() { to <T, M, D1, D2, D3, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3> void to() { to <P, M, D1, D2, D3, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3> void to() { to <B, M, D1, D2, D3, term>(); }
		template <typename F,                          typename D1, typename D2, typename D3> void to() { to <F,    D1, D2, D3, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5),       typename D1, typename D2, typename D3, typename D4> void to() { to <F,    D1, D2, D3, D4, term>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4> void to() { to <T, M, D1, D2, D3, D4, term>(); }
		template <R (P::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4> void to() { to <P, M, D1, D2, D3, D4, term>(); }
		template <R (B::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4> void to() { to <B, M, D1, D2, D3, D4, term>(); }
		template <typename F,                          typename D1, typename D2, typename D3, typename D4> void to() { to <F,    D1, D2, D3, D4, term>(); }

		template <R (*F)   (A1, A2, A3, A4, A5),       typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <F,    D1, D2, D3, D4, D5>(); }
		template <R (T::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <T, M, D1, D2, D3, D4, D5>(obj); }
		template <R (P::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <P, M, D1, D2, D3, D4, D5>(obj); }
		template <R (B::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <B, M, D1, D2, D3, D4, D5>(obj); }
		template <typename F,                          typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <F,    D1, D2, D3, D4, D5>(obj); }

		template <typename U, R (U::*M)(A1, A2, A3, A4, A5) const>                                                                  void to() { to <U, M, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5) const, typename D1>                                                     void to() { to <U, M, D1, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2>                                        void to() { to <U, M, D1, D2, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3>                           void to() { to <U, M, D1, D2, D3, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4>              void to() { to <U, M, D1, D2, D3, D4, term>(); }
		template <typename U, R (U::*M)(A1, A2, A3, A4, A5) const, typename D1, typename D2, typename D3, typename D4, typename D5> void to() { del.bind <U, M, D1, D2, D3, D4, D5>(obj); }
	};

public:

//-----------------------------------------------------------------------------

	template <typename D>
	binder <typename D::signature_type>
	bind(D& d)
	{
		typedef typename D::signature_type S;
		return binder <S>(d.raw(), derived());
	}

	template <typename D>
	const_binder <typename D::signature_type>
	const_bind(D& d) const
	{
		typedef typename D::signature_type S;
		return const_binder <S>(d.raw(), const_derived());
	}

};

//-----------------------------------------------------------------------------

}  // namespace delegate_details

using delegate_details::method_binder;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_BINDER_HPP
