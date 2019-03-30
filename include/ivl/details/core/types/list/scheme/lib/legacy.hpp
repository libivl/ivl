/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the nulls of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the nulls
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_LEGACY_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_LEGACY_HPP

#include <limits.h>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace scheme {

//-----------------------------------------------------------------------------

IVL_TOKEN(equal,          "equal?")

//-----------------------------------------------------------------------------

template <> struct define <equal> :
_<let_rec, _<
	_<e,
		_<lambda, _<e1, e2>, _<
			cond,
			_<_<_and, _<atom, e1>, _<atom, e2> >, _<eq, e1, e2> >,
			_<_<_or, _<atom, e1>, _<atom, e2> >, _false>,
			_<_else, _<l, e1, e2> >
		> >
	>,
	_<l,
		_<lambda, _<l1, l2>, _<
			cond,
			_<_<_and, _<null, l1>, _<null, l2> >, _true>,
			_<_<_or, _<null, l1>, _<null, l2> >, _false>,
			_<_else, _<_and,
				_<e, _<car, l1>, _<car, l2> >,
				_<l, _<cdr, l1>, _<cdr, l2> >
			> >
		> >
	>
>, e>
{ };

//-----------------------------------------------------------------------------

}  // namespace scheme
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_SCHEME_LIB_LEGACY_HPP
