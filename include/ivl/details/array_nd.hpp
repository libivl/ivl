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

/*! \file ivl/array_nd.hpp
    \brief Include this to use the array_nd<T> class

    This is the file the library users need to include in order to use the
    array_nd class.
*/
#ifndef IVL_DETAILS_ARRAY_ND_HPP
#define IVL_DETAILS_ARRAY_ND_HPP

#include "core/platform_specific/push_macros.hpp"

#include "array_nd/impl/common/fwd_decl.hpp"

#include "core/data/data_array_nd.hpp"
#include "core/data/conversions_array_nd.hpp"

//#include "array/impl/iterator/past_end_capable_iterator.hpp": moved to array
#include "array_nd/impl/iterator/iterator_nd.hpp"
#include "array_nd/impl/iterator/iterator_nd_interface.hpp"
#include "array_nd/impl/iterator/switch_nd.hpp"
#include "array_nd/impl/subarray_details/subarray_nd_tools.hpp"
#include "array_nd/impl/subarray_details/subarray_nd_iterator.hpp"
#include "array_nd/impl/catarray_details/catarray_nd_tools.hpp"
#include "array_nd/impl/catarray_details/catarray_nd_iterator.hpp"

#include "core/loops/meta/loops_nd_meta.hpp"
#include "core/loops/meta/out_specialized.hpp"
#include "core/loops/meta/in_specialized.hpp"
#include "core/loops/loops_nd.hpp"


#include "array_nd/impl/common/resize_details.hpp"
#include "array_nd/impl/common/array_nd_common_base.hpp"

#include "array_nd/impl/array_nd.hpp"
//TODO:delete:#include "details/array_nd/impl/cat_array.hpp"


#include "core/conversions/array_nd.hpp"

#include "array_nd/impl/iter_array_nd.hpp"


#include "array_nd/functions/array_nd_core_functions.hpp"


//#include "details/array_nd/gslice_array.hpp"
//#include "details/array_nd/sub_array.hpp"

#include "core/platform_specific/pop_macros.hpp"

#endif // IVL_DETAILS_ARRAY_ND_HPP
