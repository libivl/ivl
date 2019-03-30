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

#ifndef IVL_QT_GUI_DIALOGS_FILE_DIALOG_HPP
#define IVL_QT_GUI_DIALOGS_FILE_DIALOG_HPP

#include "../../core.hpp"
#include "../kernel/widget_base.hpp"
#include <QFileDialog>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ file_dialog : public QFileDialog,
	public widget_base <file_dialog>,
	public method_binder <file_dialog, QFileDialog>
{
	Q_OBJECT
	typedef QFileDialog T;

private slots:

	// QWidget
	void customContextMenuRequested_(const QPoint &p) { custom_context_menu_requested(p); }

	// QDialog
	void finished_(int i) { finished(i); }
	void accepted_()      { accepted(); }
	void rejected_()      { rejected(); }

	// QFileDialog
	void fileSelected_(const QString &file)            { file_selected(file); }
	void filesSelected_(const QStringList &files)      { files_selected(files); }
	void currentChanged_(const QString &path)          { current_changed(path); }
	void directoryEntered_(const QString &directory)   { directory_entered(directory); }
	void filterSelected_(const QString &filter)        { filter_selected(filter); }

private:

	void init()
	{
		// QWidget
		#include "../kernel/widget_init.hpp"

		// QDialog
		#include "dialog_init.hpp"

		// QFileDialog
		connect(this, SIGNAL(fileSelected(const QString&)),      SLOT(fileSelected_(const QString&)));
		connect(this, SIGNAL(filesSelected(const QStringList&)), SLOT(filesSelected_(const QStringList&)));
		connect(this, SIGNAL(currentChanged(const QString&)),    SLOT(currentChanged_(const QString&)));
		connect(this, SIGNAL(directoryEntered(const QString&)),  SLOT(directoryEntered_(const QString&)));
		connect(this, SIGNAL(filterSelected(const QString&)),    SLOT(filterSelected_(const QString&)));
	}

public:

//-----------------------------------------------------------------------------

	// QWidget
	#include "../kernel/widget_decl.hpp"

	// QDialog
	#include "dialog_decl.hpp"

	// QFileDialog
	signal <void (const QString&)>     file_selected;
	signal <void (const QStringList&)> files_selected;
	signal <void (const QString&)>     current_changed;
	signal <void (const QString&)>     directory_entered;
	signal <void (const QString&)>     filter_selected;

//-----------------------------------------------------------------------------

	file_dialog(QWidget* parent, Qt::WindowFlags flags) :
		QFileDialog(parent, flags) { init(); }

	explicit file_dialog(QWidget* parent = 0,
	                     const QString &caption = QString(),
	                     const QString &directory = QString(),
	                     const QString &filter = QString()) :
		QFileDialog(parent, caption, directory, filter) { init(); }

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::file_dialog;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_DIALOGS_FILE_DIALOG_HPP
