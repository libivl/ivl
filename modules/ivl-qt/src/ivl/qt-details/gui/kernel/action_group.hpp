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

#ifndef IVL_QT_GUI_KERNEL_ACTION_GROUP_HPP
#define IVL_QT_GUI_KERNEL_ACTION_GROUP_HPP

#include "../../core.hpp"
#include <QActionGroup>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ action_group : public QActionGroup,
	public method_binder <action_group, QActionGroup>
{
	Q_OBJECT
	typedef QActionGroup T;

private slots:

	// QActionGroup
	void triggered_(QAction* action) { triggered(action); }
	void hovered_(QAction* action)   { hovered(action); }

private:

	void init()
	{
		// QActionGroup
		connect(this, SIGNAL(triggered(QAction*)), SLOT(triggered_(QAction*)));
		connect(this, SIGNAL(hovered(QAction*)),   SLOT(hovered_(QAction*)));

		// QActionGroup
		bind(set_enabled)   .to <&T::setEnabled>();
		bind(set_disabled)  .to <&T::setDisabled>();
		bind(set_visible)   .to <&T::setVisible>();
		bind(set_exclusive) .to <&T::setExclusive>();
	}

public:

//-----------------------------------------------------------------------------

	// QActionGroup
	signal <void (QAction*)> triggered;
	signal <void (QAction*)> hovered;

	// QActionGroup
	slot <void (bool)>   set_enabled;
	slot <void (bool b)> set_disabled;
	slot <void (bool)>   set_visible;
	slot <void (bool)>   set_exclusive;

//-----------------------------------------------------------------------------

	explicit action_group(QObject* parent) : QActionGroup(parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QActionGroup&
operator<<(QActionGroup& g, QAction* a) { g.addAction(a); return g; }

inline QActionGroup&
operator<<(QActionGroup& g, const QString& s) { g.addAction(s); return g; }

// TODO
// addAction ( QAction * action )
// addAction ( const QString & text )
// addAction ( const QIcon & icon, const QString & text )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::action_group;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_ACTION_GROUP_HPP
