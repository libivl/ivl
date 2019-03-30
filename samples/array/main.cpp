
extern void array_main();
extern void array_nd_main();
extern void array_2d_main();
extern void other_array_main();
//extern void set_main();

#include <ivl/array_2d.hpp>
#include <ivl/system.hpp>
#include <ivl/func.hpp>
#include <ivl/lina.hpp>
using namespace ivl;

template<class T, class S> void test(const array<T, S>& o)
{
	o.size();
}

template <class T1, class T2>
ret<int, int> myf(T1 t1, T2 t2)
{
	using namespace std;
	cout << "tuple test" << endl;
	cout << t1.v1  << endl;
	cout << t1.v2  << endl;
	cout << t2.v1  << endl;
	cout << "join_tuple test" << endl;
	join_tuple<T1, T2> tt(t1, t2);
	cout << tt.val(types::number<1>())  << endl;
	cout << tt.val(types::number<2>())  << endl;
	cout << tt.val(types::number<3>())  << endl;
	int a, b;
	(_, a, b) = (_, 1, 3);
	cout << "_(a, b) = _(1, 3);" << endl;
	cout << "a : " << a << endl;
	cout << "b : " << b << endl;
	cout << "_[2] ->* 3 : " << _[2] ->* 3 << endl;
	return (_, a, b);
}

static struct foo : public ivl_func<foo>
{
	void operate(int& p, sep, int n)
	{
		p = n + 1;
	}
	template <class X, class Y>
	void operate(X& p, sep, const Y& n)
	{
		p = n + 1;
	}
	template <class A, class B, class C, class D>
	void operate(A& ta, B& tb, C& tc, D& td, sep,
				const A& a, const B& b, const C& c, const D& d)
	{
		(_, ta, tb, tc, td) = (_, a + 1, b + a + 1, c + 2, a + b * c - d);
	}
} bar;


	struct ts
	{
		template<class C, class D>
		void foo(const array_nd<C, D>& n)
		{
			std::cout << n <<std::endl;
		}
	} tst;

int main()
{
using namespace std;

	cout << "ivl_func test\n";

	int p,n;
	n=10;//@@@@@@@@@@@@@@@@
	(_, p) = bar++(n);
	cout << "should be 20: " << p << endl;

	cout << "press enter";
	string k;
	//cin.get();


	size_array sz(idx(4,3,2));
	array_nd<int> d(idx(3,3), 1);
	array_nd<int> e = d;

	array_2d<bool> b;
	const array<bool>& db=b;
	array<bool> nb(db);




	cout << "e: " << endl << e << "d: " << endl << d << endl
		<< "e.isequal(d): " << e.isequal(d) << endl;

	cout << "e: " << endl << e << "d: " << endl << d << endl;



	std::cout <<"htmm.."<<d.size()<<std::endl;
	(d+1);
	(d+1).size();
	std::cout <<"hm end"<<std::endl;

	std::cout <<"htmmXd.."<<std::endl;
	test((d+1));
	test((d));
	std::cout <<"hmMMMMMMMMM end"<<std::endl;

	static_cast<array_nd<int>::base_class&>(e)
	= (d+1);
	std::cout <<"XXXXXXXXXXXX"<<std::endl;


	e = d + 1;


	double xt;
	array_2d<double> T;
	array<double>::const_iterator fir;
	array_2d<double>::const_iterator xir;

	array<double> test(xt*T);

	//array<array< size_t > > xz(1); TODO: inspect this in visual studio: creates some subarray error in a degenerate empty case.
	//wrap(xz);


	array_main();
	// set_main(); TODO: enable
	array_nd_main();
	array_2d_main();
	other_array_main();


	double a_s[] =
	{      1,           4,           7,          10,           2,           5,
           8,          11,           3,           6,           9,          12,
          10,          40,          70,         100,          20,          50,
          80,         110,          30,          60,          90,         120,
         100,         400,         700,        1000,         200,         500,
         800,        1100,         300,         600,         900,        1200};

	array_nd<double> a_f(idx(4, 3, 3), a_s);

	//array_nd r

	cout << a_f(idxn(size_range(1,2), size_range(2,7))) << endl;

	cout << "abc" << endl;

	 size_array aaa = idx(5,4,2,0,3,1);
	 array<bool> bbb(6,false);

	  bbb[ aaa[size_range(0,2)]  ] = true;        //(A)
	cout << bbb << endl;
	bbb.init(6, false);
	  //msvc failz: bbb[ (size_array)aaa[size_range(0,2)]  ] = true;     //(B)
	cout << bbb << endl;


	using namespace ivl::internal;
	int aa, ab;
	(_, aa, ab) = myf(tpl(1, aaa), tpl(bbb));
	cout << "_(a, b) = myf(..)" << endl;
	cout << "a : " << aa << endl;
	cout << "b : " << ab << endl;

	array_nd<float> gg; // TODO: array_2d cout???
	//when the letter is g no cout????
	array_2d<int> g;
	gg.resize(2,2);
	g.resize(2,2);
	cout << "gg="<<gg << endl;
	cout << g;
	cout << "g=" << g << endl;
	lvalue(a_f(idxn(size_range(1,2), size_range(1,2))).ref(), gg) =
		meshgrid++(arr(1,2),arr(3,4));
	cout << a_f << " and " << gg << endl;
	cout << " and " << gg << endl;

#if 0
	cout << "\ntuples operator, test:\n\n";
	cout << "(_, arr(1,2), arr(3,4), 5, 6.7): \n";
	cout << (_, arr(1,2), arr(3,4), 5, 6.7) << "\n";

	int ta;
	double tb;
	float tc;
	complex<double> td;
	timer t;
	size_t i;
	size_t limit = 10000000;
	t.tic();
	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		(_, ta) = bar++(ta);
		(_, tb) = bar++(tb + ta);
	}
	cout << "operation -3: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;
	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		ta = ta + 1;
		(_, tb) = bar++(tb + ta);
	}
	cout << "operation -2: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;
	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		ta = ta + 1;
		tb = tb + ta + 1;
	}
	cout << "operation -1: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;

	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		ta = ta + 1;
		tb = tb + ta + 1;
		tc = tc + 2;
		td = ta + tb * tc - td;
	}
	cout << "operation zero: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;
	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		(_, ta, tb, tc, td) = (_, ta + 1, tb + ta + 1, tc + 2, ta + tb * tc - td);
	}
	cout << "first operation: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;
	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		(_, ta, tb, tc, td) = (_, ta + 1, tb + ta + 1, tc + 2, ta + tb * tc - td);
	}
	cout << "second operation: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;
	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		(_, ta, tb, tc, td) = bar++(ta, tb, tc, td);
	}
	cout << "third operation: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;
#endif




//	tst.foo((a_f |& a_f));
// TODO: This is the concat sample: enable it.	tst.foo((a_f |+ a_f) -+ ((a_f |+ a_f)- 100)) ;

	//cout << (a_f |& a_f).size() << endl;

	/*
	array_nd<double> foo = (a_f |& a_f);
	cout << "what" << endl;
	cout << foo << endl;
	cout << foo.length() << endl;
*/
	return 0;
}


