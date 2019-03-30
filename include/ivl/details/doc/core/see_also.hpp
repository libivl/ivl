/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontsis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the terms
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_DOC_CORE_SEE_ALSO_HPP
#define IVL_DOC_CORE_SEE_ALSO_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {

//-----------------------------------------------------------------------------

template <> struct help_also <fun::arg_max>
{ template <typename S> S& operator()(S& s) { return s << (max, f_inf_min, arg_min, t_dimension); } };

template <> struct help_also <fun::arg_min>
{ template <typename S> S& operator()(S& s) { return s << (min, f_inf_max, arg_max, t_dimension); } };

template <> struct help_also <fun::extrema>
{ template <typename S> S& operator()(S& s) { return s << (min, max, f_inf_max, f_inf_min, t_dimension); } };

template <> struct help_also <fun::max>
{ template <typename S> S& operator()(S& s) { return s << (arg_max, f_inf_min, min, extrema, t_dimension); } };

template <> struct help_also <fun::min>
{ template <typename S> S& operator()(S& s) { return s << (arg_min, f_inf_max, max, extrema, t_dimension); } };

//-----------------------------------------------------------------------------

}  // namespace doc

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DOC_REG_SEE_ALSO_HPP
