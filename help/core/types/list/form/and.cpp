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
	using ivl::types::scheme::eq;

	cout << wrap << endl << title <<
		"and - logical conjunction"
	<< endl;

	cout << endl <<
		syntax << "b = (and b1 b2)" <<
		body << " returns true if and only if both b1 and b2 are true, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		typedef _<mozzarella, pizza> l;

		cout << "l = " << l() << endl;
		cout << "(and (atom? (car l)) (eq? pizza (car? l)) = " <<
			_<_and, _<atom, _<car, l> >, _<eq, pizza, _<car, l> > > () <<
			endl << endl;
	}

	{
		typedef _<_<mozzarella, mushroom>, pizza> l;

		cout << "l = " << l() << endl;
		cout << "(and (atom? (car l)) (eq? pizza (car? l)) = " <<
			_<_and, _<atom, _<car, l> >, _<eq, pizza, _<car, l> > > () <<
			endl << endl;
	}

	{
		typedef _<pizza, _<tastes, good> > l;

		cout << "l = " << l() << endl;
		cout << "(and (atom? (car l)) (eq? pizza (car? l)) = " <<
			_<_and, _<atom, _<car, l> >, _<eq, pizza, _<car, l> > > () <<
			endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"and is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define_syntax <_and>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also or, not, cond."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
