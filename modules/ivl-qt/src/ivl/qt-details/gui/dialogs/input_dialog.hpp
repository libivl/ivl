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

#ifndef IVL_QT_GUI_DIALOGS_INPUT_DIALOG_HPP
#define IVL_QT_GUI_DIALOGS_INPUT_DIALOG_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QInputDialog>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ input_dialog : public QInputDialog,
	public widget_base <input_dialog>,
	public method_binder <input_dialog, QInputDialog>
{
	Q_OBJECT
	typedef QInputDialog T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint &p) { custom_context_menu_requested(p); }

	// QDialog
	void finished_(int i) { finished(i); }
	void accepted_()      { accepted(); }
	void rejected_()      { rejected(); }

	// QInputDialog
	void textValueChanged_(const QString& text)  { text_value_changed(text); }
	void textValueSelected_(const QString& text) { text_value_selected(text); }
	void intValueChanged_(int value)             { int_value_changed(value); }
	void intValueSelected_(int value)            { int_value_selected(value); }
	void doubleValueChanged_(double value)       { double_value_changed(value); }
	void doubleValueSelected_(double value)      { double_value_selected(value); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QDialog
		#include "dialog_init.hpp"

		// QInputDialog
		connect(this, SIGNAL(textValueChanged(const QString&)),  SLOT(textValueChanged_(const QString&)));
		connect(this, SIGNAL(textValueSelected(const QString&)), SLOT(textValueSelected_(const QString&)));
		connect(this, SIGNAL(intValueChanged(int)),              SLOT(intValueChanged_(int)));
		connect(this, SIGNAL(intValueSelected(int)),             SLOT(intValueSelected_(int)));
		connect(this, SIGNAL(doubleValueChanged(double)),        SLOT(doubleValueChanged_(double)));
		connect(this, SIGNAL(doubleValueSelected(double)),       SLOT(doubleValueSelected_(double)));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QDialog
	#include "dialog_decl.hpp"

	// QInputDialog
	signal <void (const QString&)> text_value_changed;
	signal <void (const QString&)> text_value_selected;
	signal <void (int)>            int_value_changed;
	signal <void (int)>            int_value_selected;
	signal <void (double)>         double_value_changed;
	signal <void (double)>         double_value_selected;

//-----------------------------------------------------------------------------

	input_dialog(QWidget* parent = 0, Qt::WindowFlags flags = 0) :
		QInputDialog(parent, flags) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::input_dialog;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_DIALOGS_INPUT_DIALOG_HPP
