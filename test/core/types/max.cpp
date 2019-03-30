#include <typeinfo>
#include <ivl/ivl>

using namespace std;
using namespace ivl;
using namespace ivl::types;
using namespace ivl::types::types_details;

void succ_test()
{
	cout << "successor test:" << endl;
	succ<bool>              ::type b;  cout << " b -> " << typeid(b) .name() << endl;
	succ<char>              ::type c;  cout << " c -> " << typeid(c) .name() << endl;
	succ<unsigned char>     ::type uc; cout << "uc -> " << typeid(uc).name() << endl;
	succ<short>             ::type s;  cout << " s -> " << typeid(s) .name() << endl;
	succ<unsigned short>    ::type us; cout << "us -> " << typeid(us).name() << endl;
	succ<wchar_t>           ::type w;  cout << " w -> " << typeid(w) .name() << endl;
	succ<int>               ::type i;  cout << " i -> " << typeid(i) .name() << endl;
	succ<unsigned int>      ::type ui; cout << "ui -> " << typeid(ui).name() << endl;
	succ<long>              ::type l;  cout << " l -> " << typeid(l) .name() << endl;
	succ<unsigned long>     ::type ul; cout << "ul -> " << typeid(ul).name() << endl;
	succ<long long>         ::type x;  cout << " x -> " << typeid(x) .name() << endl;
	succ<unsigned long long>::type ux; cout << "ux -> " << typeid(ux).name() << endl;
	succ<float>             ::type f;  cout << " f -> " << typeid(f) .name() << endl;
	succ<double>            ::type d;  cout << " d -> " << typeid(d) .name() << endl;
	succ<long double>       ::type e;  cout << " e -> " << typeid(e) .name() << endl;
	cout << endl;
}

void order_test()
{
	cout << "order test:" << endl;
	cout << " b -> " << ord<bool>              ::value << endl;
	cout << " c -> " << ord<char>              ::value << endl;
	cout << "uc -> " << ord<unsigned char>     ::value << endl;
	cout << " s -> " << ord<short>             ::value << endl;
	cout << "us -> " << ord<unsigned short>    ::value << endl;
//	cout << " w -> " << ord<wchar_t>           ::value << endl;
	cout << " i -> " << ord<int>               ::value << endl;
	cout << "ui -> " << ord<unsigned int>      ::value << endl;
	cout << " l -> " << ord<long>              ::value << endl;
	cout << "ul -> " << ord<unsigned long>     ::value << endl;
	cout << " x -> " << ord<long long>         ::value << endl;
	cout << "ux -> " << ord<unsigned long long>::value << endl;
	cout << " f -> " << ord<float>             ::value << endl;
	cout << " d -> " << ord<double>            ::value << endl;
	cout << " e -> " << ord<long double>       ::value << endl;
	cout << endl;
}

template <typename T>
void max_test()
{
	cout << "max test with " << typeid(T).name() << ":" << endl;
	typename types::max<T, bool>              ::type b;  cout << " b -> " << typeid(b) .name() << endl;
	typename types::max<T, char>              ::type c;  cout << " c -> " << typeid(c) .name() << endl;
	typename types::max<T, unsigned char>     ::type uc; cout << "uc -> " << typeid(uc).name() << endl;
	typename types::max<T, short>             ::type s;  cout << " s -> " << typeid(s) .name() << endl;
	typename types::max<T, unsigned short>    ::type us; cout << "us -> " << typeid(us).name() << endl;
//	typename types::max<T, wchar_t>           ::type w;  cout << " w -> " << typeid(w) .name() << endl;
	typename types::max<T, int>               ::type i;  cout << " i -> " << typeid(i) .name() << endl;
	typename types::max<T, unsigned int>      ::type ui; cout << "ui -> " << typeid(ui).name() << endl;
	typename types::max<T, long>              ::type l;  cout << " l -> " << typeid(l) .name() << endl;
	typename types::max<T, unsigned long>     ::type ul; cout << "ul -> " << typeid(ul).name() << endl;
	typename types::max<T, long long>         ::type x;  cout << " x -> " << typeid(x) .name() << endl;
	typename types::max<T, unsigned long long>::type ux; cout << "ux -> " << typeid(ux).name() << endl;
	typename types::max<T, float>             ::type f;  cout << " f -> " << typeid(f) .name() << endl;
	typename types::max<T, double>            ::type d;  cout << " d -> " << typeid(d) .name() << endl;
	typename types::max<T, long double>       ::type e;  cout << " e -> " << typeid(e) .name() << endl;
	cout << endl;
}

int main()
{
	succ_test();
	order_test();
	max_test <int>();
	max_test <complex<int> >();
	max_test <array<int> >();
	max_test <array<complex<int> > >();
	return 0;
}