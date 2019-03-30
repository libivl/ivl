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

#ifndef IVL_CORE_DETAILS_KEY_OPTION_OF_HPP
#define IVL_CORE_DETAILS_KEY_OPTION_OF_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

enum { stack_size = some_details::stack_size };

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename T,
	typename OP = typename some_operators::operator_of <T>::type,
	size_t N = stack_size
>
class option_of : public some_<N>,
	public ref_pair <option_of <T, OP, N> >,
	public gen <option_of <T, OP, N> >
{
	typedef some_<N> B;
	typedef typename OP::template ret <T>::type R;

	R (*call)(const B&, T&, bool);

//-----------------------------------------------------------------------------

	template <typename I>
	struct stub
	{
		static R call(const B& b, T& obj, bool off)
		{
			return off ?
				OP()(~b.template _<I>(), obj) :
				OP()( b.template _<I>(), obj);
		};
	};

//-----------------------------------------------------------------------------

	void read()                   { call = 0; }
	void read(const B&)           { call = 0; }
	void read(const option_of& s) { call = s.call; }

	template <typename I>
	void read(const I&) { call = stub <typename create_new <I>::type>::call; }

protected:

//-----------------------------------------------------------------------------

	option_of&                       assign()           { B::assign();  read();  return *this; }
	template <typename I> option_of& assign(const I& v) { B::assign(v); read(v); return *this; }

public:

//-----------------------------------------------------------------------------

	typedef R return_type;

	option_of() : B() { read(); }

	template <typename I> option_of(const I& v)   : B(v) { read(v); }
	template <typename I> option_of(const I  v[]) : B(v) { read <const I*>(v); }

	template <typename I> option_of& operator=(const I& v)   { return assign(v); }
	template <typename I> option_of& operator=(const I  v[]) { return assign <const I*>(v); }

	option_of& init()  { return assign(); }
	option_of& clear() { return assign(); }

	bool empty()      const { return B::empty()      || call == 0; }
	bool operator()() const { return B::operator()() && call != 0; }

	R operator()(T& obj,       bool off = false) const { return (*call)(*this, obj,       off); }
	R operator()(const T& obj, bool off = false) const { return (*call)(*this, vary(obj), off); }
	// TODO: what assumptions needed to pass a const object?
};

//-----------------------------------------------------------------------------

template <typename T, typename OP, size_t N>
class off <option_of <T, OP, N> > :
	public ref_pair <off <option_of <T, OP, N> > >,
	public gen <off <option_of <T, OP, N> > >
{
	typedef ref_pair <off <option_of <T, OP, N> > > B;

public:
	off(const option_of <T, OP, N>& s) : B(s) { }
};

//-----------------------------------------------------------------------------

template <typename S, typename T, typename OP, size_t N>
typename enable_if <is_conv <T, S>, S&>::type
inline operator<<(S& s, const option_of <T, OP, N>& o) { return o(s); }

template <typename S, typename T, typename OP, size_t N>
typename enable_if <is_conv <T, S>, S&>::type
inline operator<<(S& s, const off <option_of <T, OP, N> >& o)
{
	return (~o)(s, true);
}

//-----------------------------------------------------------------------------

}  // namespace details

using details::option_of;

namespace all { using ivl::keys::option_of; }

//-----------------------------------------------------------------------------

}  // namespace keys

using keys::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_OPTION_OF_HPP
