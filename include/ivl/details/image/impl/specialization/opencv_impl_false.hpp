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


namespace image_details {

template<bool IMP, class P>
struct cv
{
	struct nimpl { };
	typedef nimpl iplimage_t;

	template<class T, class S>
	static void load(image<T, S>& im, const std::string filename, image_channels channels)
	{
		assert(0);
	}

	template<class T, class S>
	static void save(const image<T, S>& im, const std::string filename)
	{
		assert(0);
	}

	template <class T, class D>
	static void copy_from(image<T, D>& im, const iplimage_t* src)
	{
		assert(0);
	}

	template <class T, class D>
	static void copy_to(const image<T, D>& im, iplimage_t* dest)
	{
		assert(0);
	}

	template <class T, class D>
	static iplimage_t* ipl(const image<T, D>& im)
	{
		assert(0);
		return 0;
	}

};

} /* namespace image_details */

