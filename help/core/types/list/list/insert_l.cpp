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
		"insert< - insert an atom to the left of another in a list of atoms"
	<< endl;

	cout << endl <<
		syntax << "r = (insert< new old la)" <<
		body << " returns a list r that is list la with atom new inserted to the left of the first occurrence of atom old in la, where la is assumed to be a list of atoms. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<ice, cream, _with, fudge, _for, dessert> la;

		cout << "la = " << la() << endl;
		cout << "(insert< topping for la) = " <<
			_<insert_l, topping, _for, la> () << endl << endl;
	}

	{
		typedef _<tacos, tamales, __and, salsa> la;

		cout << "la = " << la() << endl;
		cout << "(insert< jalapeno salsa la) = " <<
			_<insert_l, jalapeno, salsa, la> () << endl << endl;
	}

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(insert< e f la) = " << _<insert_l, e, f, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If old is not a member of la, then la is returned instead:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(insert< e z la) = " << _<insert_l, e, z, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If la is empty, an empty list is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(insert< e z ()) = " << _<insert_l, e, z, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"insert< is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <insert_l>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also insert<+, insert<*, insert<#, insert>, remove, subst, member?, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
