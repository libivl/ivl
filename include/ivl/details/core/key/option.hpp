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

#ifndef IVL_CORE_DETAILS_KEY_OPTION_HPP
#define IVL_CORE_DETAILS_KEY_OPTION_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename D, typename S = D>
class gen
{
	const D& d() const { return static_cast <const D&>(*this); }

public:
	template <typename T>
	item <S, T>
	operator[](T& data) const { return item <S, T>(d(), data); }

	template <typename T>
	item <S, const T>
	operator[](const T& data) const { return item <S, const T>(d(), data); }

	template <typename T>
	item <S, T*>
	operator[](T data[]) const { return item <S, T*>(d(), data); }

	template <typename T>
	item <S, const T*>
	operator[](const T data[]) const { return item <S, const T*>(d(), data); }

	template <typename R, typename T>
	item <S, item <R, T> >
	operator[](item <R, T>& data) const { return item <S, item <R, T> >(d(), data); }

	template <typename R, typename T>
	item <S, item <R, T> >
	operator[](const item <R, T>& data) const { return item <S, item <R, T> >(d(), data); }
};

//-----------------------------------------------------------------------------

struct no_gen { };

template <typename D, bool I = true>
struct generate { typedef gen <D> type; };

template <typename D>
struct generate <D, false> { typedef no_gen type; };

//-----------------------------------------------------------------------------

template <typename K> struct off;
template <typename K> struct to_mod;

//-----------------------------------------------------------------------------

template <typename T>
struct atom : public cons <T>, public streamable_identifier
{
	const T& operator*() const { return static_cast <const T&>(*this); }
};

template <typename T>
struct option : public atom <T>
{
	typedef option option_type;
	const T& operator+() const { return *(*this); }
};

//-----------------------------------------------------------------------------

template <typename T, typename O = off <T> >
struct pair : public option <T>
{
	O operator~() const { return O(); }
};

template <typename T>
struct pair <off <T> > : public pair <off <T>, T> { };

//-----------------------------------------------------------------------------

template <typename T, typename O = off <T> >
struct ref_pair : public pair <T>
{
	O operator~() const { return O(static_cast <const T&>(*this)); }
};

template <typename T>
class ref_pair <off <T> > : public pair <off <T>, T>
{
	const T& ref;

public:
	ref_pair(const T& o) : ref(o) { }
	const T& operator~() const { return ref; }
};

//-----------------------------------------------------------------------------

template <typename T>
struct off :
	public off <typename to_mod <T>::type>,
	public gen <off <T> > { };

//-----------------------------------------------------------------------------

}  // namespace details

using details::atom;
using details::option;
using details::off;

//-----------------------------------------------------------------------------

namespace all {

using ivl::keys::atom;
using ivl::keys::option;

}

//-----------------------------------------------------------------------------

}  // namespace keys

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_OPTION_HPP
