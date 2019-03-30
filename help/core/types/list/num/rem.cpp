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
	using ivl::types::scheme::rem;

	cout << wrap << endl << title <<
		"rem - remainder of integer division"
	<< endl;

	cout << endl <<
		syntax << "r = (rem n1 n2)" <<
		body << " returns number r that is the remainder of number n1 when divided by number n2. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(rem 4 2) = " << _<rem, _4_, _2_> () << endl;
		cout << "(rem 11 7) = " << _<rem, _11_, _7_> () << endl;
		cout << "(rem 45 13) = " << _<rem, number <45>, _13_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The remainder is such that n1 = q * n2 + r, where q is quotient (quot n1 n2):"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(quot 17 5) = " << _<quot, _17_, _5_> () << endl;
		cout << "(rem 17 5) = " << _<rem, _17_, _5_> () << endl;
		cout << "(add (mul (quot 17 5) 5) (rem 17 5)) = " << _<add,
			_<mul, _<quot, _17_, _5_>, _5_>,
			_<rem, _17_, _5_>
		> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is negative if n1 is negative, regardless of n2:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(rem 17 5) = " << _<rem, _17_, _5_> () << endl;
		cout << "(rem 17 -5) = " << _<rem, _17_, _m5_> () << endl;
		cout << "(rem -17 5) = " << _<rem, _m17_, _5_> () << endl;
		cout << "(rem -17 -5) = " << _<rem, _m17_, _m5_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"However, r is not defined if n2 = 0:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(rem 11 0) = " << _<rem, _11_, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is also not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(rem 1 Harry) = " << _<rem, _1_, Harry> () << endl;
		cout << "(rem (Harry), Jack) = " << _<rem, _<Harry>, Jack> () << endl;
		cout << "(rem () 0) = " << _<rem, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"rem is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <rem>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also rem:, mod, quot, gcd, lcm, div?, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
