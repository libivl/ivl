#include <ivl/ivl>

int main()
{
	using namespace std;
	using namespace ivl;

	cout << endl <<
	"last - find offset(s) of last non-zero element(s)\n" <<
	"-------------------------------------------------\n" << endl;

	cout <<
	"p = last(a) returns the offset of the last non-zero element of\n" <<
	"array or expression a, which may be boolean, e.g.\n" << endl;

//-----------------------------------------------------------------------------

	int aa[] = {0,5,6,-1,0,0,-4,2,0};
	array<int> a(aa);

	cout << "a = " << a << endl;
	cout << "last(a) = " << last(a) << endl;
	cout << "last(a < 0) = " << last(a < 0) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = last[k](a) returns an array containing the offsets of up to the\n" <<
	"k last non-zero elements. last[1](a) is still an array, unlike\n" <<
	"last(a). E.g.\n" << endl;

//-----------------------------------------------------------------------------

	cout << "last[3](a) = " << last[3](a) << endl;
	cout << "last[1](a) = " << last[1](a) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"When no occurrence is found, p = last(a) returns -1 (one before the\n" <<
	"first element of a, or the greatest value of type size_t), while\n" <<
	"p = last[k](a) returns an empty array:\n" <<
	endl;

//-----------------------------------------------------------------------------

	cout << "int(last(a < -8)) = " << int(last(a < -8)) << endl;
	cout << "last[3](a < -8) = " << last[3](a < -8) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = last(a, s) or p = last[k](a, s) search from the beginning up to,\n" <<
	"and including, offset s, e.g.\n" << endl;

//-----------------------------------------------------------------------------

	cout << "last(a, 5) = " << last(a, 5) << endl;
	cout << "last[3](a, 5) = " << last[3](a, 5) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = last[ord](a) or p = last[ord](a, s) assume a is ordered so\n" <<
	"that no non-zero element comes after a zero one, and performs binary\n" <<
	"search. E.g.\n" << endl;

//-----------------------------------------------------------------------------

	cout << "sort[in][desc](a) = " << ivl::sort[in][desc](a) << endl;
	cout << "last[ord](a > 0) = " << last[ord](a > 0) << endl;
	cout << "last[ord](a > -2, 3) = " << last[ord](a > -2, 3) << endl;
	cout << "int(last[ord](a > 8, 3)) = " << int(last[ord](a > 8, 3)) << endl;

//-----------------------------------------------------------------------------

	cout << endl;
}