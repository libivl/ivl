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

#ifndef IVL_DOC_HELP_FUNC_MIN_HPP
#define IVL_DOC_HELP_FUNC_MIN_HPP

//-----------------------------------------------------------------------------

namespace ivl {
namespace doc {

//-----------------------------------------------------------------------------

template <>
struct help_title <fun::min>
{
	template <typename OS>
	void operator()(OS& os) { os << "minimum element(s)"; }
};

//-----------------------------------------------------------------------------

template <>
struct help_body <fun::min>
{

template <typename OS>
void operator()(OS& os)
{

//-----------------------------------------------------------------------------

	os << para <<
		syntax["m = min(a, b)"] << " returns " << t_array << " " << code["m"] << " of the same size as " << t_array << "s " << code["a"] << ", " << code["b"] << ", containing their element-wise minimum. Arrays " << code["a"] << ", " << code["b"] << " should be of the same size but can be of different types, in which case one is promoted to match the other. If either is a scalar, the minimum is taken between this scalar and the elements of the other. If both are scalar, the scalar minimum is returned. " << min << " operates on arbitrary types as long as operator " << code["<"] << " is defined. E.g."
	<< sample;

	array<int> a = rand(6, -9, 9);
	array<int> b = rand(6, -9, 9);

	os << "a = " << emph[a] << nl;
	os << "b = " << emph[b] << par;

	os << "min(a, b) = " << emph[min(a, b)] << nl;
	os << "min(a, 0) = " << emph[min(a, 0)] << nl;
	os << "min(-3.5, b) = " << emph[min(-3.5, b)] << nl;
	os << "min('a', 'z') = " << emph[min('a', 'z')] << nl;

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax["m = min(a)"] << " returns the least element " << code["m"] << " of " << code["a"] << ". If " << code["a"] << " is an empty " << t_array << " of type " << type["T"] << ", " << f_inf_max << " " << code["<T>()"] << " is returned instead, which is the closest approximation of plus infinity, depending on T. If " << code["a"] << " is " << t_array_nd << ", " << code["min(a)"] << " is equivalent to " << code["min[_0](a)"] << " (see below). E.g."
	<< sample;

	os << "min(a) = " << emph[min(a)] << nl;
	os << "min(array <double>()) = " <<
		emph[min(array <double>())] << nl;

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax["(_, m, p) = min++(a)"] << " returns the least element " << code["m"] << " of " << code["a"] << " and the offset " << code["p"] << " of the first occurrence of value " << code["m"] << " in " << code["a"] << ". If " << code["a"] << " is an empty " << t_array << ", " << code["-1"] << " is returned for " << code["p"] << " (the least value of type " << t_size_t << "). If " << code["a"] << " is " << t_array_nd << ", this syntax is equivalent to " << code["(_, m, p) = min[_0]++(a)"] << " (see below). E.g."
	<< ~para;

	int m;
	size_t p;
	(_, m, p) = min++(a);

	os << lst << "(_, m, p) = min++(a);" << ~lst;
	os << out << "(_, m, p) = " << emph[(_, m, p)] << ~out;

	(_, m, p) = min++(array<char>());

	os << lst << "(_, m, p) = min++(array <char>());" << ~lst;
	os << out << "(_, m, int(p)) = " << emph[(_, m, int(p))] << ~out;

//-----------------------------------------------------------------------------

	{  // nd samples

//-----------------------------------------------------------------------------

	os << para <<
		syntax["m = min[d](a)"] << " operates on strides along dimension " << code["d"] << " of " << t_array_nd << " " << code["a"] << ", in particular column-wise (dimension " << code["_0"] << ") or row-wise (dimension " << code["_1"] << "). It returns " << t_array_nd << " " << code["m"] << " of the same dimensions and size as " << code["a"] << ", except that it is singleton in dimension " << code["d"] << ". E.g."
	<< sample;

	array_2d <int> c = rand(idx(3, 4), -9, 9);

	os << "c = " << emph[c] << par;

	for(size_t d = 0; d < c.ndims();)
	{
// 		TODO: fix vec_func
// 		os << "min[_" << d << "](c) = " << emph[min[dim(d)](c)];
			os << "min[_" << d << "](c) = " << todo;
			if (++d < c.ndims()) os << par;
	}

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax["(_, m, p) = min[d]++(a)"] << " operates on strides along dimension " << code["d"] << " of " << t_array_nd << " " << code["a"] << ", returning its least elements and their offsets in " << t_array_nd << " " << code["m"] << " and " << code["p"] << " respectively. E.g."
	<< ~para;

	array_2d <int> m;
	array_2d <size_t> p;

// 	TODO: fix vec_func
// 	(_, m, p) = min[_0]++(c);

	os << lst << "(_, m, p) = min[_0]++(c);" << ~lst;
// 	os << out << "p = " << emph[p] << ~out;
		os << out << "p = " << todo << ~out;

// 	TODO: fix vec_func
// 	(_, m, p) = min[_1]++(c);

	os << lst << "(_, m, p) = min[_1]++(c);" << ~lst;
// 	os << out << "p = " << emph[p] << ~out;
		os << out << "p = " << todo << ~out;

//-----------------------------------------------------------------------------

	os << para <<
		syntax["min[arg]"] << " is equivalent to " << arg_min << ", e.g."
	<< sample;

// 	TODO: fix vec_func
// 	os << "min[arg][_0](c) = " << min[arg](c) << nl;
		os << "min[arg][_0](c) = " << todo << nl;

//-----------------------------------------------------------------------------

	}  // nd samples

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax["min[comp=f]"] << " uses comparison functor " << code["f"] << " instead of " << fn::lt << " (less than, using operator " << code["<"] << "), e.g."
	<< sample;

	os << "min [comp=fn::gt] (a, b) = max(a, b) = " <<
		emph[min [comp=fn::gt] (a, b)] << nl;

//-----------------------------------------------------------------------------

	os << ~sample <<
		syntax["min[def=e]"] << " uses default functor " << code["e"] << " instead of " << f_inf_max << " (plus infinity or maximum), which is used to specify a default value when a single, empty array is given as input. E.g."
	<< sample;

	os << "min [comp=fn::gt] [def=fn::inf_min] (a) = max(a) = " <<
		emph[min [comp=fn::gt] [def=fn::inf_min] (a)] << nl;

//-----------------------------------------------------------------------------

	os << ~out;
}

};

//-----------------------------------------------------------------------------

}  // namespace doc
}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DOC_HELP_FUNC_MIN_HPP
