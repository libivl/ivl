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
	using vocabulary::split;

	cout << wrap << endl << title <<
		"subst2+ - replace every occurrence of any of two atoms by another"
	<< endl;

	cout << endl <<
		syntax << "r = (subst2+ new (old1 old2) la)" <<
		body << " returns a list r that is list la with every occurrence of atom old1 or atom old2 replaced by atom new, where la is assumed to be a list of atoms. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<
			banana, split,
			banana, ice, cream,
			lemon, sherbet,
			banana,
			banana, brandy
		> la;

		cout << "la = " << indent++ << endl << la() << indent-- << endl << endl;

		cout << "(subst2+ orange (banana lemon) la) = " <<
			indent++ << endl <<
			_<subst2_m, orange, _<banana, lemon>, la> () <<
			indent-- << endl << endl;
	}

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(subst2+ e (f d) la) = " <<
			_<subst2_m, e, _<f, d>, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If neither old1 nor old2 are members of la, then la is returned instead:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, b, c, d, f, g, d, h, f> la;

		cout << "la = " << la() << endl;
		cout << "(subst2+ e (w z) la) = " <<
			_<subst2_m, e, _<w, z>, la> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If la is empty, an empty list is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(subst2+ e (w z) ()) = " <<
			_<subst2_m, e, _<w, z>, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"subst2+ is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <subst2_m>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also subst2, subst2*, subst+, insert<+, insert>+, rember+, member?, lat?."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
