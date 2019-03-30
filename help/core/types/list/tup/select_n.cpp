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
		"select# - select expression(s) of a list at given position(s)"
	<< endl;

	cout << endl <<
		syntax << "e = (select# n l)" <<
		body << " returns the n-th expression of list l, where n is a number and n = 0 corresponds to the the first one. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<hotdogs, _with, mustard, sauerkraut, __and, pickles> l;

		cout << "l = " << l() << endl;
		cout << "(select# 2 l) = " << _<select_n, _2_, l> () << endl << endl;
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, macaroni, meatball> l;

		cout << "l = " << l() << endl;
		cout << "(select# 3 l) = " << _<select_n, _3_, l> () << endl << endl;*/
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(select# 3 l) = " << _<select_n, _3_, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n < 0, if n >= L (where L is the length of l), if n is not a number (or list), if l is empty or if l is not a list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(select# -2 l) = " << _<select_n, _m2_, l> () << endl;
		cout << "(select# 5 l) = " << _<select_n, _5_, l> () << endl;
		cout << "(select# four l) = " << _<select_n, four, l> () << endl << endl;

		cout << "(select# 0 ()) = " << _<select_n, _0_, _<> > () << endl;
		cout << "(select# 0 Harry) = " << _<select_n, _0_, Harry> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		syntax << "r = (select# p l)" <<
		body << " returns list r that contains the expressions of list l at positions given by list p. The order of expressions in r may differ from their order in l if positions in p are not in ascending order. An expression may occur more than once in r if its position occurs more than once in p. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<hotdogs, _with, mustard, sauerkraut, __and, pickles> l;

		cout << "l = " << l() << endl;
		cout << "(select# (0 1 3) l) = " <<
			_<select_n, _<_0_, _1_, _3_>, l> () << endl << endl;
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, macaroni, meatball> l;

		cout << "l = " << l() << endl;
		cout << "(select# (3 1 4) l) = " <<
			_<select_n, _<_3_, _1_, _4_>, l> () << endl << endl;*/
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(select# (3 0 0 2 1 0 2) l) = " << indent++ << endl <<
			_<select_n, _<_3_, _0_, _0_, _2_, _1_, _0_, _2_>, l> () <<
			indent-- << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"p may contain nested lists, in which case r contains nested lists of expressions in l, following the structure of p:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(select# (3 0 (0 2) (1 (0)) ((2))) l) = " << indent++ << endl <<
			_<select_n, _<_3_, _0_, _<_0_, _2_>, _<_1_, _<_0_> >, _<_<_2_> > >, l> () <<
			indent-- << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is an empty list if p is empty:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(select# () l) = " << _<select_n, _<>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Again, the result is not defined if l is empty or if l is not a list. It is also not defined if p contains any atom that is not a number in {0, .. , L-1}, where L is the length of l:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(select# (-2 5 four) l) = " <<
			_<select_n, _<_m2_, _5_, four>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"select# is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <select_n>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also remove#, subst#, insert<#, insert>#, length, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
