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

#ifndef IVL_ARRAY_DETAILS_COMMON_READWRITE_ARRAY_COMMON_HPP
#define IVL_ARRAY_DETAILS_COMMON_READWRITE_ARRAY_COMMON_HPP

namespace ivl {

namespace array_details {

template <
class T, class S,
class BASE,
class IS_WRITEABLE >
class readwrite_array_common
{
};

//not writeable
template <class T, class S, class BASE>
class readwrite_array_common<T, S, BASE, types::t_false>
: public conversions_array_common<T, S, BASE>
{
private:
	typedef readwrite_array_common prv_this_type;
	typedef array<T, S> t;
	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }
public:
	// ++
	// for not writeable arrays, ++ iterates through all the elements...
	t& operator++()
	{
		typedef typename t::const_iterator c_it;
		for(c_it i = to_array().begin(); i!= to_array().end(); i++) *i;
		return to_array();
	}
};

//writeable
template <class T, class S, class BASE>
class readwrite_array_common<T, S, BASE, types::t_true>
: public conversions_array_common<T, S, BASE>
{
private:
	typedef readwrite_array_common prv_this_type;
	typedef array<T, S> t;
	t& to_array() { return static_cast<t&>(*this); }
	const t& to_array() const { return static_cast<const t&>(*this); }

public:
	typedef typename prv_this_type::derived_type derived_type;
	// everything is defined twice
	// the unsafe way (function call) and the safe way (operator).

	// the unsafe way -------------------------------------------

	//plus_assign(), for +=
	template <class A>
	derived_type& plus_assign(const A& a)
	{
		loop_on<loops::assign_plus_class>(this->derived(), a);
		return this->derived();
	}

	//minus_assign(), for -=
	template <class A>
	derived_type& minus_assign(const A& a)
	{
		loop_on<loops::assign_minus_class>(this->derived(), a);
		return this->derived();
	}

	//times_assign(), for *=
	template <class A>
	derived_type& times_assign(const A& a)
	{
		loop_on<loops::assign_times_class>(this->derived(), a);
		return this->derived();
	}

	//divide_assign(), for /=
	template <class A>
	derived_type& divide_assign(const A& a)
	{
		loop_on<loops::assign_divide_class>(this->derived(), a);
		return this->derived();
	}

	// mod_assign(), for %=
	template <class A>
	derived_type& mod_assign(const A& a)
	{
		loop_on<loops::assign_mod_class>(this->derived(), a);
		return this->derived();
	}

	// bitor_assign(), for |=
	template <class A>
	derived_type& bitor_assign(const A& a)
	{
		loop_on<loops::assign_bitor_class>(this->derived(), a);
		return this->derived();
	}

	// bitand_assign(), for &=
	template <class A>
	derived_type& bitand_assign(const A& a)
	{
		loop_on<loops::assign_bitand_class>(this->derived(), a);
		return this->derived();
	}

	// bitxor_assign(), for ^=
	template <class A>
	derived_type& bitxor_assign(const A& a)
	{
		loop_on<loops::assign_bitxor_class>(this->derived(), a);
		return this->derived();
	}

	// bitlshift_assign(), for <<=
	template <class A>
	derived_type& bitlshift_assign(const A& a)
	{
		loop_on<loops::assign_bitlshift_class>(this->derived(), a);
		return this->derived();
	}

	// bitrshift_assign(), for >>=
	template <class A>
	derived_type& bitrshift_assign(const A& a)
	{
		loop_on<loops::assign_bitrshift_class>(this->derived(), a);
		return this->derived();
	}


	// decrement(), for --. no safe/unsafe way
	derived_type& decrement()
	{
		//todo: unary loop
		this->minus_assign(1);
		return this->derived();
	}

	// increment(), for ++. no safe/unsafe way
	derived_type& increment()
	{
		//todo: unary loop
		this->plus_assign(1);
		return this->derived();
	}

	// --------------------------------------------------------
	// the safe way (operator)


	//+=
	template <class A>
	derived_type& operator+=(const A& a)
	{
		safe_loop_on<loops::assign_plus_class>(this->derived(), a);
		return this->derived();
	}

	//-=
	template <class A>
	derived_type& operator-=(const A& a)
	{
		safe_loop_on<loops::assign_minus_class>(this->derived(), a);
		return this->derived();
	}

	//*=
	template <class A>
	derived_type& operator*=(const A& a)
	{
		safe_loop_on<loops::assign_times_class>(this->derived(), a);
		return this->derived();
	}

	// /=
	template <class A>
	derived_type& operator/=(const A& a)
	{
		safe_loop_on<loops::assign_divide_class>(this->derived(), a);
		return this->derived();
	}

	// %=
	template <class A>
	derived_type& operator%=(const A& a)
	{
		safe_loop_on<loops::assign_mod_class>(this->derived(), a);
		return this->derived();
	}

	// |=
	template <class A>
	derived_type& operator|=(const A& a)
	{
		safe_loop_on<loops::assign_bitor_class>(this->derived(), a);
		return this->derived();
	}

	// &=
	template <class A>
	derived_type& operator&=(const A& a)
	{
		safe_loop_on<loops::assign_bitand_class>(this->derived(), a);
		return this->derived();
	}

	// ^=
	template <class A>
	derived_type& operator^=(const A& a)
	{
		safe_loop_on<loops::assign_bitxor_class>(this->derived(), a);
		return this->derived();
	}

	// <<=
	template <class A>
	derived_type& operator<<=(const A& a)
	{
		safe_loop_on<loops::assign_bitlshift_class>(this->derived(), a);
		return this->derived();
	}

	// >>=
	template <class A>
	derived_type& operator>>=(const A& a)
	{
		safe_loop_on<loops::assign_bitrshift_class>(this->derived(), a);
		return this->derived();
	}

	// --
	derived_type& operator--()
	{
		//todo: unary loop
		this->decrement();
		return this->derived();
	}

	elem_func_unary<T, plus1_class,
		typename readwrite_array_common::derived_type> operator--(int)
	{
		//todo: unary loop
		typedef elem_func_unary<T, plus1_class,
			typename readwrite_array_common::derived_type> ret_t;
		this->decrement();
		return ret_t(this->derived());
	}

	// ++
	derived_type& operator++()
	{
		//todo: unary loop
		this->increment();
		return this->derived();
	}

	elem_func_unary<T, minus1_class,
		typename readwrite_array_common::derived_type> operator++(int)
	{
		//todo: unary loop
		typedef elem_func_unary<T, minus1_class,
			typename readwrite_array_common::derived_type> ret_t;
		this->increment();
		return ret_t(this->derived());
	}


	template <class D>
	void swap(array<T, D>& a)
	{
		// This algorithm is really bad.
		// Needs some improvement. However this is not a priority.
		// Also: I need to check that arrays are of the same level.
		size_t tl = to_array().length();
		size_t al = a.length();
		size_t mxs = std::max(tl, al);
		bool ok;
		/*
		int mns = std::min(length(), a.length());
		loops::loop_ww<write_write_swap_class, T, T>(*this, a);*/
		ok = types::r_resize(to_array(), mxs);
		CHECK(ok, ecomp);
		ok = types::r_resize(a, mxs);
		CHECK(ok, ecomp);

		// not fast enough. need loop with count or something.
		loops::loop_ww<loops::write_write_swap_class, T, T>(to_array(), a);

		ok = types::r_resize(to_array(), al);
		CHECK(ok, ecomp);
		ok = types::r_resize(a, tl);
		CHECK(ok, ecomp);
	}

};


} /* namespace array_details */

} /* namespace ivl */

#endif // IVL_ARRAY_DETAILS_COMMON_READWRITE_ARRAY_COMMON_HPP
