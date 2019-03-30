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

#ifndef IVL_CORE_DETAILS_KEY_NODE_HPP
#define IVL_CORE_DETAILS_KEY_NODE_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <>
class node <term, term> : public pair <null, null>, public gen <null>
{
	typedef cons <null> C;
	typedef pair <null, null> P;
	typedef gen  <null> G;

public:
	using P::operator~;
	using P::operator+;
	using G::operator[];
	using C::operator,;

	enum { length = 0 };
	node() { }
};

//-----------------------------------------------------------------------------

template <typename T>
class node <T> : public car <0, T>, public null,
	public cdr <node <T> >, public ref_pair <node <T> >, public gen <node <T> >
{
	typedef car <0, T> A;
	typedef cons <node <T> > C;
	typedef cdr <node <T> > D;
	typedef ref_pair <node <T> > P;
	typedef gen <node <T> > G;

public:
	using P::operator~;
	using P::operator+;
	using G::operator[];
	using A::operator();
	using A::operator*;
	using D::operator++;
	using C::operator,;

	enum { length = 1 };
	node(const T& v, const null& = null()) : A(v) { }
};

//-----------------------------------------------------------------------------

template <typename T, typename TN>
class node : public car <TN::length, T>, public TN,
	public cdr <node <T, TN> >, public ref_pair <node <T, TN> >,
	public gen <node <T, TN> >
{
	typedef car <TN::length, T> A;
	typedef cons <node <T, TN> > C;
	typedef cdr <node <T, TN> > D;
	typedef ref_pair <node <T, TN> > P;
	typedef gen <node <T, TN> > G;

public:
	using P::operator~;
	using P::operator+;
	using G::operator[];
	using TN::operator();
	using A::operator();
	using A::operator*;
	using D::operator++;
	using C::operator,;

	enum { length = TN::length + 1 };
	node(const T& v, const TN& vn) : A(v), TN(vn) { }
};

//-----------------------------------------------------------------------------

template <typename T, typename TN>
class off <node <T, TN> > : public ref_pair <off <node <T, TN> > >,
	public gen <off <node <T, TN> > >
{
	typedef ref_pair <off <node <T, TN> > > B;

public:
	off(const node <T, TN>& n) : B(n) { }
};

//-----------------------------------------------------------------------------

template <unsigned P, typename T>
const T& at(const car <P, T>& e) { return *e; }

//-----------------------------------------------------------------------------

template <typename S, typename T, typename TN>
inline S& operator<<(S& s, const node <T, TN>& n) { return s << ++n << *n; }

template <typename S>
inline S& operator<<(S& s, null) { return s; }

template <typename S, typename T, typename TN>
inline S& operator<<(S& s, const off <node <T, TN> >& on)
{
	const node <T, TN>& n = ~on;
	return s << ~*n << ~++n;
}

//-----------------------------------------------------------------------------

template <typename T, typename TN>
struct identity <node <T, TN> > : public join_identity <T, TN> { };

template <>
struct identity <null> { typedef no_id type; };

//-----------------------------------------------------------------------------

static __attribute__ ((unused))
null _;

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

namespace lists { using details::_; }

//-----------------------------------------------------------------------------

using details::node;
using details::null;
using details::at;

//-----------------------------------------------------------------------------

namespace all {

using ivl::keys::node;
using ivl::keys::null;
using ivl::keys::at;

}  // namespace all

//-----------------------------------------------------------------------------

}  // namespace keys

using keys::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_NODE_HPP
