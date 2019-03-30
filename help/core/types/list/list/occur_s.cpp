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

	using vocabulary::split;

	cout << wrap << endl << title <<
		"occur* - count the occurrences of an atom in a list throughout"
	<< endl;

	cout << endl <<
		syntax << "n = (occur* a l)" <<
		body << " returns number n that is the number of occurrences of atom a in list l. l may be a list of lists, in which case a is looked for in nested lists as well. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<
			_<banana>,
			_<split, _<
				_<_<_<banana, ice> > >,
				_<cream, _<lemon> >,
				sherbet
			> >,
			_<banana>,
			_<banana, brandy>
		> l;

		cout << "l = " << indent++ << endl << l() << indent-- << endl << endl;

		cout << "(occur* banana l) = " << indent++ << endl <<
			_<occur_s, banana, l> () << indent-- << endl << endl;
	}

	{
		typedef _<a, _<b, c, _<d> >, _<_<_<f, g>, d>, h, f> > l;

		cout << "l = " << l() << endl;
		cout << "(occur* d l) = " << _<occur_s, d, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is zero if a is not a member of l or if l is empty:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, _<b, c, _<d> >, _<_<_<f, g>, d>, h, f> > l;

		cout << "l = " << l() << endl;
		cout << "(occur* z l) = " << _<occur_s, z, l> () << endl << endl;
	}

	{
		cout << "(occur_s z ()) = " << _<occur_s, z, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"occur* is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <occur_s>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also occur, member*, length, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
