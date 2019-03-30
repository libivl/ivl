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
	using ivl::types::scheme::pair;

	cout << wrap << endl << title <<
		"pair? - test whether an expression is a pair"
	<< endl;

	cout << endl <<
		syntax << "b = (pair? e)" <<
		body << " returns true if and only if expression e is a pair, i.e., a list of exactly two items. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(pair? pear) = " << _<pair, pear> () << endl;
		cout << "(pair? (pear)) = " << _<pair, _<pear> > () << endl;
		cout << "(pair? (pear pear)) = " << _<pair, _<pear, pear> > () << endl;
		cout << "(pair? (pear pear pear)) = " <<
			_<pair, _<pear, pear, pear> > () << endl;
		cout << "(pair? (3 7)) = " << _<pair, _<_3_, _7_> > () << endl;
		cout << "(pair? ((2) (pair))) = " <<
			_<pair, _<_<_2_>, _<_pair> > > () << endl;
		cout << "(pair? (full (house))) = " <<
			_<pair, _<full, _<house> > > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"pair? is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <pair>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also first, second, rev, func?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
