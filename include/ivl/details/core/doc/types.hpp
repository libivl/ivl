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

#ifndef IVL_CORE_DETAILS_DOC_TYPES_HPP
#define IVL_CORE_DETAILS_DOC_TYPES_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {

//-----------------------------------------------------------------------------

namespace key {

struct any_type;

template <typename T> struct ivl_type;
template <typename T> struct std_type;
template <typename T> struct num_type;

template <typename T> struct ivl_fun;
template <typename T> struct std_fun;

}  // namespace key

//-----------------------------------------------------------------------------

namespace details {

using types::t_true;
using types::t_false;
using types::t_if;
using keys::atom;

//-----------------------------------------------------------------------------

struct fun_id { };

template <typename T>
struct type : public types::type_base <T, type <T> >, public atom <type <T> > { };

template <template <typename> class T>
struct tmp1 : public types::template1 <T, tmp1 <T> >, public atom <tmp1 <T> > { };

template <template <typename, typename> class T>
struct tmp2 : public types::template2 <T, tmp2 <T> >, public atom <tmp2 <T> > { };

template <template <typename, typename, typename> class T>
struct tmp3 : public types::template3 <T, tmp3 <T> >, public atom <tmp3 <T> > { };

template <template <typename> class T>
struct tfun1 : public types::template1 <T, tfun1 <T>, fun_id>, public atom <tfun1 <T> > { };

template <template <typename, typename> class T>
struct tfun2 : public types::template2 <T, tfun2 <T>, fun_id>, public atom <tfun2 <T> > { };

template <template <typename, typename, typename> class T>
struct tfun3 : public types::template3 <T, tfun3 <T>, fun_id>, public atom <tfun3 <T> > { };

//-----------------------------------------------------------------------------

template <typename T> struct is_ivl : public types::t_false { };
template <typename T> struct is_std : public types::t_false { };
template <typename T> struct is_num : public types::is_builtin <T> { };

//-----------------------------------------------------------------------------

template <typename T, typename THEN, typename ELSE>
struct if_ivl : public t_if <is_ivl <T>, THEN, ELSE> { };

template <typename T, typename THEN, typename ELSE>
struct if_std : public t_if <is_std <T>, THEN, ELSE> { };

template <typename T, typename THEN, typename ELSE>
struct if_num : public t_if <is_num <T>, THEN, ELSE> { };

//-----------------------------------------------------------------------------

template <typename T>
struct type_style : public
	if_ivl <T, key::ivl_type <T>,
		typename if_std <T, key::std_type <T>,
			typename if_num <T, key::num_type <T>, key::any_type>::type
		>::type
	> { };

template <typename T>
struct fun_style :
	public if_ivl <T, key::ivl_fun <T>, key::std_fun <T> > { };

template <typename T>
struct ivl_fun_style { typedef key::ivl_fun <T> type; };

//-----------------------------------------------------------------------------

template <typename T>
struct name { const char* operator()() const { return ""; } };

template <typename STYLE, typename T, typename S>
S& stream_type(S& s) { return s << typename STYLE::type()[name <T>()()]; }

//-----------------------------------------------------------------------------

template <typename S, typename T>
inline S& operator<<(S& s, type <T>)
{
	return stream_type <type_style <T>, T>(s);
}

template <typename S, int N, typename T>
inline S& operator<<(S& s, types::template_class <N, T>)
{
	return stream_type <type_style <T>, T>(s);
}

//-----------------------------------------------------------------------------

template <typename S, typename T>
inline S& operator<<(S& s, fun::function <T>)
{
	return stream_type <ivl_fun_style <T>, T>(s);
}

template <typename S, typename T, typename F>
inline S& operator<<(S& s, types::fun_constant <T, F>)
{
	return stream_type <fun_style <F>, F>(s);
}

template <typename S, int N, typename T>
inline S& operator<<(S& s, types::template_class <N, T, fun_id>)
{
	return stream_type <fun_style <T>, T>(s);
}

template <typename S, typename K, typename F>
inline S& operator<<(S& s, keys::key_fun <K, F>) { return s << F(); }

//-----------------------------------------------------------------------------

}  // namespace details

using details::name;

//-----------------------------------------------------------------------------

}  // namespace doc

using doc::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_DOC_TYPES_HPP
