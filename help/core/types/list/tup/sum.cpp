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
	using ivl::types::scheme::sum;

//-----------------------------------------------------------------------------

	cout << wrap << endl << title <<
		"sum - sum of all numbers in a tuple"
	<< endl;

	cout << endl <<
		syntax << "n = (sum t)" <<
		body << " returns number n that is the sum of all numbers in tuple t, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(sum (3 5 2 8)) = " <<
			_<sum, _<_3_, _5_, _2_, _8_> > () << endl;

		cout << "(sum (15 6 7 12 -3)) = " <<
			_<sum, _<_15_, _6_, _7_, _12_, _m3_> > () << endl;

		cout << "(sum ()) = " << _<sum, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if t is not a tuple:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(sum Harry) = " << _<sum, Harry> () << endl;

		cout << "(sum (3 (5 2) 8)) = " <<
			_<sum, _<_3_, _<_5_, _2_>, _8_> > () << endl;

		cout << "(sum (3 5 apple 8)) = " <<
			_<sum, _<_3_, _5_, apple, _8_> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"sum is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <sum>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also add, add:, prod, tup?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
