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
#include "list_begin.hpp"

//-----------------------------------------------------------------------------

int main()
{
	using namespace std;
	using namespace ivl;
	using namespace vocabulary;
	using namespace types;
	using ivl::types::_;
	using ivl::types::eq;

	cout << wrap << endl << title <<
		"tev - evaluate template type by substututing arguments"
	<< endl;

	cout << endl <<
		syntax << "e = (tev t l)" <<
		body << " returns template type e that has all the occurences of args<N> (e.g. __1, __2, ...) in the template type t replaced by the N-th item of list l."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef array<__1> t;

		cout << "t = array<__1>" << endl;

		typedef _<tev, t, _<double> > e;

		cout << "e = (tev, array<__1>, (double)) = array<double>" << endl;

		cout << !indent << body << endl <<
		"The following lines prove the above test."
	<< endl << indent << sample << endl;
		
		cout << "(eq t array<__1>) = " << _<eq, t, array<__1> >() << endl << endl;
		cout << "(eq e array<__1>) = " << _<eq, e, array<__1> >() << endl;
		cout << "(eq e array<double>) = " << _<eq, e, array<double> >() << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list l can not [yet] be specified inline."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is replaced by not defined types if l has less arguments than t:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<tev, array<__1>, _<> > e;
		cout << "e = (tev array<_1> ())" << endl;
		cout << "(eq (e array<nat>) = " << _<eq, e, array<nat> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also match."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "list_end.hpp"
