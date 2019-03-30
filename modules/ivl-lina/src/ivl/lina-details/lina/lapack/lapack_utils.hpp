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

#ifndef IVL_LINA_DETAILS_LAPACK_UTILS_HPP
#define IVL_LINA_DETAILS_LAPACK_UTILS_HPP

//#include "../../../array_2d.hpp"

#include "ivl/exceptions.hpp"
#include "ivl/details/array.hpp"
#include "ivl/details/array_nd.hpp"
#include "ivl/details/array_2d.hpp"



#include "../lina_typemap.hpp"
#include "lapack_algorithms.hpp"
#include "ivl_lapack_types.hpp"

namespace ivl {
namespace lina_details {

namespace defs {
extern const clapack::complex cmpl_1;
extern const clapack::complex cmpl_0;
extern const clapack::doublecomplex dcmpl_1;
extern const clapack::doublecomplex dcmpl_0;

template<class T>
struct value {};

template<>
struct value<clapack::complex>
{
	static const clapack::complex zero;
	static const clapack::complex one;
};

template<>
struct value<clapack::doublecomplex>
{
	static const clapack::doublecomplex zero;
	static const clapack::doublecomplex one;
};

template<>
struct value<clapack::real>
{
	static const clapack::real zero;
	static const clapack::real one;
};

template<>
struct value<clapack::doublereal>
{
	static const clapack::doublereal zero;
	static const clapack::doublereal one;
};

} //namespace defs


/* lapack typemap specializations...*/
template<class T> struct type_map { typedef T type; };

template<> struct type_map<clapack::complex>
	{ typedef clapack::real type; };
template<> struct type_map<clapack::doublecomplex>
	{ typedef clapack::doublereal type; };

/* lapack_type. type mapping from std::complex to clapack::complex */
template<class KEY> struct lapack_type { typedef KEY type; };

/* lapack_type specializations... */
template<> struct lapack_type<std::complex<clapack::real> >
	{ typedef clapack::complex type; };
template<> struct lapack_type<std::complex<clapack::doublereal> >
	{ typedef clapack::doublecomplex type; };

/* std_type. type mapping from clapack::complex to std::complex */
template<class KEY> struct std_type { typedef KEY type; };
/* std_type specializations... */
template<> struct std_type<clapack::complex>
	{ typedef std::complex<clapack::real> type; };
template<> struct std_type<clapack::doublecomplex>
	{ typedef std::complex<clapack::doublereal> type; };


//converters

// wrap a standard pointer to elements including std::complex to a pointer
// of lapack element types. the original pointer is used for input and output.
template <class T>
class lapack_from_std_in_out
{
public:
	typename lapack_type<T>::type* ptr;

	lapack_from_std_in_out(T* src_and_dst, size_t)
	{
		/* harshly convert a std::complex<T> to a pointer to lapack complex
		this could theoretically cause incompatibility.
		the safe way which would reduce speed is to create two specializations
		for lapack complex and doublecomplex.
		at constructor a new array and copy the real part and the imaginary part
		element-by-element to the temporary array. At the destructor do the
		opposite, copy everything back to the original array.
		The ptr should point to the temporary array's pointer.*/

		ptr = reinterpret_cast<typename lapack_type<T>::type*>(src_and_dst);
	}
};

// wrap a standard pointer to elements including std::complex to a pointer
// of lapack element types. the original pointer is used for output only.
template <class T>
class lapack_from_std_out
{
public:
	typename lapack_type<T>::type* ptr;

	lapack_from_std_out(T* dst, size_t)
	{
		/* harshly convert a std::complex<T> to a pointer to lapack complex
		this could theoretically cause incompatibility.
		the safe way which would reduce speed is to create two specializations
		for lapack complex and doublecomplex.
		at constructor a temporary array and get the pointer. At the destructor
		copy everything from the temporary to the dst array.
		The ptr should point to the temporary array's pointer.*/

		ptr = reinterpret_cast<typename lapack_type<T>::type*>(dst);
	}
};

// wrap a standard pointer to elements including std::complex to a pointer
// of lapack element types. the original pointer is used for input only.
template <class T>
class lapack_from_std_const
{
public:
	const typename lapack_type<T>::type* ptr;

	lapack_from_std_const(const T* src, size_t)
	{
		/* harshly convert a std::complex<T> to a pointer to lapack complex.
		the safe way is to copy everything to a temporary array, and at the
		destructor simply destroy the temporary array */
		ptr = reinterpret_cast<const typename lapack_type<T>::type*>(src);
	}
};


// wrap a standard pointer to elements including std::complex to a pointer
// of lapack element types. the original pointer is used for input only.
template <class T>
class lapack_from_std_clone
{
public:
	typedef typename lapack_type<T>::type lapack_type;
	lapack_type* ptr;
	array<lapack_type> a;

