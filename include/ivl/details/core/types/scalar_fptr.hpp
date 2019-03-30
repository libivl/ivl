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

#ifndef IVL_CORE_DETAILS_TYPES_SCALAR_FPTR_HPP
#define IVL_CORE_DETAILS_TYPES_SCALAR_FPTR_HPP

namespace ivl {


template<class Z, class T, class X1>
class scalar<T (Z::*)(X1) const> :
	//public unary_elem_ptr<T, X1>,
	public types::scalar_identifier
{
	typedef T (Z::*prv_elem_type)(X1) const;
	//typedef unary_elem_ptr<T, X1> prv_base;
	prv_elem_type prv_base;//@@@
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : prv_base(s.prv_base) { }
	template <class J>
	scalar(const scalar<J>& s): prv_base(s) { }
	scalar(elem_type s) : prv_base(s) { }
	elem_type base() const { return this->prv_base; }
	operator elem_type&() const { return this->prv_base; }
	scalar& operator=(const scalar& s) { this->prv_base = s.prv_base; return *this; }
	scalar& operator=(elem_type s) { this->prv_base = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { this->prv_base = o; return *this; }
};

template<class Z, class T, class X1>
class scalar<T (Z::*)(X1)> :
	//public unary_elem_ptr<T, X1>,
	public types::scalar_identifier
{
	typedef T (Z::*prv_elem_type)(X1);
	//typedef unary_elem_ptr<T, X1> prv_base;
	prv_elem_type prv_base;//@@@
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : prv_base(s.prv_base) { }
	template <class J>
	scalar(const scalar<J>& s): prv_base(s) { }
	scalar(elem_type s) : prv_base(s) { }
	elem_type base() const { return this->prv_base; }
	operator elem_type&() const { return this->prv_base; }
	scalar& operator=(const scalar& s) { this->prv_base = s.prv_base; return *this; }
	scalar& operator=(elem_type s) { this->prv_base = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { this->prv_base = o; return *this; }
};
// -------------------------------

template<class T, class X1>
class scalar<T (*)(X1)> :
	//public unary_elem_ptr<T, X1>,
	public types::scalar_identifier
{
	typedef T (*prv_elem_type)(X1);
	//typedef unary_elem_ptr<T, X1> prv_base;
	prv_elem_type prv_base;//@@@
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : prv_base(s.val) { }
	template <class J>
	scalar(const scalar<J>& s): prv_base(s) { }
	scalar(elem_type s) : prv_base(s) { }
	elem_type& base() const { return this->val; }
	operator elem_type&() const { return this->val; }
	scalar& operator=(const scalar& s) { this->val = s.val; return *this; }
	scalar& operator=(elem_type s) { this->val = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { this->val = o; return *this; }
};


template<class T, class X1>
class scalar<T (&)(X1)> :
	//public unary_elem_ptr<T, X1, X2>,
	public types::scalar_identifier
{
	typedef T (*prv_elem_type)(X1);
	//typedef unary_elem_ptr<T, X1> prv_base;
	prv_elem_type prv_base;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : prv_base(s.val) { }
	template <class J>
	scalar(const scalar<J>& s): prv_base(s) { }
	scalar(elem_type s) : prv_base(s) { }
	elem_type& base() const { return this->val; }
	operator elem_type&() const { return this->val; }
	scalar& operator=(const scalar& s) { this->val = s.val; return *this; }
	scalar& operator=(elem_type s) { this->val = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { this->val = o; return *this; }
};




// -------------------------------

template<class T, class X1, class X2>
class scalar<T (*)(X1, X2)> :
	public binary_elem_ptr<T, X1, X2>,
	public types::scalar_identifier
{
	typedef T (*prv_elem_type)(X1, X2);
	typedef binary_elem_ptr<T, X1, X2> prv_base;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : prv_base(s.val) { }
	template <class J>
	scalar(const scalar<J>& s): prv_base(s) { }
	scalar(elem_type s) : prv_base(s) { }
	elem_type& base() const { return this->val; }
	operator elem_type&() const { return this->val; }
	scalar& operator=(const scalar& s) { this->val = s.val; return *this; }
	scalar& operator=(elem_type s) { this->val = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { this->val = o; return *this; }
};


template<class T, class X1, class X2>
class scalar<T (&)(X1, X2)> :
	public binary_elem_ptr<T, X1, X2>,
	public types::scalar_identifier
{
	typedef T (*prv_elem_type)(X1, X2);
	typedef binary_elem_ptr<T, X1, X2> prv_base;
public:
	typedef prv_elem_type elem_type;
	scalar() { }
	scalar(const scalar& s) : prv_base(s.val) { }
	template <class J>
	scalar(const scalar<J>& s): prv_base(s) { }
	scalar(elem_type s) : prv_base(s) { }
	elem_type& base() const { return this->val; }
	operator elem_type&() const { return this->val; }
	scalar& operator=(const scalar& s) { this->val = s.val; return *this; }
	scalar& operator=(elem_type s) { this->val = s; return *this; }
	template <class J>
	scalar& operator=(const J& o) { this->val = o; return *this; }
};

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_SCALAR_HPP
