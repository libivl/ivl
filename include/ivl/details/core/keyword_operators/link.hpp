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

#ifndef IVL_CORE_DETAILS_KEYWORD_OPERATORS_LINK_HPP
#define IVL_CORE_DETAILS_KEYWORD_OPERATORS_LINK_HPP

namespace ivl {

namespace core_details {

template<class A, class IS_ITER_C_PTR>
struct storable_link_ops_4 { };

template<class A>
struct storable_link_ops_4<A, types::t_true>
{
	typedef typename types::change_data_class_set<
		data::const_link, A>::type type;
	static inline type from(const A& a) { return type(a); }
};

template<class A>
struct storable_link_ops_4<A, types::t_false>
{
	typedef typename types::change_data_class_set<
		data::const_link, A>::type type;
	static inline type from(const A& a)
	{
		ivl::array<typename A::elem_type, data::ref_iterator<> >
			data(a.c_ptr(), a.length());
		return type(a.size(), data);
	}
};

template<class A, class HAS_C_PTR>
struct storable_link_ops_3 { };

template<class A>
struct storable_link_ops_3<A, types::t_true> :
	public storable_link_ops_4<A,
		typename types::is_ptr<typename A::const_iterator>::type>
{ };

template<class A>
struct storable_link_ops_3<A, types::t_false>
{
	typedef typename types::change_data_class_set<
		data::storable_link, A>::type type;
	static inline type from(const A& a)
	{
		void* c_data = malloc(sizeof(typename A::elem_type) * a.length());
		array<typename A::elem_type, data::const_link>
			data(c_data, a.length());
		// copy the data to out new array, which is a reference to a pointer
		// that needs to be deallocated.
		data = a;
		type r(a.size(), data);
		r.set_free();
		return r;
	}
};

// ---

template<class A, class IS_IVL_ARRAY>
struct storable_link_ops_2 { };

template<class A>
struct storable_link_ops_2<A, types::t_false>
{
	typedef const A& type;
	static inline type from(type a) { return a; }
};

template<class A>
struct storable_link_ops_2<A, types::t_true> :
	public storable_link_ops_3<A, typename A::has_c_ptr>
{ };

// ---

template<class A>
struct storable_link_ops : public storable_link_ops_2<A,
	typename types::is_ivl_array<A>::type>
{ };

} /* namespace core_details */

template<class A>
typename core_details::storable_link_ops<A>::type storable_link(const A& a)
{
	return core_details::storable_link_ops<A>::from(a);
}

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_KEYWORD_OPERATORS_LINK_HPP
