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

#ifndef IVL_CORE_DETAILS_TOOL_SAME_PLACE_REVERSE_ITERATOR_HPP
#define IVL_CORE_DETAILS_TOOL_SAME_PLACE_REVERSE_ITERATOR_HPP

namespace ivl {

// same place reverse iterators
/**
 *  This is a class taken from the std::reverse_iterator with the difference
 *  that instead of the relation &*(reverse_iterator(i)) == &*(i - 1)
 *  we have &*(reverse_iterator(i)) == &*(i).
 *  When using this type of relation we need to ensure that there is a valid
 *  pointer right before the beginning of the data pointer, or, an invalid
 *  pointer that will "do the trick", meaning that it will never be
 *  dereferenced, and will only be checked for inequality versus another
 *  pointer.
 *  There reason for this class is an expected (but not proven) speed
 *  improvement for removing the (i - 1) overhead in &*(i - 1).
 *  It is thought to be a legal iterator for our rbegin() and rend() based
 *  on the stl standards, however (TODO) this needs to be researched
 *  furthermore and in case there are contradictions with the std standards
 *  or in case there is no speed improvement we will probably need to fall
 *  back to std::reverse_iterator and do the proper changes in all member
 *  functions that return or manipulate reverse iterators.
 *  There is probably an unsafety issue in the cases that a pointer before
 *  the beginning of the data is invalid. If same_place_reverse_iterator
 *  is not used for pointers, in some cases like subarray there is a chance
 *  (needs to be researched too) that the unsafety issue is not there at all.
*/

