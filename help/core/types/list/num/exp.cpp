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
	using ivl::types::scheme::exp;

	cout << wrap << endl << title <<
		"exp - raise a number to the power of another"
	<< endl;

	cout << endl <<
		syntax << "n = (exp n1 n2)" <<
		body << " returns number n that is number n1 raised to the power of number n2, where n2 is assumed to be non-negative, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(exp 1 1) = " << _<exp, _1_, _1_> () << endl;
		cout << "(exp 2 3) = " << _<exp, _2_, _3_> () << endl;
		cout << "(exp 2 8) = " << _<exp, _2_, _8_> () << endl;
		cout << "(exp 2 16) = " << _<exp, _2_, _16_> () << endl;
		cout << "(exp (exp(2 4) 4) = " << _<exp, _<exp, _2_, _4_>, _4_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"n1 can be negative; if it is zero, the result is zero unless n2 = 0:"
	<< endl << indent << sample << endl;

	{
		cout << "(exp -5 3) = " << _<exp, _m5_, _3_> () << endl;
		cout << "(exp -5 0) = " << _<exp, _m5_, _0_> () << endl;
		cout << "(exp 0 0) = " << _<exp, _0_, _0_> () << endl;
		cout << "(exp 0 10) = " << _<exp, _0_, _10_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n2 is negative unless |n1| = 1:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(exp 5 -3) = " << _<exp, _5_, _m3_> () << endl;
		cout << "(exp 0 -2) = " << _<exp, _0_, _m2_> () << endl;
		cout << "(exp 1 -4) = " << _<exp, _1_, _m4_> () << endl;
		cout << "(exp -1 -3) = " << _<exp, _m1_, _m3_> () << endl;
		cout << "(exp -1 -8) = " << _<exp, _m1_, _m8_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is also not defined if either of n1, n2 is not a number, unless n1 = 1 or n2 = 0:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(exp 2 Harry) = " << _<exp, _2_, Harry> () << endl;
		cout << "(exp (Harry) 2) = " << _<exp, _<Harry>, _2_> () << endl;
		cout << "(exp 1 Harry) = " << _<exp, _1_, Harry> () << endl;
		cout << "(exp () 0) = " << _<exp, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"exp is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <exp>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also exp:, log, mul, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
