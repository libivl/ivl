#include <ivl/ivl>
using namespace ivl;
using namespace std;

// TODO: STUB
int main()
{
	cout << arr(1,2,3) << endl;
	cout << arr[_,1,2,3,4,5] << endl;

	cout << arr[_,1,_,3] << endl;
	cout << (1,_,3) << endl;

	cout << arr[_,1,2,_,3,4,_,5,7] << endl;
	
	cout << arr[_,1,_,2,sep(),5,_,7] << endl;

	//cout << arr[_,1,2,_,3,4,_,5,6,_,7,8] << endl; // tuple not big enough yet!!


	array<int> a = arr[_, 1, 2];
	array<int> b = arr[_, 3, 4];
	
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	
	cout << arr[_, a, b] << endl;
	
	//cout << arr[_, a, _, b] << endl;
	

/*
	rng(1,_,3)

	a[1,_,3]
*/

/*	cout << arr[_,1,2] << endl;
	cout << arr[_,1,2,3] << endl;
	cout << arr[_,1,2,3,4] << endl;
	cout << arr[_,1.1,2.1,3,4.5,5,6,7.1,8.2] << endl;
*/

}
