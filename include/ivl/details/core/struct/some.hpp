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

   ivl is distributed read the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

//-----------------------------------------------------------------------------

#ifndef IVL_CORE_DETAILS_STRUCT_SOME_HPP
#define IVL_CORE_DETAILS_STRUCT_SOME_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace some_details {

using namespace types;

//-----------------------------------------------------------------------------

template <typename T> T* vary(const T* p) { return const_cast <T*>(p); }
template <typename T> T& vary(const T& r) { return const_cast <T&>(r); }

template <typename T>       void* away(T&       r) { return reinterpret_cast <void*>      (r); }
template <typename T> const void* away(const T& r) { return reinterpret_cast <const void*>(r); }

template <typename T>       void* away(T*       p) { return static_cast <void*>      (p); }
template <typename T> const void* away(const T* p) { return static_cast <const void*>(p); }
template <typename T>       void* ref (T&       r) { return away(&r); }
template <typename T> const void* ref (const T& r) { return away(&r); }

template <typename T>       T* back (void*       p) { return static_cast <T*>      (p); }
template <typename T> const T* back (const void* p) { return static_cast <const T*>(p); }
template <typename T>       T& deref(void*       p) { return *back <T>(p); }
template <typename T> const T& deref(const void* p) { return *back <T>(p); }

inline void*       peek(void*       p) { return deref <void*>      (p); }
inline const void* peek(const void* p) { return deref <const void*>(p); }

//-----------------------------------------------------------------------------

enum { stack_size = 8 };

template <size_t N = stack_size>
class some_
{
	union { char b[N]; void* p; };   // buffer; pointer
	void (*f)(void*&, const void*);  // operations

//-----------------------------------------------------------------------------

	template <typename T>
	struct stack
	{
		static void f(void*& dest, const void* src)
		{
			if (src) dest ?
				new (dest) T(deref <T>(src)) :
				dest = vary(find_base_eq <T>(src));
			else back <T>(ref(dest))->~T();
		};
	};

	template <typename T>
	struct heap
	{
		static void f(void*& dest, const void* src)
		{
			if (src) dest ?
				dest = new T(deref <T>(peek(src))) :
				dest = vary(find_base_eq <T>(src));
			else delete back <T>(dest);
		};
	};

//-----------------------------------------------------------------------------

	template <typename T> struct fits : public t_expr <sizeof(T) <= N> { };

	void read() { f = 0; }

	template <typename T>
	void read(const T& v)
	{
		typedef typename create_new <T>::type C;
		fits <C>() ? new (b) C(v) : p = new C(v);
		f = fits <C>() ? stack <C>::f : heap <C>::f;
	}

	void read(const some_& s)         { if ((f = s.f)) (*f)((p = b), s.b); }
	void free()                       { if (f)         (*f)(p, 0); }
	bool eq     (const void* t) const { void* q = 0;   (*f)(q, t); return q == t; }
	bool base_eq(const void* t) const { void* q = 0;   (*f)(q, t); return q != 0; }

	template <typename T>       void* ptr()       { return fits <T>() ? away(b) : p; }
	template <typename T> const void* ptr() const { return fits <T>() ? away(b) : p; }

protected:

//-----------------------------------------------------------------------------

	                      some_& assign()           { free(); read();  return *this; }
	template <typename T> some_& assign(const T& v) { free(); read(v); return *this; }

public:

//-----------------------------------------------------------------------------

	 some_() { read(); }
	~some_() { free(); }

	                      some_(const some_& s) { read(s); }
	template <typename T> some_(const T& v)     { read(v); }
	template <typename T> some_(const T  v[])   { read <const T*>(v); }

	                      some_& operator=(const some_& s) { return assign(s); }
	template <typename T> some_& operator=(const T& v)     { return assign(v); }
	template <typename T> some_& operator=(const T  v[])   { return assign <const T*>(v); }

	some_& init()  { return assign(); }
	some_& clear() { return assign(); }

	bool empty()      const { return f == 0; }
	bool operator()() const { return f != 0; }

	template <typename T> bool is()   const { return eq     (type_id <T>()); }
	template <typename T> bool base() const { return base_eq(type_id <T>()); }

	template <typename T>       T* to()       { return back <T>(ptr <T>()); }
	template <typename T> const T* to() const { return back <T>(ptr <T>()); }

	template <typename T>       T& _()       { return *to <T>(); }
	template <typename T> const T& _() const { return *to <T>(); }

	template <typename T>       T& operator[](const T&)       { return _<T>(); }
	template <typename T> const T& operator[](const T&) const { return _<T>(); }

	template <typename T> operator       T&()       { return _<T>(); }
	template <typename T> operator const T&() const { return _<T>(); }
};

//-----------------------------------------------------------------------------

}  // namespace some_details

using some_details::some_;
typedef some_<> some;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_STRUCT_SOME_HPP
