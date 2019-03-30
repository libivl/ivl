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

#ifndef IVL_CORE_DETAILS_KEY_FILTER_HPP
#define IVL_CORE_DETAILS_KEY_FILTER_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

namespace ikey = ivl::key;

//-----------------------------------------------------------------------------

template <typename K, typename KN, typename S, typename T, typename TN>
inline item <node <K, KN>, S>&
operator<<(item <node <K, KN>, S>& s, const node <T, TN>& n)
{
	return +expand(s) << n,  s;
}

template <typename K, typename KN, typename S>
inline item <node <K, KN>, S>&
operator<<(item <node <K, KN>, S>& s, null) { return s; }

//-----------------------------------------------------------------------------

template <typename S, typename T, typename TN>
inline item <ikey::off, S>&
operator<<(item <ikey::off, S>& s, const node <T, TN>& n)
{
	return s.data << ~*n,  s << ++n;
}

template <typename S>
inline item <ikey::off, S>&
operator<<(item <ikey::off, S>& s, null) { return s; }

//-----------------------------------------------------------------------------

template <typename S, typename T, typename TN>
inline item <ikey::flip, S>&
operator<<(item <ikey::flip, S>& s, const node <T, TN>& n)
{
	return s.data << *n,  s << ++n;
}

template <typename S>
inline item <ikey::flip, S>&
operator<<(item <ikey::flip, S>& s, null) { return s; }

//-----------------------------------------------------------------------------

template <typename V, typename S, typename T, typename TN>
inline item <key_val <ikey::sep, V>, S>&
operator<<(item <key_val <ikey::sep, V>, S>& s, const node <T, TN>& n)
{
	return s << ++n,  s.data << *s.opt << *n,  s;
}

template <typename V, typename S, typename T>
inline item <key_val <ikey::sep, V>, S>&
operator<<(item <key_val <ikey::sep, V>, S>& s, const node <T>& n)
{
	return s.data << *n,  s;
}

template <typename V, typename S>
inline item <key_val <ikey::sep, V>, S>&
operator<<(item <key_val <ikey::sep, V>, S>& s, null) { return s; }

//-----------------------------------------------------------------------------

template <typename F, typename S, typename T, typename TN>
inline item <key_val <ikey::filter, F>, S>&
operator<<(item <key_val <ikey::filter, F>, S>& s, const node <T, TN>& n)
{
	return s << ++n,  (*s.opt)(s.data, *n),  s;
}

template <typename F, typename S>
inline item <key_val <ikey::filter, F>, S>&
operator<<(item <key_val <ikey::filter, F>, S>& s, null) { return s; }

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace keys

using keys::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_FILTER_HPP
