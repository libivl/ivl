#include <ivl/ivl>
#include <algorithm>

using namespace std;
using namespace ivl;

//-----------------------------------------------------------------------------

int main(int argc, char *argv[])
{

	{
		typedef array <int> A;
		typedef some_of <ostream> some;
		array <some> a(8);

		a[0] = true;
		a[1] = 'A';
		a[2] = 6;
		a[3] = 3.14;
		a[4] = "hello,";
		a[5] = A(arr[_, 6, 5, 4, 3, 2, 1, 0]);
		a[6] = 2.71;
		a[7] = string("world!");

		cout << "* some <- T; some._<T>() :" << endl << endl;
		cout << "[0] bool        : " << a[0]._<bool>()         << endl;
		cout << "[1] char        : " << a[1]._<char>()         << endl;
		cout << "[2] int         : " << a[2]._<int>()          << endl;
		cout << "[3] double      : " << a[3]._<double>()       << endl;
		cout << "[4] const char* : " << a[4]._<const char*>()  << endl;
		cout << "[5] array       : " << a[5]._<array <int> >() << endl;
		cout << "[6] double      : " << a[6]._<double>()       << endl;
		cout << "[7] string      : " << a[7]._<string>()       << endl;
		cout << endl;

		cout << "* array of some : " << endl << endl << a << endl;
		cout << endl;
	}

}
