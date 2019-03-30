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

#ifndef IVL_CORE_DETAILS_TYPES_MACRO_HPP
#define IVL_CORE_DETAILS_TYPES_MACRO_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

namespace macro {

using types::cond;

struct a { };
struct b { };
struct c { };
struct d { };
struct e { };
struct f { };
struct g { };
struct h { };
struct i { };
struct j { };
struct k { };
struct l { };
struct m { };
struct n { };
struct o { };
struct p { };
struct q { };
struct r { };
struct s { };
struct t { };
struct u { };
struct v { };
struct w { };
struct x { };
struct y { };
struct z { };

struct la { };  // list of atoms
struct ls { };  // list of sets

// expressions
struct e1 { };
struct e2 { };
struct e3 { };
struct e4 { };

// lists
struct l1 { };
struct l2 { };

// numbers
struct n1 { };
struct n2 { };

// 'old'
struct o1 { };
struct o2 { };

// sets
struct s1 { };
struct s2 { };

// tuples
struct t1 { };
struct t2 { };

//-----------------------------------------------------------------------------

// equal? and eq_list? exhibit mutual recurrence, so we use a special
// strategy:

// alias of equal?
struct a_equal { };

// struct version of equal? where we can use different versions of
// eq_list? as specified by template argument EQ_LIST
template <typename EQ_LIST>
class s_equal : public
_<define, a_equal, _<lambda, _<e1, e2>, _<
	cond,
	_<_<_and, _<atom, e1>, _<atom, e2> >, _<eq, e1, e2> >,
	_<_<_or, _<atom, e1>, _<atom, e2> >, _false>,
	_<_else, _<EQ_LIST, e1, e2> >
> > >
{ };

//-----------------------------------------------------------------------------

// alias of eq_list?
struct a_eq_list { };

// nested version of equal? using a_eq_list (just the alias of eq_list?) as
// EQ_LIST to call eq_list? within equal?
typedef s_equal <a_eq_list>::list n_equal;

// public version of eq_list? using n_equal (the nested version of equal?)
typedef
_<define, a_eq_list, _<lambda, _<l1, l2>, _<
	cond,
	_<_<_and, _<null, l1>, _<null, l2> >, _true>,
	_<_<_or, _<null, l1>, _<null, l2> >, _false>,
	_<_else, _<_and,
		_<n_equal, _<car, l1>, _<car, l2> >,
		_<a_eq_list, _<cdr, l1>, _<cdr, l2> >
	> >
> > >
eq_list;

// public version of equal? using eq_list (the public version of eq_list?)
// as EQ_LIST; both equal and n_equal have the same alias (a_equal), so get
// printed out the same way
typedef s_equal <eq_list>::list equal;

//-----------------------------------------------------------------------------

struct a_eq_c { }; typedef
_<define, a_eq_c, _<lambda, _<c>, _<
	lambda, _<x>, _<eq, c, x>
> > >
eq_c;

//-----------------------------------------------------------------------------

struct a_lat { }; typedef
_<define, a_lat, _<lambda, _<l>, _<
	cond,
	_<_<null, l>, _true>,
	_<_<atom, _<car, l> >, _<a_lat, _<cdr, l> > >,
	_<_else, _false>
> > >
lat;

//-----------------------------------------------------------------------------

struct a_member { }; typedef
_<define, a_member, _<lambda, _<a, la>, _<
	cond,
	_<_<null, la>, _false>,
	_<_<eq, a, _<car, la> >, _true>,
	_<_else, _<a_member, a, _<cdr, la> > >
> > >
member;

//-----------------------------------------------------------------------------

struct a_remove { }; typedef
_<define, a_remove, _<lambda, _<a, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, a, _<car, la> >, _<cdr, la> >,
	_<_else, _<cons, _<car, la>, _<a_remove, a, _<cdr, la> > > >
> > >
remove;

//-----------------------------------------------------------------------------

struct a_insert_l { }; typedef
_<define, a_insert_l, _<lambda, _<n, o, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o, _<car, la> >, _<cons, n, _<cons, o, _<cdr, la> > > >,
	_<_else, _<cons, _<car, la>, _<a_insert_l, n, o, _<cdr, la> > > >
> > >
insert_l;

//-----------------------------------------------------------------------------

struct a_insert_r { }; typedef
_<define, a_insert_r, _<lambda, _<n, o, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o, _<car, la> >, _<cons, o, _<cons, n, _<cdr, la> > > >,
	_<_else, _<cons, _<car, la>, _<a_insert_r, n, o, _<cdr, la> > > >
> > >
insert_r;

//-----------------------------------------------------------------------------

struct a_subst { }; typedef
_<define, a_subst, _<lambda, _<n, o, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o, _<car, la> >, _<cons, n, _<cdr, la> > >,
	_<_else, _<cons, _<car, la>, _<a_subst, n, o, _<cdr, la> > > >
> > >
subst;

//-----------------------------------------------------------------------------

struct a_subst2 { }; typedef
_<define, a_subst2, _<lambda, _<n, o1, o2, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o1, _<car, la> >, _<cons, n, _<cdr, la> > >,
	_<_<eq, o2, _<car, la> >, _<cons, n, _<cdr, la> > >,
	_<_else, _<cons, _<car, la>, _<a_subst2, n, o1, o2, _<cdr, la> > > >
> > >
subst2;

//-----------------------------------------------------------------------------

struct a_remove_m { }; typedef
_<define, a_remove_m, _<lambda, _<a, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, a, _<car, la> >, _<a_remove_m, a, _<cdr, la> > >,
	_<_else, _<cons, _<car, la>, _<a_remove_m, a, _<cdr, la> > > >
> > >
remove_m;

//-----------------------------------------------------------------------------

struct a_insert_lm { }; typedef
_<define, a_insert_lm, _<lambda, _<n, o, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o, _<car, la> >, _<cons, n, _<cons, o,
		_<a_insert_lm, n, o, _<cdr, la> >
	> > >,
	_<_else, _<cons, _<car, la>, _<a_insert_lm, n, o, _<cdr, la> > > >
> > >
insert_lm;

//-----------------------------------------------------------------------------

struct a_insert_rm { }; typedef
_<define, a_insert_rm, _<lambda, _<n, o, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o, _<car, la> >, _<cons, o, _<cons, n,
		_<a_insert_rm, n, o, _<cdr, la> >
	> > >,
	_<_else, _<cons, _<car, la>, _<a_insert_rm, n, o, _<cdr, la> > > >
> > >
insert_rm;

//-----------------------------------------------------------------------------

struct a_subst_m { }; typedef
_<define, a_subst_m, _<lambda, _<n, o, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o, _<car, la> >, _<cons, n, _<a_subst_m, n, o, _<cdr, la> > > >,
	_<_else, _<cons, _<car, la>, _<a_subst_m, n, o, _<cdr, la> > > >
> > >
subst_m;

//-----------------------------------------------------------------------------

struct a_subst2_m { }; typedef
_<define, a_subst2_m, _<lambda, _<n, o1, o2, la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_<eq, o1, _<car, la> >, _<cons, n,
		_<a_subst2_m, n, o1, o2, _<cdr, la> >
	> >,
	_<_<eq, o2, _<car, la> >, _<cons, n,
		_<a_subst2_m, n, o1, o2, _<cdr, la> >
	> >,
	_<_else, _<cons, _<car, la>, _<a_subst2_m, n, o1, o2, _<cdr, la> > > >
> > >
subst2_m;

//-----------------------------------------------------------------------------

struct a_member_s { }; typedef
_<define, a_member_s, _<lambda, _<a, l>, _<
	cond,
	_<_<null, l>, _false>,
	_<_<atom, _<car, l> >, _<_or,
		_<eq, a, _<car, l> >,
		_<a_member_s, a, _<cdr, l> >
	> >,
	_<_else, _<_or,
		_<a_member_s, a, _<car, l> >,
		_<a_member_s, a, _<cdr, l> >
	> >
> > >
member_s;

//-----------------------------------------------------------------------------

struct a_remove_s { }; typedef
_<define, a_remove_s, _<lambda, _<a, l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_<atom, _<car, l> >, _<
		cond,
		_<_<eq, a, _<car, l> >, _<a_remove_s, a, _<cdr, l> > >,
		_<_else, _<cons, _<car, l>, _<a_remove_s, a, _<cdr, l> > > >
	> >,
	_<_else, _<cons,
		_<a_remove_s, a, _<car, l> >,
		_<a_remove_s, a, _<cdr, l> >
	> >
> > >
remove_s;

//-----------------------------------------------------------------------------

struct a_insert_ls { }; typedef
_<define, a_insert_ls, _<lambda, _<n, o, l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_<atom, _<car, l> >, _<
		cond,
		_<_<eq, o, _<car, l> >, _<cons, n, _<cons, o,
			_<a_insert_ls, n, o, _<cdr, l> >
		> > >,
		_<_else, _<cons, _<car, l>, _<a_insert_ls, n, o, _<cdr, l> > > >
	> >,
	_<_else, _<cons,
		_<a_insert_ls, n, o, _<car, l> >,
		_<a_insert_ls, n, o, _<cdr, l> >
	> >
> > >
insert_ls;

//-----------------------------------------------------------------------------

struct a_insert_rs { }; typedef
_<define, a_insert_rs, _<lambda, _<n, o, l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_<atom, _<car, l> >, _<
		cond,
		_<_<eq, o, _<car, l> >, _<cons, o, _<cons, n,
			_<a_insert_rs, n, o, _<cdr, l> >
		> > >,
		_<_else, _<cons, _<car, l>, _<a_insert_rs, n, o, _<cdr, l> > > >
	> >,
	_<_else, _<cons,
		_<a_insert_rs, n, o, _<car, l> >,
		_<a_insert_rs, n, o, _<cdr, l> >
	> >
> > >
insert_rs;

//-----------------------------------------------------------------------------

struct a_subst_s { }; typedef
_<define, a_subst_s, _<lambda, _<n, o, l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_<atom, _<car, l> >, _<
		cond,
		_<_<eq, o, _<car, l> >, _<cons, n, _<a_subst_s, n, o, _<cdr, l> > > >,
		_<_else, _<cons, _<car, l>, _<a_subst_s, n, o, _<cdr, l> > > >
	> >,
	_<_else, _<cons,
		_<a_subst_s, n, o, _<car, l> >,
		_<a_subst_s, n, o, _<cdr, l> >
	> >
> > >
subst_s;

//-----------------------------------------------------------------------------

struct a_subst2_s { }; typedef
_<define, a_subst2_s, _<lambda, _<n, o1, o2, l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_<atom, _<car, l> >, _<
		cond,
		_<_<eq, o1, _<car, l> >, _<cons, n,
			_<a_subst2_s, n, o1, o2, _<cdr, l> >
		> >,
		_<_<eq, o2, _<car, l> >, _<cons, n,
			_<a_subst2_s, n, o1, o2, _<cdr, l> >
		> >,
		_<_else, _<cons, _<car, l>, _<a_subst2_s, n, o1, o2, _<cdr, l> > > >
	> >,
	_<_else, _<cons,
		_<a_subst2_s, n, o1, o2, _<car, l> >,
		_<a_subst2_s, n, o1, o2, _<cdr, l> >
	> >
> > >
subst2_s;

//-----------------------------------------------------------------------------

typedef _<car, _<> >::type nat;

typedef number <-1> _m1;
typedef number <0> _0;
typedef number <1> _1;
typedef number <2> _2;

typedef number <INT_MAX> p_inf;
typedef number <INT_MIN> m_inf;

//-----------------------------------------------------------------------------

struct a_not { }; typedef
_<define, a_not, _<lambda, _<c>, _<
	cond,
	_<c, _false>,
	_<_else, _true>
> > >
_not;

//-----------------------------------------------------------------------------

struct a_gt { }; typedef
_<define, a_gt, _<lambda, _<n1, n2>, _<
	lt, n2, n1
> > >
gt;

//-----------------------------------------------------------------------------

struct a_ge { }; typedef
_<define, a_ge, _<lambda, _<n1, n2>, _<
	_not, _<lt, n1, n2>
> > >
ge;

//-----------------------------------------------------------------------------

struct a_le { }; typedef
_<define, a_le, _<lambda, _<n1, n2>, _<
	_not, _<gt, n1, n2>
> > >
le;

//-----------------------------------------------------------------------------

struct a_eqn { }; typedef
_<define, a_eqn, _<lambda, _<n1, n2>, _<
	_and, _<le, n1, n2>, _<ge, n1, n2>
> > >
eqn;

//-----------------------------------------------------------------------------

struct a_neqn { }; typedef
_<define, a_neqn, _<lambda, _<n1, n2>, _<
	_or, _<lt, n1, n2>, _<gt, n1, n2>
> > >
neqn;

//-----------------------------------------------------------------------------

struct a_zero { }; typedef
_<define, a_zero, _<lambda, _<n>, _<
	cond,
	_<_<num, n>, _<eqn, n, _0> >,
	_<_else, _false>
> > >
zero;

//-----------------------------------------------------------------------------

struct a_sign { }; typedef
_<define, a_sign, _<lambda, _<n>, _<
	cond,
	_<_<gt, n, _0>, _1>,
	_<_<lt, n, _0>, _m1>,
	_<_else, _0>
> > >
sign;

//-----------------------------------------------------------------------------

struct a_neg { }; typedef
_<define, a_neg, _<lambda, _<n>, _<
	sub, _0, n
> > >
neg;

//-----------------------------------------------------------------------------

struct a_min { }; typedef
_<define, a_min, _<lambda, _<n1, n2>, _<
	cond,
	_<_<lt, n1, n2>, n1>,
	_<_else, n2>
> > >
min;

//-----------------------------------------------------------------------------

struct a_max { }; typedef
_<define, a_max, _<lambda, _<n1, n2>, _<
	cond,
	_<_<gt, n1, n2>, n1>,
	_<_else, n2>
> > >
max;

//-----------------------------------------------------------------------------

struct a_abs { }; typedef
_<define, a_abs, _<lambda, _<n>, _<
	max, n, _<neg, n>
> > >
abs;

//-----------------------------------------------------------------------------

struct a_inc { }; typedef
_<define, a_inc, _<lambda, _<n>, _<
	add, n, _1
> > >
inc;

//-----------------------------------------------------------------------------

struct a_dec { }; typedef
_<define, a_dec, _<lambda, _<n>, _<
	sub, n, _1
> > >
dec;

//-----------------------------------------------------------------------------

struct a_inc_t { }; typedef
_<define, a_inc_t, _<lambda, _<n>, _<
	cond,
	_<_<ge, n, _0>, nat>,
	_<_else, _<inc, n> >
> > >
inc_t;

//-----------------------------------------------------------------------------

struct a_dec_t { }; typedef
_<define, a_dec_t, _<lambda, _<n>, _<
	cond,
	_<_<le, n, _0>, nat>,
	_<_else, _<dec, n> >
> > >
dec_t;

//-----------------------------------------------------------------------------

struct a_add_t { }; typedef
_<define, a_add_t, _<lambda, _<n1, n2>, _<
	cond,
	_<_<_or, _<zero, n1>, _<zero, n2> >, nat>,
	_<_<eqn, _<sign, n1>, _<sign, n2> >, nat>,
	_<_else, _<add, n1, n2> >
> > >
add_t;

//-----------------------------------------------------------------------------

struct a_sub_t { }; typedef
_<define, a_sub_t, _<lambda, _<n1, n2>, _<
	cond,
	_<_<_or, _<zero, n1>, _<zero, n2> >, nat>,
	_<_<neqn, _<sign, n1>, _<sign, n2> >, nat>,
	_<_else, _<sub, n1, n2> >
> > >
sub_t;

//-----------------------------------------------------------------------------

struct a_quot_t { }; typedef
_<define, a_quot_t, _<lambda, _<n1, n2>, _<
	cond,
	_<_<zero, n1>, nat>,
	_<_<le, _<abs, n2>, _1>, nat>,
	_<_else, _<quot, n1, n2> >
> > >
quot_t;

//-----------------------------------------------------------------------------

struct a_rem { }; typedef
_<define, a_rem, _<lambda, _<n1, n2>, _<
	sub, n1, _<mul, _<quot, n1, n2>, n2>
> > >
rem;

//-----------------------------------------------------------------------------

struct a_mod { }; typedef
_<define, a_mod, _<lambda, _<n1, n2>, _<
	cond,
	_<_<ge, n1, _0>, _<rem, n1, n2> >,
	_<_else, _<add, _<rem, n1, n2>, _<abs, n2> > >
> > >
mod;

//-----------------------------------------------------------------------------

struct a_div { }; typedef
_<define, a_div, _<lambda, _<n1, n2>, _<
	zero, _<rem, n2, n1>
> > >
div;

//-----------------------------------------------------------------------------

struct a_even { }; typedef
_<define, a_even, _<lambda, _<n>, _<
	div, _2, n
> > >
even;

//-----------------------------------------------------------------------------

struct a_odd { }; typedef
_<define, a_odd, _<lambda, _<n>, _<
	_not, _<even, n>
> > >
odd;

//-----------------------------------------------------------------------------

struct a_sgn { }; typedef
_<define, a_sgn, _<lambda, _<n>, _<
	cond,
	_<_<even, n>, _1>,
	_<_else, _m1>
> > >
sgn;

//-----------------------------------------------------------------------------

struct a_gcd { }; typedef
_<define, a_gcd, _<lambda, _<n1, n2>, _<
	cond,
	_<_<zero, n2>, _<abs, n1> >,
	_<_else, _<a_gcd, n2, _<rem, n1, n2> > >
> > >
gcd;

//-----------------------------------------------------------------------------

struct a_lcm { }; typedef
_<define, a_lcm, _<lambda, _<n1, n2>, _<
	quot, _<abs, _<mul, n1, n2> >, _<gcd, n1, n2>
> > >
lcm;

//-----------------------------------------------------------------------------

struct a_exp { }; typedef
_<define, a_exp, _<lambda, _<n1, n2>, _<
	cond,
	_<_<_or, _<zero, n2>, _<eqn, n1, _1> >, _1>,
	_<_<eqn, n1, _m1>, _<sgn, n2> >,
	_<_else, _<mul, n1, _<a_exp, n1, _<dec_t, n2> > > >
> > >
exp;

//-----------------------------------------------------------------------------

struct a_log { }; typedef
_<define, a_log, _<lambda, _<n1, n2>, _<
	cond,
	_<_<_and, _<le, _<abs, n1>, _1>, _<eqn, n1, n2> >, _1>,
	_<_<_and, _<neqn, n1, _0>,_<eqn, n2, _1> >, _0>,
	_<_<_or, _<le, _<abs, n1>, _1>, _<le, _<abs, n2>, _1> >, nat>,
	_<_<ge, _<abs, n2>, _<abs, n1> >, _<inc, _<a_log, n1, _<quot_t, n2, n1> > > >,
	_<_<eqn, _<sign, n1>, _<sign, n2> >, _0>,
	_<_else, nat>
> > >
log;

//-----------------------------------------------------------------------------

struct a_tup { }; typedef
_<define, a_tup, _<lambda, _<l>, _<
	cond,
	_<_<null, l>, _true>,
	_<_<num, _<car, l> >, _<a_tup, _<cdr, l> > >,
	_<_else, _false>
> > >
tup;

//-----------------------------------------------------------------------------

struct a_sum { }; typedef
_<define, a_sum, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, _0>,
	_<_else, _<add,
		_<car, t>,
		_<a_sum, _<cdr, t> >
	> >
> > >
sum;

//-----------------------------------------------------------------------------

struct a_prod { }; typedef
_<define, a_prod, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, _1>,
	_<_else, _<mul,
		_<car, t>,
		_<a_prod, _<cdr, t> >
	> >
> > >
prod;

//-----------------------------------------------------------------------------

struct a_min_m { }; typedef
_<define, a_min_m, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, p_inf>,
	_<_else, _<min,
		_<car, t>,
		_<a_min_m, _<cdr, t> >
	> >
> > >
min_m;

//-----------------------------------------------------------------------------

struct a_max_m { }; typedef
_<define, a_max_m, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, m_inf>,
	_<_else, _<max,
		_<car, t>,
		_<a_max_m, _<cdr, t> >
	> >
> > >
max_m;

//-----------------------------------------------------------------------------

struct a_inc_e { }; typedef
_<define, a_inc_e, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, _<> >,
	_<_else, _<cons,
		_<inc, _<car, t> >,
		_<a_inc_e, _<cdr, t> >
	> >
> > >
inc_e;

//-----------------------------------------------------------------------------

struct a_dec_e { }; typedef
_<define, a_dec_e, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, _<> >,
	_<_else, _<cons,
		_<dec, _<car, t> >,
		_<a_dec_e, _<cdr, t> >
	> >
> > >
dec_e;

//-----------------------------------------------------------------------------

struct a_add_e { }; typedef
_<define, a_add_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<null, t1>, t2>,
	_<_<null, t2>, t1>,
	_<_else, _<cons,
		_<add, _<car, t1>, _<car, t2> >,
		_<a_add_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
add_e;

//-----------------------------------------------------------------------------

struct a_sub_e { }; typedef
_<define, a_sub_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<_and, _<null, t1>, _<null, t2> >, _<> >,
	_<_<_or, _<null, t1>, _<null, t2> >, nat>,
	_<_else, _<cons,
		_<sub, _<car, t1>, _<car, t2> >,
		_<a_sub_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
sub_e;

//-----------------------------------------------------------------------------

struct a_sign_e { }; typedef
_<define, a_sign_e, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, _<> >,
	_<_else, _<cons,
		_<sign, _<car, t> >,
		_<a_sign_e, _<cdr, t> >
	> >
> > >
sign_e;

//-----------------------------------------------------------------------------

struct a_neg_e { }; typedef
_<define, a_neg_e, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, _<> >,
	_<_else, _<cons,
		_<neg, _<car, t> >,
		_<a_neg_e, _<cdr, t> >
	> >
> > >
neg_e;

//-----------------------------------------------------------------------------

struct a_min_e { }; typedef
_<define, a_min_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<null, t1>, t2>,
	_<_<null, t2>, t1>,
	_<_else, _<cons,
		_<min, _<car, t1>, _<car, t2> >,
		_<a_min_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
min_e;

//-----------------------------------------------------------------------------

struct a_max_e { }; typedef
_<define, a_max_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<null, t1>, t2>,
	_<_<null, t2>, t1>,
	_<_else, _<cons,
		_<max, _<car, t1>, _<car, t2> >,
		_<a_max_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
max_e;

//-----------------------------------------------------------------------------

struct a_abs_e { }; typedef
_<define, a_abs_e, _<lambda, _<t>, _<
	cond,
	_<_<null, t>, _<> >,
	_<_else, _<cons,
		_<abs, _<car, t> >,
		_<a_abs_e, _<cdr, t> >
	> >
> > >
abs_e;

//-----------------------------------------------------------------------------

struct a_mul_e { }; typedef
_<define, a_mul_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<null, t1>, t2>,
	_<_<null, t2>, t1>,
	_<_else, _<cons,
		_<mul, _<car, t1>, _<car, t2> >,
		_<a_mul_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
mul_e;

//-----------------------------------------------------------------------------

struct a_quot_e { }; typedef
_<define, a_quot_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<_and, _<null, t1>, _<null, t2> >, _<> >,
	_<_<_or, _<null, t1>, _<null, t2> >, nat>,
	_<_else, _<cons,
		_<quot, _<car, t1>, _<car, t2> >,
		_<a_quot_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
quot_e;

//-----------------------------------------------------------------------------

struct a_rem_e { }; typedef
_<define, a_rem_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<_and, _<null, t1>, _<null, t2> >, _<> >,
	_<_<_or, _<null, t1>, _<null, t2> >, nat>,
	_<_else, _<cons,
		_<rem, _<car, t1>, _<car, t2> >,
		_<a_rem_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
rem_e;

//-----------------------------------------------------------------------------

struct a_mod_e { }; typedef
_<define, a_mod_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<_and, _<null, t1>, _<null, t2> >, _<> >,
	_<_<_or, _<null, t1>, _<null, t2> >, nat>,
	_<_else, _<cons,
		_<mod, _<car, t1>, _<car, t2> >,
		_<a_mod_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
mod_e;

//-----------------------------------------------------------------------------

struct a_exp_e { }; typedef
_<define, a_exp_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<_and, _<null, t1>, _<null, t2> >, _<> >,
	_<_<_or, _<null, t1>, _<null, t2> >, nat>,
	_<_else, _<cons,
		_<exp, _<car, t1>, _<car, t2> >,
		_<a_exp_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
exp_e;

//-----------------------------------------------------------------------------

struct a_log_e { }; typedef
_<define, a_log_e, _<lambda, _<t1, t2>, _<
	cond,
	_<_<_and, _<null, t1>, _<null, t2> >, _<> >,
	_<_<_or, _<null, t1>, _<null, t2> >, nat>,
	_<_else, _<cons,
		_<log, _<car, t1>, _<car, t2> >,
		_<a_log_e, _<cdr, t1>, _<cdr, t2> >
	> >
> > >
log_e;

//-----------------------------------------------------------------------------

struct a_length { }; typedef
_<define, a_length, _<lambda, _<la>, _<
	cond,
	_<_<null, la>, _0>,
	_<_else, _<inc, _<a_length, _<cdr, la> > > >
> > >
length;

//-----------------------------------------------------------------------------

struct a_occur { }; typedef
_<define, a_occur, _<lambda, _<a, la>, _<
	cond,
	_<_<null, la>, _0>,
	_<_<eq, a, _<car, la> >, _<inc, _<a_occur, a, _<cdr, la> > > >,
	_<_else, _<a_occur, a, _<cdr, la> > >
> > >
occur;

//-----------------------------------------------------------------------------

struct a_occur_s { }; typedef
_<define, a_occur_s, _<lambda, _<a, l>, _<
	cond,
	_<_<null, l>, _0>,
	_<_<atom, _<car, l> >, _<cond,
		_<_<eq, a, _<car, l> >, _<inc, _<a_occur_s, a, _<cdr, l> > > >,
		_<_else, _<a_occur_s, a, _<cdr, l> > >
	> >,
	_<_else, _<add,
		_<a_occur_s, a, _<car, l> >,
		_<a_occur_s, a, _<cdr, l> >
	> >
> > >
occur_s;

//-----------------------------------------------------------------------------

struct a_select_n { }; typedef
_<define, a_select_n, _<lambda, _<n, l>, _<
	cond,
	_<_<zero, n>, _<car, l> >,
	_<_<atom, n>, _<a_select_n, _<dec, n>, _<cdr, l> > >,
	_<_<null, n>, _<> >,
	_<_else, _<cons, _<a_select_n, _<car, n>, l>, _<a_select_n, _<cdr, n>, l> > >
> > >
select_n;

//-----------------------------------------------------------------------------

struct a_remove_n { }; typedef
_<define, a_remove_n, _<lambda, _<n, l>, _<
	cond,
	_<_<zero, n>, _<cdr, l> >,
	_<_<atom, n>, _<cons, _<car, l>, _<a_remove_n, _<dec, n>, _<cdr, l> > > >,
	_<_<null, n>, l>,
	_<_<member, _0, n>,
		_<a_remove_n, _<dec_e, _<remove_m, _0, n> >, _<cdr, l> >
	>,
	_<_else, _<cons, _<car, l>,
		_<a_remove_n, _<dec_e, _<remove_m, _0, n> >, _<cdr, l> >
	> >
> > >
remove_n;

//-----------------------------------------------------------------------------

struct a_insert_ln { }; typedef
_<define, a_insert_ln, _<lambda, _<e, n, l>, _<
	cond,
	_<_<zero, n>, _<cons, e, l> >,
	_<_<atom, n>,
		_<cons, _<car, l>, _<a_insert_ln, e, _<dec, n>, _<cdr, l> > >
	>,
	_<_<null, n>, l>,
	_<_<member, _0, n>, _<cons, e,
		_<cons, _<car, l>,
			_<a_insert_ln, e, _<dec_e, _<remove_m, _0, n> >, _<cdr, l> >
		>
	> >,
	_<_else, _<cons, _<car, l>,
		_<a_insert_ln, e, _<dec_e, _<remove_m, _0, n> >, _<cdr, l> >
	> >
> > >
insert_ln;

//-----------------------------------------------------------------------------

struct a_insert_rn { }; typedef
_<define, a_insert_rn, _<lambda, _<e, n, l>, _<
	cond,
	_<_<zero, n>, _<cons, _<car, l>, _<cons, e, _<cdr, l> > > >,
	_<_<atom, n>,
		_<cons, _<car, l>, _<a_insert_rn, e, _<dec, n>, _<cdr, l> > >
	>,
	_<_<null, n>, l>,
	_<_<member, _0, n>, _<cons, _<car, l>,
		_<cons, e,
			_<a_insert_rn, e, _<dec_e, _<remove_m, _0, n> >, _<cdr, l> >
		>
	> >,
	_<_else, _<cons, _<car, l>,
		_<a_insert_rn, e, _<dec_e, _<remove_m, _0, n> >, _<cdr, l> >
	> >
> > >
insert_rn;

//-----------------------------------------------------------------------------

struct a_subst_n { }; typedef
_<define, a_subst_n, _<lambda, _<e, n, l>, _<
	cond,
	_<_<zero, n>, _<cons, e, _<cdr, l> > >,
	_<_<atom, n>, _<cons, _<car, l>, _<a_subst_n, e, _<dec, n>, _<cdr, l> > > >,
	_<_<null, n>, l>,
	_<_<atom, e>, _<a_subst_n, e, _<car, n>, _<a_subst_n, e, _<cdr, n>, l> > >,
	_<_<null, e>, l>,
	_<_else, _<a_subst_n,
		_<car, e>, _<car, n>,
		_<a_subst_n, _<cdr, e>, _<cdr, n>, l>
	> >
> > >
subst_n;

//-----------------------------------------------------------------------------

struct a_set { }; typedef
_<define, a_set, _<lambda, _<la>, _<
	cond,
	_<_<null, la>, _true>,
	_<_<member, _<car, la>, _<cdr, la> >, _false>,
	_<_else, _<a_set, _<cdr, la> > >
> > >
set;

//-----------------------------------------------------------------------------

struct a_mk_set { }; typedef
_<define, a_mk_set, _<lambda, _<la>, _<
	cond,
	_<_<null, la>, _<> >,
	_<_else, _<cons,
		_<car, la>,
		_<remove_m, _<car, la>, _<a_mk_set, _<cdr, la> > >
	> >
> > >
mk_set;

//-----------------------------------------------------------------------------

struct a_subset { }; typedef
_<define, a_subset, _<lambda, _<s1, s2>, _<
	cond,
	_<_<null, s1>, _true>,
	_<_else, _<_and,
		_<member, _<car, s1>, s2>,
		_<a_subset, _<cdr, s1>, s2>
	> >
> > >
subset;

//-----------------------------------------------------------------------------

struct a_eq_set { }; typedef
_<define, a_eq_set, _<lambda, _<s1, s2>, _<
	_and, _<subset, s1, s2>, _<subset, s2, s1>
> > >
eq_set;

//-----------------------------------------------------------------------------

struct a_intersect { }; typedef
_<define, a_intersect, _<lambda, _<s1, s2>, _<
	cond,
	_<_<null, s1>, _false>,
	_<_else, _<_or,
		_<member, _<car, s1>, s2>,
		_<a_intersect, _<cdr, s1>, s2>
	> >
> > >
intersect;

//-----------------------------------------------------------------------------

struct a_intersection { }; typedef
_<define, a_intersection, _<lambda, _<s1, s2>, _<
	cond,
	_<_<null, s1>, _<> >,
	_<_<member, _<car, s1>, s2>, _<cons,
		_<car, s1>,
		_<a_intersection, _<cdr, s1>, s2>
	> >,
	_<_else, _<a_intersection, _<cdr, s1>, s2> >
> > >
intersection;

//-----------------------------------------------------------------------------

struct a_union { }; typedef
_<define, a_union, _<lambda, _<s1, s2>, _<
	cond,
	_<_<null, s1>, s2>,
	_<_<member, _<car, s1>, s2>, _<a_union, _<cdr, s1>, s2> >,
	_<_else, _<cons,
		_<car, s1>,
		_<a_union, _<cdr, s1>, s2>
	> >
> > >
_union;

//-----------------------------------------------------------------------------

struct a_difference { }; typedef
_<define, a_difference, _<lambda, _<s1, s2>, _<
	cond,
	_<_<null, s1>, _<> >,
	_<_<member, _<car, s1>, s2>, _<a_difference, _<cdr, s1>, s2> >,
	_<_else, _<cons,
		_<car, s1>,
		_<a_difference, _<cdr, s1>, s2>
	> >
> > >
difference;

//-----------------------------------------------------------------------------

struct a_intersection_m { }; typedef
_<define, a_intersection_m, _<lambda, _<ls>, _<
	cond,
	_<_<null, ls>, _<> >,
	_<_<null, _<cdr, ls> >, _<car, ls> >,
	_<_else, _<intersection,
		_<car, ls>,
		_<a_intersection_m, _<cdr, ls> >
	> >
> > >
intersection_m;

//-----------------------------------------------------------------------------

struct a_union_m { }; typedef
_<define, a_union_m, _<lambda, _<ls>, _<
	cond,
	_<_<null, ls>, _<> >,
	_<_else, _<_union,
		_<car, ls>,
		_<a_union_m, _<cdr, ls> >
	> >
> > >
union_m;

//-----------------------------------------------------------------------------

struct a_pair { }; typedef
_<define, a_pair, _<lambda, _<e>, _<
	cond,
	_<_<atom, e>, _false>,
	_<_<null, e>, _false>,
	_<_<null, _<cdr, e> >, _false>,
	_<_<null, _<cdr, _<cdr, e> > >, _true>,
	_<_else, _false>
> > >
pair;

//-----------------------------------------------------------------------------

struct a_mk_pair { }; typedef
_<define, a_mk_pair, _<lambda, _<e1, e2>, _<
	e1, e2
> > >
mk_pair;

//-----------------------------------------------------------------------------

struct a_first { }; typedef
_<define, a_first, _<lambda, _<p>, _<
	car, p
> > >
first;

//-----------------------------------------------------------------------------

struct a_second { }; typedef
_<define, a_second, _<lambda, _<p>, _<
	car, _<cdr, p>
> > >
second;

//-----------------------------------------------------------------------------

struct a_third { }; typedef
_<define, a_third, _<lambda, _<l>, _<
	car, _<cdr, _<cdr, l> >
> > >
third;

//-----------------------------------------------------------------------------

struct a_rev { }; typedef
_<define, a_rev, _<lambda, _<p>, _<
	mk_pair, _<second, p>, _<first, p>
> > >
rev;

//-----------------------------------------------------------------------------

struct a_leftmost { }; typedef
_<define, a_leftmost, _<lambda, _<l>, _<
	cond,
	_<_<atom, _<car, l> >, _<car, l> >,
	_<_else, _<a_leftmost, _<car, l> > >
> > >
leftmost;

//-----------------------------------------------------------------------------

struct a_first_e { }; typedef
_<define, a_first_e, _<lambda, _<l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_else, _<cons,
		_<first, _<car, l> >,
		_<a_first_e, _<cdr, l> >
	> >
> > >
first_e;

//-----------------------------------------------------------------------------

struct a_second_e { }; typedef
_<define, a_second_e, _<lambda, _<l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_else, _<cons,
		_<second, _<car, l> >,
		_<a_second_e, _<cdr, l> >
	> >
> > >
second_e;

//-----------------------------------------------------------------------------

struct a_third_e { }; typedef
_<define, a_third_e, _<lambda, _<l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_else, _<cons,
		_<third, _<car, l> >,
		_<a_third_e, _<cdr, l> >
	> >
> > >
third_e;

//-----------------------------------------------------------------------------

struct a_rev_e { }; typedef
_<define, a_rev_e, _<lambda, _<l>, _<
	cond,
	_<_<null, l>, _<> >,
	_<_else, _<cons,
		_<rev, _<car, l> >,
		_<a_rev_e, _<cdr, l> >
	> >
> > >
rev_e;

//-----------------------------------------------------------------------------

// TODO: should be a set (but a set now is a lat)
struct a_rel { }; typedef
_<define, a_rel, _<lambda, _<l>, _<
	cond,
	_<_<null, l>, _true>,
	_<_else, _<_and,
		_<pair, _<car, l> >,
		_<a_rel, _<cdr, l> >
	> >
> > >
rel;

//-----------------------------------------------------------------------------

struct a_fun { }; typedef
_<define, a_fun, _<lambda, _<r>, _<
	set, _<first_e, r>
> > >
fun;

//-----------------------------------------------------------------------------

struct a_one2one { }; typedef
_<define, a_one2one, _<lambda, _<f>, _<
	set, _<second_e, f>
> > >
one2one;

//-----------------------------------------------------------------------------

struct a_Y { }; typedef
_<define, a_Y, _<lambda, _<f>, _<
	_<lambda, _<g>, _<g, g> >,
	_<lambda, _<g>, _<f, _<lambda, _<x>, _<_<g, g>, x> > > >
> > >
Y;

//-----------------------------------------------------------------------------

template <> char label <a_eq_list>         ::text[] = "eq_list?";
template <> char label <a_equal>           ::text[] = "equal?";
template <> char label <a_eq_c>            ::text[] = "eq_c?";

template <> char label <a_lat>             ::text[] = "lat?";
template <> char label <a_member>          ::text[] = "member?";

template <> char label <a_remove>          ::text[] = "remove";
template <> char label <a_insert_l>        ::text[] = "insert<";
template <> char label <a_insert_r>        ::text[] = "insert>";
template <> char label <a_subst>           ::text[] = "subst";
template <> char label <a_subst2>          ::text[] = "subst2";

template <> char label <a_remove_m>        ::text[] = "remove+";
template <> char label <a_insert_lm>       ::text[] = "insert<+";
template <> char label <a_insert_rm>       ::text[] = "insert>+";
template <> char label <a_subst_m>         ::text[] = "subst+";
template <> char label <a_subst2_m>        ::text[] = "subst2+";

template <> char label <a_member_s>        ::text[] = "member*";

template <> char label <a_remove_s>        ::text[] = "remove*";
template <> char label <a_insert_ls>       ::text[] = "insert<*";
template <> char label <a_insert_rs>       ::text[] = "insert>*";
template <> char label <a_subst_s>         ::text[] = "subst*";
template <> char label <a_subst2_s>        ::text[] = "subst2*";

//-----------------------------------------------------------------------------

template <> char label <a_not>             ::text[] = "not";

template <> char label <a_gt>              ::text[] = "gt?";
template <> char label <a_le>              ::text[] = "le?";
template <> char label <a_ge>              ::text[] = "ge?";
template <> char label <a_eqn>             ::text[] = "eq#?";
template <> char label <a_neqn>            ::text[] = "!eq#?";

template <> char label <a_zero>            ::text[] = "zero?";
template <> char label <a_sign>            ::text[] = "sign";
template <> char label <a_neg>             ::text[] = "neg";
template <> char label <a_min>             ::text[] = "min";
template <> char label <a_max>             ::text[] = "max";
template <> char label <a_abs>             ::text[] = "abs";

template <> char label <a_inc>             ::text[] = "inc";
template <> char label <a_dec>             ::text[] = "dec";
template <> char label <a_inc_t>           ::text[] = "inc!";
template <> char label <a_dec_t>           ::text[] = "dec!";
template <> char label <a_add_t>           ::text[] = "add!";
template <> char label <a_sub_t>           ::text[] = "sub!";
template <> char label <a_quot_t>          ::text[] = "quot!";

template <> char label <a_rem>             ::text[] = "rem";
template <> char label <a_mod>             ::text[] = "mod";
template <> char label <a_div>             ::text[] = "div?";
template <> char label <a_even>            ::text[] = "even?";
template <> char label <a_odd>             ::text[] = "odd?";
template <> char label <a_sgn>             ::text[] = "sgn";

template <> char label <a_gcd>             ::text[] = "gcd";
template <> char label <a_lcm>             ::text[] = "lcm";
template <> char label <a_exp>             ::text[] = "exp";
template <> char label <a_log>             ::text[] = "log";

//-----------------------------------------------------------------------------

template <> char label <a_tup>             ::text[] = "tup?";
template <> char label <a_sum>             ::text[] = "sum";
template <> char label <a_prod>            ::text[] = "prod";
template <> char label <a_min_m>           ::text[] = "min+";
template <> char label <a_max_m>           ::text[] = "max+";

template <> char label <a_inc_e>           ::text[] = "inc:";
template <> char label <a_dec_e>           ::text[] = "dec:";
template <> char label <a_add_e>           ::text[] = "add:";
template <> char label <a_sub_e>           ::text[] = "sub:";
template <> char label <a_sign_e>          ::text[] = "sign:";
template <> char label <a_neg_e>           ::text[] = "neg:";
template <> char label <a_min_e>           ::text[] = "min:";
template <> char label <a_max_e>           ::text[] = "max:";
template <> char label <a_abs_e>           ::text[] = "abs:";

template <> char label <a_mul_e>           ::text[] = "mul:";
template <> char label <a_quot_e>          ::text[] = "quot:";
template <> char label <a_rem_e>           ::text[] = "rem:";
template <> char label <a_mod_e>           ::text[] = "mod:";
template <> char label <a_exp_e>           ::text[] = "exp:";
template <> char label <a_log_e>           ::text[] = "log:";

//-----------------------------------------------------------------------------

template <> char label <a_length>          ::text[] = "length";
template <> char label <a_occur>           ::text[] = "occur";
template <> char label <a_occur_s>         ::text[] = "occur*";

template <> char label <a_select_n>        ::text[] = "select#";
template <> char label <a_remove_n>        ::text[] = "remove#";
template <> char label <a_insert_ln>       ::text[] = "insert<#";
template <> char label <a_insert_rn>       ::text[] = "insert>#";
template <> char label <a_subst_n>         ::text[] = "subst#";

//-----------------------------------------------------------------------------

template <> char label <a_set>             ::text[] = "set?";
template <> char label <a_mk_set>          ::text[] = "mk_set";
template <> char label <a_subset>          ::text[] = "subset?";
template <> char label <a_eq_set>          ::text[] = "eq_set?";
template <> char label <a_intersect>       ::text[] = "intersect?";

template <> char label <a_intersection>    ::text[] = "intersection";
template <> char label <a_union>           ::text[] = "union";
template <> char label <a_difference>      ::text[] = "difference";
template <> char label <a_intersection_m>  ::text[] = "intersection+";
template <> char label <a_union_m>         ::text[] = "union+";

template <> char label <a_pair>            ::text[] = "pair?";
template <> char label <a_mk_pair>         ::text[] = "mk_pair";
template <> char label <a_first>           ::text[] = "first";
template <> char label <a_second>          ::text[] = "second";
template <> char label <a_third>           ::text[] = "third";
template <> char label <a_rev>             ::text[] = "rev";

template <> char label <a_leftmost>        ::text[] = "leftmost";
template <> char label <a_first_e>         ::text[] = "first:";
template <> char label <a_second_e>        ::text[] = "second:";
template <> char label <a_third_e>         ::text[] = "third:";
template <> char label <a_rev_e>           ::text[] = "rev:";

template <> char label <a_rel>             ::text[] = "rel?";
template <> char label <a_fun>             ::text[] = "fun?";
template <> char label <a_one2one>         ::text[] = "one2one?";

template <> char label <a_Y>               ::text[] = "Y";

}  // namespace macro

