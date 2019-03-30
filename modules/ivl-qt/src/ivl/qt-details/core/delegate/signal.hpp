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

#ifndef IVL_QT_CORE_SIGNAL_HPP
#define IVL_QT_CORE_SIGNAL_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

template <typename D, typename E, typename G, typename S>
class signal_op_base;

//-----------------------------------------------------------------------------

template <typename D, typename E, typename G, typename R>
class signal_op_base <D, E, G, R ()>
{
	typedef R S();

	const G& sig() const { return static_cast <const G&>(*this); }

protected:
	const D& del() const { return static_cast <const D&>(sig()); }
	const E& evt() const { return static_cast <const E&>(sig()); }

	R op() const
	{
		evt().emit(invoker <S>());
		return del() ? del().D::operate() : R();
	}
};

//-----------------------------------------------------------------------------

template <typename D, typename E, typename G, typename R, typename A1>
class signal_op_base <D, E, G, R (A1)> :
	public signal_op_base <D, E, G, R ()>
{
	typedef R S(A1);
	typedef signal_op_base <D, E, G, R ()> B;

protected:
	using B::del; using B::evt; using B::op;

	R op(A1 a1) const
	{
		evt().emit(invoker <S>(a1));
		return del() ? del().D::operate(a1) : R();
	}
};

//-----------------------------------------------------------------------------

template <
	typename D, typename E, typename G, typename R,
	typename A1, typename A2
>
class signal_op_base <D, E, G, R (A1, A2)> :
	public signal_op_base <D, E, G, R (A1)>
{
	typedef R S(A1, A2);
	typedef signal_op_base <D, E, G, R (A1)> B;

protected:
	using B::del; using B::evt; using B::op;

	R op(A1 a1, A2 a2) const
	{
		evt().emit(invoker <S>(a1, a2));
		return del() ? del().D::operate(a1, a2) : R();
	}
};

//-----------------------------------------------------------------------------

template <
	typename D, typename E, typename G, typename R,
	typename A1, typename A2, typename A3
>
class signal_op_base <D, E, G, R (A1, A2, A3)> :
	public signal_op_base <D, E, G, R (A1, A2)>
{
	typedef R S(A1, A2, A3);
	typedef signal_op_base <D, E, G, R (A1, A2)> B;

protected:
	using B::del; using B::evt; using B::op;

	R op(A1 a1, A2 a2, A3 a3) const
	{
		evt().emit(invoker <S>(a1, a2, a3));
		return del() ? del().D::operate(a1, a2, a3) : R();
	}
};

//-----------------------------------------------------------------------------

template <
	typename D, typename E, typename G, typename R,
	typename A1, typename A2, typename A3, typename A4
>
class signal_op_base <D, E, G, R (A1, A2, A3, A4)> :
	public signal_op_base <D, E, G, R (A1, A2, A3)>
{
	typedef R S(A1, A2, A3, A4);
	typedef signal_op_base <D, E, G, R (A1, A2, A3)> B;

protected:
	using B::del; using B::evt; using B::op;

	R op(A1 a1, A2 a2, A3 a3, A4 a4) const
	{
		evt().emit(invoker <S>(a1, a2, a3, a4));
		return del() ? del().D::operate(a1, a2, a3, a4) : R();
	}
};

//-----------------------------------------------------------------------------

template <
	typename D, typename E, typename G, typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5
