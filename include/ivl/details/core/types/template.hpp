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

#ifndef IVL_CORE_DETAILS_TYPES_TEMPLATE_HPP
#define IVL_CORE_DETAILS_TYPES_TEMPLATE_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {

//-----------------------------------------------------------------------------

template <typename T, typename D>
struct type_base { typedef D type; };

//-----------------------------------------------------------------------------

// template classes mapped to structs
struct template_class_id { };

template <int NUM, typename DERIVED, typename ID = term>
struct template_class : public template_class_id
{
	const static int N = NUM;
	typedef DERIVED derived_type;
	typedef ID id_type;
	typedef template_class <NUM, DERIVED, ID> template_class_type;
};

//-----------------------------------------------------------------------------

// special case of template, assumed to take as input one type
// with variable number of arguments, e.g. a list
template <
	template <typename> class F,
	typename D, typename ID = term
>
struct template_var : public template_class <0, D, ID>
{
	typedef D type;
	template <class T>
	struct map : F <T> { };
};

//-----------------------------------------------------------------------------

template <
	template <typename> class F,
	typename D, typename ID = term
>
struct template1 : public template_class <1, D, ID>
{
	typedef D type;
	template <class T1>
	struct map : F <T1> { };
};

template <
	template <typename, typename> class F,
	typename D, typename ID = term
>
struct template2 : public template_class <2, D, ID>
{
	typedef D type;
	template <class T1, class T2>
	struct map : F <T1, T2> { };
};

template <
	template <typename, typename, typename> class F,
	typename D, typename ID = term
>
struct template3 : public template_class <3, D, ID>
{
	typedef D type;
	template <class T1, class T2, class T3>
	struct map : F <T1, T2, T3> { };
};

//-----------------------------------------------------------------------------

template <typename T>
struct type : public type_base <T, type <T> > { };

template <template <typename> class F>
struct tv : public template_var <F, tv <F> > { };

template <template <typename> class F>
struct tmp1 : public template1 <F, tmp1 <F> > { };

template <template <typename, typename> class F>
struct tmp2 : public template2 <F, tmp2 <F> > { };

template <template <typename, typename, typename> class F>
struct tmp3 : public template3 <F, tmp3 <F> > { };

//-----------------------------------------------------------------------------

} // namespace types

//-----------------------------------------------------------------------------

using types::type;

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_TEMPLATE_HPP
