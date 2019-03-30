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

#ifndef IVL_LINA_DETAILS_INV_HPP
#define IVL_LINA_DETAILS_INV_HPP

namespace ivl {
namespace lina_details {

template<class T>
class inv :
	public rvalue_output_converter<conversions::normal, inv<T> >
{
	// Matrix inverse.
private:
	array_2d<T, data::storable_link> x;

public:
	template <class S>
	inv(const array_2d<T, S>& src);

	// dst = inv(x)
	void output(array_2d<T> &dst) const;
};

} /* namespace line_details*/

template<class T, class S>
lina_details::inv<T> inv(const array_2d<T, S>& x)
{
	return lina_details::inv<T>(x);
}

/* implementation */

namespace lina_details {

template<class T>
template<class S>
inv<T>::inv(const array_2d<T, S>& src): x(ivl::storable_link(src))
{
	if(x.columns() == 0)
		throw eshape();

	if(!x.is_square())
		throw eshape();
}

} /* namespace line_details */

} /* namespace ivl */

#endif // IVL_LINA_DETAILS_EIG_HPP
