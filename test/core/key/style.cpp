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

//-----------------------------------------------------------------------------

using namespace std;
using namespace ivl;

template <typename T>
void f(const T& v)
{
	using types::number;
	cout << "v : " << v(number <0>()) << " " << v(number <1>()) << " " << v(number <2>()) << endl;

	using keys::at;
	cout << "v : " << at <0>(v) << " " << at <1>(v) << " " << at <2>(v) << endl;
}

//-----------------------------------------------------------------------------

int main()
{
	typedef array <int> A;
	keys::null opt;

	f((opt,3,"hello, ",A(arr[_,4,3,2,1,0])));
	cout << endl;

	cout << "opt1 : " << (opt,3,"hello, ",A(arr[_,4,3,2,1,0])) << endl;
	cout << "opt2 : " << (opt,3.14,'A',string("world!")) << endl;
	cout << endl;

	style <ostream> s1 = (opt,3,"hello, ",A(arr[_,4,3,2,1,0]));
	style <ostream> s2 = (opt,3.14,'A',string("world!"));
	cout << "s1 : " << s1 << endl << "s2 : " << s2 << endl;
	cout << endl;

	style <ostream> s = (opt,s1,s2,complex <double>(0,1));
	cout << "s : " << s << endl;
	cout << "s : " << (opt,s1,s2,complex <double>(0,1)) << endl;
	cout << "s : " << (opt,
		(opt,3,"hello, ",A(arr[_,4,3,2,1,0])),
		(opt,3.14,'A',string("world!")),
		complex <double>(0,1)
	) << endl;
	cout << endl;
}