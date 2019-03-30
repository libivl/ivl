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

#ifndef IVL_CORE_DETAILS_ELEM_HPP
#define IVL_CORE_DETAILS_ELEM_HPP

namespace ivl {

namespace core_details {

struct elem_details
{
	template<class J, class X>
	struct check
	{
		typedef typename types::t_and<types::is_ivl_array<J>,
			types::is_base_eq<typename types::bare_type<X>::type,J> >::type is_ch;
		typedef typename types::t_if<is_ch,
			scalar<J>, J>::type type;
		typedef typename types::t_if<is_ch,
			data::ices_wrap_array_attr, data::ice_wrap_array_attr>::type attr;
	};

	template<class X, class A, class IS_ARRAY>
	struct check_2_0
	{
		typedef A type;
	};
	template<class X, class A>
	struct check_2_0<X, A, types::t_true>
	{
		typedef typename types::change_data_class_set<
				data::wrap_array<A,
					typename check<typename types::get_value<A>::type, X>::attr>
				,
				typename types::change_elem_type<
					typename check<typename types::get_value<A>::type, X>::type
					,
					typename A::create_new
				>::type
			>::type
		type;
	};

	template<class A ,class X>
	struct check_2
	{
		/*
		typedef typename types::t_if<types::is_ivl_array<A>,
			array<typename check<typename types::get_value<A>::type, X>::type,
				data::wrap_array<A,
				typename check<typename types::get_value<A>::type, X>::attr> >,
			A
		>::type type_1;
		*/
		typedef typename check_2_0<X, A, typename types::is_ivl_array<A>::type>::type type_1;

		typedef typename types::t_if<types::t_and_3<types::is_ivl_array<A>,
			types::t_not<typename check<typename types::get_value<A>::type, X>::is_ch>,
			typename check<A, X>::is_ch>,
				scalar<A>,
			type_1>::type type;
		// mysterious warning of twice scalar

		//typedef type_1 type;
	};
};

} /* namespace core_details */

template <class RT, class X1, RT F(X1), int COST=0 >
struct unary_elem
{
	typedef typename types::bare_type<RT>::type T;
	typedef core_details::elem_details et;

	template <class J, class J1>
	struct functor
	{
		typedef types::number<COST> cost;
		static inline RT elem_op(X1 x)
		{
			return F(x);
		}
	};
	template <class A1>
	typename unary_elem_func_result<T, functor,
		typename et::check_2<A1, X1>::type>
		::type operator()(const A1& a1)
	{
		return unary_elem_func_result<T, functor,
			typename et::check_2<A1, X1>::type
		>::from(a1);
	}

	// tuple
	template <class TPL>
	typename unary_elem_func_result<T, functor, typename TPL::t1>
		::type operator[](const tuple_base<1, TPL>& tpl)
	{
		return unary_elem_func_result<T, functor, typename TPL::t1>
			::from(tpl.derived().v1);
	}
	/*
	// suppose array of tuples
	template <class J, class S>
	typename unary_elem_func_result<J, functor,
		member_array<array<J, S>, typename J::t1> >
		::type operator[](const array<J, S>& a)
	{
		return unary_elem_func_result<J, functor,
			member_array<array<J, S>, typename J::t1> >
			::from(a.in(&J::v1));
	}
	*/
	// suppose array of tuples
	template <class A>
	typename unary_elem_func_result<
			typename types::get_value<A>::type, functor,
		member_array<A, typename types::get_value<A>::type::t1> >
		::type operator[](const A& a)
	{
		typedef typename types::get_value<A>::type J;
		return unary_elem_func_result<J, functor,
			member_array<A, typename J::t1> >
			::from(a.in(&J::v1));
	}

};

template <class RT, class X1, class X2, RT F(X1, X2), int COST=0 >
struct binary_elem
{
	typedef typename types::bare_type<RT>::type T;
	typedef core_details::elem_details et;

