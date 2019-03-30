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

/* syntax.hpp: a set of utilities used for syntax-rule parsing */

#ifndef IVL_CORE_DETAILS_TYPES_LIST_IMPL_CONSES_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_IMPL_CONSES_HPP

namespace ivl {

namespace types {

namespace scheme {

//TODO: move
struct etc : label<etc> { };
template <> char label <etc>::text[] = "...";

struct onedot : label<onedot> { };
template <> char label <onedot>::text[] = ".";

} // namespace scheme

namespace scheme {

struct unquote : label<unquote> { };
template <> char label <unquote>::text[] = "unquote->";

// TODO: place
template<class T>
struct quote {};

template<class T>
struct srquote {};

} // namespace scheme


namespace lists {

template <class T>
struct run<quote<T> > : public t_id<T> { };

template <class T>
struct run<srquote<T> > : public t_id<T> { };

namespace details {

// NOTE: for debugging
} }  struct lambda;  namespace lists { namespace details {

using scheme::etc;
using scheme::onedot;

typedef node<etc, node<null, null> > dots;

template<class T>
struct dotsy { };

//-----------------------------------------------------------------------------

template <class T>
struct cars : public nat { };

template <>
struct cars <node<null, null> > : public node<null, null> { };

template <class T, class TN, class TR>
struct cars <node <node <T, TN>, TR> > : public
	node <T, typename cars <TR>::type> { };

//-----------------------------------------------------------------------------

template <class T>
struct cdrs : public nat { };

template <>
struct cdrs <node<null, null> > : public node<null, null> { };

template <class T, class TN, class TR>
struct cdrs <node <node <T, TN>, TR> > : public
	node <TN, typename cdrs <TR>::type> { };

//-----------------------------------------------------------------------------

template <class T, class TN>
struct conses : public nat { };

template <>
struct conses <node<null, null>, node<null, null> > : 
	public node<null, null> { };

template <class T, class TR>
struct conses <node <T, TR>, node<null, null> > : public
	node <node <T, node<null, null> >, 
	typename conses <TR, node<null, null> >::type>::type { };

template <class T, class TR, class N, class NN, class NR>
struct conses <node <T, TR>, node <node <N, NN>, NR> > :
	node <node <T, node <N, NN> >, typename conses <TR, NR>::type>::type 
{ };

//-----------------------------------------------------------------------------

template <class T>
struct conses <node <T, dots>, node<null, null> > : 
	node <node <T, node<null, null> >, dots> { };

template <class T, class N, class NN>
struct conses <node <T, dots>, node <node <N, NN>, node<null, null> > > :
	node <node <T, node <N, NN> >, node<null, null> > { };

template <class T, class N, class NN, class NR>
struct conses <node <T, dots>, node <node <N, NN>, NR> > : 
	node <node <T, node <N, NN> >,
	typename conses <node <T, dots>, NR>::type> { };

template <class N, class NN>
struct conses <node<null, null>, node <node <N, NN>, dots> > : 
	node<null, null> { };

template <class T, class TR, class N, class NN>
struct conses <node <T, TR>, node <node <N, NN>, dots> > : 
	node <node <T, node <N, NN> >,
	typename conses <TR, node <node <N, NN>, dots> >::type> { };

template <class T, class N, class NN>
struct conses <node <T, dots>, node <node <N, NN>, dots> > :
	node <node <T, node <N, NN> >, dots> { };

//-----------------------------------------------------------------------------

// all conses for var<T, K>
template <class T, int K>
struct conses <node <var <T, K>, dots>, node<null, null> > :
	node <node <var <T, K>, node<null, null> >, dots> { };

template <class T, int K, class N, class NN>
struct conses <
	node <var <T, K>, dots>, node <node <N, NN>, node<null, null> > > :
	node <node <var <T, K>, node <N, NN> >, node<null, null> > { };

template <class T, int K, class N, class NN, class NR>
struct conses <node <var <T, K>, dots>, node <node <N, NN>, NR> > :
	node <
		node <var <T, K>, node <N, NN> >,
		typename conses <node <var <T, K+1>, dots>, NR>::type
	> { };

template <class N, int K, class NN>
struct conses <node<null, null>, node <node <var <N, K>, NN>, dots> > : 
	node<null, null> { };

template <class T, class TR, class N, int K, class NN>
struct conses <node <T, TR>, node <node <var <N, K>, NN>, dots> > :
	node <
		node <T, node <var <N, K>, NN> >,
		typename conses <TR, node <node <var <N, K+1>, NN>, dots> >
	::type> { };

template <class T, int K, class N, class NN>
struct conses <node <var <T, K>, dots>, node <node <N, NN>, dots> > :
	node <node <var <T, K>, node <N, NN> >, dots> { };

template <class T, class N, int K, class NN>
struct conses <node <T, dots>, node <node <var <N, K>, NN>, dots> > :
	node <node <T, node <var <N, K>, NN> >, dots> { };

template <class T, int J, class N, int K, class NN>
struct conses <node <var <T, J>, dots>, node <node <var <N, K>, NN>, dots> > :
	node <node <var <T, J>, node <var <N, K>, NN> >, dots> { };

//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// copy of all above rules for dotsy
template <class T>
struct conses <node <dotsy<T>, node<null, null> >, node<null, null> > : 
	node <dotsy<node <T, node<null, null> > >, node<null, null> > { };

template <class T, class N, class NN>
struct conses <node <dotsy<T>, node<null, null> >, node <node <N, NN>, node<null, null> > > :
	node <node <T, node <N, NN> >, node<null, null> > { };

template <class T, class N, class NN, class NR>
struct conses <node <dotsy<T>, node<null, null> >, node <node <N, NN>, NR> > : 
	node <node <T, node <N, NN> >,
	typename conses <node <dotsy<T>, node<null, null> >, NR>::type> { };

template <class N, class NN>
struct conses <node<null, null>, node <dotsy<node <N, NN> >, node<null, null> > > : 
	node<null, null> { };

template <class T, class TR, class N, class NN>
struct conses <node <T, TR>, node <dotsy<node <N, NN> >, node<null, null> > > : 
	node <node <T, node <N, NN> >,
	typename conses <TR, node <dotsy<node <N, NN> >, node<null, null> > >::type> { };

template <class T, class N, class NN>
struct conses <node <dotsy<T>, node<null, null> >, node <dotsy<node <N, NN> >, node<null, null> > > :
	node <node <T, dotsy<node <N, NN> > >, node<null, null> > { };

//-----------------------------------------------------------------------------

// all conses for var<T, K>, copy for dotsy
template <class T, int K>
struct conses <node <dotsy<var <T, K> >, node<null, null> >, node<null, null> > :
	node <dotsy<node <var <T, K>, node<null, null> > >, node<null, null> > { };

template <class T, int K, class N, class NN>
struct conses <
	node <dotsy<var <T, K> >, node<null, null> >, node <node <N, NN>, node<null, null> > > :
	node <node <var <T, K>, node <N, NN> >, node<null, null> > { };

template <class T, int K, class N, class NN, class NR>
struct conses <node <dotsy<var <T, K> >, node<null, null> >, node <node <N, NN>, NR> > :
	node <
		node <var <T, K>, node <N, NN> >,
		typename conses <node <dotsy<var <T, K+1> >, node<null, null> >, NR>::type
	> { };

template <class N, int K, class NN>
struct conses <node<null, null>, node <dotsy<node <var <N, K>, NN> >, node<null, null> > > : 
	node<null, null> { };

template <class T, class TR, class N, int K, class NN>
struct conses <node <T, TR>, node <dotsy<node <var <N, K>, NN> >, node<null, null> > > :
	node <
		node <T, node <var <N, K>, NN> >,
		typename conses <TR, node <dotsy<node <var <N, K+1>, NN> >, node<null, null> > >
	::type> { };

template <class T, int K, class N, class NN>
struct conses <node <dotsy<var <T, K> >, node<null, null> >, node <dotsy<node <N, NN> >, node<null, null> > > :
	node <dotsy<node <var <T, K>, node <N, NN> > >, node<null, null> > { };

template <class T, class N, int K, class NN>
struct conses <node <dotsy<T>, node<null, null> >, node <dotsy<node <var <N, K>, NN> >, node<null, null> > > :
	node <dotsy<node <T, node <var <N, K>, NN> > >, node<null, null> > { };

template <class T, int J, class N, int K, class NN>
struct conses <node <dotsy<var <T, J> >, node<null, null> >, node <dotsy<node <var <N, K>, NN> >, node<null, null> > > :
	node <dotsy<node <var <T, J>, node <var <N, K>, NN> > >, node<null, null> > { };
//-----------------------------------------------------------------------------


// identifier detection

//struct identifier_id { };

template <typename T, typename THEN, typename ELSE>
struct if_identifier : t_if<is_base<scheme::identifier_id, T>, THEN, ELSE> { };

template <class T>
struct is_identifier : if_identifier<T, t_true, t_false> { };

template <class T, int K>
struct is_identifier<var<T, K> > : t_id<t_true> { };

template <typename T>
struct set_var : if_identifier <T, var <T>, t_id <T> >::type { };

template <typename T>
struct detect_var : t_id <T> { };

template <typename T>
struct detect_var <node <T, dots> > :
	node <typename set_var <T>::type, dots> { };

// ?? needed
template <class T>
struct detect_var <node <dotsy<T>, node<null, null> > > :
	node <dotsy<typename set_var <T>::type>, node<null, null> > { };
	
//-----------------------------------------------------------------------------
	
//-----------------------------------------------------------------------------

template<class V, class T>
struct conses2_1 : t_id<T> { };

template<class V, class T, class TD, class TS>
struct conses2_1<V, node<node<T, TD>, TS> > : 
	node<node<V, node<T, TD> >, TS> { };
	
template<class V, class T>
struct conses2 : nat { };

template<class V, class T, class TS>
struct conses2<V, node<T, TS> > : 
	node<typename conses2_1<V, T>::type, typename conses2<V, TS>::type> { };

template<class V>
struct conses2<V, node<null, null> > : node<null, null> { };


//-----------------------------------------------------------------------------

template<class T>
struct cars2_1 : nat { };

template<class T, class TD, class TS>
struct cars2_1<node<node<T, TD>, TS> > : node<T, TD> { };

template<class T, class TS>
struct cars2_0 : node<T, TS> { };

template<class TS>
struct cars2_0<nat, TS> : t_id<TS> { };

template<class T>
struct cars2 : nat { };

template<>
struct cars2<node<null, null> > : node<null, null> { };

template<class T, class TS>
struct cars2<node<T, TS> > :
	cars2_0<typename cars2_1<T>::type, typename cars2<TS>::type> { };

//-----------------------------------------------------------------------------
/*
template<class T, class TS>
struct keys2_0 : node<T, TS> { };

template<class TS>
struct keys2_0<nat, TS> : t_id<TS> { };

template<class T>
struct keys2_2 : t_id<T> { };

template<>
struct keys2_2<null> : nat { };

template<class T, class TS>
struct keys2_2<node<T, TS> > :
	keys2_0<typename keys2_2<T>::type, typename keys2_2<TS>::type> { };
	
template<class T>
struct keys2_1 : nat { };

template<class T, class TD, class TS>
struct keys2_1<node<node<T, TD>, TS> > : keys2_2<node<T, TD> > { };

template<class T>
struct keys2 : nat { };

template<>
struct keys2<node<null, null> > : node<null, null> { };

template<class T, class TS>
struct keys2<node<T, TS> > :
	keys2_0<typename keys2_1<T>::type, typename keys2<TS>::type> { };
*/	
//-----------------------------------------------------------------------------
	
	
} // namespace details

} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LIST_IMPL_CONSES_HPP
