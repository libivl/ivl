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
		"neg - negate a number"
	<< endl;

	cout << endl <<
		syntax << "m = (neg n)" <<
		body << " returns number m that is the negative of number n, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(neg 2) = " << _<neg, _2_> () << endl;
		cout << "(neg 0) = " << _<neg, _0_> () << endl;
		cout << "(neg -46) = " << _<neg, number <-46> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if n is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(neg Harry) = " << _<neg, Harry> () << endl;
		cout << "(neg (Harry)) = " << _<neg, _<Harry> > () << endl;
		cout << "(neg ()) = " << _<neg, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"neg is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <neg>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also neg:, sign, abs, sub, add, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
