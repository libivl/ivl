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

#ifndef IVL_QT_GUI_DIALOGS_PRINT_DIALOG_HPP
#define IVL_QT_GUI_DIALOGS_PRINT_DIALOG_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QPrintDialog>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ print_dialog : public QPrintDialog,
	public widget_base <print_dialog>,
	public method_binder <print_dialog, QPrintDialog>
{
	Q_OBJECT
	typedef QPrintDialog T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint &p) { custom_context_menu_requested(p); }

	// QDialog
	void finished_(int i) { finished(i); }
	void accepted_()      { accepted(); }
	void rejected_()      { rejected(); }

	// QPrintDialog
	void accepted_(QPrinter* printer) { accepted_1(printer); }  // TODO: oveloading

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QDialog
		#include "dialog_init.hpp"

		// QPrintDialog
		connect(this, SIGNAL(accepted(QPrinter*)), SLOT(accepted_(QPrinter*)));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QDialog
	#include "dialog_decl.hpp"

	// QPrintDialog
	signal <void (QPrinter*)> accepted_1;  // TODO: oveloading

//-----------------------------------------------------------------------------

	explicit print_dialog(QWidget* parent = 0) :
		QPrintDialog(parent) { init(); }

	explicit print_dialog(QPrinter* printer, QWidget* parent = 0) :
		QPrintDialog(printer, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::print_dialog;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_DIALOGS_PRINT_DIALOG_HPP
