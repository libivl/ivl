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

#ifndef IVL_CORE_DETAILS_UNDERSCORE_UNDERSCORE_HPP
#define IVL_CORE_DETAILS_UNDERSCORE_UNDERSCORE_HPP

namespace ivl {

namespace core_details {

struct transpose_arg { };

struct complex_transpose_arg { };

template<class J, class S>
struct range_sup;

template<class J>
struct range_sup_0 {
	J s;
	range_sup_0(J s):s(s){}
	template<class S> range_sup<J, S> operator,(const S& st) const
	{ return range_sup<J, S>(s, st); }
};
/*
template<class J, class T>
struct range_sup_check_1
{
	typedef range_sup_0<J> type;
	static inline type from(J x) { return type(x); }
};

template<class J>
struct range_sup_check_1<J, types::t_true>
{
	typedef  type;
	static inline type from(J x) { return type(x); }
};

template<class J>
struct range_sup_check :
	range_sup_check_1<J, is_base<types::tuple_identifier,
	typename types::bare_type<J>::type> { };

	types::t_if<,
		t_id<tup_sup_,
		t_id<range_sup_0<J> >
	>::type
{
	type from(


};
*/
class _class :
	public ivl::array<double, data::blackhole<> >,
	public ivl::tuple<>,
	public ivl::index_array_all_type
{
public:
	using ivl::array<double, data::blackhole<> >::derived;
	typedef ivl::array<double, data::blackhole<> >::derived_type derived_type;

	// for range, blocked when left is tuple
	template<class J>
	friend typename types::enable_if<types::t_not<types::is_base<
		types::tuple_identifier, typename types::bare_type<J>::type> >,
	range_sup_0<J> >::type operator ,(const J& first, _class)
	{
		return range_sup_0<J>(first);
	}

	template<class J, class S>
	friend range_sup_1<J, S> operator ,(const range_sup<J, S>& x, _class) { return range_sup_1<J, S>(x.j, x.s); }

	// TODO: wwww???? check???!!!
	// old:
	//tuple<_class> operator, (_class) const { return tuple<_class>(_class()); }

	// new:
	tuple<_class&> operator, (_class) { return tuple<_class&>(*this); }
	//tuple<_class> operator, (_class) const { return tuple<_class&>(*this); }

	//

	transpose_arg operator!() { return transpose_arg(); }

	//complex_transpose_arg operator~() { return complex_transpose_arg(); }

	// complex_transpose too
	index_array_all_type operator*() { return index_array_all_type(); }



	// scalar construction
	//template<class T>
	//ivl::scalar<T> operator[](const T& t) { return ivl::scalar<T>(t); }
	template<class T>
	typename types::t_if<types::t_or<types::is_builtin<T>, types::is_complex<T> >, ivl::scalar<T>,
		ivl::scalar<const T&> >::type operator[](const T& t)
	{
		return t;
		//return ivl::scalar<T>(t);
	}
	template<class T>
	ivl::scalar<T&> operator[](T& t) { return ivl::scalar<T&>(t); }


	using ivl::tuple<>::operator,;

	// iavr: every array<T, S> needs a reference type
	typedef types::skip reference;

	// ivl::lvalue_details::lval_base construction
/*
	template<class T1>
	ivl::lvalue_details::lval_base<T1&> operator()(T1& t1)
	{
		return ivl::lvalue_details::lval_base<T1&>(t1);
	}

	template<class T1, class T2>
	ivl::lvalue_details::lval_base<T1&, T2&> operator()(T1& t1, T2& t2)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&>(t1, t2);
	}

	template<class T1, class T2, class T3>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&> operator()(T1& t1, T2& t2, T3& t3)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&>(t1, t2, t3);
	}

	template<class T1, class T2, class T3, class T4>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&> operator()(T1& t1, T2& t2, T3& t3, T4& t4)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&>(t1, t2, t3, t4);
	}

	template<class T1, class T2, class T3, class T4, class T5>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&> operator()(T1& t1,
		T2& t2, T3& t3, T4& t4, T5& t5)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&>(t1, t2, t3, t4, t5);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&> operator()(T1& t1,
		T2& t2, T3& t3, T4& t4, T5& t5, T6& t6)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&>(t1, t2, t3, t4, t5, t6);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6,
	class T7>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&> operator()(T1& t1,
		T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&>(t1, t2, t3, t4, t5, t6,
														t7);
	}

	template
	<class T1, class T2, class T3, class T4, class T5,
	 class T6, class T7, class T8>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&> operator()(T1& t1,
		T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&>(
			t1, t2, t3, t4, t5, t6, t7, t8);
	}

	template
	<class T1, class T2, class T3, class T4, class T5,
	 class T6, class T7, class T8, class T9>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&> operator()(T1& t1,
		T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&>(
			t1, t2, t3, t4, t5, t6, t7, t8, t9);
	}

	template
	<class T1, class T2, class T3, class T4, class T5,
	 class T6, class T7, class T8, class T9, class T10>
	ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&> operator()(T1& t1,
		T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9,
		T10& t10)
	{
		return ivl::lvalue_details::lval_base<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&>(
			t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
	}



	template<class T1>
	ivl::lvalue_details::lval_base<const T1&> operator()(const T1& t1)
	{
		return ivl::lvalue_details::lval_base<const T1&>(t1);
	}

	template<class T1, class T2>
	ivl::lvalue_details::lval_base<const T1&, const T2&> operator()(const T1& t1, const T2& t2)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&>(t1, t2);
	}

	template<class T1, class T2, class T3>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&> operator()(const T1& t1, const T2& t2,
													const T3& t3)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&>(t1, t2, t3);
	}

	template<class T1, class T2, class T3, class T4>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&> operator()(const T1& t1,
		const T2& t2, const T3& t3, const T4& t4)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&>(t1, t2, t3,
																t4);
	}

	template<class T1, class T2, class T3, class T4, class T5>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&> operator()(
		T1& t1,
		const T2& t2, const T3& t3, const T4& t4, const T5& t5)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&>(t1,
			t2, t3, t4, t5);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&, const T6&>
	operator()(const T1& t1,
		const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&,
		const T6&>(t1, t2, t3, t4, t5, t6);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6,
	class T7>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&, const T6&,
	const T7&> operator()(const T1& t1,
		const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6,
		const T7& t7)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&,
		const T6&, const T7&>(t1, t2, t3, t4, t5, t6, t7);
	}

	template
	<class T1, class T2, class T3, class T4, class T5,
	 class T6, class T7, class T8>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&, const T6&,
	const T7&, const T8&> operator()(const T1& t1,
		const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6,
		const T7& t7, const T8& t8)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&,
		const T6&, const T7&, const T8&>(
			t1, t2, t3, t4, t5, t6, t7, t8);
	}

	template
	<class T1, class T2, class T3, class T4, class T5,
	 class T6, class T7, class T8, class T9>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&, const T6&,
	const T7&, const T8&, const T9&> operator()(const T1& t1,
		const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6,
		const T7& t7, const T8& t8, const T9& t9)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&,
		const T6&, const T7&, const T8&, const T9&>(
			t1, t2, t3, t4, t5, t6, t7, t8, t9);
	}

	template
	<class T1, class T2, class T3, class T4, class T5,
	 class T6, class T7, class T8, class T9, class T10>
	ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&, const T6&,
	const T7&, const T8&, const T9&, const T10&> operator()(const T1& t1,
		const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6,
		const T7& t7, const T8& t8, const T9& t9, const T10& t10)
	{
		return ivl::lvalue_details::lval_base<const T1&, const T2&, const T3&, const T4&, const T5&,
		const T6&, const T7&, const T8&, const T9&, const T10&>(
			t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
	}
*/
};

} /* namespace core_details */

static core_details::_class _;

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_UNDERSCORE_UNDERSCORE_HPP
