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

#ifndef IVL_CORE_DETAILS_IVL_FUNC_IVL_FUNC_HPP
#define IVL_CORE_DETAILS_IVL_FUNC_IVL_FUNC_HPP

namespace ivl {

namespace convert {

struct dd { };
struct dl { };
struct df { };
struct ff { };

struct convd { };
struct convl { };
struct convf { };

template<class C> struct get_out { typedef convd type; };
template<> struct get_out<ff> { typedef convf type; };

} /* namespace convert */

template <class IMPL, class TPL, class OUTCONV>
struct ivl_func_rvalue
:
public tuple_rvalue<ivl_func_rvalue<IMPL, TPL, OUTCONV> >
{
	//const TPL&
	TPL tpl;
	typedef typename types::bare_type<TPL>::type tp;

	// iavr: passing the original instance of derived ivl_func
	IMPL* impl;
	ivl_func_rvalue& operator()(IMPL& i) { impl = &i; return *this; }

	/*
	template<class T>
	ivl_func_rvalue(const T& t) : tpl(t) { }
	*/

	ivl_func_rvalue(TPL ts) : tpl(ts) { }

	typedef typename tp::template val_t<1>::type t1;
	typedef typename tp::template val_t<2>::type t2;
	typedef typename tp::template val_t<3>::type t3;
	typedef typename tp::template val_t<4>::type t4;
	typedef typename tp::template val_t<5>::type t5;
	typedef typename tp::template val_t<6>::type t6;
	typedef typename tp::template val_t<7>::type t7;
	typedef typename tp::template val_t<8>::type t8;
	typedef typename tp::template val_t<9>::type t9;
	typedef typename tp::template val_t<10>::type t10;

	ivl_func_rvalue(
		t1 v1 = types::skip(),
		t2 v2 = types::skip(),
		t3 v3 = types::skip(),
		t4 v4 = types::skip(),
		t5 v5 = types::skip(),
		t6 v6 = types::skip(),
		t7 v7 = types::skip(),
		t8 v8 = types::skip(),
		t9 v9 = types::skip(),
		t10 v10 = types::skip())
			: tpl(v1, v2, v3, v4, v5, v6, v7, v8, v9, v10)
		{}

	template <class TUP>
	inline
	void tuple_output(TUP& tup) const
	{
		//IMPL imp;
		//apply_tuple(tplsjoin(tup, tpl), imp);

		// iavr: passing the original instance of derived ivl_func
		apply_tuple(tplsjoin(tup, tpl), *impl);
	}

	template <class TUP>
	inline
	void tuple_output(const TUP& tup) const
	{
		// IMPL imp;
		// //imp.t_operate(tplsjoin(tup, tpl));
		// apply_tuple(tplsjoin(tup, tpl), imp);

		// iavr: passing the original instance of derived ivl_func
		apply_tuple(tplsjoin(tup, tpl), *impl);
	}

/*
	ivl_func_rvalue(const ivl_func_rvalue& oo) :tpl(oo.tpl)
	{
		std::cout << "ACOPY!!!!!!!!!!!!!!!!!!\n";
	}
*/
	//TODO:necessary?
	/*
	template <class T1>
	inline
	void output(T1& t1) const
	{
		IMPL imp;
		imp.t_operate(tplsjoin(
			reftpl(t1), tpl));
	}

	template <class T1, class T2>
	inline
	void output(T1& t1, T2& t2) const
	{
		IMPL imp;
		imp.t_operate(tplsjoin(
			reftpl(t1, t2), tpl));
	}

	template <class T1, class T2, class T3>
	inline
	void output(T1& t1, T2& t2, T3& t3) const
	{
		IMPL imp;
		imp.t_operate(tplsjoin(
			reftpl(t1, t2, t3), tpl));
	}

	template <class T1, class T2, class T3, class T4>
	inline
	void output(T1& t1, T2& t2, T3& t3, T4& t4) const
	{
		IMPL imp;
		imp.t_operate(tplsjoin(
			reftpl(t1, t2, t3, t4), tpl));
	}

	template <class T1, class T2, class T3, class T4, class T5>
	inline
	void output(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5) const
	{
		IMPL imp;
		imp.t_operate(tplsjoin(
			reftpl(t1, t2, t3, t4, t5), tpl));
	}

	template <class T1, class T2, class T3, class T4, class T5, class T6>
	inline
	void output(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6) const
	{
		IMPL imp;
		imp.t_operate(tplsjoin(
			reftpl(t1, t2, t3, t4, t5, t6), tpl));
	}

	template <class T1, class T2, class T3, class T4, class T5, class T6,
		class T7>
	inline
	void output(T1& t1, T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7) const
	{
		IMPL imp;
		imp.t_operate(tplsjoin(
			reftpl(t1, t2, t3, t4, t5, t6, t7), tpl));
	}
	*/

};

// ----

template <class IMPL, class CONV>
struct ivl_func_lcall
{
	IMPL& impl;
	ivl_func_lcall(IMPL& i) : impl(i) { }


