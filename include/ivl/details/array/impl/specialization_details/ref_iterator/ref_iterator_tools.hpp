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

#ifndef IVL_ARRAY_SPECIALIZATION_DETAILS_REF_ITERATOR_TOOLS_HPP
#define IVL_ARRAY_SPECIALIZATION_DETAILS_REF_ITERATOR_TOOLS_HPP

namespace ivl {

namespace array_details {

template <class A, class IS_PTR_CAPABLE>
struct ref_iterator_from_array_3 { };

template <class A>
struct ref_iterator_from_array_3<A, types::t_true>
{
	typedef typename types::apply_const<
		typename A::elem_type, typename types::is_const<A>::type>::type *ptr_t;
	static inline ptr_t begin_raw(A& a) { return &*a.begin(); } //@@@@
	static inline ptr_t end_raw(A& a) { return &*a.end(); } //@@@ changed to &*
};

template <class A>
struct ref_iterator_from_array_3<A, types::t_false>
{
	typedef typename types::apply_const<
		typename A::elem_type, typename types::is_const<A>::type>::type *ptr_t;
	static inline ptr_t begin_raw(A& a) { return a.c_ptr(); }
	static inline ptr_t end_raw(A& a) { return a.c_ptr() + a.length(); }
};

template <class A, class HAS_C_PTR>
struct ref_iterator_from_array_2  { };

template <class A>
struct ref_iterator_from_array_2<A, types::t_true>
	: public ref_iterator_from_array_3<A, typename
	data::iterator_extended_traits<typename A::const_iterator>
	::is_pointer_capable>
{
};

template <class A>
struct ref_iterator_from_array_2<A, types::t_false>
{
	typedef typename types::best_iterator<A>::type ptr_t;
	static inline ptr_t begin_raw(A& a) { return a.begin(); }
	static inline ptr_t end_raw(A& a) { return a.end(); }
};

template <class A>
struct ref_iterator_from_array_2<const A, types::t_false>
{
	typedef typename A::const_iterator ptr_t;
	static inline ptr_t begin_raw(A& a) { return a.begin(); }
	static inline ptr_t end_raw(A& a) { return a.end(); }
};

// -----------------------------------------------------------

// given a a reference of array type A, or const A, defines two methods,
// begin_raw() and end_raw() which will try to get a pointer to begin()
// instead of the begin() iterator if our ref_iterator array needs one
template <class A, class NEED_PTR>
struct ref_iterator_from_array { };

template <class A>
struct ref_iterator_from_array<A, types::t_true> :
public ref_iterator_from_array_2<A, typename A::has_c_ptr>
{ };

template <class A>
struct ref_iterator_from_array<const A, types::t_true> :
public ref_iterator_from_array_2<const A, typename A::has_c_ptr>
{ };

template <class A>
struct ref_iterator_from_array<A, types::t_false> :
public ref_iterator_from_array_2<A, types::t_false>
{ };

// -----------------------------------------------------------

template <class K>
struct ref_iterator_memmanage
{
	typedef types::skip store_type;
	template<class T>
	static inline void destroy(store_type, T) { }
};

// -----------------------------------------------------------

template <>
struct ref_iterator_memmanage<ivl::data::deletable_c_ptr>
{
	typedef bool store_type;
	template<class T>
	static inline void destroy(store_type b, T* ptr)
	{
		if(b)
			::free((void*)ptr);
	}
};

// -----------------------------------------------------------

template<class C, class CONST_IT>
struct ref_iterator_add_const_it
{
private:
	const C& as_array() const { return static_cast<const C&>(*this); }
public:
	typedef CONST_IT const_iterator;
	typedef std::reverse_iterator<CONST_IT> const_reverse_iterator;

	const_iterator begin() const { return const_iterator(as_array().base_ptr); }
	const_iterator end() const
		{ return const_iterator(as_array().get_it_end(as_array().end_iter)); }
	const_reverse_iterator rbegin() const { return end(); }
	const_reverse_iterator rend() const { return begin(); }
};

template<class C>
struct ref_iterator_add_const_it<C, types::term>
{
	class not_a_type{};
	void begin(not_a_type) const {}
	void end(not_a_type) const {}
	void rbegin(not_a_type) const {}
	void rend(not_a_type) const {}
};

template<class C, class IT>
struct ref_iterator_add_write_it
{
private:
	C& as_array() { return static_cast<C&>(*this); }
public:
	typedef IT iterator;
	typedef std::reverse_iterator<IT> reverse_iterator;

