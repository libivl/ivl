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
lists/impl/seq.hpp: The seq function for lists.
*/

#ifndef IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_SEQ_HPP
#define IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_SEQ_HPP

namespace ivl {

namespace types {

namespace lists {
//-----------------------------------------------------------------------------

// list seq

namespace details {

template<class T1, class T2> struct tf : public t_false { };
template<class T1, class T2> struct nrc { };

} // namespace details

// (insane) list seq

// model application: NODE<ATOM<T1>, NODE<ATOM<T2>, .. >>>
// recursive application: checks REC<T1, T2> as flag to recurse into
// flag can be cancelled from the left to the right of the list
// checks I<T1, T2> and returns node<T1, T2> on success.
// when I = [default value]details::nrc, I becomes 'not<REC>'

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, class E, 
	template <typename, typename> class REC = details::tf, 
	template <typename, typename> class I = details::nrc>
struct seq : public ATOM<E> { };

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, 
	template <typename, typename> class REC, 
	template <typename, typename> class I>
struct seq<NULLV, ATOM, NODE, nat, REC, I> : public nat { };

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE,
	template <typename, typename> class REC, 
	template <typename, typename> class I>
struct seq<NULLV, ATOM, NODE, node<null, null>, REC, I> 
	: public t_id<NULLV> { };

namespace details {

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, 
	class T1, class T2, 
	template <typename, typename> class REC, 
	template <typename, typename> class I,
	class RV, class IV>
struct seq0 : public nat { };

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, 
	class T1, class T2, 
	template <typename, typename> class REC, 
	template <typename, typename> class I, class RV>
struct seq0 <NULLV, ATOM, NODE, T1, T2, REC, I, RV, t_true> 
	: public t_id<node<T1, T2> > { };

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, 
	class T1, class T2, 
	template <typename, typename> class REC, 
	template <typename, typename> class I>
struct seq0 <NULLV, ATOM, NODE, T1, T2, REC, I, t_false, t_false> 
	: public NODE<typename ATOM<T1>::type, 
		typename seq<NULLV, ATOM, NODE, T2, 
			details::tf, details::tf>::type> { };

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, 
	class T1, class T2, 
	template <typename, typename> class REC, 
	template <typename, typename> class I>
struct seq0 <NULLV, ATOM, NODE, T1, T2, REC, I, t_true, t_false> 
	: public NODE<
		typename seq<NULLV, ATOM, NODE, T1, REC, I>::type,
		typename seq<NULLV, ATOM, NODE, T2, REC, I>::type> { };

		
template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, class T1, class T2, 
	template <typename, typename> class REC, 
	template <typename, typename> class I>
struct seq1 : public details::seq0<NULLV, ATOM, NODE, T1, T2, REC, I,
		typename REC<T1, T2>::type, 
		typename I<T1, T2>::type> { };

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, class T1, class T2, 
	template <typename, typename> class REC>
struct seq1<NULLV, ATOM, NODE, T1, T2, REC, details::nrc> 
	: public details::seq0<NULLV, ATOM, NODE, T1, T2, REC, details::nrc,
		typename REC<T1, T2>::type, 
		typename t_not<typename REC<T1, T2>::type>::type> { };
		
template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, class T1, class T2>
struct seq1<NULLV, ATOM, NODE, T1, T2, details::tf, details::nrc>
	: public details::seq0<NULLV, ATOM, NODE, T1, T2, 
		details::tf, details::tf, t_false, t_false> { };
		
} // namespace details

template<class NULLV, template <typename> class ATOM,
	template <typename, typename> class NODE, class T1, class T2, 
	template <typename, typename> class REC, 
	template <typename, typename> class I>
struct seq<NULLV, ATOM, NODE, node<T1, T2>, REC, I>
	: public details::seq1<NULLV, ATOM, NODE, T1, T2, REC, I> { };	

//-----------------------------------------------------------------------------

template <template <typename> class F, class E, 
	template <typename, typename> class RC = details::tf, 
	template <typename, typename> class IC = details::tf>
struct map : public seq <node<null, null>, F, node, E, RC, IC> { };

template <template <typename, typename> class F, class DEFAULT, class E, 
	template <typename, typename> class RC = details::tf, 
	template <typename, typename> class IC = details::tf>
struct reduce : public seq <DEFAULT, t_id, F, E, RC, IC> { };

//-----------------------------------------------------------------------------

template <class NULVAL, class ATOM, class NODE, class E, class REC = t_false, 
	class IC = t_false>
struct lzseq 
	: public seq < NULVAL, 
		lzm1<ATOM>::template map, 
		lzm2<NODE>::template map, E, 
		lzm2<REC>::template map, 
		lzm2<IC>::template map> {};
		
template <class NULVAL, class ATOM, class NODE, class E, class REC>
struct lzseq<NULVAL, ATOM, NODE, E, REC, t_true>
	: public seq < NULVAL, 
		lzm1<ATOM>::template map, 
		lzm2<NODE>::template map, E, 
		lzm2<REC>::template map, 
		details::nrc> {};

template <class MAP, typename L, class RC = t_false, class IC = t_false>
struct lzmap : 
	public lzseq <node<null, null>, MAP, node<__1, __2>, L, RC, IC> { };

template <class F, class DEFAULT, class L, 
	class RC = t_false, class IC = t_false>
struct lzreduce : public lzseq <DEFAULT, __1, F, L, RC, IC> { };

//-----------------------------------------------------------------------------

} // namespace lists

} // namespace types

} // namespace ivl

#endif // IVL_CORE_DETAILS_TYPES_LISTS_IMPL_LIST_SEQ_HPP
