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

#ifndef IVL_CORE_DETAILS_TYPES_CONSTANT_HPP
#define IVL_CORE_DETAILS_TYPES_CONSTANT_HPP

#include <algorithm>
#include <cmath>
#include <limits>
#include <complex>

// TODO: remove when integrating with ivl
#include <stdint.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

template <typename T, typename C>
struct constant
{
	typedef T type;
	T operator()() const
	{
		const C& c = static_cast <const C&>(*this);
		return static_cast <T> (c);
	}
};

template <typename S, typename T, typename C>
S& operator<<(S& s, const constant <T, C>& c) { return s << c(); }

//-----------------------------------------------------------------------------

template <typename T, T N>
struct c_integral : public constant <T, c_integral <T, N> >
{
	operator T() const { return N; }
};

template <typename T, T N>
struct c_integer : public c_integral <T, N> { };

template <typename T, T N>
struct c_enum : public c_integral <T, N> { };

//-----------------------------------------------------------------------------

template <bool B = true>
struct c_boolean : public c_integral <bool, B> { };

struct c_true  : public c_boolean <true> { };
struct c_false : public c_boolean <false> { };

template <char C = '\0'>
struct c_char : public c_integral <char, C> { };

template <unsigned char C = '\0'>
struct c_unsigned_char : public c_integral <unsigned char, C> { };

// // TODO: platform specific
// template <wchar_t C = '\0'>
// struct c_wchar_t : public c_integral <wchar_t, C> { };

//-----------------------------------------------------------------------------

template <short N = 0>
struct c_short : public c_integral <short, N> { };

template <unsigned short N = 0>
struct c_unsigned_short : public c_integral <unsigned short, N> { };

template <int N = 0>
struct c_int : public c_integral <int, N> { };

struct c_zero : public c_int <>  { };
struct c_one  : public c_int <1> { };
struct c_null : public c_zero    { };

template <unsigned N = 0>
struct c_unsigned : public c_integral <unsigned, N> { };

template <unsigned int N = 0>
struct c_unsigned_int : public c_integral <unsigned int, N> { };

template <long N = 0>
struct c_long : public c_integral <long, N> { };

template <unsigned long N = 0>
struct c_unsigned_long : public c_integral <unsigned long, N> { };

// // TODO: platform specific
// template <long long N = 0>
// struct c_long_long : public c_integral <long long, N> { };
//
// template <unsigned long long N = 0>
// struct c_unsigned_long_long : public c_integral <unsigned long long, N> { };

//-----------------------------------------------------------------------------

// // TODO: include when integrated with ivl
// template <size_t N = 0>
// struct c_size_t : public c_integral <size_t, N> { };

//-----------------------------------------------------------------------------

template <typename T, typename M, typename E>
struct c_scientific : public constant <T, c_scientific <T, M, E> >
{
	operator T() const { return M() * std::pow(T(10), T(E())); }
};

template <int M = 0, char E = '\0'>
struct c_float : public c_scientific <float, c_int <M>, c_char <E> > { };

template <long M = 0, short E = '\0'>
struct c_double : public c_scientific <double, c_long <M>, c_short <E> > { };

// // TODO: platform specific
// template <long long M = 0, short E = '\0'>
// struct c_long_double :
// 	public c_scientific <long double, c_long_long <M>, c_short <E> > { };

//-----------------------------------------------------------------------------

template <typename T, typename M, typename E>
struct c_norm_scientific : public constant <T, c_norm_scientific <T, M, E> >
{
	static T prev_pow_10(T x)
	{
		return x == 0 ? T(1) :
			std::pow(T(10), std::floor(std::log10(std::abs(x))));
	};

	operator T() const { return c_scientific <T, M, E>() / prev_pow_10(T(M())); }
};

template <int M = 0, char E = '\0'>
struct c_norm_float :
	public c_norm_scientific <float, c_int <M>, c_char <E> > { };

template <long M = 0, short E = '\0'>
struct c_norm_double :
	public c_norm_scientific <double, c_long <M>, c_short <E> > { };

// // TODO: platform specific
// template <long long M = 0, short E = '\0'>
// struct c_norm_long_double :
// 	public c_norm_scientific <long double, c_long_long <M>, c_short <E> > { };

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

class multi_char
{
	union
	{
		struct { int32_t i; char ipad; };
		struct { char p[5]; };
		struct { char a, b, c, d, e; };
	};

	multi_char(bool) : i(1) { }
	bool is_big()  const { return d != 0; }
	void flip() { std::swap(a, d); std::swap(b, c); }
	unsigned first() const { return a ? 0 : b ? 1 : c ? 2 : d ? 3 : 4; }

public:
	multi_char(int i = 0) : i(i), ipad(0) { if (!big()) flip(); }
	operator const char*() const { return p + first(); }
	static bool big() { return multi_char(true).is_big(); }
};

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

template <int N = 0>
struct c_multi_char : multi_char,
	public constant <const char*, c_multi_char <N> >
{
	c_multi_char() : multi_char(N) { }
};

//-----------------------------------------------------------------------------

namespace constant_details {

//-----------------------------------------------------------------------------

template <
	int N00 = 0, int N01 = 0, int N02 = 0, int N03 = 0, int N04 = 0,
	int N05 = 0, int N06 = 0, int N07 = 0, int N08 = 0, int N09 = 0,
	int N10 = 0, int N11 = 0, int N12 = 0, int N13 = 0, int N14 = 0,
	int N15 = 0, int N16 = 0, int N17 = 0, int N18 = 0, int N19 = 0,
	int N20 = 0, int N21 = 0, int N22 = 0, int N23 = 0, int N24 = 0,
	int N25 = 0, int N26 = 0, int N27 = 0, int N28 = 0, int N29 = 0,
	int N30 = 0, int N31 = 0, int N32 = 0, int N33 = 0, int N34 = 0,
	int N35 = 0, int N36 = 0, int N37 = 0, int N38 = 0, int N39 = 0,
	int N40 = 0, int N41 = 0, int N42 = 0, int N43 = 0, int N44 = 0,
	int N45 = 0, int N46 = 0, int N47 = 0, int N48 = 0, int N49 = 0,
	int N50 = 0, int N51 = 0, int N52 = 0, int N53 = 0, int N54 = 0,
	int N55 = 0, int N56 = 0, int N57 = 0, int N58 = 0, int N59 = 0,
	int N60 = 0, int N61 = 0, int N62 = 0, int N63 = 0, int N64 = 0,
	int N65 = 0, int N66 = 0, int N67 = 0, int N68 = 0, int N69 = 0,
	int N70 = 0, int N71 = 0, int N72 = 0, int N73 = 0, int N74 = 0,
	int N75 = 0, int N76 = 0, int N77 = 0, int N78 = 0, int N79 = 0,
	int N80 = 0, int N81 = 0, int N82 = 0, int N83 = 0, int N84 = 0,
	int N85 = 0, int N86 = 0, int N87 = 0, int N88 = 0, int N89 = 0,
	int N90 = 0, int N91 = 0, int N92 = 0, int N93 = 0, int N94 = 0,
	int N95 = 0, int N96 = 0, int N97 = 0, int N98 = 0, int N99 = 0
>
class c_string_base
{
	typedef c_multi_char <N00> first;

	typedef c_string_base <
		N01, N02, N03, N04, N05, N06, N07, N08, N09,
		N10, N11, N12, N13, N14, N15, N16, N17, N18, N19,
		N20, N21, N22, N23, N24, N25, N26, N27, N28, N29,
		N30, N31, N32, N33, N34, N35, N36, N37, N38, N39,
		N40, N41, N42, N43, N44, N45, N46, N47, N48, N49,
		N50, N51, N52, N53, N54, N55, N56, N57, N58, N59,
		N60, N61, N62, N63, N64, N65, N66, N67, N68, N69,
		N70, N71, N72, N73, N74, N75, N76, N77, N78, N79,
		N80, N81, N82, N83, N84, N85, N86, N87, N88, N89,
		N90, N91, N92, N93, N94, N95, N96, N97, N98, N99
	> shift;

public:

//-----------------------------------------------------------------------------