	lapack_from_std_clone(const T* src, size_t n) :
		a(n, reinterpret_cast<const lapack_type*>(src))
	{
		/* harshly convert a std::complex<T> to a pointer to lapack complex.
		the safe way is to construct each complex. */
		ptr = a.c_ptr();
	}
};

// convert a single element from lapack complex to std::complex.
template <class T>
const typename std_type<T>::type& lapack_to_std(const T& x)
{
	return reinterpret_cast<const typename std_type<T>::type&>(x);
}
// convert a single element from lapack complex to std::complex.
template <class T>
const typename lapack_type<T>::type& std_to_lapack(const T& x)
{
	return reinterpret_cast<const typename lapack_type<T>::type&>(x);
}


#if 0
//converter for array a
void lapack_to_std(const array<clapack::complex> &src,
		   std::complex<clapack::real> *dst);

void lapack_to_std(const array<clapack::doublecomplex> &src,
		   std::complex<clapack::doublereal> *dst);

void std_to_lapack(const std::complex<clapack::real> *src,
		   array<clapack::complex> &dst);

void std_to_lapack(const std::complex<clapack::doublereal> *src,
		   array<clapack::doublecomplex> &dst);

//converter for array
void lapack_to_std(const array<clapack::complex> &src,
		   array<std::complex<clapack::real> > &dst);

void lapack_to_std(const array<clapack::doublecomplex> &src,
		   array<std::complex<clapack::doublereal> > &dst);

void std_to_lapack(const array<std::complex<clapack::real> > &src,
		   array<clapack::complex> &dst);

void std_to_lapack(const array<std::complex<clapack::doublereal> > &src,
		   array<clapack::doublecomplex> &dst);

// generalisation of converter, for non complex arrays.
template<class T>
inline
void lapack_to_std(const array<T> &src, array<T> &dst)
{
	dst = src;
}

template<class T>
inline
void std_to_lapack(const array<T> &src, array<T> &dst)
{

	dst = src;
}

//lapack_to_std convertion for single element
inline clapack::real lapack_to_std(
		const clapack::real& v) {  return v; }

inline clapack::doublereal lapack_to_std(
		const clapack::doublereal& v) { return v; }

inline std::complex<clapack::real> lapack_to_std(
		const clapack::complex& v)
{
	return std::complex<clapack::real> (v.r, v.i);
}

inline std::complex<clapack::doublereal> lapack_to_std(
		const clapack::doublecomplex& v)
{
	return std::complex<clapack::doublereal> (v.r, v.i);
}

//std_to_lapack reverse conversion for single element
inline clapack::real std_to_lapack(
		const clapack::real& v) { return v; }

inline clapack::doublereal std_to_lapack(
		const clapack::doublereal& v) { return v; }

inline clapack::complex std_to_lapack(
		const std::complex<clapack::real>& v)
{
	clapack::complex r;
	r.r = v.real(); r.i = v.imag();
	return r;
}

inline clapack::doublecomplex std_to_lapack(
		const std::complex<clapack::doublereal>& v)
{
	clapack::doublecomplex r;
	r.r = v.real(); r.i = v.imag();
	return r;
}
#endif

/*
 * lwork_cast is needed to cast the optimal lwork size as output by the
 * lapack routines to clapack::integer.
 */
inline
clapack::integer lwork_cast(clapack::real& lwork)
{
	return (clapack::integer) lwork;
}

inline
clapack::integer lwork_cast(clapack::doublereal& lwork)
{
	return (clapack::integer) lwork;
}

inline
clapack::integer lwork_cast(clapack::complex&  lwork)
{
	return (clapack::integer) lwork.r;
}

inline
clapack::integer lwork_cast(clapack::doublecomplex& lwork)
{
	return (clapack::integer) lwork.r;
}

// wrap a standard pointer to elements including std::complex to a pointer
// of lapack element types. the original pointer is used for output only.
template <class T>
class lapack_from_std_out_and_unroll
{
private:
	typedef std::complex<T> ct;
	ct* dst;
	ct* w_ptr;
	array_2d<typename lapack_type<T>::type> a;

	static void unroll_vr();

public:
	typename lapack_type<T>::type* ptr;

	lapack_from_std_out_and_unroll(ct* dst, ct* w, size_t rows, size_t cols)
		: dst(dst), w_ptr(w), a(rows, cols)
	{
		ptr = a.c_ptr();
	}

	~lapack_from_std_out_and_unroll()
	{
		unroll<T>::unroll_vr(w_ptr, a, dst);
	}
};

template<>
class lapack_from_std_out_and_unroll<clapack::complex>
{
private:
	typedef std::complex<clapack::real> tp;

	lapack_from_std_out<tp> l;

public:
	lapack_type<tp>::type* ptr;

	lapack_from_std_out_and_unroll(tp* dst, tp* w, size_t rows, size_t cols)
		: l(dst, rows * cols)
	{
		/* convert lapack from std.*/
		ptr = l.ptr;
	}
};

template<>
class lapack_from_std_out_and_unroll<clapack::doublecomplex>
{
private:
	typedef std::complex<clapack::doublereal> tp;

	lapack_from_std_out<tp> l;

public:
	lapack_type<tp>::type* ptr;

	lapack_from_std_out_and_unroll(tp* dst, tp* w, size_t rows, size_t cols)
		: l(dst, rows * cols)
	{
		/* convert lapack from std.*/
		ptr = l.ptr;
	}
};


} /* namespace lina_details */
} /* namespace ivl */

#endif // IVL_LINA_DETAILS_LAPACK_UTILS_HPP
