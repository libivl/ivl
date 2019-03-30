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

//-----------------------------------------------------------------------------

/*! \file exception.hpp
    \brief Defines the IVL Exceptions.

    This file defines all the exceptions thrown by the IVL library.
*/

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_DETAILS_DEBUG_EXCEPTION_HPP
#define IVL_CORE_DETAILS_DEBUG_EXCEPTION_HPP

//-----------------------------------------------------------------------------

#include "../platform_specific/msc_warnings.hpp"

#include <exception>
#include <cassert>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

#ifdef _DEBUG

#ifndef THROW_EXCEPTION
#define CHECK(expr, excep) \
	assert(expr);
#else
#define CHECK(expr, excep) \
	assert(expr); \
	if(expr == false) \
	throw(excep);
#endif
#define CHECK_RELEASE(expr, exec) \
	if(expr == false) \
	throw(excep);
#define CHECK_LINA(expr, exec) \
	if(expr == false) \
	throw(excep);
#define CHECK_OPENCV(expr, exec) \
	if(expr == false) \
	throw(excep);

#else

#define CHECK(expr, excep) ;

#endif

//TODO: implement the throw decision mechanism.
/* The rules are:

We have 1 switch for each expression type, that enables/disables it
in THROW_RELEASE mode.
We have 1 switch for each extra category, LINA, OPENCV.
We have 1 switch for simple CHECK that enables/disable it. That switch
is on by default in the DEBUG mode.

*/
// These switches should change to "throw()" when the corresponding switch is set to off.
#define __dbg_throw(A) throw(A)
#define __rel_throw(A) throw(A)
#define __lina_throw(A) throw(A)
#define __opencv_throw(A) throw(A)


class exception : public std::exception
{
public :
	virtual const char* what() const throw()
	{
		return "An IVL exception occured!";
	}
};

class einvalid : public exception
{
public :
	virtual const char* what() const throw()
	{
		// A pointer has NULL.
		return "Pointer value is not valid.";
	}

};

// ?? What if array is empty but non-empty is needed?
// ?? What is array is <3 but >=3 is needed?
// erange? no. eshape? it is not the exact exception
// i probably need an esize
//TODO: use esize.

class erange : public exception
{
public :
	virtual const char* what() const throw()
	{
		// We are trying to access out of the array bounds.
		return "Value is out of range.";
	}

};

class eshape : public exception
{
public :
	virtual const char* what() const throw()
	{
		return "The shape of these arrays is not compatible for this kind of operation.";
	}

};

class etype : public exception
{
public :
	virtual const char* what() const throw()
	{
		// When communicating with another library that has abstract types,
		// it is possible to have this kind of exceptions
		return "The data type of these arrays is not compatible for this kind of operation.";
	}

};

class edims : public exception
{
public :
	virtual const char* what() const throw()
	{
		return "Incorrect number of dimensions in array.";
	}

};

class ecomp : public exception
{
public :
	virtual const char* what() const throw()
	{
		// Generic exception which means that an expression cannot be computed,
		// probably because of the argument values.
		return "Illegal computation";
	}
};

class esystem : public exception
{
public:
	virtual const char* what() const throw()
	{
		// Any kind of error that doesn't depend on the CPU, but on any other
		// kind of i/o, including memory allocation or other system calls failure.
		return "System error";
	}
};

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_DEBUG_EXCEPTION_HPP
