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

#ifndef IVL_CORE_DETAILS_DOC_STYLE_HPP
#define IVL_CORE_DETAILS_DOC_STYLE_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {
namespace details {
namespace device {

//-----------------------------------------------------------------------------

template <typename S, typename V>
inline S& operator<<(S& s, const key_val <key::page, V>& v) { return so(s, v); }

template <typename S> inline S& operator<<(S& s, key::page    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::file    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::nline   k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::para    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::head1   k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::head2   k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::head3   k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::tabular k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::row     k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::label   k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::desc    k) { return so(s, k); }

template <typename S> inline S& operator<<(S& s, key::title   k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::body    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::syntax  k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::t_ivl   k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::code    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::lst     k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::out     k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::type    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::func    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::emph    k) { return so(s, k); }
template <typename S> inline S& operator<<(S& s, key::alert   k) { return so(s, k); }

template <typename S, typename T> inline S& operator<<(S& s, type_def <T> k)  { return so(s, k); }
template <typename S, typename T> inline S& operator<<(S& s, fun_def  <T> k)  { return so(s, k); }

//-----------------------------------------------------------------------------

template <typename S> inline S& operator<<(S& s, key::in)       { return *s << (nl, ++indent); }
template <typename S> inline S& operator<<(S& s, key::disp)     { return *s << (par, ++indent); }
template <typename S> inline S& operator<<(S& s, key::sample)   { return *s << (~para, out); }
template <typename S> inline S& operator<<(S& s, key::listing)  { return *s << (~para, lst); }
template <typename S> inline S& operator<<(S& s, key::output)   { return *s << (~lst, out); }
template <typename S> inline S& operator<<(S& s, key::todo)     { return *s << alert["TODO"]; }

//-----------------------------------------------------------------------------

}  // namespace device
}  // namespace details
}  // namespace doc

using doc::details::device::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_DOC_STYLE_HPP
