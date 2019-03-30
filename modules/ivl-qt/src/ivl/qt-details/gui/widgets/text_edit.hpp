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

#ifndef IVL_QT_GUI_WIDGETS_TEXT_EDIT_HPP
#define IVL_QT_GUI_WIDGETS_TEXT_EDIT_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QTextEdit>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ text_edit : public QTextEdit,
	public widget_base <text_edit>,
	public method_binder <text_edit, QTextEdit>
{
	Q_OBJECT
	typedef QTextEdit T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QTextEdit
	void textChanged_()               { text_changed(); }
	void undoAvailable_(bool b)       { undo_available(b); }
	void redoAvailable_(bool b)       { redo_available(b); }
	void currentCharFormatChanged_
	     (const QTextCharFormat &f)   { current_char_format_changed(f); }
	void copyAvailable_(bool b)       { copy_available(b); }
	void selectionChanged_()          { selection_changed(); }
	void cursorPositionChanged_()     { cursor_position_changed(); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QTextEdit
		connect(this, SIGNAL(textChanged()),              SLOT(textChanged_()));
		connect(this, SIGNAL(undoAvailable(bool)),        SLOT(undoAvailable_(bool)));
		connect(this, SIGNAL(redoAvailable(bool)),        SLOT(redoAvailable_(bool)));
		connect(this, SIGNAL(currentCharFormatChanged
		                     (const QTextCharFormat&)),   SLOT(currentCharFormatChanged_(const QTextCharFormat&)));
		connect(this, SIGNAL(copyAvailable(bool)),        SLOT(copyAvailable_(bool)));
		connect(this, SIGNAL(selectionChanged()),         SLOT(selectionChanged_()));
		connect(this, SIGNAL(cursorPositionChanged()),    SLOT(cursorPositionChanged_()));

		// QTextEdit
		bind(set_font_point_size)         .to <&T::setFontPointSize>();
		bind(set_font_family)             .to <&T::setFontFamily>();
		bind(set_font_weight)             .to <&T::setFontWeight>();
		bind(set_font_underline)          .to <&T::setFontUnderline>();
		bind(set_font_italic)             .to <&T::setFontItalic>();
		bind(set_text_color)              .to <&T::setTextColor>();
		bind(set_text_background_color)   .to <&T::setTextBackgroundColor>();
		bind(set_current_font)            .to <&T::setCurrentFont>();
		bind(set_alignment)               .to <&T::setAlignment>();

		bind(set_plain_text)              .to <&T::setPlainText>();
		bind(insert_plain_text)           .to <&T::insertPlainText>();
#ifndef QT_NO_TEXTHTMLPARSER
		bind(set_html)                    .to <&T::setHtml>();
		bind(insert_html)                 .to <&T::insertHtml>();
#endif
		bind(set_text)                    .to <&T::setText>();
#ifndef QT_NO_CLIPBOARD
		bind(cut)                         .to <&T::cut>();
		bind(copy)                        .to <&T::copy>();
		bind(paste)                       .to <&T::paste>();
#endif
		bind(undo)                        .to <&T::undo>();
		bind(redo)                        .to <&T::redo>();
		bind(clear)                       .to <&T::clear>();
		bind(select_all)                  .to <&T::selectAll>();
		bind(append)                      .to <&T::append>();
		bind(scroll_to_anchor)            .to <&T::scrollToAnchor>();
		bind(zoom_in)                     .to <&T::zoomIn,  c_int <1> >();  // defaults: (int range = 1)
		bind(zoom_out)                    .to <&T::zoomOut, c_int <1> >();  // defaults: (int range = 1)
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QTextEdit
	signal <void ()>                        text_changed;
	signal <void (bool)>                    undo_available;
	signal <void (bool)>                    redo_available;
	signal <void (const QTextCharFormat&)>  current_char_format_changed;
	signal <void (bool)>                    copy_available;
	signal <void ()>                        selection_changed;
	signal <void ()>                        cursor_position_changed;

	// QTextEdit
	slot <void (qreal)>            set_font_point_size;
	slot <void (const QString&)>   set_font_family;
	slot <void (int)>              set_font_weight;
	slot <void (bool)>             set_font_underline;
	slot <void (bool)>             set_font_italic;
	slot <void (const QColor&)>    set_text_color;
	slot <void (const QColor&)>    set_text_background_color;
	slot <void (const QFont&)>     set_current_font;
	slot <void (Qt::Alignment)>    set_alignment;

	slot <void (const QString&)>   set_plain_text;
	slot <void (const QString&)>   insert_plain_text;
#ifndef QT_NO_TEXTHTMLPARSER
	slot <void (const QString&)>   set_html;
	slot <void (const QString&)>   insert_html;
#endif
	slot <void (const QString&)>   set_text;
#ifndef QT_NO_CLIPBOARD
	slot <void ()>                 cut;
	slot <void ()>                 copy;
	slot <void ()>                 paste;
#endif
	slot <void ()>                 undo;
	slot <void ()>                 redo;
	slot <void ()>                 clear;
	slot <void ()>                 select_all;
	slot <void (const QString&)>   append;
	slot <void (const QString&)>   scroll_to_anchor;
	slot <void (int)>              zoom_in;
	slot <void (int)>              zoom_out;

//-----------------------------------------------------------------------------

	explicit text_edit(QWidget* parent = 0) :
		QTextEdit(parent) { init(); }

	explicit text_edit(const QString& text, QWidget* parent = 0) :
		QTextEdit(text, parent) { init(); }

};

//-----------------------------------------------------------------------------

// TODO: QTextDocument

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::text_edit;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_TEXT_EDIT_HPP
