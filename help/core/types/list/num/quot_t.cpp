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
		"quot! - return quotient of integer division, terminate"
	<< endl;

	cout << endl <<
		syntax << "n = (quot! n1 n2)" <<
		body << " returns number n that is the quotient of number n1 when divided by number n2, where n1 is assumed to be nonzero and n2 absolutely greater than one. This assumption implies that division moves n1 closer to zero. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(quot! 4 2) = " << _<quot_t, _4_, _2_> () << endl;
		cout << "(quot! 45 13) = " << _<quot_t, number <45>, number <13> > () << endl;
		cout << "(quot! 12 -3) = " << _<quot_t, number <12>, _m3_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n1 is zero or if |n2| <= 1. This property guarantees that recursive division by the same number n2 eventually terminates:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(quot! 0 5) = " << _<quot_t, _0_, _5_> () << endl;
		cout << "(quot! 3 1) = " << _<quot_t, _3_, _1_> () << endl;
		cout << "(quot! 3 0) = " << _<quot_t, _3_, _0_> () << endl;
		cout << "(quot! 3 -1) = " << _<quot_t, _3_, _m1_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is also not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(sub 1 Harry) = " << _<sub, _1_, Harry> () << endl;
		cout << "(sub (Harry), Jack) = " << _<sub, _<Harry>, Jack> () << endl;
		cout << "(sub () 0) = " << _<sub, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"quot! is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <quot_t>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also quot, inc!, dec!, add!, sub!, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
