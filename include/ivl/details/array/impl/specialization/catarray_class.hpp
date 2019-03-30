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


#if 1
/**
 * \brief 1-dimensional %array of type T
 *
 * This class defines an simple one-dimensional %array.
 */
template <class T,
		 class A1,
		 class A2,
		 int CATDIM,
		 class DERIVED_INFO
	     >
class array<T, data::catarray<A1, A2, CATDIM, DERIVED_INFO> >
	:
	public array_common_base<array<T,
		data::catarray<A1, A2, CATDIM, DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::catarray<A1, A2, CATDIM,
			DERIVED_INFO> > >::type>
{
private:
	typedef array_common_base<array<T,
		data::catarray<A1, A2, CATDIM,
			DERIVED_INFO> > > common_base_class;

protected:
//--------------------------------------------------------------------------
// types

	// A1, A2 is stored or referenced? :
	typedef typename types::is_ref<A1>::type prv_a1_ref;
	typedef typename types::bare_type<A1>::type prv_a1;
	typedef typename types::t_if<prv_a1_ref, 
		typename types::ref_to_ptr<A1>::type, 
		internal::ridiculous_relaxed_pointer_face<
			typename types::bare_type<A1>::type> >
			::type prv_a1_type;
	typedef typename types::is_ref<A2>::type prv_a2_ref;
	typedef typename types::bare_type<A2>::type prv_a2;
	typedef typename types::t_if<prv_a2_ref, 
		typename types::ref_to_ptr<A2>::type, 
		internal::ridiculous_relaxed_pointer_face<
			typename types::bare_type<A2>::type> >
			::type prv_a2_type;

	// best_reference_iterator:
	// defines which is the best possible iterator to be used for the
	// underlying array, meaning the most powerful, between the const_
	// and non-const_ ones. const_ is used if the array is read only.
	typedef typename types::best_iterator<prv_a1>::type best_reference_iterator1;
	typedef typename types::best_iterator<prv_a2>::type best_reference_iterator2;


	// const_reference_iterator:
	// defines which is the const_iterator to be used for the
	// underlying array.
	typedef typename prv_a1::const_iterator const_reference_iterator1;
	typedef typename prv_a2::const_iterator const_reference_iterator2;


	typedef best_reference_iterator1 best_ref_iter1;
	typedef const_reference_iterator1 const_ref_iter1;
	typedef best_reference_iterator2 best_ref_iter2;
	typedef const_reference_iterator2 const_ref_iter2;

#if 0
	// tool:
	// the correct specialization of the class catarray_tools that implements
	// functionality of the reference iterator depending of the type.
	typedef array_details::catarray_tools<
		reference_iterator_is_nd, best_ref_iter> tool;


	// some helper structs
	typedef array_details::catarray_common_tools ctool;

#endif
	// used to disable some types. TODO: test that not_a_type actually throws an error and
	// consider explicitly making the default constructor private.
	class not_a_type { };

	typedef typename types::t_if<types::t_expr<(CATDIM == -1)>,
		ivl::scalar<int>, ivl::fixed_scalar<int, CATDIM> >::type catdim_t;


//--------------------------------------------------------------------------
// members
	//A1* in1;
	//A2* in2;
	prv_a1_type in1;
	prv_a2_type in2;

	catdim_t cdim;
	size_t catstride, catstride1, catstride2;
	size_t all_len;


	// helper data that is computed on the construction of the catarray
	// object, needed to improve speed.




//--------------------------------------------------------------------------
// functions

public:
	void init(A1& a1, A2& a2, catdim_t cdim = -1);
	void init(const array& o);

	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename std::iterator_traits<best_reference_iterator1>::reference reference;
	typedef typename std::iterator_traits<best_reference_iterator1>::reference best_reference;
	typedef typename std::iterator_traits<const_reference_iterator1>::reference const_reference;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	using base_class::derived;



	struct iter_border_walker
	{
		typedef typename prv_a1::iter_border_walker t1;
		typedef typename prv_a2::iter_border_walker t2;
		t1 s1;
		t2 s2;
		ptrdiff_t sp;

		iter_border_walker() {}
		iter_border_walker(const t1& s1, const t2& s2, ptrdiff_t sp)
		: s1(s1), s2(s2), sp(sp) { }
	};

	template<bool CONST, int SPEC = 0>
	class iterator_type
	: public types::t_if<typename array::has_random_access,
	data::data_details::
		rnd_iter_operator_expander<iterator_type<CONST, SPEC>, T, CONST,
			typename types::remove_const<reference>::type>,
	data::data_details::
		iter_operator_expander<iterator_type<CONST, SPEC>, T, CONST,
			typename types::remove_const<reference>::type >
	>::type,
	public types::border_walker_iterator_identifier
	{
	private:
		template <bool C, int S> friend class iterator_type;
		friend class array;

		friend class iter_border_walker;

		friend class data::data_details::iter_operator_expander
			<iterator_type<CONST, SPEC>, T, CONST>;
		friend class data::data_details::rnd_iter_operator_expander
			<iterator_type<CONST, SPEC>, T, CONST>;

		typedef typename types::apply_const<T, types::t_expr<CONST> >
			::type best_value_type;

		// this class is used to disable specific specialization members
		class not_a_type { };

		typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
			types::code_word<> >::type invalid_if_const;

		typedef typename types::t_if<types::t_expr<CONST>,
			typename prv_a1::const_iterator,
			typename prv_a1::best_iterator>::type iterator1;

		typedef typename types::t_if<types::t_expr<CONST>,
			typename prv_a2::const_iterator,
			typename prv_a2::best_iterator>::type iterator2;

		typedef typename std::iterator_traits<iterator1>::reference prv_reference;
		typedef prv_reference best_ref_type;

		iterator1 ir1;
		iterator2 ir2;
		ptrdiff_t p;
		size_t stride1, stride2, stride;

	protected:
		inline const_reference base(
			types::code_word<> ok = types::code_word<>()) const
			{ return p < stride1 ? (*ir1) : (*ir2); }

		inline prv_reference base(
			invalid_if_const disable = invalid_if_const())
			{ return p < stride1 ? (*ir1) : (*ir2); }

		inline typename types::apply_const<best_ref_type>::type base(size_t j,
			types::code_word<> ok = types::code_word<>()) const
		{
			ptrdiff_t soffs = (p + j) / stride;
			ptrdiff_t offs = (p + j) % stride;
			ptrdiff_t d;
			if(offs >= stride1) {
				d = soffs * stride2 +
					(p >= stride1 ? offs - p : offs);
				return ir2[d]; // TODO: rnd_add
			} else {
				d = soffs * stride1 +
					(p < stride1 ?  offs - p : offs - stride1);
				return ir1[d];
			}
		}

		inline best_ref_type base(size_t j,
			invalid_if_const disable = invalid_if_const())
		{
			ptrdiff_t soffs = (p + j) / stride;
			ptrdiff_t offs = (p + j) % stride;
			ptrdiff_t d;
			if(offs >= stride1) {
				d = soffs * stride2 +
					(p >= stride1 ? offs - p : offs);
				return ir2[d];
			} else {
				d = soffs * stride1 +
					(p < stride1 ?  offs - p : offs - stride1);
				return ir1[d];
			}
		}

	public:
		typedef iterator_type<CONST, 0> this_type;

		// iterator_traits
		typedef typename types::t_if<typename array::has_random_access,
			std::random_access_iterator_tag,
			std::bidirectional_iterator_tag>::type iterator_category;
		typedef T value_type;
		typedef typename types::apply_const<T, types::t_expr<CONST> >
			::type access_value_type;
		typedef ptrdiff_t difference_type;
		typedef access_value_type* pointer;
		typedef prv_reference reference;

		// border walker
		typedef typename array::iter_border_walker iter_border_walker;

		// constructors
		iterator_type() { }

		iterator_type(const this_type& it)
		: ir1(it.ir1), ir2(it.ir2), p(it.p),
			stride1(it.stride1), stride2(it.stride2), stride(it.stride)
		 { }

		template <bool C, int S>
		iterator_type(const iterator_type<C, S>& it)
		: ir1(it.ir1), ir2(it.ir2), p(it.p),
			stride1(it.stride1), stride2(it.stride2), stride(it.stride)
		 { }

		iterator_type(const iterator1& i1, const iterator2& i2,
			size_t p, size_t stride1, size_t stride2, size_t stride)
			: ir1(i1), ir2(i2), p(p),
				stride1(stride1), stride2(stride2), stride(stride) {}


		// members

		// increment-decrement
		this_type& operator++()
		{
			if(p++ < stride1)
				++ir1;
			else
			{
				++ir2;
				if(p >= stride)
					p = 0;
			}
			return *this;
		}
		this_type& operator--()
		{
			if(--p >= stride1)
				--ir2;
			else
			{
				--ir1;
				if(p < 0)
					p = stride;
			}
			return *this;
		}

		this_type operator++(int) { this_type t(*this); ++(*this); return t; }
		this_type operator--(int) { this_type t(*this); --(*this); return t; }

		this_type& operator +=(ptrdiff_t j)
		{
			ptrdiff_t soffs = (p + j) / stride;
			ptrdiff_t offs = (p + j) % stride;
			ptrdiff_t d;

			if(offs >= stride1) {
				d = soffs * stride2 +
					(p >= stride1 ? offs - p : offs);
				ir2 += d; // TODO: rnd_add
				ir1 += soffs * stride1 + (p >= stride1 ? 0 : stride1 - p);
			} else {
				d = soffs * stride1 +
					(p < stride1 ?  offs - p : offs - stride1);
				ir1 += d;
				ir2 += soffs * stride2 + (p < stride1 ? 0 : stride1 - p);
			}
			p = offs;

			return *this;
		}
		this_type& operator -=(ptrdiff_t j)
		{
			return (*this) += (-j);
		}
		inline this_type operator +(ptrdiff_t j) const
		{
			this_type tmp(*this);
			tmp += j;
			return tmp;
		}
		inline this_type operator -(ptrdiff_t j) const
		{
			this_type tmp(*this);
			tmp -= j;
			return tmp;
		}

		this_type& operator +=(iter_border_walker ib)
		{
			ir1 += ib.s1;
			ir2 += ib.s2;
			p += ib.sp;
			return *this;
		}
		this_type& operator -=(iter_border_walker ib)
		{
			ir1 -= ib.s1;
			ir2 -= ib.s2;
			p -= ib.sp;
			return *this;
		}
		inline this_type operator +(iter_border_walker j) const
		{
			this_type tmp(*this);
			tmp += j;
			return tmp;
		}
		inline this_type operator -(iter_border_walker j) const
		{
			this_type tmp(*this);
			tmp -= j;
			return tmp;
		}

		// difference
		ptrdiff_t operator-(const this_type& o) const
		{
			ptrdiff_t d1;
			d1 = (ir1 - o.ir1)
				+ ((p < stride1) ? -p : 0) + ((o.p < stride1) ? o.p : 0);
			return (d1 / stride1) * stride + p - o.p;
		}


		//copy same type iterator
		this_type& operator=(const this_type& it)
		{
			ir1 = it.ir1; ir2 = it.ir2; p = it.p;
			stride1 = it.stride1; stride2 = it.stride2; stride = it.stride;
			return *this;
		}
		//copy relevant type iterator
		template<bool C, int S>
		this_type& operator=(const iterator_type<C, S>& it)
		{
			ir1 = it.ir1; ir2 = it.ir2; p = it.p;
			stride1 = it.stride1; stride2 = it.stride2; stride = it.stride;
			return *this;
		}

		bool operator==(const this_type& it) const
			{ return (p == it.p && ir1 == it.ir1); }
		bool operator!=(const this_type& it) const
			{ return (p != it.p || ir1 != it.ir1); }
		bool operator<(const this_type& it) const
			{ return (ir1 < it.ir1 || (ir1 == it.ir1 && p < it.p)); }
		bool operator<=(const this_type& it) const
			{ return (ir1 < it.ir1 || (ir1 == it.ir1 && p <= it.p)); }
		bool operator>(const this_type& it) const
			{ return (ir1 > it.ir1 || (ir1 == it.ir1 && p > it.p)); }
		bool operator>=(const this_type& it) const
			{ return (ir1 > it.ir1 || (ir1 == it.ir1 && p >= it.p)); }

	};

	// typedefs for class iterators
	typedef typename types::t_if<typename array::is_writeable,
		iterator_type<false, 0>,
		not_a_type>::type iterator;

	typedef iterator_type<true, 0> const_iterator;

	typedef typename types::t_if<types::t_eq<iterator, not_a_type>,
		const_iterator, iterator>::type best_iterator;

	typedef std::reverse_iterator<iterator> reverse_iterator;

	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

#if 0
	template<int SPC>
	struct s_iterator
	{
		typedef data::catarray_iterator_type<T, best_reference_iterator,
			best_reference_iterator,
			reference_iterator_is_nd::value, false, SPC> type;
	};
	template<int SPC>
	struct const_s_iterator
	{
		typedef data::catarray_iterator_type<T, best_reference_iterator,
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
#endif

	iterator begin()
	{
		return iterator(in1->begin(), in2->begin(), 0,
			catstride1, catstride2, catstride);
	}

	iterator end()
	{
		return iterator(in1->end(), in2->end(), 0,
			catstride1, catstride2, catstride);
	}

	const_iterator begin() const
	{
		return const_iterator(in1->begin(), in2->begin(), 0,
			catstride1, catstride2, catstride);
	}

	const_iterator end() const
	{
		return const_iterator(in1->end(), in2->end(), 0,
			catstride1, catstride2, catstride);
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
		return iter_border_walker(in1->first_to_last(),
			in2->first_to_last(), catstride - 1);
	}

	iter_border_walker begin_to_end()
	{
		return iter_border_walker(in1->begin_to_end(),
			in2->begin_to_end(), catstride);
	}


	using common_base_class::operator[];

	// todo: resolve when b has no random access
	// todo: create a special reference class
	// and specialize for writing
	typename best_iterator::reference operator[](size_t j)
	{
		size_t so = j / catstride;
		size_t o = j % catstride;
		if(o < catstride1)
			return (*in1)[so * catstride1 + o];
		else
			return (*in2)[so * catstride2 + (o - catstride1)];
	}
	typename const_iterator::reference operator[](size_t j) const
	{
		size_t so = j / catstride;
		size_t o = j % catstride;
		if(o < catstride1)
			return (*in1)[so * catstride1 + o];
		else
			return (*in2)[so * catstride2 + (o - catstride1)];
	}


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
	array() { in1 = NULL; }

	array(const array& o) { init(o); }

	// Filler constructor
	array(const size_t) { in1 = NULL; }

	array(A1& a1, A2& a2, catdim_t cd = -1)
	{
		init(a1, a2, cd);
	}


	void setref(A1& a1, A2& a2, catdim_t cd = -1)
	{
		init(a1, a2, cd);
	}

	template <class D>
	bool overlap(const D& d) const
	{
		return in1->overlap(d) || in2->overlap(d);
	}

	template <class D>
	bool self_overlap(const D& d) const
	{
		return d.overlap(*in1) || d.overlap(*in2);
	}

/**/

    //! destructor
	~array() { }

	using common_base_class::operator=;

	this_type& operator=(const array& o)
	{ common_base_class::operator=(o); return *this; }

	template <class J, class P>
	derived_type& assign_array(const array<J, data::empty<P> >& o)
	{
		*in1 = o;
		*in2 = o;
		//copy_or_cut(o); // will always fallback to cut // todo
		return this->derived();
	}

	template<class D>
	derived_type& assign_array(const D& o)
	{
		//copy_or_cut(o); TODO
		static_cast<common_base_class&>(*this).assign_array(o);
		return this->derived();
	}


};


template <class T,
		 class A1,
		 class A2,
		 int CD,
		 class DERIVED_INFO
	     >
void array<T, data::catarray<A1, A2, CD, DERIVED_INFO> >
	::init(const array& o)
{
	in1 = o.in1;
	in2 = o.in2;
	cdim = o.cdim;
	catstride = o.catstride;
	catstride1 = o.catstride1;
	catstride2 = o.catstride2;
	all_len = o.all_len;
}

template <class T,
		 class A1,
		 class A2,
		 int CD,
		 class DERIVED_INFO
	     >
void array<T, data::catarray<A1, A2, CD, DERIVED_INFO> >
	::init(A1& a1, A2& a2, catdim_t cd)
{
	using namespace array_details;

	in1 = &a1;
	in2 = &a2;
	cdim = cd;
	//notice: limits dimensions to 32 bit or native bit int
	catstride1 = (cdim == int(cat_helper::ndims(a1)) - 1) ?
		a1.length() : cat_helper::stride(a1, int(cdim) + 1);
	catstride2 = (cdim == int(cat_helper::ndims(a2)) - 1) ?
		a2.length() : cat_helper::stride(a2, int(cdim) + 1);

	catstride = catstride1 + catstride2;

	all_len = a1.length() + a2.length();
}

#endif
