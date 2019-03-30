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

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_DETAILS_FUNC_REDUCE_HPP
#define IVL_CORE_DETAILS_FUNC_REDUCE_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace seq_details {

using keys::key_val;
using types::maps::id;
using types::maps::fixed;

//-----------------------------------------------------------------------------

namespace acc {

// accumulator type specifiers
template <class E, class S>
struct scalar : public id<E> { };

template <class E, class S>
struct array { typedef ivl::array<E> type; };

}  // namespace acc

//-----------------------------------------------------------------------------

namespace init {

struct none {
	template <class A, class C>
	void operator()(A& s, const C& a) const { }
};

struct reserve {
	template <class A, class C>
	void operator()(A& s, const C& a) const
	{
		s.reserve(a.length());
	}
};

}  // namespace init

//-----------------------------------------------------------------------------

namespace term {

struct none {
	template <class A, class C, class I>
	bool operator()(const A& s, const C& a, const I& i) const { return false; }
};

}  // namespace term

//-----------------------------------------------------------------------------

namespace alloc {

struct capacity {
	size_t k;
	capacity(const size_t k) : k(k) { }

	// init operator
	template <class A, class C>
	void operator()(A& s, const C& a) const
	{
		s.reserve(std::min(a.length(), k));
	}

	// term operator
	template <class A, class C, class I>
	bool operator()(const A& s, const C& a, const I& i) const
	{
		return s.length() >= k;
	}
};

}  // namespace alloc

//-----------------------------------------------------------------------------

namespace dom {

template <bool BEGIN>
struct ex { };

template <>
struct ex <true> {
	template<class C>
	size_t operator()(const C& a) const { return 0; }
};

template <>
struct ex <false> {
	template<class C>
	size_t operator()(const C& a) const { return a.length() - 1; }
};

//-----------------------------------------------------------------------------

template <bool SPEC, bool FWD, bool BEGIN>
struct extr { };

// default begin/end
template<bool FWD, bool BEGIN>
struct extr <false, FWD, BEGIN> {
	extr() { }
	extr(const extr <false, !FWD, BEGIN>&) { }
	template<class C>
	size_t operator()(const C& a) const { return ex <FWD == BEGIN> ()(a); }
};

// specified begin/end
template<bool FWD, bool BEGIN>
struct extr <true, FWD, BEGIN> {
	const size_t val;
	extr(size_t v) : val(v) { }
	extr(const extr <true, !FWD, BEGIN>& e) : val(e.val) { }
	template<class C>
	size_t operator()(const C& a) const { return val; }
};

//-----------------------------------------------------------------------------

template <bool FWD>
inline void nx(size_t& n, const size_t val = 1);

template <>
inline void nx <true>(size_t& n, const size_t val) { n += val; }

template <>
inline void nx <false>(size_t& n, const size_t val) { n -= val; }

//-----------------------------------------------------------------------------

template <bool SPEC, bool FWD>
struct nxt { };

// default step
template<bool FWD>
struct nxt <false, FWD> {
	nxt() { }
	nxt(const nxt <false, !FWD>&) { }
	size_t step() const { return 1; }
	inline void operator()(size_t& n) const { nx <FWD> (n); }
};

// specified step
template <bool FWD>
struct nxt <true, FWD> {
	const size_t val;
	nxt(size_t v) : val(v) { }
	nxt(const nxt <true, !FWD>& n) : val(n.val) { }
	size_t step() const { return val; }
	inline void operator()(size_t& n) const { nx <FWD> (n, val); }
};

//-----------------------------------------------------------------------------

template <bool STP, bool FWD>
struct past { };

// default step forward
template <>
struct past <false, true> {
	size_t operator()(const size_t, const size_t e, const size_t) const
	{
		return e + 1;
	}
};

// default step reverse
template <>
struct past <false, false> {
	size_t operator()(const size_t, const size_t e, const size_t) const
	{
		return e - 1;
	}
};

// specified step forward
template <>
struct past <true, true> {
	size_t operator()(const size_t b, const size_t e, const size_t s) const
	{
		return b + ((e - b) / s + 1) * s;
	}
};

// specified step reverse
template <>
struct past <true, false> {
	size_t operator()(const size_t b, const size_t e, const size_t s) const
	{
		return b - ((b - e) / s + 1) * s;
	}
};

//-----------------------------------------------------------------------------
// random access domain

template <bool BEG = false, bool END = false, bool STP = false,
	bool FWD = true>
struct ra {
	typedef extr <BEG, FWD, true> B;
	typedef extr <END, FWD, false> E;
	typedef nxt <STP, FWD> N;

