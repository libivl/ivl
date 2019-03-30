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

#ifndef IVL_CORE_DETAILS_TYPES_DETECT_HPP
#define IVL_CORE_DETAILS_TYPES_DETECT_HPP

namespace ivl {
namespace types {

template <class T>
class is_integer : public t_false { };

#include "platform_specific/is_integer_impl.hpp"

template <class T>
class is_bool : public t_false { };

template <>
class is_bool<bool> : public t_true { };

// ---------

template <class T>
class is_signed : public t_true { };

template <>
class is_signed<unsigned char> : public t_false { };

template <>
class is_signed<unsigned short> : public t_false { };

template <>
class is_signed<unsigned int> : public t_false { };

template <>
class is_signed<unsigned long> : public t_false { };

template <>
class is_signed<unsigned long long> : public t_false { };

// ---------

template <class T>
class is_floating : public t_false { };

template <>
class is_floating<float> : public t_true { };

template <>
class is_floating<double> : public t_true { };

template <>
class is_floating<long double> : public t_true { };

template <class T>
class is_builtin :
	public t_or_3<is_integer<T>, is_bool<T>, is_floating<T> >::type {};

// ---------

template <class T>
class is_ptr : public t_false { };

template <class T>
class is_ptr<T*> : public t_true { };

template <class T>
class is_ptr<const T*> : public t_true { };

template <class T>
class is_ref : public t_false { };

template <class T>
class is_ref<T&> : public t_true { };

template <class T>
class is_ref<const T&> : public t_true { };

template <class T>
class is_c_array : public t_false { };

template <int N, class T>
class is_c_array<T[N]> : public t_true { };

template <int N, class T>
class is_c_array<const T[N]> : public t_true { };

// ---------

template <class T>
class is_complex : public t_false { };

template <class T>
class is_complex<std::complex<T> > : public t_true { };

template <class T>
class is_num_value :
	public t_or<is_builtin<T>, is_complex<T> >::type {};

// ----------------------------------------------------------------------------

namespace types_details {

template <class B, class D>
struct is_base_match
{
	template <class T>
	static inline t_detect<t_true> check(const D& , T) ;
	static inline t_detect<t_false> check(const B& , int) ;
};

template <class B, class D>
struct is_base_struct
{
	struct convert
	{
		operator const B& () const;
		operator const D& ();
	};

	enum {
		is_base_value = (sizeof(is_base_match<B, D>::
					check(convert(), 0)) == sizeof(t_detect<t_true>))
	};

	typedef typename t_expr<is_base_value>::type type;
};

// ----------------------------------------------------------------------------

// iavr
template <class B>
struct is_base_struct <B, void> : public t_false { };

template <class D>
struct is_base_struct <void, D> : public t_false { };

template <>
struct is_base_struct <void, void> : public t_false { };

// ----------------------------------------------------------------------------

template <class B, class D>
struct is_base_conv_match
{
	template <class T>
	static inline t_detect<t_true> check(const D& , T) ;
	static inline t_detect<t_false> check(B , int) ;
};

template <class B, class D>
struct is_base_conv_struct
{
	struct convert
	{
		operator B () const;
		operator const D& ();
	};

	enum {
		is_base_value = (sizeof(is_base_conv_match<B, D>::
					check(convert(), 0)) == sizeof(t_detect<t_true>))
	};

	typedef typename t_expr<is_base_value>::type type;
};

// ----------------------------------------------------------------------------

// iavr
template <class B>
struct is_base_conv_struct <B, void> : public t_false { };

template <class D>
struct is_base_conv_struct <void, D> : public t_false { };

template <>
struct is_base_conv_struct <void, void> : public t_true { };

// ----------------------------------------------------------------------------

template <class B, class D>
struct is_eq_conv_match
{
	static inline t_detect<t_true> check(B) ;
	static inline t_detect<t_false> check(...) ;
};

template <class B, class D>
struct is_eq_conv_struct
{
	struct convert
	{
		operator D () const;
	};

	enum {
		is_base_value = (sizeof(is_eq_conv_match<B, D>::
					check(convert())) == sizeof(t_detect<t_true>))
	};

