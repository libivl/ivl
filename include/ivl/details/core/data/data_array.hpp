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

#ifndef IVL_CORE_DETAILS_DATA_DATA_ARRAY_HPP
#define IVL_CORE_DETAILS_DATA_DATA_ARRAY_HPP

namespace ivl {

namespace data {

template <class D = types::term>
struct data_type_base
{
	enum { Ch = 0 };
};

// no arg
template <template<typename> class T, class D>
class data_type_base<T<D> >
: public data_type_base<>
{
public:
	template <class DT>
	struct change_derived_param
	{
		typedef T<DT> type;
	};
	typedef D derived_param;
};

// 1 arg, int
template <template<int, typename> class T, int N, class D>
class data_type_base<T<N, D> >
: public data_type_base<>
{
public:
	template <class DT>
	struct change_derived_param
	{
		typedef T<N, DT> type;
	};
	typedef D derived_param;
};

// 1 arg template
template <template<typename, typename> class T, class T1, class D>
class data_type_base<T<T1, D> >
: public data_type_base<>
{
public:
	template <class DT>
	struct change_derived_param
	{
		typedef T<T1, DT> type;
	};
	typedef D derived_param;
};

// 2 arg template
template <template<typename, typename, typename> class T,
	class T1, class T2, class D>
class data_type_base<T<T1, T2, D> >
: public data_type_base<>
{
public:
	template <class DT>
	struct change_derived_param
	{
		typedef T<T1, T2, DT> type;
	};
	typedef D derived_param;
};

// 3 arg template
template <template<typename, typename, typename, typename> class T,
	class T1, class T2, class T3, class D>
class data_type_base<T<T1, T2, T3, D> >
: public data_type_base<>
{
public:
	template <class DT>
	struct change_derived_param
	{
		typedef T<T1, T2, T3, DT> type;
	};
	typedef D derived_param;
};


// ---------------------------------------------------------------------------

// this is the definition of the default array data class
template <class DT = types::term>
struct mem : public data_type_base<mem<DT> >
{
	// note that these tags may be overwritten by the first array<...>
	// object. generally user should use the tags from the array class
	// and not from the data class.
	/** this tag indicates the best access method of the owning array in
	// terms of performance. Access methods are:
	// seq_optimal_tag: sequencial access, using begin() iterator and ++.
	// random_optimal_tag: random access, using indexes with [].
	// seq_nd_optimal_tag: sequential access per array dimension, using
	// the iterator_nd. This is of course possible for array_nd's only. **/
	typedef seq_optimal_tag optimal_access_tag;
	/** this tag is true if the array has the ability to access elements
	// at specific index. This means that the array has the [] operator on
	// the array class and the operations +, - on the iterator as well as [] and
	// difference between iterators. The contrary is that the elements can
	// only be accessed sequentially using an iterator. There is an important
	// note here: iterator_nd always has random access in all the kinds of
	// array_nd classes, though not all kinds of array classes can be
	// extended from array to array_nd using the same data class, e.g. mask type
	// is only array and not array_nd. If however there is an array_nd with
	// no random access, it means that we cannot access the elements using an
	// index on the array level of the class, for example with sub2ind.
	// we can still use the ( .., .., ..) operator for n-dimension random
	// access and also random operations on the iterator_nd as said.
	**/
	typedef types::t_true has_random_access;
	/** this tag is true if and only if the array has write access.
	//  the opposite is that the array is readonly.
	**/
	typedef types::t_true is_writeable;
	/** this tag is true if it is possible to create a new array to hold some
	// data using the data class, and basically the type of the owner array.
	// This can easily be false, e.g. subarray array types cannot be created
	// just like that to hold any data, because they reference other arrays.
	// More to that, the restriction for an array being createable is that
	// it supports a minimal set of constructors that are the specifications
	// for having the createable tag.
	// Those are:
	// constructor(): default constructor.
	// constructor(same_type): copy constructor. Note that same_type can
	//  either be array, array_nd, or any other class, and it is the same class
	//  as the owner class is.
	// constructor(array_type<...>): constructor from same level array
	//  object. Meaning that array_type can either be array, array_nd, or any
	//  other class like image, and array_type<...> will be a template class
	//  with any template parameters that only has the class level in common,
	//  e.g. it will be array_nd<J, D, P> if array_type is an array_nd.
	// constructor(size_type): construction with given size. size_type is
	//  actually array_type::size_type. Whether the size is single or
	//  multiple dimensional depends from array_type::size_type which depends
	//  from the type of the class, so this constructor specification is
	//  always valid.
	// constructor(size_type, array<J, D, P>): constructor with size_type and
	//  a single dimensional array. Uses the size to determine the new object's
	//  size and a single dimensional array to copy the data from in a linear
	//  way. If the data is to be folded into multiple dimensions this is done
	//  the standard ivl way which is inner dimensions first, like any normal c
	//  array with continuous data, and also like matlab arrays, having the
	//  standard ivl convention that the most inner dimension is the rows and
	//  second is the columns. This however doesn't matter at low levels when
	//  dimensions are treated as numbers.
	// **/
	typedef types::t_true is_createable;
	/** this tag is true if and only if the owner array can be resized and
	//  it has the standard resize functions. These are
	// resize(size_type)
	// resize(size_type, const elem_type&) where elem_type is the padding.
	//  Note that any writeable array must have the same functions defined
	//  as well, but they will merely do nothing but a size assertion in
	//  debug mode only. This convention is made to help writing ivl functions.
	**/
	typedef types::t_true is_resizeable;
	/** this tag is true if and only if it is possible to get a c pointer
	//  of the array data.
	//  note that has_c_ptr for array<bool, data::normal, K> is specialized
	//  to be t_false, and this is a limitation caused by the std::vector.
	**/
	typedef types::t_true has_c_ptr;
	/** this tag is true if and only if the array has direct acess to
	//  it's data members, and they are linearly stored in the memory.
	//  this practically means that the array is as fast as it should be,
	//  and there is not need to make any copies of that array when
	//  doing extensive processing on it's data.
	**/
	typedef types::t_true is_linear;
	/** has_specialized_iter: notes.
	// this tag is true if there are specialized iterators for faster
	// element access. the specialized iterators are obtained by a number.
	// this number is returned at runtime by a member function, and has
	// to be passed (using cases or iterations) in a template argument,
	// to get the actual iterator. Using a complicated procedure this is
	// automatically done in the loops section of ivl, using some iterations.
	// this makes this teqnique somehow equivalent to the use of virtual
	// functions of normal C++ derived classes, without the calling convention
	// overhead with multiplication of code size as tradeoff.
	// when there is specialized iterator this class shouldn't be t_true but
	// instead types::number<X> where X is the maximum integer number of
	// the specialized iterator type. count starts at 1, and the value 0
	// indicates the default iterator, when it comes to specializing. **/
	typedef types::t_false has_specialized_iter;
	/** is_referencing_array: notes.
	// this tag is true when the array is actually using data from another
	// array, either by reading, or writing them. This is needed to be known
	// so far for the overlap function that helps prevent reading and writing at
	// the same array at the same time.
	// Note that ref_iterator arrays, e.g. iter_array, is not a class
	// with the referencing_array tag because it does not reference to an
	// array but to iterators instead.
	**/
	typedef types::t_false is_referencing_array;
	/** this tag is an approximate evaluation of the cost of accessing one
	// element of the owner array, including the cost of the progression to
	// the next element whether this means ++ in a sequential access or
	// the [] in a random access, depending on the optimal tag.
	// The measuring scale is custom. The basis
	// is that 10 is the cost of a normal array which has direct access
	// to pointer data.
	// It is used to approximately evaluate the cost of some functions,
	// basically loops, at compile time, and chose the best method for coping
	// with a problem depending on that. It is the basis of introducing
	// multithreading when exceeding some cost.
	// This would mean that ivl takes advantage of multicore
	// architectures in the standard copy loops, when this is to our advantage
	// in terms of speed. Multithreading however may not be yet implemented
	// by now.
	**/
	typedef types::number<10> optimal_access_cost;
};

template<class DT = types::term>
struct empty
: public data_type_base<empty<DT> >
{
	typedef random_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	//is_linear is ambiguous here so the answer is: why optimize an empty array!
	typedef types::t_true is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	//avoid being absolute here and saying 0 as it could intruduce difficulties.
	typedef types::number<1> optimal_access_cost;
};

template<class DT = types::term>
struct blackhole
: public data_type_base<blackhole<DT> >
{
	typedef random_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_true is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	//is_linear is ambiguous here so the answer is: why optimize an empty array!
	typedef types::t_true is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	//avoid being absolute here and saying 0 as it could intruduce difficulties.
	typedef types::number<1> optimal_access_cost;
};


template <class T, T V, class DT = types::term>
struct fixed_val_repeat
: public data_type_base<>
{
public:
	template <class DERIVED_TYPE>
	struct change_derived_param
	{
		typedef fixed_val_repeat<T, V, DERIVED_TYPE> type;
	};
	typedef DT derived_param;

public:
	typedef random_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_true is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<5> optimal_access_cost;
};

template <class DT = types::term>
struct ref_val_repeat
: public data_type_base<ref_val_repeat<DT> >
{
	typedef random_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_true is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<8> optimal_access_cost;
};

template <class DT = types::term>
struct val_repeat
: public data_type_base<val_repeat<DT> >
{
	typedef random_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_true is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<7> optimal_access_cost;
};

template <class DT = types::term>
struct range
: public data_type_base<range<DT> >
{
	typedef seq_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<7> optimal_access_cost;
};

struct point_naming { };
struct dims_naming { };
struct color_naming { };

template <int N, class NAMING = types::term, class DT = types::term>
struct fixed
: public data_type_base<>
{
public:
	template <class DERIVED_TYPE>
	struct change_derived_param
	{
		typedef fixed<N, NAMING, DERIVED_TYPE> type;
	};
	typedef DT derived_param;

public:
	typedef random_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_true is_writeable;
	typedef types::t_true is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_true has_c_ptr;
	typedef types::t_true is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<9> optimal_access_cost;
};

template <int N = 4, bool USE_REALLOC = false, bool USE_PREALLOC = true,
	class DT = types::term>
struct stack
: public data_type_base<>
{
public:
	template <class DERIVED_TYPE>
	struct change_derived_param
	{
		typedef stack<N, USE_REALLOC, USE_PREALLOC, DERIVED_TYPE> type;
	};
	typedef DT derived_param;

public:
	typedef seq_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_true is_writeable;
	typedef types::t_true is_createable;
	typedef types::t_true is_resizeable;
	typedef types::t_true has_c_ptr;
	typedef types::t_true is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_false is_referencing_array;
	typedef types::number<10> optimal_access_cost;
};

typedef stack<> tiny;

// for const mode the usage of this is
// ref_iterator<array::const_iterator>
// for read-write mode the usage is
// ref_iterator<array::iterator, array::const_iterator>
// for fixed-length N it is
// wrap_iterator<array::iterator, array::const_iterator, N>
// for write-only access (not encouraged for in-library use) it is
// wrap_iterator<array::iterator>
// IT : the writeable iterator, or the best available iterator,
//      if set to not_a_type means there is only const iterator.
//      if set to types::term means the iterator is T*
// CONST_IT: the readable iterator. if set to types::term then there is
//      either no const iterator, or if IT is set to not_a_type then
//      we only have a const iterator and it is const T*
// LENGTH: 0 means variable length, stored in a size_t. > 0 for fixed length.
// HAS_C_PTR: normally should be t_false, and this doesn't cancel the c_ptr()
//      if it is possible from the given iterator. setting HAS_C_PTR to t_true
//      however, forces the class to have a c_ptr() member that gives as a
//      pointer. Setting this to deletable_c_ptr makes the array behave like
//      a storable_link meaning that it gets one more member, which is bool
//      and, if told so, it sets the bool to true, and at the destructor it
//      frees the iterator begin() which should be a pointer with the
//      standard c free(.); function. This is obviously for cases where the
//      data is temporary.

class deletable_c_ptr : public types::t_true { };

template <
	class IT = types::not_a_type,
	class CONST_IT = types::term,
	int LENGTH = 0,
	class HAS_C_PTR = types::t_false,
	class DT = types::term
>
struct ref_iterator
: public data_type_base<>
{
private:
	typedef typename types::t_if<types::t_and<
		types::t_eq<IT, types::term>, types::t_eq<CONST_IT, types::term> >,
		int*, typename types::t_if<types::t_and<
			types::t_eq<IT, types::not_a_type>,
			types::t_eq<CONST_IT, types::term> >,
			const int*, CONST_IT>::type>::
		type const_it_at;

	typedef typename types::t_if<types::t_or<types::t_eq<IT, types::term>,
		types::t_eq<IT, types::not_a_type> >, const_it_at, IT>
		::type iter_bt;

	typedef typename types::t_if<types::is_ivl_array<iter_bt>,
		typename types::best_iterator<
			typename types::t_if<types::is_ivl_array<iter_bt>, iter_bt,
				types::term>::type
		>::type, iter_bt>::type iter_t;

	typedef std::iterator_traits<iter_t> it_t;

public:
	template <class DER_TYPE>
	struct change_derived_param
	{
		typedef ref_iterator<IT, CONST_IT, LENGTH, HAS_C_PTR, DER_TYPE> type;
	};
	typedef DT derived_param;

public:
	typedef typename types::t_if<
			types::t_eq<typename it_t::iterator_category,
				std::random_access_iterator_tag>,
			random_optimal_tag, seq_optimal_tag>
											::type optimal_access_tag;

	typedef typename types::t_eq<
				typename it_t::iterator_category,
				std::random_access_iterator_tag>
											::type has_random_access;

	typedef typename types::t_not<
		types::is_const<typename it_t::reference> >
		 ::type is_writeable;

	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr; // overriden.
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef types::number<11> optimal_access_cost;
};

// various link (ref_iterator) data types
typedef ref_iterator<> const_link;
typedef ref_iterator<types::term, types::term> rw_link;
typedef ref_iterator<types::not_a_type, types::term, 0,
	deletable_c_ptr> storable_link;



template<template <typename, typename, typename> class F,
	class A1, class A2, bool SWAP_ARGS, class DT = types::term>
struct binary_elem_func_ptr
: public data_type_base<>
{
public:
	template <class DER_TYPE>
	struct change_derived_param
	{
		typedef binary_elem_func_ptr<F, A1, A2, SWAP_ARGS, DER_TYPE> type;
	};
	typedef DT derived_param;
public:

	typedef typename minimum_access_tag<
			typename A1::optimal_access_tag, typename A2::optimal_access_tag>
			::type optimal_access_tag;

	typedef typename types::t_and<
			typename A1::has_random_access, typename A2::has_random_access>
			::type has_random_access;

	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add_3<
			typename A1::optimal_access_cost,
			typename A2::optimal_access_cost,
			/*typename F<types::term,
				typename types::t_if<types::t_expr<!SWAP_ARGS>,
					typename types::get_value<A1>::type,
					typename types::get_value<A2>::type>::type,
				typename types::t_if<types::t_expr<!SWAP_ARGS>,
					typename types::get_value<A2>::type,
					typename types::get_value<A1>::type>::type>::cost>*/
			typename types::t_max<
				typename F<
					typename A1::elem_type,
					typename A1::elem_type,
					typename A2::elem_type>::cost,
				typename F<
					typename A2::elem_type,
					typename A1::elem_type,
					typename A2::elem_type>::cost
			>::type>

		::type optimal_access_cost;
};
template<template <typename, typename, typename> class F,
	class A1, class A2, bool SWAP_ARGS, class DT = types::term>
struct binary_elem_func
: public data_type_base<>
{
public:
	template <class DER_TYPE>
	struct change_derived_param
	{
		typedef binary_elem_func<F, A1, A2, SWAP_ARGS, DER_TYPE> type;
	};
	typedef DT derived_param;
public:

	typedef typename minimum_access_tag<
			typename A1::optimal_access_tag, typename A2::optimal_access_tag>
			::type optimal_access_tag;

	typedef typename types::t_and<
			typename A1::has_random_access, typename A2::has_random_access>
			::type has_random_access;

	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add_3<
			typename A1::optimal_access_cost,
			typename A2::optimal_access_cost,
			/*typename F<types::term,
				typename types::t_if<types::t_expr<!SWAP_ARGS>,
					typename types::get_value<A1>::type,
					typename types::get_value<A2>::type>::type,
				typename types::t_if<types::t_expr<!SWAP_ARGS>,
					typename types::get_value<A2>::type,
					typename types::get_value<A1>::type>::type>::cost>*/
			typename types::t_max<
				typename F<
					typename A1::elem_type,
					typename A1::elem_type,
					typename A2::elem_type>::cost,
				typename F<
					typename A2::elem_type,
					typename A1::elem_type,
					typename A2::elem_type>::cost
			>::type>

		::type optimal_access_cost;
};

	

template<template <typename, typename> class F, class A, class DT = types::term>
struct unary_elem_func
: public data_type_base<unary_elem_func<F, A, DT> >
{
public:
	template <class DER_TYPE>
	struct change_derived_param
	{
		typedef unary_elem_func<F, A, DER_TYPE> type;
	};
	typedef DT derived_param;
public:

	typedef typename A::
			optimal_access_tag optimal_access_tag;

	typedef typename A::
			has_random_access has_random_access;

	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;

	typedef typename types::t_add<
			typename A::optimal_access_cost,
			typename F<
				typename types::get_value<A>::type,
				typename types::get_value<A>::type>::cost
		>::type optimal_access_cost;
};

template<class F, class A, class DT = types::term>
struct row_elem_func_2d
: public data_type_base<row_elem_func_2d<F, A, DT> >
{
	typedef seq_optimal_tag optimal_access_tag;
	typedef types::t_true has_random_access;
	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add<
			typename A::optimal_access_cost,
			typename F::cost
		>::type optimal_access_cost;
};

template<class F, class A, class DT = types::term>
struct row_elem_func_nd
: public data_type_base<row_elem_func_nd<F, A, DT> >
{
	typedef nd_seq_optimal_tag optimal_access_tag;
	typedef typename A::has_random_access has_random_access;
	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add<
			typename A::optimal_access_cost,
			typename F::cost
		>::type optimal_access_cost;
};

// wrap

struct ice_wrap_array_attr_base_identifier {};
template <class ATTR> struct wrap_identifier {};

struct force_wrap_array_attr {};
struct ice_wrap_array_attr : public ice_wrap_array_attr_base_identifier {};
struct ices_wrap_array_attr : public ice_wrap_array_attr_base_identifier {};
template <class T>
struct icers_wrap_array_attr : public ice_wrap_array_attr_base_identifier {};

template<class A, class ATTR = types::term, class DT = types::term>
struct wrap_array
: public data_type_base<wrap_array<A, ATTR, DT> >, public ATTR
{
	typedef typename A::optimal_access_tag optimal_access_tag;
	typedef typename A::has_random_access has_random_access;
	typedef typename types::t_and<
		types::t_not<types::is_const<A> >, typename A::is_writeable>
		::type is_writeable;

	typedef types::t_false is_createable;
	typedef typename A::is_resizeable is_resizeable;
	typedef typename A::has_c_ptr has_c_ptr;
	typedef typename A::is_linear is_linear;

	// this should actually be typename A::has_specialized_iter;
	// note: could fix this: add the specialized_iter calls for this class.
	// however this would complicate things, because array_nd level class
	// should be specialized too. Another approach is to have special
	// treatment for subarrays when force() is used, and apply force on
	// the referenced array.
	//todo:
	// Also, consider that, when specialized_iter stuff is used, the same
	// should be done for elem funcs, so if this is fixed, it needs to
	// be fixed on elem_funcs as well.
	typedef types::t_false has_specialized_iter;
	//typedef typename A::has_specialized_iter has_specialized_iter;

	//this is the most important tag for this class. we are faking (on force).
	typedef typename types::t_if<types::t_eq<ATTR, force_wrap_array_attr>,
		types::t_false, types::t_true>::type is_referencing_array;

	typedef typename A::optimal_access_cost optimal_access_cost;
};
/*
template<class A>
struct forced
{
	typedef typename A::optimal_access_tag optimal_access_tag;
	typedef typename A::has_random_access has_random_access;
	typedef typename types::t_and<
		types::t_not<types::is_const<A> >, typename A::is_writeable>
		::type is_writeable;

	typedef types::t_false is_createable;
	typedef typename A::is_resizeable is_resizeable;
	typedef typename A::has_c_ptr has_c_ptr;
	typedef typename A::is_linear is_linear;

	// this should actually be typename A::has_specialized_iter;
	// note: could fix this: add the specialized_iter calls for this class.
	// however this would complicate things, because array_nd level class
	// should be specialized too. Another approach is to have special
	// treatment for subarrays when force() is used, and apply force on
	// the referenced array.
	//todo:
	// Also, consider that, when specialized_iter stuff is used, the same
	// should be done for elem funcs, so if this is fixed, it needs to
	// be fixed on elem_funcs as well.
	typedef types::t_false has_specialized_iter;
	//typedef typename A::has_specialized_iter has_specialized_iter;

	//this is the most important tag for this class. we are faking.
	typedef types::t_false is_referencing_array;

	typedef typename A::optimal_access_cost optimal_access_cost;
};
*/
template<class A, class B, class DT = types::term>
struct member
: public data_type_base<member<A, B, DT> >
{
	typedef typename A::optimal_access_tag optimal_access_tag;
	typedef typename A::has_random_access has_random_access;
	typedef typename types::t_and<
		types::t_not<types::is_const<A> >, typename A::is_writeable>
		::type is_writeable;

	typedef types::t_false is_createable;
	typedef typename A::is_resizeable is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add<
		typename A::optimal_access_cost,
			 types::number<5>
		>::type optimal_access_cost;
};

template<class A, class B, class DT = types::term>
struct mask
: public data_type_base<mask<A, B, DT> >
{
	typedef data::seq_optimal_tag optimal_access_tag;

	typedef types::t_false has_random_access;

	typedef typename types::t_and<
		types::t_not<types::is_const<A> >, typename A::is_writeable>
		::type is_writeable;

	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add_3<
			typename A::optimal_access_cost,
			types::t_mul<types::number<5>, typename B::optimal_access_cost>,
			types::number<10>
		>::type optimal_access_cost;
};

template<class A, class B, class DT = types::term>
struct indirect
: public data_type_base<indirect<A, B, DT> >
{
private:
	typedef typename types::bare_type<B>::type b_t;
public:
	typedef typename minimum_access_tag<
		typename A::optimal_access_tag, typename b_t::optimal_access_tag>
		::type optimal_access_tag;

	typedef typename types::t_and<
			typename A::has_random_access, typename b_t::has_random_access>
			::type has_random_access;

	typedef typename types::t_and<
			types::t_not<types::is_const<A> >, typename A::is_writeable>
			::type is_writeable;

	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add_3<
			typename A::optimal_access_cost,
			typename b_t::optimal_access_cost,
			types::number<0>
		>::type optimal_access_cost;
};

template<class A, class DT = types::term>
struct slice
: public data_type_base<slice<A, DT> >
{
	typedef seq_optimal_tag optimal_access_tag;

	typedef types::t_true has_random_access;

	typedef typename types::t_and<
			types::t_not<types::is_const<A> >, typename A::is_writeable>
			::type is_writeable;

	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add<
			typename A::optimal_access_cost,
			types::number<10>
		>::type optimal_access_cost;
};

template <class A, class I, class DT = types::term>
struct subarray
: public data_type_base<subarray<A, I, DT> >
{
	typedef nd_seq_optimal_tag optimal_access_tag;
	typedef types::t_false has_random_access;

	typedef typename types::t_if<
		types::t_not<types::is_const<A> >, typename A::is_writeable,
		types::t_false>
		::type is_writeable;

	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::number<2> has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add<
			typename A::optimal_access_cost,
			types::number<70>
		>::type optimal_access_cost;
};

template <class A1, class A2, int CATDIM = -1, class DT = types::term>
struct catarray
: public data_type_base<>
{
protected:
	typedef typename types::bare_type<A1>::type a1_t;
	typedef typename types::bare_type<A2>::type a2_t;
public:
	template <class DER_TYPE>
	struct change_derived_param
	{
		typedef catarray<A1, A2, CATDIM, DER_TYPE> type;
	};
	typedef DT derived_param;
public:

	typedef nd_seq_optimal_tag optimal_access_tag;
	typedef typename types::t_and<
		typename a1_t::has_random_access, typename a2_t::has_random_access>
		::type has_random_access;

	typedef typename types::t_and<types::t_and<
			types::t_not<types::is_const<A1> >, typename a1_t::is_writeable>,
		types::t_and<
			types::t_not<types::is_const<A2> >, typename a2_t::is_writeable> >
		::type is_writeable;

	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;

	/*
	typedef typename types::t_if<types::t_expr<CATDIM == -1>,
		types::number<2>, types::t_false>
		::type has_specialized_iter;
	*/
	typedef types::t_false has_specialized_iter;

	typedef types::t_true is_referencing_array;
	typedef typename types::t_add_3<
			typename a1_t::optimal_access_cost,
			typename a2_t::optimal_access_cost,
			types::number<70>
		>::type optimal_access_cost;
};

//-----------------------------------------------------------------------------

template<template <typename, typename, typename> class F,
	class A1, class A2, class DT = types::term>
struct outersp
: public data_type_base<>
{
public:
	template <class DER_TYPE>
	struct change_derived_param
	{
		typedef outersp<F, A1, A2, DER_TYPE> type;
	};
	typedef DT derived_param;
public:

	typedef typename minimum_access_tag<
			typename A1::optimal_access_tag, typename A2::optimal_access_tag>
			::type optimal_access_tag;

	typedef typename types::t_and<
			typename A1::has_random_access, typename A2::has_random_access>
			::type has_random_access;

	typedef types::t_false is_writeable;
	typedef types::t_false is_createable;
	typedef types::t_false is_resizeable;
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	typedef types::t_false has_specialized_iter;
	typedef types::t_true is_referencing_array;
	typedef typename types::t_add_3<
			typename A1::optimal_access_cost,
			typename A2::optimal_access_cost,
			/*typename F<types::term,
				typename types::t_if<types::t_expr<!SWAP_ARGS>,
					typename types::get_value<A1>::type,
					typename types::get_value<A2>::type>::type,
				typename types::t_if<types::t_expr<!SWAP_ARGS>,
					typename types::get_value<A2>::type,
					typename types::get_value<A1>::type>::type>::cost>*/
			typename types::t_max<
				typename F<
					typename A1::elem_type,
					typename A1::elem_type,
					typename A2::elem_type>::cost,
				typename F<
					typename A2::elem_type,
					typename A1::elem_type,
					typename A2::elem_type>::cost
			>::type>

		::type optimal_access_cost;
};

//-----------------------------------------------------------------------------

template<class TP, class DT = types::term>
struct tup2arr
: public data_type_base<tup2arr<TP, DT> >
{
protected:
	typedef typename types::bare_type<TP>::type bare_tp_type;
	
public:
	// TODO: before doing anything meta on TP, make sure to bare_type it.


	// TODO: perform tuple seq using 'minimum_access_tag' 
	// and getter for ::optimal_access_tag for TP, to calculate tag.
	typedef seq_optimal_tag optimal_access_tag;

	// TODO: perform tuple seq using 't_and' 
	// and getter for ::has_random_access for TP, to calculate tag.
	// TODO: t_true!! it is simply an untested requirement.
	typedef types::t_true has_random_access;

	// TODO: this is the most tricky of all...
	// The reason is that, one-writeable x many-readable should
	// actually be semi-writeable. What this means?
	// a[x].v1 = y; is valid, where a[x].v2 = z is not.
	// However, C++ should say that, a[x].v1 = y is valid if
	// type of a[x].v1 is T&, even if type of a[x] is const A&
	// (the last statement has a PROBABLY, not certain, however
	// seems to be like the case where const struct allows
	// writes to non-const pointer which is OK).
	// SO: final conclusion is: such case can still be named readable
	// and work fine for a[x].v1 = y. Still, to do a[x] = b, we
	// do need ALL to be writeable, hence, we again, simply, do
	// seq, t_and, ::is_writeable.
	// We overstate t_true, in order to test for our custom needs.
	typedef types::t_true is_writeable;
	typedef types::t_false is_createable;
	
	// TODO: this is very tricky! Such arrays can be resizable indeed.
	// just seq 't_and' with getter '::is_resizeable' is enough
	// for now: making overstatement t_true or understatement t_false?
	typedef types::t_true is_resizeable;
	
	typedef types::t_false has_c_ptr;
	typedef types::t_false is_linear;
	
	// TODO: what if one bottom has specialized iter?
	// but this case is also in many.
	// Also, can't be handled easily for multiple specialized bottoms.
	// could be fixated to become true for exactly one base, 
	// performance issue
	typedef types::t_false has_specialized_iter;
	
	typedef types::t_true is_referencing_array;
	
	// TODO: seq, add, ::optimal_access_cost. After that, 
	// add a constant which would probably be analogue to tuple size.
	typedef types::number<50> optimal_access_cost;
};

//-----------------------------------------------------------------------------


} //namespace data

typedef data::mem<> mem;
using data::fixed_val_repeat;
typedef data::ref_val_repeat<> ref_val_repeat;
typedef data::val_repeat<> val_repeat;
using data::fixed;
using data::stack;
using data::tiny;
using data::ref_iterator;
using data::const_link;
using data::rw_link;
//using data::storable_link;
using data::wrap_array;
//typedef data::empty<> emptydt;
//typedef data::range<> rangedt;
//using data::maskdt;
//using data::indirectdt;
//using data::slicedt;
//using data::subarraydt;
//using data::binary_elem_funcdt;
//using data::unary_elem_funcdt;
//using data::row_elem_func_2ddt;
//using data::row_elem_func_nddt;

using data::catarray;


} //namespace ivl



#endif // IVL_CORE_DETAILS_DATA_DATA_ARRAY_HPP
