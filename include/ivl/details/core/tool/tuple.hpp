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

#ifndef IVL_CORE_DETAILS_TOOL_INTERNAL_HPP
#define IVL_CORE_DETAILS_TOOL_INTERNAL_HPP

namespace ivl {

// namespace internal declares structures that are not to
// be used from outside of ivl.
namespace internal {

/*
// class similar to boost::tuple, used to return multiple arguments from funcs.
// (up to 4)
template<
class T1 = types::codeword<>, class T2 = types::codeword<>,
class T3 = types::codeword<>, class T4 = types::codeword<> >
class tuple
{
	typedef typename types::bare_type<T1>::type j1;
	typedef typename types::bare_type<T2>::type j2;
	typedef typename types::bare_type<T3>::type j3;
	typedef typename types::bare_type<T4>::type j4;
	typedef typename types::t_if<types::t_eq<T1, codeword<> >,
		types::number<0>, typename types::t_if<types::t_eq<T2, codeword<> >,
		types::number<1>, typename types::t_if<types::t_eq<T3, codeword<> >,
		types::number<2>, typename types::t_if<types::t_eq<T4, codeword<> >,
		types::number<3>, types::number<4> >::type>::type>::type>::type
			size_value_type;

public:
	enum { size = size_value_type::value };
	T1 t1;
	T2 t2;
	T3 t3;
	T4 t4;
	tuple(const j1& t1 = j1(), const j2& t2 = j2(),
		const j3& t3 = j3(), const j4& t4 = j4())
		: t1(t1), t2(t2), t3(t3), t4(t4) {}

	void get(j1& o1) { o1 = t1; }
	void get(j1& o1, j2& o2) { o1 = t1; o2 = t2; }
	void get(j1& o1, j2& o2, j3& o3) { o1 = t1; o2 = t2; o3 = t3; }
	void get(j1& o1, j2& o2, j3& o3, j4& o4)
	{ o1 = t1; o2 = t2; o3 = t3; o4 = t4; }

};

template<
class T1, class T2 = types::codeword<>,
class T3 = types::codeword<>, class T4 = types::codeword<> >
tuple<T1, T2, T3, T4> tpl(T1 t1, T2 t2 = T2(), T3 t3 = T3(), T4 t4 = T4())
{
	return tuple<T1, T2, T3, T4>(t1, t2, t3, t4);
}
*/


// class similar to boost::tuple, used to return multiple arguments from funcs.
// (up to 10)

namespace internal_details {

template<class T>
struct tpl_ref_type
{
	typedef const typename types::bare_type<T>::type& cref;
	typedef typename types::bare_type<T>::type& ref;
};
template<class T>
struct tpl_ref_type<const T&>
{
	typedef const T& cref;
	typedef T& ref;
};
template<class T>
struct tpl_ref_type<T&>
{
	typedef T& cref;
	typedef T& ref;
};

template<int N, class T>
struct tpl_val
{
	typedef types::skip type;
	typedef types::skip ref;
	typedef types::skip ref_const;
	static ref val(T& tpl) { return types::skip(); }
	static ref_const val_const(const T& tpl) { return types::skip(); }
};

template<class T>
struct tpl_val<1, T>
{
	typedef typename T::t1 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v1; }
	static ref_const val_const(const T& tpl) { return tpl.v1; }
};

template<class T>
struct tpl_val<2, T>
{
	typedef typename T::t2 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v2; }
	static ref_const val_const(const T& tpl) { return tpl.v2; }
};

template<class T>
struct tpl_val<3, T>
{
	typedef typename T::t3 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v3; }
	static ref_const val_const(const T& tpl) { return tpl.v3; }
};

template<class T>
struct tpl_val<4, T>
{
	typedef typename T::t4 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v4; }
	static ref_const val_const(const T& tpl) { return tpl.v4; }
};

template<class T>
struct tpl_val<5, T>
{
	typedef typename T::t5 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v5; }
	static ref_const val_const(const T& tpl) { return tpl.v5; }
};

template<class T>
struct tpl_val<6, T>
{
	typedef typename T::t6 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v6; }
	static ref_const val_const(const T& tpl) { return tpl.v6; }
};

template<class T>
struct tpl_val<7, T>
{
	typedef typename T::t7 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v7; }
	static ref_const val_const(const T& tpl) { return tpl.v7; }
};

template<class T>
struct tpl_val<8, T>
{
	typedef typename T::t8 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v8; }
	static ref_const val_const(const T& tpl) { return tpl.v8; }
};

template<class T>
struct tpl_val<9, T>
{
	typedef typename T::t9 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v9; }
	static ref_const val_const(const T& tpl) { return tpl.v9; }
};

