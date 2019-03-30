#include <iostream>

#include <ivl/array.hpp>
#include <ivl/array_nd.hpp>
#include <ivl/ivl> // for ivl::all

using namespace std;
using namespace ivl;

void range_slice_test(void);
void indirect_array_test(void);
void indirect_operator_test(void);
void mask_array_test(void);
void subarray_test(void);
//void subarray_operator_test(void);
void gslice_test(void);



void other_array_main()
{
	range_slice_test();
	indirect_array_test();
	indirect_operator_test();
	mask_array_test();
	subarray_test();
//	subarray_operator_test();
	gslice_test();
}

void range_slice_test()
{
	#if 0
	cout << endl << "RANGE, SLICE, & SLICE_ARRAY" << endl;
	cout << "--------------------------------------" << endl;

	array<int> a(range<int>(0,10));
	cout << "Construct array by range: a = " << a << endl;

	a = range<int>(0,2,11);
	cout << "Assign range with step = 2: a = " << a << endl;

	cout << "Range diff(): " << diff(a) << endl;

	array<double> b = range<double>(0.,.2,1.);
	cout << "Assign range with step = .2: b = " << b << endl;

	int p[] = { 2, 5, 8, 10, 7, 4, 1 };
	array<int> c(7,p);
	cout << "c = " << c << endl;

	array<int> d = c[size_range(0,3)];
	cout << "Range array / read: d = " << d << endl;

	c[size_range(2,5)] = 0;
	cout << "Range array / write: c = " << c << endl;

	d = c[slice(0,4,1)];
	cout << "Slice array / read: d = " << d << endl;

	c[slice(2,4,1)] = -1;
	cout << "Slice array / write: c = " << c << endl;

	c[slice(2,4,1)] *= 10;
	cout << "Slice array operator *= 10 :" << c << endl;

	c[slice(2,4,1)] ^= 3;
	cout << "Slice array operator ^= 3 :" << c << endl;
	#endif
}

template<class X, class Y>
void plusop(array<X, Y>&a)
{
	a+=1;
}
void indirect_array_test() // indirect array
{
#if 0
	cout << endl << "INDIRECT ARRAY" << endl;
	cout << "--------------------------------------" << endl;

	int p[] = { 2, 5, 8, 10, 7, 4, 1, -5, 0, 14, 8, -9 };
	array<int> a(12,p);
	cout << "Original a = " << a << endl;

	size_array index = idx(1,2,4,5,9);
	cout << "Index array: " << index << endl;

	array<int> b(a[index]);
	cout << "Indirect array / read: b = a[index]: " << b << endl;

	a[index] = 0;
	cout << "Indirect array / write: a[index] = 0: " << a << endl;
	plusop(rval(a[index]));
	(a[index]) += 1;
	cout << "Indirect array / write: a[index] += 1: " << a << endl;
	#endif
}

void indirect_operator_test()
{
#if 0
	cout << endl << "INDIRECT ARRAY OPERATORS" << endl;
	cout << "--------------------------------------" << endl;

	int p[] = { 2, 4, 6, 8, 10, 11, -1, -3, -5 };
	array<int> a(9, p);
	array<int> c(a);
	array<int> b(6, p);
	b *= -1;
	size_array indx(a.size()/2);
	for (size_t i = 0; i < a.size() / 2; i++) indx[i] = 2*i;

	cout << "original a: " << a << endl << endl;
	cout << "indx: " << indx << endl << endl;

	// ALL ?= operators return VOID!
	cout << "Operations with scalar." << endl;
	a[indx] += 10;
	cout << "a[indx] += 10: " << a << endl << endl;
	a = c;
	a[indx] -= 10;
	cout << "a[indx] -= 10: " << a << endl << endl;
	a = c;
	a[indx] *= 10;
	cout << "a[indx] *= 10: " << a << endl << endl;
	a = c;
	a[indx] /= 10;
	cout << "a[indx] /= 10: " << a << endl << endl;
	a = c;
	a[indx] %= 10;
	cout << "a[indx] %= 10: " << a << endl << endl;
	a = c;
	cout << "... similarly for ^=, &=, |=, >>=, <<= ." << endl;
	a[indx] ^= 10;
	cout << "a[indx] ^= 10: " << a << endl << endl;
	//a = c;
	//a[indx] &= 10;
	//cout << "a[indx] &= 10: " << a << endl << endl;
	//a = c;
	//a[indx] |= 10;
	//cout << "a[indx] |= 10: " << a << endl << endl;
	//a = c;
	//a[indx] >>= 10;
	//cout << "a[indx] >>= 10: " << a << endl << endl;
	//a = c;
	//a[indx] <<= 10;
	//cout << "a[indx] <<= 10: " << a << endl << endl;
	//a = c;

	cout << "---" << endl << endl;
	cout << "Operations with array." << endl;
	cout << "b: " << b << endl << endl;
	a[indx] += b[rng(0, 3)];
	cout << "a[indx] += b[rng(0, 3)]: " << a << endl << endl;
	a = c;
	b.resize(4);
	cout << "b: " << b << endl << endl;
	a[indx] -= b;
	cout << "a[indx] -= b: " << a << endl << endl;
	a = c;
	a[indx] *= b;
	cout << "a[indx] *= b: " << a << endl << endl;
	a = c;
	a[indx] /= b;
	cout << "a[indx] /= b: " << a << endl << endl;
	a = c;
	a[indx] %= b;
	cout << "a[indx] %= b: " << a << endl << endl;
	a = c;
	cout << "... similarly for ^=, &=, |=, >>=, <<= ." << endl;
	cout << "---" << endl << endl;
	a = c;
	a[indx] = empty<int>();
	cout << "a[indx] = empty: " << a << endl << endl;


	//a[indx] ^= b;
	//cout << "a[indx] ^= b: " << a << endl << endl;
	//a = c;
	//a[indx] &= b;
	//cout << "a[indx] &= b: " << a << endl << endl;
	//a = c;
	//a[indx] |= b;
	//cout << "a[indx] |= b: " << a << endl << endl;
	//a = c;
	//a[indx] >>= b;
	//cout << "a[indx] >>= b: " << a << endl << endl;
	//a = c;
	//a[indx] <<= b;
	//cout << "a[indx] <<= b: " << a << endl << endl;
	//a = c;
	#endif
}

