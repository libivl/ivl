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

#ifndef IVL_QT_GUI_WIDGETS_DATE_TIME_EDIT_HPP
#define IVL_QT_GUI_WIDGETS_DATE_TIME_EDIT_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QDateTimeEdit>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ date_time_edit : public QDateTimeEdit,
	public widget_base <date_time_edit>,
	public method_binder <date_time_edit, QDateTimeEdit>
{
	Q_OBJECT
	typedef QDateTimeEdit T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QAbstractSpinBox
	void editingFinished_() { editing_finished(); }

	// QDateTimeEdit
	void dateTimeChanged_(const QDateTime& date) { date_time_changed(date); }
	void timeChanged_(const QTime& date)         { time_changed(date); }
	void dateChanged_(const QDate& date)         { date_changed(date); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QAbstractSpinBox
		#include "abstract_spin_box_init.hpp"

		// QDateTimeEdit
		#include "date_time_edit_init.hpp"
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QAbstractSpinBox
	#include "abstract_spin_box_decl.hpp"

	// QDateTimeEdit
	#include "date_time_edit_decl.hpp"

//-----------------------------------------------------------------------------

	explicit date_time_edit(QWidget* parent = 0) :
		QDateTimeEdit(parent) { init(); }

	explicit date_time_edit(const QDateTime& dt, QWidget* parent = 0) :
		QDateTimeEdit(dt, parent) { init(); }

	explicit date_time_edit(const QDate& d, QWidget* parent = 0) :
		QDateTimeEdit(d, parent) { init(); }

	explicit date_time_edit(const QTime& t, QWidget* parent = 0) :
		QDateTimeEdit(t, parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::date_time_edit;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_DATE_TIME_EDIT_HPP
