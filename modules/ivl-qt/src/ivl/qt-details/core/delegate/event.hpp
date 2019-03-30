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

#ifndef IVL_QT_CORE_EVENT_HPP
#define IVL_QT_CORE_EVENT_HPP

#include <list>
#include <algorithm>

namespace ivl {

//-----------------------------------------------------------------------------

namespace delegate_details {

//-----------------------------------------------------------------------------

template <typename S> class event
{
	typedef delegate <S> D;
	typedef std::list <D> L;

	typedef typename L::iterator I;
	typedef typename L::const_iterator CI;
	typedef typename L::reverse_iterator RI;

	L slots;

public:

//-----------------------------------------------------------------------------

	typedef D slot_type;

	template <typename F>
	void connect(const F& slot) { connect(slot.template adapt <S>()); }
	void connect(const D& slot) { slots.push_back(slot); }

	void disconnect() { slots.clear(); }

	template <typename F>
	void disconnect(const F& slot) { disconnect(slot.template adapt <S>()); }
	void disconnect(const D& slot)
	{
		RI i = std::find(slots.rbegin(), slots.rend(), slot);
		if (i != slots.rend()) slots.erase(i);
	}

	template <typename F>
	void disconnect_all(const F& slot) { disconnect_all(slot.template adapt <S>()); }
	void disconnect_all(const D& slot)
	{
		RI i = slots.rbegin(), e = slots.rend();
		while ((i = std::find(i, e, slot)) != e)
			slots.erase(i);
	}

	template <typename INV>
	void emit(INV const& invoker) const
	{
		for (CI i = slots.begin(), e = slots.end(); i != e; i++)
			if (*i) invoker(*i);
	}

};

//-----------------------------------------------------------------------------

}  // namespace delegate_details

using delegate_details::event;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_CORE_EVENT_HPP
