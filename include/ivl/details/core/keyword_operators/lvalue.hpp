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

#ifndef IVL_CORE_DETAILS_LVALUE_HPP
#define IVL_CORE_DETAILS_LVALUE_HPP

#if 0
namespace ivl {

namespace lvalue_details {

template <class T>
struct arg
{
	typedef T type;
};

template <class T>
struct arg<T&>
{
	typedef T& type;
};

template <class T, class REFERER>
struct const_arg
{
};

template <class T>
struct const_arg<T, types::t_true>
{
	typename types::derive<T>::type type;
};

template <class T>
struct arg<const T&>
: public const_arg<T,
	typename types::is_base<types::array_is_referer_identifier, T>::type>
{
};

template<
	typename T1 = types::skip, typename T2 = types::skip,
	typename T3 = types::skip, typename T4 = types::skip,
	typename T5 = types::skip, typename T6 = types::skip,
	typename T7 = types::skip, typename T8 = types::skip,
	typename T9 = types::skip, typename T10 = types::skip>
class lvalue_base : public tuple<
	typename arg<T1>::type,
	typename arg<T2>::type,
	typename arg<T3>::type,
	typename arg<T4>::type,
	typename arg<T5>::type,
	typename arg<T6>::type,
	typename arg<T7>::type,
	typename arg<T8>::type,
	typename arg<T9>::type,
	typename arg<T10>::type>
{
	typedef tuple<
	typename arg<T1>::type,
	typename arg<T2>::type,
	typename arg<T3>::type,
	typename arg<T4>::type,
	typename arg<T5>::type,
	typename arg<T6>::type,
	typename arg<T7>::type,
	typename arg<T8>::type,
	typename arg<T9>::type,
	typename arg<T10>::type> tpl;

	typedef typename types::bare_type<T1>::type b1;
	typedef typename types::bare_type<T2>::type b2;
	typedef typename types::bare_type<T3>::type b3;
	typedef typename types::bare_type<T4>::type b4;
	typedef typename types::bare_type<T5>::type b5;
	typedef typename types::bare_type<T6>::type b6;
	typedef typename types::bare_type<T7>::type b7;
	typedef typename types::bare_type<T8>::type b8;
	typedef typename types::bare_type<T9>::type b9;
	typedef typename types::bare_type<T10>::type b10;

public:
	lvalue_base(T1 arg1 = b1(), T2 arg2 = b2(), T3 arg3 = b3(),
		T4 arg4 = b4(), T5 arg5 = b5(), T6 arg6 = b6(), T7 arg7 = b7(),
		T8 arg8 = b8(), T9 arg9 = b9(), T10 arg10 = b10()) :
		tpl(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) {};

	//using tpl::operator=;

	template<int N, class TPL>
	lvalue_base& operator=(const ivl::tuple_base<N, TPL>& t)
	{
		tpl::operator=(t);
		return *this;
	}

	template <class F>
	lvalue_base& operator=(const rvalue_base<F>& f)
	{
		apply_tuple_output(*this, f.derived());
		return *this;
	}
};

// -------------------------------------------------------------------------
// lval_base is for operator _(.)
template<
	typename T1 = types::skip, typename T2 = types::skip,
	typename T3 = types::skip, typename T4 = types::skip,
	typename T5 = types::skip, typename T6 = types::skip,
	typename T7 = types::skip, typename T8 = types::skip,
	typename T9 = types::skip, typename T10 = types::skip>
class lval_base : public tuple<
	T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
{
	typedef tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> tpl;

	typedef typename types::bare_type<T1>::type b1;
	typedef typename types::bare_type<T2>::type b2;
	typedef typename types::bare_type<T3>::type b3;
	typedef typename types::bare_type<T4>::type b4;
	typedef typename types::bare_type<T5>::type b5;
	typedef typename types::bare_type<T6>::type b6;
	typedef typename types::bare_type<T7>::type b7;
	typedef typename types::bare_type<T8>::type b8;
	typedef typename types::bare_type<T9>::type b9;
	typedef typename types::bare_type<T10>::type b10;

public:
	lval_base(T1 arg1 = b1(), T2 arg2 = b2(), T3 arg3 = b3(),
		T4 arg4 = b4(), T5 arg5 = b5(), T6 arg6 = b6(), T7 arg7 = b7(),
		T8 arg8 = b8(), T9 arg9 = b9(), T10 arg10 = b10()) :
		tpl(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) {};

	// TODO: optimize this maybe
	template<int N, class TPL>
	lval_base& operator=(const ivl::tuple_base<N, TPL>& t)
	{
		tpl::operator=(t);
		return *this;
	}
	lval_base& operator=(const lval_base& f)
	{
		tpl::operator=(f);
		return *this;
	}
	template <class F>
	lval_base& operator=(const rvalue_base<F>& f)
	{
		f.derived().tuple_output(*this);
		return *this;
	}
		/*
	lval_base& operator=(const lval_base& f)
	{
		lvalue_base<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
			(this->v1, this->v2, this->v3, this->v4, this->v5,
				this->v6, this->v7, this->v8, this->v9, this->v10) = f;
		return *this;
	}
	template <class F>
	lval_base& operator=(const F& f)
	{
		lvalue_base<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
			(this->v1, this->v2, this->v3, this->v4, this->v5,
				this->v6, this->v7, this->v8, this->v9, this->v10) = f;
		return *this;
	}
*/
	/*
	using tpl::operator=;
	template <class F>
	lval_base& operator=(const rvalue_base<F>& f)
	{
		lvalue_base<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>
			lvb(this->v1, this->v2, this->v3, this->v4, this->v5,
				this->v6, this->v7, this->v8, this->v9, this->v10);
		apply_tuple_output(lvb, f.derived());
		return *this;
	}*/
};

} /*namespace lvalue_details*/


// lvalue functions

template <class T0>
inline
lvalue_details::lvalue_base<T0&> lvalue(T0& t0)
{
	return lvalue_details::lvalue_base<T0&>(t0);
}

template <class T0, class T1>
inline
lvalue_details::lvalue_base<T0&, T1&> lvalue(T0& t0, T1& t1)
{
	return lvalue_details::lvalue_base<T0&, T1&>(t0, t1);
}

template <class T0, class T1, class T2>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&> lvalue(T0& t0, T1& t1, T2& t2)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&>(t0, t1, t2);
}

