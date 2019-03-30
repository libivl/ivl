#include <typeinfo>
#include <ivl/ivl>

using namespace std;
using namespace ivl;

template <class LIM>
void test(const LIM& lim, const string& msg)
{
	cout << msg << endl;
	cout << " b -> " << lim((bool)0)               << endl;
	cout << " c -> " << int(lim((char)0))          << endl;
	cout << "uc -> " << int(lim((unsigned char)0)) << endl;
	cout << " s -> " << lim((short)0)              << endl;
	cout << "us -> " << lim((unsigned short)0)     << endl;
	cout << " w -> " << lim((wchar_t)0)            << endl;
	cout << " i -> " << lim((int)0)                << endl;
	cout << "ui -> " << lim((unsigned int)0)       << endl;
	cout << " l -> " << lim((long)0)               << endl;
	cout << "ul -> " << lim((unsigned long)0)      << endl;
	cout << " x -> " << lim((long long)0)          << endl;
	cout << "ux -> " << lim((unsigned long long)0) << endl;
	cout << " f -> " << lim((float)0)              << endl;
	cout << " d -> " << lim((double)0)             << endl;
	cout << " e -> " << lim((long double)0)        << endl;
	cout << endl;
}

int main()
{
	cout << endl;
	test(fn::inf, "inf:");
	test(fn::nan, "nan:");
	test(fn::lim::min, "min:");
	test(fn::lim::max, "max:");
	test(fn::inf_max, "inf_max:");
	test(fn::inf_min, "inf_min:");
	return 0;
}