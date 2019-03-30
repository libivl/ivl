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
		"add: - add two tuples"
	<< endl;

	cout << endl <<
		syntax << "t = (add: t1 t2)" <<
		body << " returns tuple t that is the sum of tuples t1, t2, possibly of different length. E.g, if t1, t2 are of length l1, l2 respectively and l1 <= l2, then t is of length l2; the n-th number in t is the sum of the n-th numbers in t1, t2 for 1 <= n <= l1, and the n-th number in t2 for l1 < n <= l2 (in case l1 < l2 only). E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_3_, _6_, _9_, _11_, _4_> t1;
		typedef _<_8_, _5_, _2_, _0_, _7_> t2;

		cout << "t1 = " << t1() << endl;
		cout << "t2 = " << t2() << endl;
		cout << "(add: t1 t2) = " << _<add_e, t1, t2> () << endl << endl;
	}

	{
		typedef _<_3_, _7_> t1;
		typedef _<_4_, _6_, _8_, _1_> t2;

		cout << "t1 = " << t1() << endl;
		cout << "t2 = " << t2() << endl;
		cout << "(add: t1 t2) = " << _<add_e, t1, t2> () << endl << endl;
	}

	{
		typedef _<_3_, _7_, _8_, _1_> t1;
		typedef _<_4_, _6_> t2;

		cout << "t1 = " << t1() << endl;
		cout << "t2 = " << t2() << endl;
		cout << "(add: t1 t2) = " << _<add_e, t1, t2> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of t1, t2 is not a tuple:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(add: (4 3) Harry) = " <<
			_<add_e, _<_4_, _3_>, Harry> () << endl;

		cout << "(add: (3 (5 2) 8) (3 7 8 1)) = " <<
			_<add_e, _<_3_, _<_5_, _2_>, _8_>, _<_3_, _7_, _8_, _1_> > () << endl;

		cout << "(add: (3 5 apple 8) (3 7 8 1)) = " <<
			_<add_e, _<_3_, _5_, apple, _8_>, _<_3_, _7_, _8_, _1_> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"add: is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <add_e>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also add, sum, inc:, sub:, mul:, tup?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