	enum { length = N00 == 0 ? 0 : shift::length + 4 };

	void copy(char* dest) const
	{
		if (N00 == 0)
			return;
		first f;
		*dest = *f;
		*(dest + 1) = *(f + 1);
		*(dest + 2) = *(f + 2);
		*(dest + 3) = *(f + 3);
		*(dest + 4) = *(f + 4);
		shift().copy(dest + 4);
	}

};

//-----------------------------------------------------------------------------

template <>
struct c_string_base <>
{
	enum { length = 0 };
	void copy(char*) const { }
};

//-----------------------------------------------------------------------------

template <
	int N00 = 0, int N01 = 0, int N02 = 0, int N03 = 0, int N04 = 0,
	int N05 = 0, int N06 = 0, int N07 = 0, int N08 = 0, int N09 = 0,
	int N10 = 0, int N11 = 0, int N12 = 0, int N13 = 0, int N14 = 0,
	int N15 = 0, int N16 = 0, int N17 = 0, int N18 = 0, int N19 = 0,
	int N20 = 0, int N21 = 0, int N22 = 0, int N23 = 0, int N24 = 0,
	int N25 = 0, int N26 = 0, int N27 = 0, int N28 = 0, int N29 = 0,
	int N30 = 0, int N31 = 0, int N32 = 0, int N33 = 0, int N34 = 0,
	int N35 = 0, int N36 = 0, int N37 = 0, int N38 = 0, int N39 = 0,
	int N40 = 0, int N41 = 0, int N42 = 0, int N43 = 0, int N44 = 0,
	int N45 = 0, int N46 = 0, int N47 = 0, int N48 = 0, int N49 = 0,
	int N50 = 0, int N51 = 0, int N52 = 0, int N53 = 0, int N54 = 0,
	int N55 = 0, int N56 = 0, int N57 = 0, int N58 = 0, int N59 = 0,
	int N60 = 0, int N61 = 0, int N62 = 0, int N63 = 0, int N64 = 0,
	int N65 = 0, int N66 = 0, int N67 = 0, int N68 = 0, int N69 = 0,
	int N70 = 0, int N71 = 0, int N72 = 0, int N73 = 0, int N74 = 0,
	int N75 = 0, int N76 = 0, int N77 = 0, int N78 = 0, int N79 = 0,
	int N80 = 0, int N81 = 0, int N82 = 0, int N83 = 0, int N84 = 0,
	int N85 = 0, int N86 = 0, int N87 = 0, int N88 = 0, int N89 = 0,
	int N90 = 0, int N91 = 0, int N92 = 0, int N93 = 0, int N94 = 0,
	int N95 = 0, int N96 = 0, int N97 = 0, int N98 = 0, int N99 = 0
>
class c_string :
	public constant <const char*, c_string <
		N00, N01, N02, N03, N04, N05, N06, N07, N08, N09,
		N10, N11, N12, N13, N14, N15, N16, N17, N18, N19,
		N20, N21, N22, N23, N24, N25, N26, N27, N28, N29,
		N30, N31, N32, N33, N34, N35, N36, N37, N38, N39,
		N40, N41, N42, N43, N44, N45, N46, N47, N48, N49,
		N50, N51, N52, N53, N54, N55, N56, N57, N58, N59,
		N60, N61, N62, N63, N64, N65, N66, N67, N68, N69,
		N70, N71, N72, N73, N74, N75, N76, N77, N78, N79,
		N80, N81, N82, N83, N84, N85, N86, N87, N88, N89,
		N90, N91, N92, N93, N94, N95, N96, N97, N98, N99
	> >

//-----------------------------------------------------------------------------

{
	typedef c_string_base <
		N00, N01, N02, N03, N04, N05, N06, N07, N08, N09,
		N10, N11, N12, N13, N14, N15, N16, N17, N18, N19,
		N20, N21, N22, N23, N24, N25, N26, N27, N28, N29,
		N30, N31, N32, N33, N34, N35, N36, N37, N38, N39,
		N40, N41, N42, N43, N44, N45, N46, N47, N48, N49,
		N50, N51, N52, N53, N54, N55, N56, N57, N58, N59,
		N60, N61, N62, N63, N64, N65, N66, N67, N68, N69,
		N70, N71, N72, N73, N74, N75, N76, N77, N78, N79,
		N80, N81, N82, N83, N84, N85, N86, N87, N88, N89,
		N90, N91, N92, N93, N94, N95, N96, N97, N98, N99
	> base;

	char c[base::length + 1];

public:
	c_string() { base().copy(c); }
	operator const char*() const { return c; }
};

//-----------------------------------------------------------------------------

template <
	typename T, unsigned L,
	T N00 = 0, T N01 = 0, T N02 = 0, T N03 = 0, T N04 = 0,
	T N05 = 0, T N06 = 0, T N07 = 0, T N08 = 0, T N09 = 0,
	T N10 = 0, T N11 = 0, T N12 = 0, T N13 = 0, T N14 = 0,
	T N15 = 0, T N16 = 0, T N17 = 0, T N18 = 0, T N19 = 0,
	T N20 = 0, T N21 = 0, T N22 = 0, T N23 = 0, T N24 = 0,
	T N25 = 0, T N26 = 0, T N27 = 0, T N28 = 0, T N29 = 0,
	T N30 = 0, T N31 = 0, T N32 = 0, T N33 = 0, T N34 = 0,
	T N35 = 0, T N36 = 0, T N37 = 0, T N38 = 0, T N39 = 0,
	T N40 = 0, T N41 = 0, T N42 = 0, T N43 = 0, T N44 = 0,
	T N45 = 0, T N46 = 0, T N47 = 0, T N48 = 0, T N49 = 0,
	T N50 = 0, T N51 = 0, T N52 = 0, T N53 = 0, T N54 = 0,
	T N55 = 0, T N56 = 0, T N57 = 0, T N58 = 0, T N59 = 0,
	T N60 = 0, T N61 = 0, T N62 = 0, T N63 = 0, T N64 = 0,
	T N65 = 0, T N66 = 0, T N67 = 0, T N68 = 0, T N69 = 0,
	T N70 = 0, T N71 = 0, T N72 = 0, T N73 = 0, T N74 = 0,
	T N75 = 0, T N76 = 0, T N77 = 0, T N78 = 0, T N79 = 0,
	T N80 = 0, T N81 = 0, T N82 = 0, T N83 = 0, T N84 = 0,
	T N85 = 0, T N86 = 0, T N87 = 0, T N88 = 0, T N89 = 0,
	T N90 = 0, T N91 = 0, T N92 = 0, T N93 = 0, T N94 = 0,
	T N95 = 0, T N96 = 0, T N97 = 0, T N98 = 0, T N99 = 0
>
class c_int_array_base
{
	typedef c_int_array_base <
		T, L - 1,
		N01, N02, N03, N04, N05, N06, N07, N08, N09,
		N10, N11, N12, N13, N14, N15, N16, N17, N18, N19,
		N20, N21, N22, N23, N24, N25, N26, N27, N28, N29,
		N30, N31, N32, N33, N34, N35, N36, N37, N38, N39,
		N40, N41, N42, N43, N44, N45, N46, N47, N48, N49,
		N50, N51, N52, N53, N54, N55, N56, N57, N58, N59,
		N60, N61, N62, N63, N64, N65, N66, N67, N68, N69,
		N70, N71, N72, N73, N74, N75, N76, N77, N78, N79,
		N80, N81, N82, N83, N84, N85, N86, N87, N88, N89,
		N90, N91, N92, N93, N94, N95, N96, N97, N98, N99
	> shift;

public:

//-----------------------------------------------------------------------------

