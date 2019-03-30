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

#ifndef IVL_DOC_CORE_TYPE_DEF_HPP
#define IVL_DOC_CORE_TYPE_DEF_HPP

#include <vector>
#include <list>

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {

//-----------------------------------------------------------------------------

namespace fp {

using namespace types::constants;

template <typename T>
struct inf_max : public c_sig <T ()>::template function <ivl::inf_max <T> > { };

template <typename T>
struct inf_min : public c_sig <T ()>::template function <ivl::inf_min <T> > { };

}  // namespace fp

//-----------------------------------------------------------------------------

namespace details {

using namespace std;
using std::list;

//-----------------------------------------------------------------------------

template <> struct name <root>                      { const char* operator()() const { return "index"; } };

//-----------------------------------------------------------------------------

template <> struct name <fun::help>                 { const char* operator()() const { return "help"; } };

template <> struct name <fun::lt>                   { const char* operator()() const { return "lt"; } };
template <> struct name <fun::gt>                   { const char* operator()() const { return "gt"; } };

template <> struct name <fun::max>                  { const char* operator()() const { return "max"; } };
template <> struct name <fun::min>                  { const char* operator()() const { return "min"; } };
template <> struct name <fun::extrema>              { const char* operator()() const { return "extrema"; } };
template <> struct name <fun::arg_max>              { const char* operator()() const { return "arg_max"; } };
template <> struct name <fun::arg_min>              { const char* operator()() const { return "arg_min"; } };

//-----------------------------------------------------------------------------

template <> struct name <tfun1 <fp::inf_max> >      { const char* operator()() const { return "inf_max"; } };
template <> struct name <tfun1 <fp::inf_min> >      { const char* operator()() const { return "inf_min"; } };

//-----------------------------------------------------------------------------

template <> struct name <tmp2 <array> >             { const char* operator()() const { return "array"; } };
template <> struct name <tmp2 <array_nd> >          { const char* operator()() const { return "array_nd"; } };
template <> struct name <dimension>                 { const char* operator()() const { return "dimension"; } };
template <> struct name <some>                      { const char* operator()() const { return "some"; } };

template <> struct name <tmp2 <vector> >            { const char* operator()() const { return "vector"; } };
template <> struct name <tmp2 <list> >              { const char* operator()() const { return "list"; } };

template <> struct name <size_t>                    { const char* operator()() const { return "size_t"; } };

//-----------------------------------------------------------------------------

template <> struct is_ivl <tfun1 <fp::inf_max> >           : public t_true { };
template <> struct is_ivl <tfun1 <fp::inf_min> >           : public t_true { };

//-----------------------------------------------------------------------------

template <> struct is_ivl <tmp2 <array> >                  : public t_true { };
template <> struct is_ivl <tmp2 <array_nd> >               : public t_true { };
template <> struct is_ivl <dimension>                      : public t_true { };
template <> struct is_ivl <some>                           : public t_true { };

template <> struct is_std <tmp2 <std::vector> >            : public t_true { };
template <> struct is_std <tmp2 <std::list> >              : public t_true { };

//-----------------------------------------------------------------------------

namespace inst {

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) tfun1 <fp::inf_max>        f_inf_max;
static __attribute__ ((unused)) tfun1 <fp::inf_min>        f_inf_min;

//-----------------------------------------------------------------------------

static __attribute__ ((unused)) tmp2 <array>               t_array;
static __attribute__ ((unused)) tmp2 <array_nd>            t_array_nd;
static __attribute__ ((unused)) type <dimension>           t_dimension;
static __attribute__ ((unused)) type <some>                t_some;

static __attribute__ ((unused)) tmp2 <vector>              t_vector;
static __attribute__ ((unused)) tmp2 <list>                t_list;

static __attribute__ ((unused)) type <size_t>              t_size_t;

//-----------------------------------------------------------------------------

}  // namespace inst

//-----------------------------------------------------------------------------

}  // namespace details

using namespace details::inst;
using details::name;

//-----------------------------------------------------------------------------

}  // namespace doc

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_DOC_CORE_TYPE_DEF_HPP
