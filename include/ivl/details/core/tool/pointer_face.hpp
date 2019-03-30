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

#ifndef IVL_CORE_DETAILS_TOOL_POINTER_FACE_HPP
#define IVL_CORE_DETAILS_TOOL_POINTER_FACE_HPP

/*
* The class pointer_face<T> immitates the behavior of a pointer but
* implements an actual copy of a value of type T. It can be also described
* as the opposite thing to the C++ reference.
* The usability is important when we are specializing with templates and
* we want to have pointer to a structure in some cases and value in some
* other cases, but we write a single implementation that only solves the
* pointer case, and we "mask" the values into pointers with this simple wrapper.
*/

namespace ivl {
namespace internal {

template <class T>
struct pointer_face
{
	T val;

	// constructors
	pointer_face() { }
	pointer_face(T* ptr) : val(*ptr) { }
	pointer_face(const T* ptr) : val(*ptr) { }
	pointer_face(const T& val) : val(val) { }
	pointer_face(const pointer_face& o) : val(o.val) { }

	// operator ='s
	pointer_face& operator=(T* ptr) { this->val = *ptr; return *this; }
	pointer_face& operator=(const T* ptr) { this->val = *ptr; return *this; }
	pointer_face& operator=(const T& val) { this->val = val; return *this; }
	pointer_face& operator=(const pointer_face& o)
		{ this->val = o.val; return *this; }

	// dereference
	T& operator *() { return val; }
	const T& operator *() const { return val; }
	T* operator ->() { return &val; }
	const T* operator ->() const { return &val; }
};

template <class T>
struct pointer_face<const T>
{
	T val;

	// constructors
	pointer_face() { }
	pointer_face(T* ptr) : val(*ptr) { }
	pointer_face(const T* ptr) : val(*ptr) { }
	pointer_face(const T& val) : val(val) { }
	pointer_face(const pointer_face& o) : val(o.val) { }

	// operator ='s
	pointer_face& operator=(T* ptr) { this->val = *ptr; return *this; }
	pointer_face& operator=(const T* ptr) { this->val = *ptr; return *this; }
	pointer_face& operator=(const T& val) { this->val = val; return *this; }
	pointer_face& operator=(const pointer_face& o)
		{ this->val = o.val; return *this; }

	// dereference
	const T& operator *() const { return val; }
	const T* operator ->() const { return &val; }
};

template <class T>
struct relaxed_pointer_face
{
	T val;

	// constructors
	relaxed_pointer_face() { }
	template <class O>
	relaxed_pointer_face(O* ptr) : val(*ptr) { }
	template <class O>
	relaxed_pointer_face(const O* ptr) : val(*ptr) { }
	template <class O>
	relaxed_pointer_face(const O& val) : val(val) { }
	relaxed_pointer_face(const relaxed_pointer_face& o) : val(o.val) { }
	template <class O>
	relaxed_pointer_face(const relaxed_pointer_face<O>& o)
		: val(o.val) { }
	template <class O>
	relaxed_pointer_face(const pointer_face<O>& o) : val(o.val) { }

	// operator ='s
	template <class O>
	relaxed_pointer_face& operator=(O* ptr)
		{ this->val = *ptr; return *this; }
	template <class O>
	relaxed_pointer_face& operator=(const O* ptr)
		{ this->val = *ptr; return *this; }
	template <class O>
	relaxed_pointer_face& operator=(const O& val)
		{ this->val = val; return *this; }
	relaxed_pointer_face& operator=(const relaxed_pointer_face& o)
		{ this->val = o.val; return *this; }
	template <class O>
	relaxed_pointer_face& operator=(const relaxed_pointer_face<O>& o)
		{ this->val = o.val; return *this; }
	template <class O>
	relaxed_pointer_face& operator=(const pointer_face<O>& o)
		{ this->val = o.val; return *this; }

	// dereference
	T& operator *() { return val; }
	const T& operator *() const { return val; }
	T* operator ->() { return &val; }
	const T* operator ->() const { return &val; }
};

template <class T>
struct ridiculous_relaxed_pointer_face
{
	char buf[sizeof(T)];
	//T val;
	T& val() { return *((T*)buf); }
	const T& val() const { return *((const T*)buf); }

	// constructors
	ridiculous_relaxed_pointer_face() { }
	template <class O>
	ridiculous_relaxed_pointer_face(O* ptr) { new(buf) T(*ptr); }
	template <class O>
	ridiculous_relaxed_pointer_face(const O* ptr) { new(buf) T(*ptr); }
	//template <class O>
	//ridiculous_relaxed_pointer_face(const O& val) { new(buf) T(val); }
	ridiculous_relaxed_pointer_face(const ridiculous_relaxed_pointer_face& o) { new(buf) T(o.val()); }
	template <class O>
	ridiculous_relaxed_pointer_face(const ridiculous_relaxed_pointer_face<O>& o)
		{ new(buf) T(o.val()); }
	template <class O>
	ridiculous_relaxed_pointer_face(const pointer_face<O>& o) { new(buf) T(o.val); }
	// special for NULL
	ridiculous_relaxed_pointer_face(void*) { }
	//ridiculous_relaxed_pointer_face(int) { }

