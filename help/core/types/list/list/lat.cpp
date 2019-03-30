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
		"lat? - test whether a list is a list of atoms"
	<< endl;

	cout << endl <<
		syntax << "b = (lat? l)" <<
		body << " returns true if and only if list l is a list of atoms, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<Jack, Sprat, could, eat, no, chicken, fat> l;

		cout << "l = " << l() << endl;
		cout << "(lat? l) = " << _<lat, l> () << endl << endl;
	}

	{
		typedef _<Jack, _<Sprat, could>, eat, no, chicken, fat> l;

		cout << "l = " << l() << endl;
		cout << "(lat? l) = " << _<lat, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list l can also be specified inline, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(lat? (bacon and eggs)) = " <<
			_<lat, _<bacon, __and, eggs> > () << endl;

		cout << "(lat? (bacon (and eggs))) = " <<
			_<lat, _<bacon, _<__and, eggs> > > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is not a list:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(lat? Harry) = " << _<lat, Harry> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"lat? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <lat>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also atom?, member?, set?, tup?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