	typedef typename t_expr<is_base_value>::type type;
};

// ----------------------------------------------------------------------------

// iavr
template <class B>
struct is_eq_conv_struct <B, void> : public t_false { };

template <class D>
struct is_eq_conv_struct <void, D> : public t_false { };

template <>
struct is_eq_conv_struct <void, void> : public t_true { };

// ----------------------------------------------------------------------------


}; /* namespace types_details */

// ----------------------------------------------------------------------------

template <class B, class D>
struct is_base_conv
: public types_details::is_base_conv_struct<B, D>::type
{
};

template <class D, class B>
struct is_conv
: t_or<types_details::is_base_conv_struct<B, D>,
       types_details::is_eq_conv_struct<B, D> > { };

// ----------------------------------------------------------------------------

template <class B, class D>
struct is_base
: public types_details::is_base_struct<B, D>::type
{
};

// Note: Added this specialization to remove problems with references checked.
// TODO: needs proper thought.
template <class B, class D>
struct is_base<B, D&>
: public types::t_false
{
};

// ----------------------------------------------------------------------------

template <class B, class D>
struct is_base_eq
: public types_details::is_base_struct<B, D>::type
{
};

// Note: Added this specialization to remove problems with references checked.
// TODO: needs proper thought.
template <class B, class D>
struct is_base_eq<B, D&>
: public types::t_false
{
};

// Note: Added this specialization to remove problems with references checked.
// TODO: needs proper thought.
template <class D>
struct is_base_eq<D&, D&>
: public types::t_true
{
};


template <class A>
struct is_base_eq<A, A> : public t_true { };

// ----------------------------------------------------------------------------

template <class A, class B>
struct is_related
: public t_or<is_base_eq<A, B>, is_base_eq<B, A> > { };

// ----------------------------------------------------------------------------

template <class A>
struct is_ivl_array
: public t_and_3<typename is_base<array_identifier, A>::type,
	t_not<typename is_base_eq<scalar_identifier, A>::type>,
	t_not<typename is_base_eq<index_array, A>::type > >::type
{
};

////needed for compilation:
template <class T, class S>
struct is_ivl_array<array<T, S> > : public t_true { };

// ----------------------------------------------------------------------------

// SFINAE (determination) has ::type mechanism

template <typename T>
struct has_typedef_const_reference {

    template <typename C>
    static t_detect<t_true>& test(typename C::const_reference*);

    template <typename>
    static t_detect<t_false>& test(...);

    // If the "sizeof" the result of calling test<T>(0) would be equal to the sizeof(yes),
    // the first overload worked and T has a nested type named foobar.
    //static const bool value = sizeof(test<T>(0)) == sizeof(yes);
	enum {
		has_type_value = (sizeof(test<T>(0)) == sizeof(t_detect<t_true>))
	};

	typedef typename t_expr<has_type_value>::type type;
};

// ----------------------------------------------------------------------------

// SFINAE (determination) has ::type mechanism

template <typename T>
struct has_typedef_type {

    template <typename C>
    static t_detect<t_true>& test(typename C::type*);

    template <typename>
    static t_detect<t_false>& test(...);

    // If the "sizeof" the result of calling test<T>(0) would be equal to the sizeof(yes),
    // the first overload worked and T has a nested type named foobar.
    //static const bool value = sizeof(test<T>(0)) == sizeof(yes);
	enum {
		has_type_value = (sizeof(test<T>(0)) == sizeof(t_detect<t_true>))
	};

	typedef typename t_expr<has_type_value>::type type;
};

// ----------------------------------------------------------------------------

// SFINAE (determination) is class mechanism

template <typename T>
struct has_typedef_base_class {

    template <typename C>
    static t_detect<t_true>& test(typename C::base_class*);

    template <typename>
    static t_detect<t_false>& test(...);

    // If the "sizeof" the result of calling test<T>(0) would be equal to the sizeof(yes),
    // the first overload worked and T has a nested type named foobar.
    //static const bool value = sizeof(test<T>(0)) == sizeof(yes);
	enum {
		has_type_value = (sizeof(test<T>(0)) == sizeof(t_detect<t_true>))
	};

	typedef typename t_expr<has_type_value>::type type;
};

// ----------------------------------------------------------------------------

} /* namespace types */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TYPES_DETECT_HPP
