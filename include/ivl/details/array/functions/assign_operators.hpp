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

#ifndef IVL_ARRAY_FUNCTIONS_DETAILS_ASSIGN_OPERATORS_HPP
#define IVL_ARRAY_FUNCTIONS_DETAILS_ASSIGN_OPERATORS_HPP

namespace ivl {
/*
template <class T, class S, class K, class J, class D, class P>
typename array<T, S, K>::derived_type operator*=(
	array<T, S, K>& l, const array<J, D, P>& r)
{
	loops::loop<loops::assign_times_class<T, J> >(l.derived(), r.derived());
	return l.derived();
}

template <class T, class S, class K>
typename array<T, S, K>::derived_type operator*=(
	array<T, S, K>& l, const T& r)
{
	typename array_details::scalar_to_array<T, array<T, S, K> >::
		type v(l.derived().size(), r);
	loops::loop<loops::assign_times_class<T, T> >(l.derived(), v);
	return l.derived();
}

#define HELPA(OP, CLAS) \
template <class T, class S, class K, class J, class D, class P> \
typename array<T, S, K>::derived_type OP( \
	array<T, S, K>& l, const array<J, D, P>& r) \
{ \
	loops::loop<loops::CLAS<T, J> >(l.derived(), r.derived()); \
	return l.derived(); \
}\
\
template <class T, class S, class K> \
typename array<T, S, K>::derived_type OP( \
	array<T, S, K>& l, const T& r) \
{ \
	typename array_details::scalar_to_array<T, array<T, S, K> >:: \
		type v(l.derived().size(), r); \
	loops::loop<loops::CLAS<T, T> >(l.derived(), v); \
	return l.derived(); \
} \

//todo: some ops need to be defined for some special types
//when operating with scalar, e.g. int for %
//the plan is to define for a few types, e.g. float, double,
//long long, int, and char and also T but automatically disable the
//T specialization if T in the pre-defined types, so that
//we avoid the already defined error. for now
// we leave only the vs T element which is inadequate.


HELPA(operator/=, assign_divide_class)
//HELPA(operator+=, assign_plus_class)
HELPA(operator-=, assign_minus_class)
HELPA(operator%=, assign_mod_class)

HELPA(operator|=, assign_bitor_class)
HELPA(operator&=, assign_bitand_class)
HELPA(operator^=, assign_bitxor_class)

HELPA(operator>>=, assign_bitrshift_class)
HELPA(operator<<=, assign_bitlshift_class)






template <class T, class S, class K, class J, class D, class P>
typename array<T, S, K>::derived_type operator+=(
	array<T, S, K>& l, const array<J, D, P>& r)
{
	loops::loop<loops::assign_plus_class<T, J> >(l.derived(), r.derived());
	return l.derived();
}

template <class T, class S, class K>
typename array<T, S, K>::derived_type operator+=(
	array<T, S, K>& l, const T& r)
{
	typename array_details::scalar_to_array<T, array<T, S, K> >::
		type v(l.derived().size(), r);
	loops::loop<loops::assign_plus_class<T, T> >(l.derived(), v);
	return l.derived();
}




*/

// need to make unary loops too. for -- ++.


} /* namespace ivl */

#endif // IVL_ARRAY_FUNCTIONS_DETAILS_ASSIGN_OPERATORS_HPP
