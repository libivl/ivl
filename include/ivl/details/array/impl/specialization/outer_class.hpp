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

template <class T,
		 template <typename, typename, typename> class F,
		 class A1, class A2, class DERIVED_INFO
	     >
class array<T, data::outersp<F, A1, A2, DERIVED_INFO> > :

public array_common_base<array<T, data::
		outersp<F, A1, A2, DERIVED_INFO> > >

{

private:
	typedef array_common_base<array<T, data::outersp<
		F, A1, A2, DERIVED_INFO> > > common_base_class;

protected:
	typedef typename array::has_random_access prv_has_random_access;

	typedef typename array_details::elem_func_tools<typename A1::elem_type,
		prv_has_random_access::value> tool1;
	typedef typename array_details::elem_func_tools<typename A2::elem_type,
		prv_has_random_access::value> tool2;

	friend class tool1::not_a_type; // allow disabled types only in our class
	friend class tool2::not_a_type; // allow disabled types only in our class

	const A1* in1;
	const A2* in2;
	size_t len1;
	size_t len;

//-----------------------------------------------------------------------------

public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef typename common_base_class::base_class base_class;

	// parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	// difference type of iterators
	typedef ptrdiff_t diff_type;

	using base_class::derived;

	typedef typename array::has_random_access has_random_access;


	class const_iterator
	{
	private:
		typedef typename A1::const_iterator iter_1;
		typedef typename A2::const_iterator iter_2;

		iter_1 ib;
		iter_1 ie;
		iter_1 i1;
		iter_2 i2;
		
		//;
		//size_t i_pos;
		//size_t 

		typedef typename tool1::template
			rnd_it<const_iterator>::type rnd_iter;

		typedef F<T, typename std::iterator_traits<iter_1>::value_type,
						 typename std::iterator_traits<iter_2>::value_type> f_t;
						 

		inline void move(ptrdiff_t j, ptrdiff_t& move1, ptrdiff_t& move2) const
		{
			ptrdiff_t len1 = tool1::dif_op(ie, ib);
			ptrdiff_t off1 = tool1::dif_op(i1, ib);
			ptrdiff_t steps_from_b = tool1::add_op(j, off1);

			move1 = 0;

			// negative:
			if(steps_from_b < 0) {
				move1 = len1 - 1;
				steps_from_b -= move1;
			}
			
			move1 += steps_from_b % len1 - off1;
			move2 = steps_from_b / len1;
		}
			
	public:

		// iterator_traits
		typedef typename types::t_if<has_random_access,
			std::random_access_iterator_tag,
			std::bidirectional_iterator_tag>::type iterator_category;

		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef internal::pointer_face<const T> pointer;
		// using this to comply with std:: iterators. if it is not optimized-out
		// by the compiler, consider using
		// `const internal::reference_face<const T, types::skip>'
		typedef const internal::reference_face<const T, const_iterator>
			reference;
			
		// constructors
		const_iterator() { }

		const_iterator(const iter_1& ib, const iter_1& ie, const iter_1& i1,  
							const iter_2& i2) : ib(ib), ie(ie), i1(i1), i2(i2) { }

		const_iterator(const const_iterator& it) : 
				ib(it.ib), ie(it.ie), i1(it.i1), i2(it.i2) { }

		// pointer
		pointer operator ->() const
		{
			return pointer(*this, f_t::elem_op(*i1, *i2));
		}

		// members
		reference operator *() const
		{
			return reference(f_t::elem_op(*i1, *i2), *this);
		}

		// optional random access in iterator
		//typename tool::brackets_ret_type
		
		reference operator[]
			(typename tool1::brackets_arg j) const
		{
			// TODO: debug to see if right results
			ptrdiff_t move1, move2;
			move(j, move1, move2);
			
			// TODO: ref brackets should give 'reference', gives 'value&'
			return reference(f_t::elem_op(tool1::ref_brackets(i1, move1), 
									 tool1::ref_brackets(i2, move2)), *this);
		}

		// increment-decrement
		const_iterator& operator++()
		{
			++i1;
			if(i1 == ie) {
				i1 = ib;
				++i2;
			}
			return *this;
		}
		const_iterator& operator--()
		{
			if(i1 == ib) {
				i1 = ie;
				--i2;
			}
			--i1;
			return *this;
		}

		const_iterator operator++(int)
			{ const_iterator tmp(*this); ++(*this); return tmp; }

		const_iterator operator--(int)
			{ const_iterator tmp(*this); --(*this); return tmp; }

		// random access. enabled only if 'has_random_access'
		const_iterator& operator +=(typename tool1::brackets_arg j)
		{
			ptrdiff_t move1, move2;
			move(j, move1, move2);
	
			tool1::add_asgn(i1, move1);
			tool1::add_asgn(i2, move2);
			
			return *this;
		}
		
		const_iterator& operator -=(typename tool1::brackets_arg j)
		{
			ptrdiff_t move1, move2;
			move(-(ptrdiff_t)j, move1, move2);
	
			tool1::add_asgn(i1, move1);
			tool1::add_asgn(i2, move2);
			
			return *this;
		}
		
		inline rnd_iter operator +(typename tool1::brackets_arg j) const
		{
			const_iterator tmp(*this);
			return (tmp += j);
		}
		inline rnd_iter operator -(typename tool1::brackets_arg j) const
		{
			const_iterator tmp(*this);
			return (tmp -= j);
		}

		// difference
		difference_type operator -(const rnd_iter& a) const
		{
			ptrdiff_t len1 = tool1::dif_op(ie, ib);
			
			return tool1::dif_op(i1, a.i1) + len1 * tool1::dif_op(i2, a.i2);
		}

		//copy same type iterator
		const_iterator& operator=(const const_iterator& o)
		{
			ib = o.ib;
			ie = o.ie;
			i1 = o.i1;
			i2 = o.i2;
			return *this;
		}

		bool operator==(const const_iterator& o) const 
			{ return (i1 == o.i1 && i2 == o.i2); }
			
		bool operator!=(const const_iterator& o) const 
			{ return (i1 != o.i1 || i2 != o.i2); }

		bool operator<(const const_iterator& o) const 
			{ return (i2 < o.i2 || (i2 == o.i2 && i1 < o.i1)); }
			
		bool operator<=(const const_iterator& o) const 
			{ return (i2 <= o.i2 || (i2 == o.i2 && i1 <= o.i1)); }
			
		bool operator>(const const_iterator& o) const 
			{ return (i2 > o.i2 || (i2 == o.i2 && i1 > o.i1)); }
			
		bool operator>=(const const_iterator& o) const 
			{ return (i2 >= o.i2 || (i2 == o.i2 && i1 >= o.i1)); }

	};

//-----------------------------------------------------------------------------

	//TODO: figure out what to do
	//typedef typename const_iterator::reference const_reference;
	typedef T const_reference;
	
	typedef const_iterator best_iterator;
	typedef const_reference best_reference;


	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef ptrdiff_t iter_border_walker;

	const_iterator begin() const
		{ return const_iterator(in1->begin(), in1->end(), 
										in1->begin(), in2->begin()); }
	const_iterator end() const
		{ return const_iterator(in1->begin(), in1->end(),
										in1->end(), in2->end()); }

	/* TODO: wrnong!! also in wrong in binary elem 
	 * const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(in1->rbegin(), in2->rbegin()); }
	const_reverse_iterator rend() const
		{ return const_reverse_iterator(in1->rend(), in2->rend()); }
	*/

//-----------------------------------------------------------------------------

	// Size functions
	size_t length() const
	{
		//return in1->derived().length() * in2->derived().length();
		return len;
	}

	// Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	// Get the length of the element sequence
	size_t numel() const { return length(); }


	iter_border_walker first_to_last() { return this->length() - 1; }
	iter_border_walker begin_to_end() { return this->length(); }


	using common_base_class::operator [];

   // Element access
	const_reference operator[](
		typename tool1::brackets_arg i) const
	{
		CHECK(i >= 0 && i < length(), erange);

		return F<T, typename A1::elem_type, 
			typename A2::elem_type>::elem_op(
			in1->derived()[i % len1],
			in2->derived()[i / len1]);
		
		
		//return (this->begin()[i]);
		/*
		return const_reference(F<T, typename A1::elem_type, 
			typename A2::elem_type>::elem_op(
			in1->derived()[i % len1],
			in2->derived()[i / len1]), *this);
		*/
	}


//-----------------------------------------------------------------------------

// Special members

	// set the reference arrays. needs to be called exactly once right
	// after the construction except from the corresponding constructor
	// or the copy constructor.
	void setref(const A1& a1, const A2& a2)
	{
		in1 = &a1;
		in2 = &a2;
		len1 = a1.length();
		len = len1 * a2.length();
	}

//-----------------------------------------------------------------------------

	template <class A>
	bool self_overlap(const A& a) const
	{
		return a.overlap(*in1) || a.overlap(*in2);
	}

	// TODO: proper place
	void init(const A1& a1, const A2& a2) { setref(a1, a2); }

	void init(const array& o) { setref(*o.in1, *o.in2); }


// Constructors
	// default constructor. setref needs to be called to complete construction.
	array() {}

	// construction from the reference arrays
	array(const A1& a1, const A2& a2) { setref(a1, a2); }

	// copy constructor
	array(const array& o) { setref(*o.in1, *o.in2); }

// filler chain constructors

//-----------------------------------------------------------------------------

// unused constructor with size_type
	array(size_t) {}

	// unused constructor with size_type and T&
	array(size_t, const T&) {}

	// unused constructor with size_type and T& or A&
	template <class J, class S>
	array(size_t, const array<J, S>&) {}

	// unused constructor with size_type and T*
	array(size_t, const T*) {}

	// unused constructor with other type array
	template<class J, class S>
	array(const array<J, S>& a) {}

//-----------------------------------------------------------------------------

    // destructor
	~array() { }

};

