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

template <class T>
inline
int is_nan(T x)
{
#ifdef _MSC_VER
	return ::_isnan(x);
#else
	// iavr: isnan macro
	//return std::isnan(x);
	return ((x) != (x));
#endif
}

template<class T>
inline
bool ivl_finite(const T& n)
{
#if defined(__VISUALC__)
    return _finite(n);
#elseif defined(__GNUC__)
    return finite(n);
#else
    return ((n) == (n));
#endif
}

template<class T>
inline
bool ivl_isnan(const T& n)
{
#if defined(__VISUALC__)
    return _isnan(n);
#elseif defined(__GNUC__)
    return is_nan(n);
#else
    return ((n) != (n));
#endif
}
