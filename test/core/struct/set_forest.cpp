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

int main()
{
	using namespace std;
	using namespace ivl;

	
	set_forest <size_t, fun::id, true> ff;
	//set_forest <size_t, fun::id, true> fg(5);

	set_forest <> f(10);
	//set_forest <> error;
	f.join(2, 5);
	f.join(1, 8);
	f.join(5, 4);
	f.join(0, 3);
	f.join(8, 6);

	cout << _[f][&set_forest <>::set]((0, _, 9)) << endl;

	
}
