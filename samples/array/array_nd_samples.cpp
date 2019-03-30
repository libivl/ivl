#include <iostream>

#include <ivl/array_nd.hpp>
#include <ivl/func>

void array_nd_sample();
void array_nd_function_sample();
void array_nd_operator_sample();

using namespace std;
using namespace ivl;

void array_nd_main()
{
	array_nd_sample();
	array_nd_function_sample();
	array_nd_operator_sample();

}

void array_nd_sample()
{

	cout << endl << "BASIC ARRAY_ND OPERATIONS" << endl;
	cout << "--------------------------------------" << endl;

	size_array sz(idx(4,3,2));

	array_nd<int> b(sz);

	for(size_t i=0; i<sz[0]; i++)
		for(size_t j=0; j<sz[1]; j++)
			for(size_t k=0; k<sz[2]; k++)
				b(idx(i,j,k)) = int(i+j+k);
	cout << "Construct array_nd of size 4x3x2 & assign elements separately: b = " << endl << b << endl;

	array_nd<double> c(sz, 42.56);
	cout << "Construct (double) array_nd of same size with scalar value: c = " << endl << c << endl;

	std::complex<double> a(1,1);
	cout << endl << "Complex number: " << a << endl;
	array_nd<std::complex<double> > compl_arr(sz, a);
	//cout << endl << compl[0] << endl;
	cout << "Construct array_nd<complex> of same size : compl = " << endl << compl_arr << endl;

	int p[36] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35};
	array_nd<int> d(sz, p);
	cout << "Construct by c-array: d = " << endl << d << endl;

	d.resize(8,8);
	cout << "Resize 4x3x2 to 1-dim 8: d = " << d << endl << endl;

	d.resize(idx(6,3,2), -2);
	cout << "Resize to 6x3x2: d = " << endl << d << endl;

	range<int> r(100,200);
//	array_nd<int> e(sz, r);
//	cout << "Construct by array copy: e = " << endl << e << endl;

//	e = array<int>(5,2);
//	cout << "(Resize) & assign to array: e = " << e << endl << endl;

//	e = 13;
//	cout << "(Resize) & assign one scalar element: e = " << e << endl << endl;

/*	d(1,2,0) = -50;
	cout << "Read & write single element: d[1,2,0] = -50 : d = " << d << endl;

	cout << "1-dimensional array_nd: " << endl << array_nd<int>(36, p) << endl;

	cout << "Coords for offsets: " << endl;
	for (size_t i = 0; i < d.length(); i++)
		cout << i << ": " << ind2sub(d, i) << endl;
	cout << endl;
*/
}

