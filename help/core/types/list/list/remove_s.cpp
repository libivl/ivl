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
		"remove* - remove a member of a list throughout"
	<< endl;

	cout << endl <<
		syntax << "r = (remove* a l)" <<
		body << " returns a list r that is list l with all occurrences of atom a removed. l may be a list of lists, in which case a is removed from nested lists as well. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<lamb, chops>, __and, _<mint, flavored>, _<mint, jelly> > l;

		cout << "l = " << l() << endl;
		cout << "(remove* mint l) = " <<
			_<remove_s, mint, l> () << endl << endl;
	}

	{
		typedef _<_<coffee>, cup, _<_<tea>, cup>, _<__and, _<hick> >, cup> l;

		cout << "l = " << l() << endl;
		cout << "(remove* cup l) = " << _<remove_s, cup, l> () << endl << endl;
	}

	{
		typedef _<
			_<_<tomato, sauce> >,
			_<_<bean>, sauce>,
			_<__and, _<_<flying> >, sauce>
		> l;

		cout << "l = " << l() << endl;
		cout << "(remove* sauce l) = " << _<remove_s, sauce, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If a is not a member of l, then l is returned instead:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<bacon, lettuce, _<__and, tomato> > l;

		cout << "l = " << l() << endl;
		cout << "(remove* toast l) = " <<
			_<remove_s, toast, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If l is empty, an empty list is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(remove* toast ()) = " <<
			_<remove_s, toast, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"remove* is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <remove_s>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also remove, remove+, remove#, insert<*, insert>*, subst*, member*."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
