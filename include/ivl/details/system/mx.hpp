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

#ifndef IVL_SYSTEM_MX_HPP
#define IVL_SYSTEM_MX_HPP

#include <string>

#ifdef IVL_MATLAB
#include "mex.h"

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

typedef int MX_SIZE_T;

namespace mx {

inline void error(char* s) { mexErrMsgTxt(s); }

inline double scalar(const mxArray* a) { return mxGetScalar(a); }

std::string text(const mxArray* in)
{	MX_SIZE_T len, status;
	char* out;
	len = (int)(mxGetM(in) * mxGetN(in)) + 1;
	out = (char*)mxCalloc(len, sizeof(char));
	status = mxGetString(in, out, len);
	if(status != 0)
		mexWarnMsgTxt("Not enough space. String is truncated.");
	return std::string(out);
}

template<class T>
inline
mxClassID type_class()
{
	return mxUNKNOWN_CLASS;
}

template<>
inline
mxClassID type_class<double>()
{
	return mxDOUBLE_CLASS;
}

template<>
inline
mxClassID type_class<float>()
{
	return mxSINGLE_CLASS;
}

template<>
inline
mxClassID type_class<int8_t>()
{
	return mxINT8_CLASS;
}

template<>
inline
mxClassID type_class<uint8_t>()
{
	return mxUINT8_CLASS;
}

template<>
inline
mxClassID type_class<int16_t>()
{
	return mxINT16_CLASS;
}

template<>
inline
mxClassID type_class<uint16_t>()
{
	return mxUINT16_CLASS;
}

template<>
inline
mxClassID type_class<int32_t>()
{
	return mxINT32_CLASS;
}

//-----------------------------------------------------------------------------

} /* namespace mx */

//-----------------------------------------------------------------------------

} /* namespace ivl */

//-----------------------------------------------------------------------------

#else

#if 0
struct mxArray {
};

namespace ivl {

typedef int MX_SIZE_T;

namespace mx {

} /* namespace mx */
} /* namespace ivl */
#endif

#endif

//-----------------------------------------------------------------------------

#endif // IVL_SYSTEM_MX_HPP
