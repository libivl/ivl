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

#ifndef IVL_CORE_DETAILS_STREAM_TEXT_BUF_HPP
#define IVL_CORE_DETAILS_STREAM_TEXT_BUF_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

// TODO: array <T>::slice_array_type -> slice_array (rename)
// TODO: array <T>::const_slice_array
// TODO: a.begin() + pos -> a.at(pos)

//-----------------------------------------------------------------------------

namespace text_buf_details {

using namespace types::constants;
using namespace keys::all;

using types::enable_if;
using keys::mod;
using keys::off;
using key_grp::color;

//-----------------------------------------------------------------------------

// TODO: fix return type, make ivl_func
template <typename T1, typename T2, typename T3>
T2 bound(const T1& x, const T2& low, const T3& high)
{
	return ivl::min(ivl::max(x, low), high);
}

//-----------------------------------------------------------------------------

inline const char* ansi_seq(key::normal)          { return "\x1b[22m"; };
inline const char* ansi_seq(key::bright)          { return "\x1b[1m"; };
inline const char* ansi_seq(key::underline)       { return "\x1b[4m"; };
inline const char* ansi_seq(no <key::underline>)  { return "\x1b[24m"; };
inline const char* ansi_seq(key::reset)           { return "\x1b[0m"; };

inline const char* ansi_seq(key::black)           { return "\x1b[30m"; };
inline const char* ansi_seq(key::red)             { return "\x1b[31m"; };
inline const char* ansi_seq(key::green)           { return "\x1b[32m"; };
inline const char* ansi_seq(key::yellow)          { return "\x1b[33m"; };
inline const char* ansi_seq(key::blue)            { return "\x1b[34m"; };
inline const char* ansi_seq(key::magenta)         { return "\x1b[35m"; };
inline const char* ansi_seq(key::cyan)            { return "\x1b[36m"; };
inline const char* ansi_seq(key::white)           { return "\x1b[37m"; };

//-----------------------------------------------------------------------------

template <typename T>
class circular_buffer : private array <T>
{
	typedef array <T> B;
	size_t off;

public:
	circular_buffer(size_t s = 0)         : B(s),    off(0) { }
	circular_buffer(size_t s, const T& v) : B(s, v), off(0) { }

	void init(size_t s = 0)         { B::init(s);    off = 0; }
	void init(size_t s, const T& v) { B::init(s, v); off = 0; }

	size_t offset(size_t p) const { return (p + off) % B::length(); }

	T&       operator[](size_t p)       { return B::operator[](offset(p)); }
	const T& operator[](size_t p) const { return B::operator[](offset(p)); }

	circular_buffer& operator+=(size_t p) { off = offset(p); return *this; }
};

//-----------------------------------------------------------------------------

template <typename S>
struct stream_buf
{
	typedef std::basic_streambuf <
		typename S::char_type,
		typename S::traits_type
	> type;
};

//-----------------------------------------------------------------------------

template <typename S>
class text_buf : public stream_buf <S>::type
{
	typedef typename stream_buf <S>::type SB;
	typedef typename SB::char_type C;
	typedef typename SB::traits_type T;
	typedef typename SB::int_type INT;
	typedef std::ostreambuf_iterator <C> I;

	using SB::pbase;
	using SB::pptr;
	using SB::pbump;
	using SB::setp;

	typedef option_of <text_buf> cmd;
	typedef style_of  <text_buf> cmd_seq;
	typedef const C* (*translator)(C);

	struct no_wrap : public keys::key <no_wrap>
		{ using keys::key <no_wrap>::operator=; };

//-----------------------------------------------------------------------------

	template <typename D>
	class inf_stack : private style_of <text_buf>
	{
		typedef style_of <text_buf> B;

	public:
		using B::length;

		template <typename E>
		inf_stack& operator<<(const E& e) { B::operator<<(e); return *this; }

		template <typename E>
		inf_stack& operator>>(E& e)
		{
			if (B::empty()) e = to_constant <D>()();
			else B::operator>>(e);
			return *this;
		}
	};

//-----------------------------------------------------------------------------

	S&  stream;     // underlying stream
	SB* streambuf;  // underlying stream buffer

	size_t width;      // line width, buffer width
	array <C> buffer;  // text buffer

	// command buffer
	circular_buffer <cmd_seq> cmd_buffer;

	// wrapping settings
	typedef c_int <80> default_wrap;
	bool wrapping;

	// indent settings
	typedef c_int <3> default_tab;
	size_t tab_width;
	size_t ind_space;

