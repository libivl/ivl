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

#ifndef IVL_QT_CORE_STUB_HPP
#define IVL_QT_CORE_STUB_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

struct NO { };
struct YES { };

template <typename T>
T* cast(void* obj) { return static_cast <T*>(obj); }

template <typename T>
T const* ccast(void* obj) { return static_cast <T*>(obj); }

template <typename T>
T* cast(void* obj, NO) { return cast <T>(obj); }

template <typename T>
T const* cast(void* obj, YES) { return ccast <T>(obj); }

//-----------------------------------------------------------------------------

template <typename S>
struct stub;

//-----------------------------------------------------------------------------

template <typename R>
struct stub <R ()>
{
	template <R (*F)()>
	struct function
	{
		static R call(void*) { return F(); }
	};

	template <typename T, R (T::*M)()>
	struct method
	{
		static R call(void* obj) { return (cast <T>(obj)->*M)(); }
	};

	template <typename T, R (T::*M)() const>
	struct const_method
	{
		static R call(void* obj) { return (ccast <T>(obj)->*M)(); }
	};

	template <typename F, typename C>
	struct functor
	{
		static R call(void* obj) { (*cast <F>(obj, C()))(); return R(); }
	};

};

//-----------------------------------------------------------------------------

template <typename R, typename A1>
struct stub <R (A1)>
{
	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);

	template <typename V>
	struct base
	{
		template <typename L>
		static void* get() { L l = V::op; return reinterpret_cast <void*>(l); }

		static void* get(const unsigned n)
		{
			typedef void* (*G)();
			static G table[] = { get <L0>, get <L1> };
			return (*table[n])();
		}
	};

//-----------------------------------------------------------------------------

	template <typename B, typename D1 = term>
	struct overload : base <overload <B, D1> >
	{
		static R op(void* obj)        { return op(obj, D1()()); }
		static R op(void* obj, A1 a1) { return B::call(obj, a1); }
	};

	template <typename B>
	struct overload <B> : base <overload <B> >
	{
		static R op(void*)            { return R(); }
		static R op(void* obj, A1 a1) { return B::call(obj, a1); }
	};

//-----------------------------------------------------------------------------

	template <R (*F)(A1), typename D1 = term>
	struct function : overload <function <F>, D1>
	{
		static R call(void*, A1 a1) { return F(a1); }
	};

	template <typename T, R (T::*M)(A1), typename D1 = term>
	struct method : overload <method <T, M>, D1>
	{
		static R call(void* obj, A1 a1) { return (cast <T>(obj)->*M)(a1); }
	};

	template <typename T, R (T::*M)(A1) const, typename D1 = term>
	struct const_method : overload <const_method <T, M>, D1>
	{
		static R call(void* obj, A1 a1) { return (ccast <T>(obj)->*M)(a1); }
	};

	template <typename F, typename C, typename D1 = term>
	struct functor : overload <functor <F, C>, D1>
	{
		static R call(void* obj, A1 a1)
			{ (*cast <F>(obj, C()))(a1); return R(); }
	};

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2>
struct stub <R (A1, A2)>
{
	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);

	template <typename V>
	struct base
	{
		template <typename L>
		static void* get() { L l = V::op; return reinterpret_cast <void*>(l); }

		static void* get(const unsigned n)
		{
			typedef void* (*G)();
			static G table[] = { get <L0>, get <L1>, get <L2> };
			return (*table[n])();
		}
	};

