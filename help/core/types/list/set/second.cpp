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
		"second - second expression of a list or pair"
	<< endl;

	cout << endl <<
		syntax << "e = (second p)" <<
		body << " returns expression e that is the second expression in list or pair p, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(second (pear pear)) = " << _<second, _<pear, pear> > () << endl;
		cout << "(second (pear pear pear)) = " <<
			_<second, _<pear, pear, pear> > () << endl;
		cout << "(second (3 7)) = " << _<second, _<_3_, _7_> > () << endl;
		cout << "(second ((2) (pair))) = " <<
			_<second, _<_<_2_>, _<_pair> > > () << endl;
		cout << "(second (full (house))) = " <<
			_<second, _<full, _<house> > > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if p is not a list or if it has less than two items:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(second pear) = " << _<second, pear> () << endl;
		cout << "(second (pear)) = " << _<second, _<pear> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"second is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <second>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also second:, first, third, pair?, rev."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
