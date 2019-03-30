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

#ifndef IVL_QT_GUI_WIDGETS_STATUS_BAR_HPP
#define IVL_QT_GUI_WIDGETS_STATUS_BAR_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QStatusBar>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ status_bar : public QStatusBar,
	public widget_base <status_bar>,
	public method_binder <status_bar, QStatusBar>
{
	Q_OBJECT
	typedef QStatusBar T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QStatusBar
	void messageChanged_(const QString& text) { message_changed(text); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QStatusBar
		connect(this, SIGNAL(messageChanged(const QString&)),  SLOT(messageChanged_(const QString&)));

		// QStatusBar
		bind(show_message)  .to <&T::showMessage>();
		bind(clear_message) .to <&T::clearMessage>();
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QStatusBar
	signal <void (const QString&)> message_changed;

	// QStatusBar
	slot <void (const QString&, int)> show_message;
	slot <void ()>                    clear_message;

//-----------------------------------------------------------------------------

	explicit status_bar(QWidget* parent = 0) :
		QStatusBar(parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QStatusBar&
operator<<(QStatusBar& s, QWidget* w) { s.addWidget(w); return s; }

// TODO
// addPermanentWidget ( QWidget * widget, int stretch = 0 )
// addWidget ( QWidget * widget, int stretch = 0 )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::status_bar;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_STATUS_BAR_HPP
