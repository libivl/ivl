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

#ifndef IVL_CORE_DETAILS_KEY_KEY_HPP
#define IVL_CORE_DETAILS_KEY_KEY_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <typename K> struct plus :
	public mod <K, plus <K> >,
	public gen <plus <K>, K>
{
	operator K() const { return K(); }
};

template <typename K> struct no :
	public mod <K, no <K> >,
	public gen <no <K> >
{
	K operator!() const { return K(); }
};

template <typename K> struct inc :
	public mod <K, inc <K> >,
	public gen <inc <K> > { };

template <typename K> struct dec :
	public mod <K, dec <K> >,
	public gen <dec <K> > { };

//-----------------------------------------------------------------------------

template <typename V>
class value
{
	typedef typename types::remove_ref <V>::type D;
	typedef typename types::apply_const <D>::type T;
	typedef typename types::apply_ref_ptr <T>::type R;
	typedef typename types::apply_ptr <T>::type P;

	T val;

public:
	typedef T type;
	typedef R ref_type;
	typedef P ptr_type;

	value(R v) : val(v) { }

	operator R()   const { return val; }
	R operator*()  const { return val; }
	P operator->() const { return &val; }
};

//-----------------------------------------------------------------------------

template <typename K, typename V>
struct key_val :
	public mod <K, key_val <K, V> >,
	public gen <key_val <K, V> >
{
	typedef typename value <V>::ref_type R;
	typedef typename value <V>::ptr_type P;

	value <V> val;

public:
	typedef key_val type;
	typedef R ref_type;
	typedef P ptr_type;

	key_val(const V& v) : val(v) { }

	R operator*()  const { return *val; }
	P operator->() const { return val.operator->(); }
};

template <typename K, typename V>
class off <key_val <K, V> > :
	public off <typename to_mod <key_val <K, V> >::type>
{
	typedef off <typename to_mod <key_val <K, V> >::type> B;

public:
	off(const key_val <K, V>& p) : B(p) { }
};

//-----------------------------------------------------------------------------

struct key_id { };

template <typename K>
struct is_key : public is_base <key_id, K> { };

//-----------------------------------------------------------------------------

template <typename K>
class key : public mod <K, key <K> >, public key_id
{
protected:
	typedef key KEY;

public:
	plus <K> operator+ () const { return plus <K>(); }
	no   <K> operator! () const { return no   <K>(); }
	inc  <K> operator++() const { return inc  <K>(); }
	dec  <K> operator--() const { return dec  <K>(); }

	template <typename V>
	key_val <K, V> operator=(const V& v) const { return key_val <K, V>(v); }

	template <typename V>
	key_val <K, const V*> operator=(const V v[]) const
	{
		return key_val <K, const V*>(v);
	}
};

//-----------------------------------------------------------------------------

template <typename K, typename F>
class key_fun : public K, public F, public cons <key_fun <K, F> >
{
	typedef cons <key_fun <K, F> > C;

public:
	typedef K key_class;
	typedef F fun_class;

	using C::operator,;
	using K::operator~;
	using K::operator+;
	using K::operator!;
	using K::operator++;
	using K::operator--;

	using F::operator++;

	template <typename V>
	key_val <K, V> operator=(const V& v) const { return K::operator=(v); }

	template <typename V>
	key_val <K, const V*> operator=(const V v[]) const
	{
		return K::operator=(v);
	}
};

//-----------------------------------------------------------------------------

}  // namespace details

using details::plus;
using details::no;
using details::inc;
using details::dec;
using details::value;
using details::key_val;
using details::key;
using details::key_fun;

//-----------------------------------------------------------------------------

namespace all {

using ivl::keys::plus;
using ivl::keys::no;
using ivl::keys::inc;
using ivl::keys::dec;
using ivl::keys::value;
using ivl::keys::key_val;

}  // namespace all

//-----------------------------------------------------------------------------

}  // namespace keys

//-----------------------------------------------------------------------------

namespace types {
namespace constants {

template <typename K, typename V, typename D>
struct c_key_val : public c_struct <keys::key_val <K, V> (D)> { };

}  // namespace constants
}  // namespace types

//-----------------------------------------------------------------------------

namespace key_fun { using keys::key_fun; }

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_KEY_KEY_HPP