//-----------------------------------------------------------------------------

// car                          -> cdr, cons, null?
// cdr                          -> car, cons, null?
// cons                         -> car, cdr, null?
// null                         -> zero? atom? car, cdr, cons
// atom                         -> num?, lat? null?, eq?
// eq                           -> equal?, eq_list?, atom?, num?
// cond / _else            TODO -> and, or, not
// lambda                       -> define, Y
// define                  TODO -> lambda, define

//-----------------------------------------------------------------------------

// _and                         -> or, not, cond
// _or                          -> and, not, cond
// num                          -> eq#?, gt?, lt?, zero?, tup? atom?, add, sub, mul
// lt                           -> le?, gt?, eq#?, min, max, num?
// add                          -> add:, add!, inc, sum, sub, neg, mul, num?
// sub                          -> sub:, sub!, dec, add, neg, quot, num?
// mul                          -> mul:, prod, exp, quot, rem, div?, add, num?
// quot                         -> quot:, quot!, rem, mod, div?, mul, sub, num?

//-----------------------------------------------------------------------------

using macro::eq_list;        // -> eq?, equal?
using macro::equal;          // -> eq?, eq#? eq_list, atom?
using macro::eq_c;           // -> TODO

using macro::lat;            // -> atom?, member?, length?, set?, tup?
using macro::member;         // -> member*, occur, remove, subst, remove+, subst+, lat

