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


/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 class A,
		 class I,
		 class DERIVED_INFO
	     >
class array<T, data::subarray<A, I, DERIVED_INFO> >
	:
	public array_common_base<array<T,
		data::subarray<A, I, DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::subarray<A, I, DERIVED_INFO> > >::type>
{
private:
	typedef array_common_base<array<T,
		data::subarray<A, I, DERIVED_INFO> > > common_base_class;

protected:
//--------------------------------------------------------------------------
// types

	// validates that I is random access.
	// if there is a compile error here, you are probably trying to create
	// a subarray with an index_array that has no random access.
	types::validate_class<typename I::has_random_access, types::t_true>
		index_array_is_valid;

	// I is stored or referenced? :
	typedef typename types::is_ref<I>::type prv_i_ref;
	typedef typename types::bare_type<I>::type prv_i;
	typedef typename types::t_if<prv_i_ref,
		const typename types::bare_type<I>::type*,
		internal::relaxed_pointer_face<
			typename types::bare_type<I>::type> >
			::type prv_i_type;

	// reference_iterator_is_nd:
	// define true if the underlying array will be accessed using an
	// iterator_nd. otherwise it will be accessed using an iterator.
	// the two options differ a lot and have seperate implementations.
	typedef typename types::t_if<
		types::t_and<
			types::t_eq<
				typename A::optimal_access_tag, data::seq_optimal_tag>,
			typename A::has_random_access
		>, types::t_false, types::t_true>::type reference_iterator_is_nd;

	// best_reference_iterator:
	// defines which is the best possible iterator to be used for the
	// underlying array, meaning the most powerful, between the const_
	// and non-const_ ones. const_ is used if the array is read only.
	typedef typename types::t_if<reference_iterator_is_nd,
		typename
			types::best_iterator_nd<A>::type
			/*types::t_if<typename A::is_writeable,
				typename A::iterator_nd,
				typename A::const_iterator_nd>::type,*/,

		typename
			types::best_iterator<A>::type/*
			types::t_if<typename A::is_writeable,
				typename A::iterator,
				typename A::const_iterator>::type todo:wipe*/

		>::type best_reference_iterator;

	// const_reference_iterator:
	// defines which is the const_iterator to be used for the
	// underlying array.
	typedef typename types::t_if<reference_iterator_is_nd,
		typename A::const_iterator_nd,
		typename A::const_iterator

		>::type const_reference_iterator;

	typedef best_reference_iterator best_ref_iter;
	typedef const_reference_iterator const_ref_iter;

	// tool:
	// the correct specialization of the class subarray_tools that implements
	// functionality of the reference iterator depending of the type.
	typedef array_details::subarray_tools<
		reference_iterator_is_nd, best_ref_iter> tool;

	// some helper structs
	typedef array_details::subarray_common_tools ctool;

	// used to disable some types. TODO: test that not_a_type actually throws an error and
	// consider explicitly making the default constructor private.
	class not_a_type { };
	struct skip_assign { template<class X> void assign_array(X t) const {} };

	typedef typename types::t_if<types::is_const<A>,
	typename types::remove_const<A>::type, not_a_type>::type prv_second_init_a;


//--------------------------------------------------------------------------
// members
	A* in;
	prv_i_type idx;


	// helper data that is computed on the construction of the subarray
	// object, needed to improve speed.

	array<size_t, tiny> all_sizes; // the subarray sizes
	size_t all_len; // the subarray total length
	int itspec1; // the inner iterator specialization
	int itspec2; // the second inner iterator specialization

	// arrays with size equal to the total of non singleton dimensions
	array<array<ptrdiff_t, tiny>, stack<5> > diffs_ar;
	array<ptrdiff_t*, stack<5> > diffs;
	array<size_t, stack<5> > sizes;
	array<ptrdiff_t, stack<5> > steps;
	array<best_reference_iterator> iters;
	const best_reference_iterator* iter;
	array<ptrdiff_t, tiny> back_diffs;
	array<ptrdiff_t, tiny> begin_to_ends;
	array<ptrdiff_t, tiny> first_to_lasts;

	// maps from one type of ordering to another
	array<size_t, tiny> nonsing_map;
	array<size_t, tiny> nonsing_rmap;
	array<size_t, tiny> idx_ar_map;
	array<ptrdiff_t, tiny> idx_ar_rmap;




//--------------------------------------------------------------------------
// functions


	array<size_t, tiny> starts_vec()
	{
		size_t i;
		size_t ndim = idx->length();
		array<size_t, tiny> ar(in->ndims());
		for(i = 0; i < ndim; i++)
			ar[i] = (*idx)[i].starts();
		for(; i < ar.length(); i++)
			ar[i] = 0;
		return ar;
	}

	array<size_t, tiny> ends_vec()
	{
		size_t i;
		size_t ndim = idx->length();
		array<size_t, tiny> ar(in->ndims());
		for(i = 0; i < ndim; i++) {
			if((*idx)[i].is_all())
				ar[i] = in->size_nd(i) - 1;
			else
				ar[i] = (*idx)[i].ends();
		}
		for(; i < ar.length(); i++)
			ar[i] = 0;
		return ar;
	}

	const best_reference_iterator& get_iter(size_t d) const
	{
		return types::r_if<reference_iterator_is_nd> (iter[d], iter[-3]);
	}

	template <class J, class D>
	void copy_or_cut_impl(const array<J, D>& o)
	{
		//if(is_content_resizeable::value && o.begin() == o.end() && len != 0) {
			/*

			cut!

			indirect_tool::shrink(*a,
				indirect_tool::cut(a->begin(), *b, a->length()));

			len = 0;
			*/

		//} else
		{
			// for non-const: do not do nothing!
			types::r_if<typename this_type::is_writeable>(
				static_cast<common_base_class&>(*this), skip_assign()).assign_array(o);
		}
	}
	template <class J, class D>
	void copy_or_cut_impl(const array_nd<J, D>& o)
	{
		//if(is_content_resizeable::value && o.begin() == o.end() && len != 0) {
			/*

			cut!

			indirect_tool::shrink(*a,
				indirect_tool::cut(a->begin(), *b, a->length()));

			len = 0;
			*/

		//} else
		{
			types::r_if<typename this_type::is_writeable>(
				static_cast<common_base_class&>(*this), skip_assign()).assign_array(o);
		}
	}
	template <class J, class D>
	void copy_or_cut(const array<J, D>& o)
	{
		copy_or_cut_impl(o);
	}
	template <class J, class D>
	void copy_or_cut(const array_nd<J, D>& o)
	{
		copy_or_cut_impl(o);
	}
	template <class J, class P2, class D>
	void copy_or_cut(const array_nd<J, data::subarray<A, P2, D> >& o)
	{
		if(!in)
			this->init(o.get_ref_1(), o.get_ref_2());
		else
			copy_or_cut_impl(o);
	}
	template <class J, class P2, class D>
	void copy_or_cut(const array_nd<J, data::subarray<
		prv_second_init_a, P2, D> >& o)
	{
		if(!in)
			this->init(o.get_ref_1(), o.get_ref_2());
		else
			copy_or_cut_impl(o);
	}

public:
	void init(A& a, const prv_i& idx);

	void init(const array& o);

	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename best_reference_iterator::reference reference;
	typedef typename best_reference_iterator::reference best_reference;
	typedef typename const_reference_iterator::reference const_reference;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	using base_class::derived;

	typename types::t_and_3<
		types::t_not<types::is_const<A> >,
		typename A::is_writeable,
		typename A::is_resizeable>
		::type is_cuttable;



	// typedefs for class iterators
	typedef typename types::t_if<types::t_and<typename array::is_writeable,
		types::t_not<types::is_const<A> > >,
		data::subarray_iterator_type<T, best_reference_iterator,
			best_reference_iterator,
			reference_iterator_is_nd::value, false>,
		not_a_type>::type iterator;

	typedef data::subarray_iterator_type<T, const_reference_iterator,
		best_reference_iterator,
		reference_iterator_is_nd::value, true> const_iterator;

	typedef typename types::t_if<types::t_eq<iterator, not_a_type>,
		const_iterator, iterator>::type best_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename const_iterator::iter_border_walker iter_border_walker;

	template<int SPC>
	struct s_iterator
	{
		typedef data::subarray_iterator_type<T, best_reference_iterator,
			best_reference_iterator,
			reference_iterator_is_nd::value, false, SPC> type;
	};
	template<int SPC>
	struct const_s_iterator
	{
		typedef data::subarray_iterator_type<T, best_reference_iterator,
			best_reference_iterator,
			reference_iterator_is_nd::value, true, SPC> type;
	};
	template<int SPC>
	struct reverse_s_iterator
	{
		typedef std::reverse_iterator<s_iterator<SPC> > type;
	};
	template<int SPC>
	struct const_reverse_s_iterator
	{
		typedef std::reverse_iterator<const_s_iterator<SPC> > type;
	};
	int iter_specialization() const
	{
		return itspec1;
	}

	iterator begin()
	{
		// 0,
		return iterator(iter[-3], iter, nonsing_map.length(),
			sizes.c_ptr(), diffs.c_ptr(), steps.c_ptr(),
			back_diffs.c_ptr(), false, 1);
	}

	iterator end()
	{
		// sum_begin_to_end, tool::index_base(iter[-1], iter[-3]),
		return iterator(iter[-1], iter, nonsing_map.length(),
			sizes.c_ptr(), diffs.c_ptr(), steps.c_ptr(),
			back_diffs.c_ptr(), false, 2); // false `ending`, not true, because it cycles like counter
	}

	const_iterator begin() const
	{
		// 0,
		return const_iterator(iter[-3], iter, nonsing_map.length(),
			sizes.c_ptr(), diffs.c_ptr(), steps.c_ptr(),
			back_diffs.c_ptr(), false, 1);
	}

	const_iterator end() const
	{
		// sum_begin_to_end, tool::index_base(iter[-1], iter[-3]),
		return const_iterator(iter[-1], iter, nonsing_map.length(),
			sizes.c_ptr(), diffs.c_ptr(), steps.c_ptr(),
			back_diffs.c_ptr(), false, 2); // false `ending`, not true, because it cycles like counter
	}

	// reverse iterator defs
	reverse_iterator rbegin() { return reverse_iterator(end()); }

	reverse_iterator rend() { return reverse_iterator(begin()); }

	const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(end()); }

	const_reverse_iterator rend() const
		{ return const_reverse_iterator(begin()); }


	iter_border_walker first_to_last()
	{
		return iter_border_walker(1,
			types::r_if<reference_iterator_is_nd>(0, iter[-2] - iter[-3]));
	}

	iter_border_walker begin_to_end()
	{
		return iter_border_walker(2,
			types::r_if<reference_iterator_is_nd>(0, iter[-1] - iter[-3]));
	}

	typename types::best_iterator<array>::type::reference operator[](size_t j)
	{
		//TODO: Note: method should be discussed
		array<size_t, data::tiny> idd(derived().size_nd().length());
		size_t i;
		for(i = 0; i + 1 < idd.length(); i++) {
			idd[i] = j % derived().size_nd(i);
			j /= derived().size_nd(i);
		}
		idd[i] = j; // % derived().size_nd(i);
		return derived()(idd);
	}

	typename const_iterator::reference operator[](size_t j) const
	{
		//TODO: Note: method should be discussed
		array<size_t, data::tiny> idd(derived().size_nd().length());
		size_t i;
		for(i = 0; i + 1 < idd.length(); i++) {
			idd[i] = j % derived().size_nd(i);
			j /= derived().size_nd(i);
		}
		idd[i] = j; // % derived().size_nd(i);
		return derived()(idd);
	}

	using common_base_class::operator [];


