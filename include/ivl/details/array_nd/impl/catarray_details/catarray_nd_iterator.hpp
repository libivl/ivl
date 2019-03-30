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

#ifndef IVL_CORE_DETAILS_ITERATOR_CATARRAY_ND_ITERATOR_HPP
#define IVL_CORE_DETAILS_ITERATOR_CATARRAY_ND_ITERATOR_HPP
#if 0

namespace ivl {

namespace data {
/*
template <class T, class IT, bool REF_IS_ND, bool CONST, int SPECIALIZED = 0>
class catarray_nd_iterator
{
};
*/

template <class T, class IT, class CONST_IT,
	bool REF_IS_ND, bool CONST, int SPECIALIZED = 0,
	bool PAST_END_CAPABLE = true>
class catarray_nd_iterator
: public data::data_details::
	iter_operator_expander<
		catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, CONST, SPECIALIZED,
		PAST_END_CAPABLE>,
			T, CONST,
			typename types::remove_const<typename IT::reference>::type>
{
private:
	template <class J, class Y, class V, bool R, bool C, int S, bool P>
	friend class catarray_nd_iterator;

	friend class array_nd_details::
		catarray_tools<typename types::t_expr<REF_IS_ND>::type>;

	typedef array_nd_details::catarray_common_tools ctool;

	typedef array_nd_details::
		catarray_tools<typename types::t_expr<REF_IS_ND>::type> tool;

	template <class X, class Y, bool C, class Z>
	friend class data::data_details::iter_operator_expander;

	typedef typename types::apply_const<T, types::t_expr<CONST> >
		::type best_value_type;

	typedef typename types::apply_const<typename IT::reference,
		types::t_expr<CONST> >::type best_ref_type;

	// this class is used to disable specific specialization members
	// this class is used to disable non-const operator [] for const_operators
	class not_a_type { operator size_t() { return 0; } };

	typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
		types::code_word<> >::type invalid_if_const;

	typedef array_nd_details::catarray_common_tools::sub_type sub_type;

protected:
/*	typedef typename types::t_if<types::t_expr<
		(!REF_IS_ND && PAST_END_CAPABLE &&
		!data::iterator_extended_traits<IT>::is_past_end_capable::value)>,
		data::past_end_capable_iterator<IT>, IT>::type ref_iter_type;
*/
	typedef iterator_nd_details::it_wrapper<typename IT::value_type, IT,
		PAST_END_CAPABLE && !REF_IS_ND, types::is_ptr<IT>::value> ref_iter_type;
/*
typename types::t_if<types::t_expr<REF_IS_ND && PAST_END_CAPABLE &&
		!data::iterator_extended_traits<IT>::is_past_end_capable::value)>,
		data::past_end_capable_iterator<IT>, IT>::type ref_iter_type;
*/
	ref_iter_type ptr;
	size_t step;
	ptrdiff_t posit;
	const size_t* idx;
	ptrdiff_t* diff;
	ptrdiff_t cur_pos; // -1 means either no array or singleton array
	sub_type type_deprecated;
	ivl::array<size_t, tiny> pos;

	inline typename types::apply_const<best_ref_type>::type base(
		types::code_word<> ok = types::code_word<>()) const
		{ return (*ptr); }

	inline best_ref_type base(
		invalid_if_const disable = invalid_if_const())
		{ return (*ptr); }


public:
	typedef catarray_nd_iterator this_type;

	// iterator_traits
	typedef std::random_access_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef best_value_type* pointer;
	typedef best_ref_type reference;

	typedef types::t_false has_base_iterator;

	typedef IT reference_iterator;

	struct iter_nd_dir_type
	{
		IT ptr;
	};

//todo: basically i need to put dir_type instead of iterator in the definition
// of border_walker(in tool), though the problem is i have not created such a
// type for array. that would be useful for many reasons. used also in the
// iterator, in array, instead of iters, for moving around. and hold only
// the 4 iterators begin end rbegin rend in the iters array. (though that'd
// make 2 pointers/iter overhead).

	/*typedef typename tool::template
		iter_nd_border_walker<catarray_nd_iterator<T, CONST_IT, CONST_IT,
			REF_IS_ND, true, 0> > iter_nd_border_walker;*/
	typedef typename tool::template
		iter_nd_border_walker<CONST_IT> iter_nd_border_walker;

	// constructors
	catarray_nd_iterator() { }
	template<class S>
	catarray_nd_iterator(
		const IT& ptr,
		size_t step,
		ptrdiff_t posit,
		const size_t* idx,
		ptrdiff_t* diff,
		ptrdiff_t cur_pos,
		sub_type type,
		const array<size_t, S>& pos) :
			ptr(types::code_word<>(), ptr), step(step), posit(posit), idx(idx), diff(diff),
			cur_pos(cur_pos), type_deprecated(type), pos(pos)
		{ }

	catarray_nd_iterator(
		const IT& ptr,
		size_t step,
		ptrdiff_t posit,
		const size_t* idx,
		ptrdiff_t* diff,
		ptrdiff_t cur_pos,
		sub_type type,
		size_t pos_size, size_t pos_dim, size_t pos_val
		) :
			ptr(types::code_word<>(), ptr), step(step), posit(posit), idx(idx), diff(diff),
			cur_pos(cur_pos), type_deprecated(type)
		{ pos.resize(pos_size, 0); pos[pos_dim] = pos_val; }


	catarray_nd_iterator(
		const IT& ptr,
		size_t step,
		ptrdiff_t posit,
		const size_t* idx,
		ptrdiff_t* diff,
		ptrdiff_t cur_pos,
		sub_type type,
		size_t pos_size
		) :
			ptr(types::code_word<>(), ptr), step(step), posit(posit), idx(idx), diff(diff),
			cur_pos(cur_pos), type_deprecated(type), pos(pos_size, size_t(0))
		{ }

	template<class S>
	catarray_nd_iterator(
		const IT& ptr,
		size_t step,
		ptrdiff_t posit,
		const size_t* idx,
		ptrdiff_t* diff,
		ptrdiff_t cur_pos,
		sub_type type,
		array<size_t, S> pos, size_t pos_dim, size_t pos_val
		) :
			ptr(types::code_word<>(), ptr), step(step), posit(posit), idx(idx), diff(diff),
			cur_pos(cur_pos), type_deprecated(type), pos(pos)
		{ pos[pos_dim] = pos_val; }

	catarray_nd_iterator(const this_type& it) :
		ptr(it.ptr), step(it.step), posit(it.posit), idx(it.idx), diff(it.diff),
		cur_pos(it.cur_pos), type_deprecated(it.type_deprecated), pos(it.pos) { }



	template <bool C, int S>
	catarray_nd_iterator(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
		PAST_END_CAPABLE>& it)
		:
		ptr(types::code_word<>(), it.ptr), step(it.step), posit(it.posit), idx(it.idx), diff(it.diff),
		cur_pos(it.cur_pos), type_deprecated(it.type_deprecated), pos(it.pos) { }



	//copy same type iterator
	this_type& operator=(const this_type& it)
	{
		ptr = it.ptr;
		step = it.step;
		posit = it.posit;
		idx = it.idx;
		diff = it.diff;
		cur_pos = it.cur_pos;
		type_deprecated = it.type_deprecated;
		pos = it.pos;
		return *this;
	}

	//copy relevant type iterator
	template <bool C, int S>
	this_type& operator=(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
		PAST_END_CAPABLE>& it)
	{
		using namespace types;

		ptr = it.ptr;
		step = it.step;

		// skip these assignments
		r_if<t_expr<S != 1> >(posit, types::skip()) = it.posit;
		r_if<t_expr<S != 1> >(idx, types::skip()) = it.idx;
		r_if<t_expr<S != 1> >(diff, types::skip()) = it.diff;
		//r_if<t_expr<S != 1> >(cur_pos, types::skip()) = it.cur_pos;
		cur_pos = r_if<t_expr<S != 1> >(it.cur_pos, -1);

		type_deprecated = it.type_deprecated;
		pos = it.pos;
		return *this;
	}


	// members

	// increment-decrement
	inline this_type& operator++()
	{
		//TODO: create the specialized versions:
		// 1: for step
		// 2: for array
		// 0: for the following with if:
		if(cur_pos >= 0) {
			ptr += *(diff++);
			posit++;

		} else {
			ptr += step;
		}
		return *this;
	}

	inline this_type& operator--()
	{
		if(cur_pos >= 0) {
			ptr -= *(--diff);
			posit--;

		} else {
			ptr -= step;
		}
		return *this;
	}

	this_type operator++(int) { this_type tmp(*this); ++(*this); return tmp; }
	this_type operator--(int) { this_type tmp(*this); --(*this); return tmp; }

	//! random access
	this_type& operator +=(ptrdiff_t j)
	{
		//TODO: create the specialized versions:
		// 1: for step
		// 2: for array
		// 0: for the following with if:
		if(cur_pos >= 0) {

			size_t last = idx[posit];
			posit += j;
			diff += j;
			ptr += step * (idx[posit] - last);

		} else {
			ptr += step * j;
		}
		return *this;
	}

	this_type& operator -=(ptrdiff_t j)
	{
		//TODO: create the specialized versions:
		// 1: for step
		// 2: for array
		// 0: for the following with if:
		if(cur_pos >= 0) {

			size_t last = idx[posit];
			posit -= j;
			diff -= j;
			ptr += step * (idx[posit] - last);

		} else {
			ptr -= step * j;
		}
		return *this;
	}

	//! border
	this_type& operator +=(const iter_nd_border_walker& b)
	{
		//TODO: create the specialized versions:
		// 1: for step, which excludes posit
		// 2: for array, and 0: same as below
		// TODO: ensure non-array has invalid curpos!!
		if(b.cur_pos >= 0) { // b is for an array dimension
			if(cur_pos == b.cur_pos) {
				posit += b.len;
				diff += b.len;
			} else {
				pos[b.cur_pos] += b.len;
			}
		}

		tool::move_ref_along(this->ptr, b.it, b.step, 1);

		return *this;
	}

	this_type& operator -=(const iter_nd_border_walker& b)
	{
		//TODO: create the specialized versions:
		// 1: for step, which excludes posit
		// 2: for array, and 0: same as below
		if(b.cur_pos >= 0) { // b is for an array dimension
			if(cur_pos == b.cur_pos) {
				posit -= b.len;
				diff -= b.len;
			} else {
				pos[b.cur_pos] -= b.len;
			}
		}

		tool::move_ref_along(this->ptr, b.it, -b.step, 1);


		return *this;
	}

	template <bool C, int S, bool P>
	void inc_along_other_dim_at_begin(const catarray_nd_iterator<T, IT, CONST_IT,
						REF_IS_ND, C, S, P>& it)
	// 1. other it must be at begin
	// 2. must be of different direction
	{
		//TODO: create specialized by SP x S versions of inc along
		//if(it.type == ctool::array_it) {
		if(it.cur_pos >= 0) {

			tool::move_ref_along(this->ptr, it.ptr,
									*(it.diff + (pos[it.cur_pos]++)), 1);

		} else {

			tool::inc_along(*this, it);
		}
	}

	template <bool C, int S, bool P>
	void dec_along_other_dim_at_begin(const catarray_nd_iterator<T, IT, CONST_IT,
						REF_IS_ND, C, S, P>& it)
	// 1. other it must be at begin
	// 2. must be of different direction
	{
		//TODO: create specialized by SP x S versions of inc along
		//if(it.type == ctool::array_it) {
		if(it.cur_pos >= 0) {

			tool::move_ref_along(this->ptr, it.ptr,
									-*(it.diff + (--pos[it.cur_pos])), 1);

		} else {

			tool::dec_along(*this, it);
		}
	}

	template <bool C, int S, bool P>
	void move_along(const catarray_nd_iterator<T, IT, CONST_IT,
						REF_IS_ND, C, S, P>& it,
		ptrdiff_t j)
	// none of these holds!
	// 1. other it must be at begin
	// 2. must be of different direction
	{
		//TODO: create specialized by SP x S versions of inc along
		//if(it.type == ctool::array_it) {
		if(it.cur_pos >= 0) {

			if(cur_pos == it.cur_pos) {

				size_t last = idx[posit];
				posit += j;
				diff += j;
				ptr += step * (idx[posit] - last);

			} else {

				size_t& p(pos[it.cur_pos]);
				ptrdiff_t last = it.idx[p];
				p += j;
				tool::move_along(*this, it, it.idx[p] - last);

			}
		} else {

			// TODO: ensure this calls the correct offset displacement
			// for singleton-dim arrays, and if not try to set step
			// accordingly, to make so.
			tool::move_along(*this, it, j);
		}
	}

	template <class J>
	inline this_type operator +(const J& j) const
	{
		this_type tmp(*this);
		tmp += j;
		return tmp;
	}

	template <class J>
	inline this_type operator -(const J& j) const
	{
		this_type tmp(*this);
		tmp -= j;
		return tmp;
	}

	//! difference
	template<bool C, int S, bool P>
	ptrdiff_t operator -(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S, P>& it)
	{
		// note: only for itertors of the same dim.
		//TODO: create the specialized versions:
		// 1: for step
		// 2: for array
		// 0: for the following with if:
		if(cur_pos >= 0) {
			return posit - it.posit;

		} else {

			return (ptr - it.ptr) / step;
		}
	}

	//! equality test
	template<bool C, int S>
	bool operator==(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
			PAST_END_CAPABLE>& it) const
	{
		return (ptr == it.ptr);
	}

	template<bool C, int S>
	bool operator!=(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
			PAST_END_CAPABLE>& it) const
	{
		return (ptr != it.ptr);
	}

	template<bool C, int S>
	bool operator<(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
			PAST_END_CAPABLE>& it) const
	{
		//TODO: specializations
		if(cur_pos >= 0) {
			return posit < it.posit;

		} else {
			return (step > 0) ? (ptr < it.ptr) : (it.ptr < ptr);
		}
	}

	template<bool C, int S>
	bool operator<=(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
			PAST_END_CAPABLE>& it) const
	{
		return (*this == it || *this < it);
	}

	template<bool C, int S>
	bool operator>(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
			PAST_END_CAPABLE>& it) const
	{
		return (!(*this == it) && !(*this < it));
	}

	template<bool C, int S>
	bool operator>=(
		const catarray_nd_iterator<T, IT, CONST_IT, REF_IS_ND, C, S,
			PAST_END_CAPABLE>& it) const
	{
		return (!(*this < it));
	}

};



} /*namespace data */

namespace catarray_iter_create {

template <class IT, class A>
IT _begin(A& a, size_t d)
{
	size_t j = a.nonsing_rmap[d];
	ptrdiff_t k = a.idx_ar_rmap[d]; // cur_pos

	return IT(a.get_iter(j), a.steps[j], 0, (*a.idx)[d].c_ptr(), a.diffs[j],
		k, a.type_from_indtype((*a.idx)[d].indtype),
		a.idx_ar_map.length());
}

template <class IT, class A>
IT _begin(A& a, size_t d, const IT& it)
{
	size_t j = a.nonsing_rmap[d];
	ptrdiff_t k = a.idx_ar_rmap[d]; // cur_pos

	return IT(it.ptr, a.steps[j], it.pos[k < 0 ? 0 : k], (*a.idx)[d].c_ptr(),
		a.diffs[j], k, a.type_from_indtype((*a.idx)[d].indtype), it.pos);
}

template <class IT, class ITS, class A>
IT _iter(A& a, size_t d, const ITS& it)
{
	size_t j = a.nonsing_rmap[d];
	ptrdiff_t k = a.idx_ar_rmap[d]; // cur_pos

	return iterator_nd(it.ir, a.steps[j], it.pos0, (*a.idx)[d].c_ptr(),
		a.diffs[j], k, a.type_from_indtype((*a.idx)[d].indtype), it.pos,
		1, it.get_pos1());

	/*return _begin(d, it);*/
}

template <class IT, class S, class A>
IT _iter(A& a, size_t d, const array<size_t, S>& ind)
{
	typename IT::reference_iterator it = a.iter[-3];

	array<size_t, tiny> pos(a.idx_ar_map.length());
	for(size_t i = 0; i < ind.length(); i++) {
		ptrdiff_t q = a.idx_ar_rmap[i];
		size_t n = a.nonsing_rmap[i];
		if(q < 0) {
			A::tool::move_along(it, a.iter[n], a.steps[n], ind[i]);
		} else {
			A::tool::move_along(it, a.iter[n], a.steps[n], (*a.idx)[i][ind[i]]);
			pos[q] = ind[i];
		}
	}
	size_t j = a.nonsing_rmap[d];
	ptrdiff_t k = a.idx_ar_rmap[d]; // cur_pos

	return IT(it, a.steps[j], ind[d], (*a.idx)[d].c_ptr(), a.diffs[j],
		k, a.type_from_indtype((*a.idx)[d].indtype), pos);
}

template <class IT, class A>
IT _next(A& a, size_t d, const IT& it)
{
	typename IT::reference_iterator itp = it.ptr;

	size_t j = a.nonsing_rmap[d];
	ptrdiff_t k = a.idx_ar_rmap[d]; // cur_pos

	A::tool::move_along(itp, a.iter[j], 1, a.begin_to_end[j]);

	if(k < 0) // maybe could also be discriminated from indtype
		return IT(itp, a.steps[j], a.sizes[j], (*a.idx)[d].c_ptr(), a.diffs[j],
			k, a.type_from_indtype((*a.idx)[d].indtype), it.pos);
	else
		return IT(itp, a.steps[j], a.sizes[j], (*a.idx)[d].c_ptr(), a.diffs[j],
			k, a.type_from_indtype((*a.idx)[d].indtype), it.pos,
			k, a.sizes[j]);
}

template <class IT, class A>
IT _end(A& a, size_t d)
{
	size_t j = a.nonsing_rmap[d];
	ptrdiff_t k = a.idx_ar_rmap[d]; // cur_pos

	typename IT::reference_iterator it = a.get_iter(j);

	it += a.begin_to_ends[j];

	if(k < 0)
		return IT(it, a.steps[j], a.sizes[j], (*a.idx)[d].c_ptr(), a.diffs[j],
			k, a.type_from_indtype((*a.idx)[d].indtype),
							a.idx_ar_map.length());
	else
		return IT(it, a.steps[j], a.sizes[j], (*a.idx)[d].c_ptr(), a.diffs[j],
			k, a.type_from_indtype((*a.idx)[d].indtype),
			a.idx_ar_map.length(), k, a.sizes[j]);
}

template <class IT, class A>
IT _last(A& a, size_t d)
{
	size_t j = a.nonsing_rmap[d];
	ptrdiff_t k = a.idx_ar_rmap[d]; // cur_pos

	typename IT::reference_iterator it = a.get_iter(j);

	it += a.first_to_lasts[j];

	if(k < 0)
		return IT(it, a.steps[j], a.sizes[j] - 1,
							(*a.idx)[d].c_ptr(), a.diffs[j],
			k, a.type_from_indtype((*a.idx)[d].indtype),
							a.idx_ar_map.length());
	else
		return IT(it, a.steps[j], a.sizes[j] - 1,
							(*a.idx)[d].c_ptr(), a.diffs[j],
			k, a.type_from_indtype((*a.idx)[d].indtype),
			a.idx_ar_map.length(), k, a.sizes[j]);
}

}; // namespace catarray_iter_create

} /*namespace ivl */

#endif
#endif // IVL_CORE_DETAILS_ITERATOR_CATARRAY_ND_ITERATOR_HPP
