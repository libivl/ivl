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


template <> struct to_signed<bool> : public to_type <char> { };

template <> struct to_signed<uint8_t> : public to_type <int8_t> { };

template <> struct to_signed<uint16_t> : public to_type <int16_t> { };

template <> struct to_signed<uint32_t> : public to_type <int32_t> { };

template <> struct to_signed<uint64_t> : public to_type <int64_t> { };

//---------------------------------------------------------------------------

template <> struct to_unsigned<int8_t> : public to_type<uint8_t> { };

template <> struct to_unsigned<int16_t> : public to_type <uint16_t> { };

template <> struct to_unsigned<int32_t> : public to_type <uint32_t> { };

template <> struct to_unsigned<int64_t> : public to_type <uint64_t> { };


#ifndef _MSC_VER
// g++ has a special type for `char' which is neither
// int8_t nor int16_t but a type of its own, whatever implementation
// is used. So it has to be specially treated.
// This does not hold for unsigned char though.
template <> struct to_unsigned<char> : public to_type <unsigned char> { };
#endif