/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const
	{
		return all_len;
	}

	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }

	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/




/** @name Constructors
@{*/
	array() { in = NULL; }

	array(const array& o) { init(o); }

	array(A& a, const prv_i& idxn)
	{
		init(a, idxn);
	}
	template<class J>
	array(A& a, const J& idxn)
	{
		init(a, idxn);
	}


	void setref(A& a, const prv_i& idxn)
	{
		init(a, idxn);
	}
	template<class J>
	void setref(A& a, const J& idxn)
	{
		init(a, idxn);
	}

	template <class D>
	bool overlap(const D& d) const
	{
		return in->overlap(d);
	}

	template <class D>
	bool self_overlap(const D& d) const
	{
		return d.overlap(*in) || d.overlap(*idx);
	}

/**/

    //! destructor
	~array() {
	}

	//using common_base_class::operator=;
	template<class K>
	derived_type& operator=(const K& o)
	{
		// avoid the safety check when we just need to assign
		// TODO: check about this all, espec. const K&. and what happens
		// when we derive to higher class, e.g. image, what is called.
		// (esp. for subarray).
		if(!in)
			this->assign(o);
		else
			common_base_class::operator=(o);
		return this->derived();
	}

	this_type& operator=(const array& o)
	{
		//TODO:check
		if(!in)
			init(o);
		else
			common_base_class::operator=(o); return *this;
	}

	template<class D>
	derived_type& assign_array(const D& o)
	{
		copy_or_cut(o);
		return this->derived();
	}

	A& get_ref_1() const { return *in; }
	const prv_i& get_ref_2() const { return *idx; }

};


