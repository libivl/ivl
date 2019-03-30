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
		"first: - first item of each nested list"
	<< endl;

	cout << endl <<
		syntax << "r = (first: l)" <<
		body << " returns a list r of the first item of each nested list or pair in list l, where l is assumed to be a list of lists. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<
			_<apple, peach, pumpkin>,
			_<plum, pear, cherry>,
			_<grape, raisin, pea>,
			_<bean, carrot, eggplant>
		> l;

		cout << "l = " << indent++ << endl << l() << endl << indent-- << endl;
		cout << "(first: l) = " << _<first_e, l> () << endl << endl;
	}

	{
		typedef _<_<a, b, c>, _<d, e, f>, _<g, h, i> > l;

		cout << "l = " << l() << endl;
		cout << "(first: l) = " << _<first_e, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If l is empty, an empty list is returned instead, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(first: ()) = " << _<first_e, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The first item of each nested list or pair may be a list itself, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<
			_<five, red, plums>,
			_<eleven, green, oranges>
		> l;

		cout << "l = " << l() << endl;
		cout << "(first: l) = " << _<first_e, l> () << endl << endl;
	}

	{
		typedef _<
			_<_<five>, _<red>, _<plums> >,
			_<_<eleven>, _<green>, _<oranges> >
		> l;

		cout << "l = " << l() << endl;
		cout << "(first: l) = " << _<first_e, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"first: is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <first_e>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also first, leftmost, second:, third:."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
