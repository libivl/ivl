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

#ifndef IVL_QT_CORE_DELEGATE_HPP
#define IVL_QT_CORE_DELEGATE_HPP

namespace ivl {

//-----------------------------------------------------------------------------
// based on code by Sergey Ryazanov
// http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

template <typename S>
class invoker;

//-----------------------------------------------------------------------------

template <typename R>
class delegate <R ()>
{
	typedef R S();
	typedef invoker <S> I;
	typedef stub <S> U;
	typedef R (*C)(void*);

	void* obj;
	C call;

	delegate& init(void* o, C c) { obj = o; call = c; return *this; }

	template <typename T>
	delegate& cinit(T const* o, C c) { return init(const_cast <T*>(o), c); }

public:  // protected

	virtual R operate() const { return (*call)(obj); }

public:

//-----------------------------------------------------------------------------

	typedef R return_type;
	typedef S signature_type;
	typedef I invoker_type;

	delegate() : obj(0), call(0) { }
	delegate& raw() { return *this; }

	operator bool()  const { return call != 0; }
	bool operator!() const { return call == 0; }

	virtual R operator()() const { return operate(); }

	template <typename E1>
	R operator()(E1, ...) const { return operate(); }

//-----------------------------------------------------------------------------

	delegate& bind(delegate const* d) { return *this = *d; }

	delegate& unbind() { return init(0, 0); }

	template <typename Z>
	delegate <Z> adapt() const { return delegate <Z>().bind(this); }

//-----------------------------------------------------------------------------

	template <R (*F)()>
	delegate& bind() { return init(0, &U::template function <F>::call); }

	template <typename T, R (T::*M)()>
	delegate& bind(T* obj)
	{
		return init(obj, &U::template method <T, M>::call);
	}

	template <typename T, R (T::*M)() const>
	delegate& bind(T const* obj)
	{
		return cinit(obj, &U::template const_method <T, M>::call);
	}

	template <typename F>
	delegate& bind(F* obj)
	{
		return init(obj, &U::template functor <F, NO>::call);
	}

	template <typename F>
	delegate& bind(F const* obj)
	{
		return cinit(obj, &U::template functor <F, YES>::call);
	}

};

//-----------------------------------------------------------------------------

template <typename R, typename A1>
class delegate <R (A1)> : public extend <R (A1)>
{
	typedef R S(A1);
	typedef invoker <S> I;
	typedef stub <S> U;

	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef void* (*G)(const unsigned);

	void* obj;
	G get;

	delegate& init(void* o, G g) { obj = o; get = g; return *this; }

	template <typename T>
	delegate& cinit(T const* o, G g) { return init(const_cast <T*>(o), g); }

	template <typename L>
	L load(const unsigned n) const { return reinterpret_cast <L>((*get)(n)); }

public:  // protected

	virtual R operate()      const { return (*load <L0>(0))(obj); }
	virtual R operate(A1 a1) const { return (*load <L1>(1))(obj, a1); }

public:

//-----------------------------------------------------------------------------

	typedef R return_type;
	typedef S signature_type;
	typedef I invoker_type;

	delegate() : obj(0), get(0) { }
	delegate& raw() { return *this; }

	operator bool()  const { return get != 0; }
	bool operator!() const { return get == 0; }

	virtual R operator()()      const { return operate(); }
	virtual R operator()(A1 a1) const { return operate(a1); }

	template <typename E1>
	R operator()(A1 a1, E1, ...) const { return operate(a1); }

//-----------------------------------------------------------------------------

	using extend <R (A1)>::bind;
	delegate& bind(delegate const* d) { return *this = *d; }

	delegate& unbind() { return init(0, 0); }

	template <typename Z>
	delegate <Z> adapt() const { return delegate <Z>().bind(this); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1), typename D1>
	delegate& bind() { return init(0, &U::template function <F, D1>::get); }

	template <typename T, R (T::*M)(A1), typename D1>
	delegate& bind(T* obj)
	{
		return init(obj, &U::template method <T, M, D1>::get);
	}

	template <typename T, R (T::*M)(A1) const, typename D1>
	delegate& bind(T const* obj)
	{
		return cinit(obj, &U::template const_method <T, M, D1>::get);
	}

	template <typename F, typename D1>
	delegate& bind(F* obj)
	{
		return init(obj, &U::template functor <F, NO, D1>::get);
	}

	template <typename F, typename D1>
	delegate& bind(F const* obj)
	{
		return cinit(obj, &U::template functor <F, YES, D1>::get);
	}

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2>
class delegate <R (A1, A2)> : public extend <R (A1, A2)>
{
	typedef R S(A1, A2);
	typedef invoker <S> I;
	typedef stub <S> U;

	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);
	typedef void* (*G)(const unsigned);

