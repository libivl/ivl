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

#ifndef IVL_CORE_DETAILS_KEY_KEY_DEF_HPP
#define IVL_CORE_DETAILS_KEY_KEY_DEF_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace key_grp {

template <typename K> struct color : public ::ivl::keys::group <K, color>       { };
template <typename K> struct style : public ::ivl::keys::group <K, style, true> { };

}  // namespace key_grp

//-----------------------------------------------------------------------------

namespace key {

//-----------------------------------------------------------------------------

struct ansi           : public ::ivl::keys::     key     <ansi>            { using KEY::operator=; };
struct arr            : public ::ivl::keys::     key     <arr>             { using KEY::operator=; };
struct arg            : public ::ivl::keys::     key     <arg>             { using KEY::operator=; };
struct arg_max        : public ::ivl::keys::     key     <arg_max>         { using KEY::operator=; };
struct arg_min        : public ::ivl::keys::     key     <arg_min>         { using KEY::operator=; };
struct asc            : public ::ivl::keys::     key     <asc>             { using KEY::operator=; };
struct assign         : public ::ivl::keys::     key     <assign>          { using KEY::operator=; };
struct begin          : public ::ivl::keys::     key     <begin>           { using KEY::operator=; };
struct black          : public ::ivl::key_grp::  color   <black>           { using KEY::operator=; };
struct blue           : public ::ivl::key_grp::  color   <blue>            { using KEY::operator=; };
struct bright         : public ::ivl::keys::     key     <bright>          { using KEY::operator=; };
struct comb           : public ::ivl::keys::     key     <comb>            { using KEY::operator=; };
struct comp           : public ::ivl::keys::     key     <comp>            { using KEY::operator=; };
struct cond           : public ::ivl::keys::     key     <cond>            { using KEY::operator=; };
struct cyan           : public ::ivl::key_grp::  color   <cyan>            { using KEY::operator=; };
struct def            : public ::ivl::keys::     key     <def>             { using KEY::operator=; };
struct desc           : public ::ivl::keys::     key     <desc>            { using KEY::operator=; };
struct elem           : public ::ivl::keys::     key     <elem>            { using KEY::operator=; };
struct end            : public ::ivl::keys::     key     <end>             { using KEY::operator=; };
struct extrema        : public ::ivl::keys::     key     <extrema>         { using KEY::operator=; };
struct field          : public ::ivl::keys::     key     <field>           { using KEY::operator=; };
struct filter         : public ::ivl::keys::     key     <filter>          { using KEY::operator=; };
struct first          : public ::ivl::keys::     key     <first>           { using KEY::operator=; };
struct flip           : public ::ivl::keys::     key     <flip>            { using KEY::operator=; };
struct free           : public ::ivl::keys::     key     <free>            { using KEY::operator=; };
struct from           : public ::ivl::keys::     key     <from>            { using KEY::operator=; };
struct fwd            : public ::ivl::keys::     key     <fwd>             { using KEY::operator=; };
struct green          : public ::ivl::key_grp::  color   <green>           { using KEY::operator=; };
struct heap           : public ::ivl::keys::     key     <heap>            { using KEY::operator=; };
struct help           : public ::ivl::keys::     key     <help>            { using KEY::operator=; };
struct html           : public ::ivl::keys::     key     <html>            { using KEY::operator=; };
struct in             : public ::ivl::keys::     key     <in>              { using KEY::operator=; };
struct indent         : public ::ivl::keys::     key     <indent>          { using KEY::operator=; };
struct last           : public ::ivl::keys::     key     <last>            { using KEY::operator=; };
struct len            : public ::ivl::keys::     key     <len>             { using KEY::operator=; };
struct magenta        : public ::ivl::key_grp::  color   <magenta>         { using KEY::operator=; };
struct max            : public ::ivl::keys::     key     <max>             { using KEY::operator=; };
struct merge          : public ::ivl::keys::     key     <merge>           { using KEY::operator=; };
struct min            : public ::ivl::keys::     key     <min>             { using KEY::operator=; };
struct nl             : public ::ivl::keys::     key     <nl>              { using KEY::operator=; };
struct normal         : public ::ivl::keys::     key     <normal>          { using KEY::operator=; };
struct off            : public ::ivl::keys::     key     <off>             { using KEY::operator=; };
struct ord            : public ::ivl::keys::     key     <ord>             { using KEY::operator=; };
struct out            : public ::ivl::keys::     key     <out>             { using KEY::operator=; };
struct par            : public ::ivl::keys::     key     <par>             { using KEY::operator=; };
struct puff           : public ::ivl::keys::     key     <puff>            { using KEY::operator=; };
struct red            : public ::ivl::key_grp::  color   <red>             { using KEY::operator=; };
struct ref            : public ::ivl::keys::     key     <ref>             { using KEY::operator=; };
struct reset          : public ::ivl::keys::     key     <reset>           { using KEY::operator=; };
struct rev            : public ::ivl::keys::     key     <rev>             { using KEY::operator=; };
struct sep            : public ::ivl::keys::     key     <sep>             { using KEY::operator=; };
struct step           : public ::ivl::keys::     key     <step>            { using KEY::operator=; };
struct swp            : public ::ivl::keys::     key     <swp>             { using KEY::operator=; };
struct sz             : public ::ivl::keys::     key     <sz>              { using KEY::operator=; };
struct tab            : public ::ivl::keys::     key     <tab>             { using KEY::operator=; };
struct tex            : public ::ivl::keys::     key     <tex>             { using KEY::operator=; };
struct to             : public ::ivl::keys::     key     <to>              { using KEY::operator=; };
struct txt            : public ::ivl::keys::     key     <txt>             { using KEY::operator=; };
struct underline      : public ::ivl::keys::     key     <underline>       { using KEY::operator=; };
struct val            : public ::ivl::keys::     key     <val>             { using KEY::operator=; };
struct verb           : public ::ivl::keys::     key     <verb>            { using KEY::operator=; };
struct vspace         : public ::ivl::keys::     key     <vspace>          { using KEY::operator=; };
struct yellow         : public ::ivl::key_grp::  color   <yellow>          { using KEY::operator=; };
struct yn             : public ::ivl::keys::     key     <yn>              { using KEY::operator=; };
struct white          : public ::ivl::key_grp::  color   <white>           { using KEY::operator=; };
struct width          : public ::ivl::key_grp::  color   <width>           { using KEY::operator=; };
struct wrap           : public ::ivl::keys::     key     <wrap>            { using KEY::operator=; };

//-----------------------------------------------------------------------------

}  // namespace key