template<class A>
void whatami(const A& a)
{
	a.whatami();
}

void mask_array_test()
{
#if 0
	cout << endl << "MASK ARRAY" << endl;
	cout << "--------------------------------------" << endl;

	int p[] = { 2, 5, 8, 10, 7, 4, 1, -5, 0, 14, 8, -9 };
	array<int> a(12,p);
	cout << "Original a = " << a << endl;

	bool_array indx(a > 4);
	cout << "Bool array idx = (a > 4): " << indx << endl;

	array<int> b(a[indx]);
	cout << "Mask array / read: b = a[idx]: " << b << endl;

	a[indx] = 5;
	cout << "Mask array / write: a[idx] = 0: " << a << endl;

	a[indx] += 100;
	cout << "Mask array operator += : " << a << endl;

	a[indx] &= 3;
	cout << "Mask array operator &= : " << a << endl;
#endif
}


void subarray_test()
{

	cout << endl << "SUB ARRAY TEST" << endl;
	cout << "------------------------------------------------" << endl;

	size_array sz(idx(4,3,2));
	array_nd<double> a(sz, range<double>(23,-1,0));

	//array<index_array> index = arr(size_range(0,3),idx(1,2),1);
	array<index_array> index = idxn(size_range(0,3),1,all());
	//array<index_array> index = idxn(all(), all(), all());

	cout << "Original array: a = " << a << endl;
	//cout << "Index array: " << index << endl;

	//array_nd<int> b(a(all(), size_range(1,2), 1));
	//array_nd<int> b(a(all(), idx(1,2), 1));

	array_nd<double> y(a(1, all(), all()));
	cout << "a(1, all(), all()): " << endl << y << endl;



	array_nd<double> b(a(idx(1,2), all(), 1));
	cout << "Sub_array / read: b = a(index): " << endl << b << endl;

	a(index) = -1;
	cout << "Sub_array / write: a(index) = -1: " << endl << a << endl;

	a(index) += 100;
	cout << "Sub_array operator += 100: " << endl << a << endl;

	a(index) /= 2;
	cout << "Sub_array operator /= 2: " << endl << a << endl;

	array_nd<int> c(sz, range<int>(0,23));
	cout << "c: " << endl << c << endl;
	cout << "flipdim(c,1):  " << endl << flipdim(c, 1) << endl ;

	cout << "cut rows 0 & 2: " << endl;
	//cout << a(idx(1,1,2,1,2), all(), all()).cut() << endl;
	a(idx(0,2), all(), all()) = empty<double>();
	cout << a << endl;

	cout << "cast test:  " << cast<double>(c(size_range(1,2),size_range(0,2),1)) << endl;

	cout << "advanced cast test: " << endl;

	//debugging::report(arr(arr(1.1,1.2),arr(1.1,1.2,1.3),arr(1.1,1.2)));
	cout << "a: " << a << endl;
	array<array<size_t> > bs = (cast<array<size_t> >(a));

	cout << "cast<array<size_t> >(a) : " << cast<array<size_t> >(a) << endl;

	bs = (cast<array<size_t> >(a));

	cout << "bs = cast<array<size_t> >(a) : " << bs << endl;

//msvc fail todo:
	bs = (cast<size_t>(a));

	cout << "bs = cast<size_t>(a) : " << bs << endl;

	cout << "cast<size_t>(a) : " << cast<size_t>(a) << endl;

	//cout << "offset array: " << a(all(), size_range(1,2), 1).offset_array() << endl;

	array<array<double> > bd = arr(arr(1.1,1.2),arr(1.1,1.2,1.3),arr(1.1,1.2));
	cout << "bd = arr(arr(1.1,1.2),arr(1.1,1.2,1.3),arr(1.1,1.2)" << endl;
	cout << bd << endl;

	cout << "cast<size_t>(bd) : " << cast<size_t>(bd) << endl;
	cout << "cast<array<size_t> >(bd) : " << cast<array<size_t> >(bd) << endl;

//msvc fail todo:	cout << "array<array>(cast<size_t>(a)) : " <<
//		array<array<size_t> >(cast<size_t>(a)) << endl;

	cout << "array<array>(cast<size_t>(a)) : " <<
		array<array<size_t, tiny>, tiny>(
		cast<array<size_t, tiny> >(cast<size_t>(a))) << endl;

	a = a(idxn(1,1,all()));
	cout << "array = self-subarray: a = " << a << endl;
	//a(index) = index[0];
}