template<class T>
struct tpl_val<10, T>
{
	typedef typename T::t10 type;
	typedef typename types::best_ref<type, T>::type ref;
	typedef typename types::best_ref<type, types::t_true>::type ref_const;
	static ref val(T& tpl) { return tpl.v10; }
	static ref_const val_const(const T& tpl) { return tpl.v10; }
};


} /* namespace internal_details */

template <class DERIVED>
struct tuple_rvalue
{
	typedef DERIVED derived_type;
	derived_type& derived() { return static_cast<derived_type&>(*this); }
	const derived_type& derived() const
		{ return static_cast<const derived_type&>(*this); }
	template<class TPL>
	void tuple_output(TPL& t) const { this->derived().tuple_output(t); }
	template<class TPL>
	void tuple_output(TPL& t) { this->derived().tuple_output(t); }
};

template<
class T1 = types::skip, class T2 = types::skip,
class T3 = types::skip, class T4 = types::skip,
class T5 = types::skip, class T6 = types::skip,
class T7 = types::skip, class T8 = types::skip,
class T9 = types::skip, class T10 = types::skip, class VALID = types::t_true>
struct tuple_helper { };

template <class TIN, class T, class VALID = types::t_true>
struct join_tuple_helper { };

template <int N, int E>
struct assign_helper
{
	template<class T, class O>
	static inline void operate(T& t, const O& o)
	{
		t.val(types::number<N>()) = o.val(types::number<N>());
		assign_helper<N+1, E>::template operate(t, o);
	}
};

template <int E>
struct assign_helper<E, E>
{
	template<class T, class O>
	static inline void operate(T& t, const O& o) { }
};

template <int N, class TPL>
struct tuple_base : types::tuple_identifier
{
	typedef TPL derived_type;
	typedef types::number<N> size_value_type;
	derived_type& derived() { return static_cast<TPL&>(*this); }
	const derived_type& derived() const
		{ return static_cast<const TPL&>(*this); }

	template<class F>
	derived_type& operator=(const tuple_rvalue<F>& v)
	{
		v.tuple_output(derived());
		return derived();
	}

	template<class F>
	derived_type& operator=(tuple_rvalue<F>& v)
	{
		v.tuple_output(derived());
		return derived();
	}

	template<class TP>
	derived_type& operator=(const tuple_base<N, TP>& o)
	{
		assign_helper<1, N+1>::template operate(derived(), o.derived());
		return derived();
	}

	template<class TP>
	struct concat_t
	{
		typedef join_tuple_helper<const derived_type, TP> j_class;
		typedef typename j_class::type join_class;
		/*typedef typename tuple_helper<
		typename join_class::template val_t<1>::type,
		typename join_class::template val_t<2>::type,
		typename join_class::template val_t<3>::type,
		typename join_class::template val_t<4>::type,
		typename join_class::template val_t<5>::type,
		typename join_class::template val_t<6>::type,
		typename join_class::template val_t<7>::type,
		typename join_class::template val_t<8>::type,
		typename join_class::template val_t<9>::type,
		typename join_class::template val_t<10>::type>::type type;*/
		typedef join_class type;
	};

	template<class EL>
	struct append_t : concat_t<const typename tuple_helper<EL>::type> { };


	// operator, for tuple concatenation
	template<class EL>
	typename tuple_base::template append_t<const EL&>
		::type operator,(const EL& e) const
	{
		return typename append_t<const EL&>
			::join_class(derived(), typename tuple_helper<const EL&>::type(e));
	}

	template<class EL>
	typename tuple_base::template append_t<EL&>
		::type operator,(EL& e) const
	{
		return typename append_t<EL&>
			::join_class(derived(), typename tuple_helper<EL&>::type(e));
	}

	// iavr: concatenate with another tuple
	template<class TP>
	typename tuple_base::template concat_t<TP>
		::type concat(TP& t) const
	{
		return typename concat_t<TP>
			::join_class(derived(), t);
	}

};

// ----------------------------------------------------------------------------

/*
inline
std::ostream& operator << (std::ostream& os, const types::skip&)
{
	return os;
}*/

