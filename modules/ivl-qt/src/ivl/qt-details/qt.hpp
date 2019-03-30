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

#ifndef IVL_QT_QT_HPP
#define IVL_QT_QT_HPP

//-----------------------------------------------------------------------------

#include "core.hpp"

#include "core/kernel/timer.hpp"

#include <QtGui>

#include "gui/kernel/widget_base.hpp"

#include "gui/kernel/action.hpp"
#include "gui/kernel/action_group.hpp"
#include "gui/kernel/application.hpp"
#include "gui/kernel/box_layout.hpp"
#include "gui/kernel/drag.hpp"
#include "gui/kernel/grid_layout.hpp"
#include "gui/kernel/stacked_layout.hpp"
#include "gui/kernel/widget.hpp"

#include "gui/dialogs/dialog.hpp"
#include "gui/dialogs/file_dialog.hpp"
#include "gui/dialogs/input_dialog.hpp"
#include "gui/dialogs/message_box.hpp"

#include "gui/graphics_view/graphics_scene.hpp"
#include "gui/graphics_view/graphics_view.hpp"

#include "gui/item_views/abstract_item_model.hpp"
#include "gui/item_views/abstract_list_model.hpp"
#include "gui/item_views/abstract_table_model.hpp"
#include "gui/item_views/dir_model.hpp"
#include "gui/item_views/file_system_model.hpp"
#include "gui/item_views/item_delegate.hpp"
#include "gui/item_views/list_view.hpp"
#include "gui/item_views/list_widget.hpp"
#include "gui/item_views/sort_filter_proxy_model.hpp"
#include "gui/item_views/string_list_model.hpp"
#include "gui/item_views/table_view.hpp"
#include "gui/item_views/table_widget.hpp"
#include "gui/item_views/tree_view.hpp"
#include "gui/item_views/tree_widget.hpp"

#include "gui/widgets/check_box.hpp"
#include "gui/widgets/combo_box.hpp"
#include "gui/widgets/date_time_edit.hpp"
#include "gui/widgets/date_edit.hpp"
#include "gui/widgets/dialog_button_box.hpp"
#include "gui/widgets/dock_widget.hpp"
#include "gui/widgets/group_box.hpp"
#include "gui/widgets/label.hpp"
#include "gui/widgets/line_edit.hpp"
#include "gui/widgets/mdi_area.hpp"
#include "gui/widgets/menu.hpp"
#include "gui/widgets/menu_bar.hpp"
#include "gui/widgets/main_window.hpp"
#include "gui/widgets/push_button.hpp"
#include "gui/widgets/radio_button.hpp"
#include "gui/widgets/slider.hpp"
#include "gui/widgets/spin_box.hpp"
#include "gui/widgets/splitter.hpp"
#include "gui/widgets/status_bar.hpp"
#include "gui/widgets/text_edit.hpp"
#include "gui/widgets/time_edit.hpp"
#include "gui/widgets/tool_bar.hpp"
#include "gui/widgets/tool_button.hpp"

//-----------------------------------------------------------------------------

#endif  // IVL_QT_QT_HPP
