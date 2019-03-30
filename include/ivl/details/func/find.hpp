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

#ifndef IVL_FUNC_FIND
#define IVL_FUNC_FIND

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

static size_t npos = size_t(-1);

//-----------------------------------------------------------------------------

namespace func_details {

//-----------------------------------------------------------------------------

template <class DERIVED>
struct find_base : public ivl_func <DERIVED>
{
private:
	DERIVED& derived() { return static_cast <DERIVED&> (*this); }

protected:

//-----------------------------------------------------------------------------

	struct op_impl { // added name to anonymous struct [kimonas]
		template<class A, class V>
		void operator()(A& s, const V& v, size_t n) {
			if(v) s.push_back(n);
		}
	} op;

	struct op_cond_impl { // added name to anonymous struct [kimonas]
		template<class A, class V>
		bool operator()(A& s, const V& v, size_t n) {
			return v ? (s = n, true) : false;
		}
	} op_cond;

public:

//-----------------------------------------------------------------------------

	/**
	 * \brief Find non-zero elements of an array_nd
	 *
	 * @param a array to search in
	 * @param from offset where to start searching from
	 *
	 * @return array of nd index arrays of all non-zero elements found
	 */
	template<class T1, class S1, class K1, class T2, class S2>
	void operate(array <array <T1, K1>, S1>& pos, sep,
		const array_nd <T2, S2>& a, size_t s = npos)
	{
		const typename array_nd <T2, S2>::base_class& b(a);
		pos = ind2sub(a, derived()(b, s));
	}

//-----------------------------------------------------------------------------

	/** Find with rows and columns **/
	/*
	template<class T1, class S1, class S2, class S3>
	void operate(array<T1, S1>& row, array<T1, S2>& col, sep,
		const array_2d<bool, S3>& in);
	*/

};

//-----------------------------------------------------------------------------

struct find_k_impl : public find_base <find_k_impl>
{
	using find_base <find_k_impl>::operate;

	// maximum number of elements to return
	size_t k;

	find_k_impl(const size_t k) : k(k) { }

//-----------------------------------------------------------------------------

	/**
	 * \brief Find the k first non-zero elements of an array
	 *
	 * @param a array to search in
	 * @param s offset where to start searching from
	 *
	 * @return array containing offsets of k first non-zero elements found
	 */
	template <class T1, class S1, class T2, class S2>
	void operate(array <T1, S1>& pos, sep,
					 const array <T2, S2>& a, size_t s = npos)
	{
		pos = (s == npos) ?
		      collect[sz][off][max=k]          (op) (a) :
		      collect[sz][off][max=k][begin=s] (op) (a) ;
	}

	template <class T, class S>
	size_array operator()(const array <T, S>& a, size_t s = npos)
	{
		return call <size_array> (this)(a, s);
	}

};

//-----------------------------------------------------------------------------

struct find_impl : public find_base <find_impl>
{
	using find_base <find_impl>::operate;

	/**
	 * \brief Find non-zero elements of an array
	 *
	 * @param a array to search in
	 * @param s offset where to start searching from
	 *
	 * @return array containing offsets of all non-zero elements found
	 */
	template <class T1, class S1, class T2, class S2>
	void operate(array <T1, S1>& pos, sep,
					 const array <T2, S2>& a, size_t s = npos)
	{
		pos = (s == npos) ?
		      collect[sz][off]          (op) (a) :
		      collect[sz][off][begin=s] (op) (a) ;
	}

	template <class T, class S>
	size_array operator()(const array <T, S>& a, size_t s = npos)
	{
		return call <size_array> (this)(a, s);
	}

//-----------------------------------------------------------------------------

	/**
	 * \brief Find first k elements only
	 */
	find_k_impl operator[](const size_t k) { return find_k_impl(k); }

};

//-----------------------------------------------------------------------------

}  // namespace func_details

//-----------------------------------------------------------------------------

namespace fun {

typedef func_details::find_impl   find;
typedef func_details::find_k_impl find_k;

}  // namespace fun

//-----------------------------------------------------------------------------

static  __attribute__ ((unused)) fun::find find;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif // IVL_FUNC_FIND
