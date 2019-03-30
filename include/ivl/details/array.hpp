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

/*! \file ivl/array.hpp
    \brief Include this to use the array<T> class

    This is the file the library users need to include in order to use the
    array class.
*/

#ifndef IVL_DETAILS_ARRAY_HPP
#define IVL_DETAILS_ARRAY_HPP

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <complex>
#include <cmath>
#include <vector>
#include <algorithm>
#include <exception>
#include <cstddef>
#include <new>
#include <limits.h> // TODO: CHECK THIS



#include "core/platform_specific/push_macros.hpp"
#include "core/platform_specific/msc_warnings.hpp"
//#include "core/platform_specific/msc_stdint.hpp"
//#include "core/platform_specific/default_stdint.hpp"
#if _MSC_VER >= 1500 // above VC2005
#include <stdint.h> // CMake will add the dep dir automatically for MSVC
#elif _MSC_VER >= 1400 // VC2005
#include "depends/stdint/stdint.h"
#else
#include <stdint.h>
#endif

//-----------------------------------------------------------------------------

#include "core/common/fwd_decl.hpp"

//-----------------------------------------------------------------------------

#include "core/types.hpp"

//-----------------------------------------------------------------------------

// TODO: this is here until the issue for reference face is fixed.
// also power is in here and has to be moved. // scalar
#include "core/tuple/tuple.hpp" // mess
#include "core/types/scalar.hpp"
#include "core/types/fun.hpp"
//

//#include "core/tool/same_place_reverse_iterator.hpp"
#include "core/tool/util.hpp"
#include "core/tool/little_arrayling.hpp"
#include "core/tool/pointer_face.hpp"
////#include "core/tool/tuple.hpp"

#include "core/debug/debug.hpp"



////#include "core/data/data_base.hpp"


#include "core/types/array_iterator.hpp"
#include "core/data/data_array.hpp"
#include "core/types/derive.hpp"
#include "core/types/array.hpp"


//-----------------------------------------------------------------------------
#include "core/types/lists/impl/list.hpp"
#include "core/types/lists/impl/seq.hpp"
#include "core/types/lists/impl/types.hpp"
#include "core/types/lists/impl/tools/list_tools.hpp"

#include "core/types/match.hpp"
//-----------------------------------------------------------------------------

#include "core/key.hpp"

//-----------------------------------------------------------------------------


#include "core/data/conversions_array.hpp"




// math core
#include "core/math/cast.hpp"
#include "core/math/constant.hpp"
#include "core/math/limit.hpp"
#include "core/math/unary_functions.hpp"
#include "core/math/binary_functions.hpp"
#include "core/math/unary_operators.hpp"
#include "core/math/binary_operators.hpp"
#include "core/math/trigonometric.hpp"
//


// scalar
#include "core/types/scalar.hpp"
//



//#include "core/safety_check/force.hpp"

#include "core/keyword_operators/force.hpp"
#include "core/keyword_operators/rval.hpp"
//#include "core/operation/lval.hpp"
#include "core/keyword_operators/rvalue.hpp"
#include "core/keyword_operators/lvalue.hpp"
//#include "core/operation/by_ref.hpp"
//#include "core/operation/clone.hpp"
#include "core/keyword_operators/link.hpp"
#include "core/keyword_operators/ret.hpp"

#include "core/conversions/attr.hpp"


#include "core/ivl_func/ivl_func.hpp"



#include "core/loops/meta/loops_meta.hpp"
#include "core/loops/loops.hpp"
//note: here a function with the same name loops::loop is defined
//and is called by generic array<> operator=, so, we either have to
//forward declare or actually include the loops_nd file, before any
//loop(..) call is used to ensure the matching for nd loops.
//other option would be a forward declaration.
#include "core/loops/meta/loops_nd_meta.hpp"
#include "core/loops/meta/out_specialized.hpp"
#include "core/loops/meta/in_specialized.hpp"
#include "core/loops/loops_nd.hpp"
#include "core/loops/loop_ops.hpp"





#include "array/impl/array_base.hpp"

