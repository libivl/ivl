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

#ifndef IVL_QT_GUI_DIALOGS_DIALOG_HPP
#define IVL_QT_GUI_DIALOGS_DIALOG_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QDialog>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ dialog : public QDialog, public widget_base <dialog>,
	public method_binder <dialog, QDialog>
{
	Q_OBJECT

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint &p) { custom_context_menu_requested(p); }

	// QDialog
	void finished_(int i) { finished(i); }
	void accepted_()      { accepted(); }
	void rejected_()      { rejected(); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QDialog
		#include "dialog_init.hpp"
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QDialog
	#include "dialog_decl.hpp"

//-----------------------------------------------------------------------------

	explicit dialog(QWidget* parent = 0, Qt::WindowFlags flags = 0) :
		QDialog(parent, flags) { init(); }

};

//-----------------------------------------------------------------------------

// TODO: reimplement all QDialog virtual methods in dialog (see flowchart_picker sample)

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::dialog;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_DIALOGS_DIALOG_HPP
