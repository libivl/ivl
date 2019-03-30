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

#ifndef IVL_FUNC_SSTR_HPP
#define IVL_FUNC_SSTR_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace sstr_details {

using std::basic_string;
using std::char_traits;
using std::allocator;
using std::basic_ostringstream;
using std::basic_istringstream;

//-----------------------------------------------------------------------------

template <
	typename C = char,
	typename TR = char_traits <C>,
	typename A = allocator <C>
>
struct osstream
{
	basic_ostringstream <C, TR, A> stream;

public:
	osstream() { }
	osstream(const osstream&) { }

	osstream& operator+() { return *this; }

	template <typename T>
	osstream& operator<<(const T& v) { return stream << v, *this; }

	operator basic_string <C, TR, A>() const { return stream.str(); }
};

//-----------------------------------------------------------------------------

template <
	typename C = char,
	typename TR = char_traits <C>,
	typename A = allocator <C>
>
struct isstream
{
	basic_istringstream <C, TR, A> stream;

public:
	isstream(const basic_string <C, TR, A>& s) : stream(s) { }
	isstream(const isstream& ss) : stream(ss.stream.str()) { }

	isstream& operator+() { return *this; }

	template <typename T>
	isstream& operator>>(T& v) { return stream >> v, *this; }

	operator bool() const { return !stream.fail(); }
};

//-----------------------------------------------------------------------------

struct sstr : public ivl_func <sstr>
{
	template <typename S>
	struct osstream_of { };

	template <typename C, typename TR, typename A>
	struct osstream_of <basic_string <C, TR, A> >
	{
		typedef osstream <C, TR, A> type;
	};

//-----------------------------------------------------------------------------

	osstream <> operator()() const { return osstream <>(); }

	template <typename S>
	typename osstream_of <S>::type
	_() const { return typename osstream_of <S>::type(); }

//-----------------------------------------------------------------------------

	template <typename C, typename TR, typename A>
	isstream <C, TR, A>
	operator()(const basic_string <C, TR, A>& s) const
	{
		return isstream <C, TR, A>(s);
	}

	template <typename C>
	isstream <>
	operator()(const C* s) const { return isstream <>(s); }

};

//-----------------------------------------------------------------------------

}  // namespace sstr_details

//-----------------------------------------------------------------------------

namespace fun { typedef sstr_details::sstr sstr; }

static  __attribute__ ((unused)) fun::sstr sstr;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUNC_SSTR_HPP