	void copy(T* dest) const
	{
		*dest = N00;
		shift().copy(dest + 1);
	}

};

//-----------------------------------------------------------------------------

template <
	typename T,
	T N00, T N01, T N02, T N03, T N04, T N05, T N06, T N07, T N08, T N09,
	T N10, T N11, T N12, T N13, T N14, T N15, T N16, T N17, T N18, T N19,
	T N20, T N21, T N22, T N23, T N24, T N25, T N26, T N27, T N28, T N29,
	T N30, T N31, T N32, T N33, T N34, T N35, T N36, T N37, T N38, T N39,
	T N40, T N41, T N42, T N43, T N44, T N45, T N46, T N47, T N48, T N49,
	T N50, T N51, T N52, T N53, T N54, T N55, T N56, T N57, T N58, T N59,
	T N60, T N61, T N62, T N63, T N64, T N65, T N66, T N67, T N68, T N69,
	T N70, T N71, T N72, T N73, T N74, T N75, T N76, T N77, T N78, T N79,
	T N80, T N81, T N82, T N83, T N84, T N85, T N86, T N87, T N88, T N89,
	T N90, T N91, T N92, T N93, T N94, T N95, T N96, T N97, T N98, T N99
>
struct c_int_array_base <
	T, 0,
	N00, N01, N02, N03, N04, N05, N06, N07, N08, N09,
	N10, N11, N12, N13, N14, N15, N16, N17, N18, N19,
	N20, N21, N22, N23, N24, N25, N26, N27, N28, N29,
	N30, N31, N32, N33, N34, N35, N36, N37, N38, N39,
	N40, N41, N42, N43, N44, N45, N46, N47, N48, N49,
	N50, N51, N52, N53, N54, N55, N56, N57, N58, N59,
	N60, N61, N62, N63, N64, N65, N66, N67, N68, N69,
	N70, N71, N72, N73, N74, N75, N76, N77, N78, N79,
	N80, N81, N82, N83, N84, N85, N86, N87, N88, N89,
	N90, N91, N92, N93, N94, N95, N96, N97, N98, N99
>
{
	void copy(T* dest) const { }
};

//-----------------------------------------------------------------------------

template <
	typename T, unsigned L,
	T N00 = 0, T N01 = 0, T N02 = 0, T N03 = 0, T N04 = 0,
	T N05 = 0, T N06 = 0, T N07 = 0, T N08 = 0, T N09 = 0,
	T N10 = 0, T N11 = 0, T N12 = 0, T N13 = 0, T N14 = 0,
	T N15 = 0, T N16 = 0, T N17 = 0, T N18 = 0, T N19 = 0,
	T N20 = 0, T N21 = 0, T N22 = 0, T N23 = 0, T N24 = 0,
	T N25 = 0, T N26 = 0, T N27 = 0, T N28 = 0, T N29 = 0,
	T N30 = 0, T N31 = 0, T N32 = 0, T N33 = 0, T N34 = 0,
	T N35 = 0, T N36 = 0, T N37 = 0, T N38 = 0, T N39 = 0,
	T N40 = 0, T N41 = 0, T N42 = 0, T N43 = 0, T N44 = 0,
	T N45 = 0, T N46 = 0, T N47 = 0, T N48 = 0, T N49 = 0,
	T N50 = 0, T N51 = 0, T N52 = 0, T N53 = 0, T N54 = 0,
	T N55 = 0, T N56 = 0, T N57 = 0, T N58 = 0, T N59 = 0,
	T N60 = 0, T N61 = 0, T N62 = 0, T N63 = 0, T N64 = 0,
	T N65 = 0, T N66 = 0, T N67 = 0, T N68 = 0, T N69 = 0,
	T N70 = 0, T N71 = 0, T N72 = 0, T N73 = 0, T N74 = 0,
	T N75 = 0, T N76 = 0, T N77 = 0, T N78 = 0, T N79 = 0,
	T N80 = 0, T N81 = 0, T N82 = 0, T N83 = 0, T N84 = 0,
	T N85 = 0, T N86 = 0, T N87 = 0, T N88 = 0, T N89 = 0,
	T N90 = 0, T N91 = 0, T N92 = 0, T N93 = 0, T N94 = 0,
	T N95 = 0, T N96 = 0, T N97 = 0, T N98 = 0, T N99 = 0
>
class c_int_array :
	public constant <const T*, c_int_array <
		T, L,
		N00, N01, N02, N03, N04, N05, N06, N07, N08, N09,
		N10, N11, N12, N13, N14, N15, N16, N17, N18, N19,
		N20, N21, N22, N23, N24, N25, N26, N27, N28, N29,
		N30, N31, N32, N33, N34, N35, N36, N37, N38, N39,
		N40, N41, N42, N43, N44, N45, N46, N47, N48, N49,
		N50, N51, N52, N53, N54, N55, N56, N57, N58, N59,
		N60, N61, N62, N63, N64, N65, N66, N67, N68, N69,
		N70, N71, N72, N73, N74, N75, N76, N77, N78, N79,
		N80, N81, N82, N83, N84, N85, N86, N87, N88, N89,
		N90, N91, N92, N93, N94, N95, N96, N97, N98, N99
	> >

//-----------------------------------------------------------------------------

{
	typedef c_int_array_base <
		T, L,
		N00, N01, N02, N03, N04, N05, N06, N07, N08, N09,
		N10, N11, N12, N13, N14, N15, N16, N17, N18, N19,
		N20, N21, N22, N23, N24, N25, N26, N27, N28, N29,
		N30, N31, N32, N33, N34, N35, N36, N37, N38, N39,
		N40, N41, N42, N43, N44, N45, N46, N47, N48, N49,
		N50, N51, N52, N53, N54, N55, N56, N57, N58, N59,
		N60, N61, N62, N63, N64, N65, N66, N67, N68, N69,
		N70, N71, N72, N73, N74, N75, N76, N77, N78, N79,
		N80, N81, N82, N83, N84, N85, N86, N87, N88, N89,
		N90, N91, N92, N93, N94, N95, N96, N97, N98, N99
	> base;

	T a[L];

public:
	c_int_array() { base().copy(a); }
	operator const T*() const { return a; }
};

//-----------------------------------------------------------------------------

// TODO: integrate with types::term
struct term { };

template <
	typename T,
	typename C00 = term, typename C01 = term, typename C02 = term, typename C03 = term, typename C04 = term,
	typename C05 = term, typename C06 = term, typename C07 = term, typename C08 = term, typename C09 = term,
	typename C10 = term, typename C11 = term, typename C12 = term, typename C13 = term, typename C14 = term,
	typename C15 = term, typename C16 = term, typename C17 = term, typename C18 = term, typename C19 = term,
	typename C20 = term, typename C21 = term, typename C22 = term, typename C23 = term, typename C24 = term,
	typename C25 = term, typename C26 = term, typename C27 = term, typename C28 = term, typename C29 = term,
	typename C30 = term, typename C31 = term, typename C32 = term, typename C33 = term, typename C34 = term,
	typename C35 = term, typename C36 = term, typename C37 = term, typename C38 = term, typename C39 = term,
	typename C40 = term, typename C41 = term, typename C42 = term, typename C43 = term, typename C44 = term,
	typename C45 = term, typename C46 = term, typename C47 = term, typename C48 = term, typename C49 = term,
	typename C50 = term, typename C51 = term, typename C52 = term, typename C53 = term, typename C54 = term,
	typename C55 = term, typename C56 = term, typename C57 = term, typename C58 = term, typename C59 = term,
	typename C60 = term, typename C61 = term, typename C62 = term, typename C63 = term, typename C64 = term,
	typename C65 = term, typename C66 = term, typename C67 = term, typename C68 = term, typename C69 = term,
	typename C70 = term, typename C71 = term, typename C72 = term, typename C73 = term, typename C74 = term,
	typename C75 = term, typename C76 = term, typename C77 = term, typename C78 = term, typename C79 = term,
	typename C80 = term, typename C81 = term, typename C82 = term, typename C83 = term, typename C84 = term,
	typename C85 = term, typename C86 = term, typename C87 = term, typename C88 = term, typename C89 = term,
	typename C90 = term, typename C91 = term, typename C92 = term, typename C93 = term, typename C94 = term,
	typename C95 = term, typename C96 = term, typename C97 = term, typename C98 = term, typename C99 = term
>
class c_array_base
{
	typedef c_array_base <
		T,
		C01, C02, C03, C04, C05, C06, C07, C08, C09,
		C10, C11, C12, C13, C14, C15, C16, C17, C18, C19,
		C20, C21, C22, C23, C24, C25, C26, C27, C28, C29,
		C30, C31, C32, C33, C34, C35, C36, C37, C38, C39,
		C40, C41, C42, C43, C44, C45, C46, C47, C48, C49,
		C50, C51, C52, C53, C54, C55, C56, C57, C58, C59,
		C60, C61, C62, C63, C64, C65, C66, C67, C68, C69,
		C70, C71, C72, C73, C74, C75, C76, C77, C78, C79,
		C80, C81, C82, C83, C84, C85, C86, C87, C88, C89,
		C90, C91, C92, C93, C94, C95, C96, C97, C98, C99
	> shift;

public:

//-----------------------------------------------------------------------------

