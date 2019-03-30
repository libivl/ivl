#include <ivl/ivl>

using namespace std;
using namespace ivl;

int main()
{
	array<int> a = arr(0,5,6,-1,0,0);
	array<int> b = arr(1,1,1,1,1,1);

	cout << "a = " << a << endl;
	cout << "all(a) = " << all(a) << endl;

	cout << "b = " << b << endl;
	cout << "all(b) = " << all(b) << endl;

	cout << "a[_] = " << a[_] << endl;
	cout << "a[all()] = " << a[all()] << endl;
}