	// pending indent at beginning of line
	bool ind_pending;

	// number of consecutive newlines sent to underlying stream buffer
	size_t lines_out;

	// graphic commands enabled
	bool ansi_on;

	// verbatim mode
	bool verbatim;

	// character translator
	translator tran;

//-----------------------------------------------------------------------------

	// history stack defaults
	typedef c_key_val <key::wrap,   int,        default_wrap>          wrap_default;
	typedef c_key_val <key::indent, int,        c_zero>                ind_default;
	typedef c_key_val <key::tab,    int,        default_tab>           tab_default;
	typedef c_key_val <key::field,  int,        c_zero>                field_default;
	typedef c_key_val <key::filter, translator, c_null <translator> >  tran_default;

	// history stacks
	inf_stack <wrap_default>          wrap_stack;
	inf_stack <ind_default>           ind_stack;
	inf_stack <tab_default>           tab_stack;
	inf_stack <field_default>         field_stack;
	inf_stack <key::normal>           bright_stack;
	inf_stack <no <key::underline> >  ul_stack;
	inf_stack <key::white>            color_stack;
	inf_stack <key::ansi>             ansi_stack;
	inf_stack <tran_default>          tran_stack;

//-----------------------------------------------------------------------------

	size_t offset (C* ptr)     const { return ptr - &buffer[0]; }
	C*     pointer(size_t off)       { return &buffer[0] + off; }

	size_t base_off() const { return offset(pbase()); }
	size_t ptr_off()  const { return offset(pptr()); }

	void set_off(size_t base)             { set_off(base, width - 1); }
	void set_off(size_t base, size_t end) { setp(pointer(base), pointer(end)); }

//-----------------------------------------------------------------------------

	void indent() { apply(!underline); do_ind(); cancel(!underline); }

	void do_ind()       { I out(streambuf); do_ind(out); }
	void do_ind(I& out) { std::fill_n(out, ind_space, ' '); }

	void release_ind() { if (ind_pending) { indent(); ind_pending = false; } }

	void new_line()       { I out(streambuf); new_line(out); }
	void new_line(I& out) { out = '\n'; lines_out++; ind_pending = true; }

	// number of consecutive newlines up to the previous n positions,
	// either in own buffer or sent to underlying stream buffer
	size_t lines_up_to(size_t n) { return lines_up_to(n, ptr_off()); }
	size_t lines_up_to(size_t n, size_t p)
	{
		if (n == 0) return 0;
		size_t k = lines_up_to(n - 1, p);
		return k < n - 1 ? k :
			(p >= n ? buffer[p - n] == '\n' : lines_out + p >= n) ? n : k;
	}

//-----------------------------------------------------------------------------

	void bypass(const C* s, I& out) { while (*s) out = *s++; }

	void translate(C c, I& out)
	{
		const C* s;
		if (tran && (s = (*tran)(c))) bypass(s, out);
		else out = c;
	}

//-----------------------------------------------------------------------------

	void put_cmd(size_t p, I& out)
	{
		cmd_seq& cs = cmd_buffer[p];
		if (!cs.empty()) { *this << cs; cs.clear(); }
	}

	void put_char(size_t p, I& out)
	{
		put_cmd(p, out);
		release_ind();
		C c = buffer[p];
		if (c == '\n') new_line(out);
		else { translate(c, out); lines_out = 0; }
	}

	void put_seq(size_t end, I& out)
	{
		for (size_t p = 0; p < end; p++)
			put_char(p, out);
	}

//-----------------------------------------------------------------------------

	void put_through(const C* s)         { I out(streambuf); put_through(s, out); }
	void put_through(const C* s, I& out) { while (*s) translate(*s++, out); }

	void buffer_char(C c)           { *pptr() = c; pbump(1); }

	void stream_char(C c)           { stream.put(c); }
	void stream_seq(const C* s)     { while (*s) stream_char(*s++); }
	void stream_fill(C c, size_t n) { for (size_t k = 0; k < n; k++) stream_char(c); }
	void stream_nl(size_t n = 1)    { stream_fill('\n', n - lines_up_to(n)); sync(); }
	void vspace(size_t n)           { stream_nl(n + 1); }

	INT eof_bullshit(bool error) { return error ? T::eof() : T::not_eof(0); }

//-----------------------------------------------------------------------------

	// shift buffer content to the left so that position 'base' comes to 0
	void shift_line(size_t base)
	{
		size_t ptr = ptr_off();
		if (base > ptr - 1)
			{ set_off(0); return; }
		size_t len = ptr - base;  // len >= 1
		buffer[0, _, len - 1] = buffer[base, _, ptr - 1];
		cmd_buffer += base;
		set_off(len);
	}