template<int N, class T>
std::ostream& stream_out(std::ostream& os, const tuple_base<N, T>& t)
{
	os << "(";
	typedef types::t_ge<types::number<N>, types::number<1> > print1;
	os << types::r_if<print1>(t.derived().val(types::number<1>()), "");
	if(N > 1) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<2> > print2;
	os << types::r_if<print2>(t.derived().val(types::number<2>()), "");
	if(N > 2) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<3> > print3;
	os << types::r_if<print3>(t.derived().val(types::number<3>()), "");
	if(N > 3) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<4> > print4;
	os << types::r_if<print4>(t.derived().val(types::number<4>()), "");
	if(N > 4) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<5> > print5;
	os << types::r_if<print5>(t.derived().val(types::number<5>()), "");
	if(N > 5) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<6> > print6;
	os << types::r_if<print6>(t.derived().val(types::number<6>()), "");
	if(N > 6) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<7> > print7;
	os << types::r_if<print7>(t.derived().val(types::number<7>()), "");
	if(N > 7) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<8> > print8;
	os << types::r_if<print8>(t.derived().val(types::number<8>()), "");
	if(N > 8) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<9> > print9;
	os << types::r_if<print9>(t.derived().val(types::number<9>()), "");
	if(N > 9) os << ", ";
	typedef types::t_ge<types::number<N>, types::number<10> > print10;
	os << types::r_if<print10>(t.derived().val(types::number<10>()), "");
	os << ")";
	return os;
}

// ----------------------------------------------------------------------------

template <class T1, class T2>
class join_tuple : public tuple_base<T1::size + T2::size, join_tuple<T1, T2> >
{
public:
	typedef tuple_base<T1::size + T2::size, join_tuple<T1, T2> > tuple_base_type;

	template<int N>
	struct val_t
	{
		typedef typename types::t_sub<
			types::number<N>, typename T1::size_value_type>::type secondidx;
		typedef typename types::t_le<
			types::number<N>, typename T1::size_value_type>::type first;

		typedef typename types::t_if<first,
			typename T1::template val_t<N>,
			typename T2::template val_t<secondidx::value>
		>::type val_struct;

		typedef typename val_struct::type type;

		typedef typename val_struct::ref_const ref;
		typedef typename val_struct::ref_const ref_const;

		template <class T>
		static ref_const val(T& t)
		{
			return val_struct::val_const(types::r_if<first>(t.t1, t.t2));
		}
		template <class T>
		static ref_const val_const(const T& t)
		{
			return val_struct::val_const(types::r_if<first>(t.t1, t.t2));
		}
	};

	T1& t1;
	T2& t2;
	join_tuple(T1& t1, T2& t2) : t1(t1), t2(t2) { }

	join_tuple(const join_tuple& o) : t1(o.t1), t2(o.t2) { }

	using tuple_base_type::operator =;
	using tuple_base_type::operator ,;

	join_tuple& operator=(const join_tuple& o)
	{
		t1 = o.t1;
		t2 = o.t2;
		return *this;
	}

	typedef typename types::t_add<
		typename T1::size_value_type, typename T2::size_value_type>
		::type size_value_type;

	enum { size = size_value_type::value };

	template<int N>
	typename val_t<N>::ref val(types::number<N>) const
	{
		return val_t<N>::val(*this);
	}
};

template <class TIN, class T>
struct join_tuple_helper<TIN, T> : types::t_id<join_tuple<TIN, T> > { };


namespace internal_details {

struct sep_val
{
	typedef ivl::sep type;
	typedef ivl::sep ref;
	typedef ivl::sep ref_const;
	template<class T>
	static inline ivl::sep val(T) { return ivl::sep(); }
	template<class T>
	static inline ivl::sep val_const(T) { return ivl::sep(); }
};

} // namespace internal_details

template <class T1, class T2>
class join_tuple_sep
: public tuple_base<T1::size + T2::size + 1, join_tuple_sep<T1, T2> >
{
	template<int N>
	struct accessor
	{
		typedef typename types::t_sub<
			types::number<N - 1>, typename T1::size_value_type>::type secondidx;
		typedef typename types::t_le<
			types::number<N>, typename T1::size_value_type>::type first;
		typedef typename types::t_eq<
			types::number<N - 1>, typename T1::size_value_type>::type sp;

		typedef typename types::t_if<first,
			typename T1::template val_t<N>,
			typename types::t_if<sp, internal_details::sep_val,
				typename T2::template val_t<secondidx::value>
				>::type
		>::type val_struct;

		typedef typename val_struct::type type;

		typedef typename val_struct::ref_const ref;
		typedef typename val_struct::ref_const ref_const;

		template <class T>
		static ref_const val(T& t)
		{
			return val_struct::val_const(types::r_if<first>(t.t1, t.t2));
		}
		template <class T>
		static ref_const val_const(const T& t)
		{
			return val_struct::val_const(types::r_if<first>(t.t1, t.t2));
		}
	};

public:
	T1& t1;
	T2& t2;
	join_tuple_sep(T1& t1, T2& t2) : t1(t1), t2(t2) { }

	join_tuple_sep(const join_tuple_sep& o) : t1(o.t1), t2(o.t2) { }



	typedef typename types::t_add_3<types::number<1>,
		typename T1::size_value_type, typename T2::size_value_type>
		::type size_value_type;

	enum { size = size_value_type::value };

	template<int N>
	typename accessor<N>::ref val(types::number<N>) const
	{
		return accessor<N>::val(*this);
	}

	template<int N>
	struct val_t : accessor<N> { };
};