	void* obj;
	G get;

	delegate& init(void* o, G g) { obj = o; get = g; return *this; }

	template <typename T>
	delegate& cinit(T const* o, G g) { return init(const_cast <T*>(o), g); }

	template <typename L>
	L load(const unsigned n) const { return reinterpret_cast <L>((*get)(n)); }

public:  // protected

	virtual R operate()             const { return (*load <L0>(0))(obj); }
	virtual R operate(A1 a1)        const { return (*load <L1>(1))(obj, a1); }
	virtual R operate(A1 a1, A2 a2) const { return (*load <L2>(2))(obj, a1, a2); }

public:

//-----------------------------------------------------------------------------

	typedef R return_type;
	typedef S signature_type;
	typedef I invoker_type;

	delegate() : obj(0), get(0) { }
	delegate& raw() { return *this; }

	operator bool()  const { return get != 0; }
	bool operator!() const { return get == 0; }

	virtual R operator()()             const { return operate(); }
	virtual R operator()(A1 a1)        const { return operate(a1); }
	virtual R operator()(A1 a1, A2 a2) const { return operate(a1, a2); }

	template <typename E1>
	R operator()(A1 a1, A2 a2, E1, ...) const { return operate(a1, a2); }

//-----------------------------------------------------------------------------

	using extend <R (A1, A2)>::bind;
	delegate& bind(delegate const* d) { return *this = *d; }

	delegate& unbind() { return init(0, 0); }

	template <typename Z>
	delegate <Z> adapt() const { return delegate <Z>().bind(this); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2), typename D1, typename D2>
	delegate& bind()
	{
		return init(0, &U::template function <F, D1, D2>::get);
	}

	template <typename T, R (T::*M)(A1, A2), typename D1, typename D2>
	delegate& bind(T* obj)
	{
		return init(obj, &U::template method <T, M, D1, D2>::get);
	}

	template <typename T, R (T::*M)(A1, A2) const, typename D1, typename D2>
	delegate& bind(T const* obj)
	{
		return cinit(obj, &U::template const_method <T, M, D1, D2>::get);
	}

	template <typename F, typename D1, typename D2>
	delegate& bind(F* obj)
	{
		return init(obj, &U::template functor <F, NO, D1, D2>::get);
	}

	template <typename F, typename D1, typename D2>
	delegate& bind(F const* obj)
	{
		return cinit(obj, &U::template functor <F, YES, D1, D2>::get);
	}

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3>
class delegate <R (A1, A2, A3)> : public extend <R (A1, A2, A3)>
{
	typedef R S(A1, A2, A3);
	typedef invoker <S> I;
	typedef stub <S> U;

	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);
	typedef R (*L3)(void*, A1, A2, A3);
	typedef void* (*G)(const unsigned);

	void* obj;
	G get;

	delegate& init(void* o, G g) { obj = o; get = g; return *this; }

	template <typename T>
	delegate& cinit(T const* o, G g) { return init(const_cast <T*>(o), g); }

	template <typename L>
	L load(const unsigned n) const { return reinterpret_cast <L>((*get)(n)); }

public:  // protected

	virtual R operate()                    const { return (*load <L0>(0))(obj); }
	virtual R operate(A1 a1)               const { return (*load <L1>(1))(obj, a1); }
	virtual R operate(A1 a1, A2 a2)        const { return (*load <L2>(2))(obj, a1, a2); }
	virtual R operate(A1 a1, A2 a2, A3 a3) const { return (*load <L3>(3))(obj, a1, a2, a3); }

public:

//-----------------------------------------------------------------------------

	typedef R return_type;
	typedef S signature_type;
	typedef I invoker_type;

	delegate() : obj(0), get(0) { }
	delegate& raw() { return *this; }

	operator bool()  const { return get != 0; }
	bool operator!() const { return get == 0; }

	virtual R operator()()                    const { return operate(); }
	virtual R operator()(A1 a1)               const { return operate(a1); }
	virtual R operator()(A1 a1, A2 a2)        const { return operate(a1, a2); }
	virtual R operator()(A1 a1, A2 a2, A3 a3) const { return operate(a1, a2, a3); }

	template <typename E1>
	R operator()(A1 a1, A2 a2, A3 a3, E1, ...) const { return operate(a1, a2, a3); }

//-----------------------------------------------------------------------------

	using extend <R (A1, A2, A3)>::bind;
	delegate& bind(delegate const* d) { return *this = *d; }

	delegate& unbind() { return init(0, 0); }

	template <typename Z>
	delegate <Z> adapt() const { return delegate <Z>().bind(this); }

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3), typename D1, typename D2, typename D3>
	delegate& bind()
	{
		return init(0, &U::template function <F, D1, D2, D3>::get);
	}

