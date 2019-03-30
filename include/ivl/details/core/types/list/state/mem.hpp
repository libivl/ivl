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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STATE_MEM_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STATE_MEM_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename M>
struct mid { typedef M mem; };

template <typename T>
struct mem_of : mid <typename T::mem> { };

//-----------------------------------------------------------------------------

// skip irrelevant information from error messages
struct skip { };

//-----------------------------------------------------------------------------

template <typename T> struct above   { typedef T below; };
template <int N>      struct of_size { enum { size = N }; };

//-----------------------------------------------------------------------------

namespace ns {

namespace deny  { template <int P>                  struct read { }; }
namespace clear { template <int P>                  struct read  { }; }
namespace clear { template <int P, typename V>      struct write { }; }

}

//-----------------------------------------------------------------------------

template <typename X = term>
struct deny : mid <deny <X> >, above <deny <X> >, of_size <0>
{
	template <typename Y>
	struct nat : nested_nat <deny <X>, Y> { };

	template <int P>
	struct read : nat <ns::deny::read <P> > { };

	template <int P, typename V>
	struct write : deny <X> { };
};

template <typename O, typename I>
struct nested_deny : deny <intro::nested <O, I> > { };

//-----------------------------------------------------------------------------

struct clear : mid <clear>, above <clear>, of_size <0>
{
	template <typename X>
	struct nat : nested_nat <clear, X> { };

	template <typename X>
	struct deny : nested_deny <clear, X> { };

	template <int P>
 	struct read : nat <ns::clear::read <P> > { };

	template <int P, typename V>
	struct write : deny <ns::clear::write <P, skip> > { };
};

//-----------------------------------------------------------------------------

template <typename V, typename M>
struct grow : mid <grow <V, M> >, above <M>
{
	enum { size = M::size + 1 };

	template <int P>
	struct read : t_if <
		t_expr <P == size>, id <V>, typename M::template read <P>
	>::type { };

	template <int P, typename U>
	struct write : t_if <
		t_expr <P == size>, grow <U, M>,
		grow <V, typename M::template write <P, U>::mem>
	>::type { };
};

//-----------------------------------------------------------------------------

namespace intro {

template <> char template_t       <deny>                  ::name[] = "deny";
template <> char template_i       <ns::deny::read>        ::name[] = "read";
template <> char template_i       <ns::clear::read>       ::name[] = "read";
template <> char template_tt      <grow>                  ::name[] = "grow";

template <typename O> O& operator<< (O& o, name <skip>)       { return o << "[...]"; }
template <typename O> O& operator<< (O& o, name <clear>)      { return o << "clear"; }

}  // namespace intro

//-----------------------------------------------------------------------------

}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STATE_STATE_HPP
