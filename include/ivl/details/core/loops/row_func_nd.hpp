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

#ifndef IVL_CORE_DETAILS_LOOPS_ROW_FUNC_ND_HPP
#define IVL_CORE_DETAILS_LOOPS_ROW_FUNC_ND_HPP

namespace ivl {

namespace loops {

// The loops for the nd row func arrays.

/* Performance Warning:
* There is a possible improvement. Each array of the output arrays
* is incemented using the sequential iterator. However, the ideal
* would be to use the best-possible iterator, having either
* sequential or nd-sequential iterations. This would make
* the loop too complicated cause it would have many arrays with
* many different iterator_nd, and so it is omitted.
*/


template
<
class T, class D, class P,
class S, class K,
class L1, class M1, class N1,
class L2, class M2, class N2>
void row_func_nd_output(const array_nd<T, D, P>& in, size_t, in_dim,
	const array<size_t, S, K> in_dims, const array<size_t, S, K>& sizes,
	array_nd<L1, M1, N1>& o1, array_nd<L2, M2, N2>& o2)
{

	/*
	array<size_t, data::little> dims(in.ndim() - 1);
	for(size_t i = 0; i < dims.length(); i++)
		dims[i] = i + (i >= in_dim ? 1 : 0);

	array<size_t, data::little> sizes(dims.length());
	for(size_t i = 0; i < dims.length(); i++)
		sizes[i] = in.size(dims[i]);

	size_t row = in_dim == 0 ? 1 : len;
	size_t col = in_dim == 1 ? 1 : len;
	*/
	iter[in_dims.size() - 1] = in->_begin(in_dims[in_dims.size() - 1]);
	iter_e[in_dims.size() - 1] = in->_end(in_dims[in_dims.size() - 1]);
	for(size_t d = in_dims.size() - 2; d > 0; d++) {
		iter[d] = in->_iter(in_dims[d], iter[d + 1]);
		iter_e[d] = in->_next(in_dims[d], iter[d]);
	}
	in_dim0 = in_dims[0];
	iter0 = in->_begin(in_dim0);
	iter_e0 = in->_end(in_dim0);
	size0 = sizes[0];

	do {
		for(; iter0 != iter_e0; iter0++) {

			F::calculate(const_iter_array(in->_iter(in_dim, iter0)),
				*it1, *it2);

			++it1;
			++it2;
		}



	} while(1);

	typename array_nd<L1, M1, N1>::iterator_nd it1 = o1._begin(1 - in_dim);
	typename array_nd<L2, M2, N2>::iterator_nd it2 = o2._begin(1 - in_dim);

	typedef typename array_nd<T, D, P>::const_iterator_nd in_iter_nd;
	in_iter_nd cit = in->_begin(1 - in_dim);
	in_iter_nd cit_end = in->_end(1 - in_dim);

	for(; cit != cit_end; ++cit, ++it1, ++it2) {
		F::calculate(
			const_iter_array(in->_iter(in_dim, cit)),
			*it1, *it2);
	}
}

template
<
class T, class D, class P,
class L1, class M1, class N1,
class L2, class M2, class N2,
class L3, class M3, class N3>
void row_func_nd_output(const array_nd<T, D, P>& in, size_t, in_dim,
	array_nd<L1, M1, N1>& o1,
	array_nd<L2, M2, N2>& o2,
	array_nd<L3, M3, N3>& o3)
{
	size_t len = this->length();
	size_t row = in_dim == 0 ? 1 : len;
	size_t col = in_dim == 1 ? 1 : len;
	o1.resize(row, col);
	o2.resize(row, col);
	o3.resize(row, col);
	typename array_nd<L1, M1, N1>::iterator_nd it1 = o1._begin(1 - in_dim);
	typename array_nd<L2, M2, N2>::iterator_nd it2 = o2._begin(1 - in_dim);
	typename array_nd<L3, M3, N3>::iterator_nd it3 = o3._begin(1 - in_dim);

	typedef typename array_nd<T, D, P>::const_iterator_nd in_iter_nd;
	in_iter_nd cit = in->_begin(1 - in_dim);
	in_iter_nd cit_end = this->_next(1 - in_dim, cit);

	for(; cit != cit_end; ++cit, ++it1, ++it2, ++it3) {
		F::calculate(const_iter_array(in->_iter(in_dim, cit)),
			*it1, *it2, *it3);
	}
}


template
<
class T, class D, class P,
class L1, class M1, class N1,
class L2, class M2, class N2,
class L3, class M3, class N3,
class L4, class M4, class N4>
void row_func_nd_output(const array_nd<T, D, P>& in, size_t, in_dim,
array_nd<L1, M1, N1>& o1,
array_nd<L2, M2, N2>& o2,
array_nd<L3, M3, N3>& o3,
array_nd<L4, M4, N4>& o4)
{
	size_t len = this->length();
	size_t row = in_dim == 0 ? 1 : len;
	size_t col = in_dim == 1 ? 1 : len;
	o1.resize(row, col);
	o2.resize(row, col);
	o3.resize(row, col);
	o4.resize(row, col);
	typename array_nd<L1, M1, N1>::iterator_nd it1 = o1._begin(1 - in_dim);
	typename array_nd<L2, M2, N2>::iterator_nd it2 = o2._begin(1 - in_dim);
	typename array_nd<L3, M3, N3>::iterator_nd it3 = o3._begin(1 - in_dim);
	typename array_nd<L4, M4, N4>::iterator_nd it4 = o4._begin(1 - in_dim);

	typedef typename array_nd<T, D, P>::const_iterator_nd in_iter_nd;
	in_iter_nd cit = in->_begin(1 - in_dim);
	in_iter_nd cit_end = this->_next(1 - in_dim, cit);

	for(; cit != cit_end; ++cit, ++it1, ++it2, ++it3, ++it4) {
		F::calculate(const_iter_array(in->_iter(in_dim, cit)),
			*it1, *it2, *it3, *it4);
	}
}


}; /*namespace loops*/

}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_LOOPS_ROW_FUNC_ND_HPP
