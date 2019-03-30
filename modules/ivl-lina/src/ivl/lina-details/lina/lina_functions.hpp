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

#ifndef LINA_DETAILS_LINA_FUNCTIONS_HPP
#define LINA_DETAILS_LINA_FUNCTIONS_HPP

namespace ivl {

template<class T>
array_2d<T> pinv(const array_2d<T>& a, double tol = -1)
{
	if(a.length() == 0) return array_2d<T>(0, 0);

	size_t m = a.rows();
	size_t n = a.columns();

	if(n > m) return pinv<T>(transpose(a), tol);

	array_2d<T> U, S, V;
	array<T> s;

	lvalue(U, S, V) = svd++(a, 0);
	if(m > 1)
		s = diag(S);
	else if(m == 1)
		s = array<T>(1, 1);
	else
		s = 0;

	if(tol == -1) tol = std::max(m, n) * eps(max(s));
	bool_array rt = s > tol;
	size_t r = sum(rt);
	if(r == 0)
		return zeros<T>(idx(n, m));
	else {
		s = array<T>(s[rng(0, r - 1)]);
		s = 1. / s;
		array_2d<T> fact1 = array_2d<T>(V(idxn(all(), rng(0, r - 1))));
		array_2d<T> fact2 = ivl::diag(s);
		array_2d<T> fact3 = U(idxn(all(), rng(0, r - 1)));

		return ivl::mtimes(ivl::mtimes(fact1, fact2), transpose(fact3));
	}
}

} // namespace ivl

#endif //LINA_DETAILS_LINA_FUNCTIONS_HPP