template <class T,
		 class A,
		 class I,
		 class DERIVED_INFO
	     >
void array<T, data::subarray<A, I, DERIVED_INFO> >
	::init(const array& o)
{
	in = o.in;
	if(!in) return;
	idx = o.idx;

	all_sizes = o.all_sizes;
	all_len = o.all_len;

	itspec1 = o.itspec1;
	itspec2 = o.itspec2;

	diffs_ar = o.diffs_ar;
	sizes = o.sizes;
	steps = o.steps;
	iters = o.iters;
	iter = iters.c_ptr() + 4;
	back_diffs = o.back_diffs;
	begin_to_ends = o.begin_to_ends;
	first_to_lasts = o.first_to_lasts;

	nonsing_map = o.nonsing_map;
	nonsing_rmap = o.nonsing_rmap;
	idx_ar_map = o.idx_ar_map;
	idx_ar_rmap = o.idx_ar_rmap;

	//diffs refers to local pointers so it has to be re-initialized.
	size_t jmin = nonsing_map.length();
	diffs.resize(jmin + 2, NULL);

	size_t ia = idx_ar_map.length();
	for(size_t a = 0; a < ia; a++)
	{
		size_t k = idx_ar_map[a];
		size_t i = nonsing_rmap[k];
		diffs[i] = diffs_ar[a].c_ptr() + 1;
	}

	if(!reference_iterator_is_nd::value) {
		diffs[jmin] = diffs_ar[ia].c_ptr();
	}

	diffs[jmin + 1] = diffs_ar[ia + 1].c_ptr() + 1;
}

