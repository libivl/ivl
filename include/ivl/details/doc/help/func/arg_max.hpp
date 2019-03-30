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

#ifndef IVL_DOC_HELP_FUNC_ARG_MAX_HPP
#define IVL_DOC_HELP_FUNC_ARG_MAX_HPP

//-----------------------------------------------------------------------------

namespace ivl {
namespace doc {

//-----------------------------------------------------------------------------

template <>
struct help_title <fun::arg_max>
{
	template <typename OS>
	OS& operator()(OS& os) { return os << "offset of maximum element(s)"; }
};

//-----------------------------------------------------------------------------

template <>
struct help_body <fun::arg_max>
{

template <typename OS>
OS& operator()(OS& os)
{

//-----------------------------------------------------------------------------

	os << para <<
		syntax["p = arg_max(a)"] << " returns the offset " << code["p"] << " of the first instance of the greatest element of " << t_array << " " << code["a"] << ". If " << code["a"] << " is an empty array of type " << type["T"] << ", " << code["-1"] << " is returned instead (the greatest value of type " << t_size_t << "). If " << code["a"] << " is " << t_array_nd << ", " << code["arg_max(a)"] << " is equivalent to " << code["arg_max[_0](a)"] << " (see below). E.g."
	<< sample;

	array<int> a = rand(6, -9, 9);

	os << "a = " << emph[a] << nl;

	os << "arg_max(a) = " << emph[arg_max(a)] << nl;
	os << "int(arg_max(array <double>())) = " <<
		emph[int(arg_max(array <double>()))] << nl;

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax["p = arg_max[d](a)"] << " operates on strides along dimension " << code["d"] << " of " << t_array_nd << " " << code["a"] << ", in particular column-wise (dimension " << code["_0"] << ") or row-wise (dimension " << code["_1"] << "). It returns " << t_array_nd << " " << code["p"] << " of the same dimensions and size as " << code["a"] << ", except that it is singleton in dimension " << code["d"] << ". E.g."
	<< sample;

	array_2d<int> b = rand(idx(3, 4), -9, 9);

	os << "b = " << emph[b] << par;

	for(size_t d = 0; d < b.ndims();)
	{
// 		TODO: fix vec_func
// 		os << "arg_max[_" << d << "](b) = " << emph[arg_max[dim(d)](b)];
			os << "arg_max[_" << d << "](b) = " << todo;
			if (++d < b.ndims()) os << par;
	}

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax["arg_max[comp=f][def=e]"] << " uses comparison functor " << code["f"] << " instead of " << fn::lt << " (less than) and default functor " << code["e"] << " instead of " << f_inf_min << " (minus infinity or minimum). The latter is used to specify a default value when a single, empty array is given as input. E.g."
	<< sample;

	os << "arg_max [comp=fn::gt] [def=fn::inf_max] (a) = arg_min(a) = " <<
		emph[arg_max [comp=fn::gt] [def=fn::inf_max] (a)] << nl;

//-----------------------------------------------------------------------------

	return os << ~out;
}

};

//-----------------------------------------------------------------------------

}  // namespace doc
}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DOC_HELP_FUNC_ARG_MAX_HPP
