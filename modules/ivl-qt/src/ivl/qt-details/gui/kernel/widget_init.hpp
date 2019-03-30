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

	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
	              SLOT(customContextMenuRequested_(const QPoint&)));

	{
		typedef QWidget W;

		bind(set_enabled)          .to <W, &W::setEnabled>();
		bind(set_disabled)         .to <W, &W::setDisabled>();
		bind(set_window_modified)  .to <W, &W::setWindowModified>();
		bind(set_window_title)     .to <W, &W::setWindowTitle>();
	#ifndef QT_NO_STYLE_STYLESHEET
		bind(set_style_sheet)      .to <W, &W::setStyleSheet>();
	#endif
		bind(set_focus)            .to <W, &W::setFocus>();
		bind(update)               .to <W, &W::update>();
		bind(repaint)              .to <W, &W::repaint>();
		bind(set_visible)          .to <W, &W::setVisible>();
		bind(set_hidden)           .to <W, &W::setHidden>();
		bind(show)                 .to <W, &W::show>();
		bind(hide)                 .to <W, &W::hide>();
		bind(set_shown)            .to <W, &W::setShown>();
		bind(show_minimized)       .to <W, &W::showMinimized>();
		bind(show_maximized)       .to <W, &W::showMaximized>();
		bind(show_full_screen)     .to <W, &W::showFullScreen>();
		bind(show_normal)          .to <W, &W::showNormal>();
		bind(close)                .to <W, &W::close>();
		bind(raise)                .to <W, &W::raise>();
		bind(lower)                .to <W, &W::lower>();
	}

//-----------------------------------------------------------------------------
