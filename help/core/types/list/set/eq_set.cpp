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
		"eq_set? - test whether two sets are equal"
	<< endl;

	cout << endl <<
		syntax << "b = (eq_set? s1 s2)" <<
		body << " returns true if and only if sets s1, s2 are equal, i.e., they contain exactly the same atoms regardless of order. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_6_, large, chickens, _with, wings> s1;
		typedef _<_6_, chickens, _with, large, wings> s2;

		cout << "s1 = " << s1() << endl;
		cout << "s2 = " << s2() << endl;
		cout << "(eq_set? s1 s2) = " << _<eq_set, s1, s2> () << endl << endl;
	}

	{
		typedef _<_4_, pounds, of, horseradish> s1;
		typedef _<
			four, pounds, chicken,
			__and, _4_, pounds, of, horseradish
		> s2;

		cout << "s1 = " << s1() << endl;
		cout << "s2 = " << s2() << endl;
		cout << "(eq_set? s1 s2) = " << _<eq_set, s1, s2> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"eq_set? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <eq_set>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also subset?, sect?, section, union, set?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
