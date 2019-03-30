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
	using ivl::types::scheme::gt;

	cout << wrap << endl << title <<
		"gt? - test whether a number is greater than another"
	<< endl;

	cout << endl <<
		syntax << "b = (gt? n1 n2)" << body
		<< " returns true if and only if number n1 is greater than n2, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(gt? 12 12) = " << _<gt, _12_, _12_> () << endl;
		cout << "(gt? 12 133) = " << _<gt, _12_, number <133> > () << endl;
		cout << "(gt? 120 11) = " << _<gt, number <120>, _11_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(gt? () (strawberry)) = " <<
			_<gt, _<>, _<strawberry> > () << endl << endl;

		typedef _<just, _1_> l;

		cout << "l = " << l() << endl;
		cout << "(gt? 10 (cdr l)) = " <<
			_<gt, _10_, _<cdr, l> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"gt? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <gt>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also ge?, lt?, eq#?, min, max, abs, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
