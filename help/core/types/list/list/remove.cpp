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
	using ivl::types::scheme::remove;

	cout << wrap << endl << title <<
		"remove - remove a member of a list of atoms"
	<< endl;

	cout << endl <<
		syntax << "r = (remove a la)" <<
		body << " returns a list r that is list la with the first occurrence of atom a removed, where la is assumed to be a list of atoms. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<lamb, chops, __and, mint, jelly> la;

		cout << "la = " << la() << endl;
		cout << "(remove mint la) = " << _<remove, mint, la> () << endl << endl;
	}

	{
		typedef _<lamb, chops, __and, mint, flavored, mint, jelly> la;

		cout << "la = " << la() << endl;
		cout << "(remove mint la) = " << _<remove, mint, la> () << endl << endl;
	}

	{
		typedef _<coffee, cup, tea, cup, __and, hick, cup> la;

		cout << "la = " << la() << endl;
		cout << "(remove cup la) = " << _<remove, cup, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list la can also be specified inline, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(remove sauce (soy sauce and tomato sauce)) = " <<
			_<remove, sauce, _<soy, sauce, __and, tomato, sauce> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If a is not a member of la, then la is returned instead:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<bacon, lettuce, __and, tomato> la;

		cout << "la = " << la() << endl;
		cout << "(remove toast la) = " << _<remove, toast, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If la is empty, an empty list is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(remove toast ()) = " << _<remove, toast, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"remove is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <remove>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also remove+, remove*, remove#, insert<, insert>, subst, member?, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
