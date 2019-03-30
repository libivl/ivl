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

#ifndef IVL_CORE_DETAILS_ITERATOR_ITERATOR_ND_HPP
#define IVL_CORE_DETAILS_ITERATOR_ITERATOR_ND_HPP


namespace ivl {

namespace iterator_nd_details {

template<class T, class IT_T, bool PAST_END_CAPABLE, bool IS_PTR>
class it_wrapper
{
};

// --- wrapper for past_end_capable

template<class T, class IT_T>
class it_wrapper<T, IT_T, true, false>
: public data::past_end_capable_iterator<IT_T>
{
	typedef data::past_end_capable_iterator<IT_T> prv_base_class;
public:
	typedef it_wrapper it_wrapper_class;
	typedef prv_base_class it_wrapper_base_class;
	it_wrapper_base_class& base()
		{ return static_cast<prv_base_class&>(*this); }
	const it_wrapper_base_class& base() const
		{ return static_cast<const prv_base_class&>(*this); }

	it_wrapper() { }
	it_wrapper(const it_wrapper& i) : prv_base_class(i) { }
	template <class X>
	it_wrapper(const X& y) : prv_base_class(y) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y, ptrdiff_t np) : prv_base_class(y, np) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y) : prv_base_class(0, y) { }
	template <class X>
	it_wrapper(const X& y, ptrdiff_t n) : prv_base_class(y, n) { }
	template <class X, class Z>
	it_wrapper(const X& p, const Z& b) : prv_base_class(b, p - b) { }

	IT_T begin_pos() const { return base().begin_pos(); }
};

template<class IT_T>
class it_wrapper<bool, IT_T, true, false>
: public data::past_end_capable_iterator<IT_T>
{
	typedef data::past_end_capable_iterator<IT_T> prv_base_class;
public:
	typedef it_wrapper it_wrapper_class;
	typedef prv_base_class it_wrapper_base_class;
	it_wrapper_base_class& base()
		{ return static_cast<prv_base_class&>(*this); }
	const it_wrapper_base_class& base() const
		{ return static_cast<const prv_base_class&>(*this); }

	it_wrapper() { }
	it_wrapper(const it_wrapper& i) : prv_base_class(i) { }
	template <class X>
	it_wrapper(const X& y) : prv_base_class(y) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y, ptrdiff_t np) : prv_base_class(np, y) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y) : prv_base_class(0, y) { }
	template <class X>
	it_wrapper(const X& y, ptrdiff_t n) : prv_base_class(y, n) { }
	template <class X, class Z>
	it_wrapper(const X& p, const Z& b) : prv_base_class(b, p - b) { }

	//typename std::iterator_traits<IT_T>::pointer operator->()
	bool* operator->() { return NULL; }
	IT_T begin_pos() const { return base().begin_pos(); }
};

// --- wrapper for simply inherited iterator

template<class T, class IT_T>
class it_wrapper<T, IT_T, false, false>
: public IT_T
{
	typedef IT_T prv_base_class;
public:
	typedef it_wrapper it_wrapper_class;
	typedef prv_base_class it_wrapper_base_class;
	it_wrapper_base_class& base()
		{ return static_cast<prv_base_class&>(*this); }
	const it_wrapper_base_class& base() const
		{ return static_cast<const prv_base_class&>(*this); }

	it_wrapper() { }
	it_wrapper(const it_wrapper& i) : prv_base_class(i) { }
	template <class X>
	it_wrapper(const X& y) : prv_base_class(y) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y, ptrdiff_t np) : prv_base_class(y + np) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y) : prv_base_class(y) { }
	template <class X>
	it_wrapper(const X& y, ptrdiff_t n) : prv_base_class(y + n) { }
	template <class X, class Z>
	it_wrapper(const X& p, const Z& b) : prv_base_class(p) { }

	IT_T begin_pos() const { return base(); }
};

template<class IT_T>
class it_wrapper<bool, IT_T, false, false>
: public IT_T
{
	typedef IT_T prv_base_class;
public:
	typedef it_wrapper it_wrapper_class;
	typedef prv_base_class it_wrapper_base_class;
	it_wrapper_base_class& base()
		{ return static_cast<prv_base_class&>(*this); }
	const it_wrapper_base_class& base() const
		{ return static_cast<const prv_base_class&>(*this); }

	it_wrapper() { }
	it_wrapper(const it_wrapper& i) : prv_base_class(i) { }
	template <class X>
	it_wrapper(const X& y) : prv_base_class(y) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y, ptrdiff_t np) : prv_base_class(y + np) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y) : prv_base_class(y) { }
	template <class X>
	it_wrapper(const X& y, ptrdiff_t n) : prv_base_class(y + n) { }
	template <class X, class Z>
	it_wrapper(const X& p, const Z& b) : prv_base_class(p) { }

	//typename std::iterator_traits<IT_T>::pointer operator->()
	bool* operator->() { return NULL; }
	IT_T begin_pos() const { return base(); }
};

// --- wrapper for pointer

