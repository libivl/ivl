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
		"rel? - test whether a list is a relation"
	<< endl;

	cout << endl <<
		syntax << "b = (rel? l)" <<
		body << " returns true if and only if list l is a relation, i.e., a set of pairs. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<apples, peaches, pumpkin, pie> l;

		cout << "l = " << l() << endl;
		cout << "(rel? l) = " << _<rel, l> () << endl << endl;
	}

	{
		typedef _<
			_<apples, peaches>,
			_<pumpkin, pie>,
			_<apples, peaches>
		> l;

		cout << "l = " << l() << endl;
		cout << "(rel? l) = " << _<rel, l> () << endl << endl;
	}

	{
		typedef _<
			_<apples, peaches>,
			_<pumpkin, pie>
		> l;

		cout << "l = " << l() << endl;
		cout << "(rel? l) = " << _<rel, l> () << endl << endl;
	}

	{
		typedef _<
			_<_4_, _3_>,
			_<_4_, _2_>,
			_<_7_, _6_>,
			_<_6_, _2_>,
			_<_3_, _4_>
		> l;

		cout << "l = " << l() << endl;
		cout << "(rel? l) = " << _<rel, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The empty list is always a relation:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(rel? ()) = " << _<rel, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"rel? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <rel>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also func?, pair?, set?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
