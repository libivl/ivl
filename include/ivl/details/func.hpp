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

#ifndef IVL_DETAILS_FUNC_HPP
#define IVL_DETAILS_FUNC_HPP

//-----------------------------------------------------------------------------

#include "core/struct.hpp"

//-----------------------------------------------------------------------------

// iavr
#include "func/sstr.hpp"
#include "func/to.hpp"
#include "func/find.hpp"
#include "func/flip.hpp"
#include "func/first.hpp"
#include "func/last.hpp"
#include "func/join.hpp"
#include "func/split.hpp"
#include "func/partition.hpp"
#include "func/sort.hpp"
#include "func/unique.hpp"
#include "func/is_space.hpp"

//-----------------------------------------------------------------------------

// kimon
#include "func/meshgrid.hpp"
#include "func/grid.hpp"
#include "func/rand.hpp"
#include "func/padarray.hpp"

//-----------------------------------------------------------------------------

// TODO: rewrite
// #include "func/set_functions.hpp"

//-----------------------------------------------------------------------------

#include "core/doc.hpp"
#include "core/stream/args.hpp"
#include "core/stream/ivl_args.hpp"
#include "core/key/stream.hpp"

//-----------------------------------------------------------------------------

#endif // IVL_DETAILS_FUNC_HPP