//-----------------------------------------------------------------------------

	template <typename B, typename D1 = term, typename D2 = term>
	struct overload : base <overload <B, D1, D2> >
	{
		static R op(void* obj)               { return op(obj, D1()(), D2()()); }
		static R op(void* obj, A1 a1)        { return op(obj, a1, D2()()); }
		static R op(void* obj, A1 a1, A2 a2) { return B::call(obj, a1, a2); }
	};

	template <typename B, typename D2>
	struct overload <B, D2> : base <overload <B, D2> >
	{
		static R op(void*)                   { return R(); }
		static R op(void* obj, A1 a1)        { return op(obj, a1, D2()()); }
		static R op(void* obj, A1 a1, A2 a2) { return B::call(obj, a1, a2); }
	};

	template <typename B>
	struct overload <B> : base <overload <B> >
	{
		static R op(void*)                   { return R(); }
		static R op(void*, A1)               { return R(); }
		static R op(void* obj, A1 a1, A2 a2) { return B::call(obj, a1, a2); }
	};

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2), typename D1 = term, typename D2 = term>
	struct function : overload <function <F>, D1, D2>
	{
		static R call(void*, A1 a1, A2 a2) { return F(a1, a2); }
	};

	template <
		typename T, R (T::*M)(A1, A2),
		typename D1 = term, typename D2 = term
	>
	struct method : overload <method <T, M>, D1, D2>
	{
		static R call(void* obj, A1 a1, A2 a2)
			{ return (cast <T>(obj)->*M)(a1, a2); }
	};

	template <
		typename T, R (T::*M)(A1, A2) const,
		typename D1 = term, typename D2 = term
	>
	struct const_method : overload <const_method <T, M>, D1, D2>
	{
		static R call(void* obj, A1 a1, A2 a2)
			{ return (ccast <T>(obj)->*M)(a1, a2); }
	};

	template <typename F, typename C, typename D1 = term, typename D2 = term>
	struct functor : overload <functor <F, C>, D1, D2>
	{
		static R call(void* obj, A1 a1, A2 a2)
			{ (*cast <F>(obj, C()))(a1, a2); return R(); }
	};

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3>
struct stub <R (A1, A2, A3)>
{
	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);
	typedef R (*L3)(void*, A1, A2, A3);

	template <typename V>
	struct base
	{
		template <typename L>
		static void* get() { L l = V::op; return reinterpret_cast <void*>(l); }

		static void* get(const unsigned n)
		{
			typedef void* (*G)();
			static G table[] = { get <L0>, get <L1>, get <L2>, get <L3> };
			return (*table[n])();
		}
	};

//-----------------------------------------------------------------------------

	template <
		typename B,
		typename D1 = term, typename D2 = term, typename D3 = term
	>
	struct overload : base <overload <B, D1, D2, D3> >
	{
		static R op(void* obj)                      { return op(obj, D1()(), D2()(), D3()()); }
		static R op(void* obj, A1 a1)               { return op(obj, a1, D2()(), D3()()); }
		static R op(void* obj, A1 a1, A2 a2)        { return op(obj, a1, a2, D3()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3) { return B::call(obj, a1, a2, a3); }
	};

	template <typename B, typename D2, typename D3>
	struct overload <B, D2, D3> : base <overload <B, D2, D3> >
	{
		static R op(void*)                          { return R(); }
		static R op(void* obj, A1 a1)               { return op(obj, a1, D2()(), D3()()); }
		static R op(void* obj, A1 a1, A2 a2)        { return op(obj, a1, a2, D3()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3) { return B::call(obj, a1, a2, a3); }
	};

	template <typename B, typename D3>
	struct overload <B, D3> : base <overload <B, D3> >
	{
		static R op(void*)                          { return R(); }
		static R op(void*, A1)                      { return R(); }
		static R op(void* obj, A1 a1, A2 a2)        { return op(obj, a1, a2, D3()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3) { return B::call(obj, a1, a2, a3); }
	};

	template <typename B>
	struct overload <B> : base <overload <B> >
	{
		static R op(void*)                          { return R(); }
		static R op(void*, A1)                      { return R(); }
		static R op(void*, A1, A2)                  { return R(); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3) { return B::call(obj, a1, a2, a3); }
	};

//-----------------------------------------------------------------------------

	template <
		R (*F)(A1, A2, A3),
		typename D1 = term, typename D2 = term, typename D3 = term
	>
	struct function : overload <function <F>, D1, D2, D3>
	{
		static R call(void*, A1 a1, A2 a2, A3 a3) { return F(a1, a2, a3); }
	};

	template <
		typename T, R (T::*M)(A1, A2, A3),
		typename D1 = term, typename D2 = term, typename D3 = term
	>
	struct method : overload <method <T, M>, D1, D2, D3>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3)
			{ return (cast <T>(obj)->*M)(a1, a2, a3); }
	};

	template <
		typename T, R (T::*M)(A1, A2, A3) const,
		typename D1 = term, typename D2 = term, typename D3 = term
	>
	struct const_method : overload <const_method <T, M>, D1, D2, D3>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3)
			{ return (ccast <T>(obj)->*M)(a1, a2, a3); }
	};

	template <
		typename F, typename C,
		typename D1 = term, typename D2 = term, typename D3 = term
	>
	struct functor : overload <functor <F, C>, D1, D2, D3>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3)
			{ (*cast <F>(obj, C()))(a1, a2, a3); return R(); }
	};

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3, typename A4>
struct stub <R (A1, A2, A3, A4)>
{
	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);
	typedef R (*L3)(void*, A1, A2, A3);
	typedef R (*L4)(void*, A1, A2, A3, A4);

	template <typename V>
	struct base
	{
		template <typename L>
		static void* get() { L l = V::op; return reinterpret_cast <void*>(l); }

		static void* get(const unsigned n)
		{
			typedef void* (*G)();
			static G table[] = { get <L0>, get <L1>, get <L2>, get <L3>, get <L4> };
			return (*table[n])();
		}
	};

