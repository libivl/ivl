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
		"insert>* - insert an atom to the right of another throughout"
	<< endl;

	cout << endl <<
		syntax << "r = (insert>* new old l)" <<
		body << " returns a list r that is list l with atom new inserted to the right of every occurrence of atom old in l. l may be a list of lists, in which case new is inserted in nested lists as well. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<
			_<how, much, _<wood> >,
			could, _<_<a, _<wood>, chuck> >,
			_<__if, _<a>, _<_<wood, chuck> > >,
			could, chuck, wood
		> l;

		cout << "l = " << indent++ << endl << l() << indent-- << endl << endl;

		cout << "(insert>* roast chuck l) = " << indent++ << endl <<
			_<insert_rs, roast, chuck, l> () << indent-- << endl << endl;
	}

	{
		typedef _<a, _<b, c, _<d> >, _<_<_<f, g>, d>, h, f> > l;

		cout << "l = " << l() << endl;
		cout << "(insert>* e d l) = " <<
			_<insert_rs, e, d, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If old is not a member of l, then l is returned instead:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<a, _<b, c, _<d> >, _<_<_<f, g>, d>, h, f> > l;

		cout << "l = " << l() << endl;
		cout << "(insert>* e z l) = " <<
			_<insert_rs, e, z, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If l is empty, an empty list is returned:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(insert>* e z ()) = " <<
			_<insert_rs, e, z, _<> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"insert>* is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <insert_rs>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also insert>, insert>+, insert>#, insert<*, remove*, subst*, member*."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