template<class T1, class T2>
join_tuple_sep<const T1, const T2> tplsjoin(const T1& t1, const T2& t2)
{
	return join_tuple_sep<const T1, const T2>(t1, t2);
}

// ----------------------------------------------------------------------------

template<
class T1 = types::skip, class T2 = types::skip,
class T3 = types::skip, class T4 = types::skip,
class T5 = types::skip, class T6 = types::skip,
class T7 = types::skip, class T8 = types::skip,
class T9 = types::skip, class T10 = types::skip >
class tuple
:
public tuple_base<types::t_if<types::t_eq<T1, types::skip>,
		types::number<0>, typename types::t_if<types::t_eq<T2, types::skip>,
		types::number<1>, typename types::t_if<types::t_eq<T3, types::skip>,
		types::number<2>, typename types::t_if<types::t_eq<T4, types::skip>,
		types::number<3>, typename types::t_if<types::t_eq<T5, types::skip>,
		types::number<4>, typename types::t_if<types::t_eq<T6, types::skip>,
		types::number<5>, typename types::t_if<types::t_eq<T7, types::skip>,
		types::number<6>, typename types::t_if<types::t_eq<T8, types::skip>,
		types::number<7>, typename types::t_if<types::t_eq<T9, types::skip>,
		types::number<8>, typename types::t_if<types::t_eq<T10, types::skip>,
		types::number<9>, types::number<10> >
		::type>::type>
		::type>::type>
		::type>::type>
		::type>::type>
		::type>::type::value,
	tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >
{
	typedef typename types::bare_type<T1>::type b1;
	typedef typename types::bare_type<T2>::type b2;
	typedef typename types::bare_type<T3>::type b3;
	typedef typename types::bare_type<T4>::type b4;
	typedef typename types::bare_type<T5>::type b5;
	typedef typename types::bare_type<T6>::type b6;
	typedef typename types::bare_type<T7>::type b7;
	typedef typename types::bare_type<T8>::type b8;
	typedef typename types::bare_type<T9>::type b9;
	typedef typename types::bare_type<T10>::type b10;

	typedef typename internal_details::tpl_ref_type<T1>::cref j1;
	typedef typename internal_details::tpl_ref_type<T2>::cref j2;
	typedef typename internal_details::tpl_ref_type<T3>::cref j3;
	typedef typename internal_details::tpl_ref_type<T4>::cref j4;
	typedef typename internal_details::tpl_ref_type<T5>::cref j5;
	typedef typename internal_details::tpl_ref_type<T6>::cref j6;
	typedef typename internal_details::tpl_ref_type<T7>::cref j7;
	typedef typename internal_details::tpl_ref_type<T8>::cref j8;
	typedef typename internal_details::tpl_ref_type<T9>::cref j9;
	typedef typename internal_details::tpl_ref_type<T10>::cref j10;

public:
	typedef T1 t1;
	typedef T2 t2;
	typedef T3 t3;
	typedef T4 t4;
	typedef T5 t5;
	typedef T6 t6;
	typedef T7 t7;
	typedef T8 t8;
	typedef T9 t9;
	typedef T10 t10;


	typedef tuple_base<types::t_if<types::t_eq<T1, types::skip>,
		types::number<0>, typename types::t_if<types::t_eq<T2, types::skip>,
		types::number<1>, typename types::t_if<types::t_eq<T3, types::skip>,
		types::number<2>, typename types::t_if<types::t_eq<T4, types::skip>,
		types::number<3>, typename types::t_if<types::t_eq<T5, types::skip>,
		types::number<4>, typename types::t_if<types::t_eq<T6, types::skip>,
		types::number<5>, typename types::t_if<types::t_eq<T7, types::skip>,
		types::number<6>, typename types::t_if<types::t_eq<T8, types::skip>,
		types::number<7>, typename types::t_if<types::t_eq<T9, types::skip>,
		types::number<8>, typename types::t_if<types::t_eq<T10, types::skip>,
		types::number<9>, types::number<10> >
		::type>::type>
		::type>::type>
		::type>::type>
		::type>::type>
		::type>::type::value,
	tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> > tuple_base_type;

	typedef typename tuple_base_type::size_value_type size_value_type;

	enum { size = size_value_type::value };

	T1 v1;
	T2 v2;
	T3 v3;
	T4 v4;
	T5 v5;
	T6 v6;
	T7 v7;
	T8 v8;
	T9 v9;
	T10 v10;

	tuple(j1 v1 = b1(), j2 v2 = b2(),
		j3 v3 = b3(), j4 v4 = b4(),
		j5 v5 = b5(), j6 v6 = b6(),
		j7 v7 = b7(), j8 v8 = b8(),
		j9 v9 = b9(), j10 v10 = b10())
		: v1(v1), v2(v2), v3(v3), v4(v4),
			v5(v5), v6(v6), v7(v7), v8(v8),
			v9(v9), v10(v10) {}

	template<int N, class TPL>
	tuple(const tuple_base<N, TPL>& t) :
		v1(t.derived().val(types::number<1>())),
		v2(t.derived().val(types::number<2>())),
		v3(t.derived().val(types::number<3>())),
		v4(t.derived().val(types::number<4>())),
		v5(t.derived().val(types::number<5>())),
		v6(t.derived().val(types::number<6>())),
		v7(t.derived().val(types::number<7>())),
		v8(t.derived().val(types::number<8>())),
		v9(t.derived().val(types::number<9>())),
		v10(t.derived().val(types::number<10>())) {}

	tuple& operator=(const tuple& o)
	{
		types::r_if<types::is_const<T1> >(types::skip(), v1) = o.v1;
		types::r_if<types::is_const<T2> >(types::skip(), v2) = o.v2;
		types::r_if<types::is_const<T3> >(types::skip(), v3) = o.v3;
		types::r_if<types::is_const<T4> >(types::skip(), v4) = o.v4;
		types::r_if<types::is_const<T5> >(types::skip(), v5) = o.v5;
		types::r_if<types::is_const<T6> >(types::skip(), v6) = o.v6;
		types::r_if<types::is_const<T7> >(types::skip(), v7) = o.v7;
		types::r_if<types::is_const<T8> >(types::skip(), v8) = o.v8;
		types::r_if<types::is_const<T9> >(types::skip(), v9) = o.v9;
		types::r_if<types::is_const<T10> >(types::skip(), v10) = o.v10;
		return *this;
	}
/*
	template<class TPL>
	tuple& operator=(const tuple_base<size, TPL>& o)
	{
		v1 = o.derived().v1;
		v2 = o.derived().v2;
		v3 = o.derived().v3;
		v4 = o.derived().v4;
		v5 = o.derived().v5;
		v6 = o.derived().v6;
		v7 = o.derived().v7;
		v8 = o.derived().v8;
		v9 = o.derived().v9;
		v10 = o.derived().v10;
		return *this;
	}
*/
	using tuple_base_type::operator =;
	using tuple_base_type::operator ,;

	void get(b1& o1) { o1 = v1; }
	void get(b1& o1, b2& o2) { o1 = v1; o2 = v2; }
	void get(b1& o1, b2& o2, b3& o3) { o1 = v1; o2 = v2; o3 = v3; }
	void get(b1& o1, b2& o2, b3& o3, b4& o4)
		{ o1 = v1; o2 = v2; o3 = v3; o4 = v4; }
	void get(b1& o1, b2& o2, b3& o3, b4& o4, b5& o5)
		{ o1 = v1; o2 = v2; o3 = v3; o4 = v4; o5 = v5; }
	void get(b1& o1, b2& o2, b3& o3, b4& o4, b5& o5, b6& o6)
		{ o1 = v1; o2 = v2; o3 = v3; o4 = v4; o5 = v5; o6 = v6; }
	void get(b1& o1, b2& o2, b3& o3, b4& o4, b5& o5, b6& o6, b7& o7)
		{ o1 = v1; o2 = v2; o3 = v3; o4 = v4; o5 = v5; o6 = v6; o7 = v7; }
	void get(b1& o1, b2& o2, b3& o3, b4& o4, b5& o5, b6& o6, b7& o7,
				b8& o8)
	{
			o1 = v1; o2 = v2; o3 = v3; o4 = v4; o5 = v5; o6 = v6; o7 = v7;
			o8 = v8;
	}
	void get(b1& o1, b2& o2, b3& o3, b4& o4, b5& o5, b6& o6, b7& o7,
				b8& o8, b9& o9)
	{
			o1 = v1; o2 = v2; o3 = v3; o4 = v4; o5 = v5; o6 = v6; o7 = v7;
			o8 = v8; o9 = v9;
	}
	void get(b1& o1, b2& o2, b3& o3, b4& o4, b5& o5, b6& o6, b7& o7,
				b8& o8, b9& o9, b10& o10)
	{
			o1 = v1; o2 = v2; o3 = v3; o4 = v4; o5 = v5; o6 = v6; o7 = v7;
			o8 = v8; o9 = v9; o10 = v10;
	}

	template<int N>
	typename internal_details::tpl_val<N, tuple>::ref
		val(types::number<N> = types::number<N>())
	{
		return internal_details::tpl_val<N, tuple>::val(*this);
	}
	template<int N>
	typename internal_details::tpl_val<N, const tuple>::ref
		val(types::number<N> = types::number<N>()) const
	{
		return internal_details::tpl_val<N, const tuple>::val(*this);
	}

	template<int N>
	struct val_t : public internal_details::tpl_val<N, tuple> {};

	// second argument is to avoid instantiations thus save compile time
	template<class T, class P = void>
	struct bracket_ref : types::t_if<
		types::is_ivl_array<typename types::bare_type<T>::type>,
		//types::skip,
		types::elem_ref<T>,
		types::t_id<types::skip> >::type { };

	typedef tuple<typename bracket_ref<T1>::type,
		typename bracket_ref<T2>::type,
		typename bracket_ref<T3>::type,
		typename bracket_ref<T4>::type,
		typename bracket_ref<T5>::type,
		typename bracket_ref<T6>::type,
		typename bracket_ref<T7>::type,
		typename bracket_ref<T8>::type,
		typename bracket_ref<T9>::type,
		typename bracket_ref<T10>::type
	> ref_tuple;

/*
	// iavr: apply operator[] to all elements, if arrays
	template<class P>
	tuple<typename bracket_ref<T1, P>::type,
		typename bracket_ref<T2, P>::type,
		typename bracket_ref<T3, P>::type,
		typename bracket_ref<T4, P>::type,
		typename bracket_ref<T5, P>::type,
		typename bracket_ref<T6, P>::type,
		typename bracket_ref<T7, P>::type,
		typename bracket_ref<T8, P>::type,
		typename bracket_ref<T9, P>::type,
		typename bracket_ref<T10, P>::type
	> operator[](P p)
	{
		return ref_tuple(v1[p], v2[p], v3[p], v4[p], v5[p],
							  v6[p], v7[p], v8[p], v9[p], v10[p]);
	};

	// iavr: resize all elements, if arrays
	template<class S>
	void resize(S s)
	{
		v1.resize(s);
		v2.resize(s);
		v3.resize(s);
		v4.resize(s);
		v5.resize(s);
		v6.resize(s);
		v7.resize(s);
		v8.resize(s);
		v9.resize(s);
		v10.resize(s);
	}
*/

	// ref to nc ref
	tuple& ref() { return *this; }
	tuple& operator >> (nc) { return *this; }
};

