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

#ifndef IVL_QT_GUI_WIDGETS_LABEL_HPP
#define IVL_QT_GUI_WIDGETS_LABEL_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QLabel>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ label : public QLabel, public widget_base <label>,
	public method_binder <label, QLabel>
{
	Q_OBJECT
	typedef QLabel T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QLabel
	void linkActivated_(const QString &l)   { link_activated(l); }
	void linkHovered_(const QString &l)     { link_hovered(l); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QLabel
		connect(this, SIGNAL(linkActivated(const QString&)), SLOT(linkActivated_(const QString&)));
		connect(this, SIGNAL(linkHovered(const QString&)),   SLOT(linkHovered_(const QString&)));

		// QLabel
		bind(set_text)    .to <&T::setText>();
		bind(set_pixmap)  .to <&T::setPixmap>();
#ifndef QT_NO_PICTURE
		bind(set_picture) .to <&T::setPicture>();
#endif
#ifndef QT_NO_MOVIE
		bind(set_movie)   .to <&T::setMovie>();
#endif
		bind(set_num_0)   .to <T, &T::setNum>();  // TODO: overloading
		bind(set_num_1)   .to <T, &T::setNum>();  // TODO: overloading
		bind(clear)       .to <&T::clear>();

//-----------------------------------------------------------------------------

// TODO: remove (experimental overloading)

// 		bind(set_num._<void (int)>())    .to <T, &T::setNum>();
// 		bind(set_num._<void (double)>()) .to <T, &T::setNum>();
//
// 		bind(set_num._<0>()) .to <T, &T::setNum>();
// 		bind(set_num._<1>()) .to <T, &T::setNum>();
//
// 		set_num(3);
// 		set_num(1.3);

	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QLabel
	signal <void (const QString&)> link_activated;
	signal <void (const QString&)> link_hovered;

	// QLabel
	slot <void (const QString&)>  set_text;
	slot <void (const QPixmap&)>  set_pixmap;
#ifndef QT_NO_PICTURE
	slot <void (const QPicture&)> set_picture;
#endif
#ifndef QT_NO_MOVIE
	slot <void (QMovie*)>         set_movie;
#endif
	slot <void (int)>             set_num_0;  // TODO: overloading
	slot <void (double)>          set_num_1;  // TODO: overloading
	slot <void ()>                clear;

//-----------------------------------------------------------------------------

// TODO: remove (experimental overloading)
// 	multi_delegate <void (int), void (double)> set_num;

//-----------------------------------------------------------------------------

	explicit label(QWidget* parent = 0, Qt::WindowFlags flags = 0) :
		QLabel(parent, flags) { init(); }

	explicit label(const QString& text, QWidget* parent = 0,
						Qt::WindowFlags flags = 0) :
		QLabel(text, parent, flags) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::label;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_LABEL_HPP
