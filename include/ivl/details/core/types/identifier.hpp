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

#ifndef IVL_CORE_DETAILS_TYPES_IDENTIFIER_HPP
#define IVL_CORE_DETAILS_TYPES_IDENTIFIER_HPP

namespace ivl {
namespace types {

//These are also called 'hidden tags'.
//They are base classes of other classes that need to be identified as
// something. The classes that do have one of these base classes are
// considered to have the actual 'hidden tag'. It is like having
// a tag with typedef, like the iterators case, however, not all classes
// must have a typedef to conform with any specs.
// Instead the hidden tag is searched to see if it is a base class of
// the questioned class, by using a boost-like technique involving
// a conversion operator, inheritance and sizeof combination trick.
// this check is made by the types::is_base_of<> class.

struct scalar_identifier { };

struct copyscalar_identifier { };

struct tuple_identifier { };

struct array_identifier { };

struct array_is_referer_identifier { };

//struct subreference_identifier { }; //to be removed

struct pointer_based_iterator_identifier { }; // note: care because this tag
// may coexist with pointer_range_based_iterator_identifier tag in which case
// only the latter is valid.
struct pointer_range_based_iterator_identifier { };
struct ivl_array_reference_based_iterator_identifier { };
struct past_end_capable_iterator_identifier { };

// it is a tag for iterators that tells us that iterator::iter_border_walker
// is defined. otherwise ptrdiff_t is presumed.
struct border_walker_iterator_identifier { };
// tag to disable border_walker_iterator_identifier on child classes.
struct no_border_walker_iterator_identifier { };

// it is a tag for iterators that tells us that iterator::iter_nd_border_walker
// is defined. otherwise ptrdiff_t is presumed.
struct nd_border_walker_iterator_identifier { };


struct rvalue_identifier { };

// tag loop with write-write option
struct loop_ww_identifier { };

// tag to detect all the types of array that have the default implementation
template <class A>
struct normal_array_identifier { };

// arguments of operators << and >> as implemented via ivl::stream_out,
// ivl::stream_in, supporting streams other than std::basic_ios and
// different priorities in overloading
struct stream_identifier     { };  // any s in expression "s << x" or "s >> x"
struct streamable_identifier { };  // any x in expression "s << x" or "s >> x"

} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_IDENTIFIER_HPP
