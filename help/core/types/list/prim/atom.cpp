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
		"atom? - test whether an expression is an atom"
	<< endl;

	cout << endl <<
		syntax << "b = (atom? e)" <<
		body << " returns true if expression e is an atom, and false if it is a list (empty or not). E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

		cout << "(atom? Harry) = " << _<atom, Harry> () << endl << endl;

		typedef _<Harry, had, a, heap, of, apples> l;

		cout << "l = " << l() << endl;
		cout << "(atom? l) = " << _<atom, l> () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Primitive atom? may be combined with car and cdr to find out whether any item of a list is an atom or another list. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(atom? (car l)) = " << _<atom, _<car, l> > () << endl;

		cout << "(atom? (cdr l)) = " <<
			_<atom, _<cdr, l> > () << endl << endl;

		cout << "(atom? (cdr (Harry))) = " <<
			_<atom, _<cdr, _<Harry> > > () << endl << endl;
	}

	{
		typedef _<swing, low, sweet, cherry, oat> l;

		cout << "l = " << l() << endl;
		cout << "(atom? (car (cdr l))) = " <<
			_<atom, _<car, _<cdr, l> > > () << endl << endl;
	}

	{
		typedef _<swing, _<low, sweet>, cherry, oat> l;

		cout << "l = " << l() << endl;
		cout << "(atom (car (cdr l))) = " <<
			_<atom, _<car, _<cdr, l> > > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also num?, lat? null?, eq?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