	// operator ='s
	template <class O>
	ridiculous_relaxed_pointer_face& operator=(O* ptr)
		{ new(buf) T(*ptr); return *this; }
	template <class O>
	ridiculous_relaxed_pointer_face& operator=(const O* ptr)
		{ new(buf) T(*ptr); return *this; }
	//template <class O>
	//ridiculous_relaxed_pointer_face& operator=(const O& val)
	//	{ new(buf) T(val); return *this; }
	ridiculous_relaxed_pointer_face& operator=(const ridiculous_relaxed_pointer_face& o)
		{ new(buf) T(o.val()); return *this; }
	template <class O>
	ridiculous_relaxed_pointer_face& operator=(const ridiculous_relaxed_pointer_face<O>& o)
		{ new(buf) T(o.val()); return *this; }
	template <class O>
	ridiculous_relaxed_pointer_face& operator=(const pointer_face<O>& o)
		{ new(buf) T(o.val); return *this; }
	// special for = NULL
	ridiculous_relaxed_pointer_face& operator=(void*) { return *this; }
	//ridiculous_relaxed_pointer_face& operator=(int) { return *this; }


	// dereference
	T& operator *() { return *((T*)buf); }
	const T& operator *() const { return *((const T*)buf); }
	T* operator ->() { return (T*)&buf; }
	const T* operator ->() const { return (const T*)&buf; }
};

template <class T>
struct relinit_pointer_face
{
	T val;

	// constructors
	relinit_pointer_face() { }
	template <class O>
	relinit_pointer_face(O* ptr) : val(*ptr) { }
	template <class O>
	relinit_pointer_face(const O* ptr) : val(*ptr) { }
	template <class O>
	relinit_pointer_face(const O& val) : val(val) { }
	relinit_pointer_face(const relinit_pointer_face& o) : val(o.val) { }
	template <class O>
	relinit_pointer_face(const relinit_pointer_face<O>& o)
		: val(o.val) { }
	template <class O>
	relinit_pointer_face(const pointer_face<O>& o) : val(o.val) { }

	// operator ='s
	template <class O>
	relinit_pointer_face& operator=(O* ptr)
		{ this->val.init(*ptr); return *this; }
	template <class O>
	relinit_pointer_face& operator=(const O* ptr)
		{ this->val.init(*ptr); return *this; }
	template <class O>
	relinit_pointer_face& operator=(const O& val)
		{ this->val.init(val); return *this; }
	relinit_pointer_face& operator=(const relinit_pointer_face& o)
		{ this->val.init(o.val); return *this; }
	template <class O>
	relinit_pointer_face& operator=(const relinit_pointer_face<O>& o)
		{ this->val.init(o.val); return *this; }
	template <class O>
	relinit_pointer_face& operator=(const pointer_face<O>& o)
		{ this->val.init(o.val); return *this; }

	// dereference
	T& operator *() { return val; }
	const T& operator *() const { return val; }
	T* operator ->() { return &val; }
	const T* operator ->() const { return &val; }
};

template <class T>
struct builtin_to_class
{
protected:
	T v;
public:
	builtin_to_class() {}
	builtin_to_class(const builtin_to_class& a) : v(a.v) {}
	builtin_to_class(const T& v) : v(v) {}

	operator T&() { return v; }
	operator const T&() const { return v; }
};

template <class T>
struct builtin_to_class <const T>
{
protected:
	T v;
public:
	builtin_to_class() {}
	builtin_to_class(const builtin_to_class& a) : v(a.v) {}
	builtin_to_class(const T& v) : v(v) {}

	operator const T&() const { return v; }
	//TODO: this is temporary, until proper fix
	// or wipe of reference face class
	operator ivl::scalar<T>() const { return scalar<T>(v); }

};

template <class T, class ITER = types::skip>
struct reference_face : public types::t_if<
	types::t_or<types::is_builtin<typename types::remove_const<T>::type>,
		types::is_ptr<T> >,
	builtin_to_class<T>, T>::type
{
private:
	typedef typename types::t_if<
	types::t_or<types::is_builtin<typename types::remove_const<T>::type>,
		types::is_ptr<T> >,	builtin_to_class<T>, T>::type builtin_base_class;
	ITER& it;

public:
	typedef builtin_base_class base_class;
	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// constructors
	reference_face(T* ptr, ITER& it)
		: builtin_base_class(*ptr), it(it) { }
	reference_face(const T* ptr, ITER& it)
		: builtin_base_class(*ptr), it(it) { }
	reference_face(const T& val, ITER& it)
		: builtin_base_class(val), it(it) { }
	reference_face(const reference_face& o)
		: builtin_base_class(static_cast<const T&>(o)), it(o.it) { }

	// reference operator
	ITER& operator &() { return it; }
	const ITER& operator &() const { return it; }
};

// TODO: When T is pointer we have failure
template <class T, class ITER>
struct reference_face<const T, ITER> : public types::t_if<
	types::t_or<types::is_builtin<typename types::remove_const<T>::type>,
		types::is_ptr<T> >,	builtin_to_class<const T>, T>::type
{
private:
	typedef typename types::t_if<
	types::t_or<types::is_builtin<typename types::remove_const<T>::type>,
		types::is_ptr<T> >,
		builtin_to_class<const T>, T>::type builtin_base_class;
	const ITER& it;

public:
	typedef builtin_base_class base_class;
	base_class& base() { return static_cast<base_class&>(*this); }
	const base_class& base() const
		{ return static_cast<const base_class&>(*this); }

	// constructors
	reference_face(const T* ptr, const ITER& it)
		: builtin_base_class(*ptr), it(it) { }
	reference_face(const T& val, const ITER& it)
		: builtin_base_class(val), it(it) { }
	reference_face(const reference_face& o)
		: builtin_base_class(static_cast<const T&>(o)), it(o.it) { }

	// reference operator
	const ITER& operator &() const { return it; }
};

} /* namespace internal */
} /* namespace ivl */

#endif // IVL_CORE_DETAILS_TOOL_POINTER_FACE_HPP
