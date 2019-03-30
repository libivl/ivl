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

#ifndef IVL_CORE_DETAILS_KEY_GROUP_HPP
#define IVL_CORE_DETAILS_KEY_GROUP_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

struct group_id { };

template <typename K, template <typename> class G, bool I = false>
struct group : public key <K>, public generate <K, I>::type, public group_id
{
	typedef group <K, G> group_type;
	using option <K>::operator*;
};

//-----------------------------------------------------------------------------

template <typename K>
struct is_group : public is_base <group_id, K> { };

template <typename K, template <typename> class G>
struct is_of_group : public is_base <G <K>, K> { };

//-----------------------------------------------------------------------------
// @stream.hpp

template <typename S, typename K, typename T>
typename enable_if <is_group <K>, S&>::type
inline operator<<(S& s, const mod <K, off <T> >& v);

//-----------------------------------------------------------------------------

}  // namespace details

using details::group;
using details::is_of_group;

//-----------------------------------------------------------------------------

namespace all {

using ivl::keys::group;
using ivl::keys::is_of_group;

}  // namespace all

//-----------------------------------------------------------------------------

}  // namespace keys

using keys::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_KEY_GROUP_HPP
