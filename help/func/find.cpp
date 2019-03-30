#include <ivl/ivl>

int main()
{
	using namespace std;
	using namespace ivl;
	using ivl::find;

	cout << endl <<
	"find - find offsets of non-zero elements\n" <<
	"----------------------------------------\n" << endl;

	cout <<
	"p = find(a) returns a size_array with the offsets of all non-zero\n" <<
	"elements of array or expression a, which may be boolean. The returned\n" <<
	"array is empty if no occurrence is found. E.g.\n" << endl;

//-----------------------------------------------------------------------------

	int aa[] = {0,5,6,-1,0,0,-4,2};
	array<int> a(aa);

	cout << "a = " << a << endl << endl;

	cout << "find(a) = " << find(a) << endl;
	cout << "find(a == 0) = " << find(a == 0) << endl;
	cout << "find(a > 0) = " << find(a > 0) << endl;
	cout << "find(a < -8) = " << find(a < -8) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = find[k](a) only returns up to the k first non-zero elements,\n" <<
	"which is equivalent to first[k](a). E.g.\n" << endl;

//-----------------------------------------------------------------------------

	cout << "find[3](a) = " << find[3](a) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"p = find(a, s) or p = find[k](a, s) starts searching from offset s,\n" <<
	"e.g.\n" << endl;

//-----------------------------------------------------------------------------

	cout << "find(a, 2) = " << find(a, 2) << endl;
	cout << "find[3](a, 2) = " << find[3](a, 2) << endl;

//-----------------------------------------------------------------------------

	cout << endl <<
	"(_,p) = find++(a, ..), for array_nd a and array<array> p, is\n" <<
	"equivalent to p = ind2sub(a, find(a, ..)) and returns the nd indices\n" <<
	"of occurrences found instead of linear offsets.\n" << endl;

	cout <<
	"(_,p) = find[k]++(a, ..) only returns up to the k first non-zero\n" <<
	"elements and is equivalent to (_,p) = first[k]++(a, ..). E.g.\n" << endl;

//-----------------------------------------------------------------------------

	array_2d<int> b(3, 4);
	b[_] = (-5,_,6);

	cout << "b = " << endl << b << endl;
	cout << "find[3](b > 2) = " << find[3](b > 2) << endl;

	array<size_array> p;
	(_,p) = find[3]++(b > 2);

	cout << "(_,p) = find[3]++(b > 2);" << endl;
	cout << "p = " << p << endl;

//-----------------------------------------------------------------------------

	cout << endl;
}