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

//-----------------------------------------------------------------------------

	cout << wrap << endl << title <<
		"abs: - absolute value of a tuple"
	<< endl;

	cout << endl <<
		syntax << "u = (abs: t)" <<
		body << " returns tuple u that is the absolute value of tuple t. u is of the same length as t; the n-th number in u is the absolute value of the n-th number in t for each n. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_3_, _6_, _9_, _m11_, _4_> t;

		cout << "t = " << t() << endl;
		cout << "(abs: t) = " << _<abs_e, t> () << endl << endl;
	}

	{
		typedef _<_8_, _m5_, _2_, _0_, _m7_> t;

		cout << "t = " << t() << endl;
		cout << "(abs: t) = " << _<abs_e, t> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if t is not a tuple:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(abs: Harry) = " << _<abs_e, Harry> () << endl;

		cout << "(abs: (3 (5 2) 8)) = " <<
			_<abs_e, _<_3_, _<_5_, _2_>, _8_> > () << endl;

		cout << "(abs: (3 5 apple 8)) = " <<
			_<abs_e, _<_3_, _5_, apple, _8_> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"abs: is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <abs_e>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also abs, max:, neg:, tup?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
