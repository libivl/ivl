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

#ifndef IVL_ARRAY_DETAILS_ELEM_FUNC_ARRAY_HPP
#define IVL_ARRAY_DETAILS_ELEM_FUNC_ARRAY_HPP


namespace ivl {

namespace data {

template <class T, template <typename, typename, typename> class A, class DI,
	template<typename, typename, typename> class F, class A1, class A2>
class elem_func_binary_set
{
};

template <template<typename, typename, typename> class F, class A1, class A2>
struct use_elem_func_binary_set
{
	template <class T, template <typename, typename, typename> class A,
		class DERIVED_CLASS>
	struct instance
	{
		typedef elem_func_binary_set <T, A, DERIVED_CLASS, F, A1, A2> type;
	};
};

template <class T, class DI,
	template<typename, typename, typename> class F, class A1, class A2>
class elem_func_binary_set<T, array, DI, F, A1, A2>
{
private:
	typedef elem_func_binary_set<T, array, DI, F, A1, A2> this_type;
	const A1& in1;
	const A2& in2;
	typedef typename types::elem_func_binary_info<T, F, A1, A2, DI>::elem_type1 elem_type1;
	typedef typename types::elem_func_binary_info<T, F, A1, A2, DI>::elem_type2 elem_type2;

public:
	typedef typename types::elem_func_binary_info<T, F, A1, A2, DI>::
		created_data_class_set created_data_class_set;


	elem_func_binary_set(const A1& in_array1, const A2& in_array2) :
		in1(in_array1), in2(in_array2) {};

	// for array<T>

	size_t length() const
	{
		CHECK(in1.derived().length() == in2.derived().length(), eshape);
		return in1.derived().length();
	}

	T operator[](size_t i) const
	{
		return (F<T, elem_type1, elem_type2>::elem_op(in1.derived()[i], in2.derived()[i]));
	}

	// no resize

	struct iterator : public data::index_iterator<T, this_type>
	{
		iterator(this_type& me, size_t pos) : data::index_iterator<T, this_type> (me, pos) { };
	};
	struct const_iterator : public data::index_iterator<const T, this_type>
	{
		const_iterator(this_type& me, size_t pos) : data::index_iterator<const T, this_type> (me, pos) { };
	};

	iterator begin() { return iterator(*this, 0); }
	iterator end() { return iterator(*this, length()); }
	const_iterator begin() const { return const_iterator(*this, 0); }
	const_iterator end() const { return const_iterator(*this, length()); }


	// no c_ptr
};







} //namespace data

} //namespace ivl


#endif // IVL_ARRAY_DETAILS_ELEM_FUNC_ARRAY_HPP
