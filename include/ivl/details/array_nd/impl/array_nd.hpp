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

#ifndef IVL_ARRAY_ND_DETAILS_ARRAY_ND_BASE_HPP
#define IVL_ARRAY_ND_DETAILS_ARRAY_ND_BASE_HPP

namespace ivl {

template<class T, class S> class array_nd;
//template<class T> class gslice_array;
//template<class T, class S, bool C> class sub_array;

typedef array_nd<bool, mem> bool_array_nd;

//print an array_nd
//template<class T>
//std::ostream& print(std::ostream& os, const array_nd<T, array_nd<T, types::term> >& a);


#include "specialization/array_nd_class.hpp"
#include "specialization/array_nd_2d_class.hpp"
#include "specialization/array_nd_image_class.hpp"
//#include "specialization/force_class.hpp"
#include "specialization/wrap_array_nd_class.hpp"
#include "specialization/subarray_class.hpp"
#include "specialization/catarray_class.hpp"
#include "specialization/unary_elem_func_nd_class.hpp"
#include "specialization/binary_elem_func_nd_class.hpp"
#include "specialization/binary_elem_func_ptr_nd_class.hpp"
//#include "specialization/outer_nd_class.hpp"


// --------------------------------------------------------
// Print functions

namespace array_nd_details {

template<class T>
inline
void print_nd_val(std::ostream& os, const T& val)
{
	os << std::setw(6) << val;
}

template<>
inline
void print_nd_val<float>(std::ostream& os, const float& val)
{
	os << std::setw(11);
	if(ivl::math::ivl_isnan(val))
		os << "NaN";
	else if(!ivl::math::ivl_finite(val))
		os << "Inf";
	else
		os << val;
	os << " ";
}

template<>
inline
void print_nd_val<double>(std::ostream& os, const double& val)
{
	os << std::setw(11);
	if(ivl::math::ivl_isnan(val))
		os << "NaN";
	else if(!ivl::math::ivl_finite(val))
		os << "Inf";
	else
		os << val;
	os << " ";
}

template<class T, class D>
std::ostream& print_array_nd (std::ostream& os,
			const array_nd<T, D>& a, bool float_point = false)
{
	std::ios::fmtflags saveflags = os.flags(); // save formatting flags

	if(float_point)
		os << std::fixed << std::setprecision(4);

	if (a.ndims() == 0) {
		os << "[unassigned]";
		return os;
	}
	os << "\n"; // added newline before printing array_nd [kimonas]

	if (a.ndims() == 1) {
		os << "[";
		for (size_t j = 0; j < a.length(); ++j) {
			print_nd_val(os, a(ivl::idx(j)));
		}
		os << "]";

		os.flags(saveflags) ; // restore formatting flags
		return os;
	}

	array<size_t, tiny> id(a.ndims(), size_t(0));//todo:here!
	bool stop = false;

	do {
		size_t j, k;

		if (a.ndims() > 2) {
			// print coordinates
			os << std::endl << "[";
			for (j = a.ndims() - 1; j > 1; j--)
				os << (j < a.ndims() - 1 ? ", " : "") << id[j];
			os << "]" << std::endl;
		}

		// print current 2-d block
		for (k = 0; k < a.size_nd()[0]; ++k) {
			for (j = 0; j < a.size_nd()[1]; ++j) {
				id[0] = k;
				id[1] = j;
				print_nd_val(os, a(id));
			}
			os << std::endl;
		}

		// increment indices
		if(a.ndims() > 2)
		{
			for (j = 2; j < a.ndims(); j++)
				if(++id[j] >= a.size_nd(j)) {
					if(j == a.ndims() - 1)
						stop = true;
					else {
						id[j] = 0;
					}
				} else
					break;

		}
		else
			stop  = true;

	} while(!stop);

	os.flags(saveflags) ; // restore formatting flags
	return os;
}

} /* namespace array_nd_details */

template <class T, class D>
inline
std::ostream& print(std::ostream& os, const array_nd<T, D>& in)
{
	return array_nd_details::print_array_nd(os, in);
}

template<class D>
inline
std::ostream& print(std::ostream& os, const array_nd<double, D>& in)
{
	return array_nd_details::print_array_nd(os, in, true);
}

template <class D>
inline
std::ostream& print(std::ostream& os, const array_nd<float, D>& in)
{
	return array_nd_details::print_array_nd(os, in, true);
}

template <class T, class D>
std::ostream& array_common_base<array_nd<T, D> >::
	print(std::ostream& os) const
{
	return ivl::print(os, to_array_nd());
}

} // namespace ivl

#endif // IVL_ARRAY_ND_DETAILS_ARRAY_ND_BASE_HPP
