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

#ifndef IVL_CORE_DETAILS_STREAM_ARGS_HPP
#define IVL_CORE_DETAILS_STREAM_ARGS_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace argument_details {

using std::cerr;
using std::cout;
using std::string;
using std::map;
using types::term;

//-----------------------------------------------------------------------------

namespace key {

using key_grp::style;

struct emph   : public style <emph>    { using KEY::operator=; };

}  // namespace key

static __attribute__ ((unused))  key::emph    emph;

//-----------------------------------------------------------------------------

namespace style_def {

using keys::lists::_;

template <typename S> S& operator<<(S& s, key::emph)  { return s << (_, bright); }

}  // namespace style_def

using ivl::operator<<;
using style_def::operator<<;

//-----------------------------------------------------------------------------

// enum <--> text converter
template <typename E, typename D>
class enum_conv
{
	struct inverse : public map <string, E>
	{
		inverse()
		{
			for (E z, n = D::lower(z); n <= D::upper(z); n = E(n+1))
				(*this)[D::text_of(n)] = n;
		}
	};

protected:

	static bool input(E& n, const string& s)
	{
		static const inverse map;

		typename inverse::const_iterator i = map.find(s);
		return i == map.end() ? false : (n = i->second, true);
	}

	static string output(E n) { return D::text_of(n); }

//-----------------------------------------------------------------------------

public:
	static E lower(E) { return E(0); }
	string operator()(E n) const { return D::text_of(n); }

};

//-----------------------------------------------------------------------------

// list of enum converters
template <
	typename D,
	typename E1 = term, typename E2 = term, typename E3 = term,
	typename E4 = term, typename E5 = term, typename E6 = term
>
class enum_list : public enum_conv <E1, D>,
	public enum_list <D, E2, E3, E4, E5, E6>
{
protected:
	using enum_conv <E1, D>::input;
	using enum_conv <E1, D>::output;
	using enum_list <D, E2, E3, E4, E5, E6>::input;
	using enum_list <D, E2, E3, E4, E5, E6>::output;
};

template <typename D>
class enum_list <D>
{
protected:
	static void input();
	static void output();
};

//-----------------------------------------------------------------------------

// handle command line arguments
template <
	typename D,
	typename E1 = term, typename E2 = term, typename E3 = term,
	typename E4 = term, typename E5 = term, typename E6 = term
>
class arguments : public enum_list <D, E1, E2, E3, E4, E5, E6>
{

//-----------------------------------------------------------------------------

	// TODO: elsewhere
	static string filename(const string& s)
	{
		size_t p = s.rfind('/');
		return p == string::npos ? s : s.length() > p + 1 ? s.substr(p + 1) : "";
	}

	// TODO: elsewhere
	static string strip(const string& s, char c)
	{
		return s.empty() ? "" : s[0] == c ? s.substr(1) : s;
	}

//-----------------------------------------------------------------------------

	typedef some_of <arguments> some;

	using enum_list <D, E1, E2, E3, E4, E5, E6>::input;
	using enum_list <D, E1, E2, E3, E4, E5, E6>::output;

//-----------------------------------------------------------------------------

	// representation of given argument values
	struct val : public string
	{
		bool used, val_used;

		val(const char* s)   : string(s), used(false), val_used(false) { }
		val(const string& s) : string(s), used(false), val_used(false) { }

		string key() const
		{
			size_t p = find('=');
			return p == string::npos ? *(*this) : substr(0, p);
		}

		string value() const
		{
			size_t p = find('=');
			return p != string::npos && length() > p + 1 ? substr(p + 1) : "";
		}

		string&       operator*()       { return static_cast <string&>      (*this); }
		const string& operator*() const { return static_cast <const string&>(*this); }
	};

//-----------------------------------------------------------------------------

	// representation of argument data
	struct arg
	{
		bool flag;           // argument is a flag (boolean)
		string defaults;     // default value, as a string
		bool mandatory;      // argument is mandatory
		string name;         // full name (including --, or empty)
		char abbrev;         // single character abbreviation
		string full_abbrev;  // abbreviation (including -, or empty)
		string help;         // help text
		string type;         // type of value, e.g. <path> (excluding <>)
		bool opt;            // value is optional, e.g --key[=<val>]

		template <typename T>
		arg(const T& d, string n, char a, const string& h,
			 const string& t, bool o) :

			flag(is_bool(d)),
			defaults(output(d)),
			mandatory(!flag && !n.empty() && n[0] == '!'),
			name((n = strip(n, '!'), n.empty() ? "" : "--" + n)),
			abbrev(a),
			full_abbrev(a == '\0' ? "" : string("-") + a),
			help(h),
			type(flag ? "" : !t.empty() && isalpha(t[0]) ? "<" + t + ">" : t),
			opt(o && a == '\0')
			{ }

