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
		"rev: - reverse all pairs in a list"
	<< endl;

	cout << endl <<
		syntax << "r = (rev: l)" <<
		body << " returns list r that contains the reverse of each pair in l, where l is assumed to be a list of pairs or a relation. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<_8_, a>, _<pumpkin, pie>, _<got, sick> > l;

		cout << "l = " << l() << endl;
		cout << "(rev: l) = " << _<rev_e, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"rev: is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <rev_e>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also rev, first:, second:."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
