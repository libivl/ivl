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
		"section - intersection of two sets"
	<< endl;

	cout << endl <<
		syntax << "s = (section s1 s2)" <<
		body << " returns set s that is the intersection of sets s1, s2, i.e., the set of atoms that are both in s1 and s2, in the same order as in s1. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<stewed, tomatoes, __and, macaroni> s1;
		typedef _<macaroni, __and, cheese> s2;

		cout << "s1 = " << s1() << endl;
		cout << "s2 = " << s2() << endl;
		cout << "(section s1 s2) = " << _<section, s1, s2> () << endl << endl;
	}

	{
		typedef _<stewed, tomatoes, _with, rigatoni> s1;
		typedef _<macaroni, __and, cheese> s2;

		cout << "s1 = " << s1() << endl;
		cout << "s2 = " << s2() << endl;
		cout << "(section s1 s2) = " << _<section, s1, s2> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"section is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <section>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also section+, sect?, union, diff, subset?, eq_set?, set?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
