#include <ivl/array_2d.hpp>
#include <ivl/system.hpp>
#include <ivl/func.hpp>
//#include <ivl/lina.hpp>
using namespace ivl;



static struct foo : public ivl_func<foo>
{
	inline
	void operate(int& p, sep, const int& n)
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
	template <class A, class B, class C, class D, class E, class F, class G>
	void operate(A& ta, B& tb, C& tc, D& td, E& te, F& tf, G& tg, sep,
				const A& a, const B& b, const C& c, const D& d,
				const E& e, const F& f, const G& g)
	{
		(_, ta, tb, tc, td, te, tf, tg) = (_, ta + 1, tb + ta + 1, tc + 2, ta + tb * tc - td, te * 2, tf + 7, tg + 19);
	}
} bar;


int main()
{
using namespace std;




	cout << "\ntuples operator, test:\n\n";
	cout << "(_, arr(1,2), arr(3,4), 5, 6.7): \n";
	cout << (_, arr(1,2), arr(3,4), 5, 6.7) << "\n";

	int ta;
	double tb;
	float tc;
	complex<double> td;
	float te;
	float tf;
	int tg;
	timer t;
	size_t i;
	size_t limit = 100000000;
	t.tic();
	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		(_, ta) = bar++(ta);
		tb = tb + ta + 1;
	}
	cout << "operation -1: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;
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

	(_, ta, tb, tc, td) = (_, 1, 2, 3, 4);
	for(i = 0; i < limit; i++)
	{
		(_, ta, tb, tc, td) = bar++(ta, tb, tc, td);
	}
	cout << "third operation: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << t.toctic() << endl;


	(_, ta, tb, tc, td, te, tf, tg) = (_, 1, 2, 3, 4, 5, 6, 7);
	for(i = 0; i < limit; i++)
	{
		(_, ta, tb, tc, td, te, tf, tg) = bar++[_, ta, tb, tc, td, te, tf, tg];
	}
	cout << "++operation0: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << te << ": " << tf << ": " << tg << ": " << t.toctic() << endl;

	(_, ta, tb, tc, td, te, tf, tg) = (_, 1, 2, 3, 4, 5, 6, 7);
	for(i = 0; i < limit; i++)
	{
		(_, ta, tb, tc, td, te, tf, tg) = (_, ta + 1, tb + ta + 1, tc + 2, ta + tb * tc - td, te * 2, tf + 7, tg + 19);
	}
	cout << "++operation1: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << te << ": " << tf << ": " << tg << ": " << t.toctic() << endl;

	(_, ta, tb, tc, td, te, tf, tg) = (_, 1, 2, 3, 4, 5, 6, 7);
	for(i = 0; i < limit; i++)
	{
		ta = ta + 1;
		tb = tb + ta + 1;
		tc = tc + 2;
		td = ta + tb * tc - td;
		te = te * 2;
		tf = tf + 7;
		tg = tg + 19;
	}
	cout << "++operation2: " << ta << ", " << tb << ", " << tc << ", " << td << ": " << te << ": " << tf << ": " << tg << ": " << t.toctic() << endl;


	return 0;
}


