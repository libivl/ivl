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

#ifndef IVL_ARRAY_DETAILS_ROW_FUNC_HPP
#define IVL_ARRAY_DETAILS_ROW_FUNC_HPP

namespace ivl {
namespace row_func_details {


template<bool enable_idx = false>
class index_count
{
public:
	index_count() { }

	inline void next();

	template<class F, class S>
	inline
	void elem_op(const F& f, const S& val)
	{
		F.elem_op(val);
	}
};

template<>
class index_count<true>
{
	size_t idx;

public:
	index_count() { idx = 0; }

	inline void next() { idx++; }

	template<class F, class S>
	inline
	void elem_op(const F& f, const S& val)
	{
		F.elem_op(val, idx);
	}
};


template<bool IDX>
struct first_elem_first
{
	template<class F, class S, class N, class K>
	static
	typename types::get_templ_arg<2, F>::type loop(const array<S, N, K>& a)
	{
		typename array<S, N, K>::const_iterator cit = a.begin();
		typename array<S, N, K>::const_iterator eit = a.end();

		F func(*cit);
		index_count<IDX> idx;

		for(++cit; cit != eit; ++cit) {
			idx.next();
			idx.elem_op(func, *cit);
		}

		return func.result();
	}


};

template<bool IDX>
struct length_first
{
	template<class F, class S, class N, class K>
	static
	typename types::get_templ_arg<2, F>::type loop(const array<S, N, K>& a)
	{
		typename array<S, N, K>::const_iterator cit = a.begin();
		typename array<S, N, K>::const_iterator eit = a.end();

		F func(a.length());
		index_count<IDX> idx;

		for(++cit; cit != eit; ++cit) {
			idx.elem_op(func, *cit);
			idx.next();
		}

		return func.result();
	}
};

// elem_row_class for max 4 lvalue args
template<template<typename, typename> class F, class S, class O1,
class O2 = types::term, class O3 = types::term, class O4 = types::term>
class elem_row_class
{
public:
	typedef O1 elem_type;

	template<class D, class P>
	static
	inline
	O1 calculate(const array<S, D, P>& in)
	{
		typedef F<S, O1> functype;
		typedef typename functype::behavior behavior;
		return behavior::loop<functype>(in);
	}

	template<class D, class P>
	static
	inline
	void calculate(const array<S, D, P>& in, O1& o1, O2& o2)
	{
		typedef F<S, tuple<O1, O2> > functype;
		typedef typename functype::behavior behavior;
		behavior::loop<functype>(in).get(o1, o2);
	}

	template<class D, class P>
	static
	inline
	void calculate(const array<S, D, P>& in, O1& o1, O2& o2, O3& o3)
	{
		typedef F<S, tuple<O1, O2, O3> > functype;
		typedef typename functype::behavior behavior;
		behavior::loop<functype>(in).get(o1, o2, o3);
	}