	// output line up to buffer position 'end', followed by an 'end_line';
	// shift content to the left
	bool put_line(size_t end, bool full = false)
	{
		I out(streambuf);
		put_seq(end, out);
		if (end < width) put_cmd(end, out);
		if (wrapping) new_line(out);
		if (wrapping && !full) end++;
		shift_line(end);
		return out.failed();
	}

//-----------------------------------------------------------------------------

	// flush one line, separated at the rightmost white space, or at the
	// rightmost endline if syncing
	bool flush_line(bool sync = false)
	{
		size_t p, ptr = ptr_off();
		size_t space = width - ind_space;
		if (ptr < (sync ? 1 : space)) return false;
		if (ptr > space) ptr = space;

		// TODO: remove
		size_t z = 0;

		// scan from current position back to beginning for a newline, ...
		if ( (p = last(buffer[z, _, ptr - 1] == '\n')) != -1 )
			return put_line(p);

		// sync only up to newlines unless line is full ...
		if (sync && ptr != space) return false;

		// ... or scan from end of line back to beginning for a space
		// if no newline is found (now ptr == width)
		if ( (p = last(is_space(buffer[z, _, space - 1]))) != -1 )
			return put_line(p);

		// otherwise, flush entire line
		return put_line(space, true);
	}

	// plain pass-through, when wrapping is disabled
	bool flush_through()
	{
		I out(streambuf);
		put_seq(ptr_off(), out);
		set_off(0);
		return out.failed();
	}

	bool flush(bool sync = false)
	{
		return wrapping ? flush_line(sync) : flush_through();
	}

protected:

//-----------------------------------------------------------------------------

	virtual INT overflow(INT c)
	{
		if (c != T::eof()) buffer_char(c);
		return eof_bullshit(flush());
	}

 	virtual int sync() { return flush(true) ? -1 : streambuf->pubsync(); }

public:

//-----------------------------------------------------------------------------

	text_buf(S& s) :
		stream(s), streambuf(s.rdbuf()), wrapping (false),
		tab_width(default_tab()), ind_space(0), ind_pending(false),
		lines_out(0), ansi_on(true), verbatim(false), tran(0)
	{
		stream.flush();
		stream.std::ios::rdbuf(this);
		set_width();
	}

	~text_buf() {
		flush_through();
		stream.std::ios::rdbuf(streambuf);
	}

private:

//-----------------------------------------------------------------------------

	void set_width(size_t w = default_wrap())
	{
		w = bound(w, ind_space + 1, 65536);
		buffer.init(width = w);
		cmd_buffer.init(width);
		set_off(0);
	}

	void wrap_on()
	{
		flush_through();
		if (!lines_out) new_line();
		wrapping = true;
	}

public:

//-----------------------------------------------------------------------------

	bool has_property(key::verb) { return verbatim; }

	template <typename CMD>
	text_buf& operator<<(const CMD& c) { apply(c); return *this; }

//-----------------------------------------------------------------------------

	template <typename CMD>
	void command(const CMD& c) { defer(c); }

	template <typename CMD>
	void defer(const CMD& c)
	{
		size_t p = ptr_off();
		if (p < width) cmd_buffer[p] << c;
	}

//-----------------------------------------------------------------------------

	void command(key::verb)       { verbatim = true; }
	void command(off <key::verb>) { verbatim = false; }

//-----------------------------------------------------------------------------

	void command(key::nl)       { stream_nl(); }
	void command(off <key::nl>) { stream_nl(); }

	void command(key::par)       { vspace(1); }
	void command(off <key::par>) { vspace(1); }

	template <typename V>
	void command(const key_val <key::vspace, V>& s) { vspace(*s); }

	template <typename V>
	void command(const off <key_val <key::vspace, V> >& s) { vspace(*~s); }

//-----------------------------------------------------------------------------

	void command(key::wrap)             { commit_wrap(); }
	void command(no <key::wrap>)        { commit_no_wrap(); }
	void command(off <key::wrap>)       { revert(wrap_stack); }
	void command(off <no <key::wrap> >) { revert(wrap_stack); }

	template <typename V>
	void command(const key_val <key::wrap, V>& w) { commit_wrap(w); }

	template <typename V>
	void command(const off <key_val <key::wrap, V> >&) { revert(wrap_stack); }

//-----------------------------------------------------------------------------

	void command(const off <key::field>) { revert(field_stack); stream << std::right; }  // TODO: fix alignment

