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
		"car - first item of non-empty list"
	<< endl;

	cout << endl <<
		syntax << "e = (car l)" <<
		body << " returns expression e that is the first item of non-empty list l, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, b, c> l;

		cout << "l = " << l() << endl;
		cout << "(car l) = " << _<car, l> () << endl << endl;
	}

	{
		typedef _<_<a, b, c>, x, y, z> l;

		cout << "l = " << l() << endl;
		cout << "(car l) = " << _<car, l> () << endl << endl;
	}

	{
		typedef _<_<_<hotdogs> >, _<__and>, _<pickle>, relish> l;

		cout << "l = " << l() << endl;
		cout << "(car l) = " << _<car, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list l can also be specified inline, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(car (((hotdogs)) (and) (pickle) relish)) = " << _<car,
				_<_<_<hotdogs> >, _<__and>, _<pickle>, relish>
			> () << endl << endl;
	}

	{
		typedef _<_<_<hotdogs> >, _<__and> > l;

		cout << "l = " << l() << endl;
		cout << "(car (car l)) = " << _<car, _<car, l> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is empty or if l is not a list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(car ()) = " << _<car, _<> > () << endl;
		cout << "(car hotdog) = " << _<car, hotdog> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also cdr, cons, null?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