		template <typename T>
		static bool is_bool(const T&) { return false; }
		static bool is_bool(bool)     { return true; }

//-----------------------------------------------------------------------------

		// alternatives: abbreviation plus name
		string alt() const
		{
			string a = full_abbrev;
			if (!full_abbrev.empty() && !name.empty()) a += "  ";
			return a + name;
		}

		// best representation: name or else abbreviation
		string best() const
		{
			return name.empty() ? full_abbrev : name;
		}

		// abbrev-type representation
		string abbrev_type() const { return full_abbrev + " " + type; }

		// name-type representation, or just name for flags
		string name_type() const
		{
			return flag ? name : opt ?
				name + "[=" + type + "]" :
				name + "="  + type;
		}

//-----------------------------------------------------------------------------

		// display help text for argument
		void display() const
		{
			static const unsigned col[] = { 3, 4, 23 },
				cum[] = { col[0], col[0] + col[1], col[0] + col[1] + col[2] };
			string full = name_type();

			cout << (indent=col[0])   << (field=col[1]) [emph[full_abbrev]]
			     << (indent=cum[1]+2) << (field=col[2]) [full];

			if (full.length() > col[2]-2) cout << nl;
			cout << (indent=cum[2]) << help;

			if (!flag && !defaults.empty())
				cout << " [default: " << emph[defaults] << "]";

			cout << ~indent << ~indent << ~indent << nl;
		}

	};

//-----------------------------------------------------------------------------

	// meta argument, e.g. --help, --version
	class meta_arg : public arg
	{
		some cmd;

	public:
		template <typename C>
		meta_arg(C c, const string& n, char a, const string& h) :
			arg(false, n, a, h, "", true), cmd(c) { }

		const some& command() const { return cmd; }
	};

//-----------------------------------------------------------------------------

	// generate index of keys and flags specified in command line
	void index()
	{
		for (size_t n = 1; n < args.length(); n++)
		{
			val& v = args[n];
			if (v == "--") { v.used = true; break; }

			else if (v.length() > 2 && v[0] == '-' && v[1] == '-')
				keys[v.key()] = n;

			else if (v.length() > 1 && v[0] == '-')
				for (size_t k = 1; k < v.length(); k++)
					flags[v[k]] = n;
		}
	}

//-----------------------------------------------------------------------------

	// locate an argument with name or abbreviation in command line
	size_t locate(const arg& a)
	{
		typename map <string, size_t>::const_iterator k;
		typename map <char,   size_t>::const_iterator f;
		size_t p;

		if ((k = keys.find(a.name)) != keys.end() && !args[p = k->second].used)
			return args[p].used = true, p;

		if ((f = flags.find(a.abbrev)) != flags.end())
			return args[p = f->second].used = true, p;

		if (a.mandatory)
			abort("option is mandatory", a.alt());

		return args.length();
	}

//-----------------------------------------------------------------------------

	// if meta-argument is given, execute relevant command
	void locate_meta()
	{
		typedef typename array <meta_arg>::iterator I;
		some cmd;

		for (I i = meta_data.begin(); i != meta_data.end(); i++)
			if (locate(*i) != args.length() && !(cmd = i->command()).empty())
				*this << cmd;
	}

//-----------------------------------------------------------------------------

	// value <- string for general type
	template <typename T>
	static bool input(T& v, const string& s)
	{
		bool ok;
		(_, v, ok) = from++(s);
		return ok;
	}

	// string <- value for general type
	template <typename T>
	static string output(const T& v) { return from(v); }

	// assign input string to variable, check for invalid input
	template <typename T>
	void assign(const arg& a, T& var, const string& value)
	{
		if (!input(var, value)) abort_conv(a);
	}

//-----------------------------------------------------------------------------

	// set value from p-th argument, if present
	template <typename T>
	void set_value(const arg& a, bool& spec, T& var, size_t p)
	{
		val& v = args[p];

		if (a.name == v.key())  // matching name
		{
			spec = true;
			string value = v.value();
			if (value.empty() || v.val_used)
				{ if (!a.opt) abort_arg(a); }
			else v.val_used = true,  assign(a, var, value);
		}

		else if (++p < args.length())  // matching abbreviation
			spec = args[p].used = true,  assign(a, var, args[p]);

		else abort_arg(a);
	}

	// bool (flag) specialization: negate default value of flag
	void set_value(const arg& a, bool& spec, bool& var, size_t p) { var = !var; }

//-----------------------------------------------------------------------------

