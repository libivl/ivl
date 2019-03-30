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
	using ivl::types::scheme::gcd;

	cout << wrap << endl << title <<
		"gcd - greatest common divisor"
	<< endl;

	cout << endl <<
		syntax << "d = (gcd n1 n2)" <<
		body << " returns number d that is the greatest common divisor of numbers n1, n2. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(gcd 10 4) = " << _<gcd, _10_, _4_> () << endl;
		cout << "(gcd 21 6) = " << _<gcd, number <21>, _6_> () << endl;
		cout << "(gcd 48 18) = " << _<gcd, number <48>, _18_> () << endl;
		cout << "(gcd 0 7) = " << _<gcd, _0_, _7_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is nonnegative regardless of the signs of n1, n2:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(gcd 48 -18) = " << _<gcd, number <48>, _m18_> () << endl;
		cout << "(gcd -48 -18) = " << _<gcd, number <-48>, _m18_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(gcd 1 Harry) = " << _<gcd, _1_, Harry> () << endl;
		cout << "(gcd (Harry), Jack) = " << _<gcd, _<Harry>, Jack> () << endl;
		cout << "(gcd () 0) = " << _<gcd, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"gcd is using the Euclidean algorithm and is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <gcd>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also lcm, div?, rem, mod, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
