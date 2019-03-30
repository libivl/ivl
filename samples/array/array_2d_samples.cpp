 #include <iostream>
//#include <ivl/timer.hpp> full bug
#include <ivl/ivl>


void array_2d_sample();
void complex_array_2d_sample();

using namespace std;
using namespace ivl;

void array_2d_main()
{
	array_2d_sample();
	complex_array_2d_sample();
}


void array_2d_sample()
{
	using ivl::rand;
#if 1
	cout << endl << "BASIC ARRAY_2D OPERATIONS" << endl;
	cout << "--------------------------------------" << endl;
	double p[36] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,
		23,24,25,26,27,28,29,30,31,32,33,34,35,36};

	//array_nd<double> c(idx(4,3),p);
	//array_2d<int> a(3,2,(int*) p);
	//cout << "Construct 3x2 array with rows, cols and arr: " << endl;
	//cout << a << endl;

	array_2d<double> b(idx(3,4), p);
	cout << "Construct 3x4 array with idx(row, col) and pointer: " << endl;
	cout << b << endl;
	cout << "Length of 1-dim array: " << b.numel() << endl << endl;

	cout << "flipud() : " << endl << flipud(b) << endl;
	cout << "fliplr() : " << endl << fliplr(b) << endl;
	flipdim(b,1);
	cout << "chain flip: " << endl << flipdim(flipdim(b,1),0) << endl; // flipdim is array_nd

	array_2d<double> d(flipdim(flipdim(b,1), 0));
	cout << "array_2d from array_nd: " << endl << d << endl;

//	array_nd<unsigned char>d2(d);
//	cout << "array_2d as array_nd - ndim : " << d2.ndims() << endl;

	array_2d<int> d3(cast<int>(d));
	cout << "cast array_2d<double> to int: " << endl << d3 << endl;

	b.resize(idx(2,6));
	cout << "resize to 2x6: " << endl << b << endl;

	array_nd<double> c(b);
	cout << "isequal(): " << b.isequal(c) << endl ;

	array<int> e(arr(1,2,3));
	array<int> f(arr(4,5,6));
	cout << endl << "e: " << e << endl << "f: " << f << endl;
	cout << "cross product (e x f): " << cross(e,f) << endl;
#endif
#if 1
	cout << "dot product   (e . f): " << int(dot(e,f)) << endl;

	cout << endl << "d: " << endl << d << endl;
	cout << "diag(d)   : " << diag(d, 1) << endl;
    /*
	cout << endl << "left half of d: " << endl << split(d,2,1)[0] << endl;
	array_2d<double> d1(split(d,2,1)[0]);
    */
    array_2d<double> d1 = d; // temporary fix
	cout << "diag(left half of d)    : " << diag(d1) << endl;

	typedef types::is_kind_base_eq<index_array, index_array_all_type>::type tst0;
	//typedef types::is_kind_base_eq_recurse<index_array, index_array_all_type>::type tst;

using namespace ivl::types;
typedef index_array A;
typedef index_array_all_type B;
typedef t_xor<t_and<is_ivl_array<A>, is_ivl_array<B> >,
		is_kind_base_eq_recurse<
			get_value<A>::type, get_value<B>::type> >::type tst1;



	cout << "horzcat d1, d1	: " << endl << horzcat(d1, d1) << endl;

	cout << "vertcat d1, d1	: " << endl << vertcat(d1, d1) << endl;

	cout << "tril(d): " << endl << tril(d) << endl;
	cout << "triu(d): " << endl << triu(d) << endl;

	cout << "d           : " << endl << d << endl;
	cout << "transpose(d): " << endl << transpose(d) << endl;
	cout << "rot90(d)    : " << endl << rot90(d) << endl;
	cout << "rot90(d,-1) : " << endl << rot90(d,-1) << endl;

	cout << "eye(5)      : " << endl << eye<int>(5) << endl;
	cout << "ones<int>(idx(3,3,2)): " << endl << ones<int>(idx(3,3,2)) << endl;
	cout << "zeros<double>(idx(3,3,2)): " << endl << zeros<double>(idx(3,3,2)) << endl;

	cout << "rand<int>(3,3,3) : " << endl << rand.type<int>(idx(3,3,3)) << endl;

//	cout << "meshgrid(1:3, 10:14) : " << endl << meshgrid<int>(size_range(1,3), size_range(10,14)) << endl;

//	array_nd<double>d4(idx(3,2,2), range<double>(1,12));
//	cout << "array_nd<uchar> size(): " << d2.size() << endl;



	//cout << "array_nd c: " << endl << c << endl ;

	// SN: Edw exw parakampsei to provlhma tou pow me to na ksanaftiaxnw array2d. Alla mallon 8eloume kalyterh lysh. :-)
	// SN: Ide item no. 41 sto TODO list.
	//cout << "Operations on 2d-array: " << endl;
	//cout << pow(b, 2.0) - (3.5 * b) + 2.1 << endl;

#endif
}

