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

#ifndef IVL_CORE_DETAILS_STREAM_IVL_ARGS_HPP
#define IVL_CORE_DETAILS_STREAM_IVL_ARGS_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace argument_details {

//-----------------------------------------------------------------------------

// handle command line arguments for ivl programs
template <
	typename D,
	typename E1 = term, typename E2 = term, typename E3 = term,
	typename E4 = term, typename E5 = term, typename E6 = term
>
class ivl_arguments : public arguments <D, E1, E2, E3, E4, E5, E6>
{
	typedef arguments <D, E1, E2, E3, E4, E5, E6> B;

public:

	// construct by command line arguments of main()
	ivl_arguments(int argc, char* argv[]) : B(argc, argv) { }

//-----------------------------------------------------------------------------
// methods in this block are treated as virtual (always called through der())

	// program version
	string version() const
	{
		return +sstr() <<
			IVL_VERSION_MAJOR << '.' <<
			IVL_VERSION_MINOR << '.' <<
			IVL_VERSION_PATCH;
	}

	// copyright
	string copyright() const
	{
		return
			"Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>\n"
			"Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>";
	}

	// license information
	string license() const
	{
		return
			"This is free software; see the source for copying conditions. "
			"There is NO warranty; not even for MERCHANTABILITY "
			"or FITNESS FOR A PARTICULAR PURPOSE.";
	}

// end of "virtual" block
//-----------------------------------------------------------------------------

};

//-----------------------------------------------------------------------------

}  // namespace argument_details

using argument_details::ivl_arguments;

//---------------------------------------------------------------------------------

} // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_STREAM_IVL_ARGS_HPP
