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

#ifndef IVL_ARRAY_DETAILS_ROW_FUNCTIONS_HPP
#define IVL_ARRAY_DETAILS_ROW_FUNCTIONS_HPP


namespace ivl {

template<class S, class T>
class mean_elem_class
{
	typename types::promote<S>::type sum;
	size_t len;

public:
	typedef row_func_details::length_first<false> behavior;

	inline
	mean_class(size_t len) : sum(S()), len(len) { }

	inline
	void elem_op(const S& elem) { sum += elem; }

	inline
	T result() { return T(sum / double(len)); }
};


template<class T, class S, class K>
typename row_array_type<
	row_func_details::elem_row_class<mean_elem_class, T,
	types::to_floating<T>::type>::eval_type
		mean(const array<T, S, K>& a, size_t dim = 1)
{
	return row_array_type<
	row_func_details::elem_row_class<mean_elem_class, T,
	types::to_floating<T>::type>::produce(a, dim);
}
	/*
array<T, S, K>, mean_elem_class,
	types::to_floating<T>::type>::eval_type
		mean(cost array<T, S, K>& a, size_t dim = 1)
{
	return row_array_type<array<T, S, K>, mean_elem_class,
	types::to_floating<T>::type>::produce(a, dim);
}
*/

#if 0

	row_func_details::elem_row_class<mean_elem_class, S,
	typename types::to_floating<S>::type>

template<class A, class S>
class mean_class :
public row_array_type<
	row_func_details::elem_row_class<mean_elem_class, S,
	typename types::to_floating<S>::type>, A>
{
public:
	mean_class(tuple<A, size_t> p) { init_input(p); }
};

// function declarations for array, array_nd and array_2d
template<class T, class S, class K>
typename mean_class<array<T, S, K>, T>::elem_type mean(
	const array<T, S, K>& a)
{
	return mean_class<array<T, S, K>, T>::calculate(a);
}

template<class T, class S, class K>
mean_class<array_nd<T, S, K>, T> mean(
	const array_nd<T, S, K>& a, size_t dim = 1)
{
	return tpl(ref(a), dim);
}

template<class T, class S, class K>
mean_class<array_2d<T, S, K>, T> mean(
	const array_2d<T, S, K>& a, size_t dim = 1)
{
	return tpl(ref(a), dim);
}


#endif

// --------------------------------------------------------

template<class S, class T>
class min_elem_class
{
private:
	T best;

public:
	typedef row_func_details::first_elem_first<false> behavior;

	inline
	min_class(const T& i) : best(i) { }

	inline
	void elem_op(const S& elem) { if(elem < best) best = elem; };

	inline
	T result() { return best; }
};

template<class S, class T, class I>
class min_elem_class<S, tuple<T, I> >
{
private:
	T best;
	I best_idx;

public:
	typedef row_func_details::first_elem_first<true> behavior;

	inline
	min_class(const T& i) : best(i), best_idx(0) { }

	inline
	void elem_op(const S& elem, I index)
	{
		if(elem < best) { best = elem; best_idx = index; }
	};

	inline
	tuple<T, I> result() { return tpl(best, best_idx); }
};


template<class A, class S>
class min_class :
public row_array_type<
	row_func_details::elem_row_class<mean_elem_class, S, S, A>
{
public:
	min_class(tuple<A, size_t> p) { init_input(p); }
};

// function declarations for array, array_nd and array_2d
template<class T, class S, class K>
mean_class<array<T, S, K>, T> mean(const array<T, S, K>& a)
{
	return tpl(a, 1);
}

template<class T, class S, class K>
mean_class<array_nd<T, S, K>, T> mean(
	const array_nd<T, S, K>& a, size_t dim = 1)
{
	return tpl(a, dim);
}

template<class T, class S, class K>
mean_class<array_2d<T, S, K>, T> mean(
	const array_2d<T, S, K>& a, size_t dim = 1)
{
	return tpl(a, dim);
}




//template<class S, class T>
//class min_row_class : public elem_row_class<min_elem_class, S, T, size_t>
//{
//
//};

template<class IN>
class min_class : public
	row_array_type<IN, elem_row_class<IN::elem_type, min_elem_class


template<class T, class S, class K>
class min_class : public row_array_type<T, S, K, min_class>
{
private:
	const array<T, S, K>& in;

public:

	template<class L, class F>
	void output(array<T, L, F>& e) const;

	// [v,i] = min(...
	template<class L, class F, class M, class N>
	void output(array<T, L, F>& v,
		array<size_t, M, N>& d) const;


};

// single type
typename row_array_type<T, S, K, min_class>::type min(const array<T, S, K>& a)
{
}

rvalue_default<typename row_array_type<T, S, K, min_class>::type>,  >




//
typename row_




} /* namespace ivl */


#endif // IVL_ARRAY_DETAILS_ROW_FUNCTIONS_HPP