template<class T>
class it_wrapper<T, T*, false, true>
	: public std::iterator_traits<T*>
{
	T* ptr;
public:
	typedef it_wrapper it_wrapper_class;
	typedef T* it_wrapper_base_class;
	it_wrapper_base_class& base() { return ptr; }
	const it_wrapper_base_class& base() const { return ptr; }

	it_wrapper() { }
	it_wrapper(const it_wrapper& i) : ptr(i) { }
	template <class X>
	it_wrapper(const X& y) : ptr(y) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y, ptrdiff_t np) : ptr(y + np) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y) : ptr(y) { }
	template <class X>
	it_wrapper(const X& y, ptrdiff_t n) : ptr(y + n) { }
	template <class X, class Z>
	it_wrapper(const X& p, const Z& b) : ptr(p) { }

	operator T*() { return ptr; }
	operator const T*() const { return ptr; }
	T& operator*() { return *ptr; }
	const T& operator*() const { return *ptr; }
	T* operator->() { return ptr; }
	const T* operator->() const { return ptr; }
	const T* begin_pos() const { return ptr; }
};

template<class T>
class it_wrapper<T, const T*, false, true>
	: public std::iterator_traits<const T*>
{
	const T* ptr;
public:
	typedef it_wrapper it_wrapper_class;
	typedef const T* it_wrapper_base_class;
	it_wrapper_base_class& base() { return ptr; }
	const it_wrapper_base_class& base() const { return ptr; }

	it_wrapper() { }
	it_wrapper(const it_wrapper& i) : ptr(i) { }
	template <class X>
	it_wrapper(const X& y) : ptr(y) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y, ptrdiff_t np) : ptr(y + np) { }
	template <class X>
	it_wrapper(types::code_word<>, const X& y) : ptr(y) { }
	template <class X>
	it_wrapper(const X& y, ptrdiff_t n) : ptr(y + n) { }
	template <class X, class Z>
	it_wrapper(const X& p, const Z& b) : ptr(p) { }

	operator const T*() { return ptr; }
	operator const T*() const { return ptr; }
	const T& operator*() const { return *ptr; }
	const T* operator->() const { return ptr; }
	const T* begin_pos() const { return ptr; }
};

// ----------------------------------------------------------------------------

struct gen_iter_border_walker
{
	ptrdiff_t x;
	gen_iter_border_walker() { }
	gen_iter_border_walker(int x) : x(x) { }
};

// ----------------------------------------------------------------------------


} /* namespace iterator_nd_details */

//namespace data {

// basic_iterator_nd has random access and needs an IT with random access
// Notice: not all iterator_nd's have a single-dim iterator as a base class.
template <class IT, bool PAST_END_CAPABLE>
class basic_iterator_nd :
protected
	iterator_nd_details::it_wrapper<typename
		std::iterator_traits<IT>::value_type, IT,
			(!data::iterator_extended_traits<IT>::is_past_end_capable::value
			&& PAST_END_CAPABLE), types::is_ptr<IT>::value>,
