/* This file is part of the ivl C++ library <http://image.ntua.gr/ivl>.
   A C++ template library extending syntax towards mathematical notation.

   Copyright (C) 2012 Yannis Avrithis <iavr@image.ntua.gr>
   Copyright (C) 2012 Kimon Kontosis <kimonas@image.ntua.gr>

   ivl is free software; you can redistribute it and/or modify
   it under the nulls of the GNU Lesser General Public License
   version 3 as published by the Free Software Foundation.

   Alternatively, you can redistribute it and/or modify it under the nulls
   of the GNU General Public License version 2 as published by the Free
   Software Foundation.

   ivl is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   and a copy of the GNU Lesser General Public License along
   with ivl. If not, see <http://www.gnu.org/licenses/>. */

#ifndef IVL_CORE_DETAILS_TYPES_STREAMY_HPP
#define IVL_CORE_DETAILS_TYPES_STREAMY_HPP

namespace ivl {

//-----------------------------------------------------------------------------

namespace types {


//-----------------------------------------------------------------------------
/*
template <typename S>
S& operator<<(S& s, t_true) { return s << "true"; }

template <typename S>
S& operator<<(S& s, t_false) { return s << "false"; }

template <typename S, int N>
S& operator<<(S& s, number <N>) { return s << N; }
*/
//-----------------------------------------------------------------------------

namespace details {

template<class T1>
struct node_chain { };

} // namespace details

template <class S, class T1, class T2>
S& operator<<(S& s, node<T1, T2>) { return s << "(" << T1() << details::node_chain<T2>() << ")"; }

template <class S>
S& operator<<(S& s, node<null, null>) { return s << "()"; }

template <class S, class T1, class T2>
S& operator<<(S& s, details::node_chain<node<T1, T2> >) { return s << " " << T1() << details::node_chain<T2>(); }

template <class S>
S& operator<<(S& s, details::node_chain<node<null, null> >) { return s; }

template <class S>
S& operator<<(S& s, nat) { return s << "nat"; }

template <class S>
S& operator<<(S& s, null) { return s << "null"; }

template <class S, class L>
S& operator<<(S& s, lists::listie<L> l) { 
	typedef typename lists::listie<L>::type tp;
	typedef typename lists::model<tp>::type tm;
	typedef typename lists::disp<tm>::type tt;
	return s << tt(); 
}

template <class S, class T>
S& operator<<(S& s, scheme::label<T>) 
{
	return s << //"ALIAS:" << 
		scheme::label<T>::text; 
}

template <class S, class T>
S& operator<<(S& s, scheme::keyword<T>) 
{
	return s << //"ALIAS:" << 
		scheme::label<T>::text; 
}

template <class S, class T, int N>
S& operator<<(S& s, lists::var<T, N>) 
{
	return s << //"ALIAS:" <<
		scheme::label<T>::text << "[" << N << "]"; 
}

template <class S, class T>
S& operator<<(S& s, scheme::quote<T>) 
{
	return s << 
		"quote \"" << scheme::label<T>::text << "\""; 
}

template <class S, class T>
S& operator<<(S& s, scheme::srquote<T>) 
{
	return s << 
		"sr-quote \"" << scheme::label<T>::text << "\""; 
}



/*
template <class S, class T, class E>
S& operator<<(S& s, alias<T, E>) { return s << "ALIAS:" << label<T>::text; }
*/

//-----------------------------------------------------------------------------
template <typename S, class K>
S& operator<<(S& s, node<lambda, K>)
{
	using ivl::operator <<;
	return s << "(" << lambda() << " " << 
		typename K::val() 
			<< " (" << indent++ << std::endl 
			<< typename K::next::val() 
			<< indent-- << std::endl << "))";
}

//template <class S, template<typename> class T>
//S& operator<<(S& s, tls<T>) { return s << scheme::label<tls<T> >::text; }

template <class S, template<typename, typename, typename> class T>
S& operator<<(S& s, t3<T>) { return s << scheme::label<t3<T> >::text; }

template <class S, template<typename, typename> class T>
S& operator<<(S& s, t2<T>) { return s << scheme::label<t2<T> >::text; }

template <class S, template<typename> class T>
S& operator<<(S& s, t1<T>) { return s << scheme::label<t1<T> >::text; }

template <class S, class T>
S& operator<<(S& s, lists::disp_word<T>) { return s << "WORD="<<scheme::label<T>::text; }

template <class S, class N>
S& operator<<(S& s, lists::listie_disp<N>) 
{ return s << typename lists::disp<N>::type(); }

template <class S, class N>
S& operator<<(S& s, lists::listie_script<N>) 
{ 
	return s << typename N::disp() << " = " << 
		//typename lists::disp<typename N::type>::type(); 
		typename N::type();
}

//-----------------------------------------------------------------------------


/*
template <typename S, class K>
S& operator<<(S& s, node<define, K>)
{
	s << "(" << types::define() << " ";
	s << typename K::val() << " ";
	s << typename K::next::val();
	s << ")";
	return s;
}
*/

//-----------------------------------------------------------------------------



#if 0
template <class T> 
struct label  { };

//-----------------------------------------------------------------------------

template <typename S>
S& operator<<(S& s, t_true) { return s << "true"; }

template <typename S>
S& operator<<(S& s, t_false) { return s << "false"; }

template <typename S, int N>
S& operator<<(S& s, number <N>) { return s << N; }

//-----------------------------------------------------------------------------

namespace macro {


template <typename S> S& operator<<(S& s, a) { return s << "a"; }
template <typename S> S& operator<<(S& s, b) { return s << "b"; }
template <typename S> S& operator<<(S& s, c) { return s << "c"; }
template <typename S> S& operator<<(S& s, d) { return s << "d"; }
template <typename S> S& operator<<(S& s, e) { return s << "e"; }
template <typename S> S& operator<<(S& s, f) { return s << "f"; }
template <typename S> S& operator<<(S& s, g) { return s << "g"; }
template <typename S> S& operator<<(S& s, h) { return s << "h"; }
template <typename S> S& operator<<(S& s, i) { return s << "i"; }
template <typename S> S& operator<<(S& s, j) { return s << "j"; }
template <typename S> S& operator<<(S& s, k) { return s << "k"; }
template <typename S> S& operator<<(S& s, l) { return s << "l"; }
template <typename S> S& operator<<(S& s, m) { return s << "m"; }
template <typename S> S& operator<<(S& s, n) { return s << "n"; }
template <typename S> S& operator<<(S& s, o) { return s << "o"; }
template <typename S> S& operator<<(S& s, p) { return s << "p"; }
template <typename S> S& operator<<(S& s, q) { return s << "q"; }
template <typename S> S& operator<<(S& s, r) { return s << "r"; }
template <typename S> S& operator<<(S& x, s) { return x << "s"; }
template <typename S> S& operator<<(S& s, t) { return s << "t"; }
template <typename S> S& operator<<(S& s, u) { return s << "u"; }
template <typename S> S& operator<<(S& s, v) { return s << "v"; }
template <typename S> S& operator<<(S& s, w) { return s << "w"; }
template <typename S> S& operator<<(S& s, x) { return s << "x"; }
template <typename S> S& operator<<(S& s, y) { return s << "y"; }
template <typename S> S& operator<<(S& s, z) { return s << "z"; }

template <typename S> S& operator<<(S& s, la) { return s << "la"; }

/*
template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }
template <typename S> S& operator<<(S& s, a_member) { return s << "a_member"; }
template <typename S> S& operator<<(S& s, a_rember) { return s << "a_rember"; }
template <typename S> S& operator<<(S& s, a_insert_l) { return s << "a_insert_l"; }
*/


//template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }
//template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }
//template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }
//template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }
//template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }
//template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }
//template <typename S> S& operator<<(S& s, a_lat) { return s << "a_lat"; }

} // namespace macro

using macro::operator <<;

//-----------------------------------------------------------------------------

namespace lists {

using ivl::operator<<;

template <typename S>
S& operator<<(S& s, nat) { return s << "not defined"; }

//template <typename S>
//S& operator<<(S& s, null) { return s; }

template <typename S, int K>
S& operator<<(S& s, arg <K>) { return s << "_" << K << "_"; }


//-----------------------------------------------------------------------------


template <typename S>
S& operator<<(S& s, car) { return s << bright << "car" << dark; }

template <typename S>
S& operator<<(S& s, cdr) { return s << bright << "cdr" << dark; }

template <typename S>
S& operator<<(S& s, cons) { return s << bright << "cons" << dark; }

template <typename S>
S& operator<<(S& s, types::null) { return s << bright << "null?" << dark; }

template <typename S>
S& operator<<(S& s, atom) { return s << bright << "atom?" << dark; }

template <typename S>
S& operator<<(S& s, eq) { return s << bright << "eq?" << dark; }

template <typename S>
S& operator<<(S& s, cond) { return s << bright << "cond" << dark; }

template <typename S>
S& operator<<(S& s, _else) { return s << bright << "else" << dark; }

template <typename S>
S& operator<<(S& s, lambda) { return s << bright << "lambda" << dark; }

template <typename S>
S& operator<<(S& s, define) { return s << bright << "define" << dark; }


//-----------------------------------------------------------------------------

template <typename S>
S& operator<<(S& s, subs) { return s << bright << "subs" << dark; }

template <typename S>
S& operator<<(S& s, find) { return s << bright << "find" << dark; }

template <typename S>
S& operator<<(S& s, concat) { return s << bright << "concat" << dark; }

template <typename S>
S& operator<<(S& s, dot) { return s << bright << "dot" << dark; }

template <typename S>
S& operator<<(S& s, types::size) { return s << bright << "size" << dark; }

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------

//dbginfo:
template <typename S, class T>
S& operator<<(S& s, naty<T>) { return s<<"naty<"<<typename T::node_type()<<">"; }


//-----------------------------------------------------------------------------


template<class S, class T>
inline S& print_node_elem(S& s, const T&) { return s << T(); }

/***dbginfo ***/

template<class S>
inline S& print_node(S& s, ivl::types::null) { return s << "null"; }

/****/

template<class S, class T1, class T2>
inline S& print_node(S& s, node<T1, T2> n) 
{ 
	return print_node(print_node_elem(s, T1()) << 
		r_if<typename t_eq<T2, node<null, null> >::type>("", " "), T2()); 
}

template<class S>
inline S& print_node(S& s, node<null, null> n) { return s << ")"; }

template<class S>
inline S& print_node(S& s, nat) { return s << nat(); }


using lists::operator <<;
	
template <typename S, typename T1, typename T2>
S& operator<<(S& s, node <T1, T2> n) { return print_node(s << "(", n); }

template <class S, class N>
//S& operator<<(S& s, listy<N>) { return s << typename listy_eval<N>::type(); }
S& operator<<(S& s, lists::listie<N>) 
{ 
	using lists::operator <<;
	s << "E="<<typename lists::listie<N>::list() << std::endl; 
	return s << "LST="<<typename lists::listie<N>::type(); 
}
/*
template <class S, class N>
S& operator<<(S& s, listy_script<listy<N> >) 
	{ return s << typename listy<N>::lisp() << " = " << listy<N>(); }
*/
//-----------------------------------------------------------------------------

template <typename S, class K>
S& operator<<(S& s, node<lambda, K>)
{
	return s << "(" << types::lambda() << " " << 
		typename K::val() 
			<< " (" << indent++ << std::endl 
			<< typename K::next::val() 
			<< indent-- << std::endl << "))";
}

template <typename S, class K>
S& operator<<(S& s, node<define, K>)
{
	s << "(" << types::define() << " ";
	s << label<typename K::val>::text << " ";
	s << typename K::next::val();
	s << ")";
	return s;
}


//-----------------------------------------------------------------------------


namespace hidden {

template <typename T>
struct nl { };

template <typename S, typename T>
S& operator<<(S& s, nl <T>) { 
	using ivl::types::lists::operator <<;
	//print_node(s, T());
	return s << " " << T(); 
}

template <class S, typename T1, typename T2>
S& operator<<(S& s, nl <node <T1, T2> >)
{
	return s << std::endl << nl <T1> () << nl <T2> ();
}
/*
template <class S, typename T>
S& operator<<(S& s, nl <listy <T> >)
{
	return s << std::endl << listy <T> ();
}
*/

} // namespace hidden


template <typename S, class K>
S& operator<<(S& s, node<types::cond, K>)
{
	return s << types::cond() << indent++ << 
		//K() 
		hidden::nl<K>()
		<< indent--;
}

//-----------------------------------------------------------------------------


//using list_details::operator<<;


}  // namespace list_details

#endif

}  // namespace types

//-----------------------------------------------------------------------------

}  // namespace ivl

#endif  // IVL_CORE_DETAILS_TYPES_STREAMY_HPP