	template<class TPL>
	inline
	ivl_func_rvalue<IMPL, const TPL&,
		typename convert::get_out<CONV>::type>
		operator[](const TPL& t)
	{
		return ivl_func_rvalue<IMPL,
		const TPL&,
		typename convert::get_out<CONV>::type>(t)(impl);
	}


	inline
	ivl_func_rvalue<IMPL,
		tuple<>,
		typename convert::get_out<CONV>::type>
		operator()()
	{
		return ivl_func_rvalue<IMPL,
		tuple<>,
		typename convert::get_out<CONV>::type>()(impl);
	}

	template<class T1>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1)
	{
		return ivl_func_rvalue<IMPL,
		tuple<const T1&>,
		typename convert::get_out<CONV>::type>(t1)(impl);
	}

	template<class T1, class T2>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2)
	{
		return ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&>,
		typename convert::get_out<CONV>::type>(t1, t2)(impl);
	}

	template<class T1, class T2, class T3>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3)
	{
		return ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3)(impl);
	}

	template<class T1, class T2, class T3, class T4>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
	{
		return ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4)(impl);
	}

	template<class T1, class T2, class T3, class T4, class T5>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5)
	{
		return ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4, t5)(impl);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6)
	{
		return ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4, t5, t6)(impl);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6,
			class T7>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&, const T7&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6, const T7& t7)
	{
		return ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&, const T7&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4, t5, t6, t7)(impl);
	}

//-----------------------------------------------------------------------------

// 1st argument is a non-const reference:

	template<class T1>
	inline
	ivl_func_rvalue<IMPL,
		tuple<T1&>,
		typename convert::get_out<CONV>::type>
		operator()(T1& t1)
	{
		return ivl_func_rvalue<IMPL,
		tuple<T1&>,
		typename convert::get_out<CONV>::type>(t1)(impl);
	}

	template<class T1, class T2>
	inline
	ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&>,
		typename convert::get_out<CONV>::type>
		operator()(T1& t1, const T2& t2)
	{
		return ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&>,
		typename convert::get_out<CONV>::type>(t1, t2)(impl);
	}

	template<class T1, class T2, class T3>
	inline
	ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&>,
		typename convert::get_out<CONV>::type>
		operator()(T1& t1, const T2& t2, const T3& t3)
	{
		return ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3)(impl);
	}

	template<class T1, class T2, class T3, class T4>
	inline
	ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&>,
		typename convert::get_out<CONV>::type>
		operator()(T1& t1, const T2& t2, const T3& t3, const T4& t4)
	{
		return ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4)(impl);
	}

	template<class T1, class T2, class T3, class T4, class T5>
	inline
	ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&,
						const T5&>,
		typename convert::get_out<CONV>::type>
		operator()(T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5)
	{
		return ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&,
						const T5&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4, t5)(impl);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	inline
	ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&>,
		typename convert::get_out<CONV>::type>
		operator()(T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6)
	{
		return ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4, t5, t6)(impl);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6,
			class T7>
	inline
	ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&, const T7&>,
		typename convert::get_out<CONV>::type>
		operator()(T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6, const T7& t7)
	{
		return ivl_func_rvalue<IMPL,
		tuple<T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&, const T7&>,
		typename convert::get_out<CONV>::type>(t1, t2, t3, t4, t5, t6, t7)(impl);
	}



/*
	inline
	ivl_func_rvalue<IMPL,
		tuple<>,
		typename convert::get_out<CONV>::type>
		operator()()
	{
		return tuple<>();
	}

	template<class T1>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1)
	{
		return reftpl(t1);
	}

	template<class T1, class T2>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2)
	{
		return reftpl(t1, t2);
	}

	template<class T1, class T2, class T3>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3)
	{
		return reftpl(t1, t2, t3);
	}

	template<class T1, class T2, class T3, class T4>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
	{
		return reftpl(t1, t2, t3, t4);
	}

	template<class T1, class T2, class T3, class T4, class T5>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5)
	{
		return reftpl(t1, t2, t3, t4, t5);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6)
	{
		return reftpl(t1, t2, t3, t4, t5, t6);
	}

	template<class T1, class T2, class T3, class T4, class T5, class T6,
			class T7>
	inline
	ivl_func_rvalue<IMPL,
		tuple<const T1&, const T2&, const T3&, const T4&,
						const T5&, const T6&, const T7&>,
		typename convert::get_out<CONV>::type>
		operator()(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6, const T7& t7)
	{
		return reftpl(t1, t2, t3, t4, t5, t6, t7);
	}
	*/
};

