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

#include <ivl/ivl>
#include <ivl/doc>

//-----------------------------------------------------------------------------

using namespace std;
using namespace ivl;

//-----------------------------------------------------------------------------

struct help_opt
{
	// dummy options
	bool detail;
	bool has_backup;
	string backup;
	bool has_quote;
	string quote;
	string owner;
	int bound;
	float exp;

	// real options
	string path;
	bool rec;

	help_opt() :

		// dummy options
		detail(true), has_backup(false), backup("good"),
		has_quote(false), quote("hello"), owner(""),
		bound(43), exp(1e-9),

		// real options
		path(""), rec(false)
		{ }
};

struct help_args : public help_opt, public ivl_arguments <help_args>
{
	template <typename S>
	void define(S& s)
	{
		section("Dummy options:");
		set(s, detail,  "detail",     'd',  "detailed system scan");
		set(s, quote,   "quote",      'q',  "quote characters from <string>",   "string",    has_quote);
		set(s, backup,  "backup",     '\0', "backup all help using <method>",   "method",    has_backup);
		set(s, owner,   "owner",      'w',  "force <name> as owner",            "name");
		set(s, bound,   "bound",      'b',  "use <number> as an upper bound",   "number");
		set(s, exp,     "exp",        'e',  "set exponent to <float>",          "float");

		section("Real options:");
		set(s, path,    "output",     'o',  "save all output to <path>",        "path");
		set(s, rec,     "recurse",    'r',  "recurse into sub-topics");
	}

	string title()  const { return "ivl help"; }
	string inputs() const { return "[<topic>]"; }

	string info() const
	{
		return
			"Display help on <topic>, "
			"or list available topics if no <topic> is given.";
	}

	help_args(int argc, char* argv[]) : ivl_arguments(argc, argv) { }

};

//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	help_args opt(argc, argv);
	opt.display();
	const array <string>& free = opt.free();
	cout << "free = " << free << nl;
}
