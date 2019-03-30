#include <ivl/ivl>

using namespace std;
using namespace ivl;
using types::number;
namespace overload = types::overload;

//-----------------------------------------------------------------------------

template <typename T>
struct A { };

struct B { };

template <typename T>
struct C : public A <T> { };

struct D : public B { };
struct E { };
struct F { };
struct S { };

//-----------------------------------------------------------------------------

template <typename T>
S& f(number <9>, S& s, const A <T>&) { cout << "a" << endl; return s; }

S& f(number <3>, S& s, const B&) { cout << "b" << endl; return s; }
S& f(            S& s, const E&) { cout << "e" << endl; return s; }

//-----------------------------------------------------------------------------

overload::fail f(...) { return overload::fail(); }

template <int N>
overload::fail f(number <N>, ...) { return overload::fail(); }

//-----------------------------------------------------------------------------

struct f_fun
{
	template <int N, typename T1, typename T2>
	struct size { enum { value = sizeof(f(number <N>(), +T1(), +T2())) }; };

	template <typename T1, typename T2>
	struct size <0, T1, T2> { enum { value = sizeof(f(+T1(), +T2())) }; };

	template <typename R, typename T1, typename T2, int N>
	static R call(number <N> n, T1 a1, T2 a2) { return f(n, a1, a2); }

	template <typename R, typename T1, typename T2>
	static R call(number <0>, T1 a1, T2 a2) { return f(a1, a2); }
};

//-----------------------------------------------------------------------------

template <typename S, typename T>
S& test(S& s, const T& v, const char* m)
{
	cout << m << ": ";
	return overload::call <f_fun, S&, S&, const T&>(s, v);
}

//-----------------------------------------------------------------------------

int main()
{
	S s;
	test(s, A <int>(), "A");
	test(s, B(), "B");
	test(s, C <int>(), "C");
	test(s, D(), "D");
	test(s, E(), "E");
// 	test(s, F(), "F");
}
