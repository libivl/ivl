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

#ifndef IVL_QT_GUI_WIDGETS_LINE_EDIT_HPP
#define IVL_QT_GUI_WIDGETS_LINE_EDIT_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QLineEdit>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ line_edit : public QLineEdit,
	public widget_base <line_edit>,
	public method_binder <line_edit, QLineEdit>
{
	Q_OBJECT
	typedef QLineEdit T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QLineEdit
	void textChanged_(const QString& s)         { text_changed(s); }
	void textEdited_(const QString& s)          { text_edited(s); }
	void cursorPositionChanged_(int i1, int i2) { cursor_position_changed(i1, i2); }
	void returnPressed_()                       { return_pressed(); }
	void editingFinished_()                     { editing_finished(); }
	void selectionChanged_()                    { selection_changed(); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QLineEdit
		connect(this, SIGNAL(textChanged(const QString&)),     SLOT(textChanged_(const QString&)));
		connect(this, SIGNAL(textEdited(const QString&)),      SLOT(textEdited_(const QString&)));
		connect(this, SIGNAL(cursorPositionChanged(int, int)), SLOT(cursorPositionChanged_(int, int)));
		connect(this, SIGNAL(returnPressed()),                 SLOT(returnPressed_()));
		connect(this, SIGNAL(editingFinished()),               SLOT(editingFinished_()));
		connect(this, SIGNAL(selectionChanged()),              SLOT(selectionChanged_()));

		// QLineEdit
		bind(set_text)     .to <&T::setText>();
		bind(clear)        .to <&T::clear>();
		bind(select_all)   .to <&T::selectAll>();
		bind(undo)         .to <&T::undo>();
		bind(redo)         .to <&T::redo>();
#ifndef QT_NO_CLIPBOARD
		bind(cut)          .to <&T::cut>();
		const_bind(copy)   .to <&T::copy>();
		bind(paste)        .to <&T::paste>();
#endif
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QLineEdit
	signal <void (const QString&)>  text_changed;
	signal <void (const QString&)>  text_edited;
	signal <void (int, int)>        cursor_position_changed;
	signal <void ()>                return_pressed;
	signal <void ()>                editing_finished;
	signal <void ()>                selection_changed;

	// QLineEdit
	slot <void (const QString&)> set_text;
	slot <void ()>               clear;
	slot <void ()>               select_all;
	slot <void ()>               undo;
	slot <void ()>               redo;
#ifndef QT_NO_CLIPBOARD
	slot <void ()>               cut;
	slot <void ()>               copy;
	slot <void ()>               paste;
#endif

//-----------------------------------------------------------------------------

	explicit line_edit(QWidget* parent = 0) :
		QLineEdit(parent) { init(); }

	explicit line_edit(const QString& text, QWidget* parent = 0) :
		QLineEdit(text, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::line_edit;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_LINE_EDIT_HPP
