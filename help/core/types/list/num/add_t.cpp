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
		"add! - add two numbers, terminate"
	<< endl;

	cout << endl <<
		syntax << "n = (add! n1 n2)" <<
		body << " returns number n that is the sum of numbers n1, n2, where n1, n2 are assumed to be nonzero and of different signs. This assumption implies that addition moves n1 closer to zero. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(add! 1 -2) = " << _<add_t, _1_, _m2_> () << endl;
		cout << "(add! 46 -12) = " << _<add_t, number <46>, _m12_> () << endl;
		cout << "(add! -12 3) = " << _<add_t, _m12_, _3_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n1, n2 are zero or of the same sign. This property guarantees that recursive addition of the same number n2 eventually terminates:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(add! 3 0) = " << _<add_t, _3_, _0_> () << endl;
		cout << "(add! 0 -5) = " << _<add_t, _0_, _m5_> () << endl;
		cout << "(add! -3 -5) = " << _<add_t, _m3_, _m5_> () << endl;
		cout << "(add! 3 5) = " << _<add_t, _3_, _5_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is also not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(add! 1 Harry) = " << _<add_t, _1_, Harry> () << endl;
		cout << "(add! (Harry), Jack) = " << _<add_t, _<Harry>, Jack> () << endl;
		cout << "(add! () 0) = " << _<add_t, _<>, _0_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"add! is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <add_t>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also add, sub!, inc!, dec!, quot!, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
