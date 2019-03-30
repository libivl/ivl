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
		"mk_set - make a set out of a lat"
	<< endl;

	cout << endl <<
		syntax << "s = (mk_set la)" <<
		body << " returns set s containing the first occurrence of each atom in la in the same order as in la, where la is assumed to be a list of atoms. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<apple, peach, pear, peach, plum, apple, lemon, peach> la;

		cout << "la = " << la() << endl;
		cout << "(mk_set la) = " << _<mk_set, la> () << endl << endl;
	}

	{
		typedef _<apple, _3_, pear, _4_, _9_, apple, _3_, _4_> la;

		cout << "la = " << la() << endl;
		cout << "(mk_set la) = " << _<mk_set, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"mk_set is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <mk_set>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also set?, subset?, eq_set?, sect?, section, union."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