using macro::remove;         // -> remove+, remove*, remove#, insert<, insert>, subst, member?, lat?
using macro::insert_l;       // -> insert<+, insert<*, insert<#, insert>, remove, subst, member?, lat?
using macro::insert_r;       // -> insert>+, insert>*, insert>#, insert<, remove, subst, member?, lat?
using macro::subst;          // -> subst+, subst*, subst#, subst2, insert<, insert>, remove, member?, lat?
using macro::subst2;         // -> subst2+, subst2*, subst, insert<, insert>, remove, member?, lat?

using macro::remove_m;       // -> remove, remove*, remove#, insert<+, insert>+, subst+, member?, lat?
using macro::insert_lm;      // -> insert<, insert<*, insert<#, insert>+, remove+, subst+, member?, lat?
using macro::insert_rm;      // -> insert>, insert>*, insert>#, insert<+, remove+, subst+, member?, lat?
using macro::subst_m;        // -> subst, subst*, subst#, subst2+, insert<+, insert>+, remove+, member?, lat?
using macro::subst2_m;       // -> subst2, subst2*, subst+, insert<+, insert>+, remove+, member?, lat?

using macro::member_s;       // -> member, occur*, remove*, subst*, lat?

using macro::remove_s;       // -> remove, remove+, remove#, insert<*, insert>*, subst*, member*
using macro::insert_ls;      // -> insert<, insert<+, insert<#, insert>*, remove*, subst*, member*
using macro::insert_rs;      // -> insert>, insert>+, insert>#, insert<*, remove*, subst*, member*
using macro::subst_s;        // -> subst, subst+, subst#, subst2*, insert<*, insert>*, remove*, member*
using macro::subst2_s;       // -> subst2, subst2+, subst*, insert<*, insert>*, remove*, member*

