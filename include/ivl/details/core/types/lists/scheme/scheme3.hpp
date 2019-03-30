/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the nulls of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the nulls
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_SCHEME_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_SCHEME_HPP

namespace ivl {

namespace types {

namespace scheme {

//-----------------------------------------------------------------------------

typedef syntax_rules rules;
//typedef fun_rules cases;
typedef onedot dot;


//-----------------------------------------------------------------------------

KEYWORD(oops,           "oops")


//-----------------------------------------------------------------------------

KEYWORD(let,            "let")

template <> struct define_syntax <let> :
_<syntax_rules, _<
	_<_<_<a, v>, etc>, b, etc>,
	_<_<lambda, _<a, etc>, b, etc>, v, etc>
> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(macro,          "macro")
KEYWORD(fun,            "fun")
KEYWORD(fn,             "fn")
KEYWORD(match,          "match")
KEYWORD(with,           "with")

//-----------------------------------------------------------------------------

template <> struct define_syntax <fn> :
_<rules, _<>, _<
	_<p, t>, _<fun, _<p, t> >
> >
{ };

template <> struct define_syntax <fun> :
_<rules, _<>, _<
	_<c, etc>, _<cases, _<>, c, etc>
> >
{ };

template <> struct define_syntax <match> :
_<rules, _<with>,
	_<_<x, with, c, etc>, _<_<fun, c, etc>, x> >,
	_<_<x,       c, etc>, _<_<fun, c, etc>, x> >
>
{ };


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

KEYWORD(id,             "id")



//-----------------------------------------------------------------------------

KEYWORD(_if,            "if")
KEYWORD(then,           "then")
KEYWORD(is,             "is")
KEYWORD(_not,           "not")
KEYWORD(_and,           "and")
KEYWORD(_or,            "or")

KEYWORD(_not2,           "not2")

//-----------------------------------------------------------------------------
/*
template <> struct define_syntax <_if> :
_<let,
	_<_<i, _<fun,
		_<_<_false>, _<macro, _<_<t, e>, e> > >,
		_<_<_true>,  _<macro, _<_<t, e>, t> > >
	> > >,
	_<rules, _<then, _else>,
		_<_<_if, c, then, t, _else, e>, _<i, c, t, e> >,
		_<_<_if, c,       t,        e>, _<i, c, t, e> >
	>
>
{ };
*/


