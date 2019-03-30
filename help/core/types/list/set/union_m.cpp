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
		"union+ - union of sets in a list"
	<< endl;

	cout << endl <<
		syntax << "s = (union+ ls)" <<
		body << " returns set s that is the union of all sets in ls, where ls is assumed to be a list of sets. Atoms only in s1 are given first in the same order as in s1, where s1 is the first set in ls; atoms only in s2 follow in the same order as in s2, where s2 is the second set in ls, and so on. After that, atoms not in s1 follow in the same order as in s2 and so on. Finally, those in the last set in ls come last in the same order as in that set. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<a, b, c>, _<c, a, d, e>, _<e, f, g, h, a, b> > ls;

		cout << "ls = " << ls() << endl;
		cout << "(union+ ls) = " << _<union_m, ls> () << endl << endl;
	}

	{
		typedef _<
			_<_6_, pears, __and>,
			_<_3_, peaches, __and, _6_, peppers>,
			_<_8_, pears, __and, _6_, plums>,
			_<__and, _6_, prunes, _with, some, apples>
		> ls;

		cout << "ls = " << indent++ << endl << ls() << indent-- << endl;
		cout << "(union+ ls) = " << indent++ << endl <<
			_<union_m, ls> () << indent-- << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If ls contains just one set, this set is returned; and if ls is empty, an empty set is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(union+ ((a b c))) = " <<
			_<union_m, _<_<a, b, c> > > () << endl;

		cout << "(union+ (())) = " << _<union_m, _<_<> > > () << endl;

		cout << "(union+ ()) = " << _<union_m, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"union+ is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <union_m>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also union, section+, set?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