template <class T0, class T1, class T2, class T3>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&> lvalue(T0& t0,
							T1& t1, T2& t2, T3& t3)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&>(t0, t1, t2, t3);
}

template <class T0, class T1, class T2, class T3, class T4>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&> lvalue(T0& t0, T1& t1,
							T2& t2, T3& t3, T4& t4)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&>(t0, t1, t2,
		t3, t4);
}

template <class T0, class T1, class T2, class T3, class T4, class T5>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&> lvalue(T0& t0, T1& t1,
							T2& t2, T3& t3, T4& t4, T5& t5)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&>(t0, t1, t2,
		t3, t4, t5);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&> lvalue(T0& t0,
		T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&>(t0,
		t1, t2, t3, t4, t5, t6);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&, T7&> lvalue(
		T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&,
		T5&, T6&, T7&>(t0, t1, t2, t3, t4, t5, t6, t7);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&,
		T7&, T8&> lvalue(T0& t0,
			T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&,
			T5&, T6&, T7&, T8&>(t0, t1, t2, t3, t4, t5, t6, t7, t8);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8, class T9>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&,
	T6&, T7&, T8&, T9&> lvalue(T0& t0,
		T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&,
			T5&, T6&, T7&, T8&, T9&>(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}


// lhs synomym

template <class T0>
inline
lvalue_details::lvalue_base<T0&> lhs(T0& t0)
{
	return lvalue_details::lvalue_base<T0&>(t0);
}

template <class T0, class T1>
inline
lvalue_details::lvalue_base<T0&, T1&> lhs(T0& t0, T1& t1)
{
	return lvalue_details::lvalue_base<T0&, T1&>(t0, t1);
}

template <class T0, class T1, class T2>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&> lhs(T0& t0, T1& t1, T2& t2)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&>(t0, t1, t2);
}

template <class T0, class T1, class T2, class T3>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&> lhs(T0& t0,
							T1& t1, T2& t2, T3& t3)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&>(t0, t1, t2, t3);
}

template <class T0, class T1, class T2, class T3, class T4>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&> lhs(T0& t0, T1& t1,
							T2& t2, T3& t3, T4& t4)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&>(t0, t1, t2,
		t3, t4);
}

template <class T0, class T1, class T2, class T3, class T4, class T5>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&> lhs(T0& t0, T1& t1,
							T2& t2, T3& t3, T4& t4, T5& t5)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&>(t0, t1, t2,
		t3, t4, t5);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&> lhs(T0& t0,
		T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&>(t0,
		t1, t2, t3, t4, t5, t6);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&, T7&> lhs(
		T0& t0, T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&,
		T5&, T6&, T7&>(t0, t1, t2, t3, t4, t5, t6, t7);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&, T6&,
		T7&, T8&> lhs(T0& t0,
			T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&,
			T5&, T6&, T7&, T8&>(t0, t1, t2, t3, t4, t5, t6, t7, t8);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8, class T9>
inline
lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&, T5&,
	T6&, T7&, T8&, T9&> lhs(T0& t0,
		T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
{
	return lvalue_details::lvalue_base<T0&, T1&, T2&, T3&, T4&,
			T5&, T6&, T7&, T8&, T9&>(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}


#if 0


template<typename T0>
class lvalue1 {
private:
	typename arg<T0>::type t0;

public:
	lvalue1(T0 arg0): t0(arg0){};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0); };
};


template<typename T0, typename T1>
class lvalue2 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;

public:
	lvalue2(T0 arg0, T1 arg1): t0(arg0), t1(arg1) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1); };
};


template<typename T0, typename T1, typename T2>
class lvalue3 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;

public:
	lvalue3(T0 arg0, T1 arg1, T2 arg2): t0(arg0), t1(arg1), t2(arg2) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2); };
};


