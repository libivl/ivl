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

#ifndef IVL_CORE_DETAILS_KEYWORD_OPERATORS_RET_HPP
#define IVL_CORE_DETAILS_KEYWORD_OPERATORS_RET_HPP

namespace ivl {

template<
class T1, class T2 = types::skip,
class T3 = types::skip, class T4 = types::skip,
class T5 = types::skip, class T6 = types::skip,
class T7 = types::skip, class T8 = types::skip,
class T9 = types::skip, class T10 = types::skip >
class ret;

template <class T>
class ret<T, types::skip,
	types::skip, types::skip,
	types::skip, types::skip,
	types::skip, types::skip,
	types::skip, types::skip> :
		public //ivl::scalar<T>//TODO:t_if
			types::t_if<types::is_builtin<T>, ivl::scalar<T>, T>::type
{
	typedef typename types::t_if<types::is_builtin<T>, ivl::scalar<T>, T>
		::type prv_base_class;
public:
	typedef prv_base_class ret_base_class;
	T& ret_base() { return static_cast<T&>(*this); }
	const T& ret_base() const { return static_cast<const T&>(*this); }

	ret() { }
	ret(const ret& x) : prv_base_class(static_cast<const T&>(x)) { }
	// other array constructors, just pass any template arguments, up to four.
	template<class A1>
	ret(const A1& a1) : prv_base_class(a1) { }
	template<class A1, class A2>
	ret(const A1& a1, const A2& a2) : prv_base_class(a1, a2) { }
	template<class A1, class A2, class A3>
	ret(const A1& a1, const A2& a2, const A3& a3) 
		: prv_base_class(a1, a2, a3) { }
	template<class A1, class A2, class A3, class A4>
	ret(const A1& a1, const A2& a2, const A3& a3, const A4& a4)
		: prv_base_class(a1, a2, a3, a4) { }

	ret& operator=(const ret& x)
	{
		// do not propagate copy constructor normally
		// as this would ruin the case ret = ret which
		// has to be swapped, so we need ret_base() = ret.
		prv_base_class::operator=(x);
		return *this;
	}
	template<class K>
	ret& operator=(const K& x)
	{
		prv_base_class::operator=(x);
		return *this;
	}
};

namespace core_details {

template <class T, class NOT_BARE>
struct ret_t_op
{
	typedef typename types::t_if<types::is_ivl_array<T>, ret<T>, T>::type type;
};

template <class T>
struct ret_t_op<T, types::t_true>
{
	typedef T type;
};

template <class T>
struct ret_t : public ret_t_op<T,
	typename types::t_or<types::is_ref<T>, types::is_ptr<T> >::type> { };

} /* namespace core_details */

template<
class T1, class T2,
class T3, class T4,
class T5, class T6,
class T7, class T8,
class T9, class T10>
class ret
: public
ivl::tuple<
typename core_details::ret_t<T1>::type, typename core_details::ret_t<T2>::type,
typename core_details::ret_t<T3>::type, typename core_details::ret_t<T4>::type,
typename core_details::ret_t<T5>::type, typename core_details::ret_t<T6>::type,
typename core_details::ret_t<T7>::type, typename core_details::ret_t<T8>::type,
typename core_details::ret_t<T9>::type, typename core_details::ret_t<T10>::type>
{
	typedef ivl::tuple<
typename core_details::ret_t<T1>::type, typename core_details::ret_t<T2>::type,
typename core_details::ret_t<T3>::type, typename core_details::ret_t<T4>::type,
typename core_details::ret_t<T5>::type, typename core_details::ret_t<T6>::type,
typename core_details::ret_t<T7>::type, typename core_details::ret_t<T8>::type,
typename core_details::ret_t<T9>::type, typename core_details::ret_t<T10>::type>
	tpl;
public:
	ret() {}
	ret(const ret& a) : tpl(a) { }
	template<class F>
	ret(const F& f) : tpl(f) { }
};

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_KEYWORD_OPERATORS_RET_HPP
