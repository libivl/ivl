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
		"insert<# - insert expression(s) to the left of given position(s)"
	<< endl;

	cout << endl <<
		syntax << "r = (insert<# e n l)" <<
		body << " returns list r that is list l with expression e inserted to the left of the n-th expression, where n = 0 corresponds to the the first expression. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<hotdogs, _with, mustard, sauerkraut, __and, pickles> l;

		cout << "l = " << l() << endl;
		cout << "(insert<# ketchup 2 l) = " <<
			_<insert_ln, ketchup, _2_, l> () << endl << endl;
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(insert<# rigatoni 3 l) = " << indent++ << endl <<
			_<insert_ln, rigatoni, _3_, l> () << indent-- << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n < 0, if n > L (where L is the length of l), if n is not a number (or tuple), if l is empty or if l is not a list. However, it is defined for n = L, effectively inserting to the right of the last expression:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(insert<# bacon -2 l) = " <<
			_<insert_ln, bacon, _m2_, l> () << endl;

		cout << "(insert<# bacon 5 l) = " <<
			_<insert_ln, bacon, _5_, l> () << endl;

		cout << "(insert<# bacon four l) = " <<
			_<insert_ln, bacon, four, l> () << endl << endl;

		cout << "(insert<# Jack 0 ()) = " <<
			_<insert_ln, Jack, _0_, _<> > () << endl;

		cout << "(insert<# Jack 0 Harry) = " <<
			_<insert_ln, Jack, _0_, Harry> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		syntax << "r = (insert<# e t l)" <<
		body << " returns list r that is list l with expression e inserted to the left of all expressions at positions given by tuple t. The order as well as any multiple occurrences of positions in t are ignored. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<chips, __and, fish, __or, fish, __and, chips> l;

		cout << "l = " << l() << endl;
		cout << "(insert<# salty (0 2) l) = " << indent ++ << endl <<
			_<insert_ln, salty, _<_0_, _2_>, l> () <<
			indent-- << endl << endl;
	}

	{
/*		typedef _<lasagna, spaghetti, ravioli, _<macaroni, meatball> > l;

		cout << "l = " << l() << endl;
		cout << "(insert<# hot (0 0 2 1 0 2) l) = " << indent++ << endl <<
			_<insert_ln, hot, _<_0_, _0_, _2_, _1_, _0_, _2_>, l> () <<
			indent-- << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is l if t is empty:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(insert<# bread () l) = " << _<insert_ln, bread, _<>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Again, the result is not defined if l is empty or if l is not a list. It is also not defined if t is not a tuple or if t contains any expression that is not a number in {0, .. , L}, where L is the length of l:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
/*		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(insert<# ((0 1)) l) = " <<
			_<insert_ln, bread, _<_<_0_, _1_> >, l> () << endl;

		cout << "(insert<# (-2 5 four) l) = " <<
			_<insert_ln, bread, _<_m2_, _5_, four>, l> () << endl;*/
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"insert<# is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <insert_ln>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also insert<, insert>#, remove#, subst#, select#, length, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
