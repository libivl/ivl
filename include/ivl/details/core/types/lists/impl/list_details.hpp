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

/*
list_details.hpp: completion of list.hpp.
*/

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_DETAILS_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_DETAILS_HPP

namespace ivl {

namespace types {
namespace scheme {
struct syntax_rules : scheme::keyword<syntax_rules> { };
template <> char scheme::label <syntax_rules>::text[] = "syntax-rules";

} // namespace scheme

//-----------------------------------------------------------------------------

namespace lists {

//-----------------------------------------------------------------------------

// convertion from lists or _'s to nodes

template<class L>
struct prefnode 
{
	typedef typename t_if<t_eq<typename reqnode<L>::type, nat>, 
		t_id<L>, reqnode<L> >::type::type type;
};

//-----------------------------------------------------------------------------

// conversion from lists or _'s to node< >, and to 1 level node<node< >, ...>

namespace details {

template<class T> 
struct prefnode_2_0 : t_id<T> { };

template<class T, class S> 
struct prefnode_2_0<node<T, S> > : node<typename prefnode<T>::type, S> { };

} // namespace details

template<class L>
struct prefnode_2 : details::prefnode_2_0<typename prefnode<L>::type> { };

//-----------------------------------------------------------------------------

// convertion (recursive) from lists or _'s to nodes
// model

namespace details {

template <class L>
struct model1 : t_id<L> { };

template <class L>
struct model0 : model1<typename prefnode<L>::type> { };

template <class T1, class T2>
struct model1<node<T1, T2> > : 
	node<typename model0<T1>::type, typename model0<T2>::type> { };

} // namespace details

template<class L>
struct model : details::model0<L> { };


//-----------------------------------------------------------------------------

// disp

template <class W> 
struct disp_word { };

namespace details {

template <class IS_TOKN, class L, class L0>
struct disp1 : t_id<typename L0::word> { };

template <class L, class L0>
struct disp1<t_false, L, L0> : t_id<L> { };

template <class L>
struct disp0 : disp1<typename is_base<scheme::word_id, L>::type,	
	typename prefnode<L>::type, L> { };

template <class T1, class T2, class L0>
struct disp1<t_false, node<T1, T2>, L0> : node<
	typename disp0<T1>::type, typename disp0<T2>::type> { };

} // namespace details

template<class L>
struct disp : details::disp0<L> { };

//-----------------------------------------------------------------------------

// implementation of get_node_index

namespace details {

template<int J> 
struct get_node_index<J, null> : public nat { };

template<class T1, class T2> 
struct get_node_index<0, node<T1, T2> > : public nat { };

template<class T1, class T2> 
struct get_node_index<1, node<T1, T2> > : public t_id<T1> { };

template<int J, class T1, class T2> 
struct get_node_index<J, node<T1, T2> > : public get_node_index<J - 1, T2> { };

template<int J> 
struct get_node_index<J, node<null, null> > : public nat { };

template<> 
struct get_node_index<1, node<null, null> > : public nat { };

template<> 
struct get_node_index<0, node<null, null> > : public nat { };

} // namespace details

//-----------------------------------------------------------------------------

} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_DETAILS_HPP
