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

#ifndef IVL_CORE_DETAILS_TOOL_UTIL_HPP
#define IVL_CORE_DETAILS_TOOL_UTIL_HPP

namespace ivl {

namespace internal {

template<class T>
void report(const T& t = T())
{
	t.unsupported_method();
}

template<class IS>
struct report_hlp
{
	template<class T, class S>
	static inline void f(const array_nd<T, S>& t) {  t.unsupported_method(); }
	template<class T, class S>
	static inline void f(const array<T, S>& t) { }
};
template<>
struct report_hlp<types::t_false>
{
	template<class T>
	static inline void f() { }
};

template<class T>
void nonlin_report(const T& t = T())
{
	report_hlp<typename 
		types::is_ivl_array<T>::type>::f(t); 
}

} /* namespace internal */
/*
template <class InputIterator, class Size, class OutputIterator>
void copy_n(InputIterator first, Size count,
	OutputIterator result)
{
	while (count--) *result++ = *first++;
}
*/
//void handle_exception(const std::exception& e);


inline void handle_exception(const std::exception& e)
{
	std::cout << std::endl << std::endl << "---------------------------------------" << std::endl;
	std::cout << "An exception has occured! : " << std::endl << e.what() << std::endl;
	std::cout << "---------------------------------------" << std::endl << std::endl;
	throw e;
}



} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TOOL_UTIL_HPP
