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

#ifndef IVL_QT_CORE_OVERLOAD_HPP
#define IVL_QT_CORE_OVERLOAD_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

template <int N, typename D>
struct select { };

template <typename S0, typename S1>
struct multi_delegate :
	public delegate <S0>, public delegate <S1>
{
	typedef multi_delegate D;
	using delegate <S0>::operator();
	using delegate <S1>::operator();

	template <typename S>
	delegate <S>& _() { return static_cast <delegate <S>&>(*this); }

	template <int N>
	delegate <typename select <N, D>::type>& _()
	{
		return _<typename select <N, D>::type>();
	}
};

//-----------------------------------------------------------------------------

template <template <typename, typename> class D, typename S0, typename S1>
struct select <0, D <S0, S1> > { typedef S0 type; };

template <template <typename, typename> class D, typename S0, typename S1>
struct select <1, D <S0, S1> > { typedef S1 type; };

//-----------------------------------------------------------------------------

}  // namespace delegate_details

using delegate_details::multi_delegate;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_OVERLOAD_HPP