	enum { length = shift::length + 1 };

	void copy(T* dest) const
	{
		*dest = C00()();
		shift().copy(dest + 1);
	}

};

//-----------------------------------------------------------------------------

template <typename T>
struct c_array_base <T>
{
	enum { length = 0 };
	void copy(T* dest) const { }
};

//-----------------------------------------------------------------------------

template <
	typename T,
	typename C00 = term, typename C01 = term, typename C02 = term, typename C03 = term, typename C04 = term,
	typename C05 = term, typename C06 = term, typename C07 = term, typename C08 = term, typename C09 = term,
	typename C10 = term, typename C11 = term, typename C12 = term, typename C13 = term, typename C14 = term,
	typename C15 = term, typename C16 = term, typename C17 = term, typename C18 = term, typename C19 = term,
	typename C20 = term, typename C21 = term, typename C22 = term, typename C23 = term, typename C24 = term,
	typename C25 = term, typename C26 = term, typename C27 = term, typename C28 = term, typename C29 = term,
	typename C30 = term, typename C31 = term, typename C32 = term, typename C33 = term, typename C34 = term,
	typename C35 = term, typename C36 = term, typename C37 = term, typename C38 = term, typename C39 = term,
	typename C40 = term, typename C41 = term, typename C42 = term, typename C43 = term, typename C44 = term,
	typename C45 = term, typename C46 = term, typename C47 = term, typename C48 = term, typename C49 = term,
	typename C50 = term, typename C51 = term, typename C52 = term, typename C53 = term, typename C54 = term,
	typename C55 = term, typename C56 = term, typename C57 = term, typename C58 = term, typename C59 = term,
	typename C60 = term, typename C61 = term, typename C62 = term, typename C63 = term, typename C64 = term,
	typename C65 = term, typename C66 = term, typename C67 = term, typename C68 = term, typename C69 = term,
	typename C70 = term, typename C71 = term, typename C72 = term, typename C73 = term, typename C74 = term,
	typename C75 = term, typename C76 = term, typename C77 = term, typename C78 = term, typename C79 = term,
	typename C80 = term, typename C81 = term, typename C82 = term, typename C83 = term, typename C84 = term,
	typename C85 = term, typename C86 = term, typename C87 = term, typename C88 = term, typename C89 = term,
	typename C90 = term, typename C91 = term, typename C92 = term, typename C93 = term, typename C94 = term,
	typename C95 = term, typename C96 = term, typename C97 = term, typename C98 = term, typename C99 = term
>
class c_array :
	public constant <const T*, c_array <
		T,
		C00, C01, C02, C03, C04, C05, C06, C07, C08, C09,
		C10, C11, C12, C13, C14, C15, C16, C17, C18, C19,
		C20, C21, C22, C23, C24, C25, C26, C27, C28, C29,
		C30, C31, C32, C33, C34, C35, C36, C37, C38, C39,
		C40, C41, C42, C43, C44, C45, C46, C47, C48, C49,
		C50, C51, C52, C53, C54, C55, C56, C57, C58, C59,
		C60, C61, C62, C63, C64, C65, C66, C67, C68, C69,
		C70, C71, C72, C73, C74, C75, C76, C77, C78, C79,
		C80, C81, C82, C83, C84, C85, C86, C87, C88, C89,
		C90, C91, C92, C93, C94, C95, C96, C97, C98, C99
	> >

//-----------------------------------------------------------------------------

{
	typedef c_array_base <
		T,
		C00, C01, C02, C03, C04, C05, C06, C07, C08, C09,
		C10, C11, C12, C13, C14, C15, C16, C17, C18, C19,
		C20, C21, C22, C23, C24, C25, C26, C27, C28, C29,
		C30, C31, C32, C33, C34, C35, C36, C37, C38, C39,
		C40, C41, C42, C43, C44, C45, C46, C47, C48, C49,
		C50, C51, C52, C53, C54, C55, C56, C57, C58, C59,
		C60, C61, C62, C63, C64, C65, C66, C67, C68, C69,
		C70, C71, C72, C73, C74, C75, C76, C77, C78, C79,
		C80, C81, C82, C83, C84, C85, C86, C87, C88, C89,
		C90, C91, C92, C93, C94, C95, C96, C97, C98, C99
	> base;

	T a[base::length];

public:
	c_array() { base().copy(a); }
	operator const T*() const { return a; }
};

//-----------------------------------------------------------------------------

}  // namespace constant_details

using constant_details::c_string;
using constant_details::c_int_array;
using constant_details::c_array;

//-----------------------------------------------------------------------------

template <typename T, T *A, typename I>
struct c_at : public constant <T&, c_at <T, A, I> >
{
	operator T&() const { return A[I()]; }
};

template <typename T, T const *A, typename I>
struct c_const_at : public constant <T&, c_const_at <T, A, I> >
{
	operator T const&() const { return A[I()]; }
};

//-----------------------------------------------------------------------------

// TODO: generic operator[]

//-----------------------------------------------------------------------------

template <typename S>
struct c_struct : public c_struct <S ()> { };

template <typename T>
struct c_struct <T ()> : public constant <T, c_struct <T ()> >
{
	operator T() const { return T(); }
};

template <typename T, typename A1>
struct c_struct <T (A1)> : public constant <T, c_struct <T (A1)> >
{
	operator T() const { return T(A1()); }
};

template <typename T, typename A1, typename A2>
struct c_struct <T (A1, A2)> : public constant <T, c_struct <T (A1, A2)> >
{
	operator T() const { return T(A1(), A2()); }
};

template <typename T, typename A1, typename A2, typename A3>
struct c_struct <T (A1, A2, A3)> :
	public constant <T, c_struct <T (A1, A2, A3)> >
{
	operator T() const { return T(A1(), A2(), A3()); }
};

template <typename T, typename A1, typename A2, typename A3, typename A4>
struct c_struct <T (A1, A2, A3, A4)> :
	public constant <T, c_struct <T (A1, A2, A3, A4)> >
{
	operator T() const { return T(A1(), A2(), A3(), A4()); }
};

