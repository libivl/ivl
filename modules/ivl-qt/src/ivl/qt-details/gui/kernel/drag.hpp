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

#ifndef IVL_QT_GUI_KERNEL_DRAG_HPP
#define IVL_QT_GUI_KERNEL_DRAG_HPP

#include "../../core.hpp"
#include <QDrag>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ drag : public QDrag,
	public method_binder <drag, QDrag>
{
	Q_OBJECT
	typedef QDrag T;

private slots:

	// QDrag
	void actionChanged_(Qt::DropAction action) { action_changed(action); }
	void targetChanged_(QWidget* target)       { target_changed(target); }

private:

	void init()
	{
		// QDrag
		connect(this, SIGNAL(actionChanged(Qt::DropAction)), SLOT(actionChanged_(Qt::DropAction)));
		connect(this, SIGNAL(targetChanged(QWidget*)),       SLOT(targetChanged_(QWidget*)));
	}

public:

//-----------------------------------------------------------------------------

	// QDrag
	signal <void (Qt::DropAction)> action_changed;
	signal <void (QWidget*)>       target_changed;

//-----------------------------------------------------------------------------

	explicit drag(QWidget* source = 0) : QDrag(source) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::drag;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_DRAG_HPP
