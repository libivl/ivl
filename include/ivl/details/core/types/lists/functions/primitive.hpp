/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the nulls of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the nulls
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_CORE_DETAILS_TYPES_LIST_PRIMITIVE_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_PRIMITIVE_HPP

namespace ivl {

namespace types {

namespace scheme {


// basic list macros

//-----------------------------------------------------------------------------

// car
typedef t1<l_car> car;
template <> char label <car>::text[] = "car";

//-----------------------------------------------------------------------------

// cdr
typedef t1<l_cdr> cdr;
template <> char label <cdr>::text[] = "cdr";

//-----------------------------------------------------------------------------

// cons
typedef t2<l_cons> cons;
template <> char label <cons>::text[] = "cons";

//-----------------------------------------------------------------------------

// atom

namespace details {

template <class T>
struct t_atom : public t_true { };

template <class T1, class T2>
struct t_atom<node<T1, T2> > : public t_false { };

} // namespace details

typedef t1<details::t_atom> atom;
template <> char label <atom>::text[] = "atom";

//-----------------------------------------------------------------------------

// null (uses a specialization of run)

using ivl::types::null;

namespace details {

template<class T>
struct isnull0 : public nat { };

template<class T1, class T2, class S>
struct isnull0<node<node<T1, T2>, S> > : public t_false { };

template<class S>
struct isnull0<node<node<null, null>, S> > : public t_true { };

} // namespace details

} // namespace scheme
namespace lists {

template<class T>
struct run<node<null, T> > 
: public scheme::details::isnull0<typename run<T>::type>::type { };

} // namespace lists
namespace scheme {

template <> char label <null>::text[] = "null?";


//-----------------------------------------------------------------------------

// eq

namespace details {

template <class T1, class T2>
struct eq_tp : public t_eq<T1, T2> { };

template <class T1, class T2, class T3, class T4>
struct eq_tp<node<T1, T2>, node<T3, T4> > : public nat { };

template <class T1, class T2, class T>
struct eq_tp<node<T1, T2>, T> : public nat { };

template <class T1, class T2, class T>
struct eq_tp<T, node<T1, T2> > : public nat { };

} // details

typedef t2<details::eq_tp> eq;
template <> char label <eq>::text[] = "eq?";

//-----------------------------------------------------------------------------

// size

namespace details {

template<class T>
struct list_size
	: public lists::seq<number<0>, lzm1<number<1> >::map, t_add, T> {
	typedef typename list_size<T>::type n;
	static const int value = n::value;
};

} // namespace details

typedef t1<details::list_size> size;
template <> char label <size>::text[] = "size?";

//-----------------------------------------------------------------------------

typedef t2<l_concat> concat;
template <> char label <concat>::text[] = "concat";

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// special type macros

//-----------------------------------------------------------------------------

// tev

namespace details {

template <class T1, class T2>
struct tev_t : public lazy<T1>::template eval<T2> { };

} // namespace details

typedef t2<details::tev_t> tev;
template <> char label <tev>::text[] = "tev";

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

// numeric macros

//-----------------------------------------------------------------------------
/*
template <class T1, class T2>
struct rem_tp : public nat { };

template <int M, int N>
struct rem_tp<number<M>, number<N> > : public number<(M%N)> { };

template <int M>
struct rem_tp<number<M>, number<0> > : public nat { };

typedef t2<rem_tp> rem;
*/
//-----------------------------------------------------------------------------

template <class T1, class T2>
struct quot_tp : public nat { };

template <int M, int N>
struct quot_tp<number<M>, number<N> > : public number<(M/N)> { };

template <int M>
struct quot_tp<number<M>, number<0> > : public nat { };

typedef t2<quot_tp> quot;

//-----------------------------------------------------------------------------

template <class T1, class T2>
struct add_tp : public nat { };

template <int M, int N>
struct add_tp<number<M>, number<N> > : public number<(M+N)> { };

typedef t2<add_tp> add;

//-----------------------------------------------------------------------------

template <class T1, class T2>
struct sub_tp : public nat { };

template <int M, int N>
struct sub_tp<number<M>, number<N> > : public number<(M-N)> { };

typedef t2<sub_tp> sub;

//-----------------------------------------------------------------------------

template <class T1, class T2>
struct mul_tp : public nat { };

template <int M, int N>
struct mul_tp<number<M>, number<N> > : public number<(M*N)> { };

typedef t2<mul_tp> mul;

//-----------------------------------------------------------------------------

template <class T1, class T2>
struct lt_tp : public nat { };

template <int M, int N>
struct lt_tp<number<M>, number<N> > : public t_expr<(M<N)> { };

typedef t2<lt_tp> lt;

//-----------------------------------------------------------------------------

template <class T1>
struct num_tp : public t_false { };

template <int M>
struct num_tp<number<M> > : public t_true { };

template <>
struct num_tp<nat> : public nat { };

typedef t1<num_tp> num;

//-----------------------------------------------------------------------------


} // namespace scheme

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LIST_PRIMITIVE_HPP