>
class signal_op_base <D, E, G, R (A1, A2, A3, A4, A5)> :
	public signal_op_base <D, E, G, R (A1, A2, A3, A4)>
{
	typedef R S(A1, A2, A3, A4, A5);
	typedef signal_op_base <D, E, G, R (A1, A2, A3, A4)> B;

protected:
	using B::del; using B::evt; using B::op;

	R op(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const
	{
		evt().emit(invoker <S>(a1, a2, a3, a4, a5));
		return del() ? del().D::operate(a1, a2, a3, a4, a5) : R();
	}
};

//-----------------------------------------------------------------------------

template <typename SD, typename S>
class signal_base;

template <typename SD, typename S>
struct signal_op :
	public slot <SD>,
	public event <S>,
	public signal_op_base <slot <SD>, event <S>, signal_base <SD, S>, S>
	{ };

//-----------------------------------------------------------------------------

template <typename SD, typename R>
class signal_base <SD, R ()> : public signal_op <SD, R ()>
{
	typedef signal_op <SD, R ()> OP;

protected:
	R operate() const { return OP::op(); }
};

//-----------------------------------------------------------------------------

template <typename SD, typename R, typename A1>
class signal_base <SD, R (A1)> : public signal_op <SD, R (A1)>
{
	typedef signal_op <SD, R (A1)> OP;

protected:
	R operate()      const { return OP::op(); }
	R operate(A1 a1) const { return OP::op(a1); }
};

//-----------------------------------------------------------------------------

template <typename SD, typename R, typename A1, typename A2>
class signal_base <SD, R (A1, A2)> : public signal_op <SD, R (A1, A2)>
{
	typedef signal_op <SD, R (A1, A2)> OP;

protected:
	R operate()             const { return OP::op(); }
	R operate(A1 a1)        const { return OP::op(a1); }
	R operate(A1 a1, A2 a2) const { return OP::op(a1, a2); }
};

//-----------------------------------------------------------------------------

template <typename SD, typename R, typename A1, typename A2, typename A3>
class signal_base <SD, R (A1, A2, A3)> : public signal_op <SD, R (A1, A2, A3)>
{
	typedef signal_op <SD, R (A1, A2, A3)> OP;

protected:
	R operate()                    const { return OP::op(); }
	R operate(A1 a1)               const { return OP::op(a1); }
	R operate(A1 a1, A2 a2)        const { return OP::op(a1, a2); }
	R operate(A1 a1, A2 a2, A3 a3) const { return OP::op(a1, a2, a3); }
};

//-----------------------------------------------------------------------------

template <
	typename SD, typename R,
	typename A1, typename A2, typename A3, typename A4
>
class signal_base <SD, R (A1, A2, A3, A4)> :
	public signal_op <SD, R (A1, A2, A3, A4)>
{
	typedef signal_op <SD, R (A1, A2, A3, A4)> OP;

protected:
	R operate()                           const { return OP::op(); }
	R operate(A1 a1)                      const { return OP::op(a1); }
	R operate(A1 a1, A2 a2)               const { return OP::op(a1, a2); }
	R operate(A1 a1, A2 a2, A3 a3)        const { return OP::op(a1, a2, a3); }
	R operate(A1 a1, A2 a2, A3 a3, A4 a4) const { return OP::op(a1, a2, a3, a4); }
};

//-----------------------------------------------------------------------------

template <
	typename SD, typename R,
	typename A1, typename A2, typename A3, typename A4, typename A5
>
class signal_base <SD, R (A1, A2, A3, A4, A5)> :
	public signal_op <SD, R (A1, A2, A3, A4, A5)>
{
	typedef signal_op <SD, R (A1, A2, A3, A4, A5)> OP;

protected:
	R operate()                                  const { return OP::op(); }
	R operate(A1 a1)                             const { return OP::op(a1); }
	R operate(A1 a1, A2 a2)                      const { return OP::op(a1, a2); }
	R operate(A1 a1, A2 a2, A3 a3)               const { return OP::op(a1, a2, a3); }
	R operate(A1 a1, A2 a2, A3 a3, A4 a4)        const { return OP::op(a1, a2, a3, a4); }
	R operate(A1 a1, A2 a2, A3 a3, A4 a4, A5 a5) const { return OP::op(a1, a2, a3, a4, a5); }
};

//-----------------------------------------------------------------------------

template <typename SD>
struct signal : public signal_base <SD, typename signature <SD>::type> { };

//-----------------------------------------------------------------------------

}  // namespace delegate_details

using delegate_details::signal;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_SIGNAL_HPP
