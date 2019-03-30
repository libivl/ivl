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

#ifndef IVL_CORE_DETAILS_DATA_BASE_HPP
#define IVL_CORE_DETAILS_DATA_BASE_HPP

#include <iostream>

namespace ivl {

namespace data {

template <class DATA_CLASS>
struct get_image_channels
{
	typedef types::number<0> type;
};

} /* namespace data */

/*
use<array>
use_1t<arrayx>

use<CC>
CC<a,use<array>
*/
namespace data {
/*
template <class DATA_ID, class PARAMS>
struct array_traits { };

template <
	class X1 = types::term,
	class X2 = types::term,
	class X3 = types::term,
	class X4 = types::term,
	class X5 = types::term,
	class X6 = types::term,
	class X7 = types::term,
	class X8 = types::term,
	class X9 = types::term>
class params { };

template <
	class DATA_IDENTIFIER,
	class OPTIMAL_ACCESS,
	class RANDOM_ACCESS,
	class WRITEABLE,
	class CREATEABLE,
	class RESIZEABLE,
	class HAS_C_PTR,
	class HAS_SPECIALIZED_ITER
>
struct array_traits<DATA_IDENTIFIER,
	params<
		OPTIMAL_ACCESS,
		RANDOM_ACCESS,
		WRITEABLE,
		CREATEABLE,
		RESIZEABLE,
		HAS_C_PTR,
		HAS_SPECIALIZED_ITER
		>
	>
	: public DATA_IDENTIFIER
{
	typedef DATA_IDENTIFIER data_identifier;
	typedef OPTIMAL_ACCESS optimal_access_tag;
	typedef RANDOM_ACCESS has_random_access;
	typedef WRITEABLE is_writeable;
	typedef CREATEABLE is_createable;
	typedef RESIZEABLE is_resizeable;
	typedef HAS_C_PTR has_c_ptr;
	typedef HAS_SPECIALIZED_ITER has_specialized_iter;
};
*/

// optimal_access_tags:
struct seq_optimal_tag { enum { evaluate = 1 } eval; };
struct random_optimal_tag { enum { evaluate = 2 } eval; };
struct nd_seq_optimal_tag { enum { evaluate = 0 } eval; };

template <class X>
class referer : public types::array_is_referer_identifier
{
public:
	typedef X derived_type;
	X& derived() { return static_cast<X&>(*this); }
	const X& derived() const { return static_cast<const X&>(*this); }
};

template <class X, class Y>
struct minimum_access_tag
{
	//typedef typename
	//	types::t_if<typename types::
	//	t_expr<(true)>::type, X, Y>::type type;

	enum { x_eval = X::evaluate };
	enum { y_eval = Y::evaluate };

	typedef typename
		types::t_if<typename types::t_expr<(int(x_eval) <  int(y_eval))>::
			type, X, Y>::type type;
};

template <template <typename, typename> class CC>
struct use
{
	template <class T, class CHILD_CLASS>
	struct instance
	{
		typedef CC <T, CHILD_CLASS> type;
	};
};

template <template <typename, int, typename> class CC, int N1>
struct use_1n
{
	template <class T, class CHILD_CLASS>
	struct instance
	{
		typedef CC <T, N1, CHILD_CLASS> type;
	};
};

template <template <typename, typename, typename> class CC, class P1>
struct use_1t
{
	template <class T, class CHILD_CLASS>
	struct instance
	{
		typedef CC <T, P1, CHILD_CLASS> type;
	};
};

template <template <typename, typename, typename, typename> class CC,
					class P1, class P2>
struct use_2t
{
	template <class T, class CHILD_CLASS>
	struct instance
	{
		typedef CC <T, P1, P2, CHILD_CLASS> type;
	};
};

template <template <typename, typename, typename, typename, typename> class CC,
					class P1, class P2, class P3>
struct use_3t
{
	template <class T, class CHILD_CLASS>
	struct instance
	{
		typedef CC <T, P1, P2, P3, CHILD_CLASS> type;
	};
};

template <template <typename, typename, typename, typename, typename, typename> class CC,
					class P1, class P2, class P3, class P4>
struct use_4t
{
	template <class T, class CHILD_CLASS>
	struct instance
	{
		typedef CC <T, P1, P2, P3, P4, CHILD_CLASS> type;
	};
};




} //namespace data

} //namespace ivl



#endif // IVL_CORE_DETAILS_DATA_BASE_HPP
