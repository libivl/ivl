#include <ivl/ivl>

int main()
{
	using namespace std;
	using namespace ivl;

	cout << endl <<
	"first - find offset(s) of first non-zero element(s)\n" <<
	"---------------------------------------------------\n" << endl;

	cout <<
	"p = first(a) returns the offset of the first non-zero element of\n" <<
	"array or expression a, which may be boolean, e.g.\n" << endl;

//-----------------------------------------------------------------------------

	int aa[] = {0,5,6,-1,0,0,-4,2};
	array<int> a(aa);

	cout << "a = " << a << endl;
	cout << "first(a) = " << first(a) << endl;
	cout << "first(a < 0) = " << first(a < 0) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = first[k](a) returns an array containing the offsets of up to the\n" <<
	"k first non-zero elements, which is equivalent to find[k](a).\n" <<
	"first[1](a) is still an array, unlike first(a). E.g.\n" <<
	endl;

//-----------------------------------------------------------------------------

	cout << "first[3](a) = " << first[3](a) << endl;
	cout << "first[1](a) = " << first[1](a) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"When no occurrence is found, p = first(a) returns a.length() (one\n" <<
	"past the last element of a), while p = first[k](a) returns an empty\n" <<
	"array:\n" << endl;

//-----------------------------------------------------------------------------

	cout << "first(a < -8) = " << first(a < -8) << endl;
	cout << "first[3](a < -8) = " << first[3](a < -8) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = first(a, s) or p = first[k](a, s) start searching from offset s,\n" <<
	"e.g.\n" << endl;

//-----------------------------------------------------------------------------

	cout << "first(a, 2) = " << first(a, 2) << endl;
	cout << "first[3](a, 2) = " << first[3](a, 2) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = first[ord](a) or p = first[ord](a, s) assume a is ordered so\n" <<
	"that no non-zero element comes before a zero one, and performs binary\n" <<
	"search. E.g.\n" << endl;

//-----------------------------------------------------------------------------

	cout << "sort[in](a) = " << ivl::sort[in](a) << endl;
	cout << "first[ord](a > 0) = " << first[ord](a > 0) << endl;
	cout << "first[ord](a > -2, 3) = " << first[ord](a > -2, 3) << endl;
	cout << "first[ord](a > 8, 3) = " << first[ord](a > 8, 3) << endl;

//-----------------------------------------------------------------------------

	cout << endl;
}