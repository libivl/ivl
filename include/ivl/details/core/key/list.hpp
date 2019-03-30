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

#ifndef IVL_CORE_DETAILS_KEY_LIST_HPP
#define IVL_CORE_DETAILS_KEY_LIST_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

using namespace types;

//-----------------------------------------------------------------------------

template <typename, typename>
struct node;

typedef node <term, term> null;

template <typename, typename = null>
struct node;

//-----------------------------------------------------------------------------

template <unsigned P, typename T>
class car
{
	typedef number <P> N;
	const T val;

public:
	car(const T& v) : val(v) { }
	const T& operator()(N) const { return val; }
	const T& operator* ()  const { return val; }
};

//-----------------------------------------------------------------------------

template <typename N>
struct cdr;

template <typename T, typename TN>
class cdr <node <T, TN> >
{
	typedef node <T, TN> N;
	const N& d() const { return static_cast <const N&>(*this); }

public:
	const TN& operator++() const { return d(); }
};

template <>
class cdr <null> { };

//-----------------------------------------------------------------------------

template <typename T>
class cons_base
{
	const T& d() const { return static_cast <const T&>(*this); }

protected:
	typedef node <T> N;
	N n() const { return N(d()); }
};

template <typename T, typename TN>
class cons_base <node <T, TN> >
{
protected:
	typedef node <T, TN> N;
	const N& n() const { return d(); }

private:
	const N& d() const { return static_cast <const N&>(*this); }
};

//-----------------------------------------------------------------------------

template <typename T>
class cons : public cons_base <T>
{
	typedef cons_base <T> B;
	typedef typename B::N N;
	template <typename U>
	struct R { typedef node <typename create_new <U>::type, N> type; };

public:
	template <typename U> typename R <U>::type
	operator,(const U& v) const { return typename R <U>::type(v, B::n()); }

	template <typename U> node <const U*, N>
	operator,(const U v[]) const { return node <const U*, N>(v, B::n()); }
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::null;
using details::node;

//-----------------------------------------------------------------------------

namespace lists {

using details::car;
using details::cdr;
using details::cons;

}  // namespace lists

//-----------------------------------------------------------------------------

namespace all {

using details::null;
using details::node;

}  // namespace all

//-----------------------------------------------------------------------------

}  // namespace keys

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_LIST_HPP
