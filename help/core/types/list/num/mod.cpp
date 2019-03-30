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
	using ivl::types::scheme::mod;

	cout << wrap << endl << title <<
		"modulo - equivalence class of a number modulo another"
	<< endl;

	cout << endl <<
		syntax << "m = (mod n1 n2)" <<
		body << " returns number m that represents the equivalence class of n1 modulo number n2. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(mod 4 2) = " << _<mod, _4_, _2_> () << endl;
		cout << "(mod 11 7) = " << _<mod, _11_, _7_> () << endl;
		cout << "(mod 45 13) = " << _<mod, number <45>, _13_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"m is a nonnegative number in {0, ..., |n1|-1} and there is a number q such that n1 = q * n2 + m. However, unlike rem, q is not equal to (quot n1 n2) if n2 < 0:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(mod 17 5) = " << _<mod, _17_, _5_> () << endl;
		cout << "(mod 17 -5) = " << _<mod, _17_, _m5_> () << endl;
		cout << "(mod -17 5) = " << _<mod, _m17_, _5_> () << endl;
		cout << "(mod -17 -5) = " << _<mod, _m17_, _m5_> () << endl << endl;

		cout << "(add (mul (quot 17 5) 5) (mod 17 5)) = " << _<add,
			_<mul, _<quot, _17_, _5_>, _5_>,
			_<mod, _17_, _5_>
		> () << endl;

		cout << "(add (mul (quot -17 5) 5) (mod -17 5)) = " << _<add,
			_<mul, _<quot, _m17_, _5_>, _5_>,
			_<mod, _m17_, _5_>
		> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n2 = 0:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(mod 11 0) = " << _<mod, _11_, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is also not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(mod 1 Harry) = " << _<mod, _1_, Harry> () << endl;
		cout << "(mod (Harry), Jack) = " << _<mod, _<Harry>, Jack> () << endl;
		cout << "(mod () 0) = " << _<mod, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"mod is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <mod>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also mod:, rem, quot, gcd, lcm, div?, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
