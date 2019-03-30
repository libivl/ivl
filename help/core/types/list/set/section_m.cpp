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
		"section+ - intersection of sets in a list"
	<< endl;

	cout << endl <<
		syntax << "s = (section+ ls)" <<
		body << " returns set s that is the intersection of all sets in ls, in the same order as in the first set in ls, where ls is assumed to be a list of sets. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<a, b, c>, _<c, a, d, e>, _<e, f, g, h, a, b> > ls;

		cout << "ls = " << ls() << endl;
		cout << "(section+ ls) = " << _<section_m, ls> () << endl << endl;
	}

	{
		typedef _<
			_<_6_, pears, __and>,
			_<_3_, peaches, __and, _6_, peppers>,
			_<_8_, pears, __and, _6_, plums>,
			_<__and, _6_, prunes, _with, some, apples>
		> ls;

		cout << "ls = " << indent++ << endl << ls() << indent-- << endl;
		cout << "(section+ ls) = " << _<section_m, ls> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If ls contains just one set, this set is returned; however, if ls is empty, the result is not defined:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(section+ ((a b c))) = " <<
			_<section_m, _<_<a, b, c> > > () << endl;

		cout << "(section+ (())) = " <<
			_<section_m, _<_<> > > () << endl;

		cout << "(section+ ()) = " << _<section_m, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"section+ is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <section_m>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also section, union+, sect?, set?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
