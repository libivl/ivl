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

#ifndef IVL_QT_GUI_KERNEL_APPLICATION_HPP
#define IVL_QT_GUI_KERNEL_APPLICATION_HPP

#include "../../core.hpp"
#include <QApplication>

namespace ivl {

//-----------------------------------------------------------------------------

namespace qt_details {

//-----------------------------------------------------------------------------

class _ivlqt_export_ application : public QApplication,
	public method_binder <application, QApplication, QCoreApplication>
{
	Q_OBJECT
	typedef QApplication T;
	typedef QCoreApplication B;

private slots:

	// QCoreApplication
	void aboutToQuit_()     { about_to_quit(); }
	void unixSignal_(int i) { unix_signal(i); }

	// QApplication
	void lastWindowClosed_()                       { last_window_closed(); }
	void focusChanged_(QWidget *old, QWidget *now) { focus_changed(old, now); }
	void fontDatabaseChanged_()                    { font_database_changed(); }
#ifndef QT_NO_SESSIONMANAGER
	void commitDataRequest_(QSessionManager &m)    { commit_data_request(m); }
	void saveStateRequest_(QSessionManager &m)     { save_state_request(m); }
#endif

private:

//-----------------------------------------------------------------------------

	void init()
	{
		static_init();

		// QCoreApplication
		connect(this, SIGNAL(aboutToQuit()),   SLOT(aboutToQuit_()));
		connect(this, SIGNAL(unixSignal(int)), SLOT(unixSignal_(int)));

		// QApplication
		connect(this, SIGNAL(lastWindowClosed()),                  SLOT(lastWindowClosed_()));
		connect(this, SIGNAL(focusChanged(QWidget*, QWidget*)),    SLOT(focusChanged_(QWidget*, QWidget*)));
		connect(this, SIGNAL(fontDatabaseChanged()),               SLOT(fontDatabaseChanged_()));
#ifndef QT_NO_SESSIONMANAGER
		connect(this, SIGNAL(commitDataRequest(QSessionManager&)), SLOT(commitDataRequest_(QSessionManager&)));
		connect(this, SIGNAL(saveStateRequest(QSessionManager&)),  SLOT(saveStateRequest_(QSessionManager&)));
#endif

		// QApplication
#ifndef QT_NO_STYLE_STYLESHEET
		bind(set_style_sheet)               .to <&T::setStyleSheet>();
#endif
#ifdef Q_WS_WINCE
		bind(set_auto_maximize_threshold)   .to <&T::setAutoMaximizeThreshold>();
		const_bind(auto_maximize_threshold) .to <&T::autoMaximizeThreshold>();
#endif
#if QT_VERSION >= 0x040600 // ivl: for Qt versions < 4.6
		bind(set_auto_sip_enabled)          .to <&T::setAutoSipEnabled>();
		const_bind(auto_sip_enabled)        .to <&T::autoSipEnabled>();
#endif
	}

//-----------------------------------------------------------------------------

	static void static_init()
	{
		static bool global_initialized = false;
		if(global_initialized)
			return;
		global_initialized = true;

		// QCoreApplication
		quit .bind <&B::quit>();

		// QApplication
		close_all_windows .bind <&T::closeAllWindows>();
		about_qt          .bind <&T::aboutQt>();
	}

public:

//-----------------------------------------------------------------------------

	// QCoreApplication
	signal <void ()>    about_to_quit;
	signal <void (int)> unix_signal;

	// QCoreApplication
	static slot <void ()> quit;

	// QApplication
	signal <void ()>                    last_window_closed;
	signal <void (QWidget*, QWidget*)>  focus_changed;
	signal <void ()>                    font_database_changed;
#ifndef QT_NO_SESSIONMANAGER
	signal <void (QSessionManager&)>    commit_data_request;
	signal <void (QSessionManager&)>    save_state_request;
#endif

	// QApplication
#ifndef QT_NO_STYLE_STYLESHEET
	slot <void (const QString&)>  set_style_sheet;
#endif
#ifdef Q_WS_WINCE
	slot <void (const int)>       set_auto_maximize_threshold;
	slot <int ()>                 auto_maximize_threshold;
#endif
#if QT_VERSION >= 0x040600 // ivl: for Qt versions < 4.6
	slot <void (const bool)>      set_auto_sip_enabled;
	slot <bool ()>                auto_sip_enabled;
#endif
	static slot <void ()>         close_all_windows;
	static slot <void ()>         about_qt;

//-----------------------------------------------------------------------------

#ifndef qdoc
	application(int &argc, char **argv, int version = QT_VERSION) :
		QApplication(argc, argv, version) { init(); }

	application(int &argc, char **argv, bool GUIenabled, int version = QT_VERSION) :
		QApplication(argc, argv, GUIenabled, version) { init(); }

	application(int &argc, char **argv, Type type, int version = QT_VERSION) :
		QApplication(argc, argv, type, version) { init(); }

#if defined(Q_WS_X11)
	application(Display* dpy, Qt::HANDLE visual = 0, Qt::HANDLE cmap = 0,
					int version = QT_VERSION) :
		QApplication(dpy, visual, cmap, version) { init(); }

	application(Display *dpy, int &argc, char **argv, Qt::HANDLE visual = 0,
					 Qt::HANDLE cmap= 0, int version = QT_VERSION) :
		QApplication(dpy, argc, argv, visual, cmap, version) { init(); }
#endif
#if defined(Q_OS_SYMBIAN)
	application(QApplication::QS60MainApplicationFactory factory,
					int &argc, char **argv, int version = QT_VERSION) :
		QApplication(factory, argc, argv, version) { init(); }
#endif
#endif

#if defined(Q_INTERNAL_QAPP_SRC) || defined(qdoc)
	application(int &argc, char **argv) :
		QApplication(argc, argv) { init(); }

	application(int &argc, char **argv, bool GUIenabled) :
		QApplication(argc, argv, GUIenabled) { init(); }

	application(int &argc, char **argv, Type type) :
		QApplication(argc, argv, type) { init(); }

#if defined(Q_WS_X11)
	application(Display* dpy, Qt::HANDLE visual = 0, Qt::HANDLE cmap = 0) :
		QApplication(dpy, visual, cmap) { init(); }

	QApplication(Display *dpy, int &argc, char **argv,
					 Qt::HANDLE visual = 0, Qt::HANDLE cmap= 0) :
		QApplication(dpy, argc, argv, visual, cmap) { init(); }
#endif
#if defined(Q_OS_SYMBIAN) || defined(qdoc)
	application(QApplication::QS60MainApplicationFactory factory,
					int &argc, char **argv) :
		QApplication(factory, argc, argv) { init(); }
#endif
#endif

};

//-----------------------------------------------------------------------------

}  // qt_details

using qt_details::application;

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_QT_GUI_KERNEL_APPLICATION_HPP
