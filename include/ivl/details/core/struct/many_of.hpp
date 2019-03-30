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

#ifndef IVL_CORE_DETAILS_STRUCT_MANY_OF_HPP
#define IVL_CORE_DETAILS_STRUCT_MANY_OF_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace some_details {

using keys::null;
using keys::node;

//-----------------------------------------------------------------------------

enum { how_many = 4 };

template <
	typename T,
	typename OP = typename some_operators::operator_of <T>::type,
	size_t N = stack_size, size_t K = how_many
>
class many_of : private array <some_of <T, OP, N>, data::stack <K> >
{
	typedef array <some_of <T, OP, N>, data::stack <K> > A;
	typedef typename A::const_iterator CI;
	typedef typename A::reverse_iterator RI;
	typedef typename A::const_reverse_iterator CRI;

	template <typename E, typename EN>
	void read(const node <E, EN>& n) { read(A::rbegin(), n); }

	template <typename E, typename EN>
	void read(RI i, const node <E, EN>& n) { *i = *n; read(++i, ++n); }

	void read(RI i, null) { }

public:

//-----------------------------------------------------------------------------

	typedef CI  const_iterator;
	typedef CRI const_reverse_iterator;

	typedef typename A::elem_type  elem_type;
	typedef typename A::base_class base_class;

	CI  begin()  const { return A::begin(); }
	CI  end()    const { return A::end(); }
	CRI rbegin() const { return A::rbegin(); }
	CRI rend()   const { return A::rend(); }

//-----------------------------------------------------------------------------

	typedef many_of create_new;
	typedef many_of create_similar;

	many_of() : A() { }

	template <typename E, typename EN>
	many_of(const node <E, EN>& n) : A(node <E, EN>::length) { read(n); }

	template <typename E>
	many_of(const E& e) : A(1) { read(node <E>(e)); }

	template <typename E>
	many_of(const E e[]) : A(1) { read(node <const E*>(e)); }

};

//-----------------------------------------------------------------------------

template <typename S, typename T, typename OP, size_t N>
typename enable_if <is_conv <T, S>, S&>::type
operator<<(S& s, const many_of <T, OP, N>& st)
{
	typedef typename many_of <T, OP, N>::const_iterator I;
	for (I i = st.begin(), e = st.end(); i != e; i++)
		s << *i;
	return s;
}

//-----------------------------------------------------------------------------

}  // namespace some_details

using some_details::many_of;
using some_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_STRUCT_MANY_OF_HPP
