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

#ifndef IVL_QT_GUI_DIALOGS_MESSAGE_BOX_HPP
#define IVL_QT_GUI_DIALOGS_MESSAGE_BOX_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QMessageBox>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ message_box : public QMessageBox,
	public widget_base <message_box>,
	public method_binder <message_box, QMessageBox>
{
	Q_OBJECT
	typedef QMessageBox T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint &p) { custom_context_menu_requested(p); }

	// QDialog
	void finished_(int i) { finished(i); }
	void accepted_()      { accepted(); }
	void rejected_()      { rejected(); }

	// QMessageBox
	void buttonClicked_(QAbstractButton* button) { button_clicked(button); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QDialog
		#include "dialog_init.hpp"

		// QMessageBox
		connect(this, SIGNAL(buttonClicked(QAbstractButton*)), SLOT(buttonClicked_(QAbstractButton*)));

		// QMessageBox
#ifdef qdoc
		bind(exec).to <&T::exec>();
#endif
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QDialog
	#include "dialog_decl.hpp"

	// QMessageBox
	signal <void (QAbstractButton*)> button_clicked;

	// QMessageBox
#ifdef qdoc
	slot <int ()> exec;
#endif

//-----------------------------------------------------------------------------

	explicit message_box(QWidget* parent = 0) :
		QMessageBox(parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QMessageBox&
operator<<(QMessageBox& m, QMessageBox::StandardButton b) { m.addButton(b); return m; }

// TODO
// addButton ( QAbstractButton * button, ButtonRole role )
// addButton ( const QString & text, ButtonRole role )
// addButton ( StandardButton button )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::message_box;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_DIALOGS_MESSAGE_BOX_HPP
