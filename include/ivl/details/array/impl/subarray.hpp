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

#ifndef IVL_DETAILS_ARRAY_SUBARRAY_HPP
#define IVL_DETAILS_ARRAY_SUBARRAY_HPP

namespace ivl {

namespace array_details {

template <class A, class I>
struct subarray_result
{
	typedef typename types::t_if<types::is_const<A>,
		const typename A::derived_type, typename A::derived_type>::type a;

	typedef typename types::change_data_class_set<
		data::subarray<a, I>, typename A::derived_type>::type type;
};

} /* namespace array_details */

template <class A, class I>
class subarray : public array_details::subarray_result<A, I>::type
{
public:
	//operator subarray&() const { } //TODO: lets see..
	//subarray& operator*() { return const_cast<subarray&>(*this); }
	subarray& ref() { return *this; }

	typedef typename array_details::subarray_result<A, I>::type base_class;

	typedef typename base_class::elem_type elem_type;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	subarray() {}

	subarray(A& a, const I& i) { this->setref(a.derived(), i); }

	subarray(const subarray& a) : base_class(a.derived()) { }

	template<class J, class S>
	explicit subarray(array<J, S>& o) : base_class(o) { }

	template<class J, class S>
	explicit subarray(const array<J, S>& o) : base_class(o) { }


	using base_class::operator();

	//using base_class::operator=;
	template<class K>
	subarray& operator=(const K& k)
		{ base_class::operator=(k); return *this; }

	subarray& operator=(const subarray& o)
		{ base_class::operator=(o); return *this; }

	/*
	subarray& operator=(const elem_type& o)
	{ base_class::operator=(o); return *this; }

	template <class S, class K>
	subarray& operator=(const ivl::array_nd<elem_type, S, K>& o)
	{ base_class::operator=(o); return *this; }

	template <class S, class K>
	subarray& operator=(const ivl::array<elem_type, S, K>& o)
	{ base_class::operator=(o); return *this; }
	*/

};

} /* namespace ivl */

#endif // IVL_DETAILS_ARRAY_SUBARRAY_HPP
