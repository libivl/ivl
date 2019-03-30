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

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_DETAILS_FUNC_RNG_HPP
#define IVL_CORE_DETAILS_FUNC_RNG_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace core_details {

template <class J, class J1, class J2>
struct rng_
{
	typedef types::number<0> cost;
	static inline size_crange elem_op(size_t x, size_t y)
	{
		return ivl::size_crange(x, y);
	}
};

} // namespace core_details
static __attribute__ ((unused)) struct rng_impl : public ivl_func<rng_impl>,
	public binary_elem_base<size_range, size_t, size_t, core_details::rng_>
{
	typedef binary_elem_base<size_range, size_t, size_t, core_details::rng_> rng_base;

	using rng_base::operator();
	using rng_base::operator[];

	/*inline size_range operator()(size_t s, size_t e)
	{
		return size_range(s, e);
	}*/

	inline size_range operator()(size_t s, size_range::step_type st, size_t e)
	{
		return size_range(s, st, e);
	}

} rng;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_FUNC_RNG_HPP