	template <class J, class J1, class J2>
	struct functor
	{
		typedef types::number<COST> cost;
		static inline RT elem_op(X1 x1, X2 x2)
		{
			return F(x1, x2);
		}
	};
	/*
	template <class A1, class A2>
	typename binary_elem_func_result<T, functor, A1, A2>
		::type operator()(const A1& a1, const A2& a2)
	{
		return binary_elem_func_result<T, functor, A1, A2>
			::from(a1, a2);
	}
	*/

	// tuple
	template <class TPL>
	typename binary_elem_func_result<T, functor,
		typename TPL::t1, typename TPL::t2>
		::type operator[](const tuple_base<2, TPL>& tpl)
	{
		return binary_elem_func_result<T, functor,
			typename TPL::t1, typename TPL::t2>
			::from(tpl.derived().v1, tpl.derived().v2);
	}
	// suppose array of tuples

	//TODO: do something more correct like a combination
	// of ice2 and an elem function doing a
	// replacer_cast<X1, scalar<X1>
	// this will reach inner_type of an array as well.

	template <class J, class S>
	typename binary_elem_func_result<T, functor,

		array<typename et::check<typename J::t1, X1>::type,
		data::wrap_array<
		member_array<const array<J, S>, typename J::t1>,
		typename et::check<typename J::t1, X1>::attr> >,

		array<typename et::check<typename J::t2, X2>::type,
		data::wrap_array<
		member_array<const array<J, S>, typename J::t2>,
		typename et::check<typename J::t2, X2>::attr> >

		>

		::type operator[](const array<J, S>& a)
	{

		return binary_elem_func_result<T, functor,

			array<typename et::check<typename J::t1, X1>::type,
			data::wrap_array<
			member_array<const array<J, S>, typename J::t1>,
			typename et::check<typename J::t1, X1>::attr> >,

			array<typename et::check<typename J::t2, X2>::type,
			data::wrap_array<
			member_array<const array<J, S>, typename J::t2>,
			typename et::check<typename J::t2, X2>::attr> >

			>::from(
			member_array<const array<J, S>, typename J::t1>(a.in(&J::v1)),
			member_array<const array<J, S>, typename J::t2>(a.in(&J::v2)));
	}

	template <class A1, class A2>
	typename binary_elem_func_result<T, functor,
		typename et::check_2<A1, X1>::type,
		typename et::check_2<A2, X2>::type
	>
		::type operator()(const A1& a1, const A2& a2)
	{
		return
			binary_elem_func_result<T, functor,
			typename et::check_2<A1, X1>::type,
			typename et::check_2<A2, X2>::type
		>
			::from(a1, a2);
	}

};


// same but with given functor
template <class RT, class X1, class X2, template<typename, typename, typename> class F >
struct binary_elem_base
{
	typedef typename types::bare_type<RT>::type T;
	typedef core_details::elem_details et;



	// tuple
	template <class TPL>
	typename binary_elem_func_result<T, F,
		typename TPL::t1, typename TPL::t2>
		::type operator[](const tuple_base<2, TPL>& tpl)
	{
		return binary_elem_func_result<T, F,
			typename TPL::t1, typename TPL::t2>
			::from(tpl.derived().v1, tpl.derived().v2);
	}
	// suppose array of tuples

	//TODO: do something more correct like a combination
	// of ice2 and an elem function doing a
	// replacer_cast<X1, scalar<X1>
	// this will reach inner_type of an array as well.

	template <class J, class S>
	typename binary_elem_func_result<T, F,

		array<typename et::check<typename J::t1, X1>::type,
		data::wrap_array<
		member_array<const array<J, S>, typename J::t1>,
		typename et::check<typename J::t1, X1>::attr> >,

		array<typename et::check<typename J::t2, X2>::type,
		data::wrap_array<
		member_array<const array<J, S>, typename J::t2>,
		typename et::check<typename J::t2, X2>::attr> >

		>

		::type operator[](const array<J, S>& a)
	{

		return binary_elem_func_result<T, F,

			array<typename et::check<typename J::t1, X1>::type,
			data::wrap_array<
			member_array<const array<J, S>, typename J::t1>,
			typename et::check<typename J::t1, X1>::attr> >,

			array<typename et::check<typename J::t2, X2>::type,
			data::wrap_array<
			member_array<const array<J, S>, typename J::t2>,
			typename et::check<typename J::t2, X2>::attr> >

			>::from(
			member_array<const array<J, S>, typename J::t1>(a.in(&J::v1)),
			member_array<const array<J, S>, typename J::t2>(a.in(&J::v2)));
	}