//-----------------------------------------------------------------------------

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5
>
struct c_struct <T (A1, A2, A3, A4, A5)> :
	public constant <T, c_struct <T (A1, A2, A3, A4, A5)> >
{
	operator T() const { return T(A1(), A2(), A3(), A4(), A5()); }
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6
>
struct c_struct <T (A1, A2, A3, A4, A5, A6)> :
	public constant <T, c_struct <T (A1, A2, A3, A4, A5, A6)> >
{
	operator T() const { return T(A1(), A2(), A3(), A4(), A5(), A6()); }
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7
>
struct c_struct <T (A1, A2, A3, A4, A5, A6, A7)> :
	public constant <T, c_struct <T (A1, A2, A3, A4, A5, A6, A7)> >
{
	operator T() const { return T(A1(), A2(), A3(), A4(), A5(), A6(), A7()); }
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7, typename A8
>
struct c_struct <T (A1, A2, A3, A4, A5, A6, A7, A8)> :
	public constant <T, c_struct <T (A1, A2, A3, A4, A5, A6, A7, A8)> >
{
	operator T() const
	{
		return T(A1(), A2(), A3(), A4(), A5(), A6(), A7(), A8());
	}
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7, typename A8, typename A9
>
struct c_struct <T (A1, A2, A3, A4, A5, A6, A7, A8, A9)> :
	public constant <T, c_struct <T (A1, A2, A3, A4, A5, A6, A7, A8, A9)> >
{
	operator T() const
	{
		return T(A1(), A2(), A3(), A4(), A5(), A6(), A7(), A8(), A9());
	}
};

//-----------------------------------------------------------------------------

template <typename S>
struct c_new : public c_new <S ()> { };

template <typename T>
struct c_new <T ()> : public constant <T*, c_new <T ()> >
{
	operator T*() const { return new T(); }
};

template <typename T, typename A1>
struct c_new <T (A1)> : public constant <T*, c_new <T (A1)> >
{
	operator T*() const { return new T(A1()); }
};

template <typename T, typename A1, typename A2>
struct c_new <T (A1, A2)> : public constant <T*, c_new <T (A1, A2)> >
{
	operator T*() const { return new T(A1(), A2()); }
};

template <typename T, typename A1, typename A2, typename A3>
struct c_new <T (A1, A2, A3)> :
	public constant <T*, c_new <T (A1, A2, A3)> >
{
	operator T*() const { return new T(A1(), A2(), A3()); }
};

template <typename T, typename A1, typename A2, typename A3, typename A4>
struct c_new <T (A1, A2, A3, A4)> :
	public constant <T*, c_new <T (A1, A2, A3, A4)> >
{
	operator T*() const { return new T(A1(), A2(), A3(), A4()); }
};

//-----------------------------------------------------------------------------

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5
>
struct c_new <T (A1, A2, A3, A4, A5)> :
	public constant <T*, c_new <T (A1, A2, A3, A4, A5)> >
{
	operator T*() const { return new T(A1(), A2(), A3(), A4(), A5()); }
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6
>
struct c_new <T (A1, A2, A3, A4, A5, A6)> :
	public constant <T*, c_new <T (A1, A2, A3, A4, A5, A6)> >
{
	operator T*() const { return new T(A1(), A2(), A3(), A4(), A5(), A6()); }
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7
>
struct c_new <T (A1, A2, A3, A4, A5, A6, A7)> :
	public constant <T*, c_new <T (A1, A2, A3, A4, A5, A6, A7)> >
{
	operator T*() const
	{
		return new T(A1(), A2(), A3(), A4(), A5(), A6(), A7());
	}
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7, typename A8
>
struct c_new <T (A1, A2, A3, A4, A5, A6, A7, A8)> :
	public constant <T*, c_new <T (A1, A2, A3, A4, A5, A6, A7, A8)> >
{
	operator T*() const
	{
		return new T(A1(), A2(), A3(), A4(), A5(), A6(), A7(), A8());
	}
};

template <typename T, typename A1, typename A2, typename A3, typename A4,
	typename A5, typename A6, typename A7, typename A8, typename A9
>
struct c_new <T (A1, A2, A3, A4, A5, A6, A7, A8, A9)> :
	public constant <T*, c_new <T (A1, A2, A3, A4, A5, A6, A7, A8, A9)> >
{
	operator T*() const
	{
		return new T(A1(), A2(), A3(), A4(), A5(), A6(), A7(), A8(), A9());
	}
};

//-----------------------------------------------------------------------------

namespace constant_details {

//-----------------------------------------------------------------------------

template <
	typename F,
	typename A1 = term, typename A2 = term, typename A3 = term,
	typename A4 = term, typename A5 = term, typename A6 = term,
	typename A7 = term, typename A8 = term, typename A9 = term,
	typename A10 = term
>
struct c_call { };

template <typename F>
struct c_call <F> : public constant <typename F::return_type, c_call <F> >
{
	operator typename F::return_type() const { return F()()(); }
};

template <typename F, typename A1>
struct c_call <F, A1> :
	public constant <typename F::return_type, c_call <F, A1> >
{
	operator typename F::return_type() const { return F()()(A1()()); }
};

template <typename F, typename A1, typename A2>
struct c_call <F, A1, A2> :
	public constant <typename F::return_type, c_call <F, A1, A2> >
{
	operator typename F::return_type() const { return F()()(A1()(), A2()()); }
};

template <typename F, typename A1, typename A2, typename A3>
struct c_call <F, A1, A2, A3> :
	public constant <typename F::return_type, c_call <F, A1, A2, A3> >
{
	operator typename F::return_type() const
	{
		return F()()(A1()(), A2()(), A3()());
	}
};

template <typename F, typename A1, typename A2, typename A3, typename A4>
struct c_call <F, A1, A2, A3, A4> :
	public constant <typename F::return_type, c_call <F, A1, A2, A3, A4> >
{
	operator typename F::return_type() const
	{
		return F()()(A1()(), A2()(), A3()(), A4()());
	}
};

//-----------------------------------------------------------------------------

template <
	typename F,
	typename A1, typename A2, typename A3, typename A4, typename A5
>
struct c_call <F, A1, A2, A3, A5, A4> :
	public constant <typename F::return_type, c_call <F, A1, A2, A3, A4, A5> >
{
	operator typename F::return_type() const
	{
		return F()()(A1()(), A2()(), A3()(), A4()(), A5()());
	}
};

template <
	typename F,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename A6
>
struct c_call <F, A1, A2, A3, A4, A5, A6> :
	public constant <typename F::return_type, c_call <F, A1, A2, A3, A4, A5, A6> >
{
	operator typename F::return_type() const
	{
		return F()()(A1()(), A2()(), A3()(), A4()(), A5()(), A6()());
	}
};

template <
	typename F,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename A6, typename A7
>
struct c_call <F, A1, A2, A3, A4, A5, A6, A7> :
	public constant <
		typename F::return_type,
		c_call <F, A1, A2, A3, A4, A5, A6, A7>
	>
{
	operator typename F::return_type() const
	{
		return F()()(A1()(), A2()(), A3()(), A4()(), A5()(), A6()(), A7()());
	}
};

template <
	typename F,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename A6, typename A7, typename A8
>
struct c_call <F, A1, A2, A3, A4, A5, A6, A7, A8> :
	public constant <
		typename F::return_type,
		c_call <F, A1, A2, A3, A4, A5, A6, A7, A8>
	>
{
	operator typename F::return_type() const
	{
		return F()()(
			A1()(), A2()(), A3()(), A4()(), A5()(), A6()(), A7()(), A8()()
		);
	}
};

template <
	typename F,
	typename A1, typename A2, typename A3, typename A4, typename A5,
	typename A6, typename A7, typename A8, typename A9
>
struct c_call <F, A1, A2, A3, A4, A5, A6, A7, A8, A9> :
	public constant <
		typename F::return_type,
		c_call <F, A1, A2, A3, A4, A5, A6, A7, A8, A9>
	>
{
	operator typename F::return_type() const
	{
		return F()()(
			A1()(), A2()(), A3()(), A4()(), A5()(), A6()(), A7()(), A8()(),
			A9()()
		);
	}
};

//-----------------------------------------------------------------------------

}  // namespace constant_details

using constant_details::c_call;

//-----------------------------------------------------------------------------

template <typename T, T &R>
struct c_ref : public constant <T&, c_ref <T, R> >
{
	operator T&() const { return R; }
};

template <typename T, T const &R>
struct c_const_ref : public constant <T const&, c_const_ref <T, R> >
{
	operator T const&() const { return R; }
};

//-----------------------------------------------------------------------------

template <typename T, T *P>
struct c_ptr : public constant <T*, c_ptr <T, P> >
{
	operator T*() const { return P; }
};

template <typename T, T const *P>
struct c_const_ptr : public constant <T const*, c_const_ptr <T, P> >
{
	operator T const*() const { return P; }
};

//-----------------------------------------------------------------------------

template <typename T, typename C, T C::*P>
struct c_member : public constant <T C::*, c_member <T, C, P> >
{
	operator T C::*() const { return P; }
};

template <typename T, typename C, T const C::*P>
struct c_const_member :
	public constant <T const C::*, c_const_member <T, C, P> >
{
	operator T const C::*() const { return P; }
};

//-----------------------------------------------------------------------------

template <typename T, typename C, C &O, T C::*P>
struct c_ref_member :
	public constant <T&, c_ref_member <T, C, O, P> >
{
	operator T&() const { return O.*P; }
};

template <typename T, typename C, C const &O, T const C::*P>
struct c_const_ref_member :
	public constant <T const&, c_const_ref_member <T, C, O, P> >
{
	operator T const&() const { return O.*P; }
};

//-----------------------------------------------------------------------------

template <typename T, typename C, C *O, T C::*P>
struct c_ptr_member :
	public constant <T&, c_ptr_member <T, C, O, P> >
{
	operator T&() const { return O->*P; }
};

template <typename T, typename C, C const *O, T const C::*P>
struct c_const_ptr_member :
	public constant <T const&, c_const_ptr_member <T, C, O, P> >
{
	operator T const&() const { return O->*P; }
};

//-----------------------------------------------------------------------------

namespace constant_details {

//-----------------------------------------------------------------------------

template <typename C, typename R>
struct ret : public C { typedef R return_type; };

template <
	typename C, C &O, typename R,
	typename A1 = term, typename A2 = term, typename A3 = term,
	typename A4 = term, typename A5 = term, typename A6 = term,
	typename A7 = term, typename A8 = term, typename A9 = term,
	typename A10 = term
>
struct c_ref_call :
	public c_call <
		ret <c_ref <C, O>, R>,
		A1, A2, A3, A4, A5, A6, A7, A8, A9, A10
	> { };

template <
	typename C, C const &O, typename R,
	typename A1 = term, typename A2 = term, typename A3 = term,
	typename A4 = term, typename A5 = term, typename A6 = term,
	typename A7 = term, typename A8 = term, typename A9 = term,
	typename A10 = term
>
struct c_const_ref_call :
	public c_call <
		ret <c_const_ref <C, O>, R>,
		A1, A2, A3, A4, A5, A6, A7, A8, A9, A10
	> { };

template <
	typename C, typename R,
	typename A1 = term, typename A2 = term, typename A3 = term,
	typename A4 = term, typename A5 = term, typename A6 = term,
	typename A7 = term, typename A8 = term, typename A9 = term,
	typename A10 = term
>
struct c_fun_call :
	public c_call <
		ret <c_struct <C>, R>,
		A1, A2, A3, A4, A5, A6, A7, A8, A9, A10
	> { };

//-----------------------------------------------------------------------------

}  // namespace constant_details

using constant_details::c_ref_call;
using constant_details::c_const_ref_call;
using constant_details::c_fun_call;

//-----------------------------------------------------------------------------

template <typename S>
class c_sig { };

template <typename R>
class c_sig <R ()>
{
	template <typename C, C &O, R (C::*M)()>
	struct del { static R call() { return (O.*M)(); } };

	template <typename C, C const &O, R (C::*M)() const>
	struct const_del { static R call() { return (O.*M)(); } };

	template <typename C, R (C::*M)() const>
	struct fun_del { static R call() { return (C().*M)(); } };

public:

//-----------------------------------------------------------------------------

	template <R (*F)()>
	struct function : constant <R (*)(), function <F> >
	{
		typedef R (*type)();
		typedef R return_type;
		operator type() const { return F; }
	};

	template <typename C, R (C::*M)()>
	struct method : constant <R (C::*)(), method <C, M> >
	{
		typedef R (C::*type)();
		operator type() const { return M; }
	};

	template <typename C, R (C::*M)() const>
	struct const_method : constant <R (C::*)() const, const_method <C, M> >
	{
		typedef R (C::*type)() const;
		operator type() const { return M; }
	};

//-----------------------------------------------------------------------------

	template <typename C, C &O, R (C::*M)()>
	struct ref_method : function <del <C, O, M>::call> { };

	template <typename C, C const &O, R (C::*M)() const>
	struct const_ref_method : function <const_del <C, O, M>::call> { };

	template <typename C, R (C::*M)() const>
	struct fun_method : function <fun_del <C, M>::call> { };

//-----------------------------------------------------------------------------

	template <R (*F)()>
	struct call : public c_call <function <F> > { };

	template <typename C, C &O, R (C::*M)()>
	struct ref_call : public c_call <ref_method <C, O, M> > { };

	template <typename C, C const &O, R (C::*M)() const>
	struct const_ref_call : public c_call <const_ref_method <C, O, M> > { };

	template <typename C, R (C::*M)() const>
	struct fun_call : public c_call <fun_method <C, M> > { };

};

//-----------------------------------------------------------------------------

template <typename R, typename A1>
class c_sig <R (A1)>
{
	template <typename C, C &O, R (C::*M)(A1)>
	struct del { static R call(A1 a1) { return (O.*M)(a1); } };

	template <typename C, C const &O, R (C::*M)(A1) const>
	struct const_del { static R call(A1 a1) { return (O.*M)(a1); } };

	template <typename C, R (C::*M)(A1) const>
	struct fun_del { static R call(A1 a1) { return (C().*M)(a1); } };

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1)>
	struct function : constant <R (*)(A1), function <F> >
	{
		typedef R (*type)(A1);
		typedef R return_type;
		operator type() const { return F; }
	};

	template <typename C, R (C::*M)(A1)>
	struct method : constant <R (C::*)(A1), method <C, M> >
	{
		typedef R (C::*type)(A1);
		operator type() const { return M; }
	};

	template <typename C, R (C::*M)(A1) const>
	struct const_method : constant <R (C::*)(A1) const, const_method <C, M> >
	{
		typedef R (C::*type)(A1) const;
		operator type() const { return M; }
	};

//-----------------------------------------------------------------------------

	template <typename C, C &O, R (C::*M)(A1)>
	struct ref_method : function <del <C, O, M>::call> { };

	template <typename C, C const &O, R (C::*M)(A1) const>
	struct const_ref_method : function <const_del <C, O, M>::call> { };

	template <typename C, R (C::*M)(A1) const>
	struct fun_method : function <fun_del <C, M>::call> { };

//-----------------------------------------------------------------------------

	template <R (*F)(A1), typename V1>
	struct call : public c_call <function <F>, V1> { };

	template <typename C, C &O, R (C::*M)(A1), typename V1>
	struct ref_call : public c_call <ref_method <C, O, M>, V1> { };

	template <typename C, C const &O, R (C::*M)(A1) const, typename V1>
	struct const_ref_call : public c_call <const_ref_method <C, O, M>, V1> { };

	template <typename C, R (C::*M)(A1) const, typename V1>
	struct fun_call : public c_call <fun_method <C, M>, V1 > { };

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2>
class c_sig <R (A1, A2)>
{
	template <typename C, C &O, R (C::*M)(A1, A2)>
	struct del { static R call(A1 a1, A2 a2) { return (O.*M)(a1, a2); } };

	template <typename C, C const &O, R (C::*M)(A1, A2) const>
	struct const_del { static R call(A1 a1, A2 a2) { return (O.*M)(a1, a2); } };

	template <typename C, R (C::*M)(A1, A2) const>
	struct fun_del { static R call(A1 a1, A2 a2) { return (C().*M)(a1, a2); } };

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2)>
	struct function : constant <R (*)(A1, A2), function <F> >
	{
		typedef R (*type)(A1, A2);
		typedef R return_type;
		operator type() const { return F; }
	};

	template <typename C, R (C::*M)(A1, A2)>
	struct method : constant <R (C::*)(A1, A2), method <C, M> >
	{
		typedef R (C::*type)(A1, A2);
		operator type() const { return M; }
	};

	template <typename C, R (C::*M)(A1, A2) const>
	struct const_method :
		constant <R (C::*)(A1, A2) const, const_method <C, M> >
	{
		typedef R (C::*type)(A1, A2) const;
		operator type() const { return M; }
	};

//-----------------------------------------------------------------------------

	template <typename C, C &O, R (C::*M)(A1, A2)>
	struct ref_method : function <del <C, O, M>::call> { };

	template <typename C, C const &O, R (C::*M)(A1, A2) const>
	struct const_ref_method : function <const_del <C, O, M>::call> { };

	template <typename C, R (C::*M)(A1, A2) const>
	struct fun_method : function <fun_del <C, M>::call> { };

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2), typename V1, typename V2>
	struct call : public c_call <function <F>, V1, V2> { };

	template <typename C, C &O, R (C::*M)(A1, A2), typename V1, typename V2>
	struct ref_call : public c_call <ref_method <C, O, M>, V1, V2> { };

	template <
		typename C, C const &O, R (C::*M)(A1, A2) const,
		typename V1, typename V2
	>
	struct const_ref_call :
		public c_call <const_ref_method <C, O, M>, V1, V2 > { };

	template <typename C, R (C::*M)(A1, A2) const, typename V1, typename V2>
	struct fun_call : public c_call <fun_method <C, M>, V1, V2> { };

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3>
class c_sig <R (A1, A2, A3)>
{
	template <typename C, C &O, R (C::*M)(A1, A2, A3)>
	struct del
	{
		static R call(A1 a1, A2 a2, A3 a3) { return (O.*M)(a1, a2, a3); }
	};

	template <typename C, C const &O, R (C::*M)(A1, A2, A3) const>
	struct const_del
	{
		static R call(A1 a1, A2 a2, A3 a3) { return (O.*M)(a1, a2, a3); }
	};

	template <typename C, R (C::*M)(A1, A2, A3) const>
	struct fun_del
	{
		static R call(A1 a1, A2 a2, A3 a3) { return (C().*M)(a1, a2, a3); }
	};

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3)>
	struct function : constant <R (*)(A1, A2, A3), function <F> >
	{
		typedef R (*type)(A1, A2, A3);
		typedef R return_type;
		operator type() const { return F; }
	};

	template <typename C, R (C::*M)(A1, A2, A3)>
	struct method : constant <R (C::*)(A1, A2, A3), method <C, M> >
	{
		typedef R (C::*type)(A1, A2, A3);
		operator type() const { return M; }
	};

	template <typename C, R (C::*M)(A1, A2, A3) const>
	struct const_method :
		constant <R (C::*)(A1, A2, A3) const, const_method <C, M> >
	{
		typedef R (C::*type)(A1, A2, A3) const;
		operator type() const { return M; }
	};

//-----------------------------------------------------------------------------

	template <typename C, C &O, R (C::*M)(A1, A2, A3)>
	struct ref_method : function <del <C, O, M>::call> { };

	template <typename C, C const &O, R (C::*M)(A1, A2, A3) const>
	struct const_ref_method : function <const_del <C, O, M>::call> { };

	template <typename C, R (C::*M)(A1, A2, A3) const>
	struct fun_method : function <fun_del <C, M>::call> { };

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3), typename V1, typename V2, typename V3>
	struct call : public c_call <function <F>, V1, V2, V3> { };

	template <
		typename C, C &O, R (C::*M)(A1, A2, A3),
		typename V1, typename V2, typename V3
	>
	struct ref_call : public c_call <ref_method <C, O, M>, V1, V2, V3> { };

	template <
		typename C, C const &O, R (C::*M)(A1, A2, A3) const,
		typename V1, typename V2, typename V3
	>
	struct const_ref_call :
		public c_call <const_ref_method <C, O, M>, V1, V2, V3> { };

	template <
		typename C, R (C::*M)(A1, A2, A3) const,
		typename V1, typename V2, typename V3
	>
	struct fun_call : public c_call <fun_method <C, M>, V1, V2, V3> { };

};

//-----------------------------------------------------------------------------

template <typename R, typename A1, typename A2, typename A3, typename A4>
class c_sig <R (A1, A2, A3, A4)>
{
	template <typename C, C &O, R (C::*M)(A1, A2, A3, A4)>
	struct del
	{
		static R call(A1 a1, A2 a2, A3 a3, A4 a4)
			{ return (O.*M)(a1, a2, a3, a4); }
	};

	template <typename C, C const &O, R (C::*M)(A1, A2, A3, A4) const>
	struct const_del
	{
		static R call(A1 a1, A2 a2, A3 a3, A4 a4)
			{ return (O.*M)(a1, a2, a3); }
	};

	template <typename C, R (C::*M)(A1, A2, A3, A4) const>
	struct fun_del
	{
		static R call(A1 a1, A2 a2, A3 a3, A4 a4)
			{ return (C().*M)(a1, a2, a3, a4); }
	};

public:

//-----------------------------------------------------------------------------

	template <R (*F)(A1, A2, A3, A4)>
	struct function : constant <R (*)(A1, A2, A3, A4), function <F> >
	{
		typedef R (*type)(A1, A2, A3, A4);
		typedef R return_type;
		operator type() const { return F; }
	};

	template <typename C, R (C::*M)(A1, A2, A3, A4)>
	struct method : constant <R (C::*)(A1, A2, A3, A4), method <C, M> >
	{
		typedef R (C::*type)(A1, A2, A3, A4);
		operator type() const { return M; }
	};

	template <typename C, R (C::*M)(A1, A2, A3, A4) const>
	struct const_method :
		constant <R (C::*)(A1, A2, A3, A4) const, const_method <C, M> >
	{
		typedef R (C::*type)(A1, A2, A3, A4) const;
		operator type() const { return M; }
	};

//-----------------------------------------------------------------------------

	template <typename C, C &O, R (C::*M)(A1, A2, A3, A4)>
	struct ref_method : function <del <C, O, M>::call> { };

	template <typename C, C const &O, R (C::*M)(A1, A2, A3, A4) const>
	struct const_ref_method : function <const_del <C, O, M>::call> { };

	template <typename C, R (C::*M)(A1, A2, A3, A4) const>
	struct fun_method : function <fun_del <C, M>::call> { };

//-----------------------------------------------------------------------------

	template <
		R (*F)(A1, A2, A3, A4),
		typename V1, typename V2, typename V3, typename V4
	>
	struct call : public c_call <function <F>, V1, V2, V3, V4> { };

	template <
		typename C, C &O, R (C::*M)(A1, A2, A3, A4),
		typename V1, typename V2, typename V3, typename V4
	>
	struct ref_call : public c_call <ref_method <C, O, M>, V1, V2, V3, V4> { };

	template <
		typename C, C const &O, R (C::*M)(A1, A2, A3, A4) const,
		typename V1, typename V2, typename V3, typename V4
	>
	struct const_ref_call :
		public c_call <const_ref_method <C, O, M>, V1, V2, V3, V4> { };

	template <
		typename C, R (C::*M)(A1, A2, A3, A4) const,
		typename V1, typename V2, typename V3, typename V4
	>
	struct fun_call : public c_call <fun_method <C, M>, V1, V2, V3, V4> { };

};

//-----------------------------------------------------------------------------

template <typename F, typename R, typename A>
struct c_unary_op : public c_fun_call <F, R, A> { };

template <typename F, typename R, typename A, typename B>
struct c_binary_op : public c_fun_call <F, R, A, B> { };

template <typename F, typename R, typename A, typename B, typename C>
struct c_ternary_op : public c_fun_call <F, R, A, B, C> { };

//-----------------------------------------------------------------------------

namespace constant_details {

//-----------------------------------------------------------------------------

// TODO: fix return types
struct plus  { template <typename A>             A operator()(const A& a)             { return +a; } };
struct minus { template <typename A>             A operator()(const A& a)             { return -a; } };
struct add   { template <typename A, typename B> A operator()(const A& a, const B& b) { return a + b; } };
struct sub   { template <typename A, typename B> A operator()(const A& a, const B& b) { return a - b; } };
struct mul   { template <typename A, typename B> A operator()(const A& a, const B& b) { return a * b; } };
struct div   { template <typename A, typename B> A operator()(const A& a, const B& b) { return a / b; } };
struct mod   { template <typename A, typename B> A operator()(const A& a, const B& b) { return a % b; } };

// TODO: fix return types
struct eq  { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a == b; } };
struct neq { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a != b; } };
struct gt  { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a > b; } };
struct lt  { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a < b; } };
struct ge  { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a >= b; } };
struct le  { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a <= b; } };