#if 0
void subarray_operator_test() {
	//Checklist of operators


	//array<int> a(range<int>(0,999));
	//size_array dimsizes(ndim, 10);
	//array_nd<int> c(dimsizes, a);	// create a true multi-dim array

	array<size_array> selector_m(ndim);
	selector_m[0] = size_array(size_range(2,5));
	selector_m[1] = size_array(size_range(3,5));
	//selector_m[2] = size_array(size_range(1,4));
	selector_m[2] = size_array(4);
	selector_m[2][0] = 8;
	selector_m[2][1] = 7;
	selector_m[2][2] = 8;
	selector_m[2][3] = 9;

	//c(selector_m) += 1000;	// += with scalar. Check.
	//c(selector_m) -= 2;	// -= with scalar. Check.
	//c(selector_m) *= 2;	// *= with scalar. Check.
	//c(selector_m) /= 2;	// /= with scalar. Check.
	//c(selector_m) %= 4;	// %= with scalar. Check.
	//c(selector_m) *= array<int>(range<int>(0,999)); // *= with array. Check.
	//c(selector_m) += array<int>(range<int>(0,999)); // += with array. Check.
	//c(selector_m) -= array<int>(range<int>(1,1000)); // -= with array. Check.
	//c(selector_m) /= array<int>(range<double>(0.1, 0.1, 100)); // /= with array. Check. (needs double)
	//c(selector_m) %= array<int>(5,1000); // %= with array. Check.
}
#endif


void gslice_test()
{
#if 0
	cout << endl << "GSLICE TEST" << endl;
	cout << "---------------------------------------" << endl;
	// IAVR: remind in documentation that gslice functionality is moved to array_nd

	size_array sz(idx(4,3,2));
	array_nd<int> a(sz, range<int>(0,35));

	gslice gs(16, idx(2,2,1), idx(3,4,2));
	cout << "Original array: a = " << a << endl;

	array_nd<int> b(a(gs));
	cout << "Gslice_array / read: b = a[gs]: " << endl << b << endl;

	a(gs) = -1;
	cout << "Gslice_array / write: a[gs] = -1: " << endl << a << endl;

	a(gs) *= 10;
	cout << "Gslice_array  operator *= 10: " << endl << a << endl;

	a(gs) /= 5;
	cout << "Gslice_array  operator /= 5 : " << endl << a << endl;

	array<slice> as = arr(slice(0,2,3), slice(1,2,4), slice(1,1,2));
	b = a(as);
	cout << "array<slice> / read: b = a(as): " << endl << b << endl;

	a(as) = -8;
	cout << "array<slice> / write: a(as) = -8: " << endl << a << endl;

	a(as) *= 10;
	cout << "array<slice> operator *= 10: " << endl << a << endl;

	a(as) /= 5;
	cout << "array<slice> operator /= 5 : " << endl << a << endl;
#endif
}


template <class T>
void shuffle_array(array<T>& a)
{
    using std::rand;

	size_t randomNum, last;
	T temporary;

	for (last = a.size(); last > 1; last--) {
		randomNum = (size_t) rand( ) % last;
		swap(a[randomNum], a[last - 1]);
	}
}
