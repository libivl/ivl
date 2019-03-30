/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ templte library extending syntax towards mathematical notation.

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

#include <ivl/ivl>
#include "../list_begin.hpp"

//-----------------------------------------------------------------------------

int main()
{
	using namespace std;
	using namespace ivl;
	using namespace vocabulary;
	using namespace types::scheme;

	using ivl::types::_;

	cout << wrap << endl << title <<
		"subst# - replace expression(s) in a list at given position(s)"
	<< endl;

	cout << endl <<
		syntax << "r = (subst# e n l)" <<
		body << " returns list r that is list l with the n-th expression replaced by expression e, where n = 0 corresponds to the the first expression. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<hotdogs, _with, mustard, sauerkraut, __and, pickles> l;

		cout << "l = " << l() << endl;
		cout << "(subst# ketchup 2 l) = " <<
			_<subst_n, ketchup, _2_, l> () << endl << endl;
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, macaroni, meatball> l;

		cout << "l = " << l() << endl;
		cout << "(subst# rigatoni 3 l) = " <<
			_<subst_n, rigatoni, _3_, l> () << endl << endl;*/
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(subst# rigatoni 3 l) = " <<
			_<subst_n, rigatoni, _3_, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n < 0, if n >= L (where L is the length of l), if n is not a number (or tuple), if l is empty or if l is not a list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(subst# bacon -2 l) = " <<
			_<subst_n, bacon, _m2_, l> () << endl;

		cout << "(subst# bacon 5 l) = " <<
			_<subst_n, bacon, _5_, l> () << endl;

		cout << "(subst# bacon four l) = " <<
			_<subst_n, bacon, four, l> () << endl << endl;

		cout << "(subst# Jack 0 ()) = " <<
			_<subst_n, Jack, _0_, _<> > () << endl;

		cout << "(subst# Jack 0 Harry) = " <<
			_<subst_n, Jack, _0_, Harry> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << endl <<
		syntax << "r = (subst# a p l)" <<
		body << " returns list r that is list l with expressions at positions given by list p each replaced by atom a. The order as well as any multiple occurrences of positions in p are ignored. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<hotdogs, _with, mustard, sauerkraut, __and, pickles> l;

		cout << "l = " << l() << endl;
		cout << "(subst# meat (0 1 3) l) = " <<
			_<subst_n, meat, _<_0_, _1_, _3_>, l> () << endl << endl;
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(subst# plum (0 0 2 1 0 2) l) = " <<
			_<subst_n, plum, _<_0_, _0_, _2_, _1_, _0_, _2_>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If p contains nested lists, its structure is ignored:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(subst# plum (0 (0 2) (1 (0)) ((2))) l) = " <<
			_<subst_n, plum, _<_0_, _<_0_, _2_>, _<_1_, _<_0_> >, _<_<_2_> > >, l> () <<
			endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is l if p is empty:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(subst# bread () l) = " << _<subst_n, bread, _<>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Again, the result is not defined if l is empty or if l is not a list. It is also not defined if p contains any expression that is not a number in {0, .. , L-1}, where L is the length of l:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(subst# bread (-2 5 four) l) = " <<
			_<subst_n, bread, _<_m2_, _5_, four>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << endl <<
		syntax << "r = (subst# s t l)" <<
		body << " returns list r that is list l with expressions at positions given by tuple t replaced expressions in list s. The expression at position pn, where pn is the n-th number in t, is replaced by the n-th expression in s for each n:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<lasagna, spaghetti, ravioli, macaroni, meatball> l;
		typedef _<pear, plum, peach> _new;

		cout << "l = " << l() << endl;
		cout << "(subst# (pear plum peach) (3 1 4) l) = " <<
			_<subst_n, _<pear, plum, peach>, _<_3_, _1_, _4_>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is l if t or s is empty. If s is longer than t, the remaining expressions in s are discarded. It it is shorter, the expressions in l at positions given by the remaining numbers in t are unaffected."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(subst# (bread) () l) = " <<
			_<subst_n, _<bread>, _<>, l> () << endl;

		cout << "(subst# (mozzarella bread) (2) l) = " <<
			_<subst_n, _<mozzarella, bread>, _<_2_>, l> () << endl;

		cout << "(subst# (mozzarella) (2 0 1) l) = " <<
			_<subst_n, _<mozzarella>, _<_2_, _0_, _1_>, l> () << endl;

		cout << "(subst# () (2 0 1) l) = " <<
			_<subst_n, _<>, _<_2_, _0_, _1_>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined in the same cases as for the previous syntax. If t is not a tuple the result is still defined but may be unpredicted:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(subst# (pear plum peach) (0 (0 2) (1 (0)) ((2))) l) = " <<
			indent++ << endl << _<subst_n, _<pear, plum, peach>,
				_<_0_, _<_0_, _2_>, _<_1_, _<_0_> >, _<_<_2_> > >,
			l> () << indent-- << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"subst# is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <subst_n>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also subst, insert<#, insert>#, remove#, select#, length, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
