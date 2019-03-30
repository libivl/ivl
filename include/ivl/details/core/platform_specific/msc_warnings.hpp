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
#pragma warning(disable: 4099)
#pragma warning(disable: 4221)
#pragma warning(disable: 4006)
#pragma warning(disable: 4288)
#pragma warning(disable: 4522)

// for specific exceptions. do think about this and decide
// whether specific exceptions are going to be used
// on function declarations...
#pragma warning( disable : 4290 )

//conversion ptrdiff_t to int
#pragma warning(disable: 4244 )

//conversion size_t to unsigned int (note : i maybe want to check this again)
#pragma warning(disable: 4267 )

//decorated name length exceeded, name was truncated
#pragma warning(disable: 4503 )

//TODO: put me somewhere else!
#define __attribute__(X)

//TODO: put me somewhere else!
#ifdef _ivl_STATIC_
#define _ivl_export_
#else
#ifdef _ivl_EXPORTS_
#define _ivl_export_ __declspec(dllexport)
#else
#define _ivl_export_ __declspec(dllimport)
#endif
#endif

//TODO: put me somewhere else!
#ifdef _ivlcv_STATIC_
#define _ivlcv_export_
#else
#ifdef _ivlcv_EXPORTS_
#define _ivlcv_export_ __declspec(dllexport)
#else
#define _ivlcv_export_ __declspec(dllimport)
#endif
#endif

//TODO: put me somewhere else!
#ifdef _ivllina_STATIC_
#define _ivllina_export_
#else
#ifdef _ivllina_EXPORTS_
#define _ivllina_export_ __declspec(dllexport)
#else
#define _ivllina_export_ __declspec(dllimport)
#endif
#endif

//TODO: put me somewhere else!
#ifdef _ivlqt_STATIC_
#define _ivlqt_export_
#else
#ifdef _ivlqt_EXPORTS_
#define _ivlqt_export_ __declspec(dllexport)
#else
#define _ivlqt_export_ __declspec(dllimport)
#endif
#endif

#endif /* _MSC_VER */

//TODO: me too!
#ifndef _MSC_VER
#define _ivl_export_
#define _ivlcv_export_
#define _ivllina_export_
#define _ivlqt_export_
#endif //_MSC_VER

