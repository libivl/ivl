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

#ifndef IVL_CORE_DETAILS_TYPES_LOGIC_HPP
#define IVL_CORE_DETAILS_TYPES_LOGIC_HPP

namespace ivl {
namespace types {

// ---------------------------------------------------

struct t_true
{
	typedef t_true type;
	enum { value = true };
	operator bool() const { return true; }
	typedef bool en_true;
};

struct t_false
{
	typedef t_false type;
	enum { value = false };
	operator bool() const { return false; }
	typedef bool en_false;
};

template <class T>
struct t_detect { };

template <>
struct t_detect<t_true>
{
private:
	char t_true_size[20]; // used to identify true/false with sizeof
};

template <>
struct t_detect<t_false>
{
private:
	char t_false_size[10]; // used to identify true/false with sizeof
};

template <bool VAL>
struct t_expr : public t_false { };

template <>
struct t_expr<true> : public t_true { };

template <class VAL>
struct t_not : public t_not<typename VAL::type> { };

template <>
struct t_not<t_true> : public t_false { };

template <>
struct t_not<t_false> : public t_true { };

template <class COND, class THEN, class ELSE>
struct t_if : public t_if <typename COND::type, THEN, ELSE> { };

template <class THEN, class ELSE>
struct t_if <t_true, THEN, ELSE> { typedef THEN type; };

template <class THEN, class ELSE>
struct t_if <t_false, THEN, ELSE> { typedef ELSE type; };

template <bool COND, class THEN, class ELSE>
struct t_if_b : t_if <t_expr <COND>, THEN, ELSE> { };

template <class A, class B>
struct t_eq : public t_false { };

template <class A>
struct t_eq <A, A> : public t_true { };

template <class A, class B>
struct t_neq : public t_not<typename t_eq<A, B>::type> { };

// ---------------------------------------------------

template <class X, class Y>
struct t_and : public t_and<typename X::type, typename Y::type> { };

template <>
struct t_and<t_true, t_true> : public t_true { };

template <>
struct t_and<t_true, t_false> : public t_false { };

template <>
struct t_and<t_false, t_true> : public t_false { };

template <>
struct t_and<t_false, t_false> : public t_false { };

template <class X, class Y>
struct t_or : public t_or<typename X::type, typename Y::type> { };

template <>
struct t_or<t_true, t_true> : public t_true { };

template <>
struct t_or<t_true, t_false> : public t_true { };

template <>
struct t_or<t_false, t_true> : public t_true { };

template <>
struct t_or<t_false, t_false> : public t_false { };

template <class X, class Y>
struct t_xor : public t_xor<typename X::type, typename Y::type> { };

template <>
struct t_xor<t_true, t_true> : public t_false { };

template <>
struct t_xor<t_true, t_false> : public t_true { };

template <>
struct t_xor<t_false, t_true> : public t_true { };

template <>
struct t_xor<t_false, t_false> : public t_false { };

template <class X, class Y, class Z>
struct t_and_3 : public t_and<t_and<X, Y>, Z> { };

template <class X, class Y, class Z>
struct t_or_3 : public t_or<t_or<X, Y>, Z> { };

template <class X, class Y, class Z>
struct t_xor_3 : public t_xor<t_xor<X, Y>, Z> { };

// ---------------------------------------------------

template <class A>
struct is_const : public t_false { };

template <class A>
struct is_const <const A> : public t_true { };

template <class A>
struct is_const <const A&> : public t_true { };

template <class A>
struct is_const <const A*> : public t_true { };

} /* namespace types */
} /* namespace ivl */


#endif // IVL_CORE_DETAILS_TYPES_LOGIC_HPP