//-----------------------------------------------------------------------------

using macro::_not;      // TODO -> and, or, cond

using macro::p_inf;
using macro::m_inf;

using macro::gt;             // -> ge?, lt?, eq#?, min, max, abs, num?
using macro::le;             // -> lt?, ge?, eq#?, num?
using macro::ge;             // -> gt?, le?, eq#?, num?
using macro::eqn;            // -> eq?, !eq#?, lt?, gt?, le?, ge?, zero?, num?
using macro::neqn;           // -> eq#?, lt?, gt?, num?

using macro::zero;           // -> sign, eq#?, gt?, lt?, div?, num?
using macro::sign;           // -> sign:, zero?, lt?, gt?, neg, num?
using macro::neg;            // -> neg:, sign, abs, sub, add, num?
using macro::min;            // -> min:, min+, max, lt?, gt?, num?
using macro::max;            // -> max:, max+, min, lt?, gt?, abs, num?
using macro::abs;            // -> abs:, max, neg, gt?, lt?, num?

using macro::inc;            // -> inc!, dec, add, sub, num?
using macro::dec;            // -> dec!, inc, sub, add, num?
using macro::inc_t;          // -> inc, dec!, add!, sub!, quot!, num?
using macro::dec_t;          // -> dec, inc!, sub!, add!, quot!, num?
using macro::add_t;          // -> add, sub!, inc!, dec!, quot!, num?
using macro::sub_t;          // -> sub, add!, dec!, inc!, quot!, num?
using macro::quot_t;         // -> quot, inc!, dec!, add!, sub!, num?

