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
		"cons - insert item at beginning of list"
	<< endl;

	cout << endl <<
		syntax << "r = (cons e l)" <<
		body << " returns list r that is l with expression e inserted as the first item, where l is a list. Hence, r is such that car(r) = e and cdr(r) = l. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef peanut a;
		typedef _<butter, __and, jelly> l;

		cout << "a = " << a() << endl;
		cout << "l = " << l() << endl;
		cout << "(cons a l) = " << _<cons, a, l> () << endl << endl;

		typedef _<banana, __and> e;

		cout << "e = " << e() << endl;
		cout << "(cons e l) = " << _<cons, e, l> () << endl << endl;
	}

	{
		typedef _<_<help>, _this> e;
		typedef _<_is, very, _<_<hard>, to, learn> > l;

		cout << "e = " << e() << endl;
		cout << "l = " << l() << endl;
		cout << "(cons e l) = " << _<cons, e, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If l is empty, (cons e l) returns expression e enclosed in a list, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(cons a ()) = " << _<cons, a, _<> > () << endl << endl;

		typedef _<a, b, _<c> > e;

		cout << "e = " << e() << endl;
		cout << "(cons e ()) = " << _<cons, e, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is not a list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(cons (a b c) b) = " << _<cons, _<a, b, c>, b> () << endl;
		cout << "(cons a b) = " << _<cons, a, b> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Primitive cons may be combined with car and cdr to attach an expression to any item or part of a list, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<b>, c, d> l;

		cout << "l = " << l() << endl;
		cout << "(cons a (car l)) = " << _<cons, a, _<car, l> > () << endl;
		cout << "(cons a (cdr l)) = " << _<cons, a, _<cdr, l> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also car, cdr, null?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
