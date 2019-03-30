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

#ifndef IVL_QT_CORE_CONSTRUCTOR_HPP
#define IVL_QT_CORE_CONSTRUCTOR_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

struct _ { };
struct term { };

template <typename D>
class extends
{
protected:
	const D& d() const { return static_cast <const D&>(*this); }
};

template <typename S, typename D = term>
struct constructor
{ };

//-----------------------------------------------------------------------------

template <typename R>
struct constructor <R ()>
{
	R operator()() const { return R(); }
};

template <typename R, typename A1>
struct constructor <R (A1)>
{
	R operator()(A1 a1) const { return R(a1); }
};

template <typename R, typename A1, typename A2>
struct constructor <R (A1, A2)>
{
	R operator()(A1 a1, A2 a2) const { return R(a1, a2); }
};

template <typename R, typename A1, typename A2, typename A3>
struct constructor <R (A1, A2, A3)>
{
	R operator()(A1 a1, A2 a2, A3 a3) const { return R(a1, a2, a3); }
};

//-----------------------------------------------------------------------------

template <template <typename> class R>
struct constructor <R <_> ()>
{
	template <typename T>
	R <T> operator()(T& t) const { return R <T> (t); }

	template <typename T>
	R <const T> operator()(const T& t) const { return R <const T> (t); }
};

template <template <typename> class R, typename A1>
class constructor <R <_> (A1)>
{
	class nested
	{
		A1 a1;

	public:
		nested(A1 a1) : a1(a1) { }

		template <typename T>
		R <T> operator()(T& t) const { return R <T> (t, a1); }

		template <typename T>
		R <const T> operator()(const T& t) const { return R <const T> (t, a1); }
	};

public:
	nested operator()(A1 a1) { return nested(a1); }
};

template <template <typename> class R, typename A1, typename A2>
struct constructor <R <_> (A1, A2)>
{
	class nested
	{
		A1 a1; A2 a2;

	public:
		nested(A1 a1, A2 a2) : a1(a1), a2(a2) { }

		template <typename T>
		R <T> operator()(T& t) const { return R <T> (t, a1, a2); }

		template <typename T>
		R <const T> operator()(const T& t) const { return R <const T> (t, a1, a2); }
	};

public:
	nested operator()(A1 a1, A2 a2) const { return nested(a1, a2); }
};

template <template <typename> class R, typename A1, typename A2, typename A3>
struct constructor <R <_> (A1, A2, A3)>
{
	class nested
	{
		A1 a1; A2 a2; A3 a3;

	public:
		nested(A1 a1, A2 a2, A3 a3) : a1(a1), a2(a2), a3(a3) { }

		template <typename T>
		R <T> operator()(T t) const { return R <T> (t, a1, a2, a3); }

		template <typename T>
		R <const T> operator()(const T& t) const { return R <const T> (t, a1, a2, a3); }
	};

public:
	nested operator()(A1 a1, A2 a2, A3 a3) const { return nested(a1, a2, a3); }
};

//-----------------------------------------------------------------------------

template <typename D, typename R>
struct constructor <R (), D> : public extends <D>
{
	using extends <D>::d;
	R operator()() const { return R(d()); }
};

template <typename D, typename R, typename A1>
struct constructor <R (A1), D> : public extends <D>
{
	using extends <D>::d;
	R operator()(A1 a1) const { return R(d(), a1); }
};

template <typename D, typename R, typename A1, typename A2>
struct constructor <R (A1, A2), D> : public extends <D>
{
	using extends <D>::d;
	R operator()(A1 a1, A2 a2) const { return R(d(), a1, a2); }
};

template <typename D, typename R, typename A1, typename A2, typename A3>
struct constructor <R (A1, A2, A3), D> : public extends <D>
{
	using extends <D>::d;
	R operator()(A1 a1, A2 a2, A3 a3) const { return R(d(), a1, a2, a3); }
};

//-----------------------------------------------------------------------------

template <typename D, template <typename> class R>
struct constructor <R <_> (), D> : public extends <D>
{
	using extends <D>::d;

	template <typename T>
	R <T> operator()(T& t) const { return R <T> (t, d()); }

	template <typename T>
	R <const T> operator()(const T& t) const { return R <const T> (t, d()); }
};

template <typename D, template <typename> class R, typename A1>
struct constructor <R <_> (A1), D> : public extends <D>
{
	class nested
	{
		const D& d; A1 a1;

	public:
		nested(const D& d, A1 a1) : d(d), a1(a1) { }

		template <typename T>
		R <T> operator()(T& t) const { return R <T> (t, d, a1); }

		template <typename T>
		R <const T> operator()(const T& t) const { return R <const T> (t, d, a1); }
	};

public:
	nested operator()(A1 a1) const { return nested(extends <D>::d(), a1); }
};

template <typename D, template <typename> class R, typename A1, typename A2>
struct constructor <R <_> (A1, A2), D> : public extends <D>
{
	class nested
	{
		const D& d; A1 a1; A2 a2;

	public:
		nested(const D& d, A1 a1, A2 a2) : d(d), a1(a1), a2(a2) { }

		template <typename T>
		R <T> operator()(T& t) { return R <T> (t, d(), a1, a2); }

		template <typename T>
		R <const T> operator()(const T& t) { return R <const T> (t, d(), a1, a2); }
	};

public:
	nested operator()(A1 a1, A2 a2) const { return nested(extends <D>::d(), a1, a2); }
};

template <typename D, template <typename> class R, typename A1, typename A2, typename A3>
struct constructor <R <_> (A1, A2, A3), D> : public extends <D>
{
	class nested
	{
		const D& d; A1 a1; A2 a2; A3 a3;

	public:
		nested(const D& d, A1 a1, A2 a2, A3 a3) : d(d), a1(a1), a2(a2), a3(a3) { }

		template <typename T>
		R <T> operator()(T& t) { return R <T> (t, d(), a1, a2, a3); }

		template <typename T>
		R <const T> operator()(const T& t) { return R <const T> (t, d(), a1, a2, a3); }
	};

public:
	nested operator()(A1 a1, A2 a2, A3 a3) const { return nested(extends <D>::d(), a1, a2, a3); }
};

//-----------------------------------------------------------------------------

}  // namespace qt_details

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_CONSTRUCTOR_HPP
