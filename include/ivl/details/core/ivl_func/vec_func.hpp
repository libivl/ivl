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

#ifndef IVL_CORE_DETAILS_IVL_FUNC_VEC_FUNC_HPP
#define IVL_CORE_DETAILS_IVL_FUNC_VEC_FUNC_HPP

namespace ivl {

//-----------------------------------------------------------------------------

template <class DERIVED>
class vec_func : public ivl_func <DERIVED>
{
	DERIVED& derived() { return static_cast<DERIVED&>(*this); }

//-----------------------------------------------------------------------------

	template<class OP>
	void operate_vec(const OP& op)
	{
		const typename OP::array& a = op.a;
		const size_array& s = a.stride();

		const size_t N = a.length();
		const size_t D = s.length();

		CHECK(dim < D, erange());

		// resize output array
		size_array sz = a.size();
		sz[dim] = 1;
		op.resize(sz);

		const size_t sd0 = s[dim];
		const size_t sd1 = (dim == D - 1) ? N : s[dim + 1];

		const size_t Nk = N / sd1;
		const size_t Nn = sd0;

		// loop over all combinations in dimensions dim+1 to D
		for (size_t k = 0; k < Nk; k++)
		{
			const size_t k0 = k * sd0;
			const size_t k1 = k * sd1;

			// loop over all combinations in dimensions 0 to dim-1
			for (size_t n = 0; n < Nn; n++)
			{
				// apply operation to range r of input,
				// store result in element q of output
				const size_t q = k0 + n;
				const size_t p = k1 + n;

				const size_range r = (p, _ , sd0, _ , p + sd1 - 1);
				op.apply(q, r);
			}
		}
	}

//-----------------------------------------------------------------------------

	template<class IMPL, class O, class A, class I>
	class vec_op
	{
		IMPL& impl;
		O& out;
		const I& in;

	public:
		typedef A array;

		const A& a;

        vec_op(IMPL& i, O& out, const A& a, const I& in) :
			impl(i), out(out), in(in), a(a) { }

		void resize(const size_array sz) const
		{
			out.resize(sz);
		}

		void apply(const size_t q, const size_range& r) const
		{
			out[q] = impl++[ (_,a[r]).concat(in) ];
		}
	};

//-----------------------------------------------------------------------------

public:

	const dimension dim;

	vec_func(dimension d = _0) : dim(d) { }

	/**
	 * \brief Specify dimension along which to operate
	 *
	 * @param d dimension along which to operate
	 */
	DERIVED operator[](dimension d) const { return DERIVED(d); }

//-----------------------------------------------------------------------------

	template<class O, class A, class I>
	void vec(O& out, const A& a, const I& in)
	{
        operate_vec(vec_op<DERIVED, O, A, I>(derived(), out, a, in));
	}

	template<class O, class A>
	void vec(O out, const A& a) { vec(out, a, tuple<>()); }

};

//-----------------------------------------------------------------------------

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_IVL_FUNC_VEC_FUNC_HPP
