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

#ifndef IVL_CORE_DETAILS_TYPES_SCALAR_HPP
#define IVL_CORE_DETAILS_TYPES_SCALAR_HPP

namespace ivl {

// -------------------

template<class T>
struct copyscalar : public types::copyscalar_identifier
{
	T t;
	copyscalar(T t) : t(t) {}
	copyscalar() {}
	copyscalar(const copyscalar& o) : t(o.t) {}
	copyscalar& operator=(const copyscalar& o) { t = o.t; return *this; }
};
// -------------------


template<class T, T V>
class fixed_scalar : public types::scalar_identifier
{
	typedef T prv_elem_type;
public:
	typedef prv_elem_type elem_type;
	fixed_scalar() {}
	fixed_scalar(const fixed_scalar& s) {}
	template<class J>
	fixed_scalar(const J& ) {}
	operator prv_elem_type() const { return V; }
	prv_elem_type base() const { return V; }
};

template<int V>
class fixed_scalar<int, V> : public types::scalar_identifier
{
	typedef int prv_elem_type;
public:
	typedef prv_elem_type elem_type;
	fixed_scalar() {}
	fixed_scalar(const fixed_scalar& s) {}
	template<class J>
	fixed_scalar(const J& ) {}
	operator prv_elem_type() const { return V; }
	prv_elem_type base() const { return V; }
};

// -------------------------------------------------------------------------

// scalar of class!!
template<class A, class TP>
struct memberfunc_constructor;

template<class T>
class scalar : public T,
	public types::t_if<types::is_base<types::scalar_identifier, T>,
		types::nop_base<T>, types::scalar_identifier>::type
{
	typedef T prv_elem_type;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : T(static_cast<const T&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : T(static_cast<const J&>(s)) { }
	scalar(const T& s) : T(s) { }
	T& base() { return static_cast<T&>(*this); }
	const prv_elem_type& base() const { return static_cast<const T&>(*this); }


	// ----------------------------------------------
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<Z, R, A1> > operator[](R (Z::*m)(A1))
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<Z, R, A1> > operator[](R (Z::*m)(A1)) const
	{
		return reftpl(*this, m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const)
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const) const
	{
		return reftpl(*this, m);
	}

	// ----------------------------------------------

	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<Z, R, A1> > in(R (Z::*m)(A1))
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<Z, R, A1> > in(R (Z::*m)(A1)) const
	{
		return reftpl(*this, m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const)
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const) const
	{
		return reftpl(*this, m);
	}
	// ----------------------------------------------

};

template<class T>
class scalar<T&> :
	public types::scalar_identifier
{
	typedef typename types::remove_const<T>::type prv_elem_type;
	T* ref;
public:
	typedef prv_elem_type elem_type;
	scalar() : ref(0) { }
	scalar(const scalar& s) : ref(s.ref) { }
	template <class J>
	scalar(const scalar<J>& s) : ref(&static_cast<T&>(s)) { }
	scalar(T& s) : ref(&s) { }
	T& base() const { return *ref; }
	//const prv_elem_type& base() const { return static_cast<const T&>(*ref); }
	operator T&() const { return *ref; }
	//operator const prv_elem_type&() const { return *ref; }
	scalar& operator=(const scalar& s)
		{ if(!ref) ref=s.ref; else *ref = *s.ref; return *this; }
	scalar& operator=(T& s) { if(!ref) ref=&s; else *ref = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { *ref = o; return *this; }


	// ----------------------------------------------
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<Z, R, A1> > operator[](R (Z::*m)(A1))
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<Z, R, A1> > operator[](R (Z::*m)(A1)) const
	{
		return reftpl(*this, m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const)
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const) const
	{
		return reftpl(*this, m);
	}

	// ----------------------------------------------
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<Z, R, A1> > in(R (Z::*m)(A1))
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<Z, R, A1> > in(R (Z::*m)(A1)) const
	{
		return reftpl(*this, m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const)
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const) const
	{
		return reftpl(*this, m);
	}
};

template<class T>
class scalar<const T&> :
	public types::scalar_identifier
{
	typedef typename types::remove_const<T>::type prv_elem_type;
	const T* ref;
public:
	typedef prv_elem_type elem_type;
	scalar() : ref(0) { }
	scalar(const scalar& s) : ref(s.ref) { }
	template <class J>
	scalar(const scalar<J>& s) : ref(&static_cast<const T&>(s)) { }
	scalar(const T& s) : ref(&s) { }
	const T& base() const { return static_cast<const T&>(*ref); }
	operator const T&() const { return *ref; }
	scalar& operator=(const scalar& s) { ref=s.ref; return *this; }
	scalar& operator=(T& s) { ref=&s; return *this; }


	// ----------------------------------------------
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<Z, R, A1> > operator[](R (Z::*m)(A1))
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<Z, R, A1> > operator[](R (Z::*m)(A1)) const
	{
		return reftpl(*this, m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const)
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<const Z, R, A1> > operator[](R (Z::*m)(A1) const) const
	{
		return reftpl(*this, m);
	}

	// ----------------------------------------------
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<Z, R, A1> > in(R (Z::*m)(A1))
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<Z, R, A1> > in(R (Z::*m)(A1)) const
	{
		return reftpl(*this, m);
	}
//
	template<class R, class A1, class Z>
	memberfunc_constructor<scalar, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const)
	{
		return reftpl(*this, m);
	}
	template<class R, class A1, class Z>
	memberfunc_constructor<const scalar, tuple<const Z, R, A1> > in(R (Z::*m)(A1) const) const
	{
		return reftpl(*this, m);
	}
};

template<class T>
class scalar<T*> :
	public types::scalar_identifier
{
	typedef T* prv_elem_type;
	T* v;
public:
	typedef prv_elem_type elem_type;
	scalar() : v(0) { }
	scalar(const scalar& s) : v(s.v) { }
	template <class J>
	scalar(const scalar<J>& s) : v(s) { }
	scalar(T* s) : v(s) { }
	T* base() const { return v; }
	operator T*() const { return v; }
	scalar& operator=(const scalar& s) { v = s.v; return *this; }
	scalar& operator=(T* s) { v = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { v = o; return *this; }
};

template<class T>
class scalar<const T*> :
	public types::scalar_identifier
{
	typedef const T* prv_elem_type;
	const T* v;
public:
	typedef prv_elem_type elem_type;
	scalar() : v(0) { }
	scalar(const scalar& s) : v(s.v) { }
	template <class J>
	scalar(const scalar<J>& s) : v(s) { }
	scalar(const T* s) : v(s) { }
	T* base() const { return v; }
	//const prv_elem_type& base() const { return static_cast<const T&>(*ref); }
	operator const T*() const { return v; }
	//operator const prv_elem_type&() const { return *ref; }
	scalar& operator=(const scalar& s) { v = s.v; return *this; }
	scalar& operator=(const T* s) { v = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { v = o; return *this; }
};

template<>
class scalar<float> : public types::scalar_identifier
{
	typedef float prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};

template<>
class scalar<double> : public types::scalar_identifier
{
	typedef double prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};

//TODO: placed here until reference face issue is fixed.
namespace math {

template <class T, class S>
inline T power(const T& x, const S& y)
{
	using std::pow; // TODO: definition of pow in right place. This line may not be needed if this is made.
	return pow(x, y);
}

inline int power(int x, int y)
{
	// TODO: fix this well, for all types. Also add integer power with different algorithm.
	return std::pow((double)x, y);
}
}

#include "platform_specific/scalar_int_impl.hpp"

template<class T>
scalar<T> operator->*(const scalar<T>& x, unsigned int y)
{
	return ivl::math::power(x.base(), y);
}

template<class T>
scalar<typename types::to_floating<T>::type> operator->*(const scalar<T>& x,
														int y)
{
	return ivl::math::power(x.base(), y);
}

template<class T>
scalar<typename types::to_floating<T>::type> operator->*(const scalar<T>& x,
														float y)
{
	return ivl::math::power(x.base(), y);
}

template<class T>
scalar<typename types::to_floating<T>::type> operator->*(const scalar<T>& x,
														double y)
{
	return ivl::math::power(x.base(), y);
}

// ----------------------------------------------------

namespace types {

namespace types_details
{

template <class DESCALARIZE, class T>
struct descalarize_tool { };

template <class T>
struct descalarize_tool<types::t_false, T>
{
	typedef T& type;
	static inline type f(T& t) { return t; }
};

template <class T>
struct descalarize_tool<types::t_true, T>
{
	typedef typename types::bare_type<T>::type t_bare;
	typedef typename t_bare::elem_type& bare_type;
	typedef typename types::apply_const<bare_type,
		types::is_const<T> >::type type;

	static inline type f(T& t) { return t.base(); }
};

template <class S, class T>
struct descalarize_type : types::t_id<T> { };
template <class T>
struct descalarize_type<types::t_true, T> : 
	descalarize_tool<types::t_true, T> { };

} /* namespace types_details */

template<class T>
struct t_descalarize : types_details::descalarize_type<
	typename types::is_base<types::scalar_identifier, T>::type, T> 
{ };
template<class T>
struct t_descalarize_ref : types_details::descalarize_type<
	typename types::is_base<types::scalar_identifier, typename types::bare_type<T>::type>::type, T> 
{ };

template<class DESCALARIZE, class T>
typename types_details::descalarize_tool<DESCALARIZE, T>
	::type r_descalarize(T& t)
{
	return types_details::descalarize_tool<DESCALARIZE, T>::f(t);
}
template<class DESCALARIZE, class T>
typename types_details::descalarize_tool<DESCALARIZE, const T>
	::type r_descalarize(const T& t)
{
	return types_details::descalarize_tool<DESCALARIZE, const T>::f(t);
}

} /* namespace types */

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_SCALAR_HPP