using macro::rem;            // -> rem:, mod, quot, gcd, lcm, div?, num?
using macro::mod;            // -> mod:, rem, quot, gcd, lcm, div?, num?
using macro::div;            // -> quot, rem, gcd, lcm, even?, odd?, num?
using macro::even;           // -> odd?, sgn, div?, rem, num?
using macro::odd;            // -> even?, sgn, div?, rem, num?
using macro::sgn;            // -> even, odd, sign, num?

using macro::gcd;            // -> lcm, div?, rem, mod, num?
using macro::lcm;            // -> gcd, div?, rem, mod, num?
using macro::exp;            // -> exp:, log, mul, num?
using macro::log;            // -> log:, exp, quot, num?

//-----------------------------------------------------------------------------

using macro::tup;            // -> num?, lat?, add:, mul:, sum, prod
using macro::sum;            // -> add, add:, prod, tup?
using macro::prod;           // -> mul, mul:, sum, tup?
using macro::min_m;          // -> min:, min, max, tup?
using macro::max_m;          // -> max:, max, min, tup?

using macro::inc_e;          // -> inc, dec:, add:, tup?
using macro::dec_e;          // -> dec, inc:, sub:, tup?
using macro::add_e;          // -> add, sum, inc:, sub:, mul:, tup?
using macro::sub_e;          // -> sub, dec:, neg:, add:, tup?
using macro::sign_e;         // -> sign, neg:, tup?
using macro::neg_e;          // -> neg, sign, abs:, sub:, add:, tup?
using macro::min_e;          // -> min+, min, max:, tup?
using macro::max_e;          // -> max+, max, min:, tup?
using macro::abs_e;          // -> abs, max:, neg:, tup?