template<typename T0, typename T1, typename T2, typename T3>
class lvalue4 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;
	typename arg<T3>::type t3;

public:
	lvalue4(T0 arg0, T1 arg1, T2 arg2, T3 arg3):
      t0(arg0), t1(arg1), t2(arg2), t3(arg3) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
class lvalue5 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;
	typename arg<T3>::type t3;
	typename arg<T4>::type t4;

public:
	lvalue5(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4):
      t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
								typename T5>
class lvalue6 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;
	typename arg<T3>::type t3;
	typename arg<T4>::type t4;
	typename arg<T5>::type t5;

public:
	lvalue6(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5):
      t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
						typename T5, typename T6>
class lvalue7 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;
	typename arg<T3>::type t3;
	typename arg<T4>::type t4;
	typename arg<T5>::type t5;
	typename arg<T6>::type t6;

public:
	lvalue7(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
		T6 arg6):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5), t6(arg6){};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename T6, typename T7>
class lvalue8 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;
	typename arg<T3>::type t3;
	typename arg<T4>::type t4;
	typename arg<T5>::type t5;
	typename arg<T6>::type t6;
	typename arg<T7>::type t7;

public:
	lvalue8(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
		T6 arg6, T7 arg7):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5),
		t6(arg6), t7(arg7) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6, t7); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
			typename T5, typename T6, typename T7, typename T8>
class lvalue9 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;
	typename arg<T3>::type t3;
	typename arg<T4>::type t4;
	typename arg<T5>::type t5;
	typename arg<T6>::type t6;
	typename arg<T7>::type t7;
	typename arg<T8>::type t8;

public:
	lvalue9(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
		T6 arg6, T7 arg7, T8 arg8):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5), t6(arg6),
		t7(arg7), t8(arg8) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6, t7, t8); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
	typename T5, typename T6, typename T7, typename T8, typename T9>
class lvalue10 {
private:
	typename arg<T0>::type t0;
	typename arg<T1>::type t1;
	typename arg<T2>::type t2;
	typename arg<T3>::type t3;
	typename arg<T4>::type t4;
	typename arg<T5>::type t5;
	typename arg<T6>::type t6;
	typename arg<T7>::type t7;
	typename arg<T8>::type t8;
	typename arg<T9>::type t9;

public:
	lvalue10(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4, T5 arg5,
		T6 arg6, T7 arg7, T8 arg8, T9 arg9):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5), t6(arg6),
		t7(arg7), t8(arg8), t9(arg9) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9); };
};


#endif


} /*namespace ivl*/
#endif





namespace ivl {


template <class T0>
inline
tuple<T0&> lvalue(T0& t0)
{
	return reftpl(t0);
}

template <class T0, class T1>
inline
tuple<T0&, T1&> lvalue(T0& t0, T1& t1)
{
	return reftpl(t0, t1);
}

template <class T0, class T1, class T2>
inline
tuple<T0&, T1&, T2&> lvalue(T0& t0, T1& t1, T2& t2)
{
	return reftpl(t0, t1, t2);
}

template <class T0, class T1, class T2, class T3>
inline
tuple<T0&, T1&, T2&, T3&> lvalue(T0& t0, T1& t1, T2& t2, T3& t3)
{
	return reftpl(t0, t1, t2, t3);
}

template <class T0, class T1, class T2, class T3, class T4>
inline
tuple<T0&, T1&, T2&, T3&, T4&> lvalue(T0& t0, T1& t1, T2& t2,
						   T3& t3, T4& t4)
{
	return reftpl(t0, t1, t2, t3, t4);
}

template <class T0, class T1, class T2, class T3, class T4, class T5>
inline
tuple<T0&, T1&, T2&, T3&, T4&, T5&> lvalue(T0& t0, T1& t1, T2& t2,
						       T3& t3, T4& t4, T5& t5)
{
	return reftpl(t0, t1, t2, t3, t4, t5);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline
tuple<T0&, T1&, T2&, T3&, T4&, T5&, T6&> lvalue(T0& t0, T1& t1,
							   T2& t2, T3& t3,
							   T4& t4, T5& t5, T6& t6)
{
	return reftpl(t0, t1, t2, t3, t4, t5, t6);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7>
inline
tuple<T0&, T1&, T2&, T3&, T4&, T5&, T6&, T7&> lvalue(T0& t0, T1& t1,
							       T2& t2, T3& t3,
							       T4& t4, T5& t5,
							       T6& t6, T7& t7)
{
	return reftpl(t0, t1, t2, t3, t4, t5, t6, t7);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8>
inline
tuple<T0&, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&> lvalue(T0& t0,
		T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8)
{
	return reftpl(t0, t1, t2, t3, t4, t5, t6, t7, t8);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8, class T9>
inline
tuple<T0&, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&> lvalue(T0& t0,
	T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
{
	return reftpl(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

} /* namespace ivl */





#endif // IVL_CORE_DETAILS_LVALUE_HPP
