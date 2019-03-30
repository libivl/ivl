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
		"Y - applicative-order Y combinator"
	<< endl;

	cout << endl <<
		syntax << "r = (Y le)" <<
		body << " returns recursive lambda expression r defined by lambda expression le without using primitive define. Here le is assumed to take one argument f representing the desired recursive lambda expression and having as body a nested lambda expression n; inside the body of n, variable f may be used to invoke n itself recursively. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef
	_<lambda, _<f>, _<
		lambda, _<l>, _<
			cond,
			_<_<null, l>, _0_>,
			_<_else, _<inc, _<f, _<cdr, l> > > >
		>
	> >
	le;

	cout << "le = " << indent++ << endl << endl << le() << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"defines lambda expression le representing recursive evaluation of the length of a list. The nested lambda expression n here takes one argument l representing an arbitrary list given as input. The body of n is assumed to compute the length of l: if l is empty, length zero is returned; otherwise, variable f is used to recursively invoke n on the cdr of l and increase the result by one. Recursive application of cdr eventually returns an empty list and then recursion terminates." << endl << endl <<

		"The role of lambda expression le can be thought of as providing a name, f, to the otherwise unnamed lambda expression n, so that the latter can invoke itself. Indeed, the syntax (lambda (f) n) by which we define le is analogous to (define f n) which, using primitive define, is already recursive. In order to achieve the same result without define, we only need to invoke Y on le, returning the desired recursive lambda expression len. But take a deep breath first!"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<Y, le> len;
	cout << "len = (Y le) = " << indent++ << endl << endl <<
		len() << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Do not look at len itself! Just keep in mind that we may now use it as a recursive lambda expression: invoking it on a list l returns the length of l,"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "(len ()) = " << _<len, _<> > () << endl;
	cout << "(len (a)) = " << _<len, _<a> > () << endl;
	cout << "(len (a b)) = " << _<len, _<a, b> > () << endl;
	cout << "(len (a b c)) = " << _<len, _<a, b, c> > () << endl;
	cout << "(len (a (b (a b)) ((c)) (d))) = " <<
		_<len, _<a, _<b, _<a, b> >, _<_<c> >, _<d> > > () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"We could equally say e.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "((Y le) ()) = " << _<_<Y, le>, _<> > () << endl;
	cout << "((Y le) (a)) = " << _<_<Y, le>, _<a> > () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"and so on. The result is not defined if l is an atom or a lambda expression:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "((Y le) Harry) = " << _<_<Y, le>, Harry> () << endl;

	cout << "((Y le) (lambda (x) ())) = " <<
		_<_<Y, le>, _<lambda, _<x>, _<> > > () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Y is a lambda expression using only primitive lambda in its body, and not primitive define. The latter is used to give Y its name rather than to recurse. We could as well use an unnamed lambda expression to achieve the same result with no use of define at all. In particular, Y is defined as follows:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << define <Y>::disp () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Do not attempt to invoke Y on Y itself!"
	<< endl;

//-----------------------------------------------------------------------------

	cout << endl <<
		"See also define, lambda."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