using macro::mul_e;          // -> mul, prod, exp:, quot:, rem:, add:, tup?
using macro::quot_e;         // -> quot, rem:, mul:, sub:, tup?
using macro::rem_e;          // -> rem, mod:, quot:, mul:, tup?
using macro::mod_e;          // -> mod, rem:, quot:, mul:, tup?
using macro::exp_e;          // -> exp, log:, mul:, tup?
using macro::log_e;          // -> log, exp:, quot:, tup?

//-----------------------------------------------------------------------------

using macro::length;         // -> select#, occur, lat?
using macro::occur;          // -> occur*, member, length, lat?
using macro::occur_s;        // -> occur, member*, length, lat?

using macro::select_n;       // -> remove#, subst#, insert<#, insert>#, length, lat?
using macro::remove_n;       // -> remove, insert<#, insert>#, subst#, select#, length, lat?
using macro::insert_ln;      // -> insert<, insert>#, remove#, subst#, select#, length, lat?
using macro::insert_rn;      // -> insert>, insert<#, remove#, subst#, select#, length, lat?
using macro::subst_n;        // -> subst, insert<#, insert>#, remove#, select#, length, lat?

//-----------------------------------------------------------------------------

using macro::set;            // -> mk_set, subset?, eq_set?, intersect?, intersection, union, rel?, fun?, lat?
using macro::mk_set;         // -> set?, subset?, eq_set?, intersect?, intersection, union
using macro::subset;         // -> eq_set, intersect?, intersection, union, set?
using macro::eq_set;         // -> subset?, intersect?, intersection, union, set?
using macro::intersect;      // -> intersection, union, difference, subset?, eq_set?, set?

