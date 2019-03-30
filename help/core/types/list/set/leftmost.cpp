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
		"leftmost - return the leftmost atom of a non-empty list"
	<< endl;

	cout << endl <<
		syntax << "a = (leftmost l)" <<
		body << " returns the leftmost atom a of non-empty list l; if the first item of l is a nested list n, a is the leftmost atom of n, again assumed to be non-empty, and so on. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<potato>, _<chips, _<_<_with>, fish>, _<chips> > > l;

		cout << "l = " << l() << endl;
		cout << "(leftmost l) = " << _<leftmost, l> () << endl << endl;
	}

	{
		typedef _<_<_<hot>, _<tuna, _<__and> > >, cheese> l;

		cout << "l = " << l() << endl;
		cout << "(leftmost l) = " << _<leftmost, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is empty or if it contains an empty list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<_<_<>, four> >, seven, _<eleven> > l;

		cout << "l = " << l() << endl;
		cout << "(leftmost l) = " << _<leftmost, l> () << endl << endl;
	}

	{
		cout << "(leftmost ()) = " << _<leftmost, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"leftmost is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <leftmost>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also first, first:, car."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
