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

#ifndef IVL_FUNC_GRID
#define IVL_FUNC_GRID

//-----------------------------------------------------------------------------

namespace ivl {

static __attribute__((unused))
struct grid_impl : public ivl_func<grid_impl>
{
	template<class T, class S1, class S2, class I1, class I2>
	void operate(array_2d<T, S1>& yy, array_2d<T, S2>& xx, sep,
				const array<T, I1>& y, const array<T, I2>& x)
	{
		xx = mtimes(ones<T>(y.length(), 1), array_2d<T>(1, x.length(), x));
		yy = mtimes(array_2d<T>(y.length(), 1, y), ones<T>(1, x.length()));
	}
	// TODO: make a global decision...
	template<class T, class T0, class T1, class T2,
		class S1, class S2, class I1, class I2>
	void operate(array_nd<T, S1>& yy, array_nd<T0, S2>& xx, sep,
				const array<T1, I1>& y, const array<T2, I2>& x)
	{
		xx = mtimes(ones<T>(y.length(), 1), array_2d<T>(1, x.length(), x));
		yy = mtimes(array_2d<T>(y.length(), 1, y), ones<T>(1, x.length()));
	}

	template<class T, class I1, class I2>
	ret<array_2d<T>, array_2d<T> > operator()(
				const array<T, I1>& y, const array<T, I2>& x)
	{
		ret<array_2d<T> > xx, yy;
		xx = mtimes(ones<T>(y.length(), 1), array_2d<T>(1, x.length(), x));
		yy = mtimes(array_2d<T>(y.length(), 1, y), ones<T>(1, x.length()));
		return (_, yy, xx);
	}

} grid;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_GRID
