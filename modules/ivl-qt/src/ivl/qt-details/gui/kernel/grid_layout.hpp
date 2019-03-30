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

#ifndef IVL_QT_GUI_KERNEL_GRID_LAYOUT_HPP
#define IVL_QT_GUI_KERNEL_GRID_LAYOUT_HPP

#include <algorithm>
#include <QGridLayout>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

struct new_line_arg : constructor <new_line_arg (int)>
{
	int rows;
	new_line_arg(int r = 1) : rows(r) { }
};

struct tab_arg : constructor <tab_arg (int)>
{
	int cols;
	tab_arg(int c = 1) : cols(c) { }
};

//-----------------------------------------------------------------------------

struct row_spacing_arg : public spacing_arg
{
	row_spacing_arg(int v) : spacing_arg(v) { }
};

struct col_spacing_arg : public spacing_arg
{
	col_spacing_arg(int v) : spacing_arg(v) { }
};

struct row_stretch_arg : public stretch_arg
{
	row_stretch_arg(int v) : stretch_arg(v) { }
};

struct col_stretch_arg : public stretch_arg
{
	col_stretch_arg(int v) : stretch_arg(v) { }
};

//-----------------------------------------------------------------------------

template <typename T>
struct span_arg : public object_arg <T>
{
	int row, col;
	span_arg(T& o, int r, int c) : object_arg <T>(o), row(r), col(c) { }
};

template <typename T>
struct row_span_arg : public span_arg <T>
{
	row_span_arg(T& o, int r) : span_arg <T>(o, r, 1) { }
};

template <typename T>
struct col_span_arg : public span_arg <T>
{
	col_span_arg(T& o, int c) : span_arg <T>(o, 1, c) { }
};

//-----------------------------------------------------------------------------

static  __attribute__ ((unused))
new_line_arg new_line, nl_;

static  __attribute__ ((unused))
tab_arg tab;

static  __attribute__ ((unused))
constructor <row_spacing_arg (int)> row_spacing;

static  __attribute__ ((unused))
constructor <col_spacing_arg (int)> col_spacing;

static  __attribute__ ((unused))
constructor <row_stretch_arg (int)> row_stretch;

static  __attribute__ ((unused))
constructor <col_stretch_arg (int)> col_stretch;

static  __attribute__ ((unused))
constructor <row_span_arg <_> (int)> row_span;

static  __attribute__ ((unused))
constructor <col_span_arg <_> (int)> col_span;

static  __attribute__ ((unused))
constructor <span_arg <_> (int, int)> span;

//-----------------------------------------------------------------------------

class grid_layout : public QGridLayout
{
	typedef QGridLayout L;
	int at_row, at_col;

//-----------------------------------------------------------------------------

	void next(int cols = 1) { at_col += cols; }

	void add(const tab_arg& t) { next(t.cols); }
	void add(const new_line_arg& nl) { at_row += nl.rows; at_col = 0; }

	void add(QLayoutItem* item, int rows = 1, int cols = 1, ivl::alignment a = none)
	{
		L::addItem(item, at_row, at_col, rows, cols, a);
		next(cols);
	}

	void add(QLayout* layout, int rows = 1, int cols = 1, ivl::alignment a = none)
	{
		L::addLayout(layout, at_row, at_col, rows, cols, a);
		next(cols);
	}

	void add(QWidget* widget, int rows = 1, int cols = 1, ivl::alignment a = none)
	{
		L::addWidget(widget, at_row, at_col, rows, cols, a);
		next(cols);
	}

//-----------------------------------------------------------------------------

	template <typename T>
	void add(const span_arg <T>& span, ivl::alignment a)
	{
		add(span.object, span.row, span.col, a);
	}

	template <typename T>
	void add(const span_arg <T>& span, int = 1, int = 1, ivl::alignment a = none)
	{
		add(span.object, span.row, span.col, a);
	}

	template <typename T>
	void add(const align_arg <T>& align, int rows = 1, int cols = 1, ivl::alignment = none)
	{
		add(align.object, rows, cols, align);
	}

//-----------------------------------------------------------------------------

	void add(const row_spacing_arg& s)
	{
		L::setRowMinimumHeight(at_row, std::max(int(s), rowMinimumHeight(at_row)));
		next();
	}

	void add(const col_spacing_arg& s)
	{
		L::setColumnMinimumWidth(at_col, std::max(int(s), columnMinimumWidth(at_col)));
		next();
	}

	void add(const row_stretch_arg& s)
	{
		L::setRowStretch(at_row, std::max(int(s), rowStretch(at_row)));
		next();
	}

	void add(const col_stretch_arg& s)
	{
		L::setColumnStretch(at_col, std::max(int(s), columnStretch(at_col)));
		next();
	}

public:

//-----------------------------------------------------------------------------

	explicit grid_layout(QWidget* parent = 0) :
		QGridLayout(parent), at_row(0), at_col(0) { }

//-----------------------------------------------------------------------------

	template <typename T>
	grid_layout& operator<<(T& o) { add(o); return *this; }

	template <typename T>
	grid_layout& operator<<(const T& o) { add(o); return *this; }

};

//-----------------------------------------------------------------------------

} // qt_details

using qt_details::grid_layout;
using qt_details::new_line;
using qt_details::nl_;
using qt_details::tab;
using qt_details::row_spacing;
using qt_details::col_spacing;
using qt_details::row_stretch;
using qt_details::col_stretch;
using qt_details::row_span;
using qt_details::col_span;
using qt_details::span;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_GRID_LAYOUT_HPP
