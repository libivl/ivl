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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STREAM_STREAM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STREAM_STREAM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

using ivl::operator<<;

//-----------------------------------------------------------------------------

template <typename T>
struct inner { };

template <typename O, typename T>
O& operator<<(O& o, inner <T>) { return o << T (); }

//-----------------------------------------------------------------------------

template <typename O>
O& operator<<(O& o, inner <_true>)
{
	return o << _white << _true () << _green;
}

template <typename O>
O& operator<<(O& o, inner <_false>)
{
	return o << _white << _false () << _green;
}

template <typename O, int N>
O& operator<<(O& o, inner <number <N> >)
{
	return o << _white << number <N> () << _green;
}

//-----------------------------------------------------------------------------

template <typename O, typename I>
O& operator<<(O& o, rec <I>) { return o << _yellow << I () << "..." << _green; }

template <typename O, typename I>
O& operator<<(O& o, block <rec <I> >) { return o << _yellow << "..." << _green; }

template <typename O, typename I, typename V>
O& operator<<(O& o, rec <I, V>)
{
	return o << _yellow << "[" << I () << "]" << _green << V ();
}

//-----------------------------------------------------------------------------

// // only for debugging
// template <typename O>
// O& operator<<(O& o, term) { return o << "."; }

template <typename O>
O& operator<<(O& o, null) { return o; }

//-----------------------------------------------------------------------------

template <typename O, typename T>
O& operator<<(O& o, node <T>) { return o << inner <T> (); }

template <typename O, typename T, typename TN>
O& operator<<(O& o, node <T, TN>)
{
	return o << inner <T> () << " " << TN ();
}

//-----------------------------------------------------------------------------
// newlines for every node at 1st level

template <typename T, bool B = false>
struct nl { };

template <class O, typename T, bool B>
O& operator<<(O& o, nl <T, B>) { return o << T (); }

template <class O, typename T, bool B>
O& operator<<(O& o, nl <node <T>, B>) { return o << nl <T> (); }

template <class O, typename T, typename TN, bool B>
O& operator<<(O& o, nl <node <T, TN>, B>)
{
	return o << T () << std::endl << nl <TN, B> ();
}

template <class O, typename T>
O& operator<<(O& o, node <scheme::cond, T>)
{
	return o << nl <node <scheme::cond, T> > ();
}

//-----------------------------------------------------------------------------
// "block" every nested list at 1st level

template <class O>
O& operator<<(O& o, nl <node <null>, false>) { return o << node <null> (); }

template <class O>
O& operator<<(O& o, nl <node <null>, true>) { return o << node <null> (); }

template <class O, typename T, typename TN>
O& operator<<(O& o, nl <node <node <T, TN> >, false>)
{
	return o << node <node <T, TN> > ();
}

template <class O, typename T, typename TN>
O& operator<<(O& o, nl <node <node <T, TN> >, true>)
{
	return o << node <block <node <T, TN>, true> > ();
}

template <class O, typename T, typename TN, typename TR>
O& operator<<(O& o, nl <node <node <T, TN>, TR>, false>)
{
	return o << node <node <T, TN> > () << std::endl << nl <TR> ();
}

template <class O, typename T, typename TN, typename TR>
O& operator<<(O& o, nl <node <node <T, TN>, TR>, true>)
{
	return o <<
		node <block <node <T, TN>, true> > () << std::endl << nl <TR, true> ();
}

//-----------------------------------------------------------------------------
// newline + indent

struct begin { };
struct end { };

template <typename O>
O& operator<<(O& o, begin) { return o << indent++ << std::endl; }

template <typename O>
O& operator<<(O& o, end) { return o << indent-- << std::endl; }

template <typename T>
struct display { };

template <typename O, typename T>
O& operator<<(O& o, display <T>) { return o << begin () << T () << end (); }

//-----------------------------------------------------------------------------
// newlines for parentheses

template <bool NL = false>
struct open { };

template <bool NL = false>
struct close { };

template <typename O>
O& operator<<(O& o, open  <false>) { return o << "("; }

template <typename O>
O& operator<<(O& o, close <false>) { return o << ")"; }

template <typename O>
O& operator<<(O& o, open  <true>) { return o << open <false> () << begin (); }

template <typename O>
O& operator<<(O& o, close <true>) { return o << end () << close <false> (); }

//-----------------------------------------------------------------------------
// newlines for nodes (blocks)

// first defined in eval; NL defaults to false
template <typename T, bool NL>
struct block : id <block <T, NL> > { };

template <typename O, typename T, bool NL>
O& operator<<(O& o, block <T, NL>) { return o << inner <T> (); }

template <typename O, typename T, typename TN, bool NL>
O& operator<<(O& o, block <node <T, TN>, NL>)
{
	return o << open <NL> () << node <T, TN> () << close <NL> ();
}

template <typename O, typename T, typename TN, bool NL>
O& operator<<(O& o, block <nl <node <T, TN> >, NL>)
{
	return o << open <NL> () << nl <node <T, TN> > () << close <NL> ();
}

template <class O, typename T, bool NL>
O& operator<<(O& o, block <node <scheme::cond, T>, NL>)
{
	return o << open <true> () << node <scheme::cond, T> () << close <true> ();
}

//-----------------------------------------------------------------------------
// block construction by node

template <typename O, typename T, typename TN>
O& operator<<(O& o, node <node <T, TN> >)
{
	return o << node <block <node <T, TN> > > ();
}

template <typename O, typename T, typename TN, typename TR>
O& operator<<(O& o, node <node <T, TN>, TR>)
{
	return o << node <block <node <T, TN> >, TR> ();
}

//-----------------------------------------------------------------------------
// block construction by lambda and functions

template <typename O, typename A, typename B>
O& operator<<(O& o, node <scheme::lambda, node <A, node <B> > >)
{
	return o << scheme::lambda () << " " <<
		block <A> () << " " << block <B, true> ();
}

template <typename O, typename A, typename B>
O& operator<<(O& o, node <scheme::lambda, node <A, B> >)
{
	return o << scheme::lambda () << " " <<
		block <A> () << " " << display <nl <B, true> > ();
}

//-----------------------------------------------------------------------------
// block construction by syntax and function rules

template <typename T>
struct rules { };

template <typename O, typename D>
O& operator<<(O& o, node <scheme::cases, D>)
{
	return o << node <rules <scheme::cases>, D> ();
}

template <typename O, typename D>
O& operator<<(O& o, node <scheme::rules, D>)
{
	return o << node <rules <scheme::rules>, D> ();
}

template <typename O, typename K, typename L, typename P, typename T>
O& operator<<(O& o,
	node <rules <K>, node <L, node <node <P, node <T> > > > >
)
{
	return o << K () << " " << block <L> () << " " <<
		block <node <nl <node <P, node <T> > > >, true> ();
}

template <typename O, typename K, typename L, typename R>
O& operator<<(O& o, node <rules <K>, node <L, R> >)
{
	return o << K () << " " << block <L> () << display <nl <R> > ();
}

//-----------------------------------------------------------------------------
// block construction by other objects

template <typename O, typename F, typename E>
O& operator<<(O& o, closure <F, E>) { return o << block <F> ();
}

template <typename O, typename L>
O& operator<<(O& o, base <L>)
{
	return o << block <typename flush <L>::type> ();
}

//-----------------------------------------------------------------------------

template <typename O, typename C, typename A, typename G, int Z>
O& operator<<(O& o, part <C, A, G, Z>)
{
	return o << open <> () << scheme::partial () << " " << C () << close <> ();
}

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STREAM_STREAM_HPP