void array_nd_function_sample()
{
    // ambiguous
    using ivl::sort;

	cout << endl << "ARRAY_ND FUNCTIONS" << endl;
	cout << "--------------------------------------" << endl;

	size_array sz(idx(4,3,2));
	array_nd<int> d(idx(3,3), 1);
	array_nd<int> e = d;

	cout << "e: " << endl << e << "d: " << endl << d << endl
		<< "e.isequal(d): " << e.isequal(d) << endl;

	cout << "e: " << endl << e << "d: " << endl << d << endl;

	e = d + 1;

	cout << "e: " << endl << e << "d: " << endl << d << endl
		<< "e.isequal(sz): " << e.isequal(cast<int>(sz)) << endl;

//	array_nd<double> f(sz, range<double>(1,24));

	double a[] = { 1., 2., 3., 4., 5., 6. ,7., 8.,9.,10.,11., 12., 13., 14.,
		15., 16. ,17., 18.,19.,20.,21., 22., 23., 24. };
	array_nd<double> f(sz, a);

	cout << "original f: " << endl << f << endl;

	cout << "split f: " << endl;
	//@@@@TODO: we need this to work:
    //array<array_nd<double> > split_f = split(f, arr(1,2));
	//
    //for (size_t j=0; j < split_f.size(); j++)
	//
    //cout << "Part " << j << ": " << endl << split_f[j] << endl;

	cout << "original f: " << endl << f << endl;
	//cout << "concatenate f with -f: " << endl << f.cat(-f,2).cat(f,2) << endl;
	cout << "f *= 1.2 : " << endl << (f *= 1.2) << endl;
	cout << "min(f) : " << f.min() << endl;
	cout << "max(f) : " << f.max() << endl;
////	cout << "abs(-f) : " << abs(-static_cast<array_common_base<array_nd<double> >&>(f)) << endl;
	cout << "sin(f) : " << sin(f) << endl;
	cout << "floor(f) : " << floor(f) << endl;
	cout << "ceil(f) : " << ceil(f) << endl;
	cout << "cumsum(f) : " << endl << cumsum(f) << endl;
    cout << "sort[desc](f): " << sort[desc](f) << endl;
	cout << "sum(f) : " << sum(f) << endl;
	f /= 1.2;
	//cout << "reshape (f, (3,2,4)) : " << endl << f.reshape(idx(3,2,4)) << endl;
	cout << "reshape (f, (3,2,4)) : " << endl << reshape(f, idx(3,2,4)) << endl;
	cout << "permute (f, (3 1 2)) : " << endl << permute(f, idx(3,1,2)) << endl;
	cout << "repmat (f, (3,2)) : " << endl << repmat(f, idx(1,1)) << endl;
#if 0
	array_nd<int> g(idx(5,4,3));
	for (size_t i = 0; i < g.length(); i++)
		g[i] = (static_cast<double>(rand()) / RAND_MAX) > .8 ? 0 : 1;
	cout << g << endl;
	cout << "g.find(0): " <<  g.find(0) << endl << endl;

	cout << "d.sub2ind(), d.ind2sub(): " << endl;
	cout << "d: " << endl << d << endl;
	for (size_t i = 0; i < d.length(); i++)
	{
		cout << "i: " << i << ", ind2sub(i): " << ind2sub(d, i) ;
		cout << ", sub2ind(ind2sub(i)): " << sub2ind(d, ind2sub(d,i)) << endl;
	}
#endif
	//cout << "concatenate f with -f: " << endl << cat(2, f, -f) << endl;
//	cout << "concatenate f with -f: " << endl ;
/*	cout << cat<double>(0,	arr<double>(0,1,2),
							range<double>(12.40, 3.3, 20.00),
							arr<double>(4,5,6),
							50.2
							) << endl;

	cout << "array_2d cat test: " << endl;
	int data[9] = {0,1,2,3,4,5,6,7,8};
	cout << cat<int>(1, array_2d<int>(idx(3,3),data), array_2d<int>(idx(3,3),data)) << endl;
*/
}


