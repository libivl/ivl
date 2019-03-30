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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_COND_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_COND_HPP

namespace ivl {

namespace types {

namespace scheme {


//-----------------------------------------------------------------------------

// cond

namespace details {

template <class HAS_TYPE, class T>
struct eval_valid0 { typedef nat type; };

template <class T>
struct eval_valid0<t_true, T> { typedef typename T::type type; };

template <class T>
struct eval_valid : public eval_valid0<
	typename has_typedef_type<T>::type, T> { };

template <class T>
struct eval_valid_logic
{
	typedef typename eval_valid<T>::type t1;
	typedef typename t_if<t_eq<t1, t_true>, t_true, t_false>::type type;
};

template <class L>
struct t_cond : public nat { };

template <>
struct t_cond <node <null, null> > : public nat { };

template <class E, class R, class S>
struct t_cond1 : public nat { };

template <class R, class S>
struct t_cond1<t_true, R, S> : lists::eval<typename R::val> { };

template <class R, class S>
struct t_cond1<t_false, R, S> : t_cond<typename lists::prefnode_2<S>::type> { };

template <class E1, class E2, class S>
struct t_cond <node<node <E1, E2>, S> > :
	public t_cond1<typename details::eval_valid<
		typename lists::eval<E1>::type>::type, E2, S> { };

template <class L>
struct t_cond_main : t_cond<typename lists::prefnode_2<L>::type> { };

} // namespace details

struct cond : tv<details::t_cond_main>, lists::lazy_args_id, 
	scheme::keyword<cond> { };
template <> char label <cond>::text[] = "cond";

//-----------------------------------------------------------------------------

} // namespace scheme

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LIST_COND_HPP
