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
		"length - length of a list"
	<< endl;

	cout << endl <<
		syntax << "n = (length l)" <<
		body << " returns number n that is the length of list l, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<hotdogs, _with, mustard, sauerkraut, __and, pickles> l;

		cout << "l = " << l() << endl;
		cout << "(length l) = " << _<length, l> () << endl << endl;
	}

	{
		typedef _<ham, __and, cheese, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(length l) = " << _<length, l> () << endl << endl;
	}

	{
		typedef _<ham, _<__and, cheese>, on, rye> l;

		cout << "l = " << l() << endl;
		cout << "(length l) = " << _<length, l> () << endl << endl;
	}

	{
		cout << "(length ()) = " << _<length, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is not a list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(length Harry) = " << _<length, Harry> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"length is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <length>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also select#, occur, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
