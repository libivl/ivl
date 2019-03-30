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
		"cdr - remove first item from non-empty list"
	<< endl;

	cout << endl <<
		syntax << "r = (cdr l)" << body
		<< " returns list r that is l with the first item removed, where l is a non-empty list. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, b, c> l;

		cout << "l = " << l() << endl;
		cout << "(cdr l) = " << _<cdr, l> () << endl << endl;
	}

	{
		typedef _<_<a, b, c>, x, y, z> l;

		cout << "l = " << l() << endl;
		cout << "(cdr l) = " << _<cdr, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list l can also be specified inline, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(cdr (hamburger)) = " << _<cdr, _<hamburger> > () << endl;
		cout << "(cdr ((x) t r)) = " << _<cdr, _<_<x>, t, r> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is empty or if l is not a list. This property guarantees that recursive application of cdr eventually terminates:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(cdr ()) = " << _<cdr, _<> > () << endl;
		cout << "(cdr hotdogs) = " << _<cdr, hotdogs> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Primitives car and cdr may be combined to obtain any item or part of a list, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<b>, _<x, y>, _<_<c> > > l;

		cout << "l = " << l() << endl;
		cout << "(car (cdr l)) = " << _<car, _<cdr, l> > () << endl;
		cout << "(cdr (cdr l)) = " << _<cdr, _<cdr, l> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also car, cons, null?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