void complex_array_2d_sample()
{
	using ivl::rand;

	cout << endl << "BASIC ARRAY_2D COMPLEX OPERATIONS" << endl;
	cout << "--------------------------------------" << endl;
	complex<double> p[] = {
		complex<double>(1,2), complex<double>(3,4), complex<double>(5,6), complex<double>(7,8),
		complex<double>(9,10), complex<double>(11,12), complex<double>(13,14), complex<double>(15,16),
		complex<double>(17,18), complex<double>(19,20), complex<double>(21,22), complex<double>(23,24),
		complex<double>(25,26), complex<double>(27,28), complex<double>(29,30), complex<double>(31,32),
		complex<double>(33,34), complex<double>(35,36)};

	array_2d<complex<double> > b(idx(3,4), p);
	cout << "Construct 3x4 array with idx(row, col) and pointer: " << endl;
	cout << b << endl;
	cout << "Length of 1-dim array: " << b.numel() << endl << endl;

	cout << "flipud() : " << endl << flipud(b) << endl;
	cout << "fliplr() : " << endl << fliplr(b) << endl;
	cout << "chain flip: " << endl << flipdim(flipdim(b,1),0) << endl; // flipdim is array_nd

	array_2d<complex<double> > d(flipdim(flipdim(b,1),0));
	cout << "array_2d from array_nd: " << endl << d << endl;

	std::cout<< (cast<unsigned char>(array_2d<double>()));
	array<unsigned char> ff(cast<unsigned char>(array_2d<double>()));
	array_2d<unsigned char> ff2(cast<unsigned char>(array_2d<double>()));
	//  array_nd<unsigned char> ff3(cast<unsigned char>(array_2d<double>())); //FAILZ!!! on VC
	cast<unsigned char>(array_2d<double>()).stride(); // should fail.



	cast<complex<unsigned char> >(array_2d<double>());
	cast<unsigned char>(array_2d<complex<double> >());
	cast<complex<unsigned char> >(array_2d<complex<double> >());

	array<complex<double> >ffff(-(-(-b)));

	array_nd<complex<unsigned char> >d2(cast<complex<unsigned char> >(d));
	cout << "array_2d as array_nd - ndim : " << d2.ndims() << endl;

	array<complex<int> > xx;
	xx = xx;
	xx = b;
	xx = cast<complex<int> >(d);
	array_2d<complex<int> > d3(cast<complex<int> >(d));
	cout << "cast array_2d<double> to int: " << endl << d3 << endl;

	b.resize(idx(2,6));
	cout << "resize to 2x6: " << endl << b << endl;

	array_nd<complex<double> > c(b);
	cout << "isequal(): " << b.isequal(c) << endl ;

	array<complex<int> > e(
		arr(complex<int>(1,0),complex<int>(2,0),complex<int>(3,0)));

	array<complex<int> > f(
		arr(complex<int>(4,0),complex<int>(5,0),complex<int>(6,0)));

	cout << endl << "e: " << e << endl << "f: " << f << endl;

// TODO: MSVC fails
//	cout << endl << "d.as_rows(): " << d.as_rows() << endl;
//	cout << endl << "d.as_columns(): " << d.as_columns() << endl;

	cout << "cross product (e x f): " << cross(e,f) << endl;
	cout << "dot product   (e . f): " << dot(e,f) << endl;

	cout << endl << "d: " << endl << d << endl;
	cout << "diag(d)   : " << diag(d, 1) << endl;
    /*
	cout << endl << "left half of d: " << endl << split(d,2,1)[0] << endl;
	array_2d<complex<double> > d1(split(d,2,1)[0]);
    */
    array_2d<complex<double> > d1 = d; // temporary fix
	cout << "diag(left half of d)    : " << diag(d1) << endl;

	cout << "horzcat d1, d1	: " << endl << horzcat(d1, d1) << endl;
	cout << "vertcat d1, d1	: " << endl << vertcat(d1, d1) << endl;

	cout << "tril(d): " << endl << tril(d) << endl;
	cout << "triu(d): " << endl << triu(d) << endl;

	cout << "d           : " << endl << d << endl;
	cout << "transpose(d): " << endl << transpose(d) << endl;
	cout << "rot90(d)    : " << endl << rot90(d) << endl;
	cout << "rot90(d,-1) : " << endl << rot90(d,-1) << endl;

	cout << "eye(5)      : " << endl << eye<int>(5) << endl;
	cout << "ones<int>(idx(3,3,2)): " << endl << ones<int>(idx(3,3,2)) << endl;
	cout << "zeros<double>(idx(3,3,2)): " << endl << zeros<double>(idx(3,3,2)) << endl;

	cout << "rand<int>(3,3,3) : " << endl << rand.type<int>(idx(3,3,3)) << endl;

//	cout << "meshgrid(1:3, 10:14) : " << endl << meshgrid<int>(size_range(1,3), size_range(10,14)) << endl;

//	array_nd<double>d4(idx(3,2,2), range<double>(1,12));
//	cout << "array_nd<uchar> size(): " << d2.size() << endl;



	//cout << "array_nd c: " << endl << c << endl ;

	// SN: Edw exw parakampsei to provlhma tou pow me to na ksanaftiaxnw array2d. Alla mallon 8eloume kalyterh lysh. :-)
	// SN: Ide item no. 41 sto TODO list.
	//cout << "Operations on 2d-array: " << endl;
	//cout << pow(b, 2.0) - (3.5 * b) + 2.1 << endl;
}
