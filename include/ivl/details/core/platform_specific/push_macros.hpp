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


#ifdef _MSC_VER
#ifndef IVL_WIN32_HEADER_FILES_MACROS_PUSHED

#pragma pack(push,_CRT_PACKING)
#if defined(min)
#pragma push_macro("min")
#undef min
#define _POP_MIN
#endif

#if defined(max)
#pragma push_macro("max")
#undef max
#define _POP_MAX
#endif

#if defined(isinf)
#pragma push_macro("isinf")
#undef isinf
#define _POP_ISINF
#endif

#if defined(isnan)
#pragma push_macro("isnan")
#undef isnan
#define _POP_ISNAN
#endif

#define IVL_WIN32_HEADER_FILES_MACROS_PUSHED
#endif /* IVL_WIN32_HEADER_FILES_MACROS_PUSHED */
#endif /* _MSC_VER */

