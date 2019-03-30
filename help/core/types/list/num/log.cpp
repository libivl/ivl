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
	using ivl::types::scheme::log;

	cout << wrap << endl << title <<
		"log - logarithm of a number to the base of another"
	<< endl;

	cout << endl <<
		syntax << "n = (log n1 n2)" <<
		body << " returns the logarithm n of number n2 to the base of n1, i.e., the greatest nonnegative number n such that n1 raised to the power of n is absolutely less than or equal to |n2| and of the same sign with n2. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(log -3 9) = " << _<log, _m3_, _9_> () << endl;
		cout << "(log 2 8) = " << _<log, _2_, _8_> () << endl;
		cout << "(log 2 256) = " << _<log, _2_, number <300> > () << endl;
		cout << "(log 2 66000) = " << _<log, _2_, number <66000> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result may be defined or not if n1, n2 are of different signs:"
	<< endl << indent << sample << endl;

	{
		cout << "(log 5 25) = " << _<log, number <5>, number <25> > () << endl;
		cout << "(log 5 -25) = " << _<log, number <5>, number <-25> > () << endl;
		cout << "(log 5 125) = " << _<log, number <5>, number <125> > () << endl;
		cout << "(log 5 -125) = " << _<log, number <5>, number <-125> > () << endl;
		cout << "(log -5 25) = " << _<log, _m5_, number <25> > () << endl;
		cout << "(log -5 -25) = " << _<log, _m5_, number <-25> > () << endl;
		cout << "(log -5 125) = " << _<log, _m5_, number <125> > () << endl;
		cout << "(log -5 -125) = " << _<log, _m5_, number <-125> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result may also be defined or not when |n1| <= 1 or |n2| <= 1:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(log 5 5) = " << _<log, _5_, _5_> () << endl;
		cout << "(log 5 1) = " << _<log, _5_, _1_> () << endl;
		cout << "(log 5 0) = " << _<log, _5_, _0_> () << endl;
		cout << "(log 5 -1) = " << _<log, _5_, _m1_> () << endl;
		cout << "(log 1 5) = " << _<log, _1_, _5_> () << endl;
		cout << "(log 1 1) = " << _<log, _1_, _1_> () << endl;
		cout << "(log 1 0) = " << _<log, _1_, _0_> () << endl;
		cout << "(log 1 -1) = " << _<log, _1_, _m1_> () << endl;
		cout << "(log 0 5) = " << _<log, _0_, _5_> () << endl;
		cout << "(log 0 1) = " << _<log, _0_, _1_> () << endl;
		cout << "(log 0 0) = " << _<log, _0_, _0_> () << endl;
		cout << "(log 0 -1) = " << _<log, _0_, _m1_> () << endl;
		cout << "(log -1 5) = " << _<log, _m1_, _5_> () << endl;
		cout << "(log -1 1) = " << _<log, _m1_, _1_> () << endl;
		cout << "(log -1 0) = " << _<log, _m1_, _0_> () << endl;
		cout << "(log -1 -1) = " << _<log, _m1_, _m1_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(log 1 Harry) = " << _<log, _1_, Harry> () << endl;
		cout << "(log (Harry), 2) = " << _<log, _<Harry>, _2_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"log is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <log>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also log:, exp, quot, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