	iterator begin()
		{ return iterator(as_array().base_ptr); }
	iterator end()
		{ return iterator(as_array().get_it_end(as_array().end_iter)); }
	reverse_iterator rbegin() { return end(); }
	reverse_iterator rend() { return begin(); }
};


template<class C>
struct ref_iterator_add_write_it<C, types::term>
{
	class not_a_type{};
	void begin(not_a_type) {}
	void end(not_a_type) {}
	void rbegin(not_a_type) {}
	void rend(not_a_type) {}
};

template<class C, class CONST_IT, class HAS_RND_ACCESS>
struct ref_iterator_add_const_rnd_op
{
private:
	const C& as_array() const { return static_cast<const C&>(*this); }
protected:
	template <class X>
	static inline X rnd_add(const X& x, size_t y) { return x + y; }
	template <class X>
	static inline size_t rnd_sub(const X& x, const X& y) { return x - y; }
public:
	//! Returns the element found at position offset
	typename std::iterator_traits<CONST_IT>
		::reference operator[](size_t offset) const
	{
		CHECK(offset >= 0 && offset < as_array().length(), erange);
		return as_array().base_ptr[offset];
	}
};

template<class C, class D>
struct ref_iterator_add_const_nonrnd_op
{
protected:
	template <class X>
	static inline X rnd_add(X& x, size_t y) { return x; }
	template <class X>
	static inline size_t rnd_sub(const X& x, const X& y) { return 0; }
public:
	class not_a_type{};
	void operator[](not_a_type) const {}
};

template<class C, class D>
struct ref_iterator_add_const_rnd_op<C, types::term, D>
: public ref_iterator_add_const_nonrnd_op<C, D> { };

template<class C, class D>
struct ref_iterator_add_const_rnd_op<C, D, types::t_false>
: public ref_iterator_add_const_nonrnd_op<C, D> { };


template<class C, class IT, class HAS_RND_ACCESS>
struct ref_iterator_add_write_rnd_op
{
private:
	C& as_array() { return static_cast<C&>(*this); }
public:
	//! Returns the element found at position offset
	typename std::iterator_traits<IT>::reference operator[](size_t offset)
	{
		CHECK(offset >= 0 && offset < as_array().length(), erange);
		return as_array().base_ptr[offset];
	}
};

template<class C, class D>
struct ref_iterator_add_write_rnd_op<C, types::term, D>
{
	class not_a_type {};
	void operator[](not_a_type) {}
};

template<class C, class D>
struct ref_iterator_add_write_rnd_op<C, D, types::t_false>
{
	class not_a_type {};
	void operator[](not_a_type) {}
};

template <class ITER>
struct ref_iterator_iter_traits
{
	typedef typename std::iterator_traits<ITER>
		::iterator_category iterator_category;

	typedef typename std::iterator_traits<ITER>::reference reference;
};

template <>
struct ref_iterator_iter_traits<types::term>
{
	typedef types::term iterator_category;
	typedef types::term reference;
};

// class that gets information about the actual iterators
// that are going to be used for the array.
template <class IT, class CONST_IT, class T>
struct ref_iterator_traits
{
protected:
	typedef typename types::t_or<
		types::t_and<types::t_eq<IT, types::term>,
			types::t_eq<CONST_IT, types::term> >,
		types::t_and<
			types::t_eq<IT, types::not_a_type>,
			types::t_eq<CONST_IT, types::term> > >::
		type use_ptr;

	typedef typename types::t_and<
		types::t_eq<IT, types::term>, types::t_eq<CONST_IT, types::term> >
		::type both_term;

	typedef typename types::t_if<use_ptr, typename types::t_if<
		both_term, T*, const T*>::type, IT>::type it;

	typedef typename types::t_if<use_ptr, const T*, CONST_IT>::type const_it;

public:
	// -- wr_best_it
	typedef typename types::t_if<types::t_eq<it, types::term>,
		const_it, it>::type wr_best_itb;

	typedef typename types::t_if<types::is_ivl_array<wr_best_itb>,
		wr_best_itb, ivl::array<int, data::empty<> > >
		::type wr_best_ita;

	typedef typename types::t_if<types::is_ivl_array<wr_best_itb>,
		typename types::best_iterator<wr_best_ita>::type, wr_best_itb>
			::type wr_best_it;

	typedef ref_iterator_iter_traits<wr_best_it> wr_best_traits;

	typedef typename types::t_if<
		types::is_const<typename wr_best_traits::reference>,
		types::t_false, types::t_true>::type wr_has_write;

	// -- wr_secondary_it
	typedef typename types::t_if<types::t_eq<it, types::term>,
		types::term, typename
			types::t_if<types::t_eq<it, const_it>, types::term, const_it>::type
			>::type wr_secondary_itb;

	typedef typename types::t_if<types::t_and<
		types::is_ivl_array<wr_best_itb>, wr_has_write>,
		typename wr_best_ita::const_iterator, wr_secondary_itb>
			::type wr_secondary_it;

