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

#ifndef IVL_CORE_DETAILS_TYPES_LIST_IMPL_HPP
#define IVL_CORE_DETAILS_TYPES_LIST_IMPL_HPP

//-----------------------------------------------------------------------------

#include "scheme/base/begin.hpp"
#include "scheme/base/token.hpp"
#include "scheme/base/pattern.hpp"
#include "scheme/base/form.hpp"
#include "scheme/base/define.hpp"

#include "intro/intro.hpp"

#include "data/list.hpp"
#include "data/model.hpp"
#include "data/tools.hpp"

#include "state/mem.hpp"
#include "state/env.hpp"
#include "state/access.hpp"
#include "state/lookup.hpp"

#include "eval/op.hpp"
#include "eval/eval.hpp"
#include "eval/function.hpp"
#include "eval/lazy.hpp"
#include "eval/partial.hpp"
#include "eval/form.hpp"

#ifdef IVL_LIST_LL
#include "low/form.hpp"
#include "low/prim.hpp"
#endif

#include "pattern/match.hpp"
#include "pattern/build.hpp"

#include "scheme/lang/id.hpp"
#include "scheme/lang/const.hpp"
#include "scheme/lang/fun.hpp"
#include "scheme/lang/form.hpp"
#include "scheme/lang/prim.hpp"

#include "scheme/lib/legacy.hpp"
#include "scheme/lib/fun.hpp"
#include "scheme/lib/num.hpp"
#include "scheme/lib/iter.hpp"
#include "scheme/lib/num_iter.hpp"
#include "scheme/lib/list.hpp"
#include "scheme/lib/tup.hpp"
#include "scheme/lib/set.hpp"

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_TYPES_LIST_IMPL_HPP
