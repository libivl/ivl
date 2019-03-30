#include <ivl/ivl>

using namespace std;
using namespace ivl;

int main()
{
	int d[] = { 1, 5, 5, 3, 3, 2, -2, 0, -4, 0, 8, -7, -1, -4, 9 };
	array <int> x = array <int> (d);

	cout << "original" << endl << x << endl << endl;
	cout << "flip" << endl << flip[in](x) << endl << x << endl << endl;
	cout << "flip" << endl << flip[in](x) << endl << x << endl << endl;
	cout << "flip, swp=nop2" << endl << flip[in][swp=fn::nop2](x) << endl << x << endl << endl;
}