using macro::intersection;   // -> intersection+, intersect?, union, difference, subset?, eq_set?, set?
using macro::_union;         // -> union+, intersection, difference, intersect?, subset?, eq_set?, set?
using macro::difference;     // -> intersection, union, intersect?, subset?, eq_set?, set?
using macro::intersection_m; // -> intersection, union+, intersect?, set?
using macro::union_m;        // -> union, intersection+, set?

using macro::pair;           // -> mk_pair, first, second, rev, rel?, fun?
using macro::mk_pair;        // -> first, second, pair?, rev
using macro::first;          // -> first:, car, leftmost, second, third, pair?, rev
using macro::second;         // -> second:, first, third, pair?, rev
using macro::third;          // -> third:, first, second
using macro::rev;            // -> rev:, first, second, mk_pair, pair?

using macro::leftmost;       // -> first, first:, car
using macro::first_e;        // -> first, leftmost, second:, third+
using macro::second_e;       // -> second, first:, third:
using macro::third_e;        // -> third, first:, second:
using macro::rev_e;          // -> rev, first:, second:

using macro::rel;            // -> fun?, pair?, set?
using macro::fun;            // -> one2one?, rel?, first:, pair?, set?
using macro::one2one;        // -> fun?, rel?, second:, pair?, set?

//-----------------------------------------------------------------------------

using macro::Y;         // TODO -> define, lambda

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_MACRO_HPP
