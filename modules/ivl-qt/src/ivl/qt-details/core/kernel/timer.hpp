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

#ifndef IVL_QT_GUI_CORE_TIMER_HPP
#define IVL_QT_GUI_CORE_TIMER_HPP

#include "../../core.hpp"
#include <QTimer>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class qslot : public QObject
{
	Q_OBJECT
	signal <void ()> activate;

public slots:
	void call() { activate(); }

public:
	template <typename D>
	qslot(const D& target) { activate.connect(target); }
};

//-----------------------------------------------------------------------------

class _ivlqt_export_ qtimer : public QTimer,
	public method_binder <qtimer, QTimer>
{
	Q_OBJECT
	typedef QTimer T;

private slots:

	// QTimer
	void timeout_() { timeout(); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QTimer
		connect(this, SIGNAL(timeout()), SLOT(timeout_()));

		// QTimer
		bind(start_0) .to <T, &T::start>();  // TODO: overloading
		bind(start_1) .to <T, &T::start>();  // TODO: overloading
		bind(stop)    .to <&T::stop>();
	}

public:

//-----------------------------------------------------------------------------

	// QTimer
	signal <void ()> timeout;

	// QTimer
	slot <void (int)> start_0;  // TODO: overloading
	slot <void ()>    start_1;  // TODO: overloading
	slot <void ()>    stop;

//-----------------------------------------------------------------------------

	explicit qtimer(QObject* parent = 0) : QTimer(parent) { init(); }

//-----------------------------------------------------------------------------

	template <typename D>
	static void single_shot(int msec, const D& receiver)
	{
		T::singleShot(msec, new qslot(receiver), SLOT(call()));
	}

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::qtimer;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_CORE_TIMER_HPP
