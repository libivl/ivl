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
	using ivl::types::scheme::rev;

	cout << wrap << endl << title <<
		"rev - reverse the expressions of a pair"
	<< endl;

	cout << endl <<
		syntax << "q = (rev p)" <<
		body << " returns pair q that is the reverse of pair p, i.e., the first (second) expression of q is the second (first) expression of p. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(rev (8 a)) = " << _<rev, _<_8_, a> > () << endl;
		cout << "(rev (pumpkin pie)) = " << _<rev, _<pumpkin, pie> > () << endl;
		cout << "(rev (got sick)) = " << _<rev, _<got, sick> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"rev is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <rev>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also rev:, first, second, pair?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
