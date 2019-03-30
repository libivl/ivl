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
		"subst2* - replace any of two atoms by another throughout"
	<< endl;

	cout << endl <<
		syntax << "r = (subst2* new (old1 old2) l)" <<
		body << " returns a list r that is list l with every occurrence of atom old1 or atom old2 replaced by atom new. l may be a list of lists, in which case replacement takes place in nested lists as well. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<
			_<banana>,
			_<split, _<
				_<_<_<banana, ice> > >,
				_<cream, _<lemon> >,
				sherbet
			> >,
			_<banana>,
			_<banana, brandy>
		> l;

		cout << "l = " << indent++ << endl << l() << indent-- << endl << endl;

		cout << "(subst2* orange (banana lemon) l) = " << indent++ << endl <<
			_<subst2_s, orange, _<banana, lemon>, l> () << indent-- << endl << endl;
	}

	{
		typedef _<a, _<b, c, _<d> >, _<_<_<f, g>, d>, h, f> > l;

		cout << "l = " << l() << endl;
		cout << "(subst2* e (f d) l) = " << _<subst2_s, e, _<f, d>, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If neither old1 nor old2 are members of l, then l is returned instead:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, _<b, c, _<d> >, _<_<_<f, g>, d>, h, f> > l;

		cout << "l = " << l() << endl;
		cout << "(subst2* e (w z) l) = " <<
			_<subst2_s, e, _<w, z>, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If l is empty, an empty list is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(subst2* e (w z) ()) = " <<
			_<subst2_s, e, _<w, z>, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"subst2* is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <subst2_s>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also subst2, subst2+, subst*, insert<*, insert>*, rember*, member*."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
