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

/*! \file ivl/image.hpp
    \brief Include this to use the image<T> class

    This is the file the library users need to include in order to use the
    image class of IVL.
*/
#ifndef IVL_DETAILS_IMAGE_HPP
#define IVL_DETAILS_IMAGE_HPP

// ............... :|  TODO fix.
#ifndef IVL_OPENCV
#define NO_OPENCV
#ifndef IVL_NO_OPENCV
#define IVL_NO_OPENCV
#endif
#endif
// |: ..................

#ifndef IVL_NO_OPENCV
#include "cv.h"
#include "highgui.h"
#endif /*IVL_NO_OPENCV*/

#include "core/platform_specific/push_macros.hpp"

#include "image/impl/common/fwd_decl.hpp"

#include "image/impl/color.hpp"
#include "image/impl/common/image_common_base.hpp"
#include "image/impl/image.hpp"

#include "core/conversions/image.hpp"


#include "image/impl/image_conversions.hpp"
//TODO: verify


//#endif /* NO_OPENCV */

#include "core/platform_specific/pop_macros.hpp"

#endif // IVL_DETAILS_IMAGE_HPP
