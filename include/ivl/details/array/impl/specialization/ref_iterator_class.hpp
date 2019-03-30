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

/**
 * \brief 1-dimensional %array of type T
 *
 * This class is a very important specialization. It wraps
 * any iterator (could be a user made iterator or an iterator from
 * an stl container) to an ivl array.
 * This class defines an simple one-dimensional %array.
 * IT should have the container iterator. CONST_IT the const_iterator.
 * LENGTH should be 0, or a number for a fixed length container.
 * give types::term as IT to make the array CONST.
 * or give IT = const_iterator and CONST_IT = types::term
 * to make the array CONST.
 * or give IT = CONST_IT = const_iterator to make the array CONST.
 * give IT = iterator and CONST_IT = types::term for an array with no
 * const access (full access only).
 * latest feature: ref iterator supports a flag that allows freeing the memory.
 */
template <class T,
		 class IT,
		 class CONST_IT,
		 int LENGTH,
		 class HAS_C_PTR,
		 class DERIVED_INFO
	     >
class array<T, data::ref_iterator<IT, CONST_IT, LENGTH, HAS_C_PTR,
	DERIVED_INFO> >
	:
	public array_common_base<array<T,
			data::ref_iterator<IT, CONST_IT, LENGTH, typename HAS_C_PTR::type,
				DERIVED_INFO> > >,

	public data::referer<typename types::derive<
		array<T, data::ref_iterator<IT, CONST_IT, LENGTH,
			typename HAS_C_PTR::type, DERIVED_INFO> > >::type>,

	public array_details::ref_iterator_extender<
			array<T, data::ref_iterator<IT, CONST_IT, LENGTH,
			typename HAS_C_PTR::type,
			DERIVED_INFO> >, T, IT, CONST_IT, typename HAS_C_PTR::type>
{
private:
/*//compiler error checking section: this section generates compiler errors
////under certain circumstances, to help the user debug their code.*/
////should you get a 'constant expression is not integral' error one of
////the following occurs:

	// template code for error 00100
	typedef typename types::t_if<types::t_and<types::t_neq<
		typename types::derive<array>::type, array>, types::t_not<
		typename array::has_random_access> >, float, int>::type 
		ivl_compile_error_00100_t;

// -----------------------------------------------------------------------------

	enum {
		// error: you are trying to define an array_nd of type ref_iterator
		// with a non-random access iterator type.
		ivl_compile_error_00100 = ivl_compile_error_00100_t(0)
	};

/*//end of error checking section///
//*/
	typedef array_common_base<array<T, data::ref_iterator<IT,
		CONST_IT, LENGTH, typename HAS_C_PTR::type,
			DERIVED_INFO> > > common_base_class;

	typedef array_details::ref_iterator_extender<
			array<T, data::ref_iterator<IT, CONST_IT, LENGTH,
			typename HAS_C_PTR::type,
			DERIVED_INFO> >,
			T, IT, CONST_IT, typename HAS_C_PTR::type> ext_base;

	template<class X, class Y, class Z>
	friend class array_details::ref_iterator_add_write_rnd_op;
	template<class X, class Y, class Z>
	friend class array_details::ref_iterator_add_const_rnd_op;
	template<class X, class Y>
	friend class array_details::ref_iterator_add_const_it;
	template<class X, class Y>
	friend class array_details::ref_iterator_add_write_it;
	// types

	// struct used to disable some members
	struct not_a_type { template<class X> not_a_type(X){} };
	struct invalid_arguments { template<class X> invalid_arguments(X){} };

	typedef typename ext_base::wr_best_it stored_it_type;
	typedef typename std::iterator_traits<stored_it_type>
		::reference prv_reference;

	// type control for fixed template length / any length

	// struct that behaves like size_t and always returns N
	struct get_n
	{
		get_n() {}
		get_n(size_t l) { CHECK(l == LENGTH, ecomp); }
		operator size_t() { return LENGTH; }
		void operator= (size_t) {}
	};

	typedef typename types::t_if<types::t_expr<LENGTH == 0>,
		size_t, get_n>::type stored_len_type;

	typedef typename types::t_if<types::t_expr<LENGTH == 0>,
		types::skip, invalid_arguments>::type illegal_if_fixedlen;

	typedef typename types::t_if<types::t_expr<LENGTH != 0>,
		types::skip, invalid_arguments>::type illegal_ifn_fixedlen;

	// type control for random access / no random access
	struct unused_iter
	{
		unused_iter() {}
		template<class X>
		unused_iter(X x) {}
	};

	typedef typename array::wr_has_random_access is_rnd;
	typedef typename array::is_writeable is_wrt;

	typedef typename types::t_if<is_rnd,
		unused_iter, stored_it_type>::type end_iter_type;

	typedef typename types::t_if<is_rnd,
		types::skip, invalid_arguments>::type illegal_ifn_rnd;

	typedef typename types::t_if<
		types::t_and<is_rnd, types::t_expr<LENGTH == 0> >,
		types::skip, invalid_arguments>::type illegal_ifn_rnd_and_fixedlen;

    typedef typename types::t_if<is_wrt,
        invalid_arguments, types::skip>::type illegal_if_writeable;
	// members

	stored_it_type base_ptr;

	stored_len_type len;

	end_iter_type end_iter;

	typename array_details::ref_iterator_memmanage<HAS_C_PTR>::store_type mmst;

	// helper functions
	inline
	stored_it_type& get_it_end(stored_it_type& it_end) { return it_end; }

	inline
	const stored_it_type& get_it_end(const stored_it_type& it_end) const
		{ return it_end; }

	inline
	stored_it_type get_it_end(const unused_iter&)
		{ return base_ptr + size_t(len); }

	inline
	stored_it_type get_it_end(const unused_iter&) const
		{ return base_ptr + size_t(len); }

	inline
	stored_it_type dec_iter(stored_it_type it) { return --it; }

    struct invalid_data_init_arg
    {
        operator stored_it_type() { return stored_it_type(); }
    };

	struct ref_iterator_initializer
	{
	    stored_it_type base_ptr;
	    stored_len_type len;
	    end_iter_type end_iter;

        //! constructor with other type array
        template<class J, class S>
        ref_iterator_initializer(const array<J, S>& a)
            : base_ptr(
                array_details::ref_iterator_from_array<const array<J, S>,
                typename types::is_ptr<stored_it_type>::type>::begin_raw(a)),
                //a.begin()),
            len(a.length()),
            end_iter(
                array_details::ref_iterator_from_array<const array<J, S>,
                typename types::is_ptr<stored_it_type>::type>::end_raw(a))/*,
                //a.end()),
            mmst(false) { }*/
        {
        }

        //! constructor with other type array
        template<class J, class S>
        ref_iterator_initializer(array<J, S>& a)
            : base_ptr(
                array_details::ref_iterator_from_array<array<J, S>,
                typename types::is_ptr<stored_it_type>::type>::begin_raw(a)),
                //a.begin()),
            len(a.length()),
            end_iter(
                array_details::ref_iterator_from_array<array<J, S>,
                typename types::is_ptr<stored_it_type>::type>::end_raw(a))/*,
                //a.end()),
            mmst(false) { }*/
        {
        }
	};

public:

	//overriden data class traits
	typedef typename ext_base::has_c_ptr has_c_ptr;

	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef stored_it_type best_iterator;
	typedef typename std::iterator_traits<stored_it_type>::reference reference;
	typedef reference best_reference;
	typedef typename types::apply_const<
		typename std::iterator_traits<typename ext_base::wr_const_it>
			::reference>::type const_reference;

	typedef typename common_base_class::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! redefine data_init_arg
	//! ref_iterator arrays of T* may be initialized with the size and a T*

	typedef typename types::t_if<types::t_and<
        types::is_ptr<stored_it_type>, is_wrt>,
        T*, invalid_data_init_arg>::type data_init_arg;

	////! redefine all_init_arg
	////! ref_iterator arrays of arrays may be initialized with a referred array
	//typedef ref_iterator_initializer all_init_arg;


	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	//! difference type of iterators
	typedef ptrdiff_t diff_type;

	using base_class::derived;

	using common_base_class::operator[];
	using ext_base::operator[];

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return size_t(len); }
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/

	//todo: well 100% correct would be a 2-mode implementation
	//1 for random-access, 2 for non-ra, with stored begin and end inside.
	//but its more complicated. (cant override + with any iterator type)
	//so need to be able to get iter_border_walker type from iterator
	//type (like with i

	typedef typename ext_base::iter_border_walker iter_border_walker;
	using ext_base::first_to_last;
	using ext_base::begin_to_end;

