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

#include "image.hpp"
#include "../../exception.hpp"

namespace ivl {
namespace image_details {
// ...
} /* namespace iamge_details */

// --------------------------------------------------------
// Print functions
/*
template<class T, class D>
std::ostream& print_array_nd (std::ostream& os, const array_nd<T,D>& a, bool float_point = false)
{
	std::ios::fmtflags saveflags = os.flags(); // save formatting flags

	if(float_point)
		os << std::fixed << std::setprecision(4);

	if (a.ndims() == 1) {
		os << "[";
		for (size_t j = 0; j < a.length(); ++j) {
			print_nd_val(os, a[j]);
		}
		os << "]";

		os.flags(saveflags) ; // restore formatting flags
		return os;
	}

	size_array indices(a.ndims(), size_t(0));
	size_t i, offs;
	while (true) {
		offs = 0;
		if (a.ndims() > 2) {
			// compute offset for block
			for (size_t j = 2; j < a.ndims(); j++)
				offs += indices[j] * a.stride()[j];
			// print coordinates
			os << std::endl << "[";
			for (size_t j = a.ndims() - 1; j > 1; j--)
				os << (j < a.ndims() - 1 ? ", " : "") << indices[j];
			os << "]" << std::endl;
		}
		// print current 2-d block
		for (size_t k = 0; k < a.size_nd()[0]; ++k) {
			for (size_t j = 0; j < a.size_nd()[1]; ++j)
				print_nd_val(os, a[offs + j * a.stride()[1] + k]);
			os << std::endl;
		}
		// increment indices
		bool more = false;
		i = 1;
		while (++i < a.ndims()) // while (0 < i--)
			if (++indices[i] < a.size_nd()[i]) {
				more = true;
				break;
			} else
				indices[i] = 0;	// carry to more-significant index

		if (!more)
			break; // No more elements.
	}
	if (a.ndims() == 1)
		os << "]";
	os.flags(saveflags) ; // restore formatting flags
	return os;
}
*/


} /* namespace ivl */
