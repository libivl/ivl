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

#ifndef IVL_CORE_DETAILS_DOC_HTML_HPP
#define IVL_CORE_DETAILS_DOC_HTML_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {

//-----------------------------------------------------------------------------

template <typename K>
struct etag : public keys::group <K, etag, true> { };

template <typename K>
struct tag : public keys::group <K, tag, true> { };

template <typename K>
struct prop : public keys::group <K, prop, true> { };

//-----------------------------------------------------------------------------

namespace key {

//-----------------------------------------------------------------------------

struct t_a        : public tag <t_a>            { using KEY::operator=; static const char* id() { return "a"; } };
struct t_b        : public tag <t_b>            { using KEY::operator=; static const char* id() { return "b"; } };
struct t_p        : public tag <t_p>            { using KEY::operator=; static const char* id() { return "p"; } };
struct t_h1       : public tag <t_h1>           { using KEY::operator=; static const char* id() { return "h1"; } };
struct t_h2       : public tag <t_h2>           { using KEY::operator=; static const char* id() { return "h2"; } };
struct t_h3       : public tag <t_h3>           { using KEY::operator=; static const char* id() { return "h3"; } };
struct t_br       : public tag <t_br>           { using KEY::operator=; static const char* id() { return "br"; } };
struct t_td       : public tag <t_td>           { using KEY::operator=; static const char* id() { return "td"; } };
struct t_tr       : public tag <t_tr>           { using KEY::operator=; static const char* id() { return "tr"; } };
struct t_div      : public tag <t_div>          { using KEY::operator=; static const char* id() { return "div"; } };
struct t_span     : public tag <t_span>         { using KEY::operator=; static const char* id() { return "span"; } };
struct t_table    : public tag <t_table>        { using KEY::operator=; static const char* id() { return "table"; } };
struct t_script   : public tag <t_script>       { using KEY::operator=; static const char* id() { return "script"; } };
struct t_code     : public tag <t_code>         { using KEY::operator=; static const char* id() { return "code"; } };

struct p_type     : public prop <p_type>        { using KEY::operator=; static const char* id() { return "type"; } };
struct p_class    : public prop <p_class>       { using KEY::operator=; static const char* id() { return "class"; } };
struct p_href     : public prop <p_href>        { using KEY::operator=; static const char* id() { return "href"; } };

struct c_emph     : public etag <c_emph>        { using KEY::operator=; static const char* id() { return "emph"; } };
struct c_alert    : public etag <c_alert>       { using KEY::operator=; static const char* id() { return "alert"; } };

struct prop_sty   : public style <prop_sty>     { using KEY::operator=; };
struct tag_sty    : public style <tag_sty>      { using KEY::operator=; };
struct tag_on     : public style <tag_on>       { using KEY::operator=; };
struct tag_off    : public style <tag_off>      { using KEY::operator=; };
struct cdata      : public style <cdata>        { using KEY::operator=; };
struct etag_on    : public style <etag_on>      { using KEY::operator=; };
struct etag_off   : public style <etag_off>     { using KEY::operator=; };

struct cell       : public style <cell>         { using KEY::operator=; };
struct table      : public style <table>        { using KEY::operator=; };
struct div        : public style <div>          { using KEY::operator=; };
struct span       : public style <span>         { using KEY::operator=; };
struct pre        : public style <pre>          { using KEY::operator=; };
struct on_verb    : public style <on_verb>      { using KEY::operator=; };
struct link       : public style <link>         { using KEY::operator=; };
struct php        : public style <php>          { using KEY::operator=; };

//-----------------------------------------------------------------------------

}  // namespace key

//-----------------------------------------------------------------------------

static __attribute__ ((unused))  key::t_a              t_a;
static __attribute__ ((unused))  key::t_b              t_b;
static __attribute__ ((unused))  key::t_p              t_p;
static __attribute__ ((unused))  key::t_h1             t_h1;
static __attribute__ ((unused))  key::t_h2             t_h2;
static __attribute__ ((unused))  key::t_h3             t_h3;
static __attribute__ ((unused))  key::t_br             t_br;
static __attribute__ ((unused))  key::t_td             t_td;
static __attribute__ ((unused))  key::t_tr             t_tr;
static __attribute__ ((unused))  key::t_div            t_div;
static __attribute__ ((unused))  key::t_span           t_span;
static __attribute__ ((unused))  key::t_table          t_table;
static __attribute__ ((unused))  key::t_script         t_script;
static __attribute__ ((unused))  key::t_code           t_code;

static __attribute__ ((unused))  key::p_type           p_type;
static __attribute__ ((unused))  key::p_class          p_class;
static __attribute__ ((unused))  key::p_href           p_href;

static __attribute__ ((unused))  key::c_emph           c_emph;
static __attribute__ ((unused))  key::c_alert          c_alert;

