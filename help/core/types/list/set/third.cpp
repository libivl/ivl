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
		"third - third expression of a list"
	<< endl;

	cout << endl <<
		syntax << "e = (third l)" <<
		body << " returns expression e that is the third expression in list l, e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(third (pear pear pear)) = " <<
			_<third, _<pear, pear, pear> > () << endl << endl;
	}

	{
		typedef _<apple, _3_, pear, _4_, _9_, apple, _3_, _4_> l;

		cout << "l = " << l() << endl;
		cout << "(third l) = " << _<third, l> () << endl << endl;
	}

	{
		typedef _<_<apple, _3_>, _<pear, _4_, _9_>, _<apple, _3_, _4_> > l;

		cout << "l = " << l() << endl;
		cout << "(third l) = " << _<third, l> () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if l is not a list or if it has less than three items:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	{
		cout << "(third ()) = " << _<third, _<> > () << endl;
		cout << "(third pear) = " << _<third, pear> () << endl;
		cout << "(third (pear)) = " << _<third, _<pear> > () << endl;
		cout << "(third (pear pear)) = " << _<third, _<pear, pear> > () << endl;
	}

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"third is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <third>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also third:, first, second."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
