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
	using ivl::types::scheme::equal;

	cout << wrap << endl << title <<
		"lambda - construct lambda expression"
	<< endl;

	cout << endl <<
		syntax << "le = (lambda (a_1 .. a_N) b)" <<
		body << " returns a lambda expression le with arguments a_1, .., a_N, assumed to be atoms, and body b, assumed to be a list. The number of arguments N is called the arity of le. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<lambda, _<x>, _<eq, c, x> > le;
	cout << "le = (lambda (x) (eq? c x)) = " <<
		indent++ << endl << endl << le () << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"constructs a lambda expression with one argument, x, which returns true if and only if x is an atom and equals c. In the body b = (eq? c x), c is treated as a free variable and x as a bound variable, because x occurs as an argument in (lambda (x) b). In a lambda expression le with arguments a_1, .., a_N and body b, the bound variable assigned to argument a_n is represented by n. This is done by creating a list l that is b with all occurrences of a_n replaced by n for all n in {1, .., N}. Then, le is represented by (lambda [N] l)."
	<< endl;

//-----------------------------------------------------------------------------

	cout << endl <<
		syntax << "r = (le v_1 .. v_N)" <<
		body << " invokes lambda expression le with argument values v_1, .., v_N, i.e., creates a list l that is the body of le with all occurrences of its n-th argument replaced by expression v_n for all n in {1, .., N} and returns expression r that is list l evaluated. We also say this syntax invokes le on v_1, .., v_N. E.g."
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "(le a) = " << _<le, a> () << endl;
	cout << "(le b) = " << _<le, b> () << endl;
	cout << "(le c) = " << _<le, c> () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"This is equivalent to using the unnamed lambda construct directly:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "((lambda (x) (eq? c x)) a) = " <<
		_<_<lambda, _<x>, _<eq, c, x> >, a> () << endl;

	cout << "((lambda (x) (eq? c x)) b) = " <<
		_<_<lambda, _<x>, _<eq, c, x> >, b> () << endl;

	cout << "((lambda (x) (eq? c x)) c) = " <<
		_<_<lambda, _<x>, _<eq, c, x> >, c> () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"The result is not defined if a lambda expression is invoked on a number of arguments that does not match its definition:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "((lambda (x) (eq? c x))) = " <<
		_<_<lambda, _<x>, _<eq, c, x> > > () << endl;

	cout << "((lambda (x) (eq? c x)) a b) = " <<
		_<_<lambda, _<x>, _<eq, c, x> >, a, b> () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << endl <<
		title << "Lambda returning lambda. " <<
		body << "A lambda expression may be used exactly as any other expression, i.e., atom or list. For instance, a lambda expression may contain one or more nested lambda expressions, or return one:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<lambda, _<c>, _<lambda, _<x>, _<eq, c, x> > > eq_c;
	cout << "eq_c? = (lambda (c) (lambda (x) (eq? c x))) = " <<
		indent++ << endl << endl << eq_c() << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"in which case c becomes a bound variable as well in body b = (lambda (x) (eq? c x))) because c occurs as an argument in (lambda (c) b). The argument numbers of the inner lambda expression are increased by 1, which is the arity of the outer one. Invoking the outer lambda expression on an atom yields the inner one,"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<eq_c, salad> eq_salad;
	cout << "eq_salad? = (eq_c? salad) = " <<
		indent++ << endl << endl << eq_salad() << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"at the same time decreasing the argument numbers back. Now, invoking the latter lambda expression on another atom yields a concrete result,"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "(eq-salad? salad) = " << _<eq_salad, salad> () << endl;
	cout << "(eq-salad? tuna) = " << _<eq_salad, tuna> () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"Again, this is equivalent to"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "((eq-c? salad) salad) = " << _<_<eq_c, salad>, salad> () << endl;
	cout << "((eq-c? salad) tuna) = " << _<_<eq_c, salad>, tuna> () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"or even to"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "(((lambda (c) (lambda (x) (eq? c x))) salad) salad) = " <<
		_<_<_<lambda, _<c>, _<lambda, _<x>, _<eq, c, x> > >, salad>, salad> () <<
		endl;

	cout << "(((lambda (c) (lambda (x) (eq? c x))) salad) tuna) = " <<
		_<_<_<lambda, _<c>, _<lambda, _<x>, _<eq, c, x> > >, salad>, tuna> () <<
		endl;

//-----------------------------------------------------------------------------

	cout << !indent << endl << body <<
		"This alternative way of expressing e.g. question (eq? salad tuna) is an example of partial function application or currying."
	<< endl;

//-----------------------------------------------------------------------------

	cout << endl <<
		title << "Invoking lambda on lambda. " <<
		body << "As another example, a lambda expression may be invoked on yet another lambda expression. This may be used to generalize test eq? of the previous example to an arbitrary test t:"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<lambda , _<t>, _<lambda, _<c>, _<lambda, _<x>, _<t, c, x> > > >
		eq_t;

	cout << "eq_t? = (lambda (t?) (lambda (c) (lambda (x) (t? c x)))) = " <<
		indent++ << endl << endl << eq_t() << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"If we define this test e.g. as"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<lambda, _<a, b>, _<equal, _<a, a>, b> > twice;
	cout << "twice? = (lambda (a b) (equal? (a a) b)) = " <<
		indent++ << endl << endl << twice() << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"and then use it as the value of t? in eq_t?,"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	typedef _<eq_t, twice> eq_twice;
	cout << "eq_twice? = (eq_t twice?) = " <<
		indent++ << endl << endl << eq_twice() << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"the argument numbers in twice? when inside lambda expression le = (eq_t twice?) are increased by 2, which is the depth of twice? in le. Seeing the body of le as a tree, the depth is defined as the sum of arities of nested lambda expressions in the path from the root to the occurrence of twice?. Hence, when it is time for twice? to be invoked, its argument numbers will have decreased so that the number of the first argument is again 1. It now follows that"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "(eq_twice? bye) = " <<
		indent++ << endl << endl << _<eq_twice, bye> () << indent-- << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"implying that"
	<< endl << indent << sample << endl;

//-----------------------------------------------------------------------------

	cout << "((eq_twice? bye) hello) = " << _<_<eq_twice, bye>, hello> () << endl;
	cout << "((eq_twice? bye) bye) = " << _<_<eq_twice, bye>, bye> () << endl;

	cout << "((eq_twice? bye) (bye bye)) = " <<
		_<_<eq_twice, bye>, _<bye, bye> > () << endl;

//-----------------------------------------------------------------------------

	cout << !indent << body << endl <<
		"See also define, Y."
	<< endl << endl;
}

//-----------------------------------------------------------------------------

#include "../list_end.hpp"
