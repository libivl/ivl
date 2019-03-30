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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_STREAM_ERROR_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_STREAM_ERROR_HPP

#include <typeinfo>

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {
namespace list_details {

//-----------------------------------------------------------------------------

template <typename T, bool DB = IVL_LIST_DB>
struct error { };

//-----------------------------------------------------------------------------

template <typename O, typename X>
O& operator<< (O& o, nat <X>) { return o << error <nat <X> > (); }

template <typename O, typename X>
O& operator<< (O& o, fail <X>) { return o << error <fail <X> > (); }

//-----------------------------------------------------------------------------

template <typename O, typename X>
O& operator<< (O& o, error <nat <X>, true>)
{
	return o << intro::type_name <nat <X> > ();
}

template <typename O, typename X>
O& operator<< (O& o, error <fail <X>, true>)
{
	return o << intro::type_name <fail <X> > ();
}

//-----------------------------------------------------------------------------

template <typename O, typename X>
O& operator<< (O& o, error <nat <X>, false>)
{
	return o << _white << "nat" << _green;
}

template <typename O, typename X>
O& operator<< (O& o, error <fail <X>, false>)
{
	return o << _white << "fail" << _green;
}

//-----------------------------------------------------------------------------

template <typename O, typename X>
O& operator<< (O& o, block <nat <X> >)
{
	return o << error <block <nat <X> > > ();
}

//-----------------------------------------------------------------------------

template <typename O, typename X>
O& operator<< (O& o, error <block <nat <X> >, true>)
{
	return o << std::endl << indent++ << !wrap << std::endl <<
		error <nat <X>, true> () << wrap << indent-- << std::endl;
}

template <typename O, typename X>
O& operator<< (O& o, error <block <nat <X> >, false>)
{
	return o << error <nat <X>, false> ();
}

//-----------------------------------------------------------------------------

namespace intro {

//-----------------------------------------------------------------------------

template <typename O, bool NL>
O& operator<< (O& o, type_name <nat <>, NL>)
{
	return o << template_t <nat>::name;
}

template <typename O, bool NL, typename X>
O& operator<< (O& o, type_name <nat <X>, NL>)
{
	return o << template_t <nat>::name << type_list_in <X, NL> ();
}

//-----------------------------------------------------------------------------

template <typename O, bool NL>
O& operator<< (O& o, type_name <fail <>, NL>)
{
	return o << template_t <fail>::name;
}

template <typename O, bool NL, typename X>
O& operator<< (O& o, type_name <fail <X>, NL>)
{
	return o << template_t <fail>::name << type_list_in <X, NL> ();
}

//-----------------------------------------------------------------------------

template <typename O, bool NL>
O& operator<< (O& o, type_name <deny <>, NL>)
{
	return o << template_t <deny>::name;
}

template <typename O, bool NL, typename X>
O& operator<< (O& o, type_name <deny <X>, NL>)
{
	return o << template_t <deny>::name << type_list_in <X, NL> ();
}

//-----------------------------------------------------------------------------

template <typename O, bool NL>
O& operator<< (O& o, type_name <null, NL>) { return o << name <null> (); }

template <typename O, bool NL, typename T>
O& operator<< (O& o, type_name <node <T>, NL>)
{
	return o << block <type_name <T, NL>, NL> ();
}

template <typename O, bool NL, typename T>
O& operator<< (O& o, type_name <inner <node <T> >, NL>)
{
	return o << type_name <T, NL> ();
}

template <typename O, bool NL, typename T, typename TN>
O& operator<< (O& o, type_name <node <T, TN>, NL>)
{
	return o << block <type_name <inner <node <T, TN> >, NL>, NL> ();
}

template <typename O, bool NL, typename T, typename TN>
O& operator<< (O& o, type_name <inner <node <T, TN> >, NL>)
{
	return o << type_name <T, NL> () << delim <NL> () <<
		type_name <inner <TN>, NL> ();
}

//-----------------------------------------------------------------------------

template <typename O, bool NL, typename T>
O& operator<< (O& o, block <type_name <T, NL>, NL>)
{
	return o << open <NL> () << type_name <T, NL> () << close <NL> ();
}

//-----------------------------------------------------------------------------

template <typename O, bool NL, template <typename> class F>
O& operator<< (O& o, type_name <scheme::op1 <F>, NL>)
{
	return o << scheme::op1 <F> ();
}

template <typename O, bool NL, template <typename, typename> class F>
O& operator<< (O& o, type_name <scheme::op2 <F>, NL>)
{
	return o << scheme::op2 <F> ();
}

//-----------------------------------------------------------------------------

}  // namespace intro
}  // namespace list_details
}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_LIST_STREAM_ERROR_HPP
