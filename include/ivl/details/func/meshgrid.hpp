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

// TODO: remove
/*
function [xx, yy] = meshgrid (x, y)

  if (nargin == 1)
    y = x;
  endif
  if (nargin > 0 && nargin < 3)
    if (is_vector (x) && is_vector (y))
      xx = ones(length(y), 1) * x(:).';
      yy = y(:) * ones(1, length(x));
    else
      error ("meshgrid: arguments must be vectors");
    endif
  else
    usage ("[xx, yy] = meshgrid (x, y)");
  endif

endfunction
*/

//-----------------------------------------------------------------------------

#ifndef IVL_FUNC_MESHGRID
#define IVL_FUNC_MESHGRID

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

static __attribute__((unused))
struct meshgrid_impl : public ivl_func<meshgrid_impl>
//, _<
//	ret<array_2d<_T>, array_2d<_T> >(const array<_T, _S1>&, const array<_T, _S2>&)
//> >
{
	template<class T, class S1, class S2, class I1, class I2>
	void operate(array_2d<T, S1>& xx, array_2d<T, S2>& yy, sep,
				const array<T, I1>& x, const array<T, I2>& y)
	{
		xx = mtimes(ones<T>(y.length(), 1), array_2d<T>(1, x.length(), x));
		yy = mtimes(array_2d<T>(y.length(), 1, y), ones<T>(1, x.length()));
	}
	// TODO: make a global decision...
	template<class T, class T0, class T1, class T2,
		class S1, class S2, class I1, class I2>
	void operate(array_nd<T, S1>& xx, array_nd<T0, S2>& yy, sep,
				const array<T1, I1>& x, const array<T2, I2>& y)
	{
		xx = mtimes(ones<T>(y.length(), 1), array_2d<T>(1, x.length(), x));
		yy = mtimes(array_2d<T>(y.length(), 1, y), ones<T>(1, x.length()));
	}

	template<class T, class I1, class I2>
	ret<array_2d<T>, array_2d<T> > operator()(
				const array<T, I1>& x, const array<T, I2>& y)
	{
		ret<array_2d<T> > xx, yy;
		xx = mtimes(ones<T>(y.length(), 1), array_2d<T>(1, x.length(), x));
		yy = mtimes(array_2d<T>(y.length(), 1, y), ones<T>(1, x.length()));
		return (_, xx, yy);
	}
} meshgrid;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUNC_MESHGRID