	typedef typename types::t_if<types::t_eq<types::term, wr_secondary_it>,
		wr_best_it, wr_secondary_it>::type wr_secondary_it_always_exist;

	typedef ref_iterator_iter_traits<wr_secondary_it_always_exist>
		wr_secondary_traits;

	// -- rest information
	typedef typename types::t_if<wr_has_write,
		wr_best_it, types::term>::type wr_write_it;

	typedef typename types::t_if<wr_has_write,
		wr_secondary_it_always_exist, wr_best_it>::type wr_const_it;

	typedef typename types::t_if<types::t_eq<wr_const_it, types::term>,
		types::t_false, types::t_true>::type wr_has_const;

	typedef typename types::t_if<
		types::t_eq<typename wr_best_traits::iterator_category,
			std::random_access_iterator_tag>,
			types::t_true, types::t_false>::type
				wr_has_random_access;

};

template <class C, class HAS_RND_ACCESS, class CONST_IT, class WRITE_IT>
struct ref_iterator_extender_base :
public
	ref_iterator_add_const_it<C, CONST_IT>,
public
	ref_iterator_add_write_it<C, WRITE_IT>,
public
	ref_iterator_add_const_rnd_op<C, CONST_IT, HAS_RND_ACCESS>,
public
	ref_iterator_add_write_rnd_op<C, WRITE_IT, HAS_RND_ACCESS>
{
	using ref_iterator_add_const_it<C, CONST_IT>::begin;
	using ref_iterator_add_const_it<C, CONST_IT>::end;
	using ref_iterator_add_const_it<C, CONST_IT>::rbegin;
	using ref_iterator_add_const_it<C, CONST_IT>::rend;
	using ref_iterator_add_write_it<C, WRITE_IT>::begin;
	using ref_iterator_add_write_it<C, WRITE_IT>::end;
	using ref_iterator_add_write_it<C, WRITE_IT>::rbegin;
	using ref_iterator_add_write_it<C, WRITE_IT>::rend;
	using ref_iterator_add_const_rnd_op<C, CONST_IT, HAS_RND_ACCESS>
		::operator[];
	using ref_iterator_add_write_rnd_op<C, WRITE_IT, HAS_RND_ACCESS>
		::operator[];
};

template <
	class C,
	class A,
	class PTR_RANGED_ITERS,
	class C_AND_A_HAS_CPTR,
	class C_REFERS_ARRAY,
	class DISABLE
>
struct ref_iterator_overlap
{
	static inline bool overlap(const C& c, const A& a) { return false; }
};

template <class C, class A, class E, class F>
struct ref_iterator_overlap<C, A,
	E, types::t_true, F, types::t_false>
{
	// pointer region overlapping test.
	static inline bool overlap(const C& c, const A& a)
	{
		// simple pointer range intersection.
		ptrdiff_t d = c.c_ptr() - a.c_ptr();
		return ((d > -ptrdiff_t(c.length())) && (d < ptrdiff_t(a.length())));
	}
};

template <class C, class A, class E>
struct ref_iterator_overlap<C, A,
	types::t_true, types::t_false, E, types::t_false>
{
	static inline bool overlap(const C& c, const A& a)
	{
		// simple pointer range intersection.
		return &(*c.begin()) <= &(*a.end()) && &(*a.begin()) <= &(*c.end());
	}
};

template <class C, class A>
struct ref_iterator_overlap<C, A,
	types::t_false, types::t_false, types::t_true, types::t_false>
{
	static inline bool overlap(const C& c, const A& a)
	{
		return c.begin().owner().overlap(a);
	}
};

template <class C, class A, class E, class F, class G>
struct ref_iterator_overlap<C, A, E, F, G, types::t_false>
{
	static inline bool overlap(const C& c, const A& a)
	{
		return false;
	}
};
//---

template <class C, class T, class HAS_C_PTR> struct ref_iterator_add_c_ptr { };

template <class C, class T>
struct ref_iterator_add_c_ptr<C, T*, types::t_true>
{
private:
	C& as_array() { return static_cast<C&>(*this); }
	const C& as_array() const { return static_cast<const C&>(*this); }
public:
	typedef types::t_true has_c_ptr;
	T* c_ptr() { return &(*(as_array().begin())); }
	const T* c_ptr() const { return &(*(as_array().begin())); }
};

template <class C, class T>
struct ref_iterator_add_c_ptr<C, const T*, types::t_true>
{
private:
	const C& as_array() const { return static_cast<const C&>(*this); }
public:
	typedef types::t_true has_c_ptr;
	const T* c_ptr() const { return &(*(as_array().begin())); }
};

template <class C, class T>
struct ref_iterator_add_c_ptr<C, T, types::t_false>
{
	typedef types::t_false has_c_ptr;
};

template <class T> struct is_force_class
: public types::t_false { };

template <class A>
struct is_force_class <data::wrap_array<A, data::force_wrap_array_attr> >
: public types::t_true { };

template <class C, class TR, class HAS_C_PTR>
struct ref_iterator_add_c_ptr_and_overlap
:
public ref_iterator_add_c_ptr <C,
			typename std::iterator_traits<typename TR::wr_best_it>::pointer,
			typename types::t_or_3<
				types::is_ptr<typename TR::wr_best_it>,
				HAS_C_PTR,
				typename data::iterator_extended_traits<typename
					TR::wr_best_it>::is_pointer_based_and_contiguous
			>::type>
{
private:
	const C& as_array() const { return static_cast<const C&>(*this); }
public:
	template <class A>
	bool overlap_array(const A& a) const
	{
		typedef typename std::iterator_traits<typename TR::wr_const_it>
			::pointer c_pointer;
		typedef typename std::iterator_traits<typename A::const_iterator>
			::pointer a_pointer;
		typedef typename types::t_eq<c_pointer, a_pointer>::type eq_p;

		return ref_iterator_overlap<C, A,
			typename types::t_and_3<eq_p,
				typename data::iterator_extended_traits<typename
					TR::wr_const_it>::is_pointer_based,
				typename data::iterator_extended_traits<typename
					A::const_iterator>::is_pointer_based
				>::type,
			typename types::t_and_3<eq_p,
				typename ref_iterator_add_c_ptr_and_overlap::has_c_ptr,
				typename A::has_c_ptr>::type,
			typename data::iterator_extended_traits<typename TR::wr_const_it>
				::is_array_reference_based,
			typename is_force_class<typename A::data_type>::type
				>::overlap(as_array(), a);
	}
	template <class J>
	bool overlap_element(const J& s) const
	{
		return false;
	}
};

// --------

template <class C, class TR, class HAS_BORDER_WALKER>
struct ref_iterator_add_border_walker { };

template <class C, class TR>
struct ref_iterator_add_border_walker<C, TR, types::t_false>
{
private:
	const C& as_array() const { return static_cast<const C&>(*this); }
public:
	typedef ptrdiff_t iter_border_walker;
	iter_border_walker first_to_last() const { return as_array().length() - 1; }
	iter_border_walker begin_to_end() const { return as_array().length(); }
};

template <class C, class TR>
struct ref_iterator_add_border_walker<C, TR, types::t_true>
{
private:
	const C& as_array() const { return static_cast<const C&>(*this); }
	typedef typename TR::wr_const_it it_store;
public:
	typedef typename it_store::iter_border_walker iter_border_walker;
	iter_border_walker fist_to_last() const
	{
		it_store end_1 = as_array().end();
		--end_1;
		return iter_border_walker(as_array().begin(), end_1);
	}
	iter_border_walker begin_to_end() const
	{
		return iter_border_walker(as_array().begin(), as_array().end());
	}
};

// --------

template <class C, class T, class IT, class CONST_IT, class HAS_C_PTR>
struct ref_iterator_extender :

public
	ref_iterator_extender_base <C,
		typename ref_iterator_traits <IT, CONST_IT, T>::wr_has_random_access,
		typename ref_iterator_traits <IT, CONST_IT, T>::wr_const_it,
		typename ref_iterator_traits <IT, CONST_IT, T>::wr_write_it>,

public
	ref_iterator_add_c_ptr_and_overlap <C, ref_iterator_traits<IT, CONST_IT, T>,
		HAS_C_PTR>,

public
	ref_iterator_add_border_walker <C, ref_iterator_traits<IT, CONST_IT, T>,
		typename data::iterator_extended_traits<typename
			ref_iterator_traits<IT, CONST_IT, T>::wr_const_it>
		::has_border_walker>,

protected
	ref_iterator_traits <IT, CONST_IT, T>
{
	typedef ref_iterator_extender_base <C,
		typename ref_iterator_traits <IT, CONST_IT, T>::wr_has_random_access,
		typename ref_iterator_traits <IT, CONST_IT, T>::wr_const_it,
		typename ref_iterator_traits <IT, CONST_IT, T>::wr_write_it> ext;
public:
	using ext::operator[];
	using ext::begin;
	using ext::end;
	using ext::rbegin;
	using ext::rend;
};

} /* namespace array_details */

} /* namespace ivl */

#endif // IVL_ARRAY_SPECIALIZATION_DETAILS_REF_ITERATOR_TOOLS_HPP
