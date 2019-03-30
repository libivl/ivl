#include <ivl/ivl>

using namespace std;
using namespace ivl;

// TODO: STUB
int main()
{
	using ivl::sort;

	int d[] = { 1, 5, 5, 3, 3, 2, -2, 0, -4, 0, 8, -7, -1, -4 };
	array <int> s, x(d);
	size_array p;

	cout << "original" << endl << x << endl << endl;

	cout << "sorted" << endl << sort(x) << endl << endl;

	(_, s, p) = sort++(x);
	cout << "idx" << endl << s << endl << x[p] << endl << p << endl << endl;

	(_, s, p) = sort[flip]++(x);
	cout << "flip" << endl << s << endl << x[p] << endl << p << endl << endl;

	(_, s, p) = sort[desc]++(x);
	cout << "desc" << endl << s << endl << x[p] << endl << p << endl << endl;

	(_, s, p) = sort[comp=fn::gt]++(x);
	cout << "comp=gt" << endl << s << endl << x[p] << endl << p << endl << endl;

	cout << "in" << endl << sort[in](x) << endl << x << endl << endl;

	array <int> y = x;
	(_, p) = sort[in][desc]++(x);
	cout << "in, desc" << endl << s << endl << x << endl << y[p] << endl << p << endl << endl;
}