	template <typename V>
	void command(const key_val <key::field, V>& f) { commit_field(f); }

	template <typename V>
	void command(const off <key_val <key::field, V> >&) { revert(field_stack); stream << std::right; }  // TODO: fix alignment

private:

//-----------------------------------------------------------------------------

	void commit_wrap()
	{
		wrap_stack << (ivl::wrap=width);
		if (!wrapping) wrap_on();
	}

	void commit_no_wrap()
	{
		wrap_stack << (!ivl::wrap);
		defer(no_wrap()=wrap_stack.length());
	}

	bool wrap_valid(const size_t l) { return l == wrap_stack.length(); }

	template <typename V>
	void commit_wrap(const key_val <key::wrap, V>& w)
	{
		wrap_stack << w;
		if (!wrapping) wrap_on();
		if (*w != width) set_width(*w);
	}

//-----------------------------------------------------------------------------

	template <typename CMD>
	void apply(const off <CMD>& c) { cancel(~c); }

	void apply(const off <key::puff>& c) { }

//-----------------------------------------------------------------------------

	template <typename T>
	void apply (const key_val <key::filter, T>& t) { tran_stack << t; tran = *t; }

	template <typename T>
	void cancel(const key_val <key::filter, T>&) { revert(tran_stack); }

//-----------------------------------------------------------------------------

	void apply (key::wrap)      { commit_wrap(); }
	void apply (no <key::wrap>) { commit_no_wrap(); }

	void cancel(key::wrap)      { }  // dummy (to compile only)
	void cancel(no <key::wrap>) { }  // dummy (to compile only)

	void apply (const key_val <no_wrap, size_t>& l) { if (wrap_valid(*l)) wrapping = false; }
	void cancel(const key_val <no_wrap, size_t>&)   { }  // dummy (to compile only)

	template <typename V>
	void apply(const key_val <key::wrap, V>& w) { commit_wrap(w); }

	template <typename V>
	void cancel(const key_val <key::wrap, V>&) { }  // dummy (to compile only)

//-----------------------------------------------------------------------------

	void apply(const key::indent& c)       { commit_ind(c); }
	void apply(const no <key::indent>& c)  { commit_ind(c); }
	void apply(const inc <key::indent>& c) { commit_ind(c); }
	void apply(const dec <key::indent>& c) { commit_ind(c); }

	void apply_ind(key::indent)       { if (!ind_space) ind_space = tab_width; }
	void apply_ind(no <key::indent>)  { ind_space = 0; }
	void apply_ind(inc <key::indent>) { ind_space = bound_space(ind_space + tab_width); }
	void apply_ind(dec <key::indent>) { ind_space = ind_space < tab_width ? 0 : ind_space - tab_width; }

	void cancel(key::indent)       { revert(ind_stack); }
	void cancel(no <key::indent>)  { revert(ind_stack); }
	void cancel(inc <key::indent>) { revert(ind_stack); }
	void cancel(dec <key::indent>) { revert(ind_stack); }

	template <typename V>
	void apply(const key_val <key::indent, V>& c) { commit_ind(c); }

	template <typename V>
	void apply_ind(const key_val <key::indent, V>& s) { ind_space = bound_space(*s); }

	template <typename V>
	void cancel(const key_val <key::indent, V>&) { revert(ind_stack); }

	template <typename V>
	void apply(const key_val <key::tab, V>& c) { commit_tab(c); }

	template <typename V>
	void apply_ind(const key_val <key::tab, V>& w) { tab_width = bound_tab(*w); }

	template <typename V>
	void cancel(const key_val <key::tab, V>&) { revert(tab_stack); }

//-----------------------------------------------------------------------------

	template <typename CMD>
	void commit_ind(const CMD& c)
	{
		apply_ind(c);
		ind_stack << (ivl::indent=ind_space);
	}

	template <typename CMD>
	void commit_tab(const CMD& c)
	{
		apply_ind(c);
		tab_stack << (ivl::tab=tab_width);
	}

//-----------------------------------------------------------------------------

	template <typename T>
	size_t bound_space(const T& s) { return bound(s, 0, width - 1); }

	template <typename T>
	size_t bound_tab(const T& w) { return bound(w, 1, width - ind_space - 1); }

//-----------------------------------------------------------------------------

	template <typename V>
	void apply(const key_val <key::field, V>&) { }  // dummy (to compile only)

	template <typename V>
	void cancel(const key_val <key::field, V>&) { }  // dummy (to compile only)