// TODO: fix return types
struct not_    { template <typename A>             bool operator()(const A& a)             { return !a; } };
struct and_    { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a && b; } };
struct or_     { template <typename A, typename B> bool operator()(const A& a, const B& b) { return a || b; } };
struct bit_not { template <typename A>             A    operator()(const A& a)             { return ~a; } };
struct bit_and { template <typename A, typename B> A    operator()(const A& a, const B& b) { return a & b; } };
struct bit_or  { template <typename A, typename B> A    operator()(const A& a, const B& b) { return a | b; } };
struct bit_xor { template <typename A, typename B> A    operator()(const A& a, const B& b) { return a ^ b; } };
struct left    { template <typename A, typename B> A    operator()(const A& a, const B& b) { return a << b; } };
struct right   { template <typename A, typename B> A    operator()(const A& a, const B& b) { return a >> b; } };

//-----------------------------------------------------------------------------

// TODO: fix return types
struct cond
{
	template <typename A, typename B, typename C>
	B operator()(const A& a, const B& b, const C& c) const { return a ? b : c; }
};

//-----------------------------------------------------------------------------

template <typename A>             struct c_plus  : public c_unary_op  <plus,  typename A::type, A>    { };
template <typename A>             struct c_minus : public c_unary_op  <minus, typename A::type, A>    { };
template <typename A, typename B> struct c_add   : public c_binary_op <add,   typename A::type, A, B> { };
template <typename A, typename B> struct c_sub   : public c_binary_op <sub,   typename A::type, A, B> { };
template <typename A, typename B> struct c_mul   : public c_binary_op <mul,   typename A::type, A, B> { };
template <typename A, typename B> struct c_div   : public c_binary_op <div,   typename A::type, A, B> { };
template <typename A, typename B> struct c_mod   : public c_binary_op <mod,   typename A::type, A, B> { };

