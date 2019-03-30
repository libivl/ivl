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
		"member* - test whether an atom appears in a list"
	<< endl;

	cout << endl <<
		syntax << "b = (member* a l)" <<
		body << " returns true if and only if atom a appears in list l. l may be a list of lists, in which case a is searched for in nested lists as well. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<_<fried, eggs>, __and, _<scrambled, eggs> > l;

		cout << "l = " << l() << endl;
		cout << "(member* poached l) = " <<
			_<member_s, poached, l> () << endl;
		cout << "(member* fried l) = " <<
			_<member_s, fried, l> () << endl << endl;
	}

	{
		typedef _<_<potato>, _<chips, _<_<_with>, fish>, _<chips> > > l;

		cout << "l = " << l() << endl;
		cout << "(member* chips l) = " <<
			_<member_s, chips, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The input list l can also be specified inline, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(member* bagels ((bagels) and lox)) = " <<
			_<member_s, bagels, _<_<bagels>, __and, lox> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"member* is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <member_s>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also member, occur*, rember*, subst*, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
