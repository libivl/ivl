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

#ifndef IVL_QT_GUI_WIDGETS_DIALOG_BUTTON_BOX_HPP
#define IVL_QT_GUI_WIDGETS_DIALOG_BUTTON_BOX_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QDialogButtonBox>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ dialog_button_box : public QDialogButtonBox,
	public widget_base <dialog_button_box>,
	public method_binder <dialog_button_box, QDialogButtonBox>
{
	Q_OBJECT
	typedef QDialogButtonBox T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QDialogButtonBox
	void clicked_(QAbstractButton* b) { clicked(b); }
	void accepted_()                  { accepted(); }
	void helpRequested_()             { help_requested(); }
	void rejected_()                  { rejected(); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QDialogButtonBox
		connect(this, SIGNAL(clicked(QAbstractButton*)), SLOT(clicked_(QAbstractButton*)));
		connect(this, SIGNAL(accepted()),                SLOT(accepted_()));
		connect(this, SIGNAL(helpRequested()),           SLOT(helpRequested_()));
		connect(this, SIGNAL(rejected()),                SLOT(rejected_()));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QDialogButtonBox
	signal <void (QAbstractButton*)> clicked;
	signal <void ()>                 accepted;
	signal <void ()>                 help_requested;
	signal <void ()>                 rejected;

//-----------------------------------------------------------------------------

	dialog_button_box(QWidget* parent = 0) :
		QDialogButtonBox(parent) { init(); }

	dialog_button_box(Qt::Orientation orientation, QWidget* parent = 0) :
		QDialogButtonBox(orientation, parent) { init(); }

	dialog_button_box(StandardButtons buttons,
							Qt::Orientation orientation = Qt::Horizontal,
						   QWidget* parent = 0) :
		QDialogButtonBox(buttons, orientation, parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QDialogButtonBox&
operator<<(QDialogButtonBox& d, QDialogButtonBox::StandardButton b) { d.addButton(b); return d; }

// TODO
// addButton ( QAbstractButton * button, ButtonRole role )
// addButton ( const QString & text, ButtonRole role )
// addButton ( StandardButton button )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::dialog_button_box;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_DIALOG_BUTTON_BOX_HPP