template<
class T1, class T2,
class T3, class T4,
class T5, class T6,
class T7, class T8,
class T9, class T10>
struct tuple_helper<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> :
	types::t_id<tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> > { };

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

// TODO: best place
template <class T1, int L = 1>
class shift_tuple
: public tuple_base<T1::size - L, shift_tuple<T1> >
{
	template<int N>
	struct accessor
	{
		typedef typename T1::template val_t<N + L> val_struct;

		typedef typename val_struct::type type;
		typedef typename val_struct::ref ref;

		template <class T>
		static ref val(T& t)
		{
			return val_struct::val(t.t1);
		}
	};

public:
	T1& t1;
	shift_tuple(T1& t1) : t1(t1) { }

	typedef types::number<T1::size - L> size_value_type;

	enum { size = size_value_type::value };

	template<int N>
	typename accessor<N>::ref val(types::number<N>) const
	{
		return accessor<N>::val(*this);
	}

	template<int N>
	struct val_t : accessor<N> { };
};

// ----------------------------------------------------------------------------

namespace internal_details {

template<class T>
struct ref_t
{
	T& r;
	operator T&() { return r; }
	ref_t(T& r) : r(r) { }
};

template<class T>
struct reslv
{
	typedef T type;
};

template<class T>
struct reslv<ref_t<T> >
{
	typedef T& type;
};

} /* namespace internal_details */

