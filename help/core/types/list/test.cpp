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
   and a copy of the GNU Lesser General Public License alongb, c,
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#include <ivl/ivl>
#include "list_begin.hpp"

//-----------------------------------------------------------------------------

int main()
{
	using namespace std;
	using namespace ivl;
	using namespace vocabulary;
	using namespace types::scheme;

	using ivl::types::_;
	using ivl::types::scheme::cond;
	using ivl::types::scheme::dot;
	using ivl::types::scheme::eq;
	using ivl::types::scheme::fun;
	using ivl::types::scheme::is;

//-----------------------------------------------------------------------------

	cout << sample << endl;

//-----------------------------------------------------------------------------

// 	{
// 		typedef
// 		_<lambda, _<l>, _<
// 			cond,
// 			_<_<null, l>, _true>,
// 			_<_<atom, _<car, l> >, _<milk, _<cdr, l> > >,
// 			_<_else, _false>
// 		> >
// 		lat;
//
// 		cout << "lat = " << lat() << endl << endl;
//
//  		cout << "(lat Harry) = " << _<lat, Harry> () << endl;
//  		cout << "(lat ()) = " << _<lat, _<> > () << endl;
// 		cout << "(lat (a b c)) = " << _<lat, _<a, b, c> > () << endl;
// 		cout << "(lat ((a) b c)) = " << _<lat, _<_<a>, b, c> > () << endl << endl;
// 	}

// 	{
// 		cout << _<car, _<a, b, c, d> > () << endl;
// 		cout << _<car, _<_<a, z>, b, c, d> > () << endl;
// 		cout << _<car, _<a> > () << endl;
// 		cout << _<car, _<_<a> > > () << endl;
// 		cout << _<car, _<_<_<a, x, y, z> > > > () << endl;
// 		cout << _<car, _<> > () << endl;
// 		cout << _<car, a> () << endl << endl;
//
// 		cout << _<cdr, _<a, b, c, d> > () << endl;
// 		cout << _<cdr, _<_<a, z>, b, c, d> > () << endl;
// 		cout << _<cdr, _<a> > () << endl;
// 		cout << _<cdr, _<_<a> > > () << endl;
// 		cout << _<cdr, _<_<_<a, x, y, z> > > > () << endl;
// 		cout << _<cdr, _<> > () << endl;
// 		cout << _<cdr, a> () << endl << endl;
//
// 		cout << _<cons, a, _<b, c, d> > () << endl;
// 		cout << _<cons, _<a, z>, _<b, c, d> > () << endl;
// 		cout << _<cons, a, _<> > () << endl;
// 		cout << _<cons, _<a>, _<> > () << endl;
// 		cout << _<cons, _<_<a, x, y, z> >, _<> > () << endl;
// 		cout << _<cons, a, b> () << endl << endl;
// 	}

	{
		cout << _<let,
			_<>,
			_<a, _<x, b>, y, c, x, _<d, z> >
		> () << endl;

		cout << _<let,
			_<_<x, p>, _<y, q>, _<z, r> >,
			_<a, _<x, b>, y, c, x, _<d, z> >
		> () << endl;

		cout << _<let,
			_<_<x, _<u, v, w> >, _<y, _<p, q, r> >, _<z, _<f, g, h> > >,
			_<a, _<x, b>, y, c, x, _<d, z> >
		> () << endl;
	}

// 	{
// 		typedef syntax_rules rules;
//
// 		cout << define <_if> () << endl << endl;
// 		cout << define <_and> () << endl << endl;
//
// 		cout << _<rules, _<_<>, _<> > > () << endl << endl;
// 		cout << _<rules, _<_<>, b> > () << endl << endl;
// 		cout << _<rules, _<_<>, _<a, b> > > () << endl << endl;
// 		cout << _<rules, _<_<>, _<a, b>, c, _<d, e, f> > > () << endl << endl;
//
// 		cout << _<lambda, _<>, _<> > () << endl << endl;
// 		cout << _<lambda, _<>, b> () << endl << endl;
// 		cout << _<lambda, _<>, _<a, b> > () << endl << endl;
// 		cout << _<lambda, _<>, _<a, b>, c, _<a, b>, _<d, e, f> > () << endl << endl;
// 	}

// 	{
// 		typedef _<lambda, _<x>, _<cdr, x> > l;
//
// 		cout << l::map <_<a, b, c> > () << endl;
// 	}

// 	{
// 		typedef _<let_rec, _<_<a1, v1>, _<a2, v2>, _<a3, v3> >, b1, b2, b3> l;
//
// 		cout << "let_rec = " << endl << indent++ << endl <<
// 			define_syntax <let_rec> () << endl << indent-- << endl;
//
// 		cout << "(let_rec ((a1 v1) (a2 v2) (a3 v3)) b1 b2 b3) = " <<
// 			endl << indent++ << endl <<
// 			l () << endl << indent-- << endl;
// 	}

// 	{
// 		typedef _<lambda, _<x>, _<add, _<mul, a, x>, b> > F;
//
// 		typedef _<lambda, _<y>,
// 			_<let, _<>,
// 				_<set_b, a, _3_>,
// 				_<set_b, b, _2_>
// 			>,
// 			_<F, y>
// 		> SF;
//
// 		cout << _<SF, _5_> () << endl;
// 		cout << _<let, _<_<a, _4_>, _<b, _3_> >, _<SF, _5_> > () << endl << endl;
// 	}

// 	{
// 		typedef
// 		_<lambda, _<l>, _<
// 			cond,
// 			_<_<null, l>, _0_>,
// 			_<_else, _<inc, _<h, _<cdr, l> > > >
// 		> >
// 		L;
//
// 	// 		typedef
// 	// 		_<let, _<_<h, _0_> >,
// 	// 			_<let, _<_<f, L> >,
// 	// 				_<set_b, h, f>
// 	// 			>,
// 	// 			h
// 	// 		>
// 	// 		len;
//
// 		typedef
// 		_<letrec, _<_<h, L> >,
// 			h
// 		>
// 		len;
//
// 		cout << len () << endl;
// 		cout << _<len, _<> > () << endl;
// 		cout << _<len, _<a> > () << endl;
// 		cout << _<len, _<a, b> > () << endl;
// 		cout << _<len, _<a, b, c> > () << endl;
// 		cout << _<len, _<_<a>, _<b, b>, _<c, c, c> > > () << endl;
// 		cout << _<len, _<a, b, c, d, e, f, g, h, i, j, k> > () << endl;
// 	}

// 	{
// 		cout << _<_and> () << endl;
//
// 		cout << _<_and, _true> () << endl;
// 		cout << _<_and, _false> () << endl;
//
// 		cout << _<_and, _true, _true> () << endl;
// 		cout << _<_and, _true, _false> () << endl;
// 		cout << _<_and, _false, _true> () << endl;
// 		cout << _<_and, _false, _false> () << endl;
//
// 		cout << _<_and, _true, _true, _true> () << endl;
// 		cout << _<_and, _true, _true, _false> () << endl;
// 		cout << _<_and, _true, _false, _true> () << endl;
// 		cout << _<_and, _true, _false, _false> () << endl;
// 		cout << _<_and, _false, _true, _true> () << endl;
// 		cout << _<_and, _false, _true, _false> () << endl;
// 		cout << _<_and, _false, _false, _true> () << endl;
// 		cout << _<_and, _false, _false, _false> () << endl;
// 	}

// 	{
//  		cout << define <scheme::car> () << endl;
//  		cout << define <scheme::cdr> () << endl;
//  		cout << define <scheme::cons> () << endl;
//  		cout << define <scheme::null> () << endl;
//  		cout << define <scheme::atom> () << endl;
//  		cout << define <scheme::eq> () << endl;
// 	}

// 	{
// 		typedef
// 		_<function,
// 			_<_<_<hash, n> >, _<inc, n> >
// 		>
// 		f;
//
// 		cout << f () << endl;
// 		cout << _<f, _1_> () << endl;
//
// 		cout << define <num> () << endl;
// 		cout << _<num, _2_> () << endl;
// 		cout << _<num, a> () << endl;
// 		cout << _<num, _<a> > () << endl;
// 	}

// 	{
// 		cout << list_details::nat <op2 <t_quot> > () << endl;
// 	}

// 	{
// 		typedef _<fn, _<>, _3_> f;
// 		typedef _<fn, _<>, f> g;
//
// 		cout << f () << endl;
// 		cout << g () << endl;
// 		cout << _<f> () << endl;
// 		cout << _<g> () << endl;
// 		cout << _<_<f> > () << endl;
// 		cout << _<_<g> > () << endl;
//
// 		cout << endl;
//
// 		cout << _<f, a, b> () << endl;
// 		cout << _<g, a, b> () << endl;
// 		cout << _<_<f>, a, b> () << endl;
// 		cout << _<_<g>, a, b> () << endl;
// 		cout << _<_<_<f> >, a, b> () << endl;
// 		cout << _<_<_<g> >, a, b> () << endl;
// 		cout << _<_<_<_<f> > >, a, b> () << endl;
// 		cout << _<_<_<_<g> > >, a, b> () << endl;
//
// 		cout << endl;
// 	}

// 	{
// 		typedef _<let_rec, _<_<f, _<fn, _<>, f> > >, f> f;
//
// 		cout << f () << endl;
// 		cout << _<f> () << endl;
// 		cout << _<_<f> > () << endl;
// 		cout << _<_<_<f> > > () << endl;
//
// 		cout << endl;
//
// 		cout << _<f, a> () << endl;
// 		cout << _<_<f>, a> () << endl;
// 		cout << _<_<_<f> >, a> () << endl;
// 	}

// 	{
// 		cout << _<pif, _true> () << endl;
// 		cout << _<pif, _false> () << endl;
// 		cout << _<pif, _true, t, e> () << endl;
// 		cout << _<pif, _false, t, e> () << endl;
// 		cout << _<_<pif, _true>, t, e> () << endl;
// 		cout << _<_<pif, _false>, t, e> () << endl;
// 	}

// 	{
// 		typedef _<macro, _<_<_<c, ___, etc> >, c> > kar;
//
// 		cout << kar () << endl;
// 		cout << _<kar, _<a, b, c> > () << endl;
// 	}

// 	{
// 		typedef
// 		_<cases, _<>, _<_<_<c, ___, etc> >, c> >
// 		kar;
//
// 		typedef
// 		_<partial, _<cases, _<>, _<_<_<c, ___, etc> >, c> > >
// 		par;
//
// 		typedef
// 		_<lambda, _<a, l>, _<_<kar, l>, l> >
// 		k;
//
// 		typedef
// 		_<lambda, _<a, l>, _<_<par, l>, l> >
// 		p;
//
// 		cout << _<k, z, _<a, z> > () << endl;
// 		cout << _<p, z, _<a, z> > () << endl;
// 	}

// 	{
// 		typedef
// 		_<let,
// 			_<_<a, _<b, c, d> >, _<_<f, x>, _<lat, x> > >,
// 			_<a, _<f, _<_<b>, c> > >
// 		> test;
//
// 		cout << test () << endl << endl;
//
// 		typedef _<lambda, _<x>, _<s, x> > L;
//
// 		cout << _<let, _<_<s, L> >, s > () << endl << endl;
// 		cout << _<let_rec, _<_<s, L> >, s> () << endl << endl;
// 	}

// 	{
// 		typedef
//  		_<fun, _<_<_<c, scheme::dot, d> >, _<d, c> > >
// 		f1;
//
// 		typedef
// 		_<fun, _<_<_<_<c, scheme::dot, d>, as, l> >, _<d, _<c, dot, l> > > >
// 		f2;
//
// 		typedef
// 		_<macro, _<_<_<_<c, scheme::dot, d>, as, l> >, _<d, _<c, dot, l> > > >
// 		f3;
//
// 		typedef
// 		_<fun, _<_<x, y>, _<y, x> > >
// 		f4;
//
// 		cout << _<f1, _<a, b, c> > () << endl << endl;
// 		cout << _<f2, _<a, b, c> > () << endl << endl;
// 		cout << _<f3, _<a, b, c> > () << endl << endl;
// 		cout << _<f4, a, b, c> () << endl << endl;
// 	}

// 	{
// 		typedef _<partial, _<rules, _<>, _<_<___, _<p, q>, y>, _<y, _<q, p> > > > > r;
// 
// 		cout << _<r, _<car, _<_<y, z>, b, c> >, b, c, d> () << endl << endl;
// 
// 		typedef
// 		_<be_rec, a, _<lambda, _<x>, _<a, x> >, _<_0_, a> >
// 		s;
// 
// 		typedef
// 		_<let_rec,
// 			_<
// 				_<a, _<lambda, _<x>, _<b, x> > >,
// 				_<b, _<lambda, _<x>, _<a, _<b, x> > > >
// 			>,
// 			a
// 		>
// 		m;
// 
// 		cout << s () << endl << endl;
// 		cout << m () << endl << endl;
// 	}

// 	{
// 		typedef _<fun, _<x, y>, _<x, _<y, y> > > f;
// 		typedef _<pac, _<i, j>, _<f, j, i> > g;
// 		typedef _<pac, _<a, b>, _<g, a, _<b, b> > > h;
// 		typedef _<pac, _<a, b>, _<f, _<b, b>, a> > h1;
//
// 		cout << _<f, u, v, w, x> () << endl;
// 		cout << _<g, u, v, w, x> () << endl;
// 		cout << _<h, u, v, w, x> () << endl;
// 		cout << _<h1, u, v, w, x> () << endl;
// 	}

//-----------------------------------------------------------------------------

	cout << body << endl;

}

//-----------------------------------------------------------------------------

#include "list_end.hpp"
