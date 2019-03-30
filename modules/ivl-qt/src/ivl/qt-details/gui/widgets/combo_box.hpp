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

#ifndef IVL_QT_GUI_WIDGETS_COMBO_BOX_HPP
#define IVL_QT_GUI_WIDGETS_COMBO_BOX_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QComboBox>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ combo_box : public QComboBox,
	public widget_base <combo_box>,
	public method_binder <combo_box, QComboBox>
{
	Q_OBJECT
	typedef QComboBox T;

private slots:

	void editTextChanged_(const QString &text)     { edit_text_changed(text); }
	void activated_(int index)                     { activated_0(index); }              // TODO: overloading
	void activated_(const QString &text)           { activated_1(text); }               // TODO: overloading
	void highlighted_(int index)                   { highlighted_0(index); }            // TODO: overloading
	void highlighted_(const QString &text)         { highlighted_1(text); }             // TODO: overloading
	void currentIndexChanged_(int index)           { current_index_changed_0(index); }  // TODO: overloading
	void currentIndexChanged_(const QString &text) { current_index_changed_1(text); }   // TODO: overloading

private:

	void init()
	{
		connect(this, SIGNAL(editTextChanged(const QString&)),     SLOT(editTextChanged_(const QString&)));
		connect(this, SIGNAL(activated(int)),                      SLOT(activated_(int)));
		connect(this, SIGNAL(activated(const QString&)),           SLOT(activated_(const QString&)));
		connect(this, SIGNAL(highlighted(int)),                    SLOT(highlighted_(int)));
		connect(this, SIGNAL(highlighted(const QString&)),         SLOT(highlighted_(const QString&)));
		connect(this, SIGNAL(currentIndexChanged(int)),            SLOT(currentIndexChanged_(int)));
		connect(this, SIGNAL(currentIndexChanged(const QString&)), SLOT(currentIndexChanged_(const QString&)));

		bind(clear)             .to <&T::clear>();
		bind(clear_edit_text)   .to <&T::clearEditText>();
		bind(set_edit_text)     .to <&T::setEditText>();
		bind(set_current_index) .to <&T::setCurrentIndex>();
	}

public:

//-----------------------------------------------------------------------------

	signal <void (const QString&)>  edit_text_changed;
	signal <void (int)>             activated_0;              // TODO: overloading
	signal <void (const QString&)>  activated_1;              // TODO: overloading
	signal <void (int)>             highlighted_0;            // TODO: overloading
	signal <void (const QString&)>  highlighted_1;            // TODO: overloading
	signal <void (int)>             current_index_changed_0;  // TODO: overloading
	signal <void (const QString&)>  current_index_changed_1;  // TODO: overloading

	slot <void ()>                clear;
	slot <void ()>                clear_edit_text;
	slot <void (const QString&)>  set_edit_text;
	slot <void (int)>             set_current_index;

//-----------------------------------------------------------------------------

	explicit combo_box(QWidget* parent = 0) :
		QComboBox(parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QComboBox&
operator<<(QComboBox& c, const QString& text) { c.addItem(text); return c; }

// TODO
// addItem ( const QString & text, const QVariant & userData = QVariant() )
// addItem ( const QIcon & icon, const QString & text, const QVariant & userData = QVariant() )

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::combo_box;
using qt_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_COMBO_BOX_HPP
