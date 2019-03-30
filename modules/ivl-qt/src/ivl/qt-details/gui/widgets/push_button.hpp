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

#ifndef IVL_QT_GUI_WIDGETS_PUSH_BUTTON_HPP
#define IVL_QT_GUI_WIDGETS_PUSH_BUTTON_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QPushButton>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ push_button : public QPushButton,
	public widget_base <push_button>,
	public method_binder <push_button, QPushButton, QAbstractButton>
{
	Q_OBJECT
	typedef QPushButton T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QAbstractButton
	void pressed_()             { pressed(); }
	void released_()            { released(); }
	void clicked_(bool checked) { clicked(checked); }
	void toggled_(bool checked) { toggled(checked); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractButton
		#include "abstract_button_init.hpp"

		// QPushButton
#ifndef QT_NO_MENU
		bind(show_menu)     .to <&T::showMenu>();
#endif
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractButton
	#include "abstract_button_decl.hpp"

	// QPushButton
#ifndef QT_NO_MENU
	slot <void ()> show_menu;
#endif

//-----------------------------------------------------------------------------

	explicit push_button(QWidget* parent = 0) :
		QPushButton(parent) { init(); }

	explicit push_button(const QString& text, QWidget* parent = 0) :
		QPushButton(text, parent) { init(); }

	push_button(const QIcon& icon, const QString& text, QWidget* parent = 0) :
		QPushButton(icon, text, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::push_button;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_PUSH_BUTTON_HPP
