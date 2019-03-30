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
		"member? - test whether an atom occurs in a list of atoms"
	<< endl;

	cout << endl <<
		syntax << "b = (member? a la)" <<
		body << " returns true if and only if atom a occurs in list of atoms la, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<coffee, tea, __or, milk> la;

		cout << "la = " << la() << endl;
		cout << "(member? tea la) = " <<
			_<member, tea, la> () << endl << endl;
	}

	{
		typedef _<fried, eggs, __and, scrambled, eggs> la;

		cout << "la = " << la() << endl;
		cout << "(member? poached la) = " <<
			_<member, poached, la> () << endl << endl;
	}

	{
		typedef _<mashed, potatoes, __and, meat, gravy> la;

		cout << "la = " << la() << endl;
		cout << "(member? meat la) = " <<
			_<member, meat, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list la can also be specified inline, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(member? liver (bagels and lox)) = " <<
			_<member, liver, _<bagels, __and, lox> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"member? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <member>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also member*, occur, remove, subst, remove+, subst+, lat."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