	typedef size_t iterator;

	const B begin;
	const E last;
	const N next;

	ra(const B& b = B(), const E& e = E(), const N& n = N()) :
		begin(b), last(e), next(n) { }

	inline size_t& operator[](size_t& n) const { return n; }

	// last(a) is the requested last element to visit
	// end(a) is one past the actual last element to visit
	template<class C>
	size_t end(const C& a) const
	{
		return past <STP, FWD>()(begin(a), last(a), next.step());
	}

	template <class D, class B>
	D gen_b(const B& b) const { return D(typename D::B(b), last, next); }

	template <class D, class E>
	D gen_e(const E& e) const { return D(begin, typename D::E(e), next); }

	template <class D, class S>
	D gen_s(const S& s) const { return D(begin, last, typename D::N(s)); }

	template <class D>
	D gen() const { return D(begin, last, next); }
};

}  // namespace dom

//-----------------------------------------------------------------------------

namespace in {

struct elem { };
struct off { };
struct ar { };

}  // namespace in

//-----------------------------------------------------------------------------

namespace out {

template <class T_IN, bool COND>
struct ref { };

template <>
struct ref <in::elem, false> {
	template <class OP, class A, class C, class I>
	void operator()(OP& op, A& s, const C& a, const I& i) const {
		op(s, a[i]);
	}
};

template <>
struct ref <in::elem, true> {
	template <class OP, class A, class C, class I>
	bool operator()(OP& op, A& s, const C& a, const I& i) const {
		return op(s, a[i]);
	}
};

template <>
struct ref <in::off, false> {
	template <class OP, class A, class C, class I>
	void operator()(OP& op, A& s, const C& a, const I& i) const {
		op(s, a[i], i);
	}
};

template <>
struct ref <in::off, true> {
	template <class OP, class A, class C, class I>
	bool operator()(OP& op, A& s, const C& a, const I& i) const {
		return op(s, a[i], i);
	}
};

template <>
struct ref <in::ar, false> {
	template <class OP, class A, class C, class I>
	void operator()(OP& op, A& s, const C& a, const I& i) const {
		op(s, a, i);
	}
};

template <>
struct ref <in::ar, true> {
	template <class OP, class A, class C, class I>
	bool operator()(OP& op, A& s, const C& a, const I& i) const {
		return op(s, a, i);
	}
};

//-----------------------------------------------------------------------------

template <class T_IN, bool COND>
struct assign { };

template <bool COND>
struct assign <in::elem, COND> {
	template <class OP, class A, class C, class I>
	void operator()(OP& op, A& s, const C& a, const I& i) const {
		s = op(s, a[i]);
	}
};

template <bool COND>
struct assign <in::off, COND> {
	template <class OP, class A, class C, class I>
	void operator()(OP& op, A& s, const C& a, const I& i) const {
		s = op(s, a[i], i);
	}
};

template <bool COND>
struct assign <in::ar, COND> {
	template <class OP, class A, class C, class I>
	void operator()(OP& op, A& s, const C& a, const I& i) const {
		s = op(s, a, i);
	}
};

}  // namespace out

//-----------------------------------------------------------------------------

template <bool COND>
struct loop { };

template <>
struct loop <false> {
	template <class APP, class OP, class A, class C, class DOM, class TERM>
	void operator()(const APP& app, OP& op, A& s, const C& a,
						 const DOM& dom, const TERM& term) const
	{
		typedef typename DOM::iterator IT;

		for (IT i = dom.begin(a), end = dom.end(a); i != end; dom.next(i))
		{
			app(op, s, a, dom[i]);
			if(term(s, a, dom[i])) return;
		}
	}
};

template <>
struct loop <true> {
	template <class APP, class OP, class A, class C, class DOM, class TERM>
	void operator()(const APP& app, OP& op, A& s, const C& a,
						 const DOM& dom, const TERM& term) const
	{
		typedef typename DOM::iterator IT;

		for (IT i = dom.begin(a), end = dom.end(a); i != end; dom.next(i))
		{
			if(app(op, s, a, dom[i])) return;
			if(term(s, a, dom[i])) return;
		}
	}
};

//-----------------------------------------------------------------------------

template<
	class OP, class DEF,
    template <typename, bool> class T_OUT,
	template <typename, typename> class ACC,
	class INIT, class TERM,
	template <typename> class ELEM,
    class T_IN, bool COND, class DOM
