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
	using ivl::types::scheme::lcm;

	cout << wrap << endl << title <<
		"lcm - least common multiple"
	<< endl;

	cout << endl <<
		syntax << "d = (lcm n1 n2)" <<
		body << " returns number d that is the least common multiple of numbers n1, n2. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(lcm 10 4) = " << _<lcm, _10_, _4_> () << endl;
		cout << "(lcm 21 6) = " << _<lcm, number <21>, _6_> () << endl;
		cout << "(lcm 48 18) = " << _<lcm, number <48>, _18_> () << endl;
		cout << "(lcm 0 7) = " << _<lcm, _0_, _7_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is nonnegative regardless of the signs of n1, n2:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(lcm 48 -18) = " << _<lcm, number <48>, _m18_> () << endl;
		cout << "(lcm -48 -18) = " << _<lcm, number <-48>, _m18_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(lcm 1 Harry) = " << _<lcm, _1_, Harry> () << endl;
		cout << "(lcm (Harry), Jack) = " << _<lcm, _<Harry>, Jack> () << endl;
		cout << "(lcm () 0) = " << _<lcm, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"lcm is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <lcm>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also gcd, div?, rem, mod, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