/*
	//#1
	typedef ptrdiff_t iter_border_walker;
	iter_border_walker first_to_last() const { return this->length() - 1; }
	iter_border_walker begin_to_end() const { return this->length(); }

	//#2
	typedef typename (IT)::iter_border_walker iter_border_walker;
	iter_border_walker fist_to_last() const
	{
		stored_it_type end_1 = end();
		--end_1;
		return iter_border_walker(begin(), end_1);
	}
	iter_border_walker begin_to_end() const
	{
		return iter_border_walker(begin(), end());
	}
*/

/** @name Constructors
@{*/
	//! Default constructor
	array() : len(0) { }

	//! with number (for null)
	explicit array(int) : len(0), base_ptr(stored_it_type()) { }

	//! Constructor from iterator, in case container is const
	//! and N is positive.
	array(const stored_it_type& it,
		illegal_ifn_fixedlen disable = illegal_ifn_fixedlen(),
		illegal_ifn_rnd disable2 = illegal_ifn_rnd())
		: base_ptr(it), end_iter(array::rnd_add(it, LENGTH)), mmst(false) { }

	//! Constructor from iterator and size.
	//! in case iterator is random access
	array(const stored_it_type& it, size_t n,
		illegal_if_fixedlen disable = illegal_if_fixedlen(),
		illegal_ifn_rnd disable_cond_2 = illegal_ifn_rnd())
		: base_ptr(it), len(n), end_iter(array::rnd_add(it, n)), mmst(false) { }

	//! Constructor from begin() iterator, size and end() iterator.
	//! for non-random-access iterators, and all other types.
	array(const stored_it_type& it, size_t n, const stored_it_type& it_end,
		illegal_if_fixedlen disable = illegal_if_fixedlen())
		: base_ptr(it), len(n), end_iter(it_end), mmst(false) { }

	//! Constructor from begin() iterator, size and end() iterator.
	//! for non-random-access iterators, and all other types.
	array(const stored_it_type& it, const stored_it_type& it_end, size_t n)
		: base_ptr(it), len(n), end_iter(it_end), mmst(false) { }

	//! Constructor from begin() iterator, size and end() iterator.
	//! for non-random-access iterators, and all other types.
	array(const stored_it_type& it, const stored_it_type& it_end,
		illegal_ifn_rnd_and_fixedlen disable = illegal_ifn_rnd_and_fixedlen())
		: base_ptr(it), len(array::rnd_sub(it_end, it)),
			end_iter(it_end), mmst(false) { }

	//! Copy-constructor
	array(const this_type& a)
		: base_ptr(a.base_ptr), len(a.len),
			end_iter(a.end_iter), mmst(false) { }

	// -- array based constructors --

	//! chain constructor with size_type and T& or A&
	template <class J, class S>
	array(size_t len, const array<J, S>& a)
		: base_ptr(
			array_details::ref_iterator_from_array<const array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a)),
					//a.begin()),
		len(len),
		end_iter(array::rnd_add(

				array_details::ref_iterator_from_array<const array<J, S>,
					typename types::is_ptr<stored_it_type>::type>::begin_raw(a),
				//a.begin(),

				len)), mmst(false) { }

	//! chain constructor with size_type and T& or A&
	template <class J, class S>
	array(size_t len, array<J, S>& a)
		: base_ptr(
			array_details::ref_iterator_from_array<array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a)),
			//a.begin()),
		len(len),
		end_iter(array::rnd_add(
				array_details::ref_iterator_from_array<array<J, S>,
					typename types::is_ptr<stored_it_type>::type>::begin_raw(a),
				//a.begin(),
			len)), mmst(false) { }

	// --
	/*
    //! chain constructor with all_init_arg
    array(const all_init_arg& z)
        : base_ptr(z.base_ptr), len(z.len), end_iter(z.end_iter), mmst(false)
        {
        }
    */
	//! chain constructor with other type array
	template<class J, class S>
	array(const array<J, S>& a)
		: base_ptr(
			array_details::ref_iterator_from_array<const array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a)),
			//a.begin()),
		len(a.length()),
		end_iter(
			array_details::ref_iterator_from_array<const array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::end_raw(a)),
			//a.end()),
		mmst(false) { }

	//! chain constructor with other type array
	template<class J, class S>
	array(array<J, S>& a)
		: base_ptr(
			array_details::ref_iterator_from_array<array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a)),
			//a.begin()),
		len(a.length()),
		end_iter(
			array_details::ref_iterator_from_array<array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::end_raw(a)),
			//a.end()),
		mmst(false) { }


