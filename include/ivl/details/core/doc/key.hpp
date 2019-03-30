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

#ifndef IVL_CORE_DETAILS_DOC_KEY_HPP
#define IVL_CORE_DETAILS_DOC_KEY_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

template <> struct is_id <ivl::key::html>  : public types::t_true { };
template <> struct is_id <ivl::key::tex>   : public types::t_true { };
template <> struct is_id <ivl::key::txt>   : public types::t_true { };

}  // namespace keys

//-----------------------------------------------------------------------------

namespace doc {

//-----------------------------------------------------------------------------

template <typename K>
struct type_def : public keys::group <K, type_def, true> { };

template <typename K>
struct fun_def : public keys::group <K, fun_def, true> { };

//-----------------------------------------------------------------------------

namespace key {

using key_grp::style;

//-----------------------------------------------------------------------------

struct page       : public style <page>         { using KEY::operator=; };
struct file       : public style <file>         { using KEY::operator=; };
struct nline      : public style <nline>        { using KEY::operator=; };
struct para       : public style <para>         { using KEY::operator=; };
struct head1      : public style <head1>        { using KEY::operator=; };
struct head2      : public style <head2>        { using KEY::operator=; };
struct head3      : public style <head3>        { using KEY::operator=; };
struct tabular    : public style <tabular>      { using KEY::operator=; };
struct row        : public style <row>          { using KEY::operator=; };
struct label      : public style <label>        { using KEY::operator=; };
struct desc       : public style <desc>         { using KEY::operator=; };

struct title      : public style <title>        { using KEY::operator=; };
struct body       : public style <body>         { using KEY::operator=; };
struct syntax     : public style <syntax>       { using KEY::operator=; };
struct t_ivl      : public style <t_ivl>        { using KEY::operator=; };
struct code       : public style <code>         { using KEY::operator=; };
struct lst        : public style <lst>          { using KEY::operator=; };
struct out        : public style <out>          { using KEY::operator=; };
struct type       : public style <type>         { using KEY::operator=; };
struct func       : public style <func>         { using KEY::operator=; };
struct emph       : public style <emph>         { using KEY::operator=; };
struct alert      : public style <alert>        { using KEY::operator=; };

struct in         : public style <in>           { using KEY::operator=; };
struct disp       : public style <disp>         { using KEY::operator=; };
struct sample     : public style <sample>       { using KEY::operator=; };
struct listing    : public style <listing>      { using KEY::operator=; };
struct output     : public style <output>       { using KEY::operator=; };
struct todo       : public style <todo>         { using KEY::operator=; };

//-----------------------------------------------------------------------------

struct                       any_type   : public type_def <any_type>          { using KEY::operator=; };
template <typename T> struct ivl_type   : public type_def <ivl_type <T> >     { using type_def <ivl_type <T> >::operator=; };
template <typename T> struct std_type   : public type_def <std_type <T> >     { using type_def <std_type <T> >::operator=; };
template <typename T> struct num_type   : public type_def <num_type <T> >     { using type_def <num_type <T> >::operator=; };

template <typename T> struct ivl_fun    : public fun_def <ivl_fun <T> >       { using fun_def <ivl_fun <T> >::operator=; };
template <typename T> struct std_fun    : public fun_def <std_fun <T> >       { using fun_def <std_fun <T> >::operator=; };

//-----------------------------------------------------------------------------

}  // namespace key

//-----------------------------------------------------------------------------

static __attribute__ ((unused))  key::page             page;
static __attribute__ ((unused))  key::file             file;
static __attribute__ ((unused))  key::nline            nline;
static __attribute__ ((unused))  key::para             para;
static __attribute__ ((unused))  key::head1            head1;
static __attribute__ ((unused))  key::head2            head2;
static __attribute__ ((unused))  key::head3            head3;
static __attribute__ ((unused))  key::tabular          tabular;
static __attribute__ ((unused))  key::row              row;
static __attribute__ ((unused))  key::label            label;
static __attribute__ ((unused))  key::desc             desc;

static __attribute__ ((unused))  key::title            title;
static __attribute__ ((unused))  key::body             body;
static __attribute__ ((unused))  key::syntax           syntax;
static __attribute__ ((unused))  key::t_ivl            t_ivl;
static __attribute__ ((unused))  key::code             code;
static __attribute__ ((unused))  key::lst              lst;
static __attribute__ ((unused))  key::out              out;
static __attribute__ ((unused))  key::type             type;
static __attribute__ ((unused))  key::func             func;
static __attribute__ ((unused))  key::emph             emph;
static __attribute__ ((unused))  key::alert            alert;

//-----------------------------------------------------------------------------

static __attribute__ ((unused))  key::in               in;
static __attribute__ ((unused))  key::disp             disp;
static __attribute__ ((unused))  key::sample           sample;
static __attribute__ ((unused))  key::listing          listing;
static __attribute__ ((unused))  key::output           output;
static __attribute__ ((unused))  key::todo             todo;

//-----------------------------------------------------------------------------

namespace details {

namespace ikey = ivl::key;
using namespace keys::all;
using keys::id;
using keys::mod;
using keys::off;
using keys::lists::_;
using std::string;

namespace device {

using types::enable_if;
using doc::type;

}  // namespace device

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace doc

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_DOC_KEY_HPP