	template <
		typename T, R (T::*M)(A1, A2, A3),
		typename D1, typename D2, typename D3
	>
	delegate& bind(T* obj)
	{
		return init(obj, &U::template method <T, M, D1, D2, D3>::get);
	}

	template <
		typename T, R (T::*M)(A1, A2, A3) const,
		typename D1, typename D2, typename D3
	>
	delegate& bind(T const* obj)
	{
		return cinit(obj, &U::template const_method <T, M, D1, D2, D3>::get);
	}

	template <typename F, typename D1, typename D2, typename D3>
	delegate& bind(F* obj)
	{
		return init(obj, &U::template functor <F, NO, D1, D2, D3>::get);
	}

	template <typename F, typename D1, typename D2, typename D3>
	delegate& bind(F const* obj)
	{
		return cinit(obj, &U::template functor <F, YES, D1, D2, D3>::get);
	}

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3, typename A4>
class delegate <R (A1, A2, A3, A4)> : public extend <R (A1, A2, A3, A4)>
{
	typedef R S(A1, A2, A3, A4);
	typedef invoker <S> I;
	typedef stub <S> U;

	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);
	typedef R (*L3)(void*, A1, A2, A3);
	typedef R (*L4)(void*, A1, A2, A3, A4);
	typedef void* (*G)(const unsigned);

	void* obj;
	G get;

	delegate& init(void* o, G g) { obj = o; get = g; return *this; }

	template <typename T>
	delegate& cinit(T const* o, G g) { return init(const_cast <T*>(o), g); }

	template <typename L>
	L load(const unsigned n) const { return reinterpret_cast <L>((*get)(n)); }

public:  // protected

	virtual R operate()                           const { return (*load <L0>(0))(obj); }
	virtual R operate(A1 a1)                      const { return (*load <L1>(1))(obj, a1); }
	virtual R operate(A1 a1, A2 a2)               const { return (*load <L2>(2))(obj, a1, a2); }
	virtual R operate(A1 a1, A2 a2, A3 a3)        const { return (*load <L3>(3))(obj, a1, a2, a3); }
	virtual R operate(A1 a1, A2 a2, A3 a3, A4 a4) const { return (*load <L4>(4))(obj, a1, a2, a3, a4); }

public:

//-----------------------------------------------------------------------------

	typedef R return_type;
	typedef S signature_type;
	typedef I invoker_type;

	delegate() : obj(0), get(0) { }
	delegate& raw() { return *this; }

	operator bool()  const { return get != 0; }
	bool operator!() const { return get == 0; }

	virtual R operator()()                           const { return operate(); }
	virtual R operator()(A1 a1)                      const { return operate(a1); }
	virtual R operator()(A1 a1, A2 a2)               const { return operate(a1, a2); }
	virtual R operator()(A1 a1, A2 a2, A3 a3)        const { return operate(a1, a2, a3); }
	virtual R operator()(A1 a1, A2 a2, A3 a3, A4 a4) const { return operate(a1, a2, a3, a4); }

	template <typename E1>
	R operator()(A1 a1, A2 a2, A3 a3, A4 a4, E1, ...) const { return operate(a1, a2, a3, a4); }

//-----------------------------------------------------------------------------

	using extend <R (A1, A2, A3, A4)>::bind;
	delegate& bind(delegate const* d) { return *this = *d; }

	delegate& unbind() { return init(0, 0); }

	template <typename Z>
	delegate <Z> adapt() const { return delegate <Z>().bind(this); }

//-----------------------------------------------------------------------------

	template <
		R (*F)(A1, A2, A3, A4),
		typename D1, typename D2, typename D3, typename D4
	>
	delegate& bind()
	{
		return init(0, &U::template function <F, D1, D2, D3, D4>::get);
	}

	template <
		typename T, R (T::*M)(A1, A2, A3, A4),
		typename D1, typename D2, typename D3, typename D4
	>
	delegate& bind(T* obj)
	{
		return init(obj, &U::template method <T, M, D1, D2, D3, D4>::get);
	}

	template <
		typename T, R (T::*M)(A1, A2, A3, A4) const,
		typename D1, typename D2, typename D3, typename D4
	>
	delegate& bind(T const* obj)
	{
		return cinit(obj, &U::template const_method <T, M, D1, D2, D3, D4>::get);
	}

	template <typename F, typename D1, typename D2, typename D3, typename D4>
	delegate& bind(F* obj)
	{
		return init(obj, &U::template functor <F, NO, D1, D2, D3, D4>::get);
	}

