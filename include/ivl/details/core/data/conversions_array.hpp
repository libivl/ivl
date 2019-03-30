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

#ifndef IVL_CORE_DETAILS_DATA_CONVERSIONS_ARRAY_HPP
#define IVL_CORE_DETAILS_DATA_CONVERSIONS_ARRAY_HPP

namespace ivl {

namespace data {



// The following structs describe the promotions that happen to the data types
// when new arrays are automatically created as function return values.
// Depending in the input array type the following transitions occur.
//
// array_creation: the type of the created array<T, ..> classes
// array_nd_creation: the type of the created array_nd<T, ..> classes
// derived_creation: the type of the classes that are created using the
//	new_derived or similar_derived typedefs, but only when the derived
//	class is below the array_nd class.
//
// similar_type defines the creation when a similar type is requested using
//	the appropriate typedef.
// new_type defines the creation type of a request for a completely new array.
// the difference has to do with the shape of the new array.
// a new_type is supposed to be freely resizable.
// It is also guaranteed to be able to be created, using the constructor
//		new_type(input_array_of_same_level::size_type)
// a similar_type is supposed to be able to hold the exact same size of the
// 	input array using strictly the constructor
//		similar_type(input_array_of_same_level::size_type)
// In the cases above, the input_array_of_same_level is an array when
// 	the created type is an array, an array_nd when the created type is
// 	an array_nd, and a ::derived_type when the created type is of the
//	form ::derived_type<T,...>, so the assumption that there is a valid
//	constructor that takes the ::size_type is always qualified,
//	as long as the conversions below are well-defined.
// Furthermore, is some cases, where both similar_type and new_type
// are resizable, it would be wise for similar_type to be declared to
// a type that could be more easily resized, to the predicted size
// of the initial array. data::little is a that kind of example,
// when we are expecting small input array sizes, but the input size
// is unknown, improving speed in several cases, without dropping
// generalisation.
typedef mem<> normal;

template <class D>
struct conversion
{
	struct array_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
	struct array_nd_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
	struct derived_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
};

template <class D>
struct conversion<mem<D> >
{
	struct array_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
	struct array_nd_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
	struct derived_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
};

template <class D>
struct conversion<empty<D> >
{
	struct array_creation
	{
		typedef empty<> similar_type;
		typedef normal new_type;
	};
	struct array_nd_creation : public array_creation {};
	struct derived_creation : public array_creation {};
};

// no need to state this actually, with the new mechanism...
template<class D>
struct conversion<range<D> > : public conversion<normal>
{
};


template <int N, bool B1, bool B2, class D>
struct conversion<stack<N, B1, B2, D> >
{
	struct array_creation
	{
		typedef stack<N> similar_type;
		typedef stack<N + 2> new_type;
	};
	struct array_nd_creation
	{
		typedef stack<N> similar_type;
		typedef stack<N + 8> new_type;
	};
	struct derived_creation
	{
		typedef stack<N> similar_type;
		typedef stack<N + 8> new_type;
	};
};


template <int N, class NM, class D>
struct conversion<fixed<N, NM, D> >
{
	struct array_creation
	{
		typedef fixed<N, NM> similar_type;
		typedef stack<N + 2> new_type;
	};
	struct array_nd_creation
	{
		// TODO: why not fixed? probably because it is not yet supporting nd
		// level arrays? or maybe the `standard' is not like this for nd?
		// this question is about the similar_type. new_type is right.
		typedef stack<N> similar_type;
		typedef stack<N + 8> new_type;
	};
	struct derived_creation
	{
		//!!! TODO: this is put here in order elem_func types to be recognized
		/// properly. however it should either be little, or everything should
		/// be fixed, and fixed should be implemented for nd, or somehow
		/// make it work that there is no case for nd (how come in binary
		/// elem funcs??!. but also check why derived_creation is used
		/// instead of array_creation, and whether this is ok when the
		/// class is really an array!...
		typedef fixed<N, NM> similar_type;
		typedef stack<N + 8> new_type;
	};
};

template <class IT, class CONST_IT, int LENGTH, class D>
struct conversion<ref_iterator<IT, CONST_IT, LENGTH, D> >
{
	struct array_creation
	{
		typedef fixed<LENGTH> similar_type;
		typedef stack<LENGTH + 2> new_type;
	};
	struct array_nd_creation
	{
		typedef stack<LENGTH> similar_type;
		typedef stack<LENGTH + 8> new_type;
	};
	struct derived_creation
	{
		typedef stack<LENGTH> similar_type;
		typedef stack<LENGTH + 8> new_type;
	};
};

template <class IT, class CONST_IT, class D>
struct conversion<ref_iterator<IT, CONST_IT, 0, D> >
{
	struct array_creation
	{
		typedef stack<4> similar_type; // having pixel of image<0> in mind.
		typedef normal new_type;
	};
	struct array_nd_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
	struct derived_creation
	{
		typedef normal similar_type;
		typedef normal new_type;
	};
};

template <class A, class ATTR, class D>
struct conversion<wrap_array<A, ATTR, D> >
	: public conversion<typename A::data_type> { };

template<template <typename, typename, typename> class F,
	class A1, class A2, bool SWAP_ARGS, class D>
struct conversion<binary_elem_func<F, A1, A2, SWAP_ARGS, D> >
: public conversion<typename A1::data_type> {};
//: public A1::data_type::data_identifier
/*: public conversion<normal>
{
	// binary_elem_func inherits conversions from the first of the two operand classes
	// however, a conversion to normal is always acceptable, and thus, will be
	// used for now.
};*/

template<template <typename, typename> class F, class A, class D>
struct conversion<unary_elem_func<F, A, D> >
: public conversion<typename A::data_type>
{
};



/* not needed
template<template <typename, typename> class F, class A>
class conversion<unary_elem_func<F, A> : public conversion<normal>
{
};


template<class A, class B>
class conversion<mask<A, B> > : public conversion<normal>
{
};

template<class A, class B>
class indirect_data_id : public normal_data_id
{
};


template<class A, class I>
class subarray_data_id
{

};*/

} //namespace data

} //namespace ivl

#endif // IVL_CORE_DETAILS_DATA_CONVERSIONS_ARRAY_HPP