	// contains data of all arguments to display help
	array <arg> data;

	// contains data of meta arguments only
	array <meta_arg> meta_data;

	// input arguments
	array <val> args;

	// argument secs, used in displaying help
	map <size_t, string> secs;

	// index of keys and flags in command line
	map <string, size_t> keys;
	map <char,   size_t> flags;

	// array of free arguments, i.e. those (unnamed) arguments
	// not used during reading via call to read_args(), excluding argv[0]
	array <string> free_args;

	// internal commands
	struct read_cmd { } read;
	struct disp_cmd { } disp;
	struct help_cmd { } help;
	struct ver_cmd  { } ver;
	struct use_cmd  { } use;

//-----------------------------------------------------------------------------

	// control whether an optional value was specified
	static bool& no_spec() { static bool b; return b; }
	bool has(const bool& spec) const { return &spec != &no_spec(); }

//-----------------------------------------------------------------------------

	// derived class references
	D& der() { return static_cast <D&> (*this); }
	const D& der() const { return static_cast <const D&> (*this); }
	D& const_der() const { return const_cast <D&> (der()); }

//-----------------------------------------------------------------------------

	// read arguments as specified by der()
	void read_args() { der().define(read); }

	// define meta arguments as specified by der()
	void meta_args() { der().define_meta(); }

	// read free arguments
	void read_free()
	{
		args[0].used = true;
		free_args = args[!args[&val::used]];
	}

	// abort unless minimum number of free arguments is given
	void check_free() const
	{
		if (free_args.length() < der().min_free())
			abort(+sstr() << "at least " << der().min_free() <<
				" arguments are required.");
	}

//-----------------------------------------------------------------------------

public:

	// construct by command line arguments of main()
	arguments(int argc, char* argv[]) :
		args(array <char*> (argc, argv))  // TODO: args(argc, argv) ?
	{
		index();
		read_args();
		meta_args();
		locate_meta();
		read_free();
		check_free();
	}

//-----------------------------------------------------------------------------

	// execute deferred command for given meta argument and exit
	template <typename C>
	arguments& operator<<(C c) { der().meta(c); exit(0); }

	// array of free arguments, i.e. those (unnamed) arguments
	// not used during reading via call to read_args(), excluding argv[0]
	const array <string>& free() const { return free_args; }

	// number of free arguments
	size_t length() const { return free_args.length(); }

	// n-th free argument, or empty string if not available
	string free(size_t n) const
	{
		return n < free_args.length() ? free_args[n] : "";
	}

	// same as above, convenient syntax
	string operator[](size_t n) const { return free(n); }

	// executable filename
	const string name() const { return filename(args[0]); }

	// display arguments as specified by der()
	void display() const { const_der().define(disp); }

//-----------------------------------------------------------------------------

	// abort on error
	void abort(const string& msg, const string& arg = "") const
	{
		cerr << nl << name() << ": " << msg;
		if (!arg.empty()) cerr << ": " << emph[arg];
		cerr << nl << "Try `" << name() << " --help' or `" << name() <<
			" --usage' for more information." << par;
		exit(1);
	}

	void abort(const string& msg, const arg& a) const { abort(msg, a.alt()); }

	void abort_conv(const arg& a) const { abort("invalid input for option",    a); }
	void abort_arg (const arg& a) const { abort("option requires an argument", a); }

protected:

//-----------------------------------------------------------------------------

	// add section of arguments, used in displaying help
	void section(const string& s) { secs[data.length()] = s; }

//-----------------------------------------------------------------------------

	// get value of type T for argument with given name or abbreviation;
	// specify argument data to display help
	template <typename T>
	T get(read_cmd c, const T& defaults, const string& name, char abbrev = '\0',
		const string& help = "", const string& type = "", bool& spec = no_spec())
	{
		T value(defaults);
		set(c, value, name, abbrev, help, type, spec);
		return value;
	}

	// specialization for strings
	template <typename C>
	std::basic_string <C>
	get(read_cmd c, const C* defaults, const string& name, char abbrev = '\0',
		const string& help = "", const string& type = "", bool& spec = no_spec())
	{
		std::basic_string <C> value(defaults);
		set(c, value, name, abbrev, help, type, spec);
		return value;
	}

//-----------------------------------------------------------------------------

	// set value of type T for argument with given name or abbreviation;
	// specify argument data to display help
	template <typename T>
	void set(read_cmd c, T& var, const string& name, char abbrev = '\0',
		const string& help = "", const string& type = "", bool& spec = no_spec())
	{
		arg a(var, name, abbrev, help, type, has(spec));
		data.push_back(a);
		size_t p = locate(a);
		if (p != args.length())
			set_value(a, spec, var, p);
	}

//-----------------------------------------------------------------------------

