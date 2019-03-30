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

#ifndef IVL_CORE_DETAILS_TYPES_TYPES_HPP
#define IVL_CORE_DETAILS_TYPES_TYPES_HPP

//-----------------------------------------------------------------------------

namespace ivl {
namespace types {

//-----------------------------------------------------------------------------

template <class T, class ENABLE = t_true>
struct apply_ref : public apply_ref <T, typename ENABLE::type> { };

template <class T>
struct apply_ref <T, t_false>
{
	typedef T type;
};

template <class T>
struct apply_ref <T, t_true>
{
	typedef T& type;
};

template <class T>
struct apply_ref <T&, t_true>
{
	typedef T& type;
};

//-----------------------------------------------------------------------------
// iavr

template <class T, class ENABLE = t_true>
struct apply_ptr : public apply_ptr <T, typename ENABLE::type> { };

template <class T> struct apply_ptr <T,  t_false> { typedef T type; };
template <class T> struct apply_ptr <T,  t_true>  { typedef T* type; };
template <class T> struct apply_ptr <T*, t_true>  { typedef T* type; };

//-----------------------------------------------------------------------------

template <class T, class ENABLE = t_true>
struct apply_const : public apply_const<T, typename ENABLE::type> {};

template <class T>
struct apply_const<T, t_false>
{
	typedef T type;
};

template <class T>
struct apply_const<T, t_true>
{
	typedef const T type;
};

template <class T>
struct apply_const<T&, t_true>
{
	typedef const T& type;
};

template <class T>
struct apply_const<const T&, t_true>
{
	typedef const T& type;
};

template <class T>
struct apply_const<T*, t_true>
{
	typedef const T* type;
};

template <class T>
struct apply_const<const T*, t_true>
{
	typedef const T* type;
};

//-----------------------------------------------------------------------------

template <class T, class OBJ>
struct best_ref :
	public best_ref<T, typename types::is_const<OBJ>::type> {};

template <class T>
struct best_ref<T, t_true>
{
	typedef const T& type;
};

template <class T>
struct best_ref<T&, t_true>
{
	typedef T& type;
};

template <class T>
struct best_ref<T, t_false>
{
	typedef typename apply_ref<T>::type type;
};

//-----------------------------------------------------------------------------

template <class T>
struct remove_const
{
	typedef T type;
};

template <class T>
struct remove_const<const T>
{
	typedef T type;
};

template <class T>
struct remove_const<const T*>
{
	typedef T* type;
};

template <class T>
struct remove_const<const T&>
{
	typedef T& type;
};

//-----------------------------------------------------------------------------

template <class T>
struct remove_ref
{
	typedef T type;
};

template <class T>
struct remove_ref<const T>
{
	typedef const T type;
};

template <class T>
struct remove_ref<T&>
{
	typedef T type;
};

template <class T>
struct remove_ref<const T&>
{
	typedef const T type;
};

//-----------------------------------------------------------------------------
// bare_type <T> gets the type T without reference and without const

template <class T>
struct bare_type
{
	typedef T type;
};

template <class T>
struct bare_type<T&>
{
	typedef T type;
};

template <class T>
struct bare_type<const T&>
{
	typedef T type;
};

template <class T>
struct bare_type<const T>
{
	typedef T type;
};

//-----------------------------------------------------------------------------

template <class T>
struct deref_ptr
{
	typedef T type;
};

template <class T>
struct deref_ptr<T*>
{
	typedef T type;
};

template <class T>
struct deref_ptr<const T*>
{
	typedef T type;
};

//-----------------------------------------------------------------------------

template <class T>
struct ref_to_ptr
{
	typedef T type;
};

template <class T>
struct ref_to_ptr <T&>
{
	typedef T* type;
};

template <class T>
struct ref_to_ptr <const T&>
{
	typedef const T* type;
};

//-----------------------------------------------------------------------------
// iavr

template <typename T> struct apply_ref_ptr      { typedef T& type; };
template <typename T> struct apply_ref_ptr <T&> { typedef T& type; };
template <typename T> struct apply_ref_ptr <T*> { typedef T* type; };

template <typename T> struct apply_ptr_ref      { typedef T* type; };
template <typename T> struct apply_ptr_ref <T&> { typedef T& type; };
template <typename T> struct apply_ptr_ref <T*> { typedef T* type; };

//-----------------------------------------------------------------------------

}  // namespace types
}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_TYPES_TYPES_HPP
