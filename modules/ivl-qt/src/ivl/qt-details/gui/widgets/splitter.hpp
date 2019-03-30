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

#ifndef IVL_QT_GUI_WIDGETS_SPLITTER_HPP
#define IVL_QT_GUI_WIDGETS_SPLITTER_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QSplitter>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ splitter : public QSplitter,
	public widget_base <splitter>,
	public method_binder <splitter, QSplitter>
{
	Q_OBJECT
	typedef QSplitter T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint& p) { custom_context_menu_requested(p); }

	// QSplitter
	void splitterMoved_(int pos, int index) { splitter_moved(pos, index); }

private:

//-----------------------------------------------------------------------------

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QSplitter
		connect(this, SIGNAL(splitterMoved(int, int)), SLOT(splitterMoved_(int, int)));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QSplitter
	signal <void (int, int)> splitter_moved;

//-----------------------------------------------------------------------------

	explicit splitter(QWidget* parent = 0) :
		QSplitter(parent) { init(); }

	explicit splitter(Qt::Orientation orientation, QWidget* parent = 0) :
		QSplitter(orientation, parent) { init(); }

};

//-----------------------------------------------------------------------------

inline QSplitter&
operator<<(QSplitter& s, QWidget* w) { s.addWidget(w); return s; }

template <typename T>
inline QSplitter&
operator<<(QSplitter& s, const obj_stretch_arg <T>& stretch)
{
	s << stretch.object;
	s.setStretchFactor(s.count() - 1, stretch);
	return s;
}

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::splitter;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_WIDGETS_SPLITTER_HPP