	template <typename V>
	void commit_field(const key_val <key::field, V>& f)
	{
		std::streamsize w = max(*f, 0);
		stream << std::setw(w) << std::left;  // TODO: fix alignment
		field_stack << (field=w);
	}

//-----------------------------------------------------------------------------

	void apply(key::reset) { graphic <key::reset>(); }

	void apply(const key::ansi& c)      { ansi_on = true;  ansi_stack << c; }
	void apply(const no <key::ansi>& c) { ansi_on = false; ansi_stack << c; }

	void cancel(key::ansi)      { revert(ansi_stack); }
	void cancel(no <key::ansi>) { revert(ansi_stack); }

	void apply(const key::normal& c)         { commit_graphic(c, bright_stack); }
	void apply(const key::bright& c)         { commit_graphic(c, bright_stack); }
	void apply(const key::underline& c)      { commit_graphic(c, ul_stack); }
	void apply(const no <key::underline>& c) { commit_graphic(c, ul_stack); }

	void cancel(key::normal)         { revert(bright_stack); }
	void cancel(key::bright)         { revert(bright_stack); }
	void cancel(key::underline)      { revert(ul_stack); }
	void cancel(no <key::underline>) { revert(ul_stack); }

	template <typename C>
	void apply(const color <C>& c) { commit_graphic(*c, color_stack); }

	template <typename C>
	void cancel(color <C>) { revert(color_stack); }

//-----------------------------------------------------------------------------

	template <typename CODE>
	void graphic() { if (ansi_on) put_through(ansi_seq(CODE())); }

	template <typename CODE, typename D>
	void commit_graphic(const CODE& c, inf_stack <D>& s) { graphic <CODE>(); s << c; }

//-----------------------------------------------------------------------------

	template <typename D>
	void revert(inf_stack <D>& s) { cmd c; s >> c >> c; *this << c; }

};

//-----------------------------------------------------------------------------

template <typename S>
text_buf <S>* try_text_buf(S& s)
{
	return dynamic_cast <text_buf <S>*>(s.std::ios::rdbuf());
}

template <typename S>
void delete_text_buf(S& s)
{
	text_buf <S>* tb = try_text_buf(s);
	if (tb) delete tb;
}

template <typename S>
text_buf <S>* get_text_buf(S& s)
{
	text_buf <S>* tb = try_text_buf(s);
	return tb ? tb : new text_buf <S>(s);
}

template <typename S, typename P>
bool text_buf_prop(S& s, P p)
{
	text_buf <S>* tb = try_text_buf(s);
	return tb ? tb->has_property(p) : false;
}

//-----------------------------------------------------------------------------

template <typename S>
S& cmd(S& s, const key::puff)
{
	return delete_text_buf(item_data(s)),  s;
}

template <typename S, typename CMD>
S& cmd(S& s, const option <CMD>& c)
{
	return get_text_buf(item_data(s))->command(*c),  s;
}

template <typename S, typename P>
bool has_property(S& s, P p) { return text_buf_prop(item_data(s), p); }

template <typename S>
bool is_verbatim(S& s) { return has_property(s, verb); }

//-----------------------------------------------------------------------------

template <typename S> inline S& operator<<(S& s, key::puff c)   { return cmd(s, c); }

template <typename S, typename T> inline S& operator<<(S& s, const mod <key::verb,      T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::filter,    T>& c) { return cmd(s, *c); }

template <typename S, typename T> inline S& operator<<(S& s, const mod <key::nl,        T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::par,       T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::vspace,    T>& c) { return cmd(s, *c); }

template <typename S, typename T> inline S& operator<<(S& s, const mod <key::wrap,      T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::indent,    T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::tab,       T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::field,     T>& c) { return cmd(s, *c); }

template <typename S, typename T> inline S& operator<<(S& s, const mod <key::ansi,      T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::reset,     T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::normal,    T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::bright,    T>& c) { return cmd(s, *c); }
template <typename S, typename T> inline S& operator<<(S& s, const mod <key::underline, T>& c) { return cmd(s, *c); }

template <typename S, typename C>
inline S& operator<<(S& s, color <C> c) { return cmd(s, *c); }

template <typename S, typename C, typename T>
typename enable_if <is_of_group <C, color>, S&>::type
inline operator<<(S& s, off <mod <C, T> > c) { return cmd(s, *c); }

//-----------------------------------------------------------------------------

}  // namespace text_buf_details

//-----------------------------------------------------------------------------

using text_buf_details::is_verbatim;
using text_buf_details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_STREAM_TEXT_BUF_HPP