void array_nd_operator_sample()
{

	cout << endl << "array_nd OPERATORS" << endl;
	cout << "--------------------------------------" << endl;

	size_array sz = idx(4,3,2);

	int p[36] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	array_nd<int> e(sz, p);


	array_nd<int> c(sz,10);
	array_nd<int> f(e);

	cout << "original e: " << e << endl;
	cout << "original c: " << c << endl;

	cout << "---" << endl << endl;

////	cout << "+e: " << +e << endl;
////	cout << "-e: " << -e << endl;
////	cout << "!e: " << !e << endl;
////	cout << "~e: " << ~e << endl;

	cout << "---" << endl << endl;

	cout << "e += 1: " << (e += 1) << endl;
	e = f;
	cout << "e -= 1: " << (e -= 1) << endl;
	e = f;
	cout << "e *= 1: " << (e *= 1) << endl;
	e = f;
	cout << "e /= 1: " << (e /= 1) << endl;
	e = f;
	cout << "e %= 1: " << (e %= 1) << endl;
	e = f;
	cout << "... similarly for ^=, |=, &=, >>=, <<= " << endl;
	//cout << "e ^= 1: " << (e ^= 1) << endl;
	//e = f;
	//cout << "e |= 1: " << (e |= 1) << endl;
	//e = f;
	//cout << "e &= 1: " << (e &= 1) << endl;
	//e = f;
	//cout << "e >>= 1: " << (e >>= 1) << endl;
	//e = f;
	//cout << "e <<= 1: " << (e <<= 1) << endl;
	//e = f;

	cout << "---" << endl << endl;

	cout << "e += c: " << (e += c) << endl;
	e = f;
	cout << "e -= c: " << (e -= c) << endl;
	e = f;
	cout << "e *= c: " << (e *= c) << endl;
	e = f;
	cout << "e /= c: " << (e /= c) << endl;
	e = f;
	cout << "e %= c: " << (e %= c) << endl;
	e = f;
	cout << "... similarly for ^=, |=, &=, >>=, <<= " << endl;
	//cout << "e ^= c: " << (e ^= c) << endl;
	//e = f;
	//cout << "e |= c: " << (e |= c) << endl;
	//e = f;
	//cout << "e &= c: " << (e &= c) << endl;
	//e = f;
	//cout << "e >>= c: " << (e >>= c) << endl;
	//e = f;
	//cout << "e <<= c: " << (e <<= c) << endl;
	//e = f;

	cout << "---" << endl << endl;
	cout << "original e:" << endl << e << endl;

	cout << "e + c: " << (e + c) << endl;
	cout << "e - c: " << (e - c) << endl;
	cout << "e * c: " << (e * c) << endl;
	cout << "e / c: " << (e / c) << endl;
	cout << "e % c: " << (e % c) << endl;
	cout << "... similarly for ^, |, &, >>, <<, &&, || " << endl;
	//cout << "e ^ c: " << (e ^ c) << endl;
	//cout << "e | c: " << (e | c) << endl;
	//cout << "e & c: " << (e & c) << endl;
	//cout << "e << c: " << (e << c) << endl;
	//cout << "e >> c: " << (e >> c) << endl;
	cout << "e && c: " << (e && c) << endl;
	cout << "e || c: " << (e || c) << endl;

	cout << "---" << endl << endl;

	cout << "e + 3: " << (e + 3) << endl;
	cout << "e - 3: " << (e - 3) << endl;
	cout << "e * 3: " << (e * 3) << endl;
	cout << "e / 3: " << (e / 3) << endl;
	//cout << "e % 3: " << (e % 3) << endl;
	cout << "... similarly for ^, |, &, >>, <<, &&, || " << endl;
	//cout << "e ^ 3: " << (e ^ 3) << endl;
	//cout << "e | 3: " << (e | 3) << endl;
	//cout << "e & 3: " << (e & 3) << endl;
	//cout << "e << 3: " << (e << 3) << endl;
	//cout << "e >> 3: " << (e >> 3) << endl;
	//cout << "e && 3: " << (e && 3) << endl;
	//cout << "e || 3: " << (e || 3) << endl;

	cout << "---" << endl << endl;

	cout << "3 + e: " << (3 + e) << endl;
	cout << "3 - e: " << (3 - e) << endl;
	cout << "3 * e: " << (3 * e) << endl;
	cout << "3 / e: " << (3 / e) << endl;
	cout << "3 % e: " << (3 % e) << endl;
	cout << "... similarly for ^, |, &, >>, <<, &&, || " << endl;
	//cout << "3 ^ e: " << (3 ^ e) << endl;
	//cout << "3 | e: " << (3 | e) << endl;
	//cout << "3 & e: " << (3 & e) << endl;
	//cout << "3 << e: " << (3 << e) << endl;
	//cout << "3 >> e: " << (3 >> e) << endl;
	//cout << "3 && e: " << (3 && e) << endl;
	//cout << "3 || e: " << (3 || e) << endl;

	cout << "---" << endl << endl;

	cout << "e == 5: " << (e == 5) << endl;
	cout << "e != 5: " << (e != 5) << endl;
	cout << "e < 5 : " << (e < 5) << endl;
	cout << "e <= 5: " << (e <= 5) << endl;
	cout << "e > 5 : " << (e > 5) << endl;
	cout << "e >= 5 : " << (e >= 5) << endl;

	cout << "---" << endl << endl;

	cout << "e == c: " << (e == c) << endl;
	cout << "e != c: " << (e != c) << endl;
	cout << "e < c : " << (e < c) << endl;
	cout << "e <= c: " << (e <= c) << endl;
	cout << "e > c : " << (e > c) << endl;
	cout << "e >= c : " << (e >= c) << endl;

	cout << "---" << endl << endl;

	cout << "++e: " << ++e << endl;
	cout << "e++: " << e++ << endl;
	cout << "new e: " << e << endl;

	cout << "--e: " << --e << endl;
	cout << "e--: " << e-- << endl;
	cout << "new e: " << e << endl;


	cout << "---" << endl << endl;
}
