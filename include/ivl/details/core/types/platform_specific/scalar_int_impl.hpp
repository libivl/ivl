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


template<>
class scalar<bool> : public types::scalar_identifier
{
	typedef bool prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};

template<>
class scalar<int8_t> : public types::scalar_identifier
{
	typedef int8_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
template<>
class scalar<uint8_t> : public types::scalar_identifier
{
	typedef uint8_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
template<>
class scalar<int16_t> : public types::scalar_identifier
{
	typedef int16_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
template<>
class scalar<uint16_t> : public types::scalar_identifier
{
	typedef uint16_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
template<>
class scalar<int32_t> : public types::scalar_identifier
{
	typedef int32_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
template<>
class scalar<uint32_t> : public types::scalar_identifier
{
	typedef uint32_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
template<>
class scalar<int64_t> : public types::scalar_identifier
{
	typedef int64_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
template<>
class scalar<uint64_t> : public types::scalar_identifier
{
	typedef uint64_t prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};

#ifndef _MSC_VER
// g++ has a special type for `char' which is neither
// int8_t nor int16_t but a type of its own, whatever implementation
// is used. So it has to be specially treated.
// This does not hold for unsigned char though.
template<>
class scalar<char> : public types::scalar_identifier
{
	typedef char prv_elem_type;
	prv_elem_type v;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : v(static_cast<const prv_elem_type&>(s)) { }
	template <class J>
	scalar(const scalar<J>& s) : v(static_cast<const J&>(s)) { }
	scalar(const prv_elem_type& s) : v(s) { }
	operator prv_elem_type&() { return v; }
	operator const prv_elem_type&() const { return v; }
	prv_elem_type& base() { return v; }
	const prv_elem_type& base() const { return v; }
};
#endif
