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

#ifndef IVL_ARRAY_DETAILS_ARRAY_HPP
#define IVL_ARRAY_DETAILS_ARRAY_HPP

namespace ivl {

#include "specialization/array_class.hpp"

#include "specialization/empty_class.hpp"

#include "specialization/blackhole_class.hpp"

#include "specialization/little_class.hpp"

#include "specialization/ref_iterator_class.hpp"

#include "specialization/range_class.hpp"

#include "specialization/val_repeat_class.hpp"

#include "specialization/ref_val_repeat_class.hpp"

#include "specialization/fixed_val_repeat_class.hpp"

#include "specialization/fixed_class.hpp"

#include "specialization/binary_elem_func_ptr_class.hpp"

#include "specialization/binary_elem_func_class.hpp"

#include "specialization/unary_elem_func_class.hpp"

#include "specialization/row_elem_func_class_2d.hpp"

#include "specialization/row_elem_func_class_nd.hpp"

//#include "specialization/force_class.hpp"
#include "specialization/wrap_array_class.hpp"

#include "specialization/member_class.hpp"

#include "specialization/mask_class.hpp"

#include "specialization/indirect_class.hpp"

#include "specialization/slice_class.hpp"

#include "specialization/subarray_class.hpp"

#include "specialization/catarray_class.hpp"

#include "specialization/outer_class.hpp"

//--------------------------------------------------------------
// array MEMBER FUNCTIONS


//! print an array
	/*
template<class T>
std::ostream& print(std::ostream& os,
    const array<T, data::normal, types::term>& in);
*/

namespace array_details {

// forward declaration for casting recursivity.
/*
template <class TO, class FROM> class elem_cast;

template <class S, class T, class D, class P>
struct cast
{
	typedef typename types::to_type<S, array<T, D, P> >::type
		::create_similar return_type;
};
*/

} /* namespace array_details */

template <class T, class S, class J, class D>
void copy(array<T, S>& out, const array<J, D>& in)
{
	CHECK(out.length() == in.length(), erange);
	loops::loop<loops::assign_copy_class<T&, const J&> >(
		out.derived(), in.derived());
}

template <class T, class S, class J, class D>
void copy_out(array<T, S>& out, const array<J, D>& in)
{
	CHECK(out.length() <= in.length(), erange);
	typename array<J, D>::const_iterator it_src = in.begin();
	typename array<T, S>::iterator it_end = out.end();
	typename array<T, S>::iterator it = out.begin();

	while (it != it_end) *it++ = *it_src++;
}

template <class T, class S, class J, class D>
void copy_n(array<T, S>& out, const array<J, D>& in, int n)
{
	/* TODO: would be nice
	CHECK(out.length() <= in.length(), erange);
	loops::loop_n<loops::assign_copy_class<T, J> >
		(out.derived(), in.derived(), n);
	*/
	typename array<J, D>::const_iterator it_src = in.begin();
	typename array<T, S>::iterator it = out.begin();

	while (n--) *it++ = *it_src++;
}

template <class T, class S, class J>
void copy(array<T, S>& out, const J* it_src)
{
	CHECK(it_src != NULL, einvalid);

	typename array<T, S>::iterator it_end = out.end();
	typename array<T, S>::iterator it = out.begin();

	while (it != it_end)
		*it++ = cast<T>(*it_src++);
}

template <class T, class S>
void copy(array<T, S>& out, const T& val,
		types::term as_element)
{
	typename array<T, S>::iterator it_end = out.end();
	typename array<T, S>::iterator it = out.begin();

	while (it != it_end)
		*(it++) = (val);
}

template <class T, class D>
std::ostream& print(std::ostream&, const array<T, D>&);


template<class T>
inline
void elem_print(std::ostream& os, const T& val)
{
	os << val << " ";
}


template<>
inline
void elem_print<float>(std::ostream& os, const float& val)
{
	os << std::setw(11);
	if(math::ivl_isnan(val))
		os << "NaN";
	else if(!math::ivl_finite(val))
		os << "Inf";
	else
		os << val;
	os << " ";
}

template<>
inline
void elem_print<double>(std::ostream& os, const double& val)
{
	os << std::setw(11);
	if(math::ivl_isnan(val))
		os << "NaN";
	else if(!math::ivl_finite(val))
		os << "Inf";
	else
		os << val;
	os << " ";
}



namespace array_details {

template <class T>
struct print_init
{
	print_init(std::ostream& os) {}
};

template<>
struct print_init<float>
{
	std::ostream& os;
	std::ios::fmtflags saveflags;
	print_init(std::ostream& os) : os(os), saveflags(os.flags())
	{
		os << std::fixed << std::setprecision(4);
	}
	~print_init()
	{
		os.flags(saveflags);
	}
};

template<>
struct print_init<double>
{
	std::ostream& os;
	std::ios::fmtflags saveflags;
	print_init(std::ostream& os) : os(os), saveflags(os.flags())
	{
		os << std::fixed << std::setprecision(4);
	}
	~print_init()
	{
		os.flags(saveflags);
	}
};

} /* namespace array_details */


template <class T, class S>
std::ostream& print(std::ostream& os, const ivl::array<T, S>& in)
{
	array_details::print_init<T> init(os);

	os << "[ " ;
	for(typename ivl::array<T, S>::const_iterator it = in.begin();
		it != in.end(); it++) {
			elem_print(os, *it);
		}
	os << "]";

	return os;
}


} // namespace ivl

#endif // IVL_ARRAY_DETAILS_ARRAY_HPP
