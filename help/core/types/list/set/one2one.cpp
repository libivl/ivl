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
		"one2one? - test whether a function is one-to-one"
	<< endl;

	cout << endl <<
		syntax << "b = (one2one? f)" <<
		body << " returns true if and only if function f is one-one, i.e., the list of second expressions of each pair in f is a set (or equivalently, the reverse of f is a function). E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<
			_<_8_, _3_>,
			_<_4_, _2_>,
			_<_7_, _6_>,
			_<_6_, _2_>,
			_<_3_, _4_>
		> f;

		cout << "f = " << f() << endl;
		cout << "(one2one? f) = " << _<one2one, f> () << endl << endl;
	}

	{
		typedef _<
			_<_8_, _3_>,
			_<_4_, _8_>,
			_<_7_, _6_>,
			_<_6_, _2_>,
			_<_3_, _4_>
		> f;

		cout << "f = " << f() << endl;
		cout << "(one2one? f) = " << _<one2one, f> () << endl << endl;
	}

	{
		typedef _<
			_<grape, raisin>,
			_<plum, prune>,
			_<stewed, prune>
		> f;

		cout << "f = " << f() << endl;
		cout << "(one2one? f) = " << _<one2one, f> () << endl;
		cout << "(fun? (rev+, f)) = " << _<fun, _<rev_m, f> > () << endl << endl;
	}

	{
		typedef _<
			_<grape, raisin>,
			_<plum, prune>,
			_<stewed, grape>
		> f;

		cout << "f = " << f() << endl;
		cout << "(one2one? f) = " << _<one2one, f> () << endl;
		cout << "(fun? (rev+, f)) = " << _<fun, _<rev_m, f> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"one2one? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <one2one>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also func?, rel?, second:, pair?, set?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
