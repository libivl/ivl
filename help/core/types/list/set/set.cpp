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
		"set? - test whether a list of atoms is a set"
	<< endl;

	cout << endl <<
		syntax << "b = (set? la)" <<
		body << " returns true if and only if list of atoms la is a set, i.e., no atom in la occurs more than once. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<apple, peaches, apple, plum> la;

		cout << "la = " << la() << endl;
		cout << "(set? la) = " << _<set, la> () << endl << endl;
	}

	{
		typedef _<apples, peaches, pears, plums> la;

		cout << "la = " << la() << endl;
		cout << "(set? la) = " << _<set, la> () << endl << endl;
	}

	{
		typedef _<apple, _3_, pear, _4_, _9_, apple, _3_, _4_> la;

		cout << "la = " << la() << endl;
		cout << "(set? la) = " << _<set, la> () << endl;
	}

//-----------------------------------------------------------------------------

	// TODO: The result IS defined
	cout << !indent << body << endl <<
		"The the result is not defined if la is not a list of atoms:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<apple, _3_>, _<pear, _4_, _9_>, _<apple, _3_, _4_> > la;

		cout << "la = " << la() << endl;
		cout << "(set? la) = " << _<set, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The empty list is always a set:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(set? ()) = " << _<set, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"set? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <set>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also mk_set, subset?, eq_set?, sect?, section, union, rel?, func?, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