>
class seq_impl
{
	typedef loop<COND> LOOP;
    typedef T_OUT<T_IN, COND> IO;

	template <class T, class S>
	struct acc {
		typedef typename ACC<typename ELEM<T>::type, S>::type type;
	};

	OP& op;
	const DEF& def;
	const INIT init;
	const TERM term;
	const DOM dom;

	// accumulator given to work on
	template <class T, class S>
	typename acc<T, S>::type
	operator()(typename acc<T, S>::type& s, const array<T, S>& a) const
	{
		init(s, a);
		LOOP()(IO(), op, s, a, dom, term);
		return s;
	}

public:

	seq_impl(OP& o, const DEF& df, const INIT& i, const TERM& t, const DOM& d)
		: op(o), def(df), init(i), term(t), dom(d) { }

	// default: new accumulator
	template <class T, class S>
	typename acc<T, S>::type
	operator()(const array<T, S>& a) const
	{
		typedef typename acc<T, S>::type A;
		A s = def(A());
		return (*this)(s, a);
	}

	// accumulator given to initialize only
	template <class T, class S>
	typename acc<T, S>::type
	operator()(const array<T, S>& a, const typename acc<T, S>::type& si) const
	{
		typename acc<T, S>::type s(si);
		return (*this)(s, a);
	}
};

//-----------------------------------------------------------------------------
// level 0, generic

template <
    template <typename, bool> class T_OUT,
	template <typename, typename> class ACC,
	class INIT, class TERM,
	template <typename> class ELEM,
    class T_IN, bool COND, class DOM,
	template <
		template <typename, bool> class,
		template <typename, typename> class,
		typename, typename,
		template <typename> class,
		typename, bool, typename
	> class DERIVED
>
class seq_call_0
{
	// some operator[] is required because seq_call is using operator[] of
	// seq_call_base specializations. so we define an inaccessible one.
	struct X { };

public:
	void operator[](X) { }
};

//-----------------------------------------------------------------------------
// level 0, specialized over T_OUT

template <
    /* template <typename, bool> class T_OUT, */
	template <typename, typename> class ACC,
	class INIT, class TERM,
	template <typename> class ELEM,
    class T_IN, bool COND, class DOM,
	template <
		template <typename, bool> class,
		template <typename, typename> class,
		typename, typename,
		template <typename> class,
		typename, bool, typename
	> class DERIVED
>
class seq_call_0 <out::ref, ACC, INIT, TERM, ELEM, T_IN, COND, DOM, DERIVED>
{
    typedef DERIVED<out::ref, ACC, INIT, TERM, ELEM, T_IN, COND, DOM> DER;

	DER& der() { return static_cast <DER&> (*this); }

	// loop type
    typedef DERIVED<out::ref, ACC, INIT, TERM, ELEM, T_IN, false, DOM>
		CALL_free;
    typedef DERIVED<out::ref, ACC, INIT, TERM, ELEM, T_IN, true, DOM>
		CALL_cond;

public:

	// free loop
	CALL_free operator[](key::free) { return der().template gen<CALL_free>(); }

	// conditional loop
	CALL_cond operator[](key::cond) { return der().template gen<CALL_cond>(); }
};

//-----------------------------------------------------------------------------
// level 1, generic

template <
    template <typename, bool> class T_OUT,
	template <typename, typename> class ACC,
	class INIT, class TERM,
	template <typename> class ELEM,
    class T_IN, bool COND, class DOM,
	template <
		template <typename, bool> class,
		template <typename, typename> class,
		typename, typename,
		template <typename> class,
		typename, bool, typename
	> class DERIVED
>
class seq_call_1 : public
    seq_call_0 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM, DERIVED>
{
	struct X { };

public:
	void operator[](X) { }
};

//-----------------------------------------------------------------------------
// level 1, specialized over INIT

template <
    template <typename, bool> class T_OUT,
	template <typename, typename> class ACC,
	/* class INIT, */ class TERM,
	template <typename> class ELEM,
    class T_IN, bool COND, class DOM,
	template <
		template <typename, bool> class,
		template <typename, typename> class,
		typename, typename,
		template <typename> class,
		typename, bool, typename
	> class DERIVED
