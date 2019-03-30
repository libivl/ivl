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

#ifndef IVL_CORE_DETAILS_KEY_ITEM_HPP
#define IVL_CORE_DETAILS_KEY_ITEM_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename S, typename T>
class item;

template <typename S, typename T>
struct nested_item;

template <typename K, typename F>
class key_fun;

//-----------------------------------------------------------------------------

template <typename T>
struct item_ref : public types::apply_ref_ptr <T> { };

template <typename S, typename T>
struct item_ref <item <S, T> > { typedef item <S, T> type; };

//-----------------------------------------------------------------------------

template <typename S, typename T>
class item :
	public derive_identity <item <S, T> >::type,
	public stream_identifier
{
protected:
	typedef typename item_ref <T>::type D;

public:
	typedef D data_type;
	const S& opt;
	D data;
	item(const S& opt, D data) : opt(opt),   data(data)   { }
	item(const item& i)        : opt(i.opt), data(i.data) { }
	item& operator+() { return *this; }
};

template <typename K, typename F, typename T>
class item <key_fun <K, F>, T> : public item <K, T>
{
	typedef item <K, T> B;
	typedef typename B::D D;

public:
	item(const K& opt, D data) : B(opt, data) { }
	item(const B& i)           : B(i)         { }
};

//-----------------------------------------------------------------------------

template <typename T>
struct add_const { typedef const T type; };

template <typename T>
struct add_const <const T> { typedef const T type; };

//-----------------------------------------------------------------------------

template <typename T>
struct item_data_type { typedef T type; };

template <typename S, typename T>
struct item_data_type <item <S, T> > : public item_data_type <T> { };

template <typename S, typename T>
struct item_data_type <const item <S, T> > :
	public add_const <typename item_data_type <T>::type> { };

//-----------------------------------------------------------------------------

template <typename T>
T& item_data(T& v) { return v; }

template <typename T>
const T& item_data(const T& v) { return v; }

template <typename S, typename T>
typename item_data_type <item <S, T> >::type&
item_data(item <S, T>& i) { return item_data(i.data); };

template <typename S, typename T>
typename item_data_type <const item <S, T> >::type&
item_data(const item <S, T>& i) { return item_data(i.data); };

//-----------------------------------------------------------------------------

template <typename T>
struct nested_item <null, T> { typedef typename item_ref <T>::type type; };

template <typename S, typename T>
struct nested_item <node <S>, T> { typedef item <S, T> type; };

template <typename S, typename SN, typename T>
struct nested_item <node <S, SN>, T>
{
	typedef item <S, typename nested_item <SN, T>::type> type;
};

//-----------------------------------------------------------------------------

template <typename SN, typename T>
struct nested_item <node <null, SN>, T>
{
	typedef typename nested_item <SN, T>::type type;
};

template <typename S, typename SR, typename T>
struct nested_item <node <node <S, SR> >, T>
{
	typedef typename nested_item <node <S, SR>, T>::type type;
};

template <typename S, typename SR, typename SN, typename T>
struct nested_item <node <node <S, SR>, SN>, T>
{
	typedef typename nested_item <
		node <S, SR>,
		typename nested_item <SN, T>::type
	>::type type;
};

//-----------------------------------------------------------------------------

template <typename T>
typename nested_item <null, T>::type
expand   (const item <null, T>& i) { return i.data; }

template <typename S, typename SN, typename T>
typename nested_item <node <S, SN>, T>::type
expand   (const item <node <S, SN>, T>& i)
{
	return (+*i.opt)[expand((++i.opt)[i.data])];
}

template <typename SN, typename T>
typename nested_item <node <null, SN>, T>::type
expand   (const item <node <null, SN>, T>& i)
{
	return expand((++i.opt)[i.data]);
}

template <typename S, typename SR, typename SN, typename T>
typename nested_item <node <node <S, SR>, SN>, T>::type
expand   (const item <node <node <S, SR>, SN>, T>& i)
{
	return expand((*i.opt)[expand((++i.opt)[i.data])]);
}

//-----------------------------------------------------------------------------

template <typename S, typename T>
struct identity <item <S, T> > : public identity <S> { };

template <typename S, typename R, typename T>
struct identity <item <S, item <R, T> > > :
	public join_identity <S, item <R, T> > { };

//-----------------------------------------------------------------------------

template <typename OS, typename S, typename T>
inline OS& operator<<(OS& s, const item <S, T>& i)
{
	return s << i.opt << i.data << ~i.opt;
}

template <typename OS, typename S, typename SN, typename T>
inline OS& operator<<(OS& s, const item <node <S, SN>, T>& i)
{
	return s << expand(i);
}

//-----------------------------------------------------------------------------

template <typename T>
struct is_stream : public is_base <stream_identifier, T> { };

template <typename T>
struct is_streamable : public is_base <streamable_identifier, T> { };

template <typename S, typename T>
struct stream_fail : public t_and <
	is_stream <S>,
	t_not <is_streamable <T> >
> { };

template <typename S, typename T>
typename enable_if <stream_fail <S, T>, S&>::type
inline operator<<(S& s, const T& v) { return item_data(s) << v, s; }

template <typename S, typename T>
typename enable_if <stream_fail <S, T>, S&>::type
inline operator<<(S& s, const T* v) { return item_data(s) << v, s; }

//-----------------------------------------------------------------------------

}  // namespace details

using details::item;
using details::item_data;

//-----------------------------------------------------------------------------

namespace all {

using ivl::keys::item;
using ivl::keys::item_data;

}

//-----------------------------------------------------------------------------

}  // namespace keys

using keys::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_ITEM_HPP
