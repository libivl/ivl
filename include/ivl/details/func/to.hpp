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

#ifndef IVL_FUNC_TO_HPP
#define IVL_FUNC_TO_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace in_details {

using std::string;

//-----------------------------------------------------------------------------

struct out : public ivl_func <out>
{
	// formatted value to (generic) string
	template <typename S, typename T>
	S _(const T& v) { return +sstr._<S>() << v; }

	// bool to (generic) string
	template <typename S>
	S _(const bool& v) { return _<S>(v ? "true" : "false"); }

	// formatted value to std::string
	template <typename T>
	string _(const T& v) { return _<string>(v); }

	// bool to std::string
	string _(const bool& v) { return _<string>(v); }

};

//-----------------------------------------------------------------------------

struct in : public ivl_func <in>
{
	// string to formatted value
	template <typename T, typename S>
	T _(const S& s) { T v; return +sstr(s) >> v,  v; }

	// string to formatted value, checking for invalid input
	template <typename T, typename S>
	void operate(T& v, bool& ok, sep, const S& s) { ok = +sstr(s) >> v; }

};

//-----------------------------------------------------------------------------

}  // namespace in_details

//-----------------------------------------------------------------------------

namespace fun {

typedef in_details::out out;
typedef in_details::in  in;

}

namespace key_fun {

typedef key_fun <key::out, fun::out> out;
typedef key_fun <key::in,  fun::in>  in;

}

static  __attribute__ ((unused)) key_fun::out out;
static  __attribute__ ((unused)) key_fun::in  in;

//-----------------------------------------------------------------------------

namespace to_details {

using std::string;
using std::basic_string;

//-----------------------------------------------------------------------------

struct to : public ivl_func <to>
{
	// formatted string to value
	template <typename T, typename C, typename TR, typename A>
	T _(const basic_string <C, TR, A>& s) { return in._<T>(s); }

	// formatted const C* to value
	template <typename T, typename C>
	T _(const C* s) { return in._<T>(s); }

	// value to formatted string
	template <typename S, typename T>
	S _(const T& v) { return out._<S>(v); }

};

//-----------------------------------------------------------------------------

class from : public ivl_func <from>
{

	template <typename S>
	struct conv : public S
	{
		conv(const S& s) : S(s) { };

		template <typename T>
		operator T() { return in._<T>(*this); }
	};

public:

//-----------------------------------------------------------------------------

	// formatted string to value, checking for invalid input
	template <typename T, typename C, typename TR, typename A>
	void operate(T& v, bool& ok, sep, const basic_string <C, TR, A>& s)
	{
		(_, v, ok) = in++(s);
	}

	// formatted const C* to value, checking for invalid input
	template <typename T, typename C>
	void operate(T& v, bool& ok, sep, const C* s)
	{
		(_, v, ok) = in++(basic_string <C>(s));
	}

//-----------------------------------------------------------------------------

	// formatted string to value
	template <typename C, typename TR, typename A>
	conv <basic_string <C, TR, A> >
	operator()(const basic_string <C, TR, A>& s)
	{
		return conv <basic_string <C, TR, A> >(s);
	}

	// formatted const C* to value
	template <typename C>
	conv <basic_string <C> >
	operator()(const C* s) { return conv <basic_string <C> >(s); }

	// value to formatted string
	template <typename T>
	string operator()(const T& v) { return out._<string>(v); }

};

//-----------------------------------------------------------------------------

}  // namespace to_details

//-----------------------------------------------------------------------------

namespace fun {

typedef to_details::from from;
typedef to_details::to   to;

}

namespace key_fun {

typedef key_fun <key::from, fun::from> from;
typedef key_fun <key::to,   fun::to>   to;

}

static  __attribute__ ((unused)) key_fun::from from;
static  __attribute__ ((unused)) key_fun::to   to;

//---------------------------------------------------------------------------------

} // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUNC_TO_HPP