static __attribute__ ((unused))  key::prop_sty         prop_sty;
static __attribute__ ((unused))  key::tag_sty          tag_sty;
static __attribute__ ((unused))  key::tag_on           tag_on;
static __attribute__ ((unused))  key::tag_off          tag_off;
static __attribute__ ((unused))  key::cdata            cdata;
static __attribute__ ((unused))  key::etag_on          etag_on;
static __attribute__ ((unused))  key::etag_off         etag_off;

static __attribute__ ((unused))  key::cell             cell;
static __attribute__ ((unused))  key::table            table;
static __attribute__ ((unused))  key::div              div;
static __attribute__ ((unused))  key::span             span;
static __attribute__ ((unused))  key::pre              pre;
static __attribute__ ((unused))  key::on_verb          on_verb;
static __attribute__ ((unused))  key::link             link;
static __attribute__ ((unused))  key::php              php;

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

namespace device {

using ikey::html;

//-----------------------------------------------------------------------------
// html tags

template <typename S, typename K>
inline S& operator<<(S& s, tag <K>) { return *s << tag_on[K::id()]; }

template <typename S, typename K, typename T>
typename enable_if <is_of_group <K, tag>, S&>::type
inline operator<<(S& s, const off <mod <K, T> >&) { return *s << tag_off[K::id()]; }

template <typename S, typename K, typename V>
typename enable_if <is_of_group <K, tag>, S&>::type
inline operator<<(S& s, const key_val <K, V>& v)
{
	return *s << tag_on << K::id() << prop_sty[*v] << ~tag_on;
}

template <typename S, typename K, typename V>
typename enable_if <is_of_group <K, prop>, S&>::type
inline operator<<(S& s, const key_val <K, V>& v)
{
	return *s << " " << K::id() << "=\"" << *v << "\"";
}

template <typename S> inline S& operator<<(S& s, key::prop_sty)      { return *s << (_, normal); }
template <typename S> inline S& operator<<(S& s, key::tag_sty)       { return *s << (bright, yellow); }

template <typename S> inline S& operator<<(S& s, key::tag_on)        { return *s <<  tag_sty << "<"; }
template <typename S> inline S& operator<<(S& s, off <key::tag_on>)  { return *s << ">" << ~tag_sty; }
template <typename S> inline S& operator<<(S& s, key::tag_off)       { return *s << tag_sty << "</"; }
template <typename S> inline S& operator<<(S& s, off <key::tag_off>) { return *s << ">" << ~tag_sty; }
template <typename S> inline S& operator<<(S& s, key::cdata)         { return *s <<  tag_sty["<![CDATA["] << nl; }
template <typename S> inline S& operator<<(S& s, off <key::cdata>)   { return *s <<  nl << tag_sty["]]>"]; }

//-----------------------------------------------------------------------------
// escape tags

template <typename S, typename K>
inline S& operator<<(S& s, etag <K>) { return *s << etag_on[K::id()]; }

template <typename S, typename K>
typename enable_if <is_of_group <K, etag>, S&>::type
inline operator<<(S& s, const off <K>&) { return *s << etag_off[K::id()]; }

template <typename S> inline S& operator<<(S& s, key::etag_on)        { return *s << tag_sty << "<@"; }
template <typename S> inline S& operator<<(S& s, off <key::etag_on>)  { return *s << ">" << ~tag_sty; }
template <typename S> inline S& operator<<(S& s, key::etag_off)       { return *s << tag_sty << "<@/"; }
template <typename S> inline S& operator<<(S& s, off <key::etag_off>) { return *s << ">" << ~tag_sty; }

//-----------------------------------------------------------------------------
// convenience macros

template <typename S> inline S& operator<<(S& s, key::cell)          { return *s <<  t_td; }
template <typename S> inline S& operator<<(S& s, off <key::cell>)    { return *s << (~t_td, nl); }

template <typename S, typename V>
inline S& operator<<(S& s, const key_val <key::table, V>& v)         { return *s << (_, t_table=(p_class=*v)); }

template <typename S, typename V>
inline S& operator<<(S& s, const key_val <key::div, V>& v)           { return *s << (_, t_div=(p_class=*v)); }

template <typename S, typename V>
inline S& operator<<(S& s, const key_val <key::span, V>& v)          { return *s << (_, t_span=(p_class=*v)); }

//-----------------------------------------------------------------------------
// code highlighting

inline const char* brush(key::lst) { return "brush:ivl;"; }
inline const char* brush(key::out) { return "brush:out;"; }

template <typename S, typename V>
inline S& operator<<(S& s, const key_val <key::pre, V>& v)
{
	return *s << (
		par, t_p, nl,
		t_script=(p_type="syntaxhighlighter", p_class=brush(*v)),
		cdata, verb
	);
}

template <typename S, typename V, typename M>
inline S& operator<<(S& s, const key_val <key::on_verb, node <M, node <V> > >& m)
{
	return is_verbatim(*s) ? *s << (_, *++*m) : *s << (_, **m);
}

inline const char* escape(char c) { return c == '<' ? "&lt;" : 0; }

//-----------------------------------------------------------------------------
// links, anchor tags

inline string http (const string& address) { return "http://" + address + "/"; }
inline string wiki (const string& article) { return http("en.wikipedia.org/wiki") + article; }
inline string cpp  (const string& query)   { return http("cplusplus.com") + "search.do?q=" + query; }
inline string local(const string& file)    { return file + ".php"; }

template <typename T> inline const T& href(const T& v)        { return v; }
template <typename T> inline string   href(key::ivl_type <T>) { return local(name <T>()()); }
template <typename T> inline string   href(key::ivl_fun <T>)  { return local(name <T>()()); }
template <typename T> inline string   href(key::num_type <T>) { return wiki("C_data_types"); }
template <typename T> inline string   href(key::std_type <T>) { return cpp(name <T>()()); }
template <typename T> inline string   href(key::std_fun <T>)  { return cpp(name <T>()()); }

template <typename S, typename V>
inline S& operator<<(S& s, const key_val <key::link, V>& v) { return *s << (_, t_a=(p_href=href(*v))); }

//-----------------------------------------------------------------------------
// begin/end php scripts

template <typename S> inline S& operator<<(S& s, key::php) { return *s << (php=""); }

template <typename S, typename V>
inline S& operator<<(S& s, const key_val <key::php, V>& title)
{
	return *s << tag_sty["<?"] << in <<
		"$title = \"" << *title << " - ivl help\";" << nl <<
		"include '../php/start.php';" << nl <<
		"include '../php/menu.php';" << nl <<
		"include '../php/contents-start.php'" << nl <<
	~in << tag_sty["?>"];
}

template <typename S, typename T>
inline S& operator<<(S& s, const off <mod <key::php, T> >&)
{
	return *s << tag_sty["<?"] << in <<
		"include '../php/contents-stop.php';" << nl <<
		"include '../php/stop.php';" << nl <<
	~in << tag_sty["?>"];
}

//-----------------------------------------------------------------------------

template <typename S, typename V>
inline S& so(id <html, S>& s, const key_val <key::page, V>& v)       { return *s << (file, (php=*v)); }

template <typename S> inline S& so(id <html, S>& s, key::page)       { return *s << (file, php); }
template <typename S> inline S& so(id <html, S>& s, key::file)       { return *s << (!wrap, !indent, par); }
template <typename S> inline S& so(id <html, S>& s, key::nline)      { return *s << (t_br, nl); }
template <typename S> inline S& so(id <html, S>& s, key::para)       { return *s << (par, t_p, in); }
template <typename S> inline S& so(id <html, S>& s, key::head1)      { return *s << (par, t_h1, bright); }
template <typename S> inline S& so(id <html, S>& s, key::head2)      { return *s << (par, t_h2, bright); }
template <typename S> inline S& so(id <html, S>& s, key::head3)      { return *s << (par, t_h3, bright); }
template <typename S> inline S& so(id <html, S>& s, key::tabular)    { return *s << (par, table="lst", in); }
template <typename S> inline S& so(id <html, S>& s, key::row)        { return *s << (nl, t_tr, in); }
template <typename S> inline S& so(id <html, S>& s, key::label)      { return *s << (_, cell); }
template <typename S> inline S& so(id <html, S>& s, key::desc)       { return *s << (_, cell); }

template <typename S> inline S& so(id <html, S>& s, key::title)      { return *s << (head2, white); }
template <typename S> inline S& so(id <html, S>& s, key::body)       { return *s << (par, div="txbox", normal, white); }
template <typename S> inline S& so(id <html, S>& s, key::syntax)     { return *s << (span="syntax", bright, cyan); }
template <typename S> inline S& so(id <html, S>& s, key::t_ivl)      { return *s << (span="ivl")["ivl"]; }
template <typename S> inline S& so(id <html, S>& s, key::code)       { return *s << (t_code, filter=&escape, cyan); }
template <typename S> inline S& so(id <html, S>& s, key::lst)        { return *s << (pre=lst, cyan); }
template <typename S> inline S& so(id <html, S>& s, key::out)        { return *s << (pre=out, green); }
template <typename S> inline S& so(id <html, S>& s, key::type)       { return *s << (_, magenta); }
template <typename S> inline S& so(id <html, S>& s, key::func)       { return *s << (bright, blue); }
template <typename S> inline S& so(id <html, S>& s, key::emph)       { return *s << (on_verb=(c_emph, t_b), bright); }
template <typename S> inline S& so(id <html, S>& s, key::alert)      { return *s << (on_verb=(c_alert, span="alert"), bright, red); }

template <typename S>             inline S& so(id <html, S>& s, key::any_type)   { return *s << (span="type", type); }
template <typename S, typename T> inline S& so(id <html, S>& s, type_def <T> t)  { return *s << (link=*t, t_code, type); }
template <typename S, typename T> inline S& so(id <html, S>& s, fun_def  <T> t)  { return *s << (link=*t, t_code, func); }

//-----------------------------------------------------------------------------

}  // namespace device

//-----------------------------------------------------------------------------

}  // namespace details

//-----------------------------------------------------------------------------

}  // namespace doc

using doc::details::device::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_DOC_HTML_HPP
