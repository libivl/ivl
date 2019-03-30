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

#include <fstream>
#include <ivl/ivl>
#include <ivl/doc>

//-----------------------------------------------------------------------------

using namespace std;
using namespace ivl;

//-----------------------------------------------------------------------------

struct help_opt
{
	enum target { txt, html, tex };

	target format;
	string path;
	bool   recur;

	help_opt() : format(txt), path(""), recur(false) { }
};

//-----------------------------------------------------------------------------

struct help_args : public help_opt,
	public ivl_arguments <help_args, help_opt::target>
{
	static target upper(target) { return tex; }
	static const char* text_of(target f)
	{
		static const char* name[] = { "txt", "html", "tex" };
		return name[f];
	}

//-----------------------------------------------------------------------------

	template <typename S>
	void define(S& s)
	{
		set(s, format,  "format",   'f',  "output format",                    "{txt|html}");
		set(s, path,    "output",   'o',  "save output file(s) to <path>",    "path");
		set(s, recur,   "recur",    'r',  "display sub-topics recursively");
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

using doc::name_of;
using doc::content_of;

//-----------------------------------------------------------------------------

template <typename F, typename O>
class helper
{
	const O& opt;

//-----------------------------------------------------------------------------

	string ext() const
	{
		string x = opt(opt.format);
		return x == "html" ? "php" : x;
	}

//-----------------------------------------------------------------------------

	template <typename T>
	void output(const T& topic) const
	{
		static F format;

		if (opt.path.empty())
			cout << help[format](topic);

		else
		{
			string file = opt.path + '/' + name_of(topic) + '.' + ext();
			ofstream s(file.c_str());
			if (!(s.is_open())) opt.abort("cannot write to file " + file);
			s << !ansi << help[format](topic);
			s.close();
		}
	}

public:

//-----------------------------------------------------------------------------

	helper(const O& opt) : opt(opt) { }

	template <typename S, typename T>
	void operator()(S&, const T& topic) const { (*this)(topic); }

//-----------------------------------------------------------------------------

	void operator()() const { (*this)(opt[0]); }

	template <typename T>
	void operator()(const T& topic) const
	{
		output(topic);

		if (opt.recur)
			+(filter=*this)[_] << content_of(help(topic));
	}

};

//-----------------------------------------------------------------------------

template <typename F, typename O>
void run(F, const O& opt) { return helper <F, O>(opt)(); }

template <typename O>
void run(const O& opt)
{
	switch (opt.format)
	{
		case O::txt  : run(txt,  opt);  return;
// 		case O::html : run(txt,  opt);  return;
// 		case O::txt  : run(html, opt); return;
		case O::html : run(html, opt); return;
// 		case O::tex  : run(txt, opt);  return;
		default :
			opt.abort(+sstr() << "format not supported", opt(opt.format));
	}
}

//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	run(help_args(argc, argv));
}
