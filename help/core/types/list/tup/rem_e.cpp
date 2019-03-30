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
		"rem: - remainder of integer division of two tuples"
	<< endl;

	cout << endl <<
		syntax << "t = (rem: t1 t2)" <<
		body << " returns tuple t that is the remainder of integer division of tuples t1, t2 of the same length. t is of the same length as t1, t2; the n-th number in t is the remainder of the n-th number in t1 when divided by the n-th number in t2 for each n. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_4_, _m11_, number <45>, _12_, _11_, _0_, _m17_> t1;
		typedef _<_2_, _7_, _13_, _m3_, _m4_, _7_, _m5_> t2;

		cout << "t1 = " << t1() << endl;
		cout << "t2 = " << t2() << endl;
		cout << "(rem: t1 t2) = " << _<rem_e, t1, t2> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if t1, t2 are not of the same length:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_3_, _7_> t1;
		typedef _<_4_, _6_, _8_, _1_> t2;

		cout << "t1 = " << t1() << endl;
		cout << "t2 = " << t2() << endl;
		cout << "(rem: t1 t2) = " << _<rem_e, t1, t2> () << endl << endl;
	}

	{
		typedef _<_3_, _7_, _8_, _1_> t1;
		typedef _<_4_, _6_> t2;

		cout << "t1 = " << t1() << endl;
		cout << "t2 = " << t2() << endl;
		cout << "(rem: t1 t2) = " << _<rem_e, t1, t2> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is also not defined if either of t1, t2 is not a tuple:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(rem: (4 3) Harry) = " <<
			_<rem_e, _<_4_, _3_>, Harry> () << endl;

		cout << "(rem: (3 (5 2) 8) (3 7 8 1)) = " <<
			_<rem_e, _<_3_, _<_5_, _2_>, _8_>, _<_3_, _7_, _8_, _1_> > () << endl;

		cout << "(rem: (3 5 apple 8) (3 7 8 1)) = " <<
			_<rem_e, _<_3_, _5_, apple, _8_>, _<_3_, _7_, _8_, _1_> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"rem: is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <rem_e>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also rem, mod:, quot:, mul:, tup?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