#include "array/impl/iterator/extended_traits.hpp"
#include "array/impl/iterator/iterator.hpp"
#include "array/impl/iterator/past_end_capable_iterator.hpp"


// member control is a utility that enables/disables
// members in class specializations. consider renaming
#include "core/data/member_control.hpp"

//#include "core/rvalue.hpp"
//#include "core/lvalue.hpp"


#include "array/impl/catarray.hpp"


#include "array/impl/common/array_common_tools.hpp"
#include "array/impl/specialization_details/elem_func/elem_func_tools.hpp"
#include "array/impl/specialization_details/subarray/subarray_tools.hpp"
#include "array/impl/specialization_details/catarray/catarray_tools.hpp"
#include "array/impl/specialization_details/ref_iterator/ref_iterator_tools.hpp"
#include "array/impl/specialization_details/fixed/fixed_storage.hpp"
#include "array/impl/specialization_details/subarray/subarray_iterator.hpp"
#include "array/impl/specialization_details/catarray/catarray_iterator.hpp"



#include "array/impl/repval.hpp"
#include "array/impl/member_array.hpp"
#include "array/impl/slice.hpp"
#include "array/impl/mask_array.hpp"
#include "array/impl/slice_array.hpp"
#include "array/impl/indirect_array.hpp"
#include "array/impl/subarray.hpp"
#include "array/impl/all_array.hpp"
#include "array/impl/elem_func.hpp"




#include "core/loops/loop_on.hpp"
#include "core/safety_check/safe_loop.hpp"




// the common functions for all the array specializations
#include "array/impl/common/fwd_decl.hpp"
#include "array/impl/common/conversions_array_common.hpp"
#include "array/impl/common/readwrite_array_common.hpp"
#include "array/impl/common/dependable_array_common.hpp"


////
#include "array/impl/elem_func.hpp"
#include "array/impl/elem_func_ptr.hpp"
////

// the actual elem-op classes of various functions
#include "core/math/array/unary_element_functions.hpp"
#include "core/math/array/binary_element_functions.hpp"
////

//
// the function-to-array *_elem keyword
#include "core/keyword_operators/elem.hpp"

//
#include "core/keyword_operators/elem_ptr.hpp"
#include "core/types/scalar_fptr.hpp"
//

//

#include "array/impl/common/array_common_base.hpp"




// --------------------------------------------------------------
// the array class including all specializations
// --------------------------------------------------------------
#include "array/impl/array.hpp"
// --------------------------------------------------------------



#include "core/conversions/array.hpp"




// this unit defines the derived classes X_elem_func that
// derive from a corresponding array
#include "array/impl/elem_func.hpp"
#include "array/impl/elem_func_ptr.hpp"

// elem functions were here: todo; delete this line.




#include "array/impl/range.hpp"

#include "array/impl/fixed_array.hpp"
#include "array/impl/ptr_interface.hpp"

//#include "array/slice_array.hpp"
#include "array/impl/index_array.hpp"


#include "array/impl/wrap_stl.hpp"

#include "array/impl/iter_array.hpp"


// underscore
#include "core/underscore/underscore.hpp"


// TODO: coding style
//--- functions ---


// the actual elem-op classes of various functions
#include "core/math/array/unary_element_functions.hpp"
#include "core/math/array/binary_element_functions.hpp"



#include "array/functions/assign_operators.hpp"

// from functions but this is in the array implementation include file
#include "array/functions/array_core_functions.hpp"
#include "array/functions/array_operators.hpp"


#include "core/platform_specific/pop_macros.hpp"

// iavr
#include "core/struct/dimension.hpp"
#include "core/ivl_func/vec_func.hpp" // --> ivl-func

//-----------------------------------------------------------------------------

#ifdef LISTIE

#include "core/types/lists/stream.hpp"

#else
#ifdef LISTY

#include "core/types/streamy.hpp"

#else

// #include "core/types/list/stream.hpp"

#endif
#endif

//-----------------------------------------------------------------------------

#endif // IVL_DETAILS_ARRAY_HPP