>
class seq_call_1 <T_OUT, ACC, init::reserve, TERM, ELEM, T_IN, COND, DOM,
	DERIVED> : public
    seq_call_0 <T_OUT, ACC, init::reserve, TERM, ELEM, T_IN, COND, DOM,
	DERIVED>
{
    typedef DERIVED<T_OUT, ACC, init::reserve, TERM, ELEM, T_IN, COND,
		DOM> DER;

	DER& der() { return static_cast <DER&> (*this); }

	// accumulator capacity
    typedef DERIVED<T_OUT, ACC, alloc::capacity, alloc::capacity, ELEM,
        T_IN, COND, DOM>
		CALL_max;

public:

	// specified max capacity accumulator
	template <class V>
	CALL_max operator[](const key_val <key::max, V>& k)
	{
		return der().template gen_it<CALL_max>(alloc::capacity(*k));
	}
};

//-----------------------------------------------------------------------------
// level 2, generic

template <
    template <typename, bool> class T_OUT,
	template <typename, typename> class ACC,
	class INIT, class TERM,
	template <typename> class ELEM,
    class T_IN, bool COND, class DOM,
	template <
		template <typename, bool> class,
		template <typename, typename> class,
		typename, typename,
		template <typename> class,
		typename, bool, typename
	> class DERIVED
>
class seq_call_2 : public
    seq_call_1 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM, DERIVED>
{
	struct X { };

public:
	void operator[](X) { }
};

//-----------------------------------------------------------------------------
// level 2, specialized over DOM

template <
    template <typename, bool> class T_OUT,
	template <typename, typename> class ACC,
	class INIT, class TERM,
	template <typename> class ELEM,
    class T_IN, bool COND, /* class DOM, */
	bool BEG, bool END, bool STP, bool FWD,
	template <
		template <typename, bool> class,
		template <typename, typename> class,
		typename, typename,
		template <typename> class,
		typename, bool, typename
	> class DERIVED
>
class seq_call_2 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND,
		dom::ra <BEG, END, STP, FWD>, DERIVED>
	: public
        seq_call_1 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND,
		dom::ra <BEG, END, STP, FWD>, DERIVED>
{
	typedef dom::ra <BEG, END, STP, FWD> D;
    typedef DERIVED <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, D> DER;

	DER& der() { return static_cast <DER&> (*this); }
	const D& d() { return der().dom; }

	typedef dom::ra <true, END, STP, FWD> D_B;
    typedef DERIVED <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, D_B> DER_B;

	typedef dom::ra <BEG, true, STP, FWD> D_E;
    typedef DERIVED <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, D_E> DER_E;

	typedef dom::ra <BEG, END, true, FWD> D_S;
    typedef DERIVED <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, D_S> DER_S;

	typedef dom::ra <BEG, END, STP, FWD> D_F;
    typedef DERIVED <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, D_F> DER_F;

	typedef dom::ra <BEG, END, STP, false> D_R;
    typedef DERIVED <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, D_R> DER_R;

public:

	// begin position
	template <class V>
	DER_B operator[](const key_val<key::begin, V>& b)
	{
		return der().template gen_d<DER_B>(der().dom.template gen_b<D_B>(*b));
	}

	// end position
	template <class V>
	DER_E operator[](const key_val<key::end, V>& e)
	{
		return der().template gen_d<DER_E>(der().dom.template gen_e<D_E>(*e));
	}

	// step
	template <class V>
	DER_S operator[](const key_val<key::step, V>& s)
	{
		return der().template gen_d<DER_S>(der().dom.template gen_s<D_S>(*s));
	}

	// forward iteration
	DER_F operator[](key::fwd)
	{
		return der().template gen_d<DER_F>(der().dom.template gen<D_F>());
	}

	// reverse iteration
	DER_R operator[](key::rev)
	{
		return der().template gen_d<DER_R>(der().dom.template gen<D_R>());
	}
};

//-----------------------------------------------------------------------------
// level 3

template <
    template <typename, bool> class T_OUT = out::ref,
	template <typename, typename> class ACC = acc::scalar,
	class INIT = init::none, class TERM = term::none,
	template <typename> class ELEM = id,
    class T_IN = in::elem, bool COND = false,
	class DOM = dom::ra<>
