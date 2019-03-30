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
	using ivl::types::scheme::first;

	cout << wrap << endl << title <<
		"first - first expression of a list or pair"
	<< endl;

	cout << endl <<
		syntax << "e = (first p)" <<
		body << " returns expression e that is the first expression in list or pair p, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(first (pear)) = " << _<first, _<pear> > () << endl;
		cout << "(first (pear pear)) = " << _<first, _<pear, pear> > () << endl;
		cout << "(first (pear pear pear)) = " <<
			_<first, _<pear, pear, pear> > () << endl;
		cout << "(first (3 7)) = " << _<first, _<_3_, _7_> > () << endl;
		cout << "(first ((2) (pair))) = " <<
			_<first, _<_<_2_>, _<_pair> > > () << endl;
		cout << "(first (full (house))) = " <<
			_<first, _<full, _<house> > > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if p is not a list or if it is empty:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(first pear) = " << _<first, pear> () << endl;
		cout << "(first ()) = " << _<first, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"first is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <first>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also first:, car, leftmost, second, third, pair?, rev."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