// ----

template <class DERIVED, class CONV = convert::ff>
struct ivl_func : public fun::function <DERIVED>
{
private:
	DERIVED& derived() { return static_cast<DERIVED&>(*this); }
public:
	typedef func_details::sep sep;

	typedef ivl_func_lcall<DERIVED, CONV> lcall_type;

	//lcall_type operator++(int) { return lcall_type(); }

	// iavr: passing the original instance of derived ivl_func
	lcall_type operator++(int) { return lcall_type(derived()); }

/*
//TODO: necessary?
	template<int N, class T>
	inline void t_operate(const tuple_base<N, T>& tpl)
	{
		//TODO: fix
		//the fix should probably be in the tuple value access.
		//if any fix.
		//otherwise, construct a tuple object when passing here
		//and get an actual reference.
		//other option, skip this part anyway to also avoid using.
		T& t(const_cast<T&>(tpl.derived()));
		apply_tuple(t, derived());
	}
*/
/*
	template<class T>
	inline void operate(tuple_base<1, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1);
	}

	template<class T>
	inline void operate(tuple_base<2, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2);
	}

	template<class T>
	inline void operate(tuple_base<3, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3);
	}

	template<class T>
	inline void operate(tuple_base<4, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3, t.v4);
	}

	template<class T>
	inline void operate(tuple_base<5, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3, t.v4, t.v5);
	}

	template<class T>
	inline void operate(tuple_base<6, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3, t.v4, t.v5, t.v6);
	}

	template<class T>
	inline void operate(tuple_base<7, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3, t.v4, t.v5, t.v6, t.v7);
	}

	template<class T>
	inline void operate(tuple_base<8, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3, t.v4, t.v5, t.v6, t.v7, t.v8);
	}

	template<class T>
	inline void operate(tuple_base<9, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3, t.v4, t.v5, t.v6, t.v7, t.v8, t.v9);
	}

	template<class T>
	inline void operate(tuple_base<10, T> tpl)
	{
		T& t(tpl.derived());
		derived().operate(t.v1, t.v2, t.v3, t.v4, t.v5, t.v6, t.v7, t.v8, t.v9,
							t.v10);
	}
*/
	// ---------------------------------------------------------------------

	template <class RT, class T1>
	RT simple(const T1& t1)
	{
		RT r = derived()++(t1);
		return r;
	}

	template <class RT, class T1, class T2>
	RT simple(const T1& t1, const T2& t2)
	{
		RT r = derived()++(t1, t2);
		return r;
	}

	template <class RT, class T1, class T2, class T3>
	RT simple(const T1& t1, const T2& t2, const T3& t3)
	{
		RT r = derived()++(t1, t2, t3);
		return r;
	}

	template <class RT, class T1, class T2, class T3, class T4>
	RT simple(const T1& t1, const T2& t2, const T3& t3, const T4& t4)
	{
		RT r = derived()++(t1, t2, t3, t4);
		return r;
	}

	template <class RT, class T1, class T2, class T3, class T4,
		class T5>
	RT simple(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5)
	{
		RT r = derived()++(t1, t2, t3, t4, t5);
		return r;
	}

	template <class RT, class T1, class T2, class T3, class T4,
		class T5, class T6>
	RT simple(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6)
	{
		RT r = derived()++(t1, t2, t3, t4, t5, t6);
		return r;
	}

	template <class RT, class T1, class T2, class T3, class T4,
		class T5, class T6, class T7>
	RT simple(const T1& t1, const T2& t2, const T3& t3, const T4& t4,
					const T5& t5, const T6& t6, const T7& t7)
	{
		RT r = derived()++(t1, t2, t3, t4, t5, t6, t7);
		return r;
	}

	// ---------------------------------------------------------------------

