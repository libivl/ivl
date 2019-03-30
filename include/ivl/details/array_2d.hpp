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

/*! \file ivl/array_2d.hpp
    \brief Include this to use the array_2d<T> class

    This is the file the library users need to include in order to use the
    array_2d class.
*/
#ifndef IVL_DETAILS_ARRAY_2D_HPP
#define IVL_DETAILS_ARRAY_2D_HPP

#include "core/platform_specific/push_macros.hpp"

#include "array_2d/impl/common/fwd_decl.hpp"

#include "array_2d/impl/iterator/wrap_2d_iterator.hpp"

//matrix based
#include "core/keyword_operators/matrix_based.hpp"

#include "array_2d/impl/common/array_2d_common_base.hpp"

#include "array_2d/impl/array_2d.hpp"


#include "core/conversions/array_2d.hpp"


#include "array_2d/functions/array_2d_core_functions.hpp"


#include "core/platform_specific/pop_macros.hpp"

#endif // IVL_DETAILS_ARRAY_2D_HPP