 template <> struct define_syntax <_if> :
 _<rules, _<then, _else>,
 	_<_<c, then, t, _else, e>, _<cond, _<c, t>, _<_else, e> > >,
 	_<_<c,       t,        e>, _<cond, _<c, t>, _<_else, e> > >
 >
 { };


// template <> struct define_syntax <_if> :
// _<rules, _<then, _else>,
// 	_<_<_if, c, then, t, _else, e>, _<cond, _<c, t>, _<_else, e> > >,
// 	_<_<_if, c,       t,        e>, _<cond, _<c, t>, _<_else, e> > >
// >
// { };

template <> struct define <is> :
_<fun,
	_<_<_false>, _false>,
	_<_<_true>,  _true>
>
{ };

template <> struct define <_not> :
_<fun,
	_<_<_false>, _true>,
	_<_<_true>,  _false>
>
{ };

template <> struct define <_not2> :
_<fun,
	_<_<_false, _false>, _true>,
	_<_<_true, _true>,  _false>
>
{ };

template <> struct define_syntax <_and> :
_<rules, _<>,
	_<_<>, _true>,
	_<_<a>, _<is, a> >,
	_<_<a, b, etc>, _<_if, a, _<_and, b, etc>, _false> >
>
{ };

template <> struct define_syntax <_or> :
_<rules, _<>,
	_<_<>, _false>,
	_<_<a>, _<is, a> >,
	_<_<a, b, etc>, _<_if, a, _true, _<_or, b, etc> > >
>
{ };

//-----------------------------------------------------------------------------

template <> struct define <id> :
_<lambda, _<x>, x>
{ };

//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------

KEYWORD(seq,            "seq")
KEYWORD(seq0,            "seqzero")
KEYWORD(seq1,            "seqzero1")
KEYWORD(fold,           "fold")
KEYWORD(map,            "map")
KEYWORD(append,         "append")

//-----------------------------------------------------------------------------

template <> struct define <seq0> :
_<fn, _<e, m, f, l>, _<match, l,
	_<_<_<> >, e>,
	_<_<_<a, dot, l> >, _<f, _<m, a> > >
> >
{ };

template <> struct define <seq1> :
_<fn, _<e, m, f, l>, _<f, _<m, a> >
>
{ };

//	_<_<match, x,       c, etc>, _<_<fun, c, etc> /*, x*/> >

//template <> struct define_syntax <fn> :
//_<rules, _<>, _<
//	_<fn, p, t>, _<fun, _<p, t> >
//> > { };

//template <> struct define_syntax <fun> :
//_<rules, _<>, _<
//	_<fun, c, etc>, _<cases, _<>, c, etc>
//> >
//{ };

template <> struct define <seq> :
_<fn, _<e, m, f, l>, _<match, l,
	_<_<_<> >, e>,
	_<_<_<a, dot, l> >, _<f, _<m, a>, _<seq, e, m, f, l> > >
> >
{ };

template <> struct define <fold> :
_<fn, _<e>, _<seq, e, id> >
{ };

template <> struct define <map> :
_<fn, _<e, m>, _<seq, e, m, cons> >
{ };

template <> struct define <append> :
_<fn, _<l1, l2>, _<fold, l2, cons, l1> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(lat,            "lat?")
KEYWORD(member,         "member?")
KEYWORD(in,             "in?")

//-----------------------------------------------------------------------------

template <> struct define <lat> :
_<seq, _true, atom, _and>
{ };

template <> struct define <member> :
_<fn, _<a>, _<seq, _false, _<eq, a>, _or> >
{ };

template <> struct define <in> :
_<fn, _<la, a>, _<member, a, la> >
{ };


//-----------------------------------------------------------------------------

KEYWORD(edit,           "edit")
KEYWORD(replace,        "replace")

//-----------------------------------------------------------------------------

template <> struct define <edit> :
_<fn, _<t, r, l>, _<match, l,
	_<_<_<> >, _<> >,
	_<_<_<a, dot, l> >, _<
		_if, _<t, a>, _<append, r, l>, _<a, dot, _<edit, t, r, l> >
	> >
> >
{ };

template <> struct define <replace> :
_<fn, _<a>, _<edit, _<eq, a> > >
{ };

//-----------------------------------------------------------------------------

KEYWORD(letrec,         "letrec")

template <> struct define_syntax <letrec> :
_<syntax_rules, _<
	_<_<_<a, v>, etc>, b, etc>,
	_<let, _<_<a, _0>, etc>,
		_<let, _<_<f, v>, etc>,
			_<set_b, a, f>, etc
		>,
		b, etc
	>
> >
{ };


//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

KEYWORD(remove,         "remove")
KEYWORD(insert_l,       "insert<")
KEYWORD(insert_r,       "insert>")
KEYWORD(subst,          "subst")
KEYWORD(subst2,         "subst2")

//-----------------------------------------------------------------------------

template <> struct define <remove> :
_<fn, _<a>, _<replace, a, _<> > >
{ };

template <> struct define <insert_l> :
_<fn, _<n, o>, _<replace, o, _<n, o> > >
{ };

template <> struct define <insert_r> :
_<fn, _<n, o>, _<replace, o, _<o, n> > >
{ };

template <> struct define <subst> :
_<fn, _<n, o>, _<replace, o, _<n> > >
{ };

template <> struct define <subst2> :
_<fn, _<n, o1, o2>, _<edit, _<in, _<o1, o2> >, _<n> > >
{ };


#if 0


//-----------------------------------------------------------------------------




KEYWORD(_if,            "if")

template <> struct define_syntax <_if> :
_<syntax_rules, _<
	_<_if, c, t, e>,
	_<cond, _<c, t>, _<_else, e> >
> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(is,             "is")

template <> struct define_syntax <is> :
_<syntax_rules, _<
	_<is, a>,
	_<_if, a, _true, _false>
> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(_and,           "and")

template <> struct define_syntax <_and> :
_<syntax_rules, _<>, _<
	_<_and, a, b>,
	_<_if, a, _<is, b>, _false>
> , _<
	_<_and, b, b>,
	_<_if, b, _<is, b>, _false>
> 
>
{ };

//-----------------------------------------------------------------------------

KEYWORD(_or,            "or")

template <> struct define_syntax <_or> :
_<syntax_rules, _<
	_<_or, a, b>,
	_<_if, a, _true, _<is, b> >
> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(_not,           "not")

template <> struct define_syntax <_not> :
_<syntax_rules, _<
	_<_not, a>,
	_<_if, a, _false, _true>
> >
{ };


//-----------------------------------------------------------------------------

#endif

KEYWORD(lett,            "lett")
/*
template <> struct define_syntax <lett> :
_<syntax_rules, _<
	_<lett, _<_<a, v>, etc> >,
	_<_<lambda, _<>, _<_<v, etc> > > >
> >
{ };
*/

//note: if I put _<let, _<_<a, "_0">, etc>, _<a, _1, a, etc> >
// i get nat
template <> struct define_syntax <lett> :
_<syntax_rules, _<
	_<lett, _<_<a, v>, etc>, b, etc>,
	_<let, _<_<a, _0>, etc>,
		_<let, _<_<f, v>, etc>,
			_<set_b, a, f>, etc
		>
	>
	/*_<let, _<_<a, _0>, etc>,
		_<let, _<_<f, v>, etc>,
			_<set_b, a, f>, etc
		>
	>*/
> >
{ };

#if 0
//-----------------------------------------------------------------------------

KEYWORD(letrec,         "letrec")

template <> struct define_syntax <letrec> :
_<syntax_rules, _<
	_<letrec, _<_<a, v>, etc>, b, etc>,
	_<let, _<_<a, _0>, etc>,
		_<let, _<_<f, v>, etc>,
			_<set_b, a, f>, etc
		>,
		b, etc
	>
> >
{ };


//-----------------------------------------------------------------------------

KEYWORD(eq_list,        "eq_list?")
KEYWORD(equal,          "equal?")


template <> struct define <equal> :
_<letrec, _<
	_<E,
		_<lambda, _<e1, e2>, _<
			cond,
			_<_<_and, _<atom, e1>, _<atom, e2> >, _<eq, e1, e2> >,
			_<_<_or, _<atom, e1>, _<atom, e2> >, _false>,
			_<_else, _<L, e1, e2> >
		> >
	>,
	_<L,
		_<lambda, _<l1, l2>, _<
			cond,
			_<_<_and, _<null, l1>, _<null, l2> >, _true>,
			_<_<_or, _<null, l1>, _<null, l2> >, _false>,
			_<_else, _<_and,
				_<E, _<car, l1>, _<car, l2> >,
				_<L, _<cdr, l1>, _<cdr, l2> >
			> >
		> >
	>
>, E>
{ };

template <> struct define <eq_list> :
_<lambda, _<l1, l2>, _<
	cond,
	_<_<_and, _<null, l1>, _<null, l2> >, _true>,
	_<_<_or, _<null, l1>, _<null, l2> >, _false>,
	_<_else, _<_and,
		_<equal, _<car, l1>, _<car, l2> >,
		_<eq_list, _<cdr, l1>, _<cdr, l2> >
	> >
> >
{ };

//-----------------------------------------------------------------------------

// template <> struct define <equal> :
// _<lambda, _<e1, e2>, _<
// 	cond,
// 	_<_<_and, _<atom, e1>, _<atom, e2> >, _<eq, e1, e2> >,
// 	_<_<_or, _<atom, e1>, _<atom, e2> >, _false>,
// 	_<_else, _<eq_list, e1, e2> >
// > >
// { };


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

KEYWORD(id,             "id")

template <> struct define <id> :
_<lambda, _<l>, l>
{ };

//-----------------------------------------------------------------------------

KEYWORD(eq_c,           "eq_c?")

template <> struct define <eq_c> :
_<lambda, _<c>, _<lambda, _<x>, _<eq, c, x> > >
{ };

KEYWORD(eq_or,           "eq_or?")

template <> struct define <eq_or> :
_<lambda, _<c1, c2>, _<lambda, _<x>, _<_or, _<eq, c1, x>, _<eq, c2, x> > > >
{ };

//-----------------------------------------------------------------------------

KEYWORD(comb,           "comb")

template <> struct define <comb> :
_<lambda, _<e, f, l>, _<_if, _<null, l>, e, _<f, _<car, l>, _<cdr, l> > > >
{ };

KEYWORD(fold,           "fold")

template <> struct define <fold> :
_<lambda, _<e, f, l>, _<
	comb, e, _<lambda, _<c, d>, _<f, c, _<fold, e, f, d> > >, l
> >
{ };

KEYWORD(seq,            "seq")

template <> struct define <seq> :
_<lambda, _<e, f, m, l>, _<
	fold, e, _<lambda, _<c, d>, _<f, _<m, c>, d> >, l
> >
{ };

KEYWORD(map,            "map")

template <> struct define <map> :
_<lambda, _<e, m, l>, _<seq, e, cons, m, l> >
{ };

KEYWORD(append,         "append")

template <> struct define <append> :
_<lambda, _<l1, l2>, _<fold, l2, cons, l1> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(lat,            "lat?")

//template <> struct define <lat> :
//_<lambda, _<l>, _<seq, _true, atom, _and, l> > { };

template <> struct define <lat> :
_<lambda, _<l>, _<
	cond,
	_<_<null, l>, _true>,
	_<_<atom, _<car, l> >, _<lat, _<cdr, l> > >,
	_<_else, _false>
> > 
{ };

#endif

#if 0
KEYWORD(member,         "member?")

template <> struct define <member> :
_<lambda, _<a, la>, _<seq, _false, _<eq_c, a>, _or, la> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(edit,           "edit")

template <> struct define <edit> :
_<lambda, _<t, r, la>, _<
	comb, _<>,
	_<lambda, _<c, d>, _<
		_if, _<t, c>, _<append, r, d>, _<cons, c, _<edit, t, r, d> >
	> >, la
> >
{ };

KEYWORD(replace,        "replace")

template <> struct define <replace> :
_<lambda, _<a, r, la>, _<edit, _<eq_c, a>, r, la> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(remove,         "remove")

template <> struct define <remove> :
_<lambda, _<a, l>, _<replace, a, _<>, l> >
{ };

KEYWORD(insert_l,       "insert<")

template <> struct define <insert_l> :
_<lambda, _<n, o, l>, _<replace, o, _<n, o>, l> >
{ };

KEYWORD(insert_r,       "insert>")

template <> struct define <insert_r> :
_<lambda, _<n, o, l>, _<replace, o, _<o, n>, l> >
{ };

KEYWORD(subst,          "subst")

template <> struct define <subst> :
_<lambda, _<n, o, l>, _<replace, o, _<n>, l> >
{ };

KEYWORD(subst2,         "subst2")

template <> struct define <subst2> :
_<lambda, _<n, o1, o2, l>, _<edit, _<eq_or, o1, o2>, _<n>, l> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(inc,            "inc")

template <> struct define <inc> :
_<lambda, _<n>, _<add, n, _1> >
{ };

//-----------------------------------------------------------------------------

KEYWORD(Y,              "Y")

template <> struct define <Y> :
_<lambda, _<f>, _<
	_<lambda, _<g>, _<g, g> >,
	_<lambda, _<h>, _<
		f, _<lambda, _<x>, _<_<h, h>, x> >
	> >
> >
{ };
#endif
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// forms

// cond / _else             TODO -> if, is, and, or, not
// lambda                        -> define, Y
// set_b                    TODO ->
// define                   TODO ->
// syntax_rules             TODO ->

//-----------------------------------------------------------------------------
// atom / list primitives

// null                          -> zero? atom? car, cdr, cons
// atom                          -> num?, lat? null?, eq?
// eq                            -> equal?, eq_list?, atom?, num?

//-----------------------------------------------------------------------------
// numeric primitives

// num                           -> eq#?, gt?, lt?, zero?, tup? atom?, add, sub, mul
// lt                            -> le?, gt?, eq#?, min, max, num?
// add                           -> add:, add!, inc, sum, sub, neg, mul, num?
// sub                           -> sub:, sub!, dec, add, neg, quot, num?
// mul                           -> mul:, prod, exp, quot, rem, div?, add, num?
// quot                          -> quot:, quot!, rem, mod, div?, mul, sub, num?

//-----------------------------------------------------------------------------
// macros


}  // namespace scheme
}  // namespace types
}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_SCHEME_HPP
