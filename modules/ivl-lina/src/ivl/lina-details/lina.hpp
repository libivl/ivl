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
#ifndef IVL_DETAILS_LINA_HPP
#define IVL_DETAILS_LINA_HPP

#include "ivl/details/core/platform_specific/push_macros.hpp"

//// ??
#include "ivl/details/core/platform_specific/msc_warnings.hpp"
//// ??


#include "lina/lapack_interface.hpp"
#include "lina/lapack/lapack_utils.hpp"

#include "lina/inv.hpp"
#include "lina/eig.hpp"
#include "lina/qr.hpp"
#include "lina/svd.hpp"
#include "lina/lu.hpp"
#include "lina/lina_functions.hpp"


#include "ivl/details/core/platform_specific/pop_macros.hpp"

#endif // IVL_DETAILS_LINA_HPP
