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

#ifndef IVL_FUNC_SORT
#define IVL_FUNC_SORT

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace sort_details {

using keys::key_val;
using func_details::sep;

//-----------------------------------------------------------------------------

struct comb
{
	template <typename COMP, typename SWAP>
	struct sorter
	{
		typedef fun::order <COMP, fun::state2 <SWAP> > ORDER;

		template <typename T, typename S>
		void sort(array <T, S>& a)
		{
			ORDER order;
			size_t gap = a.length();
			typedef typename array <T, S>::iterator I;

			while (gap > 1 || order.swap.on()) {
				order.swap.reset();
				if (gap > 1)
					gap /= 1.247330950103979;

				for (I i = a.begin(), j = i + gap, e = a.end(); j != e; i++, j++)
					order(*i, *j);
			}
		}
	};
};

//-----------------------------------------------------------------------------

struct heap
{
	template <typename COMP, typename SWAP>
	struct sorter
	{
		template <typename T, typename S>
		void sort(array <T, S>& a)
		{
			binary_heap <T, array <T, S>&, COMP, SWAP> h(a);
			h.sort();
		}
	};
};

//-----------------------------------------------------------------------------

struct merge
{
	template <typename COMP, typename SWAP>
	class sorter
	{
		SWAP swap;
		fun::order <COMP, SWAP> order;
		fun::fixed_op2el2 <COMP, bool> comp;

		template <typename T, typename S>
		void block_swap(array <T, S>& a, size_t m)
		{
			size_t l = a.length();
			if (!(m && l - m)) return;
			flip[in][swp=swap](a[0, _, m - 1].ref());
			flip[in][swp=swap](a[m, _, l - 1].ref());
			flip[in][swp=swap](a);
		}

//-----------------------------------------------------------------------------

		template <typename T, typename S>
		void merge(array <T, S>& a, size_t m)
		{
			size_t l = a.length();
			if (!(m && l - m)) return;
			if (l == 2) { order(a[0], a[1]); return; }

			size_t c1, c2;
			if (2 * m > l) {
				c1 = m / 2;
				c2 = m + first[ord](array <bool> (!comp(a[int(m), _, l - 1], a[c1])));
					// TODO: remove array <bool> and int()
			}
			else {
				c2 = (l + m) / 2;
				c1 = first[ord](array <bool> (comp(a[c2], a[0, _, m - 1])));
					// TODO: remove array <bool>
			}
			size_t n = c1 + c2 - m;
			block_swap(a[c1, _, c2 - 1].ref(), m - c1);
			merge(a[size_array((0, _, n - 1))].ref(), c1);  // TODO: remove size_array()
			merge(a[size_array((n, _, l - 1))].ref(), c2 - n);
		}

	public:

//-----------------------------------------------------------------------------

		template <typename T, typename S>
		void sort(array <T, S>& a)
		{
			size_t l = a.length();
			if(l < 2) return;
			size_t m = l / 2;

			sort(a[size_array((0, _, m - 1))].ref());  // TODO: remove size_array()
			sort(a[size_array((m, _, l - 1))].ref());
			merge(a, m);
		}
	};
};

//-----------------------------------------------------------------------------

template <typename ALG>
struct sorter
{
	template <typename COMP, typename SWAP>
	struct fun
	{
		template <typename T, typename S>
		void operator()(array <T, S>& a)
		{
			typename ALG::template sorter <COMP, SWAP> ().sort(a);
		}
	};

	template <typename COMP, typename SWAP>
	fun <COMP, SWAP> operator()(COMP, SWAP) { return fun <COMP, SWAP> (); }
};

template <typename ALG>
sorter <ALG> sort (ALG) { return sorter <ALG> (); }

//-----------------------------------------------------------------------------

template <typename T1, typename S1, typename T2, typename S2>
array <tuple <T1*, T2*> >
tup_array (array <T1, S1>& a1, array <T2, S2>& a2)
{
	typedef tuple <T1*, T2*> T;
	array <T> r(a1.length());

	typename array <T>     ::iterator i  = r.begin();
	typename array <T1, S1>::iterator i1 = a1.begin();
	typename array <T2, S2>::iterator i2 = a2.begin(), e = a2.end();

	for (; i2 != e; i++, i1++, i2++)
		*i = T(&*i1, &*i2);

	return r;
}

//-----------------------------------------------------------------------------

template <typename D>
class sort_base;

template <
	typename ALG = merge, typename COMP = fun::lt,
    bool FLIP = false, bool T_IN = false
>
class sort_impl;

template <
	typename ALG = merge, typename COMP = fun::lt,
    bool FLIP = false, bool T_IN = false
>
class sort_off_impl;

//-----------------------------------------------------------------------------

template <
	template <typename, typename, bool, bool> class DER,
    typename ALG, typename COMP, bool FLIP, bool T_IN
>
class sort_base <DER <ALG, COMP, FLIP, T_IN> > :
    public ivl_func <DER <ALG, COMP, FLIP, T_IN> >
{
protected:

	template <typename T, typename S>
	void cond_flip(array <T, S>& a)
	{
		if(FLIP) flip[in](a);
	}

	template <typename T1, typename S1, typename T2, typename S2>
	void cond_flip(array <T1, S1>& a1, array <T2, S2>& a2)
	{
 		if(FLIP) { flip[in](a1); flip[in](a2); }
	}

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Use comb sort algorithm
	 */
    DER <comb, COMP, FLIP, T_IN>
    operator[](key::comb) { return DER <comb, COMP, FLIP, T_IN> (); }

	/**
	 * \brief Use heap sort algorithm
	 */
    DER <merge, COMP, FLIP, T_IN>
    operator[](key::heap) { return DER <heap, COMP, FLIP, T_IN> (); }

	/**
	 * \brief Use merge sort algorithm
	 */
    DER <merge, COMP, FLIP, T_IN>
    operator[](key::merge) { return DER <merge, COMP, FLIP, T_IN> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Specify comparison functor (lt for ascending, gt for descending)
	 *
	 * @param C (template) type of comparison functor
	 */
	template <typename C>
    DER <ALG, C, FLIP, T_IN>
    operator[](key_val<key::comp, C>) { return DER <ALG, C, FLIP, T_IN> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Specify ascending order; shortcut to [comp=fun::lt]
	 */
    DER <ALG, fun::lt, FLIP, T_IN>
    operator[](key::asc) { return DER <ALG, fun::lt, FLIP, T_IN> (); }

	/**
	 * \brief Specify descending order; shortcut to [comp=fun::gt]
	 */
    DER <ALG, fun::gt, FLIP, T_IN>
    operator[](key::desc) { return DER <ALG, fun::gt, FLIP, T_IN> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Flip array after sorting to get reverse order
	 */
    DER <ALG, COMP, true, T_IN>
    operator[](key::flip) { return DER <ALG, COMP, true, T_IN> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Use in-place sorting if possible
	 */
	DER <ALG, COMP, FLIP, true>
	operator[](key::in) { return DER <ALG, COMP, FLIP, true> (); }

//-----------------------------------------------------------------------------

	/**
	 * \brief Return offsets only
	 */
    sort_off_impl <ALG, COMP, FLIP, T_IN>
    operator[](key::off) { return sort_off_impl <ALG, COMP, FLIP, T_IN> (); }

};

//-----------------------------------------------------------------------------

template <typename ALG, typename COMP, bool FLIP>
class sort_impl <ALG, COMP, FLIP, false> :
	public sort_base <sort_impl <ALG, COMP, FLIP, false> >
{
	typedef sort_base <sort_impl <ALG, COMP, FLIP, false> > base;

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Sort array in ascending order, return sorted array and indices
	 *
	 * @param a input array
	 *
	 * @return (_, s, i) where
	 * @param s sorted array
	 * @param i index array such that s = a[i]
	 */
	template <typename T1, typename S1, typename S2, typename T3, typename S3>
	void operate(array<T1, S1>& s, array <size_t, S2>& i, sep,
					 const array<T3, S3>& a)
	{
		base()[in].operate(i, sep(), s = a);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Sort array in ascending order, return sorted array
	 *
	 * @param a array to sort
	 *
	 * @return sorted array
	 */
	template <typename T1, typename S1, typename T2, typename S2>
	void operate(array<T1, S1>& s, sep,
					 const array<T2, S2>& a)
	{
		base()[in](s = a);
	}

	template <typename T, typename S>
	typename array<T, S>::create_similar
	operator()(const array<T, S>& a)
	{
		return typename base::template
			call <typename array<T, S>::create_similar> (a);
	}

};

//-----------------------------------------------------------------------------

template <typename ALG, typename COMP, bool FLIP>
class sort_impl <ALG, COMP, FLIP, true> :
	public sort_base <sort_impl <ALG, COMP, FLIP, true> >
{
	typedef fun::tup_first2_const <fun::deref2_const <COMP, bool>, bool> IDX_COMP;
	typedef fun::tup_both2 <fun::deref2 <fun::swap> > IDX_SWAP;
	typedef sort_base <sort_impl <ALG, COMP, FLIP, true> > base;
	using base::cond_flip;

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Sort array in-place in ascending order, return sorted indices
	 *
	 * @param a input array
	 *
	 * @return index array such that s = a[i]
	 */
	template <typename S2, typename T1, typename S1>
	void operate(array <size_t, S2>& i, sep,
					 array<T1, S1>& a)
	{
		i = size_range(0, a.length() - 1);
		sort (ALG()) (IDX_COMP(), IDX_SWAP()) (tup_array(a, i).ref());
		cond_flip(a, i);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Sort array in-place in ascending order
	 *
	 * @param a array to sort
	 *
	 * @return reference to (sorted) a
	 */
	template <typename T, typename S>
	array<T, S>& operator()(array<T, S>& a)
	{
		sort (ALG()) (COMP(), fn::swap) (a);
		cond_flip(a);
		return a;
	}
};

//-----------------------------------------------------------------------------

template <typename ALG, typename COMP, bool FLIP>
class sort_off_impl <ALG, COMP, FLIP, false> :
	public sort_base <sort_off_impl <ALG, COMP, FLIP, false> >
{
	typedef sort_base <sort_off_impl <ALG, COMP, FLIP, false> > base;
	typedef sort_impl <ALG, COMP, FLIP, false> F;

public:

	/**
	 * \brief Sort array in ascending order, return sorted indices only
	 *
	 * @param a input array
	 *
	 * @return (_, i) where
	 * @param i index array such that s = a[i]
	 */
	template <class I, class A>
	void operate(I& i, sep, const A& a)
	{
		typename A::create_similar s;
		F f; (_, s, i) = f++(a);
	}

	template <class A>
	size_array operator()(const A& a) const
	{
		return typename base::template call <size_array> (a);
	}

};

//-----------------------------------------------------------------------------

template <typename ALG, typename COMP, bool FLIP>
class sort_off_impl <ALG, COMP, FLIP, true> :
	public sort_base <sort_off_impl <ALG, COMP, FLIP, true> >
{
	typedef sort_base <sort_off_impl <ALG, COMP, FLIP, true> > base;
	typedef sort_impl <ALG, COMP, FLIP, true> F;

public:

	/**
	 * \brief Sort array in-place in ascending order, return sorted indices
	 *
	 * @param a input array
	 *
	 * @return (_, i) where
	 * @param i index array such that s = a[i]
	 */
	template <class I, class A>
	void operate(I& i, sep, const A& a) { F f; (_, i) = f++(a); }

	template <class A>
	size_array operator()(const A& a) const
	{
		return typename base::template call <size_array> (a);
	}

};

//-----------------------------------------------------------------------------

}  // namespace sort_details

//-----------------------------------------------------------------------------

namespace fun { typedef sort_details::sort_impl <> sort; }

static  __attribute__ ((unused)) fun::sort sort;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_SORT