  template<typename _Iterator>
    class same_place_reverse_iterator
    : public std::iterator<typename std::iterator_traits<_Iterator>
		::iterator_category,
		      typename std::iterator_traits<_Iterator>::value_type,
		      typename std::iterator_traits<_Iterator>::difference_type,
		      typename std::iterator_traits<_Iterator>::pointer,
                      typename std::iterator_traits<_Iterator>::reference>
    {
    protected:
      _Iterator current;

    public:
      typedef _Iterator					       iterator_type;
      typedef typename std::iterator_traits<_Iterator>::difference_type
							       difference_type;
      typedef typename std::iterator_traits<_Iterator>::reference   reference;
      typedef typename std::iterator_traits<_Iterator>::pointer     pointer;

    public:
      /**
       *  The default constructor default-initializes member @p current.
       *  If it is a pointer, that means it is zero-initialized.
      */
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 235 No specification of default ctor for same_place_reverse_iterator
      same_place_reverse_iterator() : current() { }

      /**
       *  This %iterator will move in the opposite direction that @p x does.
      */
      explicit
      same_place_reverse_iterator(iterator_type __x) : current(__x) { }

      /**
       *  The copy constructor is normal.
      */
      same_place_reverse_iterator(const same_place_reverse_iterator& __x)
      : current(__x.current) { }

      /**
       *  A same_place_reverse_iterator across other types can be copied in the normal
       *  fashion.
      */
      template<typename _Iter>
        same_place_reverse_iterator(const same_place_reverse_iterator<_Iter>& __x)
	: current(__x.base()) { }

      /**
       *  @return  @c current, the %iterator used for underlying work.
      */
      iterator_type
      base() const
      { return current; }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reference
      operator*() //const
      {
      	//This is the only difference for same_place_reverse_iterator
      	return *current;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      pointer
      operator->() const
      { return &(operator*()); }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator&
      operator++()
      {
	--current;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator
      operator++(int)
      {
	same_place_reverse_iterator __tmp = *this;
	--current;
	return __tmp;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator&
      operator--()
      {
	++current;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator
      operator--(int)
      {
	same_place_reverse_iterator __tmp = *this;
	++current;
	return __tmp;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator
      operator+(difference_type __n) const
      { return same_place_reverse_iterator(current - __n); }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator&
      operator+=(difference_type __n)
      {
	current -= __n;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator
      operator-(difference_type __n) const
      { return same_place_reverse_iterator(current + __n); }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      same_place_reverse_iterator&
      operator-=(difference_type __n)
      {
	current += __n;
	return *this;
      }

      /**
       *  @return  TODO
       *
       *  @doctodo
      */
      reference
      operator[](difference_type __n) const
      { return *(*this + __n); }
    };

  //@{
  /**
   *  @param  x  A %same_place_reverse_iterator.
   *  @param  y  A %same_place_reverse_iterator.
   *  @return  A simple bool.
   *
   *  Reverse iterators forward many operations to their underlying base()
   *  iterators.  Others are implemented in terms of one another.
   *
  */
  template<typename _Iterator>
    inline bool
    operator==(const same_place_reverse_iterator<_Iterator>& __x,
	       const same_place_reverse_iterator<_Iterator>& __y)
    { return __x.base() == __y.base(); }

  template<typename _Iterator>
    inline bool
    operator<(const same_place_reverse_iterator<_Iterator>& __x,
	      const same_place_reverse_iterator<_Iterator>& __y)
    { return __y.base() < __x.base(); }

  template<typename _Iterator>
    inline bool
    operator!=(const same_place_reverse_iterator<_Iterator>& __x,
	       const same_place_reverse_iterator<_Iterator>& __y)
    { return !(__x == __y); }

  template<typename _Iterator>
    inline bool
    operator>(const same_place_reverse_iterator<_Iterator>& __x,
	      const same_place_reverse_iterator<_Iterator>& __y)
    { return __y < __x; }

  template<typename _Iterator>
    inline bool
    operator<=(const same_place_reverse_iterator<_Iterator>& __x,
	       const same_place_reverse_iterator<_Iterator>& __y)
    { return !(__y < __x); }

  template<typename _Iterator>
    inline bool
    operator>=(const same_place_reverse_iterator<_Iterator>& __x,
	       const same_place_reverse_iterator<_Iterator>& __y)
    { return !(__x < __y); }

  template<typename _Iterator>
    inline typename same_place_reverse_iterator<_Iterator>::difference_type
    operator-(const same_place_reverse_iterator<_Iterator>& __x,
	      const same_place_reverse_iterator<_Iterator>& __y)
    { return __y.base() - __x.base(); }

  template<typename _Iterator>
    inline same_place_reverse_iterator<_Iterator>
    operator+(typename same_place_reverse_iterator<_Iterator>::difference_type __n,
	      const same_place_reverse_iterator<_Iterator>& __x)
    { return same_place_reverse_iterator<_Iterator>(__x.base() - __n); }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // DR 280. Comparison of same_place_reverse_iterator to const same_place_reverse_iterator.
  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator==(const same_place_reverse_iterator<_IteratorL>& __x,
	       const same_place_reverse_iterator<_IteratorR>& __y)
    { return __x.base() == __y.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<(const same_place_reverse_iterator<_IteratorL>& __x,
	      const same_place_reverse_iterator<_IteratorR>& __y)
    { return __y.base() < __x.base(); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator!=(const same_place_reverse_iterator<_IteratorL>& __x,
	       const same_place_reverse_iterator<_IteratorR>& __y)
    { return !(__x == __y); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>(const same_place_reverse_iterator<_IteratorL>& __x,
	      const same_place_reverse_iterator<_IteratorR>& __y)
    { return __y < __x; }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator<=(const same_place_reverse_iterator<_IteratorL>& __x,
	       const same_place_reverse_iterator<_IteratorR>& __y)
    { return !(__y < __x); }

  template<typename _IteratorL, typename _IteratorR>
    inline bool
    operator>=(const same_place_reverse_iterator<_IteratorL>& __x,
	       const same_place_reverse_iterator<_IteratorR>& __y)
    { return !(__x < __y); }

  template<typename _IteratorL, typename _IteratorR>
#ifdef __GXX_EXPERIMENTAL_CXX0X__
    // DR 685.
    inline auto
    operator-(const same_place_reverse_iterator<_IteratorL>& __x,
	      const same_place_reverse_iterator<_IteratorR>& __y)
    -> decltype(__y.base() - __x.base())
#else
    inline typename same_place_reverse_iterator<_IteratorL>::difference_type
    operator-(const same_place_reverse_iterator<_IteratorL>& __x,
	      const same_place_reverse_iterator<_IteratorR>& __y)
#endif
    { return __y.base() - __x.base(); }
  //@}

} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TOOL_SAME_PLACE_REVERSE_ITERATOR_HPP