public
	types::t_if<types::is_base<types::pointer_based_iterator_identifier, IT>,
		types::pointer_range_based_iterator_identifier, types::term>::type
{
	size_t stride;

	template <class X, bool Y> friend class basic_iterator_nd;
	//template <class X> friend class data::past_end_capable_iterator;
	//template <class X, class Y, class Z> friend class array_nd;

	// this class is used to disable non-const operator [] for const_operators
	class not_a_type { operator size_t() { return 0; } };

public:
	typedef basic_iterator_nd this_type;

	typedef typename this_type::it_wrapper_class it_base_class;
	/*typedef iterator_nd_details::
			it_wrapper<typename
				std::iterator_traits<IT>::value_type, IT, PAST_END_CAPABLE>
					it_base_class;*/

	typedef std::iterator_traits<it_base_class> it_t;

	typedef typename it_t::iterator_category iterator_category;
	typedef typename it_t::value_type value_type;
	typedef typename it_t::difference_type difference_type;
	typedef typename it_t::pointer pointer;
	typedef typename it_t::reference reference;

	typedef types::t_true has_base_iterator;

	typedef typename it_base_class::it_wrapper_base_class base_it;
	// base() will be either the reference iterator (could be pointer).
	// or a past_end_capable iterator (modified) if needed.
	// it will therefore be a necessary kind of iterator,
	// enough to be able to be based upon for nd_iterator.
	typename it_base_class::it_wrapper_base_class& base()
		{ return static_cast<it_base_class&>(*this).base(); }
	const typename it_base_class::it_wrapper_base_class& base() const
		{ return static_cast<const it_base_class&>(*this).base(); }

	struct iter_nd_border_walker : iterator_nd_details::gen_iter_border_walker
	{
		typedef iterator_nd_details::gen_iter_border_walker b_t;

		iter_nd_border_walker() {}
		iter_nd_border_walker(ptrdiff_t x) : b_t(x) { }
		iter_nd_border_walker(const iter_nd_border_walker& y) : b_t(y.x) { }
		iter_nd_border_walker(const gen_iter_border_walker& y) : b_t(y.x) { }

		//TODO: care about this.
		//void debg(const iter_nd_border_walker& o) { }
		template <class Aiter_nd_border_walker>
		iter_nd_border_walker& operator=(const Aiter_nd_border_walker& o)
		{
			//debg(o);
			x = o.x;
			return *this;
		}
	};

	typedef ptrdiff_t iter_nd_dir_type ;

	// constructors
	basic_iterator_nd() : it_base_class() { }

	basic_iterator_nd(const basic_iterator_nd& it_nd)
		: it_base_class(it_nd.base()), stride(it_nd.stride) { }

	template <class CIT, bool PC>
	basic_iterator_nd(const basic_iterator_nd<CIT, PC>& it_nd)
		: it_base_class(it_nd.base()), stride(it_nd.stride) { }

	/*template <class CIT, bool PC>
	basic_iterator_nd(const basic_iterator_nd<CIT, PC>& b, ptrdiff_t offs)
		: it_base_class(b.base().pos_begin(), offs), stride(b.stride) { }*/

	basic_iterator_nd(types::code_word<>, size_t stride, const IT& it)
		: it_base_class(types::code_word<>(), it), stride(stride) { }


	basic_iterator_nd(size_t stride, const basic_iterator_nd& it)
		: it_base_class(it.base()), stride(stride) { }

	basic_iterator_nd(size_t stride, const IT& it, ptrdiff_t offs)
		: it_base_class(it, offs), stride(stride) { }

	basic_iterator_nd(size_t stride, const IT& it, const IT& b)
		: it_base_class(it, b), stride(stride) { }

	// dereference
	using it_base_class::operator*;
	using it_base_class::operator->;

	// increment-decrement
	this_type& operator++() { base() +=(stride); return *this; }
	this_type& operator--() { base() -=(stride); return *this; }

	this_type operator++(int)
		{ this_type tmp(*this); base() +=(stride); return tmp; }

	this_type operator--(int)
		{ this_type tmp(*this); base() -=(stride); return tmp; }

	// random access
	this_type operator +(const typename it_t::difference_type j) const
		{ /*TODO: maybe: optimize*/
			this_type tmp(*this); tmp.base() += (stride * j); return tmp; }

	this_type operator -(const typename it_t::difference_type j) const
		{ this_type tmp(*this); tmp.base() -= (stride * j); return tmp; }

	this_type& operator +=(const typename it_t::difference_type j)
		{ base() += (stride * j); return *this; }

	this_type& operator -=(const typename it_t::difference_type j)
		{ base() -= (stride * j); return *this; }

	// border walker
	// TODO: eliminate typedefs and conversions in several classes of border_walker to size_t cause of ambiguous candidates
	this_type operator +(const iter_nd_border_walker& z)
		{ /*TODO: maybe: optimize*/
			this_type tmp(*this);
			tmp.base() += z.x; return tmp; }

	this_type operator -(const iter_nd_border_walker& z)
		{ this_type tmp(*this); tmp.base() -= z.x; return tmp; }

	this_type& operator +=(const iter_nd_border_walker& z)
		{ base() += (z.x); return *this; }

	this_type& operator -=(const iter_nd_border_walker& z)
		{ base() -= (z.x); return *this; }


	iter_nd_dir_type dir() const { return stride; }

	iter_nd_dir_type dir(ptrdiff_t x) const { return stride * x; }

	template<class Y, bool PC>
	void inc_along_other_dim_at_begin(const basic_iterator_nd<Y, PC>& y)
		{ base() += (y.dir()); }

	template<class Y, bool PC>
	void dec_along_other_dim_at_begin(const basic_iterator_nd<Y, PC>& y)
		{ base() -= (y.dir()); }

	template<class Y, bool PC>
	void move_along(const basic_iterator_nd<Y, PC>& y, ptrdiff_t x)
		{ base() += (y.dir(x)); }

	// const random access operator
	typename types::apply_const<typename it_t::reference>::type operator [] (
		size_t j) const
		{ return base() [(stride * j)]; }

	// non-const random access, enabled only for non-const T
	typename it_t::reference operator [] (typename
			types::t_if<types::is_const<typename it_t::reference>,
				not_a_type, size_t>::type j)
		{ return base() [(stride * j)]; }  // iavr: base -> base()

	// difference
	typename it_t::difference_type operator -(const this_type& a) const
		{ return (base() - (a)) / stride; }

	// comparing
	bool operator==(const this_type& it) const { return base() == it.base(); }
	bool operator!=(const this_type& it) const { return base() != it.base(); }
	bool operator<(const this_type& it) const { return base() < it.base(); }
	bool operator<=(const this_type& it) const { return base() <= it.base(); }
	bool operator>(const this_type& it) const { return base() > it.base(); }
	bool operator>=(const this_type& it) const { return base() >= it.base(); }

};



//} /*namespace data */

} /*namespace ivl */

#endif // IVL_CORE_DETAILS_ITERATOR_ITERATOR_ND_HPP
