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

#ifndef IVL_CORE_DETAILS_LOOPS_ROW_FUNC_2D_HPP
#define IVL_CORE_DETAILS_LOOPS_ROW_FUNC_2D_HPP

namespace ivl {

namespace loops {

template
<
class T, class D, class P,
class L1, class M1, class N1,
class L2, class M2, class N2>
void row_func_2d_output(const array_2d<T, D, P>& in, size_t in_dim,
	array_2d<L1, M1, N1>& o1, array_2d<L2, M2, N2>& o2)
{
	typename array_2d<L1, M1, N1>::iterator_nd it1 = o1._begin(1 - in_dim);
	typename array_2d<L2, M2, N2>::iterator_nd it2 = o2._begin(1 - in_dim);

	typedef typename array_2d<T, D, P>::const_iterator_nd in_iter_nd;
	in_iter_nd cit = in->_begin(1 - in_dim);
	in_iter_nd cit_end = this->_next(1 - in_dim, cit);

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
void row_func_2d_output(const array_2d<T, D, P>& in, size_t in_dim,
	array_2d<L1, M1, N1>& o1,
	array_2d<L2, M2, N2>& o2,
	array_2d<L3, M3, N3>& o3)
{
	typename array_2d<L1, M1, N1>::iterator_nd it1 = o1._begin(1 - in_dim);
	typename array_2d<L2, M2, N2>::iterator_nd it2 = o2._begin(1 - in_dim);
	typename array_2d<L3, M3, N3>::iterator_nd it3 = o3._begin(1 - in_dim);

	typedef typename array_2d<T, D, P>::const_iterator_nd in_iter_nd;
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
void row_func_2d_output(const array_2d<T, D, P>& in, size_t, in_dim,
	array_2d<L1, M1, N1>& o1,
	array_2d<L2, M2, N2>& o2,
	array_2d<L3, M3, N3>& o3,
	array_2d<L4, M4, N4>& o4)
{
	typename array_2d<L1, M1, N1>::iterator_nd it1 = o1._begin(1 - in_dim);
	typename array_2d<L2, M2, N2>::iterator_nd it2 = o2._begin(1 - in_dim);
	typename array_2d<L3, M3, N3>::iterator_nd it3 = o3._begin(1 - in_dim);
	typename array_2d<L4, M4, N4>::iterator_nd it4 = o4._begin(1 - in_dim);

	typedef typename array_2d<T, D, P>::const_iterator_nd in_iter_nd;
	in_iter_nd cit = in->_begin(1 - in_dim);
	in_iter_nd cit_end = this->_next(1 - in_dim, cit);

	for(; cit != cit_end; ++cit, ++it1, ++it2, ++it3, ++it4) {
		F::calculate(const_iter_array(in->_iter(in_dim, cit)),
			*it1, *it2, *it3, *it4);
	}
}


}; /*namespace loops*/

}; /*namespace ivl*/

#endif // IVL_CORE_DETAILS_LOOPS_ROW_FUNC_2D_HPP
