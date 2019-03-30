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

#ifndef IVL_CORE_DETAILS_DOC_HELP_HPP
#define IVL_CORE_DETAILS_DOC_HELP_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {

using ivl::operator<<;

//-----------------------------------------------------------------------------

typedef types::term root;

template <typename T>        struct help_title;
template <typename T>        struct help_body;
template <typename T>        struct help_also;
template <typename T = root> struct help_content { template <typename S> void operator()(S) { } };

template <typename S, typename T> inline S& operator<<(S& s, help_title   <T> h) { return h(s), s; }
template <typename S, typename T> inline S& operator<<(S& s, help_body    <T> h) { return h(s), s; }
template <typename S, typename T> inline S& operator<<(S& s, help_also    <T> h) { return h(s), s; }
template <typename S, typename T> inline S& operator<<(S& s, help_content <T> h) { return h(s), s; }

//-----------------------------------------------------------------------------

namespace details {

using std::string;
using types::t_if;
using types::t_eq;
using types::term;
using types::enable_if;

//-----------------------------------------------------------------------------

template <typename T = term, typename D = term> struct
help_topic { };

template <typename T>        struct see_also { };
template <typename T = term> struct disp_content { };

template <typename T>             struct inline_list { };
template <typename T, typename F> struct disp_list { };

//-----------------------------------------------------------------------------

template <typename F = term, typename D = term>
struct query : public value <string>
{
	typedef string S;
	typedef typename t_if <t_eq <F, term>, fun::id, F>::type fun;
	explicit query(const S& q = S()) : value <S>(q) { }
};

template <typename F = fun::id>
struct not_found : public value <string>
{
	typedef string S;
	explicit not_found(const S& q = S()) : value <S>(q) { }
};

//-----------------------------------------------------------------------------

template <typename S, typename T>
inline S& operator<<(S& s, inline_list <T>) { return +(sep=", ")[s] << T(),  s; };

template <typename S, typename T, typename F>
inline S& operator<<(S& s, disp_list <T, F>)
{
	return s << tabular,
		+(filter=F())[s] << T(),
	s << ~tabular;
};

//-----------------------------------------------------------------------------

template <typename S, typename T, typename D>
inline S& operator<<(S& s, help_topic <T, D>)
{
	return +(+D())[s] << help_topic <T>(),  s;
}

template <typename S, typename T>
S& operator<<(S& s, help_topic <T>)
{
	return s << (page=name <T>()()) <<
		title << name <T>()() << " : " << help_title <T>() << ~title <<
		body << help_body <T>() << see_also <T>() << ~body <<
	~page;
}

//-----------------------------------------------------------------------------

template <typename S, typename T>
S& operator<<(S& s, see_also <T>)
{
	return s << para <<
		"See also " << inline_list <help_also <T> >() << "." <<
	~para;
}

//-----------------------------------------------------------------------------

template <typename D = ikey::txt>
struct help : public ivl_func <help <D> >
{
	template <typename T>
	help_topic <T, D>
	operator()(type <T>) { return help_topic <T, D>(); }

	template <int N, typename T>
	help_topic <T, D>
	operator()(types::template_class <N, T>) { return help_topic <T, D>(); }

//-----------------------------------------------------------------------------

	template <typename T>
	help_topic <T, D>
	operator()(fun::function <T>) { return help_topic <T, D>(); }

// 	template <typename T>
// 	help_topic <T, D>
// 	operator()(const ivl_func <T>&) { return help_topic <T, D>(); }

	template <typename T, typename F>
	help_topic <F, D>
	operator()(types::fun_constant <T, F>) { return help_topic <F, D>(); }

	template <int N, typename T>
	help_topic <T, D>
	operator()(types::template_class <N, T, fun_id>) { return help_topic <T, D>(); }

	template <typename K, typename F>
	help_topic <F, D>
	operator()(keys::key_fun <K, F>) { return help_topic <F, D>(); }

//-----------------------------------------------------------------------------

	query <term, D>
	operator()(const string& q) { return query <term, D>(q); }

//-----------------------------------------------------------------------------

	template <typename K>
	typename enable_if <is_id <K>, help <K> >::type
	operator[](keys::key <K>) { return help <K>(); }

	help <term>
	operator[](core_details::_class) { return help <term>(); }
};

static  __attribute__ ((unused)) help <term> hlp;

//-----------------------------------------------------------------------------

struct to_full
{
	template <typename S, typename T>
	void operator()(S& s, const T& id) const { s << hlp(id); }
};

struct to_short
{
	template <typename S, typename T>
	void operator()(S& s, const T& id) const
	{
		s << row << label[id] << desc[title_of(hlp(id))] << ~row;
	}
};

//-----------------------------------------------------------------------------

template <typename S>
S& operator<<(S& s, help_topic <>)
{
	return s <<
	(page="home") <<
		title << t_ivl << " help" << ~title <<
		body <<
			para["Help is available for the following topics:"] <<
			disp_content <>() <<
			para <<
				"Type " << code["help <name>"] << " to view help for topic " <<
				code["name"] << "." <<
			~para <<
		~body <<
	~page;
};

template <typename S, typename T>
inline S& operator<<(S& s, disp_content <T>)
{
	return s << disp_list <help_content <T>, to_short>();
};

//-----------------------------------------------------------------------------

template <typename T, typename D> help_title <T>
title_of(help_topic <T, D>) { return help_title <T>(); }

template <typename T, typename D> help_body <T>
body_of(help_topic <T, D>) { return help_body <T>(); }

template <typename T, typename D> help_also <T>
also_of(help_topic <T, D>) { return help_also <T>(); }

//-----------------------------------------------------------------------------

struct to_name
{
	template <typename T> string
	operator()(const T& id) { return (*this)(hlp(id)); }

	template <typename T, typename D> string
	operator()(help_topic <T, D>) { return name <T>()(); }

	string
	operator()(const string& s) { return s == "" ? "index" : s; }
};

static  __attribute__ ((unused)) to_name name_of;

//-----------------------------------------------------------------------------

struct to_content
{
	template <typename T, typename D> help_content <T>
	operator()(help_topic <T, D>) { return help_content <T>(); }

	template <typename F, typename D> query <to_content>
	operator()(const query <F, D>& q) { return query <to_content>(q); }
};

static  __attribute__ ((unused)) to_content content_of;

//-----------------------------------------------------------------------------

}  // namespace details

using details::help_topic;
using details::name_of;
using details::content_of;
using details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace doc

using doc::operator<<;

//-----------------------------------------------------------------------------

namespace fun     { typedef doc::details::help <>          help; }
namespace key_fun { typedef key_fun <key::help, fun::help> help; }

//-----------------------------------------------------------------------------

static  __attribute__ ((unused)) key_fun::help help;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_DOC_HELP_HPP