	template <class A1, class A2>
	typename binary_elem_func_result<T, F,
		typename et::check_2<A1, X1>::type,
		typename et::check_2<A2, X2>::type
	>
		::type operator()(const A1& a1, const A2& a2)
	{
		return
			binary_elem_func_result<T, F,
			typename et::check_2<A1, X1>::type,
			typename et::check_2<A2, X2>::type
		>
			::from(a1, a2);
	}

};

/*
template <class T, class X1, T F(X1), class A1 >
typename unary_elem_func_result<T,
		unary_elem<T, X1, F>::template functor,
		typename core_details::elem_details::check_2<A1, X1>::type
	>
		::type
		elem_run(T (*f)(X1), const A1& a1)
{
		return
			unary_elem_func_result<T,
			unary_elem<T, X1, F>::template functor,
			typename core_details::elem_details::check_2<A1, X1>::type
		>
			::from(a1);
}

//template<class T, class X1, class X2>
//struct binary_elem_f
template <class T, class X1, class X2, class F0, class A1, class A2 >
struct elem_func_res


template <class T, class X1, class X2, T F(X1, X2), class A1, class A2 >
typename binary_elem_func_result<T,
		binary_elem<T, X1, X2, F>::template functor,
		typename core_details::elem_details::check_2<A1, X1>::type,
		typename core_details::elem_details::check_2<A2, X2>::type
	>
		::type
		elem_run((*F), const A1& a1, const A2& a2)
{
		return
			binary_elem_func_result<T,
			binary_elem<T, X1, X2, f>::template functor,
			typename core_details::elem_details::check_2<A1, X1>::type,
			typename core_details::elem_details::check_2<A2, X2>::type
		>
			::from(a1, a2);
}
*/

// --------------------------------------------------

template<class A, class TP>
struct memberfunc_constructor
{
};


template<class C, class RT, int COST = 0>
struct void_memberfunc
{
	typedef typename types::bare_type<RT>::type R;

	template <class J, class J1>
	struct functor
	{
		typedef types::number<COST> cost;
		static inline RT elem_op(const tuple<C*, RT (C::*)()>& x1)
		{
			return (x1.v1->*x1.v2());
		}
	};

};


template<class A, class RT, class C>
struct memberfunc_constructor<A, tuple<C, RT> >
{
	typedef typename types::bare_type<RT>::type R;

	A* a;
	RT (C::*m)();
	template<class T>
	memberfunc_constructor(const T& t)
	{
		a = &t.v1;
		m = t.v2;
	}
};

template<class C, class R, class X1, int COST = 0>
struct unary_memberfunc
{



};

namespace memberfunc_details {

template<class T>
struct pointerize
{
	typedef T type;
	static inline T amp(T x) { return x; }
};
template<class T>
struct pointerize<T&>
{
	typedef T* type;
	static inline T* amp(T& x) { return &x; }
};
template<class T>
struct pointerize<T*&>
{
	typedef T* type;
	static inline T* amp(T* x) { return x; }
};

template<class T>
typename types::remove_const<T&>::type vary(T& t)
{ return const_cast<typename types::remove_const<T&>::type>(t); }

} // memberfunc_details

template<class A, class RT, class C, class X1>
struct memberfunc_constructor<A, tuple<C, RT, X1> >
{
	struct nac { };
	typedef typename types::t_if<types::t_eq<RT, void>, nac, RT>::type R0;
	typedef typename types::t_if<types::t_eq<RT, void>, nac, int>::type ncall_arg;
	typedef typename types::bare_type<R0>::type R;
	typedef typename types::remove_const<C>::type Z;
	typedef memberfunc_details::pointerize<typename
		types::t_descalarize_ref<typename types::elem_ref_inner<A>::type>::type> pointerizer;
	//typedef memberfunc_details::pointerize<typename
	//	types::elem_ref<A>::type> pointerizer;
	typedef typename pointerizer::type Zp;

