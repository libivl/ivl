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
		"or - logical disjunction"
	<< endl;

	cout << endl <<
		syntax << "b = (or b1 b2)" <<
		body << " returns true if and only if either b1 or b2 is true, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<> l1;
		typedef _<d, e, f, g> l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(or (null? l1) (atom? l2)) = " <<
			_<_or, _<null, l1>, _<atom, l2> > () << endl << endl;
	}

	{
		typedef _<a, b, c> l1;
		typedef _<> l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(or (null? l1) (null? l2)) = " <<
			_<_or, _<null, l1>, _<null, l2> > () << endl << endl;
	}

	{
		typedef _<a, b, c> l1;
		typedef _<_atom> l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(or (null? l1) (null? l2)) = " <<
			_<_or, _<null, l1>, _<null, l2> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"or is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define_syntax <_or>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also and, not, cond."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
