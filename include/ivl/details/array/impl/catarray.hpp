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

#ifndef IVL_DETAILS_ARRAY_CATARRAY_HPP
#define IVL_DETAILS_ARRAY_CATARRAY_HPP

namespace ivl {

namespace array_details {

struct cat_helper
{
	template<class T, class S>
	static inline size_t ndims(const array<T, S>& a)
	{
		return 1;
	}
	template<class T, class S>
	static inline size_t ndims(const array_nd<T, S>& a)
	{
		return a.ndims();
	}
	template<class T, class S>
	static inline size_t stride(const array<T, S>& a, size_t i)
	{
		return 1;
	}
	template<class T, class S>
	static inline size_t stride(const array_nd<T, S>& a, size_t i)
	{
		return a.stride(i);
	}	
	template<class T, class S>
	static inline size_t size(const array<T, S>& a, size_t i)
	{
		return i == 0 ? a.size() : 1;
	}
	template<class T, class S>
	static inline size_t size(const array_nd<T, S>& a, size_t i)
	{
		return a.size(i);
	}
};

template<class T>
ivl::array<T, data::range<> > prv_range(T f, T l)
{
	array<T, data::range<> > r;
	r.first = f;
	r.last = l;
	r.step = 1;
	return r;
}

template <class A1, class A2, int CATDIM>
struct catarray_result
{
	//need both be non-const
	/*
	typedef typename types::t_if<types::is_const<A>,
		const typename A::derived_type, typename A::derived_type>::type a;

	typedef typename types::change_data_class_set<
		data::catarray<a, I>, typename A::derived_type>::type type;
		*/
};

} /* namespace array_details */
/*
template <class A1, class A2, int CD>
class catarray : public array_details::catarray_result<A1, A2, CD>::type
{
public:
	//operator catarray&() const { } //TODO: lets see..
	//catarray& operator*() { return const_cast<catarray&>(*this); }
	catarray& ref() { return *this; }

	typedef typename array_details::catarray_result<A1, A2, CD>
		::type base_class;

	typedef typename base_class::elem_type elem_type;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	catarray(A1& a1, A2& a2, int dim = CD) { this->setref(a.derived(), i); }

	catarray(const catarray& a) : base_class(a.derived()) { }

	using base_class::operator();

	//using base_class::operator=;
	template<class K>
	catarray& operator=(const K& k)
	{ base_class::operator=(k); return *this; }

	catarray& operator=(const catarray& o)
	{ base_class::operator=(o); return *this; }



};
*/


// kimonas, 2013 note.
// Instructions:
// This class is using the latest revision in template
// parameter classes where simple `array<...>` means actually holding an
// array by values, and to add a reference we need to have `array<...>&',
// so the usage should be done with care. 
// This is also true - as of the time of writing this - for the index
// arrays of subarray, indirect array etc., but NOT for their actual
// array data holders, which are implicitly always by reference.
// One way to go would be to make everything explicit which would be
// like this class, and would force users to go with:
// e.g. elem_class<const array<T>&, ...>
// Another way to go which is also very possible and looks maybe better
// is to have explicit parameters in the array specialization classes,
// but let the wrapper classes (like this one) to have implicit reference
// by default. In the latter case, this wrapper class should change again,
// to reflect this.
template <class A1, class A2, int CD>
class concat : public array_nd<typename types::bare_type<A1>::type::elem_type,
	data::catarray<A1, A2, CD> >
{
public:
	concat& ref() { return *this; }

	typedef array_nd<typename types::bare_type<A1>::type::elem_type,
	data::catarray<A1, A2, CD> > base_class;

	typedef typename base_class::elem_type elem_type;

	base_class& base()
		{ return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// note: 2003: used to be like this before removing implicit reference
	//concat(A1& a1, A2& a2, int dim = CD) :
	//base_class(a1.size() + a2.size(dim) * cast<int>(rng(0, a2.ndims()-1) == dim))
	//	{ this->setref(a1, a2, dim); }
	concat(A1 a1, A2 a2, int dim = CD) :
	base_class(a1.size() + array_details::cat_helper::size(a2, dim) * 
		cast<int>(array_details::prv_range<size_t>(0, 
			array_details::cat_helper::ndims(a2)-1) == dim))
		{ this->setref(a1, a2, dim); }

	template<class T1, class T2>
	concat(const tuple<T1, T2>& tp) :
	base_class(tp.v1.size() + tp.v2.size(CD) *
				cast<int>(array_details::prv_range<size_t>(0, tp.v2.ndims()-1) == CD))
		{ this->setref(tp.v1, tp.v2, CD); }


	concat(const concat& a) : base_class(a.derived()) { }

	using base_class::operator();

	//using base_class::operator=;
	template<class K>
	concat& operator=(const K& k)
	{ base_class::operator=(k); return *this; }

	concat& operator=(const concat& o)
	{ base_class::operator=(o); return *this; }



};

} /* namespace ivl */

#endif // IVL_DETAILS_ARRAY_CATARRAY_HPP
