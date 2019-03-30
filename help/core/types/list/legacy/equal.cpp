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
	using ivl::types::scheme::equal;
	using vocabulary::split;

	cout << wrap << endl << title <<
		"equal? - test whether two expressions are equal"
	<< endl;

	cout << endl <<
		syntax << "b = (equal? e1 e2)" <<
		body << " returns true if and only if expressions e1 and e2 are equal. Two atoms are equal as defined by eq?. Two lists are equal if and only if they contain exactly the same expressions (atoms or lists) in the same order. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(equal? Harry Harry) = " << _<equal, Harry, Harry> () << endl;

		cout << "(equal? margarine butter) = " <<
			_<equal, margarine, butter> () << endl << endl;
	}

	{
		typedef _<strawberry, ice, cream> l1;
		typedef _<strawberry, ice, cream> l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(equal? l1 l2) = " << _<equal, l1, l2> () << endl << endl;
	}

	{
		typedef _<strawberry, ice, cream> l1;
		typedef _<strawberry, cream, ice> l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(equal? l1 l2) = " << _<equal, l1, l2> () << endl << endl;
	}

	{
		typedef _<banana, _<_<split> > > l1;
		typedef _<_<banana>, _<split> > l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(equal? l1 l2) = " << _<equal, l1, l2> () << endl << endl;
	}

	{
		typedef _<beef, _<_<sausage> >, _<__and, _<soda> > > l1;
		typedef _<beef, _<_<salami> >, _<__and, _<soda> > > l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(equal? l1 l2) = " << _<equal, l1, l2> () << endl << endl;
	}

	{
		typedef _<beef, _<_<sausage> >, _<__and, _<soda> > > l1;
		typedef _<beef, _<_<sausage> >, _<__and, _<soda> > > l2;

		cout << "l1 = " << l1() << endl;
		cout << "l2 = " << l2() << endl;
		cout << "(equal? l1 l2) = " << _<equal, l1, l2> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is defined even if e1, e2 are not both atoms or both lists:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<bread, sausage, ketchup, __and, mustard> l;

		cout << "l = " << l() << endl;
		cout << "(equal? hotdog l) = " << _<equal, hotdog, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"equal? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <equal>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also eq?, eq#? eq_list, atom?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
