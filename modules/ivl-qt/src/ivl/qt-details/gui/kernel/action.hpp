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

#ifndef IVL_QT_GUI_KERNEL_ACTION_HPP
#define IVL_QT_GUI_KERNEL_ACTION_HPP

#include "../../core.hpp"
#include <QAction>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ action : public QAction,
	public method_binder <action, QAction>
{
	Q_OBJECT
	typedef QAction T;

private slots:

	// QAction
	void changed_()               { changed(); }
	void triggered_(bool checked) { triggered(checked); }
	void hovered_()               { hovered(); }
	void toggled_(bool checked)   { toggled(checked); }

private:

	void init()
	{
		// QAction
		connect(this, SIGNAL(changed()),       SLOT(changed_()));
		connect(this, SIGNAL(triggered(bool)), SLOT(triggered_(bool)));
		connect(this, SIGNAL(hovered()),       SLOT(hovered_()));
		connect(this, SIGNAL(toggled(bool)),   SLOT(toggled_(bool)));

		// QAction
		bind(trigger)      .to <&T::trigger>();
		bind(hover)        .to <&T::hover>();
		bind(set_checked)  .to <&T::setChecked>();
		bind(toggle)       .to <&T::toggle>();
		bind(set_enabled)  .to <&T::setEnabled>();
		bind(set_disabled) .to <&T::setDisabled>();
		bind(set_visible)  .to <&T::setVisible>();
	}

//-----------------------------------------------------------------------------

	typedef defaults <void (bool), c_false>
	triggered_signature;  // defaults: (bool checked = false)

public:

//-----------------------------------------------------------------------------

	// QAction
	signal <void ()>              changed;
	signal <triggered_signature>  triggered;
	signal <void ()>              hovered;
	signal <void (bool)>          toggled;

	// QAction
	slot <void ()>      trigger;
	slot <void ()>      hover;
	slot <void (bool)>  set_checked;
	slot <void ()>      toggle;
	slot <void (bool)>  set_enabled;
	slot <void (bool)>  set_disabled;
	slot <void (bool)>  set_visible;

//-----------------------------------------------------------------------------

	explicit action(QObject* parent = 0) : QAction(parent) { init(); }

	action(const QString &text, QObject* parent = 0) :
		QAction(text, parent) { init(); }

	action(const QIcon &icon, const QString &text, QObject* parent = 0) :
		QAction(icon, text, parent) { init(); }

};

//-----------------------------------------------------------------------------

struct separator_action : public action
{
	separator_action() { setSeparator(true); }
};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::action;
using qt_details::separator_action;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_ACTION_HPP