template <typename A, typename B> struct c_eq  : public c_binary_op <eq,  bool, A, B> { };
template <typename A, typename B> struct c_neq : public c_binary_op <neq, bool, A, B> { };
template <typename A, typename B> struct c_gt  : public c_binary_op <gt,  bool, A, B> { };
template <typename A, typename B> struct c_lt  : public c_binary_op <lt,  bool, A, B> { };
template <typename A, typename B> struct c_ge  : public c_binary_op <ge,  bool, A, B> { };
template <typename A, typename B> struct c_le  : public c_binary_op <le,  bool, A, B> { };

template <typename A>             struct c_not     : public c_unary_op  <not_,    bool, A>    { };
template <typename A, typename B> struct c_and     : public c_binary_op <and_,    bool, A, B> { };
template <typename A, typename B> struct c_or      : public c_binary_op <or_,     bool, A, B> { };
template <typename A>             struct c_bit_not : public c_unary_op  <bit_not, typename A::type, A>    { };
template <typename A, typename B> struct c_bit_and : public c_binary_op <bit_and, typename A::type, A, B> { };
template <typename A, typename B> struct c_bit_or  : public c_binary_op <bit_or,  typename A::type, A, B> { };
template <typename A, typename B> struct c_bit_xor : public c_binary_op <bit_xor, typename A::type, A, B> { };
template <typename A, typename B> struct c_left    : public c_binary_op <left,    typename A::type, A, B> { };
template <typename A, typename B> struct c_right   : public c_binary_op <right,   typename A::type, A, B> { };

