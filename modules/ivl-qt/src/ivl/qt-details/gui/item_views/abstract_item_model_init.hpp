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

//-----------------------------------------------------------------------------

	connect(this, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),     SLOT(dataChanged_(const QModelIndex&, const QModelIndex&)));
	connect(this, SIGNAL(headerDataChanged(Qt::Orientation, int, int)),            SLOT(headerDataChanged_(Qt::Orientation, int, int)));
	connect(this, SIGNAL(layoutChanged()),                                         SLOT(layoutChanged_()));
	connect(this, SIGNAL(layoutAboutToBeChanged()),                                SLOT(layoutAboutToBeChanged_()));
	connect(this, SIGNAL(rowsAboutToBeInserted    (const QModelIndex&, int, int)), SLOT(rowsAboutToBeInserted_    (const QModelIndex&, int, int)));
	connect(this, SIGNAL(rowsInserted             (const QModelIndex&, int, int)), SLOT(rowsInserted_             (const QModelIndex&, int, int)));
	connect(this, SIGNAL(rowsAboutToBeRemoved     (const QModelIndex&, int, int)), SLOT(rowsAboutToBeRemoved_     (const QModelIndex&, int, int)));
	connect(this, SIGNAL(rowsRemoved              (const QModelIndex&, int, int)), SLOT(rowsRemoved_              (const QModelIndex&, int, int)));
	connect(this, SIGNAL(columnsAboutToBeInserted (const QModelIndex&, int, int)), SLOT(columnsAboutToBeInserted_ (const QModelIndex&, int, int)));
	connect(this, SIGNAL(columnsInserted          (const QModelIndex&, int, int)), SLOT(columnsInserted_          (const QModelIndex&, int, int)));
	connect(this, SIGNAL(columnsAboutToBeRemoved  (const QModelIndex&, int, int)), SLOT(columnsAboutToBeRemoved_  (const QModelIndex&, int, int)));
	connect(this, SIGNAL(columnsRemoved           (const QModelIndex&, int, int)), SLOT(columnsRemoved_           (const QModelIndex&, int, int)));
	connect(this, SIGNAL(modelAboutToBeReset()),                                   SLOT(modelAboutToBeReset_()));
	connect(this, SIGNAL(modelReset()),                                            SLOT(modelReset_()));
	connect(this, SIGNAL(rowsAboutToBeMoved    (const QModelIndex&, int, int, const QModelIndex&, int)), SLOT(rowsAboutToBeMoved_    (const QModelIndex&, int, int, const QModelIndex&, int)));
	connect(this, SIGNAL(rowsMoved             (const QModelIndex&, int, int, const QModelIndex&, int)), SLOT(rowsMoved_             (const QModelIndex&, int, int, const QModelIndex&, int)));
	connect(this, SIGNAL(columnsAboutToBeMoved (const QModelIndex&, int, int, const QModelIndex&, int)), SLOT(columnsAboutToBeMoved_ (const QModelIndex&, int, int, const QModelIndex&, int)));
	connect(this, SIGNAL(columnsMoved          (const QModelIndex&, int, int, const QModelIndex&, int)), SLOT(columnsMoved_          (const QModelIndex&, int, int, const QModelIndex&, int)));

	{
		typedef QAbstractItemModel A;

		bind(submit) .to <A, &A::submit>();
		bind(revert) .to <A, &A::revert>();
	}

//-----------------------------------------------------------------------------
