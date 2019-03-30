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

#ifndef IVL_ARRAY_DETAILS_INDEX_ARRAY_HPP
#define IVL_ARRAY_DETAILS_INDEX_ARRAY_HPP

namespace ivl {

struct index_array_all_type
{
};

//! Defines an index array that will be used to
//! select elements in an array.
class index_array
: public array<size_t, data::stack<4, true> >
, public size_range
{
protected:

public:
	typedef array<size_t, data::stack<4, true> > size_array;

	using size_array::operator[];
	using size_array::operator=;

	enum index_array_type {
		ARRAY,
		RANGE,
		ALL
	};

	index_array_type indtype;

	// Constructors
	index_array() : size_array(1,(size_t)(0)), indtype(ALL) { }

	index_array(const size_array& sa) : size_array(sa), indtype(ARRAY) { }

	template <class S>
	index_array(const array<size_t, S>& sa) : size_array(sa), indtype(ARRAY) { }

	index_array(size_t s) : size_array(1,s), indtype(ARRAY) { }

	index_array(const size_range& sr) : size_range(sr), indtype(RANGE) { }

	index_array(const range<int>& sr) : size_range(sr), indtype(RANGE) { }

	index_array(const index_array_all_type& sa) : indtype(ALL) { }

	index_array(const index_array& ia)
		: size_array(ia), size_range(ia), indtype(ia.indtype) { }


	// Operator=
	index_array& operator= (const size_array& sa)
	{
		size_array::operator=(sa);
		indtype = ARRAY;
		return *this;
	}

	template <class S>
	index_array& operator= (const array<size_t, S>& sa)
	{
		size_array::operator=(sa);
		indtype = ARRAY;
		return *this;
	}

	template <class S>
	index_array& operator= (size_t s)
	{
		size_array::resize(1, s);
		indtype = ARRAY;
		return *this;
	}

	index_array& operator =(const size_range &a)
	{
		size_range::operator=(a);
		indtype = RANGE;
		return *this;
	}
	index_array& operator =(const range<int> &a)
	{
		size_range::operator=(a);
		indtype = RANGE;
		return *this;
	}

	index_array& operator =(const index_array_all_type& sa)
	{
		indtype = ALL;
		return *this;
	}

	index_array& operator =(const index_array &a)
	{
		const size_array &tmp = a;
		size_array::operator=(tmp);
		size_range::operator=(a);
		indtype = a.indtype;
		return *this;
	}



	inline bool is_all() const;
	inline bool is_array() const;
	inline bool is_range() const;
	inline size_t length() const;
	inline size_t length(const size_array& sizes, size_t dim = 0) const;
	inline size_t starts() const;
	inline size_t ends() const;
	inline size_t steps() const;
	inline size_array cast() const; //!< Casts RANGE to ARRAY.

	inline size_array& as_array()
	{
		return static_cast<size_array&>(*this);
	}
	inline const size_array& as_array() const
	{
		return static_cast<const size_array&>(*this);
	}
	inline size_range& as_range()
	{
		return static_cast<size_range&>(*this);
	}
	inline const size_range& as_range() const
	{
		return static_cast<const size_range&>(*this);
	}
};

inline
size_t index_array::length() const
{
	switch (indtype) {
	case ARRAY:
		return size_array::length();
	case RANGE:
		return size_range::length();
	default:
	// In case we have ALL, the length is not known.
	// We need the array this index is applied to to compute it.
		return 0;
	}
}

inline
size_t index_array::length(const size_array& sizes, size_t dim) const
{
	switch (indtype) {
	case ARRAY:
		return size_array::length();
	case RANGE:
		return size_range::length();
	case ALL:
		return sizes[dim];
	default:
		return 0;
	}
}

inline
size_t index_array::starts() const
{
	switch (indtype) {
	case ARRAY:
		return size_array::operator[](0);
	case RANGE:
		return size_range::first;
	case ALL:
	default:
		return 0;
	}
}

inline
size_t index_array::ends() const
{
	switch (indtype) {
	case ARRAY:
		return size_array::operator[](length() - 1);
	case RANGE:
		return size_range::last;
	case ALL:
	default:
		return 0;
	}
}

inline
size_t index_array::steps() const
{
	switch (indtype) {
	case RANGE:
		return size_range::step;
	case ALL:
		return 1;
	case ARRAY:
		return 1; // steps() is meaningless in case of array.
				  // however the minimum step is 1 and has to be returned
				  // because it is used in subarray.
	default:
		return 0;
	}
}

inline
index_array::size_array index_array::cast() const
{
	size_array a;
	const size_array& myself = *this;

	switch (indtype) {
	case RANGE:
		a = size_array(size_range::length());
		for (size_t i = 0; i < a.length(); i++)
			a[i] = first + i * step;
		return a;
	case ALL:
		return size_array(0);
	case ARRAY:
		return myself;
	default:
		return size_array(0);
	}
}

/*
inline index_array::type index_array::index_type() const
{
	return indtype;
}
*/

inline
bool index_array::is_all() const
{
	return (indtype == ALL);
}

inline
bool index_array::is_array() const
{
	return (indtype == ARRAY);
}

inline
bool index_array::is_range() const
{
	return (indtype == RANGE);
}

//! ostream operator<< overload for index_array
inline
std::ostream& stream_out(std::ostream& os, const index_array& a)
{
	if (a.is_all())
		os << ":";
	else if(a.is_range())
		os << a.as_range();
	else if(a.is_array())
		os << a.as_array();

	return os;
}

// index_array NON_MEMBER FUNCTIONS

// iavr: all() moved to corefunc, here renamed as index_all()
inline
index_array_all_type index_all()
{
	return index_array_all_type();
}

} // namespace ivl

#endif // IVL_ARRAY_DETAILS_INDEX_ARRAY_HPP
