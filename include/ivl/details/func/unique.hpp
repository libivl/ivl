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

#ifndef IVL_FUNC_UNIQUE
#define IVL_FUNC_UNIQUE

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

template <typename D>
struct unique_base;

template <bool SORT = true, bool FIRST = true>
struct unique_impl;

template <bool SORT = true, bool FIRST = true>
class unique_off_impl;

//-----------------------------------------------------------------------------

template <template <bool, bool> class DER, bool SORT, bool FIRST>
struct unique_base <DER <SORT, FIRST> > :
	public ivl_func <DER <SORT, FIRST> >
{

//-----------------------------------------------------------------------------

	/**
	 * \brief Assume input array is in ascending order and skip sorting
	 */
	DER <false, FIRST>
	operator[](key::ord) { return DER <false, FIRST> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Return the first occurrence of each repeating element
	 */
	DER <SORT, true>
	operator[](key::first) { return DER <SORT, true> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Return the last occurrence of each repeating element
	 */
	DER <SORT, false>
	operator[](key::last) { return DER <SORT, false> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Return offsets only
	 */
	unique_off_impl <SORT, FIRST>
	operator[](key::off) { return unique_off_impl <SORT, FIRST> (); }

};

//-----------------------------------------------------------------------------

template <bool SORT, bool FIRST>
class unique_off_impl : public unique_base <unique_off_impl <SORT, FIRST> >
{
	typedef unique_base <unique_off_impl <SORT, FIRST> > base;
	typedef unique_impl <SORT, FIRST> F;

public:

	template <class P, class Q, class A>
	void operate(P& p, Q& q, sep, const A& a) { F f; (_, _, p, q) = f++(a); }

	template <class P, class A>
	void operate(P& p, sep, const A& a) { F f; (_, _, p) = f++(a); }

	template <class A>
	size_array operator()(const A& a)
	{
		return typename base::template call <size_array> (a);
	}

};

//-----------------------------------------------------------------------------

template <bool FIRST>
class unique_impl <true, FIRST> :
	public unique_base <unique_impl <true, FIRST> >
{
	typedef unique_base <unique_impl <true, FIRST> > base;

public:

//-----------------------------------------------------------------------------

	template <class U, class P, class Q, class A>
	void operate(U& u, P& p, Q& q, sep, const A& a)
	{
		typename A::create_similar s;
		size_array idx;
		(_, s, idx) = sort++(a);
		(_, u, p, q) = base()[ord]++(s, idx);
		q[idx] = q;
	}

//-----------------------------------------------------------------------------

	template <class U, class P, class A>
	void operate(U& u, P& p, sep, const A& a)
	{
		typename A::create_similar s;
		size_array idx;
		(_, s, idx) = sort++(a);
		(_, u, p) = base()[ord]++(s, idx);
	}

//-----------------------------------------------------------------------------

	template <class U, class A>
	void operate(U& u, sep, const A& a) { (_, u) = base()[ord]++(sort(a)); }

	template <class A>
	typename A::create_similar operator()(const A& a)
	{
		return typename base::template call <typename A::create_similar> (a);
	}

};

//-----------------------------------------------------------------------------

template <bool FIRST>
class unique_impl <false, FIRST> :
	public unique_base <unique_impl <false, FIRST> >
{
	typedef unique_base <unique_impl <false, FIRST> > base;

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Find unique elements of an array and their offsets
	 *
	 * @param a array with possibly repeating elements
	 *
	 * @return (_, u, p, q) where
	 * @param u array containing the unique elements of a in ascending order
	 * @param p array containing, for each unique element u[i] of a, an array of
	 * offsets p[i] of all its occurrences, such that p[i] = find(a == u[i])
	 * and sort(a) = a[flat(p)]
	 * @param q offsets of unique elements in u, such that a = u[q]
	 */
	template <
		class T1, class S1, class T2, class S21, class S22,
		class T3, class S3, class T4, class S4
	>
	void operate(array<T1, S1>& u, array <array <T2, S21>, S22>& p,
					 array <T3, S3>& q, sep,
					 const array<T4, S4>& a, const size_array& idx = size_array())  // idx only used internally!
	{
		if (a.empty()) { u.init(); p.init(); q.init(); return; }
		q = arr(true).cat(diff(a) != 0);
		size_array first = find(q);
		u = a[first];
		if (idx.empty()) (_, p) = partition++(size_array((0, _, a.length() - 1)), first);  // TODO: remove size_array copy
		else             (_, p) = partition++(idx, first);
		q[0] = T3();
		q = cumsum(q);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Find unique elements of an array and their offsets
	 *
	 * @param a array with possibly repeating elements
	 *
	 * @return (_, u, p, q) where
	 * @param u array containing the unique elements of a in ascending order
	 * @param p offsets of unique elements in a, such that u = a[p]
	 * @param q offsets of unique elements in u, such that a = u[q]
	 */
	template <
		class T1, class S1, class T2, class S2,
		class T3, class S3, class T4, class S4
	>
	void operate(array<T1, S1>& u, array <T2, S2>& p, array <T3, S3>& q, sep,
					 const array<T4, S4>& a, const size_array& idx = size_array())  // idx only used internally!
	{
		if (a.empty()) { u.init(); p.init(); q.init(); return; }
		q = arr(true).cat(diff(a) != 0);
		if (FIRST) (_, p) = find++(q);
		else       (_, p) = find++(cshift(q, -1));
		u = a[p];
		if (!idx.empty()) force(p) = idx[p];
		q[0] = T3();
		q = cumsum(q);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Find unique elements of an array and their offsets
	 *
	 * @param a array with possibly repeating elements
	 *
	 * @return (_, u, p) where
	 * @param u array containing the unique elements of a in ascending order
	 * @param p array containing, for each unique element u[i] of a, an array of
	 * offsets p[i] of all its occurrences, such that p[i] = find(a == u[i])
	 * and sort(a) = a[flat(p)]
	 */
	template <
		class T1, class S1, class T2, class S21, class S22,
		class T3, class S3
	>
	void operate(array<T1, S1>& u, array <array <T2, S21>, S22>& p, sep,
					 const array<T3, S3>& a, const size_array& idx = size_array())  // f only used internally!
	{
		if (a.empty()) { u.init(); p.init(); return; }
		size_array first = find(arr(true).cat(diff(a) != 0));
		u = a[first];
		if (idx.empty()) (_, p) = partition++(size_array((0, _, a.length() - 1)), first);  // TODO: remove size_array copy
		else             (_, p) = partition++(idx, first);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Find unique elements of an array and their offsets
	 *
	 * @param a array with possibly repeating elements
	 *
	 * @return (_, u, p) where
	 * @param u array containing the unique elements of a in ascending order
	 * @param p offsets of unique elements in a, such that u = a[p]
	 */
	template <
		class T1, class S1, class T2, class S2,
		class T3, class S3
	>
	void operate(array<T1, S1>& u, array <T2, S2>& p, sep,
					 const array<T3, S3>& a, const size_array& idx = size_array())  // f only used internally!
	{
		if (a.empty()) { u.init(); p.init(); return; }
		if (FIRST) (_, p) = find++(arr(true).cat(diff(a) != 0));  // TODO: check speed of cat()
		else       (_, p) = find++((diff(a) != 0).cat(arr(true)));
		u = a[p];
		if (!idx.empty()) force(p) = idx[p];
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Find unique elements of an array
	 *
	 * @param a array with possibly repeating elements
	 *
	 * @return array containing the unique elements of a in ascending order
	 */
	template <class T1, class S1, class T2, class S2>
	void operate(array<T1, S1>& u, sep,
					 const array<T2, S2>& a)
	{
		if (a.empty()) { u.init(); return; }
		u = a[arr(true).cat(diff(a) != 0)];
	}

	template <class T, class S>
	typename array<T, S>::create_similar
	operator()(const array<T, S>& a)
	{
		return typename base::template
			call <typename array<T, S>::create_similar> (a);
	}

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun { typedef func_details::unique_impl <> unique; }

static  __attribute__ ((unused)) fun::unique unique;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_FUNC_UNIQUE