/**@}*/

/** @name filler chain constructors
@{*/
	//! used to work with NULL
	array(size_t) : base_ptr(stored_it_type()) {}

	//! chain constructor with size_type and T*
	array(size_t len, const T* ptr, illegal_if_writeable = illegal_if_writeable())
		: base_ptr(types::r_if<types::t_eq<stored_it_type, const T*> >
					(ptr, stored_it_type())), len(len), mmst(false)
	{
		end_iter = array::rnd_add(base_ptr, len);
	}
	//! chain constructor with size_type and data_init_arg
	array(size_t len, const data_init_arg& y)
        : base_ptr(y), len(len), mmst(false)
	{
		end_iter = array::rnd_add(base_ptr, len);
		mmst = false;
	}

	/*
	array(size_t len, T* ptr)
		: base_ptr(types::r_if<types::t_eq<stored_it_type, T*> >
					(ptr, stored_it_type())), len(len), mmst(false)
	{
	    std::cout << "Chain constructor nc: " << (size_t)ptr << std::endl;
		end_iter = array::rnd_add(base_ptr, len);
	}
	*/

/**@}*/


/** @name Special member functions
@{*/

	void set_null()
	{
		base_ptr = stored_it_type();
	}
	bool is_null() const
	{
		return base_ptr == stored_it_type();
	}
	void set_free(bool enable = true)
	{
		mmst = enable;
	}

