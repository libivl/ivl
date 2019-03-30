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

#ifndef IVL_CORE_DETAILS_CONVERSIONS_ATTR_HPP
#define IVL_CORE_DETAILS_CONVERSIONS_ATTR_HPP

namespace ivl {
namespace conversions {

struct ro;
struct wo;
struct rw;

struct normal;

template <class T>
struct get_access_type
{
	typedef ro type;
};

// ---------------------------
/*
template <class ARRAY_TYPE, class CONV_TYPE, class ACCESS_TYPE =
	typename get_access_type<CONV_TYPE>::type>
class attr
{
};
*/
namespace conversions_details {

template <class A>
class wrap_op :
	public types::change_data_class_set<A, data::wrap_array<A> >::type
{
	typedef typename types::change_data_class_set<A,
		data::wrap_array<A> >::type base_class;
public:
	template <class K>
	wrap_op(K& k) : base_class(k) { }
	wrap_op(const wrap_op& k) : base_class(k) { }
	A& ref() { return *this; }
	typename types::apply_const<A&>::type ref() const { return *this; }
};

// ---------------------------

// normal conversion

template<class A, class D, class C, class M>
class attr_op
{
};

// ---

template<class A, class D>
class attr_op<A, D, normal, ro> :
	public types::normal_type<A>::type
{
	typedef typename types::normal_type<A>::type base_class;
public:
	template <class K>
	attr_op(K& k) : base_class(k) { }
	attr_op(const attr_op& k) : base_class(k) { }
	base_class& ref() { return *this; }
	const base_class& ref() const { return *this; }
};

template<class A, class D>
class attr_op<A, D, normal, wo> :
	public types::normal_type<A>::type
{
	typedef typename types::normal_type<A>::type base_class;
	base_class& base() { return *this; }
	A* tmp;
public:
	attr_op(A& k) : tmp(&k) { }
	attr_op(const attr_op& k) : tmp(&k) { }
	~attr_op() { *tmp = base(); /* iavr: base -> base() */  /*(*tmp).swap(base());*/ }
	base_class& ref() { return *this; }
	const base_class& ref() const { return *this; }
};

template<class A, class D>
class attr_op<A, D, normal, rw> :
	public types::normal_type<A>::type
{
	typedef typename types::normal_type<A>::type base_class;
	base_class& base() { return *this; }
	A* tmp;
public:
	attr_op(A& k) : tmp(&k) { base() = k; /*base().swap(k);*/ }
	attr_op(const attr_op& k) : tmp(&k) { base() = k; /*base().swap(k);*/ }
	~attr_op() { *tmp = base(); /* iavr: base -> base() */  /*(*tmp).swap(base());*/ }
	base_class& ref() { return *this; }
	const base_class& ref() const { return *this; }
};

// or maybe only for normal ?
template <class A, class D, class M, class IS_IVL_ARRAY>
class attr_2 :
	public conversions_details::attr_op<A, typename A::data_type, D, M>
{
	typedef conversions_details::attr_op<A, typename A::data_type, D, M>
		base_class;
public:
	typedef attr_2 type;
	template<class K>
	attr_2(K& k) : base_class(k) { }
	attr_2(const attr_2& k) : base_class(k) { }
};

template <class A, class D, class M>
class attr_2<A, D, M, types::t_false>
{
public:
	typedef A& type;
};

} /* namespace conversions_details */
/*
template <class A, class M>
class attr<A, normal, M> :
	public conversions_details::attr_op<A, typename A::data_type, normal, M>
{
	typedef conversions_details::attr_op<A, typename A::data_type, normal, M>
		base_class;
public:
	template<class K>
	attr(K& k) : base_class(k) { }
	attr(const attr& k) : base_class(k) { }
};*/


template <class ARRAY_TYPE, class CONV_TYPE, class ACCESS_TYPE =
	typename get_access_type<CONV_TYPE>::type>
class attr :
	public conversions_details::attr_2<ARRAY_TYPE, CONV_TYPE, ACCESS_TYPE,
		typename types::is_ivl_array<ARRAY_TYPE>::type>
{
	typedef conversions_details::attr_2<ARRAY_TYPE, CONV_TYPE, ACCESS_TYPE,
		typename types::is_ivl_array<ARRAY_TYPE>::type> base_class;
public:
	template<class K>
	attr(K& k) : base_class(k) { }
	attr(const attr& k) : base_class(k) { }
};
// ---------------------------


} /* namespace conversions */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_CONVERSIONS_ATTR_HPP
