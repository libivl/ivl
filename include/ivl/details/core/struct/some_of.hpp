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

   ivl is distributed read the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_CORE_DETAILS_STRUCT_SOME_OF_HPP
#define IVL_CORE_DETAILS_STRUCT_SOME_OF_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace some_operators {

//-----------------------------------------------------------------------------

struct apply
{
	template <typename T>
	struct ret { typedef void type; };

	template <typename F, typename T>
	void operator()(const F& fun, T& obj) { fun(obj); }
};

struct stream
{
	template <typename T>
	struct ret { typedef T& type; };

	template <typename I, typename T>
	T& operator()(const I& item, T& obj) { return obj << item; }
};

struct bracket
{
	template <typename T>
	struct ret { typedef T& type; };

	template <typename P, typename T>
	T& operator()(const P& prop, T& obj) { return obj[prop]; }
};

//-----------------------------------------------------------------------------

template <typename T>
struct operator_of { typedef stream type; };

}  // namespace some_operators

//-----------------------------------------------------------------------------

namespace some_details {

using namespace some_operators;

//-----------------------------------------------------------------------------

template <
	typename T,
	typename OP = typename operator_of <T>::type,
	size_t N = stack_size
>
class some_of : public some_<N>
{
	typedef some_<N> B;
	typedef typename OP::template ret <T>::type R;

	R (*call)(const B&, T&);

//-----------------------------------------------------------------------------

	template <typename I>
	struct stub
	{
		static R call(const B& b, T& obj) { return OP()(b.template _<I>(), obj); };
	};

//-----------------------------------------------------------------------------

	void read()                 { call = 0; }
	void read(const B&)         { call = 0; }
	void read(const some_of& s) { call = s.call; }

	template <typename I>
	void read(const I&) { call = stub <typename create_new <I>::type>::call; }

protected:

//-----------------------------------------------------------------------------

	some_of&                       assign()           { B::assign();  read();  return *this; }
	template <typename I> some_of& assign(const I& v) { B::assign(v); read(v); return *this; }

public:

//-----------------------------------------------------------------------------

	some_of() : B() { read(); }

	template <typename I> some_of(const I& v)   : B(v) { read(v); }
	template <typename I> some_of(const I  v[]) : B(v) { read <const I*>(v); }

	template <typename I> some_of& operator=(const I& v)   { return assign(v); }
	template <typename I> some_of& operator=(const I  v[]) { return assign <const I*>(v); }

	some_of& init()  { return assign(); }
	some_of& clear() { return assign(); }

	bool empty()      const { return B::empty()      || call == 0; }
	bool operator()() const { return B::operator()() && call != 0; }

	R operator()(T& obj)       const { return (*call)(*this, obj); }
	R operator()(const T& obj) const { return (*call)(*this, vary(obj)); }
	// TODO: what assumptions needed to pass a const object?
};

//-----------------------------------------------------------------------------

template <typename S, typename T, typename OP, size_t N>
typename enable_if <is_conv <T, S>, S&>::type
operator<<(S& s, const some_of <T, OP, N>& o) { return o(s); }

//-----------------------------------------------------------------------------

}  // namespace some_details

using some_details::some_of;
using some_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_STRUCT_SOME_OF_HPP