	typedef RT (Z::*mm)(X1);
	typedef RT (Z::*mmc)(X1) const;

	typedef typename types::t_if<types::is_const<C>,
		mmc, mm>::type ptr_type;
	// todo: const C
	typedef core_details::elem_details et;

	A* a;
	ptr_type m;
	template<class T>
	memberfunc_constructor(const T& t)
	{
		a = &t.v1;
		m = t.v2;
	}
	template <class J, class J1, class J2>
	struct extender
	{
		typedef types::number<10> cost;
		static inline tuple<Zp, copyscalar<ptr_type> > elem_op(const Z& x1, const copyscalar<ptr_type>& x2)
		{
			return tuple<Zp, copyscalar<ptr_type> >(
				const_cast<Zp>(pointerizer::amp(memberfunc_details::vary(x1))), // unacceptable!!!!!!!! TODO: fix ASAP @@@
				x2);
		}
		// alternative for pointer-arrays
		static inline tuple<Zp, copyscalar<ptr_type> > elem_op(const Z* x1, const copyscalar<ptr_type>& x2)
		{
			return tuple<Zp, copyscalar<ptr_type> >(
				const_cast<Zp>(x1), // unacceptable!!!!!!!! TODO: fix ASAP @@@,
				x2);
		}
	};
	template <class J, class J1, class J2>
	struct functor
	{
		typedef types::number<10> cost;
		template<typename L>
		static inline R0 elem_op_imp(Z& cr, ptr_type m, X1 x2, L)
		{
			return (cr.*m)(x2);
		}
		// void specialization
		static inline R0 elem_op_imp(Z& cr, ptr_type m, X1 x2, nac)
		{
			(cr.*m)(x2);
			return nac();
		}

		static inline R0 elem_op(const tuple<Z*, copyscalar<ptr_type> >& x1, X1 x2)
		{
			Z& cr = *x1.v1;
			ptr_type m = x1.v2.t;

			return elem_op_imp(cr, m, x2, ncall_arg() );
		}
    };

    template<class J, class T, class K>
	static inline T ncall(T x, K) { return x; }
	template<class J, class T>
	static inline T ncall(T x, nac) { ++(J(x)); return x; }


	template <class A1>
	typename binary_elem_func_result<R, functor,
		typename types::t_if<types::is_ivl_array<A>,
			array<tuple<Z*, copyscalar<ptr_type> >, wrap_array<
				typename
				binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
				::type,
				data::ice_wrap_array_attr
			> >,
			scalar<tuple<Z*, copyscalar<ptr_type> > >
		>::type,
		typename et::check_2<A1, X1>::type
		>
		::type operator()(const A1& a1) const
	{
		return
		ncall<typename binary_elem_func_result<R, functor,
				typename types::t_if<types::is_ivl_array<A>,
					array<tuple<Z*, copyscalar<ptr_type> >, wrap_array<
						typename
						binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
						::type,
						data::ice_wrap_array_attr
					> >,
					scalar<tuple<Z*, copyscalar<ptr_type> > >
				>::type,
				typename et::check_2<A1, X1>::type
					>::type>
			(binary_elem_func_result<R, functor,
				typename types::t_if<types::is_ivl_array<A>,
					array<tuple<Z*, copyscalar<ptr_type> >, wrap_array<
						typename
						binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
						::type,
						data::ice_wrap_array_attr
					> >,
					scalar<tuple<Z*, copyscalar<ptr_type> > >
				>::type,
				typename et::check_2<A1, X1>::type
				>
				::from(
					binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
					::from(*a, copyscalar<ptr_type>(m)),
                    a1), ncall_arg());


		/*
		typedef array<tuple<Z&, copyscalar<ptr_type> >, wrap_array<
				typename
				binary_elem_func_result<tuple<Z&, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
				::type,
				data::ice_wrap_array_attr
			> > warp;

		typedef binary_elem_func_result<tuple<Z&, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
				bint;

		return
			binary_elem_func_result<R, functor,
			warp,
			typename et::check_2<A1, X1>::type
			>
			::from(
				bint::from(*a, copyscalar<ptr_type>(m))
			, a1);
		*/
	}

};

// Note: June 2013
// however if above needs fix, this needs fix too.


template<class A, class RT, class C>
struct memberfunc_constructor<A, tuple<C, RT, types::term> >
{
    struct nac { };
    typedef typename types::t_if<types::t_eq<RT, void>, nac, RT>::type R0;
    typedef typename types::t_if<types::t_eq<RT, void>, nac, int>::type ncall_arg;
    typedef typename types::bare_type<R0>::type R;
    typedef typename types::remove_const<C>::type Z;
    typedef RT (Z::*mm)();
    typedef RT (Z::*mmc)() const;