//-----------------------------------------------------------------------------

	template <
		typename B,
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term
	>
	struct overload : base <overload <B, D1, D2, D3, D4> >
	{
		static R op(void* obj)                             { return op(obj, D1()(), D2()(), D3()(), D4()()); }
		static R op(void* obj, A1 a1)                      { return op(obj, a1, D2()(), D3()(), D4()()); }
		static R op(void* obj, A1 a1, A2 a2)               { return op(obj, a1, a2, D3()(), D4()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)        { return op(obj, a1, a2, a3, D4()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4) { return B::call(obj, a1, a2, a3, a4); }
	};

	template <typename B, typename D2, typename D3, typename D4>
	struct overload <B, D2, D3, D4> : base <overload <B, D2, D3, D4> >
	{
		static R op(void*)                                 { return R(); }
		static R op(void* obj, A1 a1)                      { return op(obj, a1, D2()(), D3()(), D4()()); }
		static R op(void* obj, A1 a1, A2 a2)               { return op(obj, a1, a2, D3()(), D4()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)        { return op(obj, a1, a2, a3, D4()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4) { return B::call(obj, a1, a2, a3, a4); }
	};

	template <typename B, typename D3, typename D4>
	struct overload <B, D3, D4> : base <overload <B, D3, D4> >
	{
		static R op(void*)                                 { return R(); }
		static R op(void*, A1)                             { return R(); }
		static R op(void* obj, A1 a1, A2 a2)               { return op(obj, a1, a2, D3()(), D4()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)        { return op(obj, a1, a2, a3, D4()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4) { return B::call(obj, a1, a2, a3, a4); }
	};

	template <typename B, typename D4>
	struct overload <B, D4> : base <overload <B, D4> >
	{
		static R op(void*)                                 { return R(); }
		static R op(void*, A1)                             { return R(); }
		static R op(void*, A1, A2)                         { return R(); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)        { return op(obj, a1, a2, a3, D4()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4) { return B::call(obj, a1, a2, a3, a4); }
	};

	template <typename B>
	struct overload <B> : base <overload <B> >
	{
		static R op(void*)                                 { return R(); }
		static R op(void*, A1)                             { return R(); }
		static R op(void*, A1, A2)                         { return R(); }
		static R op(void*, A1, A2, A3)                     { return R(); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4) { return B::call(obj, a1, a2, a3, a4); }
	};

//-----------------------------------------------------------------------------

	template <
		R (*F)(A1, A2, A3, A4),
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term
	>
	struct function : overload <function <F>, D1, D2, D3, D4>
	{
		static R call(void*, A1 a1, A2 a2, A3 a3, A4 a4)
			{ return F(a1, a2, a3, a4); }
	};

	template <
		typename T, R (T::*M)(A1, A2, A3, A4),
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term
	>
	struct method : overload <method <T, M>, D1, D2, D3, D4>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)
			{ return (cast <T>(obj)->*M)(a1, a2, a3, a4); }
	};

	template <
		typename T, R (T::*M)(A1, A2, A3, A4) const,
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term
	>
	struct const_method : overload <const_method <T, M>, D1, D2, D3, D4>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)
			{ return (ccast <T>(obj)->*M)(a1, a2, a3, a4); }
	};

	template <
		typename F, typename C,
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term
	>
	struct functor : overload <functor <F, C>, D1, D2, D3, D4>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)
			{ (*cast <F>(obj, C()))(a1, a2, a3, a4); return R(); }
	};

};

//-----------------------------------------------------------------------------

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5
>
struct stub <R (A1, A2, A3, A4, A5)>
{
	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);
	typedef R (*L3)(void*, A1, A2, A3);
	typedef R (*L4)(void*, A1, A2, A3, A4);
	typedef R (*L5)(void*, A1, A2, A3, A4, A5);

	template <typename V>
	struct base
	{
		template <typename L>
		static void* get() { L l = V::op; return reinterpret_cast <void*>(l); }

		static void* get(const unsigned n)
		{
			typedef void* (*G)();
			static G table[] =
			{
				get <L0>, get <L1>, get <L2>, get <L3>, get <L4> , get <L5>
			};
			return (*table[n])();
		}
	};