/**@}*/

	//----------------------------------------------------
/** @name Init member functions
@{*/

	//setup functions are same as the constructors for provided iterators
	void init(const array& o)
	{
		base_ptr = o.base_ptr;
		len = o.len;
		end_iter = o.end_iter;
		mmst = false;
	}

	void init(const stored_it_type& it,
		illegal_ifn_fixedlen disable = illegal_ifn_fixedlen(),
		illegal_ifn_rnd disable2 = illegal_ifn_rnd())
	{
		base_ptr = it;
		end_iter = array::rnd_add(it, LENGTH);
		mmst = false;
	}

	void init(const stored_it_type& it, size_t n,
		illegal_if_fixedlen disable = illegal_if_fixedlen(),
		illegal_ifn_rnd disable_cond_2 = illegal_ifn_rnd())
	{
		base_ptr = it;
		len = n;
		end_iter = array::rnd_add(it, n);
		mmst = false;
	}

	void init(const stored_it_type& it, size_t n, const stored_it_type& it_end,
		illegal_if_fixedlen disable = illegal_if_fixedlen())
	{
		base_ptr = it;
		len = n;
		end_iter = it_end;
		mmst = false;
	}

	void init(const stored_it_type& it, const stored_it_type& it_end, size_t n)
	{
		base_ptr = it;
		len = n;
		end_iter = it_end;
		mmst = false;
	}

	void init(const stored_it_type& it, const stored_it_type& it_end,
		illegal_ifn_rnd_and_fixedlen disable = illegal_ifn_rnd_and_fixedlen())
	{
		base_ptr = it;
		len = array::rnd_sub(it_end, it);
		end_iter = it_end;
		mmst = false;
	}

	// -- array based constructors --

	//! chain constructor with size_type and T& or A&
	template <class J, class S>
	void init(size_t len, const array<J, S>& a)
	{
		base_ptr =
			array_details::ref_iterator_from_array<const array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a);
					//a.begin()),
		this->len = len;
		end_iter = array::rnd_add(

				array_details::ref_iterator_from_array<const array<J, S>,
					typename types::is_ptr<stored_it_type>::type>::begin_raw(a),
				//a.begin(),

				len);
		mmst = false;
	}

	//! chain constructor with size_type and T& or A&
	template <class J, class S>
	void init(size_t len, array<J, S>& a)
	{
		base_ptr =
			array_details::ref_iterator_from_array<array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a);
			//a.begin()),
		this->len = len;
		end_iter = array::rnd_add(
				array_details::ref_iterator_from_array<array<J, S>,
					typename types::is_ptr<stored_it_type>::type>::begin_raw(a),
				//a.begin(),
			len);
		mmst = false;
	}
