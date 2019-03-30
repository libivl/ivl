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

#ifndef IVL_CORE_DETAILS_MATH_CAST_HPP
#define IVL_CORE_DETAILS_MATH_CAST_HPP

namespace ivl {

// ... unfortunately here we need forward declarations
template <class J, class K> class cast_class;

template<class R, template<typename, typename> class F, class A>
struct unary_elem_func_result;

/* TODO: this was there. uncomment to play.
template<class R, class A>
inline
typename unary_elem_func_result<
	typename types::get_value<R>::type, cast_class, A>::type cast(const A& in);
	*/
// ...
/*
template<class R, class A>
inline
typename unary_elem_func_result<
	typename types::get_value<R>::type, cast_class, A>::type cast(const A& in);
*/

template<class R, class A>
inline
typename unary_elem_func_result<
	typename types::change_data_class_set_rec<data::fixed<1>, R>::type,
		cast_class, A>::type cast(const A& in);


namespace math {
namespace math_details {

// -----------------------------------------------------------

template <class T, bool BUILTIN>
struct spec_cast_complex_initializer { };

// converting an integer or floating-point type to complex requires .real()
template <class T>
struct spec_cast_complex_initializer<T, true>
{
	template <class S>
	static inline S from(const std::complex<S>& x) { return x.real(); }
};

// any other type should be implicitly converted if conversion is supported.
template <class T>
struct spec_cast_complex_initializer<T, false>
{
	template <class S>
	static inline const std::complex<S>& from(const std::complex<S>& x)
	{ return x; }
};

// conversion of complex to non-complex, not bool type, requires specialization
template <class T>
struct cast_complex_initializer
: public spec_cast_complex_initializer<T, types::is_builtin<T>::value>
{
};

// conversion of complex to bool returns true if .real() or .imag() is != 0
template <>
struct cast_complex_initializer<bool>
{
	template <class S>
	static inline bool from(const std::complex<S>& x)
	{ return x.real() || x.imag(); }
};

// -----------------------------------------------------------

template <class T>
struct cast_initializer : public cast_complex_initializer<T>
{
	using cast_complex_initializer<T>::from;

	template <class S>
	static inline const S& from(const S& x) { return x; }
};

template <class T>
struct cast_initializer<std::complex<T> >
{
	template <class S>
	static inline T from(const S& x) { return T(x); }

	template <class S>
	static inline std::complex<T> from(const std::complex<S>& x)
	{ return std::complex<T>(T(x.real()), T(x.imag())); }
};

// -----------------------------------------------------------

} /* namespace math_details */

template <class T, class S>
inline
T cast(const S& x)
{
	return T(math_details::cast_initializer<T>::from(x));
}

// -----------------------------------------------------------

namespace math_details {

template <class T, bool IS_ARRAY>
struct spec_elem_cast_result
{
};

template <class T>
struct spec_elem_cast_result<T, false>
{
	typedef T type;
	typedef T elem_type;
	template <class S>
	inline type from(const S& x)
	{
		return type(math_details::cast_initializer<T>::from(x));
	}
};

template <class A>
struct spec_elem_cast_result<A, true>
{
	typedef typename A::derived_type type;
	typedef typename A::elem_type elem_type;
	template <class S>
	inline type from(const S& x)
	{
		// note: need to have ivl::cast predeclared.
		// (which is defined in unary_elem_functions)
		return type(ivl::cast<elem_type>(x));
	}
};

/*
// on : todo.
// also decide like array<int> = array<double>;

template<class T>
struct elem_cast_result
: public spec_elem_cast_result<T, types::is_array<T>::value>
{
};
*/

} /* namespace math_details */

/*
// same as cast for simple elements
template <class T, class S>
inline
typename types_details::elem_cast_result<T>::type elem_cast(const S& x)
{
	return types_details::elem_cast_result<T>::from(x);
}
*/


} /* namespace math */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_MATH_CAST_HPP
