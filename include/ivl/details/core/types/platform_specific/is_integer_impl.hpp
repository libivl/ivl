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

template <>
class is_integer<int8_t> : public types::t_true { };

template <>
class is_integer<uint8_t> : public types::t_true { };

template <>
class is_integer<int16_t> : public types::t_true { };

template <>
class is_integer<uint16_t> : public types::t_true { };

template <>
class is_integer<int32_t> : public types::t_true { };

template <>
class is_integer<uint32_t> : public types::t_true { };

template <>
class is_integer<int64_t> : public types::t_true { };

template <>
class is_integer<uint64_t> : public types::t_true { };

#ifndef _MSC_VER
// g++ has a special type for `char' which is neither
// int8_t nor int16_t but a type of its own, whatever implementation
// is used. So it has to be specially treated.
// This does not hold for unsigned char though.
template <>
class is_integer<char> : public types::t_true { };

#endif
