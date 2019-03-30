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
		"subset? - test whether a set is subset of another"
	<< endl;

	cout << endl <<
		syntax << "b = (subset? s1 s2)" <<
		body << " returns true if and only if set s1 is a subset of set s2, i.e., every atom in s1 is also in s2. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_5_, chicken, wings> s1;
		typedef _<
			_5_, hamburgers,
			_2_, pieces, fried, chicken,
			__and, light, duckling, wings
		> s2;

		cout << "s1 = " << s1() << endl;
		cout << "s2 = " << s2() << endl;
		cout << "(subset? s1 s2) = " << _<subset, s1, s2> () << endl << endl;
	}

	{
		typedef _<_4_, pounds, of, horseradish> s1;
		typedef _<
			four, pounds, chicken,
			__and, _5_, ounces, horseradish
		> s2;

		cout << "s1 = " << s1() << endl;
		cout << "s2 = " << s2() << endl;
		cout << "(subset? s1 s2) = " << _<subset, s1, s2> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"subset? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <subset>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also eq_set, sect?, section, union, set?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