    typedef typename types::t_if<types::is_const<C>,
        mmc, mm>::type ptr_type;
    // todo: const C
    typedef core_details::elem_details et;

    A* a;
    ptr_type m;
    template<class T>
    memberfunc_constructor(const T& t)
    {
        a = &t.v1;
        m = t.v2;
    }
    template <class J, class J1, class J2>
    struct extender
    {
        typedef types::number<10> cost;
        static inline tuple<Z*, copyscalar<ptr_type> > elem_op(const Z& x1, const copyscalar<ptr_type>& x2)
        {
            return tuple<Z*, copyscalar<ptr_type> >(
                &const_cast<Z&>(x1), // unacceptable!!!!!!!! TODO: fix ASAP @@@
                x2);
        }
        // alternative for pointer-arrays
        static inline tuple<Z*, copyscalar<ptr_type> > elem_op(const Z* x1, const copyscalar<ptr_type>& x2)
        {
            return tuple<Z*, copyscalar<ptr_type> >(
                const_cast<Z*>(x1), // unacceptable!!!!!!!! TODO: fix ASAP @@@,
                x2);
        }
    };
    template <class J, class J1>
    struct functor
    {
        typedef types::number<10> cost;
        template<typename L>
        static inline R0 elem_op_imp(Z& cr, ptr_type m, L)
        {
            return (cr.*m)();
        }
        // void specialization
        static inline R0 elem_op_imp(Z& cr, ptr_type m, nac)
        {
            (cr.*m)();
            return nac();
        }

        static inline R0 elem_op(const tuple<Z*, copyscalar<ptr_type> >& x1)
        {
            Z& cr = *x1.v1;
            ptr_type m = x1.v2.t;

            return elem_op_imp(cr, m, ncall_arg() );
        }
    };

    template<class J, class T, class K>
    static inline T ncall(T x, K) { return x; }
    template<class J, class T>
    static inline T ncall(T x, nac) { ++(J(x)); return x; }


    typename unary_elem_func_result<R, functor,
        typename types::t_if<types::is_ivl_array<A>,
            array<tuple<Z*, copyscalar<ptr_type> >, wrap_array<
                typename
                binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
                ::type,
                data::ice_wrap_array_attr
            > >,
            scalar<tuple<Z*, copyscalar<ptr_type> > >
        >::type
        >
        ::type operator()() const
    {
        return
        ncall<typename unary_elem_func_result<R, functor,
                typename types::t_if<types::is_ivl_array<A>,
                    array<tuple<Z*, copyscalar<ptr_type> >, wrap_array<
                        typename
                        binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
                        ::type,
                        data::ice_wrap_array_attr
                    > >,
                    scalar<tuple<Z*, copyscalar<ptr_type> > >
                >::type
                    >::type>
            (unary_elem_func_result<R, functor,
                typename types::t_if<types::is_ivl_array<A>,
                    array<tuple<Z*, copyscalar<ptr_type> >, wrap_array<
                        typename
                        binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
                        ::type,
                        data::ice_wrap_array_attr
                    > >,
                    scalar<tuple<Z*, copyscalar<ptr_type> > >
                >::type
                >
                ::from(
                    binary_elem_func_result<tuple<Z*, copyscalar<ptr_type> >, extender, A, copyscalar<ptr_type> >
                    ::from(*a, copyscalar<ptr_type>(m))), ncall_arg());


    }

};


} /*namespace ivl*/

#endif // IVL_CORE_DETAILS_ELEM_HPP