//-----------------------------------------------------------------------------

#ifndef IVL_LISTIE
static    __attribute__ ((unused))  key::ansi             ansi;
// static __attribute__ ((unused))  key::arr              arr;           // @ core/func/arr.hpp
static    __attribute__ ((unused))  key::arg              arg;
// static __attribute__ ((unused))  key::arg_max          arg_max;       // @ core/func/extrema.hpp
// static __attribute__ ((unused))  key::arg_min          arg_min;       // @ core/func/extrema.hpp
static    __attribute__ ((unused))  key::asc              asc;
static    __attribute__ ((unused))  key::assign           assign;
static    __attribute__ ((unused))  key::begin            begin;
static    __attribute__ ((unused))  key::black            black;
static    __attribute__ ((unused))  key::blue             blue;
static    __attribute__ ((unused))  key::bright           bright;
static    __attribute__ ((unused))  key::comb             comb;
static    __attribute__ ((unused))  key::comp             comp;
static    __attribute__ ((unused))  key::cond             cond;
static    __attribute__ ((unused))  key::cyan             cyan;
static    __attribute__ ((unused))  key::def              def;
static    __attribute__ ((unused))  key::desc             desc;
static    __attribute__ ((unused))  key::elem             elem;
static    __attribute__ ((unused))  key::end              end;
// static __attribute__ ((unused))  key::extrema          extrema;       // @ core/func/extrema.hpp
static    __attribute__ ((unused))  key::field            field;
static    __attribute__ ((unused))  key::filter           filter;
// static __attribute__ ((unused))  key::first            first;         // @ func/first.hpp
// static __attribute__ ((unused))  key::flip             flip;          // @ func/flip.hpp
static    __attribute__ ((unused))  key::free             free;
// static __attribute__ ((unused))  key::from             from;          // @ func/to.hpp
static    __attribute__ ((unused))  key::fwd              fwd;
static    __attribute__ ((unused))  key::green            green;
static    __attribute__ ((unused))  key::heap             heap;
// static __attribute__ ((unused))  key::help             help;          // @ doc/help.hpp
static    __attribute__ ((unused))  key::html             html;
// static __attribute__ ((unused))  key::in               in;            // @ func/to.hpp
static    __attribute__ ((unused))  key::indent           indent;
// static __attribute__ ((unused))  key::last             last;          // @ func/last.hpp
static    __attribute__ ((unused))  key::len              len;
static    __attribute__ ((unused))  key::magenta          magenta;
// static __attribute__ ((unused))  key::max              max;           // @ core/func/extrema.hpp
static    __attribute__ ((unused))  key::merge            merge;
// static __attribute__ ((unused))  key::min              min;           // @ core/func/extrema.hpp
static    __attribute__ ((unused))  key::nl               nl;
static    __attribute__ ((unused))  key::normal           normal;
static    __attribute__ ((unused))  key::off              off;
static    __attribute__ ((unused))  key::ord              ord;
// static __attribute__ ((unused))  key::out              out;           // @ func/to.hpp
static    __attribute__ ((unused))  key::par              par;
static    __attribute__ ((unused))  key::puff             puff;
static    __attribute__ ((unused))  key::red              red;
static    __attribute__ ((unused))  key::ref              ref;
static    __attribute__ ((unused))  key::reset            reset;
static    __attribute__ ((unused))  key::rev              rev;
static    __attribute__ ((unused))  key::sep              sep;
static    __attribute__ ((unused))  key::step             step;
static    __attribute__ ((unused))  key::swp              swp;
static    __attribute__ ((unused))  key::sz               sz;
static    __attribute__ ((unused))  key::tab              tab;
static    __attribute__ ((unused))  key::tex              tex;
// static __attribute__ ((unused))  key::to               to;            // @ func/to.hpp
static    __attribute__ ((unused))  key::txt              txt;
static    __attribute__ ((unused))  key::underline        underline;
static    __attribute__ ((unused))  key::val              val;
static    __attribute__ ((unused))  key::verb             verb;
static    __attribute__ ((unused))  key::vspace           vspace;
static    __attribute__ ((unused))  key::yellow           yellow;
static    __attribute__ ((unused))  key::yn               yn;
static    __attribute__ ((unused))  key::width            width;
static    __attribute__ ((unused))  key::white            white;
static    __attribute__ ((unused))  key::wrap             wrap;
#endif

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_KEY_KEY_DEF_HPP
