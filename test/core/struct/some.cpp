#include <ivl/ivl>
#include <algorithm>

using namespace std;
using namespace ivl;
void main2(array<some>);
//-----------------------------------------------------------------------------

template <typename T>
struct type_is
{
	template <typename S>
	bool operator()(const S& s) const { return s.S::template is <T>(); }
};

//-----------------------------------------------------------------------------

struct text : public string
{
	typedef string base_class;
	text(const char* c) : string(c) { }
};

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{
	{
		using ivl::find;
		typedef array <int> A;
		typedef const char* const_char_ptr;
		array <some> a(8);

		a[0] = true;
		a[1] = 'A';
		a[2] = 6;
		a[3] = 3.14;
		a[4] = "hello,";
		a[5] = A(arr[_, 6, 5, 4, 3, 2, 1, 0]);
		a[6] = 2.71;
		a[7] = text("world!");

		cout << "* some <- T; some._<T>() :" << endl << endl;
		cout << "[0] bool        : " << a[0]._<bool>()            << endl;
		cout << "[1] char        : " << a[1]._<char>()            << endl;
		cout << "[2] int         : " << a[2]._<int>()             << endl;
		cout << "[3] double      : " << a[3]._<double>()          << endl;
		cout << "[4] const char* : " << a[4]._<const char*>()     << endl;
		cout << "[5] array       : " << a[5]._<array <int> >()    << endl;
		cout << "[6] double      : " << a[6]._<double>()          << endl;
		cout << "[7] string      : " << a[7]._<string>()          << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		cout << "there are "
			<< count_if(a.begin(), a.end(), type_is <double>())
			<< " double elements in array a" << endl;
		cout << "there are " << sum(a[&some::is <double>]())
			<< " double elements in array a, at positions "
			<< find(a[&some::is <double>]()) << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		some s0 = a[0];
		some s1 = a[1];
		some s2 = a[2];
		some s3 = a[3];
		some s4(a[4]);
		some s5(a[5]);
		some s6(a[6]);
		some s7(a[7]);
		a.init();

		cout << "* some <- some, or some(some); some._<T>() :" << endl << endl;
		cout << "[0] bool        : " << s0._<bool>()            << endl;
		cout << "[1] char        : " << s1._<char>()            << endl;
		cout << "[2] int         : " << s2._<int>()             << endl;
		cout << "[3] double      : " << s3._<double>()          << endl;
		cout << "[4] const char* : " << s4._<const char*>()     << endl;
		cout << "[5] array       : " << s5._<array <int> >()    << endl;
		cout << "[6] double      : " << s6._<double>()          << endl;
		cout << "[7] string      : " << s7._<string>()          << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		cout << "* some[T()] :" << endl << endl;
		cout << "[0] bool        : " << s0[bool()]           << endl;
		cout << "[1] char        : " << s1[char()]           << endl;
		cout << "[2] int         : " << s2[int()]            << endl;
		cout << "[3] double      : " << s3[double()]         << endl;
		cout << "[4] const char* : " << s4[const_char_ptr()] << endl;  // TODO: __<T> ?
		cout << "[5] array       : " << s5[array <int>()]    << endl;
		cout << "[6] double      : " << s6[double()]         << endl;
		cout << "[7] string      : " << s7[string()]         << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		bool           t0(s0);
		char           t1(s1);
		int            t2(s2);
		double         t3(s3);
		const char*    t4 = s4;
		array <int>    t5 = s5;
		double         t6 = s6;
		string         t7 = s7;

		cout << "* T(some), or T <- some :" << endl << endl;
		cout << "[0] bool        : " << t0 << endl;
		cout << "[1] char        : " << t1 << endl;
		cout << "[2] int         : " << t2 << endl;
		cout << "[3] double      : " << t3 << endl;
		cout << "[4] const char* : " << t4 << endl;
		cout << "[5] array       : " << t5 << endl;
		cout << "[6] double      : " << t6 << endl;
		cout << "[7] string      : " << t7 << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		array <int>& r5(s5);  r5[2] = -2;
		string&      r7 = s7; r7 += " ...";

		s5._<array <int> >()[4] = -2;
		s7._<string>()[0] = 'W';

		cout << "* T&(some), or T& <- some :" << endl << endl;
		cout << "[5] array       : " << s5[array <int>()]    << endl;
		cout << "[7] string      : " << s7[string()]         << endl;
		cout << endl;

//-----------------------------------------------------------------------------

		cout << "* type check :" << endl << endl;
		cout << "[0] is long / bool        : " << s0.is <long>() << " / " << s0.is <bool>()            << endl;
		cout << "[1] is long / char        : " << s1.is <long>() << " / " << s1.is <char>()            << endl;
		cout << "[2] is long / int         : " << s2.is <long>() << " / " << s2.is <int>()             << endl;
		cout << "[3] is long / double      : " << s3.is <long>() << " / " << s3.is <double>()          << endl;
		cout << "[4] is long / const char* : " << s4.is <long>() << " / " << s4.is <const char*>()     << endl;
		cout << "[5] is long / array       : " << s5.is <long>() << " / " << s5.is <array <int> >()    << endl;
		cout << "[5] is long / array_nd    : " << s5.is <long>() << " / " << s5.is <array_nd <int> >() << endl;
		cout << "[6] is long / double      : " << s6.is <long>() << " / " << s6.is <double>()          << endl;
		cout << "[7] is long / string      : " << s7.is <long>() << " / " << s7.is <string>()          << endl;
		cout << endl;

//-----------------------------------------------------------------------------

#ifdef SOME2
		a.init(8);
		a[0] = true;
		a[1] = 'A';
		a[2] = 6;
		a[3] = 3.14;
		a[4] = "hello,";
		a[5] = arr[_, 6, 5, 4, 3, 2, 1, 0];
		a[6] = 2.71;
		a[7] = text("world!");
		main2(a);
#endif

	}

}
