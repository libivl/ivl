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
	using ivl::types::scheme::min;

	cout << wrap << endl << title <<
		"min - minimum of two numbers"
	<< endl;

	cout << endl <<
		syntax << "n = (min n1 n2)" <<
		body << " returns number n that is the minimum of numbers n1, n2, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(min 1 2) = " << _<min, _1_, _2_> () << endl;
		cout << "(min 46 12) = " << _<min, number <46>, number <12> > () << endl;
		cout << "(min 12 -3) = " << _<min, number <12>, _m3_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(min 1 Harry) = " << _<min, _1_, Harry> () << endl;
		cout << "(min (Harry), Jack) = " << _<min, _<Harry>, Jack> () << endl;
		cout << "(min () 0) = " << _<min, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"min is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <min>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also min:, min+, max, lt?, gt?, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
