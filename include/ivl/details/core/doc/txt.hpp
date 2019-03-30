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

#ifndef IVL_CORE_DETAILS_DOC_TXT_HPP
#define IVL_CORE_DETAILS_DOC_TXT_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {
namespace details {
namespace device {

using ikey::txt;

//-----------------------------------------------------------------------------

template <typename S, typename V>
inline S& so(id <txt, S>& s, const key_val <key::page, V>& v)    { return *s << (_, file); }

template <typename S> inline S& so(id <txt, S>& s, key::page)    { return *s << (_, file); }
template <typename S> inline S& so(id <txt, S>& s, key::file)    { return *s << (wrap, !indent, par); }
template <typename S> inline S& so(id <txt, S>& s, key::nline)   { return *s << (_, nl); }
template <typename S> inline S& so(id <txt, S>& s, key::para)    { return *s << (_, par); }
template <typename S> inline S& so(id <txt, S>& s, key::head1)   { return *s << (par, bright); }
template <typename S> inline S& so(id <txt, S>& s, key::head2)   { return *s << (par, bright); }
template <typename S> inline S& so(id <txt, S>& s, key::head3)   { return *s << (par, bright); }
template <typename S> inline S& so(id <txt, S>& s, key::tabular) { return *s << (_, disp); }
template <typename S> inline S& so(id <txt, S>& s, key::row)     { return *s << (_, nl); }
template <typename S> inline S& so(id <txt, S>& s, key::label)   { return *s << (_, field=14); }
template <typename S> inline S& so(id <txt, S>& s, key::desc)    { return *s; }

template <typename S> inline S& so(id <txt, S>& s, key::title)   { return *s << (head2, white); }
template <typename S> inline S& so(id <txt, S>& s, key::body)    { return *s << (normal, white); }
template <typename S> inline S& so(id <txt, S>& s, key::syntax)  { return *s << (bright, cyan); }
template <typename S> inline S& so(id <txt, S>& s, key::t_ivl)   { return *s << (_, code["ivl"]); }
template <typename S> inline S& so(id <txt, S>& s, key::code)    { return *s << (_, cyan); }
template <typename S> inline S& so(id <txt, S>& s, key::lst)     { return *s << (disp, cyan); }
template <typename S> inline S& so(id <txt, S>& s, key::out)     { return *s << (disp, green); }
template <typename S> inline S& so(id <txt, S>& s, key::type)    { return *s << (_, magenta); }
template <typename S> inline S& so(id <txt, S>& s, key::func)    { return *s << (bright, blue); }
template <typename S> inline S& so(id <txt, S>& s, key::emph)    { return *s << (_, bright); }
template <typename S> inline S& so(id <txt, S>& s, key::alert)   { return *s << (bright, red); }

template <typename S, typename T> inline S& so(id <txt, S>& s, type_def <T>)  { return *s << (_, type); }
template <typename S, typename T> inline S& so(id <txt, S>& s, fun_def  <T>)  { return *s << (_, func); }

//-----------------------------------------------------------------------------

}  // namespace device
}  // namespace details
}  // namespace doc

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_DOC_TXT_HPP