// ----------------------------------------------------------------------------

template<class T>
internal_details::ref_t<T> ref(T& r)
{
	return r;
}

// ----------------------------------------------------------------------------


template<class T1>
tuple<
		typename internal_details::reslv<T1>::type
	> tpl(T1 t1)
{
	return tuple<
		typename internal_details::reslv<T1>::type
	>(t1);
}

template<class T1, class T2>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type
	> tpl(T1 t1, T2 t2)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type
	>(t1, t2);
}

template<class T1, class T2, class T3>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type
	> tpl(T1 t1, T2 t2, T3 t3)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type
	>(t1, t2, t3);
}

template<class T1, class T2, class T3, class T4>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type
	> tpl(T1 t1, T2 t2, T3 t3, T4 t4)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type
	>(t1, t2, t3, t4);
}

template<class T1, class T2, class T3, class T4, class T5>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type
	> tpl(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type
	>(t1, t2, t3, t4, t5);
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type
	> tpl(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type
	>(t1, t2, t3, t4, t5, t6);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type
	> tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type
	>(t1, t2, t3, t4, t5, t6, t7);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type,
		typename internal_details::reslv<T8>::type
	> tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type,
		typename internal_details::reslv<T8>::type
	>(
		t1, t2, t3, t4, t5, t6, t7, t8);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8, class T9>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type,
		typename internal_details::reslv<T8>::type,
		typename internal_details::reslv<T9>::type
	> tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type,
		typename internal_details::reslv<T8>::type,
		typename internal_details::reslv<T9>::type
	>(
		t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8, class T9, class T10>
tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type,
		typename internal_details::reslv<T8>::type,
		typename internal_details::reslv<T9>::type,
		typename internal_details::reslv<T10>::type
	> tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10)
{
	return tuple<
		typename internal_details::reslv<T1>::type,
		typename internal_details::reslv<T2>::type,
		typename internal_details::reslv<T3>::type,
		typename internal_details::reslv<T4>::type,
		typename internal_details::reslv<T5>::type,
		typename internal_details::reslv<T6>::type,
		typename internal_details::reslv<T7>::type,
		typename internal_details::reslv<T8>::type,
		typename internal_details::reslv<T9>::type,
		typename internal_details::reslv<T10>::type
	>(
		t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
}

#if 0
template<class T1>
tuple<T1>  tpl(T1 t1)
{
	return tuple<T1>(t1);
}

template<class T1, class T2>
tuple<T1, T2>  tpl(T1 t1, T2 t2)
{
	return tuple<T1, T2>(t1, t2);
}

template<class T1, class T2, class T3>
tuple<T1, T2, T3>  tpl(T1 t1, T2 t2, T3 t3)
{
	return tuple<T1, T2, T3>(t1, t2, t3);
}

template<class T1, class T2, class T3, class T4>
tuple<T1, T2, T3, T4>  tpl(T1 t1, T2 t2, T3 t3, T4 t4)
{
	return tuple<T1, T2, T3, T4>(t1, t2, t3, t4);
}

template<class T1, class T2, class T3, class T4, class T5>
tuple<T1, T2, T3, T4, T5>  tpl(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
{
	return tuple<T1, T2, T3, T4, T5>(t1, t2, t3, t4, t5);
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
tuple<T1, T2, T3, T4, T5, T6>  tpl(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
{
	return tuple<T1, T2, T3, T4, T5, T6>(t1, t2, t3, t4, t5, t6);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
tuple<T1, T2, T3, T4, T5, T6, T7>  tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
{
	return tuple<T1, T2, T3, T4, T5, T6, T7>(t1, t2, t3, t4, t5, t6, t7);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8>
tuple<T1, T2, T3, T4, T5, T6, T7, T8>  tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
{
	return tuple<T1, T2, T3, T4, T5, T6, T7, T8>(
		t1, t2, t3, t4, t5, t6, t7, t8);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8, class T9>
tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9>  tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
{
	return tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9>(
		t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8, class T9, class T10>
tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>  tpl(T1 t1,
	T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10)
{
	return tuple<T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(
		t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
}
#endif
// ----


template<class T1>
tuple<T1&>  reftpl(T1& t1)
{
	return tuple<T1&>(t1);
}

template<class T1, class T2>
tuple<T1&, T2&>  reftpl(T1& t1, T2& t2)
{
	return tuple<T1&, T2&>(t1, t2);
}

template<class T1, class T2, class T3>
tuple<T1&, T2&, T3&>  reftpl(T1& t1, T2& t2, T3& t3)
{
	return tuple<T1&, T2&, T3&>(t1, t2, t3);
}

template<class T1, class T2, class T3, class T4>
tuple<T1&, T2&, T3&, T4&>  reftpl(T1& t1, T2& t2, T3& t3, T4& t4)
{
	return tuple<T1&, T2&, T3&, T4&>(t1, t2, t3, t4);
}

template<class T1, class T2, class T3, class T4, class T5>
tuple<T1&, T2&, T3&, T4&, T5&>  reftpl(T1& t1,
	T2& t2, T3& t3, T4& t4, T5& t5)
{
	return tuple<T1&, T2&, T3&, T4&, T5&>(t1, t2, t3, t4, t5);
}

template<class T1, class T2, class T3, class T4, class T5, class T6>
tuple<T1&, T2&, T3&, T4&, T5&, T6&>  reftpl(T1& t1,
	T2& t2, T3& t3, T4& t4, T5& t5, T6& t6)
{
	return tuple<T1&, T2&, T3&, T4&, T5&, T6&>(t1, t2, t3, t4, t5, t6);
}

template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&>  reftpl(T1& t1,
	T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7)
{
	return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&>(t1, t2, t3, t4, t5, t6, t7);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8>
tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&>  reftpl(T1& t1,
	T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8)
{
	return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&>(
		t1, t2, t3, t4, t5, t6, t7, t8);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8, class T9>
tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&>  reftpl(T1& t1,
	T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9)
{
	return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&>(
		t1, t2, t3, t4, t5, t6, t7, t8, t9);
}

template
<class T1, class T2, class T3, class T4, class T5,
 class T6, class T7, class T8, class T9, class T10>
tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&>  reftpl(T1& t1,
	T2& t2, T3& t3, T4& t4, T5& t5, T6& t6, T7& t7, T8& t8, T9& t9, T10& t10)
{
	return tuple<T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&, T9&, T10&>(
		t1, t2, t3, t4, t5, t6, t7, t8, t9, t10);
}

// ---------------

namespace internal_details {

template <int N>
struct apply_tuple_impl { };

template <>
struct apply_tuple_impl<0>
{
	template <class T, class O>
	static inline void operate(T& t, O& o) { o.operate(); }
	template <class T, class O>
	static inline void output(T& t, O& o) { o.output(); }
};

template <>
struct apply_tuple_impl<1>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{ o.operate(t.val(types::number<1>())); }
	template <class T, class O>
	static inline void output(T& t, O& o)
	{ o.output(t.val(types::number<1>())); }
};

template <>
struct apply_tuple_impl<2>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{ o.operate(t.val(types::number<1>()), t.val(types::number<2>())); }
	template <class T, class O>
	static inline void output(T& t, O& o)
	{ o.output(t.val(types::number<1>()), t.val(types::number<2>())); }
};

template <>
struct apply_tuple_impl<3>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(t.val(number<1>()), t.val(number<2>()),
				t.val(number<3>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(t.val(number<1>()), t.val(number<2>()),
				t.val(number<3>()));
	}
};

template <>
struct apply_tuple_impl<4>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()));
	}
};

template <>
struct apply_tuple_impl<5>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()));
	}
};

template <>
struct apply_tuple_impl<6>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()));
	}
};

template <>
struct apply_tuple_impl<7>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()));
	}
};

