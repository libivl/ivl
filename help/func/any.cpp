#include <ivl/ivl>

using namespace std;
using namespace ivl;

int main()
{
	array<int> a = arr(0,5,6,-1,0,0);
	array<int> b = arr(0,0,0,0,0,0);

	cout << "a = " << a << endl;
	cout << "any(a) = " << any(a) << endl;

	cout << "b = " << b << endl;
	cout << "any(b) = " << any(b) << endl;
}