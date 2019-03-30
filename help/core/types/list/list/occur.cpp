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

	using vocabulary::split;

	cout << wrap << endl << title <<
		"occur - count the occurrences of an atom in a list"
	<< endl;

	cout << endl <<
		syntax << "n = (occur a la)" <<
		body << " returns number n that is the number of occurrences of atom a in list la, where la is assumed to be a list of atoms. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<lamb, chops, __and, mint, flavored, mint, jelly> la;

		cout << "la = " << la() << endl;
		cout << "(occur mint la) = " <<
			_<occur, mint, la> () << endl << endl;
	}

	{
		typedef _<
			banana, split,
			banana, ice, cream,
			lemon, sherbet,
			banana,
			banana, brandy
		> la;

		cout << "la = " << indent++ << endl << la() << indent-- << endl << endl;

		cout << "(occur banana la) = " <<
			_<occur, banana, la> () << endl << endl;
	}

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(occur d la) = " << _<occur, d, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is zero if a is not a member of la or if la is empty:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(occur z la) = " << _<occur, z, la> () << endl << endl;
	}

	{
		cout << "(occur z ()) = " << _<occur, z, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"occur is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <occur>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also occur*, member, length, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