	template<class D, class P>
	static
	inline
	void calculate(const array<S, D, P>& in, O1& o1, O2& o2, O3& o3, O4& o4)
	{
		typedef F<S, tuple<O1, O2, O3, O4> > functype;
		typedef typename functype::behavior behavior;
		behavior::loop<functype>(in).get(o1, o2, o3, o4);
	}
};

template<class F, class A>
class row_array_type
{
};

template<class F, class T, class D, class P>
class row_array_type<F, array<T, D, P> >
//: public types::class_type<typename F::elem_type>
{
public:
	typedef typename F::elem_type elem_type;
	typedef typename A::elem_type eval_type;

	static
	inline
	elem_type calculate(const array<T, D, P>& a)
	{
		return F::calculate(a);
	}

	static
	inline
	elem_type produce(const array<T, D, P>& a)
	{
		return calculate(a);
	}

};


template<class F, class T, class D, class P>
class row_array_type<F, array_2d<T, D, P> >
:
public array_2d<typename F::elem_type,
	data::row_elem_func_2d_data_id<F, array_2d<T, D, P> >, types::term>,
public rvalue_base<row_array_type<F, array_2d<T, D, P>
{
public:
	typedef row_array_type eval_type;
	static inline tuple<const array_2d<T, D, P>&, size_t dim>
		produce(const array<T, D, P>&a, size_t dim)
			{ return tpl(a,dim);}

	// this class is initialized with set_input, and not with constructor.
	// the reason is to simplify (make smaller) the code
	// in each row_function specialization [TODO: subject to debate]
	row_array_type() { }

	template
	<class L1, class M1, class N1,
	class L2, class M2, class N2>
	void output(
		const array_2d<L1, M1, N1>& o1,
		const array_2d<L2, M2, N2>& o2)
	{
		size_t len = this->length();
		size_t row = in_dim == 0 ? 1 : len;
		size_t col = in_dim == 1 ? 1 : len;
		o1.resize(row, col);
		o2.resize(row, col);

		return loops::row_func_2d_output<F>(in, in_dim, o1, o2);
	}

	template
	<class L1, class M1, class N1,
	class L2, class M2, class N2,
	class L3, class M3, class N3>
	void output(
		const array_2d<L1, M1, N1>& o1,
		const array_2d<L2, M2, N2>& o2,
		const array_2d<L3, M3, N3>& o3)
	{
		size_t len = this->length();
		size_t row = in_dim == 0 ? 1 : len;
		size_t col = in_dim == 1 ? 1 : len;
		o1.resize(row, col);
		o2.resize(row, col);
		o3.resize(row, col);

		return loops::row_func_2d_output<F>(in, in_dim, o1, o2, o3);
	}

	template
	<class L1, class M1, class N1,
	class L2, class M2, class N2,
	class L3, class M3, class N3,
	class L4, class M4, class N4>
	void output(
		const array_2d<L1, M1, N1>& o1,
		const array_2d<L2, M2, N2>& o2,
		const array_2d<L3, M3, N3>& o3,
		const array_2d<L4, M4, N4>& o4)
	{
		size_t len = this->length();
		size_t row = in_dim == 0 ? 1 : len;
		size_t col = in_dim == 1 ? 1 : len;
		o1.resize(row, col);
		o2.resize(row, col);
		o3.resize(row, col);
		o4.resize(row, col);

		return loops::row_func_2d_output<F>(in, in_dim, o1, o2, o3, o4);
	}

};



template<class F, class T, class D, class P>
class row_array_type<F, array_nd<T, D, P> >
:
public array_nd<typename F::elem_type,
	data::row_elem_func_nd_data_id<F, array_nd<T, D, P> >, types::term>,
public rvalue<row_array_type<F, array_nd<T, D, P>
{
public:
	typedef row_array_type eval_type;

	// this class is initialized with set_input, and not with constructor.
	// the reason is to simplify (make smaller) the code
	// in each row_function specialization [TODO: subject to debate]
	row_array_type() { }

	template
	<class L1, class M1, class N1,
	class L2, class M2, class N2>
	void output(
		const array_nd<L1, M1, N1>& o1,
		const array_nd<L2, M2, N2>& o2)
	{
		return loops::row_func_nd_output<F>(in, in_dim,
			this->in_dims, this->size_nd(), o1, o2);
	}

	template
	<class L1, class M1, class N1,
	class L2, class M2, class N2,
	class L3, class M3, class N3>
	void output(
		const array_nd<L1, M1, N1>& o1,
		const array_nd<L2, M2, N2>& o2,
		const array_nd<L3, M3, N3>& o3)
	{
		return loops::row_func_nd_output<F>(in, in_dim,
			this->in_dims, this->size_nd(), o1, o2, o3);
	}

	template
	<class L1, class M1, class N1,
	class L2, class M2, class N2,
	class L3, class M3, class N3,
	class L4, class M4, class N4>
	void output(
		const array_nd<L1, M1, N1>& o1,
		const array_nd<L2, M2, N2>& o2,
		const array_nd<L3, M3, N3>& o3,
		const array_nd<L4, M4, N4>& o4)
	{
		return loops::row_func_nd_output<F>(in, in_dim,
			this->in_dims, this->size_nd(), o1, o2, o3, o4);
	}

};

} /* namespace row_func_details */
} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_ROW_FUNC_HPP
