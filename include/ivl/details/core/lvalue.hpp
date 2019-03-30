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

//to be removed
#if 0

namespace ivl
{

namespace lvalue_details
{
template<typename T0>
class lvalue1 {
private:
	T0 &t0;

public:
	lvalue1(T0& arg0): t0(arg0){};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0); };
};


template<typename T0, typename T1>
class lvalue2 {
private:
	T0 &t0;
	T1 &t1;

public:
	lvalue2(T0& arg0, T1& arg1): t0(arg0), t1(arg1) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1); };
};


template<typename T0, typename T1, typename T2>
class lvalue3 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;

public:
	lvalue3(T0& arg0, T1& arg1, T2& arg2): t0(arg0), t1(arg1), t2(arg2) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2); };
};


template<typename T0, typename T1, typename T2, typename T3>
class lvalue4 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;
	T3 &t3;

public:
	lvalue4(T0& arg0, T1& arg1, T2& arg2, T3& arg3):
      t0(arg0), t1(arg1), t2(arg2), t3(arg3) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4>
class lvalue5 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;
	T3 &t3;
	T4 &t4;

public:
	lvalue5(T0& arg0, T1& arg1, T2& arg2, T3& arg3, T4& arg4):
      t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
								typename T5>
class lvalue6 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;
	T3 &t3;
	T4 &t4;
	T5 &t5;

public:
	lvalue6(T0& arg0, T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5):
      t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
						typename T5, typename T6>
class lvalue7 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;
	T3 &t3;
	T4 &t4;
	T5 &t5;
	T6 &t6;

public:
	lvalue7(T0& arg0, T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5,
		T6& arg6):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5), t6(arg6){};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
					typename T5, typename T6, typename T7>
class lvalue8 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;
	T3 &t3;
	T4 &t4;
	T5 &t5;
	T6 &t6;
	T7 &t7;

public:
	lvalue8(T0& arg0, T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5,
		T6& arg6, T7& arg7):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5),
		t6(arg6), t7(arg7) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6, t7); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
			typename T5, typename T6, typename T7, typename T8>
class lvalue9 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;
	T3 &t3;
	T4 &t4;
	T5 &t5;
	T6 &t6;
	T7 &t7;
	T8 &t8;

public:
	lvalue9(T0& arg0, T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5,
		T6& arg6, T7 &arg7, T8 &arg8):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5), t6(arg6),
		t7(arg7), t8(arg8) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6, t7, t8); };
};

template<typename T0, typename T1, typename T2, typename T3, typename T4,
	typename T5, typename T6, typename T7, typename T8, typename T9>
class lvalue10 {
private:
	T0 &t0;
	T1 &t1;
	T2 &t2;
	T3 &t3;
	T4 &t4;
	T5 &t5;
	T6 &t6;
	T7 &t7;
	T8 &t8;
	T9 &t9;

public:
	lvalue10(T0& arg0, T1& arg1, T2& arg2, T3& arg3, T4& arg4, T5& arg5,
		T6& arg6, T7 &arg7, T8 &arg8, T9 &arg9):
	t0(arg0), t1(arg1), t2(arg2), t3(arg3), t4(arg4), t5(arg5), t6(arg6),
		t7(arg7), t8(arg8), t9(arg9) {};

	template <class F> void operator=(const rvalue_base<F>& f)
	{ f.derived().output(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9); };
};

} /*namespace lvalue_details*/

template <class T0>
inline
lvalue_details::lvalue1<T0> lvalue(T0& t0)
{
	return lvalue_details::lvalue1<T0>(t0);
}

template <class T0, class T1>
inline
lvalue_details::lvalue2<T0, T1> lvalue(T0& t0, T1& t1)
{
	return lvalue_details::lvalue2<T0, T1>(t0, t1);
}

template <class T0, class T1, class T2>
inline
lvalue_details::lvalue3<T0, T1, T2> lvalue(T0& t0, T1& t1, T2& t2)
{
	return lvalue_details::lvalue3<T0, T1, T2>(t0, t1, t2);
}

template <class T0, class T1, class T2, class T3>
inline
lvalue_details::lvalue4<T0, T1, T2, T3> lvalue(T0& t0, T1& t1, T2& t2, T3& t3)
{
	return lvalue_details::lvalue4<T0, T1, T2, T3>(t0, t1, t2, t3);
}

template <class T0, class T1, class T2, class T3, class T4>
inline
lvalue_details::lvalue5<T0, T1, T2, T3, T4> lvalue(T0& t0, T1& t1, T2& t2,
						   T3& t3, T4& t4)
{
	return lvalue_details::lvalue5<T0, T1, T2, T3, T4>(t0, t1, t2, t3, t4);
}

template <class T0, class T1, class T2, class T3, class T4, class T5>
inline
lvalue_details::lvalue6<T0, T1, T2, T3, T4, T5> lvalue(T0& t0, T1& t1, T2& t2,
						       T3& t3, T4& t4, T5& t5)
{
	return lvalue_details::lvalue6<T0, T1, T2, T3, T4, T5>(t0, t1, t2, t3,
		t4, t5);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6>
inline
lvalue_details::lvalue7<T0, T1, T2, T3, T4, T5, T6> lvalue(T0& t0, T1& t1,
							   T2& t2, T3& t3,
							   T4& t4, T5& t5, T6& t6)
{
	return lvalue_details::lvalue7<T0, T1, T2, T3, T4, T5, T6>(t0, t1, t2,
		t3, t4, t5, t6);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7>
inline
lvalue_details::lvalue8<T0, T1, T2, T3, T4, T5, T6, T7> lvalue(T0& t0, T1& t1,
							       T2& t2, T3& t3,
							       T4& t4, T5& t5,
							       T6& t6, T7& t7)
{
	return lvalue_details::lvalue8<T0, T1, T2, T3, T4, T5, T6, T7>(t0, t1,
		t2, t3, t4, t5, t6, t7);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8>
inline
lvalue_details::lvalue9<T0, T1, T2, T3, T4, T5, T6, T7, T8> lvalue(T0& t0,
		T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8)
{
	return lvalue_details::lvalue9<T0, T1, T2, T3, T4, T5, T6, T7, T8>(t0,
		t1, t2, t3, t4, t5, t6, t7, t8);
}

template <class T0, class T1, class T2, class T3, class T4, class T5, class T6,
class T7, class T8, class T9>
inline
lvalue_details::lvalue10<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> lvalue(T0& t0,
	T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
{
	return lvalue_details::lvalue10<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>(
		t0, t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

} /*namespace ivl*/

#endif


#endif // IVL_CORE_DETAILS_LVALUE_HPP
