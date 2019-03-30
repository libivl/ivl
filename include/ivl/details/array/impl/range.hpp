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

#ifndef IVL_ARRAY_DETAILS_RANGE_HPP
#define IVL_ARRAY_DETAILS_RANGE_HPP


namespace ivl {

/**
 * \brief A %range of Numbers
 *
 * eg:
 * 1:2:9 = [1 3 5 7 9]
 */
template<class T>
class range : public array<T, data::range<> >
{
private:
	typedef array<T, data::range<> > base_class;

public:
	typedef typename base_class::step_type step_type;

	using base_class::first;	//!< the starting element
	using base_class::last;		//!< the ending element
	using base_class::step;		//!< the distance between elements

	//! @name Constructors
	//@{
	//! Default Constructor
	inline range();

	/**
	 * \brief Construct a range (default step)
	 *
	 * @param s Start - The starting element of the %range.
	 * @param e End - The ending element of the %range.
	 */
	inline range(T s, T e);
	/**
	 * \brief Construct a range
	 *
	 * @param s Start - The starting element of the %range.
	 * @param st Step - The distance between two consecutive elements.
	 * @param e End - The ending element of the %range
	 */
	inline range(T s, step_type st , T e);
	//@}
	template<class J>
	inline range(const range<J>& o)
	{
		first = o.first;
		last = o.last;
		step = o.step;
	}

	/**
	 * \brief The %range length
	 *
	 * @return The number of elements this range contains
	 */
	using base_class::length;
};

typedef range<size_t> size_range;


//-----------------------------------------------------------------------------
// range CONSTRUCTORS

template <class T>
inline
range<T>::range()
{
	first  =0;
	last = 0;
	step = 0;
}

template <class T>
inline
range<T>::range(T s, typename range<T>::step_type st, T e)
{
	first = s;
	last = e;
	step = st;
	CHECK(!((st == 0 || (st > 0 && s > e) || (st < 0 && s < e))), erange);
}

template <class T>
inline
range<T>::range(T s, T e)
{
	//matlab like
	first = s;
	last = e;
	step = 1;
	if(e < s)
		last = first - 1;
}

inline slice::slice(size_range ra)
: start(ra.first), length(ra.length()), stride(ra.step)
{
}
/*
inline size_range rng(size_t s, size_t e)
{
	return size_range(s, e);
}

inline size_range rng(size_t s, size_range::step_type st, size_t e)
{
	return size_range(s, st, e);
}

*/

//-----------------------------------------------------------------------------

/**
 * \brief A %contiguous range of Numbers
 *
 * eg:
 * 1:2:9 = [1 3 5 7 9]
 */
template<class T>
class crange : public range<T>
{
private:
	typedef range<T> base_class;

public:
	typedef typename base_class::step_type step_type;

	using base_class::first;	//!< the starting element
	using base_class::last;		//!< the ending element
	using base_class::step;		//!< the distance between elements

	//! @name Constructors
	//@{
	//! Default Constructor
	crange()
	{
		first = 0;
		last = 0;
		step = 1;
	}

	/**
	 * \brief Construct a range (default step)
	 *
	 * @param s Start - The starting element of the %range.
	 * @param e End - The ending element of the %range.
	 */
	crange(T s, T e)
	{
		first = s;
		last = e;
		step = 1;		
	}

	
	//@}
	
	template<class J>
	crange(const crange<J>& o)
	{
		first = o.first;
		last = o.last;
		step = 1;
	}

	/**
	 * \brief The %range length
	 *
	 * @return The number of elements this range contains
	 */
	using base_class::length;
};

typedef crange<size_t> size_crange;


//-----------------------------------------------------------------------------

namespace core_details {

template<class J, class S>
struct range_sup_1
{
	J j; S s;
	range_sup_1(J j, S s) : j(j), s(s) {}
	template<class K>
	range<J> operator, (const K& k) { return range<J>(j, s, k); }
};

template<class J, class S>
struct range_sup : public crange<J>
{
	J j; S s;
	range_sup() {}
	range_sup(const J& j, const S& s) : crange<J>(j, s), j(j), s(s) { }	
};

}; // namespace core_details

//-----------------------------------------------------------------------------


} // namespace ivl


#endif // IVL_ARRAY_DETAILS_RANGE_HPP
