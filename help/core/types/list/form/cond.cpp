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
	using ivl::types::scheme::cond;

	cout << wrap << endl << title <<
		"cond - evaluate expression conditionally"
	<< endl;

	cout << endl <<
		syntax << "r = (cond (c_1 e_1) .. (c_N e_N) (_else e))" <<
		body << " tests conditions c_1, .., c_N in turn and returns expression r that is one of expressions e_1, .., e_N, or e. If c_i is the first condition to be satisfied, e_i is returned; if none is satisfied, e is returned instead. Each condition is assumed to be an expression evaluating to _true or _false. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<bacon, __and, eggs> l;

	cout << "l = " << l() << endl << endl;

	cout <<
	"(cond" << indent++ << endl <<
		"((null? l) _true)" << endl <<
		"((atom? (car l)) (cdr l))" << endl <<
		"(_else _false)" << indent-- << endl <<
	") = " <<
	_<cond,
		_<_<null, l>, _true>,
		_<_<atom, _<car, l> >, _<cdr, l> >,
		_<_else, _false>
	> () << endl;

	// TODO: more, simpler and more meaningful examples

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also lambda, if."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
