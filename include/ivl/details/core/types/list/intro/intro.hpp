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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_INTRO_INTRO_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_INTRO_INTRO_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {
namespace intro {

//-----------------------------------------------------------------------------

template <typename T>
struct name { };

//-----------------------------------------------------------------------------

template <template <bool> class F>
struct template_b { static char name[]; };

template <template <int> class F>
struct template_i { static char name[]; };

template <template <typename> class F>
struct template_t { static char name[]; };

template <template <typename, bool> class F>
struct template_tb { static char name[]; };

template <template <typename, int> class F>
struct template_ti { static char name[]; };

template <template <typename, typename> class F>
struct template_tt { static char name[]; };

template <template <typename, typename, bool> class F>
struct template_ttb { static char name[]; };

template <template <typename, typename, int> class F>
struct template_tti { static char name[]; };

template <template <typename, typename, typename> class F>
struct template_ttt { static char name[]; };

template <template <typename, typename, typename, bool> class F>
struct template_tttb { static char name[]; };

template <template <typename, typename, typename, int> class F>
struct template_ttti { static char name[]; };

template <template <typename, typename, typename, typename> class F>
struct template_tttt { static char name[]; };

template <template <typename, typename, typename, typename, bool> class F>
struct template_ttttb { static char name[]; };

template <template <typename, typename, typename, typename, int> class F>
struct template_tttti { static char name[]; };

template <template <typename, typename, typename, typename, typename> class F>
struct template_ttttt { static char name[]; };

//-----------------------------------------------------------------------------

template <template <template <typename> class> class F>
struct template_1t_ { static char name[]; };

template <template <template <typename, typename> class> class F>
struct template_2tt_ { static char name[]; };

//-----------------------------------------------------------------------------

template <typename T, typename TN>
struct nested { };

//-----------------------------------------------------------------------------

}  // namespace intro
}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_INTRO_INTRO_HPP