>
class seq_call : public
    seq_call_2 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM, seq_call>
{
    typedef seq_call_0 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM,
		ivl::seq_details::seq_call> P0;
    typedef seq_call_1 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM,
		ivl::seq_details::seq_call> P1;
    typedef seq_call_2 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM,
		ivl::seq_details::seq_call> P2;

	// typedef'd friends not allowed
    friend class seq_call_0 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM,
		ivl::seq_details::seq_call>;
    friend class seq_call_1 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM,
		ivl::seq_details::seq_call>;
    friend class seq_call_2 <T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM,
		ivl::seq_details::seq_call>;

	template <class C, class IT>
	C gen_it(const IT& it) const { return C(it, it, dom); }

	template <class C, class I, class T>
	C gen_it(const I& i, const T& t) const { return C(i, t, dom); }

	template <class C, class D>
	C gen_d(const D& d) const { return C(init, term, d); }

	template <class C>
	C gen() const { return C(init, term, dom); }

	template <class OP, class DEF>
	struct impl {
        typedef seq_impl<OP, DEF, T_OUT, ACC, INIT, TERM, ELEM, T_IN, COND, DOM>
			type;
	};

	// output syntax
    typedef seq_call <out::ref, ACC, INIT, TERM, ELEM, T_IN, COND, DOM>
		CALL_ref;
    typedef seq_call <out::assign, ACC, INIT, TERM, ELEM, T_IN, false, DOM>
		CALL_assign;

	// output type
    typedef seq_call <T_OUT, ACC, INIT, TERM, id, T_IN, COND, DOM>
		CALL_val;
    typedef seq_call <T_OUT, ACC, INIT, TERM, fixed<bool>::map, T_IN, COND, DOM>
		CALL_yn;
    typedef seq_call <T_OUT, ACC, INIT, TERM, fixed<size_t>::map, T_IN, COND, DOM>
		CALL_sz;

	// op input
    typedef seq_call <T_OUT, ACC, INIT, TERM, ELEM, in::elem, COND, DOM>
		CALL_elem;
    typedef seq_call <T_OUT, ACC, INIT, TERM, ELEM, in::off, COND, DOM>
		CALL_off;
    typedef seq_call <T_OUT, ACC, INIT, TERM, ELEM, in::ar, COND, DOM>
		CALL_ar;

	// identity default initializer
	typedef fun::id ID;

	const INIT init;
	const TERM term;
	const DOM dom;

public:

	using P0::operator[];
	using P1::operator[];
	using P2::operator[];

	seq_call(const INIT& i = INIT(), const TERM& t = TERM(),
				const DOM& d = DOM())
		: init(i), term(t), dom(d) { }

	// main call given functor
	template <class OP>
	typename impl <OP, ID>::type operator()(OP& op)
	{
		return typename impl<OP, ID>::type(op, ivl::id, init, term, dom);
	}

	// main call given functor and default initializer
	template <class OP, class DEF>
	typename impl <OP, DEF>::type operator()(OP& op, const DEF& def)
	{
		return typename impl <OP, DEF>::type(op, def, init, term, dom);
	}

	// use accumulator non-const reference
	CALL_ref operator[](key::ref) { return this->template gen <CALL_ref>(); }

	// use accumulator const reference + assign new accumulator value
	CALL_assign operator[](key::assign) { return this->template gen <CALL_assign>(); }

	// return value
	CALL_val operator[](key::val) { return this->template gen <CALL_val>(); }

	// return yes/no (bool)
	CALL_yn operator[](key::yn) { return this->template gen <CALL_yn>(); }

	// return offset/size (size_t)
	CALL_sz operator[](key::sz) { return this->template gen <CALL_sz>(); }

	// return arbitrary type
	template <class T>
    seq_call <T_OUT, ACC, INIT, TERM, fixed<T>::template map, T_IN, COND, DOM>
	operator[](const T&) { return this->template
        gen <seq_call <T_OUT, ACC, INIT, TERM, fixed<T>::template map, T_IN, COND, DOM> >(); }

	// op input is element only
	CALL_elem operator[](key::elem) { return this->template gen <CALL_elem>(); }

	// op input is element + offset
	CALL_off operator[](key::off) { return this->template gen <CALL_off>(); }

	// op input is entire array + offset
	CALL_ar operator[](key::arr) { return this->template gen <CALL_ar>(); }
};

//-----------------------------------------------------------------------------

typedef seq_call<> reduce_impl;
typedef seq_call<out::ref, acc::array, init::reserve> collect_impl;

//-----------------------------------------------------------------------------

}  // namespace seq_details

//-----------------------------------------------------------------------------

static  __attribute__ ((unused)) seq_details::reduce_impl  reduce;
static  __attribute__ ((unused)) seq_details::collect_impl collect;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_FUNC_REDUCE_HPP