template <class T,
		 class A,
		 class I,
		 class DERIVED_INFO
	     >
void array<T, data::subarray<A, I, DERIVED_INFO> >
::init(A& a, const
	   typename array<T, data::subarray<A, I, DERIVED_INFO> >::prv_i& idx)
{
	using namespace ivl::types;

	in = &a;
	this->idx = &idx;
	//todo: check no sizes==0!!

	size_t ndims = idx.length(); //a.ndims();

	//std::cout << "SUBARRAY " << idx << "OF:" << a << ":O (" <<ndims << ")"<<std::endl;
	CHECK(ndims != 0, ecomp);
//@@@@todo:redo	CHECK(idx.length() == ndims, ecomp);

	size_t j = 0;
	size_t ia = 0;

	all_sizes.resize(ndims);
	all_len = 1;
	itspec1 = 0;
	itspec2 = 0;

	for(size_t i = 0; i < ndims; i++) {

		if(idx[i].is_all())
			all_sizes[i] = a.size_nd(i);
		else
			all_sizes[i] = idx[i].length();

		if(all_sizes[i] > 1) {
			if(idx[i].is_array()) ia++;
			j++;
		}

		//@@@@@
		if(ndims < idx.length() && i == ndims - 1) {
			for(size_t p = i + 1; p < idx.length(); p++) {
				all_sizes[i] *= a.size_nd(p);
			}
		}

		all_len *= all_sizes[i];
	}

	bool j0 = (j == 0);
	size_t jmin = (j <= 1 ? 2 : j);
		// in case we have only 1 dimension, we have to make it 2 dimensions
		// with outer having size = 1, to comply with the loops.

	nonsing_map.resize(jmin);
	//first_to_last.resize(jmin);todo:wipe
	diffs.resize(jmin + 2); // 1 for an extra helper dim which moves to end
						 // and 1 to use for all singleton dims
	back_diffs.resize(jmin + 2);
	begin_to_ends.resize(jmin + 2);
	first_to_lasts.resize(jmin + 2);
	sizes.resize(jmin + 2);
	steps.resize(jmin + 2);
	iters.resize(4 + r_if<reference_iterator_is_nd>(jmin + 2, 0));
		// same as above for nd_reference, but also 4 iterators in front
		// which are: begin-1, begin, end-1, end
	iter = iters.c_ptr() + 4;


	nonsing_rmap.resize(ndims);
	nonsing_map[1] = size_t(-1);

	for(size_t i = 0, k = 0; i < ndims; i++)
		if(all_sizes[i] == 1) {
			nonsing_rmap[i] = jmin + 1;
			// singleton location
		} else {
			nonsing_map[k] = i;
			nonsing_rmap[i] = k;
			k++;
		}

	if(j0) {
		// single element subarray
		nonsing_map[0] = 0;
		nonsing_rmap[0] = 0;
	}

	// inner iterator specializations
	size_t inner = nonsing_map[0];
	if(idx[inner].is_array()) itspec1 = 2; else itspec1 = 1;
	if(j > 1) {
		if(idx[nonsing_map[1]].is_array()) itspec2 = 2; else itspec2 = 1;
	}

	// store the 4 important reference iterators
	if(all_len == 0) { //todo: check if this is actually necessary and why
		//iters[0] = tool::end(a, inner); //todo: also use something faster here.
		iters[1] = tool::end(a, inner);
		iters[2] = tool::end(a, inner);
		iters[3] = tool::end(a, inner);
	} else {
		//iters[0] = tool::rend_base(a, inner);
		iters[1] = tool::begin(a, inner, starts_vec());
		iters[2] = tool::begin(a, inner, ends_vec()); //rbegin_base
		iters[3] = tool::end(a, inner);
	}

	if(reference_iterator_is_nd::value) {
		// one iterator for each non-singleton dimension.
		for(size_t i = 0; i < j; i++) {
			iters[4 + i] = tool::iter(a, nonsing_map[i], iters[1]);
		}

		// [jmin + 5] for all singleton dimensions. [jmin + 4] is padding.
		iters[jmin + 5] = iters[1];

		// if dims = 1, iter[4 + 1] must have a value but it won't be used.
		if(jmin > j) iters[5] = iters[1];
	}

	//sizes
	sizes[1] = 1;
	for(size_t i = 0; i < j; i++)
		sizes[i] = all_sizes[nonsing_map[i]];

	sizes[jmin] = 3;
	sizes[jmin + 1] = 1;

	//steps
	for(size_t i = 0; i < j; i++) {
		size_t k = nonsing_map[i];
		steps[i] = idx[k].steps();

		if(!reference_iterator_is_nd::value)
			steps[i] *= tool::stride(a, k);
	}
	steps[jmin] = 1;
	steps[jmin + 1] = 1;


	//diffs resize
	diffs_ar.resize(ia + 2);
	idx_ar_map.resize(ia);
	idx_ar_rmap.resize(ndims, -1);

	//diffs
	for(size_t i = 0, a = 0; i < j; i++) {
		size_t k = nonsing_map[i];
		if(!idx[k].is_array())
			diffs[i] = NULL;
		else {
			idx_ar_map[a] = k;
			idx_ar_rmap[k] = a;

			array<ptrdiff_t, tiny>& diff = diffs_ar[a];
			typedef typename I::elem_type::size_array idx_sz_t;
			const idx_sz_t& idc = idx[k];
			diff.resize(idc.length() + 1);

			for(size_t p = 0, l = idc.length() -1; p < l; p++)
				diff[p + 1] = (idc[p + 1] - idc[p]) *
					r_if<reference_iterator_is_nd>(1, steps[i]);

			diff[0] = (idc[0] + 1) *
				r_if<reference_iterator_is_nd>(1, steps[i]);

			*diff.rbegin() = (ptrdiff_t(in->size_nd(k)) - ptrdiff_t(*idc.rbegin())) *
				r_if<reference_iterator_is_nd>(1, steps[i]);

			diffs[i] = diff.c_ptr() + 1;

			a++;
		}
	}

	if(!reference_iterator_is_nd::value) {
		diffs_ar[ia].resize(2);
		diffs[jmin] = diffs_ar[ia].c_ptr();
		//diffs[jmin][0] = 0; // we dont need begin to begin-1!!!
			//r_if<reference_iterator_is_nd>(0, iters[1]) -
			//r_if<reference_iterator_is_nd>(0, iters[0]);//maybe 2 to 0 if back is considered.

		diffs[jmin][1] =
			r_if<reference_iterator_is_nd>(0, iters[3]) -
			r_if<reference_iterator_is_nd>(0, iters[1]);
	}

	diffs_ar[ia + 1].resize(2);
	diffs[jmin + 1] = diffs_ar[ia + 1].c_ptr() + 1;
	diffs[jmin + 1][-1] = 1;
	diffs[jmin + 1][0] = 1;



	//back_diffs, begin_to_ends and first_to_lasts
	for(size_t i = 0, a = 0; i < j; i++) {
		size_t k = nonsing_map[i];
		if(idx[k].is_array()) {
			back_diffs[i] = - steps[i] *
			(*(idx[k].as_array().rbegin()) -
			*(idx[k].as_array().begin()));

			first_to_lasts[i] = -back_diffs[i];
            begin_to_ends[i] = -back_diffs[i] + *diffs_ar[a].rbegin();

            a++;

		} else {
			back_diffs[i] = - ptrdiff_t(sizes[i] - 1) * steps[i];

			first_to_lasts[i] = -back_diffs[i];
            begin_to_ends[i] = -back_diffs[i] + steps[i];
		}


		if(i > 0 && !reference_iterator_is_nd::value)
			back_diffs[i] += back_diffs[i - 1];
	}

	if(!reference_iterator_is_nd::value) {
		for(size_t i = 0; i + 1 < j; i++) {
			if(!idx[nonsing_map[i + 1]].is_array())
				back_diffs[i] += steps[i + 1];
		}
	}

	if(jmin > j)
		back_diffs[1] =
			(reference_iterator_is_nd::value ? 0 : back_diffs[0]);

	back_diffs[jmin] = 0;
	back_diffs[jmin + 1] = 0;

    begin_to_ends[jmin + 1] = 1;
    first_to_lasts[jmin + 1] = 0;
/*
for(size_t i=0;i<iters.length();i++)
std::cout << "itr:["<<i<<"]=" << &*iters[i] << std::endl;
std::cout << "su:" << diffs_ar << " of sz: " << all_sizes << std::endl;
std::cout << idx[idx.length()-1].length() << std::endl;*/
}
