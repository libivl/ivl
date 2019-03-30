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

#ifndef IVL_CORE_DETAILS_TYPES_ENTITY_HPP
#define IVL_CORE_DETAILS_TYPES_ENTITY_HPP

namespace ivl {

// ivl function argument list separator
namespace func_details { struct sep { }; }

// non-const reference asker
struct nc { };

namespace types {

// empty terminator struct
struct term { };

// struct passed as argument to differentiate overloaded functions
template<int N = 0>
struct code_word
{
	code_word() { }
};

// struct to become a substitute template base class that does nothing
template<class T>
struct nop_base { };

// used as an l-value with combination of r_if to disable/enable assignments
struct skip
{
	skip() {}
	template<class K>
	skip(const K& x) {}
	//template<class K>
	//const skip& operator=(const K& x) const { return *this; }
	skip& operator=(const skip& x) { return *this; }
	const skip& operator=(const skip& x) const { return *this; }

	// iavr: make operator[] work for tuples
	typedef skip reference;
	typedef skip const_reference;
	template<class P>
	skip& operator[](P p) { return *this; }
	template<class P>
	const skip& operator[](P p) const { return *this; }

	// iavr: make resize() work for tuples
	template<class S>
	void resize(S s) { }
};

// argument to disable function
struct invalid_arg
{
    template<class X>
    invalid_arg(X){}
};

// argument to disable function, when used many times
template<int N>
struct invalid_arg_n
{
    template<class X>
    invalid_arg_n(X){}
};
template<class T>
struct invalid_arg_t
{
    template<class X>
    invalid_arg_t(X){}
};

// disabled type
class not_a_type
{
private:
	not_a_type() {}
};

} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_ENTITY_HPP