/*
    //! chain constructor with all_init_type
    void init(const all_init_arg& z)
    {
        base_ptr = z.base_ptr;
        len = z.len;
        end_iter = z.end_iter;
        mmst = false;
    }
	// --
	*/
	//! chain constructor with other type array
	template<class J, class S>
	void init(const array<J, S>& a)
	{
		base_ptr =
			array_details::ref_iterator_from_array<const array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a);
			//a.begin()),
		len = a.length();
		end_iter =
			array_details::ref_iterator_from_array<const array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::end_raw(a);
			//a.end()),
		mmst = false;
	}

	//! chain constructor with other type array
	template<class J, class S>
	void init(array<J, S>& a)
	{
		base_ptr =
			array_details::ref_iterator_from_array<array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::begin_raw(a);
			//a.begin()),
		len = a.length();
		end_iter =
			array_details::ref_iterator_from_array<array<J, S>,
				typename types::is_ptr<stored_it_type>::type>::end_raw(a);
			//a.end()),
		mmst = false;
	}


	void init(size_t s) // for NULL!
	{
		if(s == 0)
			base_ptr = stored_it_type();
	}

	//! chain constructor with size_type and T*
	void init(size_t len, const T* ptr,
           illegal_if_writeable disable = illegal_if_writeable())
	{
		base_ptr = types::r_if<types::t_eq<stored_it_type, const T*> >
					(ptr, stored_it_type());
		this->len = len;
		end_iter = array::rnd_add(base_ptr, len);
		mmst = false;
	}
	/*
	//! chain constructor with size_type and T*
	void init(size_t len, T* ptr)
	{
		base_ptr = types::r_if<types::t_eq<stored_it_type, T*> >
					(ptr, stored_it_type());
		this->len = len;
		end_iter = array::rnd_add(base_ptr, len);
		mmst = false;
	}
	*/
	void init(size_t len, const data_init_arg& y)
	{
	    base_ptr = y;
	    this->len = len;
		end_iter = array::rnd_add(base_ptr, len);
		mmst = false;
	}

/**@}*/

/** @name setref member functions
@{*/
	//setup functions are same as the constructors for provided iterators
	void setref(const array& o) { init(o); }

	void setref(const stored_it_type& it,
		illegal_ifn_fixedlen disable = illegal_ifn_fixedlen(),
		illegal_ifn_rnd disable2 = illegal_ifn_rnd()) { init(it); }

	void setref(const stored_it_type& it, size_t n,
		illegal_if_fixedlen disable = illegal_if_fixedlen(),
		illegal_ifn_rnd disable_cond_2 = illegal_ifn_rnd()) { init(it, n); }

	void setref(const stored_it_type& it, size_t n, const stored_it_type& it_end,
		illegal_if_fixedlen disable = illegal_if_fixedlen())
		{ init(it, n, it_end); }

	void setref(const stored_it_type& it, const stored_it_type& it_end, size_t n)
		{ init(it, it_end, n); }

	void setref(const stored_it_type& it, const stored_it_type& it_end,
		illegal_ifn_rnd_and_fixedlen disable = illegal_ifn_rnd_and_fixedlen())
		{ init(it, it_end); }

	// -- array based setref --
	template <class J, class S>
	void setref(size_t len, const array<J, S>& a) { init(len, a); }

	template <class J, class S>
	void setref(size_t len, array<J, S>& a) { init(len, a); }

	template<class J, class S>
	void setref(const array<J, S>& a) { init(a); }

	template<class J, class S>
	void setref(array<J, S>& a) { init(a); }

   // void setref(const all_init_arg& a) { init(a); }

	void setref(size_t s) { init(s); }

	void setref(size_t len, const T* ptr,
        illegal_if_writeable disable = illegal_if_writeable())
        { init(len, ptr); }

	void setref(size_t len, const data_init_arg& y) { init(len, y); }

/**@}*/

    //! destructor
	~array()
	{
		// frees the memory on the special case of a data::deletable_c_ptr
		// and flag mmst == true.
		array_details::ref_iterator_memmanage<HAS_C_PTR>::
			destroy(mmst, base_ptr);
	}


/** @name Assignement Operators
@{*/

	//using common_base_class::operator=;
	template<class K>
	derived_type& operator=(const K& k)
	{
		common_base_class::operator=(k);
		return derived();
	}

	this_type& operator=(const this_type& a)
	{
		common_base_class::operator=(a);
		return *this;
	}
/**@}*/
	using ext_base::overlap_array;
	using ext_base::overlap_element;

	// TODO: needs different implementation.
	template <class D>
	bool self_overlap(const D& d) const { return overlap_array(d); }

	/*
	template <class A>
	bool overlap(const A& a) const
	{
		return ext_base::overlap(a);
		//should check the pointers if you have pointers.
		//should have a few specializations concerning all the normal array
		//iterators, and iterator_nd objects and convert the to pointers and
		//then check them against the range (begin, end) of the other array
		//pointerwise. Although this ruins the beauty of the abstraction,
		//it does give us a really great way to predict and correct data
		//overlapping errors which could allow great results like safely using:
		//pixel = function(image area)
		//
		//for the current moment this is too much.
		//however, another good idea that saves the abstraction disaster
		//is to put a fourth optional bool template argument in the data class
		//which will tell us that &(*iter) is a pointer, and even though this
		//would be false by default, we could also enforce it by a hidden tag
		//in the participating iterators which will give us the same info.
		//with a logical or we can decide which is the case.
		return false;
	}
	*/

};

