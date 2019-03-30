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
		"!eq#? - test whether two numbers are not equal"
	<< endl;

	cout << endl <<
		syntax << "b = (!eq#? n1 n2)" << body
		<< " returns true if and only if numbers n1, n2 are not equal, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(!eq#? 12 12) = " << _<neqn, _12_, _12_> () << endl;
		cout << "(!eq#? 12 133) = " << _<neqn, _12_, number <133> > () << endl;
		cout << "(!eq#? 120 11) = " << _<neqn, number <120>, _11_> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if either of n1, n2 is not a number:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(!eq#? () (strawberry)) = " <<
			_<neqn, _<>, _<strawberry> > () << endl << endl;

		typedef _<just, _1_> l;

		cout << "l = " << l() << endl;
		cout << "(!eq#? 10 (cdr l)) = " <<
			_<neqn, _10_, _<cdr, l> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"!eq#? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <neqn>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also eq#?, lt?, gt?, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