//-----------------------------------------------------------------------------

template <typename A, typename B, typename C>
struct c_cond : public c_ternary_op <cond, B, A, B, C> { };

//-----------------------------------------------------------------------------

}  // namespace constant_details

using constant_details::c_plus;
using constant_details::c_minus;
using constant_details::c_add;
using constant_details::c_sub;
using constant_details::c_mul;
using constant_details::c_div;
using constant_details::c_mod;
using constant_details::c_eq;
using constant_details::c_neq;
using constant_details::c_gt;
using constant_details::c_lt;
using constant_details::c_ge;
using constant_details::c_le;
using constant_details::c_not;
using constant_details::c_and;
using constant_details::c_or;
using constant_details::c_bit_not;
using constant_details::c_bit_and;
using constant_details::c_bit_or;
using constant_details::c_bit_xor;
using constant_details::c_left;
using constant_details::c_right;
using constant_details::c_cond;

//-----------------------------------------------------------------------------

template <typename T, T (*F)()>
struct c_gen : public c_sig <T ()>::template call <F> { };

template <typename T, T (*F)(T), typename A1>
struct c_gen_1 : public c_sig <T (T)>::template call <F, A1> { };

template <typename T, T (*F)(T, T), typename A1, typename A2>
struct c_gen_2 : public c_sig <T (T, T)>::template call <F, A1, A2> { };

//-----------------------------------------------------------------------------

template <typename T>
struct c_min : public c_gen <T, std::numeric_limits <T>::min> { };

template <typename T>
struct c_max : public c_gen <T, std::numeric_limits <T>::max> { };

template <typename T = double>
struct c_eps : public c_gen <T, std::numeric_limits <T>::epsilon> { };

template <typename T = double>
struct c_inf : public c_gen <T, std::numeric_limits <T>::infinity> { };

template <typename T = double>
struct c_nan : public c_gen <T, std::numeric_limits <T>::quiet_NaN> { };

//-----------------------------------------------------------------------------

template <typename T = double>
struct c_e  : public c_gen_1 <T, std::exp, c_one> { };

template <typename T = double>
struct c_pi : public c_mul <c_gen_1 <T, std::atan, c_one>, c_int <4> > { };

template <typename T = double>
struct c_i  : public c_struct <std::complex <T> (c_zero, c_one)> { };

template <typename T = double>
struct c_j  : public c_i <T> { };

//-----------------------------------------------------------------------------

template <typename T>
struct c_sizeof : public constant <unsigned long, c_sizeof <T> >
{
	operator unsigned long() const { return sizeof(T); }
};

template <typename S, typename T, T &O>
struct c_static_cast: public constant <S, c_static_cast<S, T, O> >
{
	operator S() const { return static_cast <S> (O); }
};

template <typename S, typename T, T &O>
struct c_dynamic_cast: public constant <S, c_dynamic_cast<S, T, O> >
{
	operator S() const { return dynamic_cast <S> (O); }
};

template <typename S, typename T, T &O>
struct c_const_cast: public constant <S, c_const_cast<S, T, O> >
{
	operator S() const { return const_cast <S> (O); }
};

template <typename S, typename T, T &O>
struct c_reinterpret_cast: public constant <S, c_reinterpret_cast<S, T, O> >
{
	operator S() const { return reinterpret_cast <S> (O); }
};

//-----------------------------------------------------------------------------

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_CONSTANT_HPP
