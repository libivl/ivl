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

#ifndef IVL_ARRAY_SPECIALIZATION_DETAILS_SUBARRAY_ITERATOR_HPP
#define IVL_ARRAY_SPECIALIZATION_DETAILS_SUBARRAY_ITERATOR_HPP

namespace ivl {

namespace data {


template <class T, class IT, class BEST_IT,
	bool REF_IS_ND, bool CONST, int SPECIALIZED = 0>
class subarray_iterator_type
{
};

template <class T, class IT, class BEST_IT, bool CONST, int SPECIALIZED>
class subarray_iterator_type<T, IT, BEST_IT, false, CONST, SPECIALIZED>
: public data::data_details::
	iter_operator_expander<
		subarray_iterator_type<T, IT, BEST_IT, false, CONST, SPECIALIZED>,
			T, CONST, typename IT::reference>
{
private:
	typedef IT reference_iterator;
	typedef BEST_IT best_reference_iterator;

	template <class J, class Y, class Z, bool R, bool C, int S>
	friend class subarray_iterator_type;

	typedef array_details::subarray_common_tools ctool;

	/*
	A little notice:
	This code was intended to be here:
	friend class data::data_details::iter_operator_expander
		<subarray_iterator_type, T, CONST, typename IT::reference>;
	however MSVC does not like it, so instead of making portability hacks
	I will rather generalize the declaration. I've also done this in other places.
	*/
	template <class X, class Y, bool C, class Z>
	friend class data::data_details::iter_operator_expander;

	typedef typename types::apply_const<T, types::t_expr<CONST> >
		::type best_value_type;

	typedef typename types::apply_const<typename IT::reference,
		types::t_expr<CONST> >::type best_ref_type;

	// this class is used to disable specific specialization members
	class not_a_type { };

	typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
		types::code_word<> >::type invalid_if_const;

protected:
	reference_iterator ir;
	const size_t* sizes;
	size_t size0;
	const ptrdiff_t* const* diffs;
	const ptrdiff_t* diff0;
	ptrdiff_t step0;
	const ptrdiff_t* back;
	internal::little_arrayling<ptrdiff_t> pos;
	// iavr: should be signed
	//size_t pos0;
	ptrdiff_t pos0;

	inline size_t get_pos1() const { return pos[1]; }

	inline typename types::apply_const<typename IT::reference>::type base(
		types::code_word<> ok = types::code_word<>()) const
		{ return (*ir); }

	inline best_ref_type base(
		invalid_if_const disable = invalid_if_const())
		{ return (*ir); }

public:
	typedef subarray_iterator_type this_type;

	// iterator_traits
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef best_value_type* pointer;
	typedef best_ref_type reference;

	struct iter_border_walker
	{
		char type; // 0: stay. 1: first_to_last. 2: begin_to_end
		ptrdiff_t step;
		iter_border_walker(ptrdiff_t x) : type(0), step(0) { }
		iter_border_walker(ptrdiff_t x, char t) : type(t), step(x) { }
	};

	// constructors
	subarray_iterator_type() { }
	subarray_iterator_type(const this_type& it)
	: ir(it.ir), sizes(it.sizes), size0(it.size0), diffs(it.diffs),
		diff0(it.diff0), step0(it.step0), back(it.back),
		pos(it.pos), pos0(it.pos0) { }

	template <class Y, bool C, int S>
	subarray_iterator_type(
		const subarray_iterator_type<T, Y, BEST_IT, false, C, S>& it)
			: ir(it.ir), sizes(it.sizes), size0(it.size0), diffs(it.diffs),
		diff0(it.diff0), step0(it.step0), back(it.back),
		pos(it.pos), pos0(it.pos0) { }

	template <class Y>
	subarray_iterator_type(
		const Y& ir,
		const best_reference_iterator* iter,
		size_t ndims,
		const size_t* sizes,
		const ptrdiff_t* const* diffs,
		const ptrdiff_t* steps,
		const ptrdiff_t* back,
		bool ending,
		ptrdiff_t outer_pos) :
			ir(ir),
			sizes(sizes),
			diffs(diffs),
			step0(steps[0]),
			back(back),
			pos(ndims + 1)
	{
		diff0 = diffs[0];
		size0 = sizes[0];

		if(!ending) {
			for(size_t j = 0; j <= ndims; j++)
				pos[j] = 0;

		} else {

			for(size_t j = 0; j < ndims; j++)
				pos[j] = sizes[j] - 1;
		}

		pos[ndims] = outer_pos;
		pos0 = pos[0];
	}

	//copy same type iterator
	this_type& operator=(const this_type& it)
	{
		ir = it.ir;
		sizes = it.sizes;
		size0 = it.size0;
		diffs = it.diffs;
		diff0 = it.diff0;
		step0 = it.step0;
		back = it.back;
		pos = it.pos;
		pos0 = it.pos0;

		return *this;
	}

	//copy relevant type iterator
	template<class Y, bool C, int S>
	this_type& operator=(const subarray_iterator_type<T, Y,
						BEST_IT, true, C, S>& it)
	{
		ir = it.ir;
		sizes = it.sizes;
		size0 = it.size0;
		diffs = it.diffs;
		diff0 = it.diff0;
		step0 = it.step0;
		pos = it.pos;
		pos0 = it.pos0;
		back = it.back;

		return *this;
	}

	// members

	// increment-decrement
	inline this_type& operator++()
	{
		if(++pos0 >= size0) {
			pos0 = 0;

			size_t i = 1;
			while(/*i < pos.length() &&*/ ++pos[i] >= ptrdiff_t(sizes[i])) {
				pos[i++] = 0;
			}

			ir += back[i - 1];
			if(diffs[i])
				ir += diffs[i][pos[i] - 1];

		}
		else {
			ctool::inner_dim_adder<SPECIALIZED>::template
				operate<ctool::add_op>(ir, diff0, pos0 - 1, step0);
		}
		return *this;
	}

	inline this_type& operator--()
	{
		if(--pos0 < 0) {
			pos0 = size0 - 1;

			size_t i = 1;
			while(/*i < pos.length() &&*/ --pos[i] < 0) {
				pos[i] = sizes[i] - 1;
				i++;
			}
			ir -= back[i - 1];
			if(diffs[i])
				ir -= diffs[i][pos[i]];
		}
		else {
			ctool::inner_dim_adder<SPECIALIZED>::template
				operate<ctool::sub_op>(ir, diff0, pos0, step0);
		}
		return *this;
	}

	this_type operator++(int) { this_type tmp(*this); ++(*this); return tmp; }
	this_type operator--(int) { this_type tmp(*this); --(*this); return tmp; }

	//! operator += w/o random access. implemented only for (iterator + 1)
	this_type& operator +=(size_t j)
	{
		CHECK(j == 1, ecomp);
		++(*this);
		return *this;
	}
	//! operator -= w/o random access. implemented only for (iterator + 1)
	this_type& operator -=(size_t j)
	{
		CHECK(j == 1, ecomp);
		--(*this);
		return *this;
	}
	inline this_type operator +(size_t j) const
	{
		CHECK(j == 1, ecomp);
		this_type tmp(*this);
		++(*this);
		return tmp;
	}
	inline this_type operator -(size_t j) const
	{
		CHECK(j == 1, ecomp);
		this_type tmp(*this);
		--(*this);
		return tmp;
	}

	this_type& operator +=(const iter_border_walker& b)
	{
		ir += b.step;

		size_t p = pos.length() - 1;

		if(b.type == 1 || (b.type && pos[p] != 1)) {
			// first to last or begin to end, added from begin-1

			for(size_t i = 1; i < p; i++)
				pos[i] = sizes[i] - 1;

			pos[p] = 1;

			pos0 = size0 - 1;

		} else if(b.type == 2) { // begin to end, added from begin

			pos[p] = 2; // end

		}
		return *this;
	}

	this_type& operator -=(const iter_border_walker& b)
	{
		ir += b.step;

		size_t p = pos.length() - 1;

		if(b.type == 1 || (b.type && pos[p] != 1)) {
			// first to last or begin to end, subtracted from end

			for(size_t i = 1; i < p; i++)
				pos[i] = 0;

			pos[p] = 1;

			pos0 = 0;

		} else if(b.type == 2) { // begin to end, subtracted from end-1

			pos[p] = 0; // begin-1

		}
		return *this;
	}


	inline this_type operator +(const iter_border_walker& b) const
	{
		this_type tmp(*this);
		tmp += b;
		return tmp;
	}
	inline this_type operator -(const iter_border_walker& b) const
	{
		this_type tmp(*this);
		tmp -= b;
		return tmp;
	}

	// difference is not implemented.
	// this is a non-random_access iterator.


	bool operator==(const this_type& it) const { return (ir == it.ir); }
	bool operator!=(const this_type& it) const { return (ir != it.ir); }

};

template <class T, class IT, class BEST_IT,
	bool CONST, int SPECIALIZED>
class subarray_iterator_type<T, IT, BEST_IT, true, CONST, SPECIALIZED>
: public data::data_details::
	iter_operator_expander<
		subarray_iterator_type<T, IT, BEST_IT, true, CONST, SPECIALIZED>, T, CONST,
			typename IT::reference>
{
private:
	typedef IT reference_iterator;
	typedef BEST_IT best_reference_iterator;

	template <class J, class Y, class Z, bool R, bool C, int S>
	friend class subarray_iterator_type;

	typedef array_details::subarray_common_tools ctool;

	template <class X, class Y, bool C, class Z>
	friend class data::data_details::iter_operator_expander;

	typedef typename types::apply_const<T, types::t_expr<CONST> >
		::type best_value_type;

	typedef typename types::apply_const<typename IT::reference,
		types::t_expr<CONST> >::type best_ref_type;

	// this class is used to disable specific specialization members
	class not_a_type { };

	typedef typename types::t_if<types::t_expr<CONST>, not_a_type,
		types::code_word<> >::type invalid_if_const;


protected:



	reference_iterator ir;
	const best_reference_iterator* iter;
	reference_iterator it1;
	const size_t* sizes;
	size_t size0;
	size_t size1;
	const ptrdiff_t* const* diffs;
	const ptrdiff_t* diff0;
	const ptrdiff_t* diff1;
	const ptrdiff_t* steps;
	size_t step0;
	size_t step1;
	const ptrdiff_t* back;
	ptrdiff_t back0;
	ptrdiff_t back1;
	// iavr: should be signed
	//internal::little_arrayling<size_t> pos;
	//size_t pos0;
	//size_t pos1;
	internal::little_arrayling<ptrdiff_t> pos;
	ptrdiff_t pos0;
	ptrdiff_t pos1;

	inline size_t get_pos1() const { return pos1; }

	inline typename IT::reference base(
		types::code_word<> ok = types::code_word<>()) const
		{ return (*ir); }

	inline best_ref_type base(
		invalid_if_const disable = invalid_if_const())
		{ return (*ir); }

public:
	typedef subarray_iterator_type this_type;

	// iterator_traits
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef best_value_type* pointer;
	typedef best_ref_type reference;

	struct iter_border_walker
	{
		char type; // 0: stay. 1: first_to_last. 2: begin_to_end
		iter_border_walker(ptrdiff_t x) : type(0) { }
		iter_border_walker(ptrdiff_t x, char t) : type(t) { }
	};


	// constructors
	subarray_iterator_type() { }
	subarray_iterator_type(const this_type& it)
	: ir(it.ir), iter(it.iter), it1(it.it1), sizes(it.sizes),
		size0(it.size0), size1(it.size1), diffs(it.diffs), diff0(it.diff0),
		diff1(it.diff1), steps(it.steps), step0(it.step0), step1(it.step1),
		back(it.back), back0(it.back0), back1(it.back1), pos(it.pos),
		pos0(it.pos0), pos1(it.pos1) { }

	template <class Y, bool C, int S>
	subarray_iterator_type(
		const subarray_iterator_type<T, Y, BEST_IT, false, C, S>& it)
	: ir(it.ir), iter(it.iter), it1(it.it1), sizes(it.sizes),
		size0(it.size0), size1(it.size1), diffs(it.diffs), diff0(it.diff0),
		diff1(it.diff1), steps(it.steps), step0(it.step0), step1(it.step1),
		back(it.back), back0(it.back0), back1(it.back1), pos(it.pos),
		pos0(it.pos0), pos1(it.pos1) { }

	template <class Y>
	subarray_iterator_type(
		const Y& ir,
		const best_reference_iterator* iter,
		size_t ndims,
		const size_t* sizes,
		const ptrdiff_t* const* diffs,
		const ptrdiff_t* steps,
		const ptrdiff_t* back,
		bool ending,
		ptrdiff_t outer_pos) :
			ir(ir),
			iter(iter),
			sizes(sizes),
			diffs(diffs),
			steps(steps),
			back(back),
			pos(ndims + 1)
	{
		diff0 = diffs[0];
		diff1 = diffs[1];
		size0 = sizes[0];
		size1 = sizes[1];
		step0 = steps[0];
		step1 = steps[1];
		back0 = back[0];
		back1 = back[1];

		if(ndims > 1)
			it1 = iter[1];

		if(!ending) {

			for(size_t j = 0; j <= ndims; j++)
				pos[j] = 0;

		} else {

			for(size_t j = 0; j < ndims; j++)
				pos[j] = sizes[j] - 1;
		}

		pos[ndims] = outer_pos;
		pos0 = pos[0];
		pos1 = ndims <= 1 ?  0 : pos[1];
	}

	// members

	// increment-decrement

	inline this_type& operator++()
	{
		size_t i;

		if(++pos0 >= size0) {
			pos0 = 0;

			ir -= back0;
			if(++pos1 < size1) {
				ctool::inc_along(ir, it1, diff1, pos1 - 1, step1);

			} else {
				// TODO: ensure in the case of ndim == 1 to have:
				// first_to_last1 = 0
				// pos = minimum 3, instead of 1+1 = 2.
				// pos1 = 0, pos[1] = 0
				// sizes[1]=size1 =0 in that case. so sizes = minimum 2.
				// size1 = 0 is adequate for all the above line.
				pos1 = 0;
				ir.move_along(it1, -back1);
				i = 2;
				/*if(pos[pos.length() - 1] == 0) { // begin-1 to begin
					ir = iter[-3];
					for(; i < pos.length(); i++)
						pos[i] = 0;
					pos[i] = 1;
					i++; // to disable both while and if below
				}*/
				while(i < pos.length() && ++pos[i] >= sizes[i]) {
					pos[i] = 0;
					ir.move_along(iter[i], -back[i]);
					i++;
				}
				if(i == pos.length()-1) { // end-1 to end  //:14-2-2013 was .length()
					pos[i] = 2; //:14-2-2013 unnecessary?
					ir = iter[-1]; //:14-2-2013 unnecessary?
				} else {
					ctool::inc_along(ir, iter[i],
						diffs[i], pos[i] - 1, steps[i]);
				}
			}
		}
		else {
			ctool::inner_dim_adder<SPECIALIZED>::template
				operate<ctool::add_op>(ir, diff0, pos0 - 1, step0);
		}
		return *this;
	}

	inline this_type& operator--()
	{
		size_t i;

		if(--pos0 < 0) {
			pos0 = size0 - 1;

			ir += back0;
			if(--pos1 >= 0) {
				ctool::dec_along(ir, it1, diff1, pos1, step0);

			} else {

				pos1 = size1 - 1;
				ir.move_along(it1, back1);
				i = 2;
				if(pos[pos.length() - 1] == 2) { // end to end-1
					ir = iter[-2];
					for(; i < pos.length(); i++)
						pos[i] = sizes[i] - 1;
					pos[i] = 1;
					return *this;//:14-2-2013 was //i++;
				}
				while(i < pos.length() && --pos[i] < 0) {
					pos[i] = sizes[i] - 1;
					ir.move_along(iter[i], back[i]);
					i++;
				}
				/*if(i == pos.length()) { // begin to begin-1
					pos[i] = 0;
					ir = iter[-4];
				} else */{
					ctool::dec_along(ir, iter[i], diffs[i], pos[i], steps[i]);
				}
			}
		}
		else {
			ctool::inner_dim_adder<SPECIALIZED>::template
				operate<ctool::sub_op>(ir, diff0, pos0, step0);
		}
		return *this;
	}

	this_type operator++(int) { this_type tmp(*this); ++(*this); return tmp; }
	this_type operator--(int) { this_type tmp(*this); --(*this); return tmp; }

	//! operator += w/o random access. implemented only for (iterator + 1)
	this_type& operator +=(size_t j)
	{
		CHECK(j == 1, ecomp);
		++(*this);
		return *this;
	}
	//! operator -= w/o random access. implemented only for (iterator + 1)
	this_type& operator -=(size_t j)
	{
		CHECK(j == 1, ecomp);
		--(*this);
		return *this;
	}
	inline this_type operator +(size_t j) const
	{
		CHECK(j == 1, ecomp);
		this_type tmp(*this);
		++(*this);
		return tmp;
	}
	inline this_type operator -(size_t j) const
	{
		CHECK(j == 1, ecomp);
		this_type tmp(*this);
		--(*this);
		return tmp;
	}


	this_type& operator +=(const iter_border_walker& b)
	{
		size_t p = pos.length() - 1;

		if(b.type == 1 /*|| (b.type && pos[p] != 1)*/) {
			// first to last [[or begin to end, added from begin-1]]

			for(size_t i = 2; i < p; i++)
				pos[i] = sizes[i] - 1;

			pos[p] = 1;

			pos0 = size0 - 1;
			pos1 = size1 - 1;

			ir = iter[-2];

		} else if(b.type == 2) { // begin to end, added from begin

			pos[p] = 2; // end

			ir = iter[-1];

		}
		return *this;
	}

	this_type& operator -=(const iter_border_walker& b)
	{
		size_t p = pos.length() - 1;

		//if(b.type == 1 || (b.type && pos[p] != 1)) {
			// first to last or begin to end, subtracted from end

			for(size_t i = 2; i < p; i++)
				pos[i] = 0;

			pos[p] = 1;

			pos0 = 0;
			pos1 = 0;

			ir = iter[-3];

		/*} else if(b.type == 2) { // begin to end, subtracted from end-1

			pos[p] = 0; // begin-1

			ir = iter[-1];

		}*/
		return *this;
	}

	inline this_type operator +(const iter_border_walker& b) const
	{
		this_type tmp(*this);
		tmp += b;
		return tmp;
	}
	inline this_type operator -(const iter_border_walker& b) const
	{
		this_type tmp(*this);
		tmp -= b;
		return tmp;
	}

	// difference is not implemented.
	// this is a non-random_access iterator.

	//copy same type iterator
	this_type& operator=(const this_type& it)
	{
		ir = it.ir;
		iter = it.iter;
		it1 = it.it1;
		sizes = it.sizes;
		size0 = it.size0;
		size1 = it.size1;
		diffs = it.diffs;
		diff0 = it.diff0;
		diff1 = it.diff1;
		steps = it.steps;
		step0 = it.step0;
		step1 = it.step1;
		back = it.back;
		back0 = it.back0;
		back1 = it.back1;
		pos = it.pos;
		pos0 = it.pos0;
		pos1 = it.pos1;

		return *this;
	}
	//copy relevant type iterator
	template<class J, bool C, int S>
	this_type& operator=(const subarray_iterator_type<T, J,
						BEST_IT, true, C, S>& it)
	{
		ir = it.ir;
		iter = it.iter;
		it1 = it.it1;
		sizes = it.sizes;
		size0 = it.size0;
		size1 = it.size1;
		diffs = it.diffs;
		diff0 = it.diff0;
		diff1 = it.diff1;
		steps = it.steps;
		step0 = it.step0;
		step1 = it.step1;
		back = it.back;
		back0 = it.back0;
		back1 = it.back1;
		pos = it.pos;
		pos0 = it.pos0;
		pos1 = it.pos1;

		return *this;
	}

	bool operator==(const this_type& it) const { return (ir == it.ir); }
	bool operator!=(const this_type& it) const { return (ir != it.ir); }
	bool operator<(const this_type& it) const
	{
		size_t p = pos.length() - 1;
		// we will also consider the last pos in the < operator
		// which is not a pos in a valid dimension but rather
		// a 'pseudo pos' indicating if we are after the array data. (end).
		for(; p > 0; p--) if(pos[p] < it.pos[p]) return true;
		return pos0 < it.pos0;
	}
	bool operator>(const this_type& it) const
	{
		// same as above
		size_t p = pos.length() - 1;
		for(; p > 0; p--) if(pos[p] > it.pos[p]) return true;
		return pos0 > it.pos0;
	}
	bool operator<=(const this_type& it) const
		{ return this_type::operator<(it) || this_type::operator==(it); }
	bool operator>=(const this_type& it) const
		{ return this_type::operator>(it) || this_type::operator==(it); }

};


}; /*namespace data */

}; /*namespace ivl*/

#endif // IVL_ARRAY_SPECIALIZATION_DETAILS_SUBARRAY_ITERATOR_HPP
