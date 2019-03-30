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

#ifndef IVL_CORE_DETAILS_KEY_MOD_HPP
#define IVL_CORE_DETAILS_KEY_MOD_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename K>             struct is_key;
template <typename K>             class  key;
template <typename K, typename V> struct key_val;

//-----------------------------------------------------------------------------

template <typename K, typename T>
struct mod : public pair <T> { };

template <typename K>
struct mod <K, key <K> > : public pair <K> { };

template <typename K, typename V>
struct mod <K, key_val <K, V> > : public ref_pair <key_val <K, V> > { };

//-----------------------------------------------------------------------------

template <typename K, typename T>
struct mod <K, off <T> > : public pair <off <T> > { };

template <typename K, typename V>
class mod <K, off <key_val <K, V> > > :
	public ref_pair <off <key_val <K, V> > >
{
	typedef ref_pair <off <key_val <K, V> > > B;

public:
	mod(const key_val <K, V>& p) : B(p) { }
};

//-----------------------------------------------------------------------------

template <typename K, typename T>
struct off <mod <K, T> > : public mod <K, off <T> > { };

template <typename K>
struct off <mod <K, key <K> > > : public mod <K, off <K> > { };

template <typename K, typename V>
class off <mod <K, key_val <K, V> > > :
	public mod <K, off <key_val <K, V> > >
{
	typedef mod <K, off <key_val <K, V> > > B;

public:
	off(const key_val <K, V>& p) : B(p) { }
};

//-----------------------------------------------------------------------------

template <typename T>
struct to_mod_type;

template <template <typename> class M, typename K>
struct to_mod_type <M <K> > { typedef mod <K, M <K> > type; };

template <typename K, typename V>
struct to_mod_type <key_val <K, V> > { typedef mod <K, key_val <K, V> > type; };

template <typename K>
struct to_mod : public t_if <is_key <K>,
	t_id <mod <K, key <K> > >,
	to_mod_type <K>
>::type { };

//-----------------------------------------------------------------------------

}  // namespace details

using details::mod;

//-----------------------------------------------------------------------------

namespace all { using ivl::keys::mod; }

//-----------------------------------------------------------------------------

}  // namespace keys

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_KEY_MOD_HPP
