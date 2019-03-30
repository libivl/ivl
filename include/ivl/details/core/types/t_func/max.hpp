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

#ifndef IVL_CORE_DETAILS_TYPES_MAX_TYPE_HPP
#define IVL_CORE_DETAILS_TYPES_MAX_TYPE_HPP

namespace ivl {
namespace types {

namespace types_details {

//-----------------------------------------------------------------------------
// primitive type successor

template<typename T> struct succ { typedef term type; };

template<> struct succ<bool>               { typedef char type; };
template<> struct succ<char>               { typedef unsigned char type; };
template<> struct succ<unsigned char>      { typedef short type; };
template<> struct succ<short>              { typedef unsigned short type; };
template<> struct succ<unsigned short>     { typedef wchar_t type; };
//template<> struct succ<wchar_t>            { typedef int type; };
template<> struct succ<int>                { typedef unsigned int type; };
template<> struct succ<unsigned int>       { typedef long type; };
template<> struct succ<long>               { typedef unsigned long type; };
template<> struct succ<unsigned long>      { typedef long long type; };
template<> struct succ<long long>          { typedef unsigned long long type; };
template<> struct succ<unsigned long long> { typedef float type; };
template<> struct succ<float>              { typedef double type; };
template<> struct succ<double>             { typedef long double type; };

//-----------------------------------------------------------------------------
// primitive type comparison, based on successor relations

// less than: successor is less than or equal
template<typename T1, typename T2> struct lt_rel {
	typedef typename succ<T1>::type S1;
	typedef t_or<t_eq<S1, T2>, typename lt_rel<S1, T2>::type > type;
};

template<typename T> struct lt_rel<T, term> : public t_false { };
template<typename T> struct lt_rel<term, T> : public t_false { };

//-----------------------------------------------------------------------------
// primitive type order

template<typename T> struct ord : public number<0> { };

template<> struct ord<bool>               : public number<1>  { };
template<> struct ord<char>               : public number<2>  { };
template<> struct ord<unsigned char>      : public number<3>  { };
template<> struct ord<short>              : public number<4>  { };
template<> struct ord<unsigned short>     : public number<5>  { };
//template<> struct ord<wchar_t>            : public number<6>  { };
template<> struct ord<int>                : public number<7>  { };
template<> struct ord<unsigned int>       : public number<8>  { };
template<> struct ord<long>               : public number<9>  { };
template<> struct ord<unsigned long>      : public number<10>  { };
template<> struct ord<long long>          : public number<11> { };
template<> struct ord<unsigned long long> : public number<12> { };
template<> struct ord<float>              : public number<13> { };
template<> struct ord<double>             : public number<14> { };
template<> struct ord<long double>        : public number<15> { };

//-----------------------------------------------------------------------------
// primitive type comparison, based on order

// less than, but none zero
template<typename N1, typename N2> struct lt0 {
	typedef typename t_lt<N1, N2>::type type;
};

template<typename T> struct lt0<T, number<0> > : public t_false { };
template<typename T> struct lt0<number<0>, T > : public t_false { };

template<typename T1, typename T2> struct lt_ord {
	typedef typename lt0<ord<T1>, ord<T2> >::type type;
};

//-----------------------------------------------------------------------------
// choose comparison mode here: relations or order

template<typename T1, typename T2> struct lt_prim : public
	lt_ord<T1, T2> { };

//-----------------------------------------------------------------------------
// max primitive type

// max size in bytes
template<typename T1, typename T2> struct max_size {
	typedef typename
		t_if<t_expr<(sizeof(T1) >= sizeof(T2))>, T1, T2>::type type;
};

// max type if comparable, max size otherwise
template<typename T1, typename T2> struct max_prim {
	typedef
		typename t_if<typename lt_ord<T1, T2>::type, T2,
		typename t_if<typename lt_ord<T2, T1>::type, T1,
			typename max_size<T1, T2>::type>::type >::type type;
};

//-----------------------------------------------------------------------------
// max numeric type, primitive or complex

template<typename T1, typename T2> struct max_num : public
	max_prim<T1, T2> { };

template<typename T1, typename T2> struct
	max_num<std::complex<T1>, T2> {
		typedef std::complex<typename max_prim<T1, T2>::type> type;
};

template<typename T1, typename T2> struct
	max_num<T1, std::complex<T2> > {
		typedef std::complex<typename max_prim<T1, T2>::type> type;
};

template<typename T1, typename T2> struct
	max_num<std::complex<T1>, std::complex<T2> > {
		typedef std::complex<typename max_prim<T1, T2>::type> type;
};

//-----------------------------------------------------------------------------
// max composite type, array or numeric

template <typename T1, typename T2> struct max_comp : public
	t_if<is_ivl_array<T1>,
		typename t_if<is_ivl_array<T2>,
			to_type<typename max_num<typename subtype<T1>::type,
			                         typename subtype<T2>::type>::type, T1>,
			to_type<typename max_num<typename subtype<T1>::type, T2>::type, T1>
		>::type,
		typename t_if<is_ivl_array<T2>,
			to_type<typename max_num<T1, typename subtype<T2>::type>::type, T2>,
			to_type<typename max_num<T1, T2>::type>
		>::type
	>::type { };

template<typename T> struct max_comp<T, term> { typedef T type; };
template<typename T> struct max_comp<term, T> { typedef T type; };

template<> struct max_comp<term, term> { typedef bool type; };

};  // namespace types_details

//-----------------------------------------------------------------------------
// max type, public

namespace maps {

template <class T1, class T2> struct max : public
	types_details::max_comp<T1, T2> { };

}  // namespace maps
}  // namespace types
}  // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_MAX_TYPE_HPP
