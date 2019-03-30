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
		"inc! - increase a non-negative number by one, terminate"
	<< endl;

	cout << endl <<
		syntax << "m = (inc! n)" <<
		body << " returns number m that is number n increased by one, where n is assumed to be negative. This assumption implies that n moves closer to zero. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(inc! -2) = " << _<inc_t, _m2_> () << endl;
		cout << "(inc! -46) = " << _<inc_t, number <-46> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n is nonnegative. This property guarantees that recursive increase eventually terminates:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(inc! 0) = " << _<inc_t, _0_> () << endl;
		cout << "(inc! 3) = " << _<inc_t, number <3> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is also not defined if n is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(inc! Harry) = " << _<inc_t, Harry> () << endl;
		cout << "(inc! (Harry)) = " << _<inc_t, _<Harry> > () << endl;
		cout << "(inc! ()) = " << _<inc_t, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"inc! is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <inc_t>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also inc, dec!, add!, sub!, quot!, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