template <>
struct apply_tuple_impl<8>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()));
	}
};

template <>
struct apply_tuple_impl<9>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()));
	}
};

template <>
struct apply_tuple_impl<10>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()));
	}
};

template <>
struct apply_tuple_impl<11>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()));
	}
};

template <>
struct apply_tuple_impl<12>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()));
	}
};

template <>
struct apply_tuple_impl<13>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()),
				t.val(number<13>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()),
				t.val(number<13>()));
	}
};

template <>
struct apply_tuple_impl<14>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()),
				t.val(number<13>()), t.val(number<14>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()),
				t.val(number<13>()), t.val(number<14>()));
	}
};

template <>
struct apply_tuple_impl<15>
{
	template <class T, class O>
	static inline void operate(T& t, O& o)
	{
		using namespace types;
		o.operate(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()),
				t.val(number<13>()), t.val(number<14>()), t.val(number<15>()));
	}
	template <class T, class O>
	static inline void output(T& t, O& o)
	{
		using namespace types;
		o.output(
				t.val(number<1>()), t.val(number<2>()), t.val(number<3>()),
				t.val(number<4>()), t.val(number<5>()), t.val(number<6>()),
				t.val(number<7>()), t.val(number<8>()), t.val(number<9>()),
				t.val(number<10>()), t.val(number<11>()), t.val(number<12>()),
				t.val(number<13>()), t.val(number<14>()), t.val(number<15>()));
	}
};

} /* namespace internal_details */

template <class T, class O>
void apply_tuple(T& t, O& o)
{
	internal_details::apply_tuple_impl<T::size>::operate(t, o);
};
template <class T, class O>
void apply_tuple(const T& t, O& o)
{
	internal_details::apply_tuple_impl<T::size>::operate(t, o);
};
template <class T, class O>
void apply_tuple_output(T& t, O& o)
{
	internal_details::apply_tuple_impl<T::size>::output(t, o);
};

} /* namespace internal */

using tuple;

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TOOL_INTERNAL_HPP
