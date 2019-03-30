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
 * This class defines an simple one-dimensional %array.
 * little array has the following properties:
 * + very fast for small data that are <= N in size
 * + economic in memory allocation. does free extra memory on resize
 *     in chunks of 64K elements, for larger sizes.
 * -/+ optimized for small data.
 * + can hold any size data, even > 4GB for a 64-bit system.
 * - slower resize than vector, especially for lengths > N
 * - class data might be moved to different pointer,
 *     this is done without using copy constructor when USE_REALLOC is used.
 * - There is a temporary overhead which up to 2 * array size,
 * during resizing. The two last - also apply to std::vector.
 *
 * Note: some (few) element classes will be completely invalid with USE_REALLOC.
 * Those are classes that depend on their own pointer location, e.g. have
 * references on their own data. array<little> is one of those classes itself!
 */
template <class T,
		 class DERIVED_INFO,
		 int N,
		 bool USE_REALLOC,
		 bool USE_PREALLOC
	     >
class array<T,
	data::stack<N, USE_REALLOC, USE_PREALLOC, DERIVED_INFO> >
	:
	public array_common_base<array<T, data::stack<N,
			USE_REALLOC, USE_PREALLOC, DERIVED_INFO> > >

{

private:
	typedef array prv_this_type;
	typedef typename prv_this_type::common_base_class common_base_class;
		/*array_common_base<array<T, data::stack<N,
			USE_REALLOC, USE_PREALLOC, DERIVED_INFO> > > common_base_class;*/

	typedef T dt_array_type[(N == 0) ? 1 : N];
	typedef typename types::t_if<types::t_expr<(N == 0)>,
		types::term, dt_array_type>::type dt_type;

	dt_type dt;
	T* base_ptr;
	size_t len;


	// plain fast ilog2 with binary search for up to 4GB integer x
	/*
	inline unsigned int ilog2(register size_t x)
	{
		register unsigned int l=0;
		if(x >= 1<<16) { x>>=16; l|=16; } //
		if(x >= 1<<8) { x>>=8; l|=8; }
		if(x >= 1<<4) { x>>=4; l|=4; }
		if(x >= 1<<2) { x>>=2; l|=2; }
		if(x >= 1<<1) l|=1;
		return l;
	}*/


	// ivl devel: toggle this to change the memory management
	// scheme for realloc-enabled arrays.
	// false: use realloc directly
	// true: use realloc under memory management layer.
	static const bool custom_realloc_mm = false;

	typedef typename types::is_builtin<T> use_realloc_t;
	static const bool use_realloc = use_realloc_t::value || USE_REALLOC;
	// use the memory management scheme that do preallocate some space.
	// opposite: compact data
	static const bool use_prealloc = USE_PREALLOC;

	static const unsigned int lu_ilog[16];

	static const unsigned int lu_256[256];

	// some tricky memory management
	// container is sized on either the most significant bit or
	// the multiple of 64K of the array size, whichever is smaller.
	template <bool X_LT_64K>
	inline unsigned int ilog2_16b(register size_t x)
	{
		register unsigned int l=0;
		if(!X_LT_64K) x&=((1<<16)-1);
		if(x >= 1<<8) { x>>=8; l|=8; }
		if(x >= 1<<4) { x>>=4; l|=4; }
		l |= lu_ilog[x];
		return l;
	}
	/*
	inline size_t memmanage_sig(register size_t x)
	{
		// save a few if's for small inputs.
		// this array should be optimal for small data
		if(x < 256)
			return lu_256[x];

		return (x & (~((1<<16) - 1))) | ilog2_16b<false>(x);
	} not used. no gain.
	*/
	inline size_t memmanage_sz(register size_t x)
	{
		// this should be optimized-out by the compiler
		if(use_prealloc || (use_realloc && !custom_realloc_mm)) return x;

		else {
			// save a few if's for small inputs.
			// this array should be optimal for small data
			if(x < 256)
				return lu_256[x];

			size_t y = (x & (~((1<<16) - 1)));
			if(!y)
				return 1 << (ilog2_16b<true>(x) + 1);
			else
				return y + (1 << 16);
		}
	}




	inline void grow(size_t l)
	{
		len = l;
		if(len <= N)
			base_ptr = dt;
		else
			base_ptr = (T*)malloc(sizeof(T) * memmanage_sz(len));

		for(size_t i = 0; i < l; i++)
			new(&base_ptr[i]) T();
	}

	inline void grow(size_t l, const T& val)
	{
		len = l;
		if(len <= N)
			base_ptr = dt;
		else
			base_ptr = (T*)malloc(sizeof(T) * memmanage_sz(len));

		for(size_t i = 0; i < l; i++)
			new(&base_ptr[i]) T(val);
	}

	template<bool copy, bool pad>
	void regrow(size_t l, const T* padding = 0);

public:
	typedef array this_type;

	typedef this_type this_array_type;

	typedef this_type array_type;

	typedef T elem_type;

	typedef T& reference;
	typedef const T& const_reference;
	typedef reference best_reference;

	typedef typename this_type::derived_type derived_type;

	typedef typename common_base_class::base_class base_class;

	//! parameter of resize, in each class of the hierarchy
	typedef size_t size_type;

	//! difference type of iterators
	typedef ptrdiff_t diff_type;

	using common_base_class::init_size_with;//todo:fix


	void resize(size_t len)
	{
		if(len != this->len) regrow<true, false>(len);
	}

	void resize(size_t len, const T& s) // with padding
	{
		if(len != this->len) regrow<true, true>(len, &s);
	}

	//! Reshape is same as resize for 1-d arrays
	void reshape(size_t len) { resize(len); }
	void reshape(size_t len, const T& s) { resize(len, s); }

	//! Init is same as resize for 1-d arrays
	//todo: optimize, remove ifs etc, and maybe even make custom regrow.
	void init(size_t len) { resize(0); resize(len); }
	void init(size_t len, const T& s) { resize(0); resize(len, s); }

	void clear() { resize(0); }
/*
	void reset(size_t len)
	{
		regrow<false, false>(len);
	}

	void reset(size_t len, const T& s)
	{
		regrow<false, true>(len, &s);
	}
*/
	typedef data::ptr_iterator<T, false> iterator;
	typedef data::ptr_iterator<T, true> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef iterator best_iterator;

	typedef ptrdiff_t iter_border_walker;

	iterator begin() { return iterator(base_ptr); }
	iterator end() { return iterator(base_ptr + len); }
	const_iterator begin() const { return const_iterator(base_ptr); }
	const_iterator end() const { return const_iterator(base_ptr + len); }

	reverse_iterator rbegin()
		{ return reverse_iterator(iterator(base_ptr + len)); }
	reverse_iterator rend()
		{ return reverse_iterator(iterator(base_ptr)); }
	const_reverse_iterator rbegin() const
		{ return const_reverse_iterator(const_iterator(base_ptr + len)); }
	const_reverse_iterator rend() const
		{ return const_reverse_iterator(const_iterator(base_ptr)); }

	T* c_ptr() { return base_ptr; }
	const T* c_ptr() const { return base_ptr; }

/** @name Size functions
@{*/
	//TODO: explain this better.
	//! Get the length of the element sequence
	size_t length() const { return len; }
	//! Get the size of the array. generic-class function.
	size_type size() const { return length(); }
	//! Get the length of the element sequence
	size_t numel() const { return length(); }
/**@}*/

	iter_border_walker first_to_last() const { return this->length() - 1; }
	iter_border_walker begin_to_end() const { return this->length(); }

	void swap(this_type& v)
	{
		//need a more sophisticated implementation.
		//for now will use this simple one.
		T* old_ptr = base_ptr;
		size_t old_len = len;
		array tmp;
		if(v.length() <= N) {
			tmp = *this;
			old_ptr = tmp.c_ptr();
			*this = v;
		} else {
			base_ptr = v.base_ptr;
			len = v.len;
		}

		if(old_len <= N) {
			for(size_t i = 0; i < old_len; i++)
				v[i] = old_ptr[i];
		} else {
			v.base_ptr = old_ptr;
			v.len = old_len;
		}
	}

/** @name Element access
 *
 * Access a unique element by specifying the position
 *
@{*/
	using common_base_class::operator[];
	//! Returns the const element found at position offset
	const T& operator[](size_t offset) const {
		CHECK(offset >= 0 && offset < length(), erange);
		return base_ptr[offset];
	}
	//! Returns the element found at position offset
	T& operator[](size_t offset) {
		CHECK(offset >= 0 && offset < length(), erange);
		return base_ptr[offset];
	}
/**@}*/


/** @name Constructors
@{*/
	//! Default constructor
	array() { grow(0); }

	//! Construnct by defining an initial number of elements.
	explicit array(size_t count) { grow(count); }

	//! Construnct by defining an initial number of elements.
	explicit array(int count) { grow(size_t(count)); }

	//! Construnct by defining an initial number of elements.
	explicit array(long int count) { grow(size_t(count)); }

	/** \brief Construnct by defining an initial number of elements and a
	 * default value
	 *
	 * @param count Length of the %array
	 * @param s Default value for all elements
	 */
	array(size_t count, const T& s) { grow(count, s); }

	/**
	 * \brief Construct by using a C %array.
	 *
	 * @param count Length of the %array
	 * @param ptr The C %array
	 */
	array(size_t count, const T *ptr) { grow(count); ivl::copy(*this, ptr); }

	/** \brief Construct array with rvalue */
	template <class J>
	array(const tuple_rvalue<J>& r)
		{ grow(0); r.tuple_output(reftpl(*this)); }

	//! Copy-constructor
	array(const this_type& a) { grow(a.length()); ivl::copy(*this, a); }

    /** \brief construct from classes derived from array, using N elements
     *
     * Developper's note: You cannot remove the defined constructor
     * even though it is a subset of this. This is because the copy
     * constructor has a specific declaration, and should be declared
     * to override the C++ default copy-constructor which is wrong and
     * causes heap corruption.
     */
	template <class J, class S>
	array(const array<J, S>& a, size_t n)
	{
		grow(n);
		ivl::copy_out(*this, a);
	}

	/** \brief construct from an existing array of any type.
	 */
	template <class J, class S>
	array(const array<J, S>& a)
	{
		grow(a.length());
		ivl::copy(*this, a);
	}

    /**
     * \brief Construct from array of the same type, using (shape, array)
     *
     * This constructor has the same functionality as the (array, n)
     * constructor, but fulfills a standard construction template that
     * defines that all kinds of arrays (2d, nd etc) can be constructed with
     * derived.size(), array<..> pair
     * A difference is that this function can also accept zero length
     */
	template <class J, class S>
	array(size_t count, const array<J, S>& a)
	{
		grow(count);
		this->init_size_with(a);
	}

/**@}*/

    //! destructor
	~array() {
		// destroy array content
		for(size_t i = 0; i < len; i++)
			(&(base_ptr[i]))->~T();

		if(len > N) ::free(base_ptr);
		base_ptr = 0;
	}


/** @name Assignement Operators
@{*/

	/**
	 * \brief Copy-Assign another array of identical type
	 *
	 * eg:
	 * \code ivl::array<int> a(10, 0);
	 * ivl::array<int> b;
	 * b = a; \endcode
	 */
	using base_class::operator=;

	this_type& operator=(const this_type& a)
	{
		common_base_class::operator=(a);
		return *this;
	}

	 /*
	this_type& operator=(const this_type& a) // LEFT IN THE CONST MODE FOR A COPY CONSTRUCTOR!
	{
		// if(this != &a) TODO: make this a rule: make clear that ...
		// Note: the data class handles the check: if(this != &a),
		// and only IF needed, so there is no case of cpu waste
		if(this == &a) return *this;
		derived().resize(a.length());
		ivl::copy(*this, a);
		return *this;
	}

	template<class S, class K>
	derived_type& operator=(const ivl::array<S, K>& a)
	{
		derived().resize(a.length());
		ivl::copy(*this, a);
		return derived();
	}

	template<class S, class K>
	derived_type& operator=(const T& s)
	{
		derived().resize(1);
		(*this)[0] = s;
		return derived();
	}
*/


};