	template <
		class R1, class R2 = types::skip, class R3 = types::skip,
		class R4 = types::skip, class R5 = types::skip, class R6 = types::skip,
		class R7 = types::skip, class R8 = types::skip, class R9 = types::skip,
		class R10 = types::skip>
	struct call
	:
	public ret<R1, R2, R3, R4, R5, R6, R7, R8, R9, R10>
	{
		// iavr: needed as return type of operator()
		typedef call current_type;

		// kimonas: fix for call<N arguments>
		// note: TODO: implementation should be questioned
		ivl::tuple<R1&,
			typename types::t_if<types::t_eq<R2, types::skip>, types::skip, R2&>::type,
			typename types::t_if<types::t_eq<R3, types::skip>, types::skip, R3&>::type,
			typename types::t_if<types::t_eq<R4, types::skip>, types::skip, R4&>::type,
			typename types::t_if<types::t_eq<R5, types::skip>, types::skip, R5&>::type,
			typename types::t_if<types::t_eq<R6, types::skip>, types::skip, R6&>::type,
			typename types::t_if<types::t_eq<R7, types::skip>, types::skip, R7&>::type,
			typename types::t_if<types::t_eq<R8, types::skip>, types::skip, R8&>::type,
			typename types::t_if<types::t_eq<R9, types::skip>, types::skip, R9&>::type,
			typename types::t_if<types::t_eq<R10, types::skip>, types::skip, R10&>::type>
		ref_this() { return reftpl(this->v1, this->v2, this->v3, this->v4,
			this->v5, this->v6, this->v7, this->v8, this->v9, this->v10); }

		// iavr: passing the original instance of derived ivl_func
		DERIVED* derived_impl;
		call(DERIVED* d) : derived_impl(d) { }
		DERIVED& derived() { return *derived_impl; }

		template<class T1>
		call(T1& t1)
		{
			DERIVED d;
			d++(t1).tuple_output(ref_this()); // [kimonas]: ref_this() instead of *this
		}

		// iavr: passing the original instance of derived ivl_func
		template<class T1>
		current_type& operator()(T1& t1)
		{
			derived()++(t1).tuple_output(ref_this());
			return *this;
		}

		template<class T1, class T2>
		call(T1& t1, T2& t2)
		{
			DERIVED d;
			d++(t1, t2).tuple_output(ref_this());
		}

		// iavr: passing the original instance of derived ivl_func
		template<class T1, class T2>
		current_type& operator()(T1& t1, T2& t2)
		{
			derived()++(t1, t2).tuple_output(ref_this());
			return *this;
		}

		template<class T1, class T2, class T3>
		call(T1& t1, T2& t2, T3& t3)
		{
			DERIVED d;
			d++(t1, t2, t3).tuple_output(ref_this());
		}

		// iavr: passing the original instance of derived ivl_func
		template<class T1, class T2, class T3>
		current_type& operator()(T1& t1, T2& t2, T3& t3)
		{
			derived()++(t1, t2, t3).tuple_output(ref_this());
			return *this;
		}
	};
};

template <class DERIVED, class CONV>
template <class R1>
struct ivl_func<DERIVED, CONV>::call<R1, types::skip, types::skip, types::skip,
	types::skip, types::skip, types::skip, types::skip, types::skip,
	types::skip>
	:
	public ret<R1>
{
	//ret<R1>& r() { return static_cast<ret<R1>&>(*this); }

	// iavr: throw away ret<> in call to DERIVED::operate()
	R1& r() { return ret<R1>::ret_base(); }

	// iavr: needed as return type of operator()
	typedef ivl_func<DERIVED, CONV>::call<R1, types::skip, types::skip,
	types::skip, types::skip, types::skip, types::skip, types::skip, types::skip,
	types::skip> current_type;

	// iavr: passing the original instance of derived ivl_func
	DERIVED* derived_impl;
	call(DERIVED* d) : derived_impl(d) { }
	DERIVED& derived() { return *derived_impl; }

	template<class T1>
	call(T1& t1)
	{
		//Note: old was: DERIVED()++(t1).output(r())
		DERIVED d;
		d++(t1).tuple_output(reftpl(r()));
	}

	// iavr: passing the original instance of derived ivl_func
	template<class T1>
	current_type& operator()(T1& t1)
	{
		//Note: old was: DERIVED()++(t1).output(r())
		derived()++(t1).tuple_output(reftpl(r()));
		return *this;
	}

	template<class T1, class T2>
	call(T1& t1, T2& t2)
	{
		DERIVED d;
		d++(t1, t2).tuple_output(reftpl(r()));
	}

	// iavr: passing the original instance of derived ivl_func
	template<class T1, class T2>
	current_type& operator()(T1& t1, T2& t2)
	{
		derived()++(t1, t2).tuple_output(reftpl(r()));
		return *this;
	}

	template<class T1, class T2, class T3>
	call(T1& t1, T2& t2, T3& t3)
	{
		DERIVED d;
		d++(t1, t2, t3).tuple_output(reftpl(r()));
	}

	// iavr: passing the original instance of derived ivl_func
	template<class T1, class T2, class T3>
	current_type& operator()(T1& t1, T2& t2, T3& t3)
	{
		derived()++(t1, t2, t3).tuple_output(reftpl(r()));
		return *this;
	}

};

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_IVL_FUNC_IVL_FUNC_HPP

