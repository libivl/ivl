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

#ifndef IVL_QT_GUI_ITEM_VIEWS_FILE_SYSTEM_MODEL_HPP
#define IVL_QT_GUI_ITEM_VIEWS_FILE_SYSTEM_MODEL_HPP

#include "../../core.hpp"
#include <QFileSystemModel>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ file_system_model : public QFileSystemModel,
	public method_binder <file_system_model, QFileSystemModel>
{
	Q_OBJECT
	typedef QFileSystemModel T;

private slots:

	// QAbstractItemModel
	void dataChanged_(const QModelIndex& top_left, const QModelIndex& bottom_right) { data_changed(top_left, bottom_right); }
	void headerDataChanged_(Qt::Orientation orient, int from, int to)               { header_data_changed(orient, from, to); }
	void layoutChanged_()                                                           { layout_changed(); }
	void layoutAboutToBeChanged_()                                                  { layout_about_to_be_changed(); }
	void rowsAboutToBeInserted_    (const QModelIndex& parent, int from, int to)    { rows_about_to_be_inserted    (parent, from, to); }
	void rowsInserted_             (const QModelIndex& parent, int from, int to)    { rows_inserted                (parent, from, to); }
	void rowsAboutToBeRemoved_     (const QModelIndex& parent, int from, int to)    { rows_about_to_be_removed     (parent, from, to); }
	void rowsRemoved_              (const QModelIndex& parent, int from, int to)    { rows_removed                 (parent, from, to); }
	void columnsAboutToBeInserted_ (const QModelIndex& parent, int from, int to)    { columns_about_to_be_inserted (parent, from, to); }
	void columnsInserted_          (const QModelIndex& parent, int from, int to)    { columns_inserted             (parent, from, to); }
	void columnsAboutToBeRemoved_  (const QModelIndex& parent, int from, int to)    { columns_about_to_be_removed  (parent, from, to); }
	void columnsRemoved_           (const QModelIndex& parent, int from, int to)    { columns_removed              (parent, from, to); }
	void modelAboutToBeReset_()                                                     { model_about_to_be_reset(); }
	void modelReset_()                                                              { model_reset(); }
	void rowsAboutToBeMoved_    (const QModelIndex& parent, int from, int to, const QModelIndex& dest, int row) { rows_about_to_be_moved    (parent, from, to, dest, row); }
	void rowsMoved_             (const QModelIndex& parent, int from, int to, const QModelIndex& dest, int row) { rows_moved                (parent, from, to, dest, row); }
	void columnsAboutToBeMoved_ (const QModelIndex& parent, int from, int to, const QModelIndex& dest, int col) { columns_about_to_be_moved (parent, from, to, dest, col); }
	void columnsMoved_          (const QModelIndex& parent, int from, int to, const QModelIndex& dest, int col) { columns_moved             (parent, from, to, dest, col); }

	// QFileSystemModel
	void rootPathChanged_(const QString& new_path)                                           { root_path_changed(new_path); }
	void fileRenamed_(const QString& path, const QString& old_name, const QString& new_name) { file_renamed(path, old_name, new_name); }
	void directoryLoaded_(const QString& path)                                               { directory_loaded(path); }

private:

	void init()
	{
		// QAbstractItemModel
		#include "abstract_item_model_init.hpp"

		// QFileSystemModel
		connect(this, SIGNAL(rootPathChanged(const QString&)),                             SLOT(rootPathChanged_(const QString&)));
		connect(this, SIGNAL(fileRenamed(const QString&, const QString&, const QString&)), SLOT(fileRenamed_(const QString&, const QString&, const QString&)));
		connect(this, SIGNAL(directoryLoaded(const QString&)),                             SLOT(directoryLoaded_(const QString&)));
	}

public:

//-----------------------------------------------------------------------------

	// QAbstractItemModel
	#include "abstract_item_model_decl.hpp"

	// QFileSystemModel
	signal <void (const QString&)>                                 root_path_changed;
	signal <void (const QString&, const QString&, const QString&)> file_renamed;
	signal <void (const QString&)>                                 directory_loaded;

//-----------------------------------------------------------------------------

	explicit file_system_model(QObject* parent = 0) :
		QFileSystemModel(parent) { init(); }
};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::file_system_model;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_ITEM_VIEWS_FILE_SYSTEM_MODEL_HPP

