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

#ifndef IVL_LINA_DETAILS_SVD_HPP
#define IVL_LINA_DETAILS_SVD_HPP

#include "ivl/details/array_2d.hpp"

#include "lina_typemap.hpp"

namespace ivl {

enum svd_type {
	columns_economy = 0,
	econ = 1,
	full = 2
};

namespace lina_details {

template<class T>
class svd :
	public rvalue_output_converter<conversions::normal, svd<T> >
{
	// Singular value decomposition
private:
	typedef typename types::to_real<T>::type prv_real_type;

	array_2d<T, data::storable_link> x;
	const size_t m;
	const size_t n;
	const size_t min_mn;
	bool econ; // true means economy or economy on rows
	bool compute_v; // false means no compute v ( econ economy )

	void diag_s(array_2d<prv_real_type>& s) const;

public:
	typedef typename types::to_real<T>::type real_type;

	template<class S>
	svd(const array_2d<T, S>& src, enum svd_type economy = full);

	// s = svd(...
	void output(array<real_type>& s) const;

	// [u,s] = svd(...
	void output(array_2d<T>& u,
		array_2d<real_type>& s) const;
	// [u,s,v] = svd(...
	void output(array_2d<T>& u, array_2d<real_type>& s,
		array_2d<T>& v) const;
};

template<class T>
template<class S>
svd<T>::svd(const array_2d<T, S>& src, svd_type economy):
	x(ivl::storable_link(src)), m(x.rows()), n(x.columns()),
			min_mn((x.rows() < x.columns()) ? x.rows() : x.columns()),
			econ((x.rows() <= x.columns() && economy == 0) ?
				false : economy != full),
			compute_v(economy != ivl::econ)
{
	if(x.columns() == 0)
		throw eshape();
}

} // namespace lina details

static struct svd_impl
{
	struct plus
	{
		template<class T, class S>
		lina_details::svd<T> operator()(const array_2d<T, S>& x,
									enum svd_type economy = full)
		{
			return lina_details::svd<T>(x, economy);
		}

		template<class T, class S>
		lina_details::svd<T> operator()(const array_2d<T, S>& x, int economy)
		{
			return lina_details::svd<T>(x, svd_type(economy));
		}
	};
	plus operator++(int) { return plus(); }
} svd;

} /* namespace ivl */

#endif // IVL_LINA_DETAILS_SVD_HPP