	// display value of type T for argument with given name or abbreviation
	template <typename T>
	void get(disp_cmd, T& var, const string& name, char abbrev = '\0',
		const string& help = "", const string& type = "",
		bool spec = no_spec()) const
		{ }

	template <typename T>
	void set(disp_cmd c, T& var, const string& name, char abbrev = '\0',
		const string& help = "", const string& type = "",
		const bool& spec = no_spec()) const
	{
		arg a(var, name, abbrev, help, type, has(spec));
		display_value(a, var, spec);
	}

//-----------------------------------------------------------------------------
// methods in this block are treated as virtual (always called through der())

	// minimum number of free arguments
	size_t min_free()   const { return 0; }

	// optional title, inputs, info messages
	string title()  const { return name(); }
	string inputs() const { return ""; }
	string info()   const { return ""; }

	// optional usage message
	string usage() const
	{
		return "Usage: " + name() + " [<options>] " + der().inputs();
	}

	// program version, copyright, license
	string version()   const { return ""; }
	string copyright() const { return ""; }
	string license()   const { return ""; }

	// specify meta arguments
	void define_meta()
	{
		section("Other options:");
		set_meta(help, "help",    '?',  "display this help and exit");
		set_meta(use,  "usage",   '\0', "display usage information and exit");
		set_meta(ver,  "version", '\0', "display version information and exit");
	}

// end of "virtual" block
//-----------------------------------------------------------------------------

	// set meta argument
	template <typename C>
	void set_meta(C cmd, const string& name, char abbrev = '\0',
		const string& help = "")
	{
		meta_arg a(cmd, name, abbrev, help);
		data.push_back(a);
		meta_data.push_back(a);
	}

//-----------------------------------------------------------------------------

	// display program version, copyright and license information
	void meta(ver_cmd) const
	{
		cout << wrap << nl <<
			emph << der().title() << " " << der().version() << ~emph << par <<
			der().copyright() << par <<
			der().license() << par <<
		~wrap << par;
	}

//-----------------------------------------------------------------------------

	// display usage information
	void meta(use_cmd) const
	{
		typedef typename array <arg>::const_iterator I;

		string n = name();
		cout << wrap << nl << "Usage: " << n << (indent=n.length()+8);

		string flags;
		for (I i = data.begin(); i != data.end(); i++)
			if (i->flag && !i->full_abbrev.empty()) flags += i->abbrev;
		if (!flags.empty()) cout << " [-" << flags << "]";

		for (I i = data.begin(); i != data.end(); i++)
			if (!i->flag && !i->full_abbrev.empty())
				cout << " [" << i->abbrev_type() << "]";

		for (I i = data.begin(); i != data.end(); i++)
			if (!i->name.empty()) cout << " [" << i->name_type() << "]";

		cout << " " << der().inputs() << ~indent << ~wrap << par;
	}

//-----------------------------------------------------------------------------

	// display help given the complete argument data
	void meta(help_cmd)
	{
		cout << wrap << nl;
		para(der().usage());
		para(der().info());

		if (data.empty()) return;
		if (secs.empty() || secs.find(0) == secs.end())
			secs[0] = "Options:";

		typedef map <size_t, string>::const_iterator I;
		for (I i, k = secs.begin(); (i = k) != secs.end();)
		{
			size_t p = ++k == secs.end() ? data.length() : k->first;
			display_args(data[i->first, _, p - 1], i->second);
		}

		cout << ~wrap << par;
	}

private:

//-----------------------------------------------------------------------------

	// display name (or abbreviation) and value of a given argument,
	// unless name and abbreviation are both empty
	template <typename T>
	void display_value(const arg& a, const T& var, const bool& spec) const
	{
		if (has(spec))
		cout << a.best() << " : " << emph[output(spec)] << nl;
		cout << a.best() << " = " << emph[output(var)]  << nl;
	}

//-----------------------------------------------------------------------------

	// display help for a list of arguments, with optional heading
	template <typename T, typename R>
	void display_args(const array <T, R>& a, const string& head = "") const
	{
		if (a.empty()) return;
		para(head);
 		a[&arg::display]();
		cout << par;
	}

//-----------------------------------------------------------------------------

	// display paragraph with optional heading, unless body is empty
	static void para(const string& body, const string& head = "")
	{
		if (!body.empty()) cout << head << body << par;
	}

};

//-----------------------------------------------------------------------------

}  // namespace argument_details

using argument_details::arguments;
using argument_details::style_def::operator<<;

//---------------------------------------------------------------------------------

} // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_STREAM_ARGS_HPP