	template <typename F, typename D1, typename D2, typename D3, typename D4>
	delegate& bind(F const* obj)
	{
		return cinit(obj, &U::template functor <F, YES, D1, D2, D3, D4>::get);
	}

};

//-----------------------------------------------------------------------------

template <
	typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5
>
class delegate <R (A1, A2, A3, A4, A5)> :
	public extend <R (A1, A2, A3, A4, A5)>
{
	typedef R S(A1, A2, A3, A4, A5);
	typedef invoker <S> I;
	typedef stub <S> U;

	typedef R (*L0)(void*);
	typedef R (*L1)(void*, A1);
	typedef R (*L2)(void*, A1, A2);
	typedef R (*L3)(void*, A1, A2, A3);
	typedef R (*L4)(void*, A1, A2, A3, A4);
	typedef R (*L5)(void*, A1, A2, A3, A4, A5);
	typedef void* (*G)(const unsigned);

	void* obj;
	G get;

	delegate& init(void* o, G g) { obj = o; get = g; return *this; }

	template <typename T>
	delegate& cinit(T const* o, G g) { return init(const_cast <T*>(o), g); }

	template <typename L>
	L load(const unsigned n) const { return reinterpret_cast <L>((*get)(n)); }

public:  // protected

	virtual R operate()                                  const { return (*load <L0>(0))(obj); }
	virtual R operate(A1 a1)                             const { return (*load <L1>(1))(obj, a1); }
	virtual R operate(A1 a1, A2 a2)                      const { return (*load <L2>(2))(obj, a1, a2); }
	virtual R operate(A1 a1, A2 a2, A3 a3)               const { return (*load <L3>(3))(obj, a1, a2, a3); }
	virtual R operate(A1 a1, A2 a2, A3 a3, A4 a4)        const { return (*load <L4>(4))(obj, a1, a2, a3, a4); }
	virtual R operate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const { return (*load <L5>(5))(obj, a1, a2, a3, a4, a5); }

public:

//-----------------------------------------------------------------------------

	typedef R return_type;
	typedef S signature_type;
	typedef I invoker_type;

	delegate() : obj(0), get(0) { }
	delegate& raw() { return *this; }

	operator bool()  const { return get != 0; }
	bool operator!() const { return get == 0; }

	virtual R operator()()                                  const { return operate(); }
	virtual R operator()(A1 a1)                             const { return operate(a1); }
	virtual R operator()(A1 a1, A2 a2)                      const { return operate(a1, a2); }
	virtual R operator()(A1 a1, A2 a2, A3 a3)               const { return operate(a1, a2, a3); }
	virtual R operator()(A1 a1, A2 a2, A3 a3, A4 a4)        const { return operate(a1, a2, a3, a4); }
	virtual R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const { return operate(a1, a2, a3, a4, a5); }

	template <typename E1>
	R operator()(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, E1, ...) const { return operate(a1, a2, a3, a4, a5); }

//-----------------------------------------------------------------------------

	using extend <R (A1, A2, A3, A4, A5)>::bind;
	delegate& bind(delegate const* d) { return *this = *d; }

	delegate& unbind() { return init(0, 0); }

	template <typename Z>
	delegate <Z> adapt() const { return delegate <Z>().bind(this); }

//-----------------------------------------------------------------------------

	template <
		R (*F)(A1, A2, A3, A4, A5),
		typename D1, typename D2, typename D3, typename D4, typename D5
	>
	delegate& bind()
	{
		return init(0, &U::template function <F, D1, D2, D3, D4, D5>::get);
	}

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5),
		typename D1, typename D2, typename D3, typename D4, typename D5
	>
	delegate& bind(T* obj)
	{
		return init(obj, &U::template method <T, M, D1, D2, D3, D4, D5>::get);
	}

	template <
		typename T, R (T::*M)(A1, A2, A3, A4, A5) const,
		typename D1, typename D2, typename D3, typename D4, typename D5
	>
	delegate& bind(T const* obj)
	{
		return cinit
			(obj, &U::template const_method <T, M, D1, D2, D3, D4, D5>::get);
	}

	template <
		typename F,
		typename D1, typename D2, typename D3, typename D4, typename D5
	>
	delegate& bind(F* obj)
	{
		return init(obj, &U::template functor <F, NO, D1, D2, D3, D4, D5>::get);
	}

	template <
		typename F,
		typename D1, typename D2, typename D3, typename D4, typename D5
	>
	delegate& bind(F const* obj)
	{
		return cinit(obj, &U::template functor <F, YES, D1, D2, D3, D4, D5>::get);
	}

};

//-----------------------------------------------------------------------------

}  // namespace delegate_details

using delegate_details::delegate;
using delegate_details::invoker;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_DELEGATE_HPP
