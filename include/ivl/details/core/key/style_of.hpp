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

#ifndef IVL_CORE_DETAILS_KEY_STYLE_OF_HPP
#define IVL_CORE_DETAILS_KEY_STYLE_OF_HPP

//-----------------------------------------------------------------------------

namespace ivl {

//-----------------------------------------------------------------------------

namespace keys {

//-----------------------------------------------------------------------------

namespace details {

//-----------------------------------------------------------------------------

template <
	typename T,
	typename OP = typename some_operators::operator_of <T>::type,
	size_t N = stack_size
>
class style_of : private array <option_of <T, OP, N> >,
	public ref_pair <style_of <T, OP, N> >,
	public gen <style_of <T, OP, N> >
{
	typedef array <option_of <T, OP, N> > A;
	typedef typename A::const_iterator CI;
	typedef typename A::reverse_iterator RI;
	typedef typename A::const_reverse_iterator CRI;
	typedef ref_pair <style_of <T, OP, N> > P;
	typedef gen <style_of <T, OP, N> > G;

	template <typename E, typename EN>
	void read(const node <E, EN>& n) { read(A::rbegin(), n); }

	template <typename E, typename EN>
	void read(RI i, const node <E, EN>& n) { *i = *n; read(++i, ++n); }

	void read(RI i, null) { }

	void read(const off <style_of>& os)
	{
		CI r; RI w;
		for (r = (~os).begin(), w = A::rbegin(); w != A::rend(); ++r, ++w)
			*w = ~*r;
	}

public:

//-----------------------------------------------------------------------------

	typedef CI  const_iterator;
	typedef CRI const_reverse_iterator;

	typedef typename A::elem_type  elem_type;
	typedef typename A::base_class base_class;

	CI  begin()  const { return A::begin(); }
	CI  end()    const { return A::end(); }
	CRI rbegin() const { return A::rbegin(); }
	CRI rend()   const { return A::rend(); }

//-----------------------------------------------------------------------------

	typedef style_of create_new;
	typedef style_of create_similar;
	using P::operator~;
	using G::operator[];

	style_of() : A() { }

	template <typename E, typename EN>
	style_of(const node <E, EN>& n) : A(node <E, EN>::length) { read(n); }

	template <typename E>
	style_of(const E& e) : A(1) { read(node <E>(e)); }

	template <typename E>
	style_of(const E e[]) : A(1) { read(node <const E*>(e)); }

	style_of(const off <style_of>& os) : A((~os).length()) { read(os); }

//-----------------------------------------------------------------------------

	void   clear()        { A::clear(); }
	bool   empty()  const { return A::empty(); }
	size_t length() const { return A::length(); }

	template <typename E>
	style_of& operator<<(const E& e) { A::push_back(e); return *this; }

	template <typename E>
	style_of& operator>>(E& e) { e = A::back(); A::pop_back(); return *this; }

};

//-----------------------------------------------------------------------------

template <typename T, typename OP, size_t N>
class off <style_of <T, OP, N> > :
	public ref_pair <off <style_of <T, OP, N> > >,
	public gen <off <style_of <T, OP, N> > >
{
	typedef ref_pair <off <style_of <T, OP, N> > > B;

public:
	off(const style_of <T, OP, N>& s) : B(s) { }
};

//-----------------------------------------------------------------------------

template <typename S, typename T, typename OP, size_t N>
typename enable_if <is_conv <T, S>, S&>::type
inline operator<<(S& s, const style_of <T, OP, N>& st)
{
	typedef typename style_of <T, OP, N>::const_iterator I;
	for (I i = st.begin(), e = st.end(); i != e; ++i)
		s << *i;
	return s;
}

template <typename S, typename T, typename OP, size_t N>
typename enable_if <is_conv <T, S>, S&>::type
inline operator<<(S& s, const off <style_of <T, OP, N> >& ost)
{
	typedef style_of <T, OP, N> STY;
	typedef typename STY::const_reverse_iterator I;
	const STY& sty = ~ost;
	for (I i = sty.rbegin(), e = sty.rend(); i != e; ++i)
		s << ~*i;
	return s;
}

//-----------------------------------------------------------------------------

}  // namespace details

using details::style_of;

namespace all { using ivl::keys::style_of; }

//-----------------------------------------------------------------------------

}  // namespace keys

using keys::details::operator<<;

//-----------------------------------------------------------------------------

}  // namespace ivl

//-----------------------------------------------------------------------------

#endif  // IVL_CORE_DETAILS_KEY_STYLE_OF_HPP
