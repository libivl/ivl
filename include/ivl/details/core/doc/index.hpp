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

#ifndef IVL_CORE_DETAILS_DOC_INDEX_HPP
#define IVL_CORE_DETAILS_DOC_INDEX_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace doc {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename S, typename F>
class entry
{
	some_of <S> data;

	template <typename T>
	void init(const T& id) { data = F()(hlp(id)); }

public:
	entry() { }

	template <typename T>
	entry(const T& id) { init(id); }

	template <typename T>
	entry& operator=(const T& id) { init(id); return *this; }

	operator some_of <S>() const { return data; }
};

//-----------------------------------------------------------------------------

template <typename S = item <ikey::txt, std::ostream>, typename F = fun::id>
class index
{
	typedef entry <S, F> E;

	// constructor tab() -> @doc/core/index.cpp
	struct tab : public std::map <std::string, E> { tab(); };
	typedef typename tab::const_iterator CI;

	static tab& table() { static tab t; return t; }

public:

	some_of <S>
	operator()(const std::string& name) const { return lookup(name); }

	static some_of <S>
	lookup(const std::string& name)
	{
		CI i = table().find(name);
		return i == table().end() ? E() : i->second;
	}
};

static  __attribute__ ((unused)) index <> lookup;

//-----------------------------------------------------------------------------

template <typename S, typename F, typename D>
inline S& operator<<(S& s, const query <F, D>& q)
{
	return +(+D())[s] << query <F>(q),  s;
}

template <typename S, typename G>
S& operator<<(S& s, const query <G>& q)
{
	typedef typename query <G>::fun F;
	if (q->empty()) return s << F()(help_topic <>());

	some_of <S> entry = index <S, F>()(q);
	return entry() ? s << entry : s << not_found <F>(q);
}

//-----------------------------------------------------------------------------

template <typename S, typename F>
inline S& operator<<(S& s, const not_found <F>&) { return s; };

template <typename S>
S& operator<<(S& s, const not_found <>& q)
{
	return s << page << body <<
		"No help entry found for " << code[*q] << "." <<
	~body << ~page;
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::index;
using details::lookup;

//-----------------------------------------------------------------------------

}  // namespace doc

using doc::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_DOC_INDEX_HPP
