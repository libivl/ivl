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
	using ivl::types::scheme::eq;

	cout << wrap << endl << title <<
		"eq? - test whether two atoms are equal"
	<< endl;

	cout << endl <<
		syntax << "b = (eq? a b)" << body
		<< " returns true if and only if atoms a and b are equal, i.e. represent the same type. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(eq? Harry Harry) = " << _<eq, Harry, Harry> () << endl;

		cout << "(eq? margarine butter) = " <<
			_<eq, margarine, butter> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Primitive eq? may be combined with car and cdr to compare any two items of the same or two different lists. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<Mary, had, a, little, lamb, chop> l;

		cout << "l = " << l() << endl;
		cout << "(eq? (car l) Mary) = " <<
			_<eq, _<car, l>, Mary> () << endl << endl;
	}

	{
		typedef _<beans, beans, we, need, jelly, beans> l;

		cout << "l = " << l() << endl;
		cout << "(eq? (car l) (car (cdr l))) = " <<
			_<eq, _<car, l>, _<car, _<cdr, l> > > () <<  endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if any of a, b is not an atom:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(eq? () (strawberry)) = " <<
			_<eq, _<>, _<strawberry> > () << endl << endl;

		typedef _<soured, milk> l;

		cout << "l = " << l() << endl;
		cout << "(eq? (cdr l) (milk)) = " <<
			_<eq, _<cdr, l>, milk> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also equal?, eq_list?, atom?, num?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
