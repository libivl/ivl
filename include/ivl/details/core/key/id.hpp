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

#ifndef IVL_CORE_DETAILS_KEY_ID_HPP
#define IVL_CORE_DETAILS_KEY_ID_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

template <typename T>
struct is_id : public types::t_false { };

//-----------------------------------------------------------------------------

namespace details {

using namespace types;

//-----------------------------------------------------------------------------

template <typename K, typename D>
struct id
{
	D& operator*() { return static_cast <D&>(*this); }
};

struct no_id { };

template <typename T>
struct identity : public t_if <is_id <T>, T, no_id> { };

//-----------------------------------------------------------------------------

template <typename T1, typename T2>
struct join_identity_type { typedef no_id type; };

template <typename T>
struct join_identity_type <no_id, T> { typedef T type; };

template <typename T>
struct join_identity_type <T, no_id> { typedef T type; };

template <>
struct join_identity_type <no_id, no_id> { typedef no_id type; };

template <typename T1, typename T2>
struct join_identity : public join_identity_type <
	typename identity <T1>::type,
	typename identity <T2>::type
> { };

//-----------------------------------------------------------------------------

template <typename K, typename T>
struct derive_identity_type { typedef id <K, T> type; };

template <typename T>
struct derive_identity_type <no_id, T> { typedef no_id type; };

template <typename T>
struct derive_identity :
	public derive_identity_type <typename identity <T>::type, T> { };

//-----------------------------------------------------------------------------

}  // namespace details

using details::id;

//-----------------------------------------------------------------------------

namespace all {

using ivl::keys::id;
using ivl::keys::is_id;

}

//-----------------------------------------------------------------------------

}  // namespace keys

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_ID_HPP
