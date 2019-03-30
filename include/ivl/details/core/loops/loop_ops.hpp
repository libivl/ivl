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

#ifndef IVL_CORE_DETAILS_LOOP_OPS_HPP
#define IVL_CORE_DETAILS_LOOP_OPS_HPP

namespace ivl {
namespace loops {
#if 0
namespace loops_details {

// =, assign_copy_class
template <class J, class K, class IS_ARRAY>
struct assign_copy_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 = elem2;
	};
};

template <class J, class K>
struct assign_copy_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.assign(elem2);
	};
};

// +=, assign_plus_class
template <class J, class K, class IS_ARRAY>
struct assign_plus_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 += elem2;
	};
};

template <class J, class K>
struct assign_plus_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.plus_assign(elem2);
	};
};

// -=, assign_minus_class
template <class J, class K, class IS_ARRAY>
struct assign_minus_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 -= elem2;
	};
};

template <class J, class K>
struct assign_minus_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.minus_assign(elem2);
	};
};

// *=, assign_times_class
template <class J, class K, class IS_ARRAY>
struct assign_times_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 *= elem2;
	};
};

template <class J, class K>
struct assign_times_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.times_assign(elem2);
	};
};

// /=, assign_divide_class
template <class J, class K, class IS_ARRAY>
struct assign_divide_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 /= elem2;
	};
};

template <class J, class K>
struct assign_divide_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.divide_assign(elem2);
	};
};

// %=, assign_mod_class
template <class J, class K, class IS_ARRAY>
struct assign_mod_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 %= elem2;
	};
};

template <class J, class K>
struct assign_mod_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.mod_assign(elem2);
	};
};

// &=, assign_bitand_class
template <class J, class K, class IS_ARRAY>
struct assign_bitand_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 &= elem2;
	};
};

template <class J, class K>
struct assign_bitand_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.bitand_assign(elem2);
	};
};

// |=, assign_bitor_class
template <class J, class K, class IS_ARRAY>
struct assign_bitor_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 |= elem2;
	};
};

template <class J, class K>
struct assign_bitor_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.bitor_assign(elem2);
	};
};

// <<=, assign_bitlshift_class
template <class J, class K, class IS_ARRAY>
struct assign_bitlshift_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 <<= elem2;
	};
};

template <class J, class K>
struct assign_bitlshift_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.bitlshift_assign(elem2);
	};
};

// >>=, assign_bitrshift_class
template <class J, class K, class IS_ARRAY>
struct assign_bitrshift_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 >>= elem2;
	};
};

template <class J, class K>
struct assign_bitrshift_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.bitrshift_assign(elem2);
	};
};

// ^=, assign_bitxor_class
template <class J, class K, class IS_ARRAY>
struct assign_bitxor_class_details
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1 ^= elem2;
	};
};

template <class J, class K>
struct assign_bitxor_class_details<J, K, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
	{
		elem1.bitxor_assign(elem2);
	};
};

} /* namespace loops_details */

// =, assign_copy_class
template<class J, class K>
struct assign_copy_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_copy_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// +=, assign_plus_class
template<class J, class K>
struct assign_plus_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_plus_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// -=, assign_minus_class
template<class J, class K>
struct assign_minus_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_minus_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// *=, assign_times_class
template<class J, class K>
struct assign_times_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_times_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// /=, assign_divide_class
template<class J, class K>
struct assign_divide_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_divide_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// %=, assign_mod_class
template<class J, class K>
struct assign_mod_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_mod_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// &=, assign_bitand_class
template<class J, class K>
struct assign_bitand_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_bitand_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// |=, assign_bitor_class
template<class J, class K>
struct assign_bitor_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_bitor_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// <<=, assign_bitlshift_class
template<class J, class K>
struct assign_bitlshift_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_bitlshift_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// >>=, assign_bitrshift_class
template<class J, class K>
struct assign_bitrshift_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_bitrshift_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};

// ^=, assign_bitxor_class
template<class J, class K>
struct assign_bitxor_class
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::assign_bitxor_class_details<J, K,
			typename types::is_ivl_array<J>::type>::elem_op(elem1, elem2);
	};
};
#else

// =, assign_copy_class
template<class J, class K>
struct assign_copy_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force_assign(elem1, elem2); }
};

// +=, assign_plus_class
template<class J, class K>
struct assign_plus_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) += elem2; }
};

// -=, assign_minus_class
template<class J, class K>
struct assign_minus_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) -= elem2; }
};

// *=, assign_times_class
template<class J, class K>
struct assign_times_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) *= elem2; }
};

// /=, assign_divide_class
template<class J, class K>
struct assign_divide_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) /= elem2; }
};

// %=, assign_mod_class
template<class J, class K>
struct assign_mod_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) %= elem2; }
};

// &=, assign_bitand_class
template<class J, class K>
struct assign_bitand_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) &= elem2; }
};

// |=, assign_bitor_class
template<class J, class K>
struct assign_bitor_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) |= elem2; }
};

// <<=, assign_bitlshift_class
template<class J, class K>
struct assign_bitlshift_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) <<= elem2; }
};

// >>=, assign_bitrshift_class
template<class J, class K>
struct assign_bitrshift_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) >>= elem2; }
};

// ^=, assign_bitxor_class
template<class J, class K>
struct assign_bitxor_class
{
	static inline void elem_op(J elem1, K elem2)
		{ ivl::force(elem1) ^= elem2; }
};

#endif



// -------------------------------------------------------

// write-write loops


namespace loops_details {

// =, assign_copy_class
template <class J, class K, class IS_ARRAY_1, class IS_ARRAY_2>
struct write_write_swap_class_details { };

template <class J, class K>
struct write_write_swap_class_details<J, K, types::t_false, types::t_false>
{
	static inline void elem_op(J elem1, K elem2)
		{ std::swap(elem1, elem2); }
};

template <class J, class K>
struct write_write_swap_class_details<J, K, types::t_true, types::t_true>
{
	static inline void elem_op(J elem1, K elem2)
		{ elem1.swap(elem2); }
};

} /* namespace loops_details */

template<class J, class K>
struct write_write_swap_class
: public types::loop_ww_identifier
{
	static inline void elem_op(J elem1, K elem2)
	{
		return loops_details::write_write_swap_class_details<J, K,
			typename types::is_ivl_array<J>::type,
			typename types::is_ivl_array<K>::type>::elem_op(elem1, elem2);
	}
};


} /* namespace loops */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_LOOP_OPS_HPP
