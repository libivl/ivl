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

#ifndef IVL_QT_GUI_ITEM_VIEWS_ITEM_DELEGATE_HPP
#define IVL_QT_GUI_ITEM_VIEWS_ITEM_DELEGATE_HPP

#include "../../core.hpp"
#include <QItemDelegate>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ item_delegate : public QItemDelegate,
	public method_binder <item_delegate, QItemDelegate, QAbstractItemDelegate>
{
	Q_OBJECT
	typedef QItemDelegate T;
	typedef QAbstractItemDelegate B;

private slots:

	// QAbstractItemDelegate
	void commitData_(QWidget* editor)               { commit_data(editor); }
	void closeEditor_(QWidget* editor, QAbstractItemDelegate::EndEditHint hint)
	                                                { close_editor(editor, hint); }
	void sizeHintChanged_(const QModelIndex& index) { size_hint_changed(index); }

private:

	void init()
	{
		// QAbstractItemDelegate
		connect(this, SIGNAL(commitData(QWidget*)),                SLOT(commitData_(QWidget*)));
		connect(this, SIGNAL(closeEditor(QWidget*, QAbstractItemDelegate::EndEditHint)),
                    SLOT(closeEditor_(QWidget*, QAbstractItemDelegate::EndEditHint)));
		connect(this, SIGNAL(sizeHintChanged(const QModelIndex&)), SLOT(sizeHintChanged_(const QModelIndex&)));

		// QAbstractItemDelegate
		bind(help_event).to <&B::helpEvent>();
	}

//-----------------------------------------------------------------------------

	typedef QAbstractItemDelegate::EndEditHint H;
	typedef defaults <void (QWidget*, H hint), c_enum <H, NoHint> >
		close_editor_signature;
	// defaults: (QWidget* editor, QAbstractItemDelegate::EndEditHint hint = NoHint)

public:

//-----------------------------------------------------------------------------

	// QAbstractItemDelegate
	signal <void (QWidget*)>           commit_data;
	signal <close_editor_signature>    close_editor;
	signal <void (const QModelIndex&)> size_hint_changed;

	// QAbstractItemDelegate
	slot <bool (QHelpEvent*, QAbstractItemView*, const QStyleOptionViewItem&,
	            const QModelIndex&)> help_event;

//-----------------------------------------------------------------------------

	explicit item_delegate(QObject* parent = 0) :
		QItemDelegate(parent) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::item_delegate;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_ITEM_DELEGATE_HPP
