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
	using ivl::types::scheme::lt;

	cout << wrap << endl << title <<
		"lt? - test whether a number is less than another"
	<< endl;

	cout << endl <<
		syntax << "b = (lt? n1 n2)" << body
		<< " returns true if and only if number n1 is less than n2, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(lt? 12 12) = " << _<lt, _12_, _12_> () << endl;
		cout << "(lt? 12 133) = " << _<lt, _12_, number <133> > () << endl;
		cout << "(lt? 120 11) = " << _<lt, number <120>, _11_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(lt? () (strawberry)) = " <<
			_<lt, _<>, _<strawberry> > () << endl << endl;

		typedef _<just, _1_> l;

		cout << "l = " << l() << endl;
		cout << "(lt? (cdr l) 10) = " <<
			_<lt, _<cdr, l>, _10_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also le?, gt?, eq#?, min, max, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