template <class T, class D, int N, bool USE_REALLOC, bool USE_PREALLOC>
const unsigned int array<T, data::
	stack<N, USE_REALLOC, USE_PREALLOC, D> >::lu_ilog[16] =
{ 0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3 };


template <class T, class D, int N, bool USE_REALLOC, bool USE_PREALLOC>
const unsigned int array<T, data::
	stack<N, USE_REALLOC, USE_PREALLOC, D> >::lu_256[256] =
{
	0, 2, 4, 4, 8, 8, 8, 8, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 32, 32,
	32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
	64, 64, 64, 64, 64, 64, 64, 64, 128, 128, 128, 128, 128, 128, 128, 128,
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
	128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256, 256,
	256, 256
};

// This is the array resize implementation!
// looks quite complicated but many if expressions are
// templates, and most of the code is cases, so it shouldn't
// perform that bad. There are also two possible calls to the
// memmanage_sz function, which is optimized, however it does
// consume some time, for sure less than the vector's stored capacity.
template <class T, class D, int N, bool USE_REALLOC, bool USE_PREALLOC>
template <bool copy, bool pad>
void array<T, data::stack<N, USE_REALLOC, USE_PREALLOC, D> >::
	regrow(size_t l, const T* padding)
{
	if(l > N && len <= N) {
		base_ptr = (T*)malloc(sizeof(T) * memmanage_sz(l));
		// copy resized content
		if(copy) {
			for(size_t i = 0; i < len; i++)
				new(&(base_ptr[i])) T(dt[i]);
		}

		// destroy array content
		for(size_t i = 0; i < len; i++)
			(&(dt[i]))->~T();
	}
	else if(l <= N && len > N) {
		// copy resized content
		if(copy)
			for(size_t i = 0; i < l; i++)
				new(&(dt[i])) T(base_ptr[i]);

		// destroy array content
		for(size_t i = 0; i < len; i++)
			(&(base_ptr[i]))->~T();

		::free(base_ptr);
		base_ptr = dt;
	}
	else if(l < N) {
		// destroy array content
		for(size_t i = l; i < len; i++)
			(&(base_ptr[i]))->~T();
	}
	else if(l > N) {
		size_t sz = memmanage_sz(l);
		if(sz != memmanage_sz(len)) {
			if(use_realloc || !copy)
			{
				// case 1
				// let the system manage the memory hoping it will do
				// that better.
				if(copy) {
					// destroy array content
					for(size_t i = l; i < len; i++)
						(&(base_ptr[i]))->~T();

					base_ptr = (T*)realloc(base_ptr, sizeof(T) * sz);
				}
				else // if(!copy)
				{
					// this scenario is a questionmark.
					// could it be possible that realloc is faster than
					// malloc for small change in size? I wouldn't think, so:

					// destroy array content
					for(size_t i = 0; i < len; i++)
						(&(base_ptr[i]))->~T();

					::free(base_ptr);
					base_ptr = (T*)malloc(sizeof(T) * sz);
				}

			} else { // if (!use_realloc && copy)
				T* old_ptr = base_ptr;
				base_ptr = (T*)malloc(sizeof(T) * memmanage_sz(len));
				size_t lc = (len < l ? len : l);

				// copy resized content
				for(size_t i = 0; i < lc; i++)
					new(&(base_ptr[i])) T(old_ptr[i]);

				// destroy old array content
				for(size_t i = 0; i < len; i++)
					(&(old_ptr[i]))->~T();

				::free(old_ptr);
			}
		}
		else //if(sz == memmanage_sz(len))
		{
			// destroy array content
			for(size_t i = l; i < len; i++)
				(&(base_ptr[i]))->~T();
		}
	}

	if(!copy) len = 0;
	if(pad)
		for(; len < l; len++)
			new(&(base_ptr[len])) T(*padding);
	else
		for(; len < l; len++)
			new(&(base_ptr[len])) T();
	len = l;
}
