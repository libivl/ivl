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
		"subst - replace an atom by another in a list of atoms"
	<< endl;

	cout << endl <<
		syntax << "r = (subst new old la)" <<
		body << " returns a list r that is list la with the first occurrence of atom old replaced by atom new, where la is assumed to be a list of atoms. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<ice, cream, _with, fudge, _for, dessert> la;

		cout << "la = " << la() << endl;
		cout << "(subst topping fudge la) = " <<
			_<subst, topping, fudge, la> () << endl << endl;
	}

	{
		typedef _<tacos, tamales, __and, salsa> la;

		cout << "la = " << la() << endl;
		cout << "(subst jalapeno salsa la) = " <<
			_<subst, jalapeno, salsa, la> () << endl << endl;
	}

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(subst e f la) = " << _<subst, e, f, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If old is not a member of la, then la is returned instead:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(subst e z la) = " << _<subst, e, z, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If la is empty, an empty list is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(subst e z ()) = " << _<subst, e, z, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"subst is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <subst>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also subst+, subst*, subst#, subst2, insert<, insert>, remove, member?, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
