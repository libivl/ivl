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

/* types.hpp : includes files of the types namespace
 */

#ifndef IVL_CORE_DETAILS_TYPES_HPP
#define IVL_CORE_DETAILS_TYPES_HPP

//-----------------------------------------------------------------------------

#include "types/entity.hpp"
#include "types/extraction.hpp"
#include "types/template.hpp"
#include "types/identifier.hpp"
#include "types/t_func/logic.hpp"
#include "types/functional.hpp"
#include "types/numeric.hpp"

#include "data/data_base.hpp"

#include "types/t_func/lang_types.hpp"
#include "types/detect.hpp"
#include "types/t_func/array_types.hpp"
#include "types/t_func/evolution.hpp"
#include "types/t_func/var.hpp"

#include "types/lazy.hpp"
#include "types/lazy_defs.hpp"

#include "types/t_func/max.hpp"
#include "types/maps.hpp"

// iavr
#include "types/constant.hpp"
#include "types/overload.hpp"
#include "types/type_id.hpp"

//-----------------------------------------------------------------------------

#ifdef LISTIE

#include "types/templ.hpp"
#include "types/lists/list.hpp"

#else
#ifdef LISTY

#include "types/listy.hpp"
#include "types/lisp.hpp"

#ifndef LISTY_NOMACRO

#include "types/macroy.hpp"

#endif
#else

// #include "types/list/impl.hpp"

#endif
#endif

//-----------------------------------------------------------------------------

#endif // IVL_CORE_DETAILS_TYPES_HPP
