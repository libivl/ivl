/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ temptupe library extending syntax towards mathematical notation.

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
		"tup? - test whether a list is a list of numbers"
	<< endl;

	cout << endl <<
		syntax << "b = (tup? l)" <<
		body << " returns true if and only if list l is a tuple, i.e., a list of numbers, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_2_, _11_, _3_, number <79>, number <47>, _m6_> l;

		cout << "l = " << l() << endl;
		cout << "(tup? l) = " << _<tup, l> () << endl << endl;
	}

	{
		typedef _<_1_, _2_, _8_, apple, _4_, _3_> l;

		cout << "l = " << l() << endl;
		cout << "(tup? l) = " << _<tup, l> () << endl << endl;
	}

	{
		typedef _<_3_, _<_4_, _7_>, number <13>, _9_> l;

		cout << "l = " << l() << endl;
		cout << "(tup? l) = " << _<tup, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list l can also be specified inline, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(tup? ()) = " << _<tup, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is not a list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(tup? Harry) = " << _<tup, Harry> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"tup? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <tup>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also num? lat?, add+."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
