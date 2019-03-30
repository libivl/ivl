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

#ifndef IVL_ARRAY_ND_DETAILS_COMMON_RESIZE_DETAILS_HPP
#define IVL_ARRAY_ND_DETAILS_COMMON_RESIZE_DETAILS_HPP

namespace ivl {
namespace array_nd_details {

template <class T, class S, class D, class L>
void resize_rearrange(array_nd<T, S>& a, const array<size_t, D>& new_sz,
						const array<size_t, L>& new_stride,
						bool pad = false, const T& padval = T())
{
	bool skip_flag = true;
	size_t dm = std::min(size_t(a.ndims()), size_t(new_sz.length()));
	array<index_array, tiny> id(a.ndims());

	for(size_t i = dm; i < a.ndims(); i++)
		id[i] = idx(0);

	array<size_t, tiny> junc(dm);
	for(size_t i = 0; i < dm; i++)
		junc[i] = std::min(new_sz[i], a.size_nd(i));

	for(size_t i = 0; i < dm; i++) {
		// should some dims be reverse and some not
		if(a.stride(i) >= new_stride[i])
			id[i] = size_range(0, junc[i] - 1);
		else
			id[i] = size_range(junc[i] - 1, 0);
		if(a.stride(i) != new_stride[i] &&
			!(new_sz[i] == 1) && !(a.size_nd(i) == 1))
			skip_flag = false;
	}

	// if data is in the same position, it needs no repositioning.
	if(!skip_flag) {
		// shape of the old array, but with same number of dims as the new array
		array<size_t, tiny> new_szm(a.ndims(), 1);
		size_range new_szr(0, std::min(new_sz.length() - 1, a.ndims() - 1));
		new_szm[new_szr] = new_sz[new_szr];

		// performs shape manipulation on the array without resizing it:
		array_nd<T, data::ref_iterator<array_nd<T, S> > >
			new_arr(new_szm/* */, a);
		//new_arr.init(a);

		//TODO: ivl::serial(.)
		//and worry about dimension sorting
		force(new_arr(id)) = a(id);
	}

	if(pad) {
		id.resize(new_sz.length(), idx(0));
		array_nd<T, data::ref_iterator<array_nd<T, S> > >
			new_arr(new_sz, a);

		// padding common dimensions
		for(size_t i = 0; i < dm; i++) {
			id[i] = size_range(junc[i], new_sz[i] - 1);
			new_arr(id) = padval;
			id[i] = index_all();
		}

		// padding extra dimensions
		for(size_t i = dm; i < new_sz.length(); i++) {
			id[i] = size_range(1, new_sz[i] - 1);
			new_arr(id) = padval;
			id[i] = index_all();
		}
	}
}

// since an array can be of many types, we have to see if it is resizeable
template <class IS_RESIZEABLE>
struct resize_rearrange_detail
{
	template <class T, class S, class D, class L>
	static inline
	void operate(array_nd<T, S>& a, const array<size_t, D>& new_sz,
				const array<size_t, L>& new_stride, const T& p = T()) { }
};

template <>
struct resize_rearrange_detail<types::t_true>
{
	template <class T, class S, class D, class L>
	static inline
	void operate(array_nd<T, S>& a, const array<size_t, D>& new_sz,
				const array<size_t, L>& new_stride)
	{
		resize_rearrange(a, new_sz, new_stride);
	}
	template <class T, class S, class D, class L>
	static inline
	void operate(array_nd<T, S>& a, const array<size_t, D>& new_sz,
				const array<size_t, L>& new_stride, const T& padval)
	{
		resize_rearrange(a, new_sz, new_stride, true, padval);
	}
};

template <class T, class S, class D, class L>
void enlarge_rearrange(array_nd<T, S>& a, const array<size_t, D>& new_sz,
						const array<size_t, L>& new_stride)
{
	if(a.ndims() > 0) {
		size_t ldim = a.ndims() - 1;
		size_t old_len = a.size_nd(ldim) * a.stride(ldim);
		if(a.length() > old_len && old_len > 0)
			resize_rearrange_detail<typename array_nd<T, S>::is_resizeable>
				::operate(a, new_sz, new_stride);
	}
}

template <class T, class S, class D, class L>
void shrink_rearrange(array_nd<T, S>& a, const array<size_t, D>& new_sz,
						const array<size_t, L>& new_stride)
{
	size_t new_len = (*new_sz.rbegin()) * (*new_stride.rbegin());
	if(new_len <= a.length() && !a.size().isequal(new_sz))
		resize_rearrange_detail<typename array_nd<T, S>::is_resizeable>
			::operate(a, new_sz, new_stride);
}

template <class T, class S, class D, class L>
void enlarge_rearrange(array_nd<T, S>& a, const array<size_t, D>& new_sz,
						const array<size_t, L>& new_stride, const T& pad)
{
	if(a.ndims() > 0) {
		size_t ldim = a.ndims() - 1;
		size_t old_len = a.size_nd(ldim) * a.stride(ldim);
		if(a.length() > old_len && old_len > 0)
			resize_rearrange_detail<typename array_nd<T, S>::is_resizeable>
				::operate(a, new_sz, new_stride, pad);
	}
}

template <class T, class S, class D, class L>
void shrink_rearrange(array_nd<T, S>& a, const array<size_t, D>& new_sz,
						const array<size_t, L>& new_stride, const T& pad)
{
	size_t new_len = (*new_sz.rbegin()) * (*new_stride.rbegin());
	if(new_len <= a.length() && !a.size().isequal(new_sz))
		resize_rearrange_detail<typename array_nd<T, S>::is_resizeable>
			::operate(a, new_sz, new_stride, pad);
}
} /* namespace array_nd_details */
} /* namespace ivl */

#endif // IVL_ARRAY_ND_DETAILS_COMMON_RESIZE_DETAILS_HPP