//-----------------------------------------------------------------------------

	template <
		typename B,
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term, typename D5 = term
	>
	struct overload : base <overload <B, D1, D2, D3, D4, D5> >
	{
		static R op(void* obj)                                    { return op(obj, D1()(), D2()(), D3()(), D4()(), D5()()); }
		static R op(void* obj, A1 a1)                             { return op(obj, a1, D2()(), D3()(), D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2)                      { return op(obj, a1, a2, D3()(), D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)               { return op(obj, a1, a2, a3, D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)        { return op(obj, a1, a2, a3, a4, D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return B::call(obj, a1, a2, a3, a4, a5); }
	};

	template <typename B, typename D2, typename D3, typename D4, typename D5>
	struct overload <B, D2, D3, D4, D5> : base <overload <B, D2, D3, D4, D5> >
	{
		static R op(void*)                                        { return R(); }
		static R op(void* obj, A1 a1)                             { return op(obj, a1, D2()(), D3()(), D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2)                      { return op(obj, a1, a2, D3()(), D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)               { return op(obj, a1, a2, a3, D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)        { return op(obj, a1, a2, a3, a4, D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return B::call(obj, a1, a2, a3, a4, a5); }
	};

	template <typename B, typename D3, typename D4, typename D5>
	struct overload <B, D3, D4, D5> : base <overload <B, D3, D4, D5> >
	{
		static R op(void*)                                        { return R(); }
		static R op(void*, A1)                                    { return R(); }
		static R op(void* obj, A1 a1, A2 a2)                      { return op(obj, a1, a2, D3()(), D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)               { return op(obj, a1, a2, a3, D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)        { return op(obj, a1, a2, a3, a4, D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return B::call(obj, a1, a2, a3, a4, a5); }
	};

	template <typename B, typename D4, typename D5>
	struct overload <B, D4, D5> : base <overload <B, D4, D5> >
	{
		static R op(void*)                                        { return R(); }
		static R op(void*, A1)                                    { return R(); }
		static R op(void*, A1, A2)                                { return R(); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3)               { return op(obj, a1, a2, a3, D4()(), D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)        { return op(obj, a1, a2, a3, a4, D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return B::call(obj, a1, a2, a3, a4, a5); }
	};

	template <typename B, typename D5>
	struct overload <B, D5> : base <overload <B, D5> >
	{
		static R op(void*)                                        { return R(); }
		static R op(void*, A1)                                    { return R(); }
		static R op(void*, A1, A2)                                { return R(); }
		static R op(void*, A1, A2, A3)                            { return R(); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4)        { return op(obj, a1, a2, a3, a4, D5()()); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return B::call(obj, a1, a2, a3, a4, a5); }
	};

	template <typename B>
	struct overload <B> : base <overload <B> >
	{
		static R op(void*)                                        { return R(); }
		static R op(void*, A1)                                    { return R(); }
		static R op(void*, A1, A2)                                { return R(); }
		static R op(void*, A1, A2, A3)                            { return R(); }
		static R op(void*, A1, A2, A3, A4)                        { return R(); }
		static R op(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) { return B::call(obj, a1, a2, a3, a4, a5); }
	};

//-----------------------------------------------------------------------------

	template <
		R (*F)(A1, A2, A3, A4, A5),
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term, typename D5 = term
	>
	struct function : overload <function <F>, D1, D2, D3, D4, D5>
	{
		static R call(void*, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
			{ return F(a1, a2, a3, a4, a5); }
	};

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5),
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term, typename D5 = term
	>
	struct method : overload <method <T, M>, D1, D2, D3, D4, D5>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
			{ return (cast <T>(obj)->*M)(a1, a2, a3, a4, a5); }
	};

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5) const,
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term, typename D5 = term
	>
	struct const_method : overload <const_method <T, M>, D1, D2, D3, D4, D5>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
			{ return (ccast <T>(obj)->*M)(a1, a2, a3, a4, a5); }
	};

	template <
		typename F, typename C,
		typename D1 = term, typename D2 = term, typename D3 = term,
		typename D4 = term, typename D5 = term
	>
	struct functor : overload <functor <F, C>, D1, D2, D3, D4, D5>
	{
		static R call(void* obj, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
			{ (*cast <F>(obj, C()))(a1, a2, a3, a4, a5); return R(); }
	};

};

//-----------------------------------------------------------------------------

}  // namespace delegate_details

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_STUB_HPP
