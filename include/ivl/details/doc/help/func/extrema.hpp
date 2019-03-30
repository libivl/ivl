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

//-----------------------------------------------------------------------------

#ifndef IVL_DOC_HELP_FUNC_EXTREMA_HPP
#define IVL_DOC_HELP_FUNC_EXTREMA_HPP

//-----------------------------------------------------------------------------

namespace ivl {
namespace doc {

//-----------------------------------------------------------------------------

template <>
struct help_title <fun::extrema>
{
	template <typename OS>
	void operator()(OS& os) { os << "minimum and maximum element(s)"; }
};

//-----------------------------------------------------------------------------

template <>
struct help_body <fun::extrema>
{

template <typename OS>
void operator()(OS& os)
{

//-----------------------------------------------------------------------------

	os << para <<
		syntax["(_, m, M) = extrema(a)"] <<
		" returns the least element " << code["m"] << " and the greatest element " << code["M"] << " of " << code["a"] << ". If " << code["a"] << " is an empty " << type["array"] << " of type " << code["T"] << ", " << f_inf_max << " " << code["<T>()"] << " and " << f_inf_min << " " << code["<T>()"] << " are returned instead, which are the closest approximations of plus and minus infinity respectively, depending on " << code["T"] << ". If " << code["a"] << " is " << type["array_nd"] << ", " << code["extrema(a)"] << " is equivalent to " << code["extrema[_0](a)"] << " (see below). E.g."
	<< sample;

	array<int> a = rand(6, -9, 9);

	os << "a = " << emph[a] << par;

	os << "extrema(a) = " << emph[extrema(a)] << nl;
	os << "extrema(array<double>()) = " <<
		emph[extrema(array<double>())];

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax ["(_, m, M) = extrema[d](a)"] <<
		" operates on strides along dimension " << code["d"] << " of " << type["array_nd"] << " " << code["a"] <<", in particular column-wise (dimension " << code["_0"] << ") or row-wise (dimension " << code["_1"] << ") if " << code["a"] << " is " << type["array_nd"] << ". It returns " << type["array_nd"] << " " << code["m"] << ", " << code["M"] << " of the same dimensions and size as " << code["a"] << ", except that they are singleton in dimension " << code["d"] << ". E.g."
	<< sample;

	array_2d <int> c = rand(idx(3, 4), -9, 9);

	os << "c = " << emph[c] << par;

	for(size_t d = 0; d < c.ndims();)
	{
// 		TODO: fix vec_func
// 		os << "extrema[_" << d << "](c) = " << emph[extrema[dim(d)](c)];
			os << "extrema[_" << d << "](c) = " << todo;
			if (++d < c.ndims()) os << par;
	}

//-----------------------------------------------------------------------------

	os << ~out;
}

};

//-----------------------------------------------------------------------------

}  // namespace doc
}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DOC_HELP_FUNC_EXTREMA_HPP
