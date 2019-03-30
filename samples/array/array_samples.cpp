#include <ivl/array.hpp>
#include <ivl/ivl> // TODO: this is for 'all'. but needs fix.

using namespace std;
using namespace ivl;

void array_sample();
void array_operator_sample();
void array_function_sample();

void complex_array_sample();
void complex_array_function_sample();
//void complex_array_operator_sample();

void array_main()
{
//	array_sample();
	array_operator_sample();
//	array_function_sample();

	complex_array_sample();
	complex_array_function_sample();
//	complex_array_operator_sample();
}

void array_sample()
{
	cout << endl << "BASIC ARRAY OPERATIONS" << endl;
	cout << "--------------------------------------" << endl;


	array<int> a;
	cout << "Default constructor: a="<< a << endl << endl;

	array<float> b(5, float(1.1));
	cout << "Construct using element count and default value:" << endl <<"b= " << b << endl << endl;

	double c_ptr[] = {2.1, 1.2, 4.3, 3.4, -1.5};
	array<double> c(5, c_ptr);
	cout << "Construct using element count and C array:" << endl <<"c= " << c << endl << endl;

	array<double> d(c);
	cout << "Copy construct:" << endl <<"d= " << d << endl << endl;

	array<double> e(d, size_t(4));
	cout << "Construct using other array and element count:" << endl <<"e= " << e << endl << endl;

	array<double> f(range<double>(1.1, 1, 6.1));
	cout << "Construct using range:" << endl <<"f= " << f << endl << endl;

	array<double> g = arr(5.6, 7.8, 9.2, 5.8);
	cout << "Construct using element values:" << endl <<"g= " << g << endl << endl;

	array<double> h = cast<double>(b);
	cout << "Construct by casting another array:" << endl <<"h= " << h << endl << endl;

	h = e;
	cout << "Resize and assign:" << endl <<"h = e = " << h << endl << endl;

	h.resize(3, -1.1);
	cout << "Resize and assign scalar:" << endl <<"h = e = " << h << endl << endl;

	h[0] = g[3];
	cout << "Read & write single element:" << endl <<"h[0] = g[3] : h = " << h << endl;
}

void array_operator_sample()
{

	cout << endl << "ARRAY OPERATORS" << endl;
	cout << "--------------------------------------" << endl;

	array<int> c = arr(5, 3, 1, -8, 9);
	array<int> e(range<int>(1,5));
	array<int> f = e;

	cout << "original e: " << e << endl;
	cout << "original c: " << c << endl;

	cout << "---" << endl << endl;

	cout << "++e: " << ++e << endl;
	cout << "e++: " << e++ << endl;
	cout << "new e: " << e << endl;

	cout << "--e: " << --e << endl;
	cout << "e--: " << e-- << endl;
	cout << "new e: " << e << endl;

	cout << "---" << endl << endl;

	cout << "+e: " << +e << endl;
	cout << "-e: " << -e << endl;
	cout << "!e: " << !e << endl;
	cout << "~e: " << ~e << endl;

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

	cout << "---" << endl << endl;

	e[all()] = 1;
	cout << "e[all()] = 1: " << e << endl;
	e = f;

	cout << "---" << endl << endl;

	cout << "e + c: " << (e + c) << endl;
	cout << "e - c: " << (e - c) << endl;
	cout << "e * c: " << (e * c) << endl;
	cout << "e / c: " << (e / c) << endl;
	cout << "e % c: " << (e % c) << endl;
	cout << "... similarly for ^, |, &, >>, <<, &&, || " << endl;

	cout << "---" << endl << endl;

	cout << "e + 3: " << (e + 3) << endl;
	cout << "e - 3: " << (e - 3) << endl;
	cout << "e * 3: " << (e * 3) << endl;
	cout << "e / 3: " << (e / 3) << endl;
	cout << "e % 3: " << (e % 3) << endl;
	cout << "... similarly for ^, |, &, >>, <<, &&, || " << endl;

	cout << "---" << endl << endl;

	cout << "3 + e: " << (3 + e) << endl;
	cout << "3 - e: " << (3 - e) << endl;
	cout << "3 * e: " << (3 * e) << endl;
	cout << "3 / e: " << (3 / e) << endl;
	cout << "3 % e: " << (3 % e) << endl;
	cout << "... similarly for ^, |, &, >>, <<, &&, || " << endl;

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

	cout << "different data type assignments" << endl;
	array<double> z = arr._<double>()(2.0, 3.0, 4.3, 4.5);
	cout << "z: " << z << endl;
	cout << "e = z: " << (e = z) << endl;
	cout << "e += z: " << (e += z) << endl;
}
/*
template<class T>
T why(const T& a)
{
	return 0;
}
*/
template<class T, class S>
T why(const array<T, S>& a)
{
	return 5;
}

void array_function_sample()
{
    // solve std/ivl ambiguities here:
    using ivl::sort;


	cout << endl << "ARRAY FUNCTIONS" << endl;
	cout << "--------------------------------------" << endl;

	array<int> e(range<int>(1,6));
	why(e+1);

	cout << "e: " << e << endl;
	cout << "sum(e)     (scalar): " << sum(e) << endl;
	cout << "prod(e)   (scalar): " << prod(e) << endl;
	cout << "mean(e)   (scalar): " << mean(e) << endl;
	cout << "median(e) (scalar): " << median(e) << endl;
	cout << "cumsum(e)   (array): " << cumsum(e) << endl;
	cout << "cumprod(e)  (array): " << cumprod(e) << endl;
	cout << "diff(e)     (array): " << diff(e) << endl;
	cout << "shift(e)    (array): " << shift(e,-3,-1) << endl;
	cout << "cshift(e)   (array): " << cshift(e,1) << endl;
	cout << "cshift(e)   (array): " << cshift(e,2) << endl;
	cout << "cshift(e)   (array): " << cshift(e,3) << endl;
	cout << "cshift(e)   (array): " << cshift(e,4) << endl;
	cout << "cshift(e)   (array): " << cshift(e,5) << endl;

	cout << "---" << endl << endl;

	array<double>g = cast<double>(e);
	cout << "g : " << endl << g << endl << endl;
	cout << "abs (g) : " <<  endl << abs(g) << endl << endl;
	cout << "exp (g) : " << endl << exp(g) << endl << endl;
	cout << "log (g) : " << endl << log(g) << endl << endl;
	cout << "log10 (g) : " << endl << log10(g) << endl << endl;
	cout << "power(g,2) : " << endl << power(g, 2.0) << endl << endl;
	cout << "power(2,g) : " << endl << power(2.0 ,g) << endl << endl;
	cout << "power(g,g) : " << endl << power(g,g) << endl << endl;

	cout << "sin (g) : " << endl << sin(g) << endl << endl;
	cout << "cot (g) : " << endl << cot(g) << endl << endl;
	cout << "sec (g) : " << endl << sec(g) << endl << endl;
	cout << "csc (g) : " << endl << csc(g) << endl << endl;
	cout << "coth (g) : " << endl << coth(g) << endl << endl;
	cout << "sech (g) : " << endl << sech(g) << endl << endl;
	cout << "csch (g) : " << endl << csch(g) << endl << endl;
	cout << "atan (g) : " << endl << ivl::atan(g) << endl << endl;
	cout << "acot (g) : " << endl << acot(g) << endl << endl;
	cout << "asec (g) : " << endl << asec(g) << endl << endl;
	cout << "acsc (g) : " << endl << acsc(g) << endl << endl;
	cout << "asinh (g) : " << endl << asinh(g) << endl << endl;
	cout << "acosh(g+1) : " << endl << acosh(g + 1.0) << endl << endl;
	cout << "atanh(g+1) : " << endl << atanh(g + 1.0) << endl << endl;
	cout << "acoth(g+1) : " << endl << acoth(g + 1.0) << endl << endl;
	cout << "asech(1/(g+1)) : " << endl << asech(1.0 / (g + 1.)) << endl << endl;
	cout << "acsch(g+1) : " << endl << acsch(g + 1.0) << endl << endl;

	g *= 1.2;
	cout << "g *= 1.2: " << g << endl;
	cout << "round(g): " << round(g) << endl;
	cout << "fix(g)  : " << fix(g) << endl;
	cout << "ceil(g) : " << ceil(g) << endl;
	cout << "floor(g): " << floor(g) << endl;
	cout << "rem(g)  : " << rem(g, 2.) << endl;
	cout << "mod(g)  : " << mod(g, 2.) << endl;
	cout << "flip(g) : " << flip(g) << endl;
	cout << "sort(g) : " << sort(g) << endl;
    cout << "sort[desc](g): " << sort[desc](g) << endl;

	cout << endl;

	e = arr(10, 9, 3, 500);
	cout << "e          : " << e << endl;
	cout << "mean(e)    : " << mean(e) << endl;
	cout << "median(e)  : " << median(e) << endl;
	cout << "var(e)     : " << var(e) << endl;
	cout << "std(e)     : " << ivl::std(e) << endl;

	cout << "isequal(e, cshift(e,6)): " << isequal(e, cshift(e,6)) << endl;

	array<double> h = linspace<double>(1,10);
	cout << "linspace(1, 10) (array): " << h << endl;
	cout << "h.length() " << h.length() << endl;
	h = logspace<double>(1.5, 3.3 , 24);
	cout << "logspace(1, 10) (array): " << h << endl;
	cout << "h.length() " << h.length() << endl;

	cout << "exp(range(1,5)) : " << exp(arr._<double>()(1.,2.,3.,4.,5.)) << endl;
	cout << "log2(16,32,64,128,256) : " << log2(arr._<double>()(16,32,64,128,256)) << endl;
	cout << "nextpow2(15,30,61,132,280) : " << nextpow2(arr._<double>()(15,30,61,132,280)) << endl;

}



void complex_array_sample()
{
	array<complex<int> > a(4);

	for(size_t i=0; i<4; i++)
		a[i] = int(2*i);
	cout << "Construct empty 5-element array & assign all elements:" << endl;
	cout << "1. with real values: a = " << a << endl;

	for(size_t i=0; i<4; i++)
		a[i] = complex<int>(0, int(2*i));
	cout << "2. with complex values: a = " << a << endl << endl;

	array<complex<int> > b(6,-4);
	cout << "Construct 6-element array with:" << endl;
	cout << "scalar  value -4: b = " << b << endl;
	array<complex<int> > c(6,complex<int>(0,-4));
	cout << "complex value (0,-4): c = " << c << endl << endl;

	complex<int> p[5] = { 5, 3, 0, -18, 9 };
	array<complex<int> > d(5,p);
	cout << "Construct by c-array: d = " << d << endl;

	array<int> y = arr._<int>()(5,6,0,-9);
	array<complex<int> > st;
	st = ( cast<complex<int> > (y) );

	array<complex<int> > at( ivl::cast<complex<int> > (y) );

	array<complex<int> > t = ivl::cast<complex<int> >(arr(5,6,0,-9));
	cout << "Construct by element values: t = " << t << endl;

	array<complex<int> > e = a;
	cout << "Construct by array copy: e = a = " << e << endl << endl;

	array<complex<double> > f = cast<complex<double> >(a);
	cout << "Construct by array copy (different type): " << endl;
	cout << "a<int> = " << a << endl;
	cout << "f<double> = " << f << endl << endl;

	d = b;
	cout << "Resize & assign to array: d = b = " << d << endl;
	d = 13;
	cout << "Assign one scalar element: d = " << d << endl;

	c.resize(7, complex<int>(0,8));
	cout << "Resize c & assign value (0,8): c = " << c << endl;
}


void complex_array_function_sample()
{

	cout << endl << "ARRAY FUNCTIONS" << endl;
	cout << "--------------------------------------" << endl;

	array<complex<int> > e = cast<complex<int> >(arr(1, 5, 6, 7, 8, 9));

	array<complex<int> > f(e);

	e[1] = complex<int>(5, 1);
	cout << "e: " << e << endl;
	cout << "sum(e)     (scalar): " << sum(e) << endl;
	cout << "prod(e)    (scalar): " << prod(e) << endl;
	cout << "mean()     (scalar): " << mean(e) << endl;
	cout << "median()   (scalar): " << median(e) << endl;
	cout << "cumsum(e)   (array): " << cumsum(e) << endl;
	cout << "cumprod(e)  (array): " << cumprod(e) << endl;
	cout << "diff(e)     (array): " << diff(e) << endl;
	cout << "shift(e)    (array): " << shift(e, -3, complex<int>(0, -1)) << endl;
	cout << "cshift(e)   (array): " << cshift(e,1) << endl;
	cout << "cshift(e)   (array): " << cshift(e,2) << endl;
	cout << "cshift(e)   (array): " << cshift(e,3) << endl;
	cout << "cshift(e)   (array): " << cshift(e,4) << endl;
	cout << "cshift(e)   (array): " << cshift(e,5) << endl;

	//cout << "e.apply()   (array): " << apply(e,&func) << endl;
	//cout << "e.apply().sort()   : " << sort(apply(e,&func)) << endl;

	cout << "---" << endl << endl;

	array<complex<double> > g(cast<complex<double> >(e));

	cout << "g       : " << g << endl;
	cout << "abs (g) : " << abs(g) << endl;
	cout << "exp (g) : " << exp(g) << endl;
	cout << "log (g)   : " << log(g) << endl;
	cout << "log10 (g) : " << log10(g) << endl;
	//cout << "pow (g,2) : " << power(g, 2.0) << endl;
	//cout << "pow (2,g) : " << power(2.0 ,g) << endl;
	//cout << "pow (g,g) : " << power(g,g) << endl;

	cout << "sin (g) : " << sin(g) << endl;

	cout << "cot (g)   : " << cot(g) << endl;
	cout << "sec (g)   : " << sec(g) << endl;
	cout << "csc (g)   : " << csc(g) << endl;
	cout << "coth (g)  : " << coth(g) << endl;
	cout << "sech (g)  : " << sech(g) << endl;
	cout << "csch (g)  : " << csch(g) << endl;
	cout << "atan (g)  : " << atan(g) << endl;
	cout << "acot (g)  : " << acot(g) << endl;
	cout << "asec (g)  : " << asec(g) << endl;
	cout << "acsc (g)  : " << acsc(g) << endl;
	cout << "asinh (g) : " << asinh(g) << endl;

	cout << "acosh(g+1): " << acosh(g + complex<double>(1.0)) << endl;
	cout << "atanh(g+1): " << atanh(g + complex<double>(1.0)) << endl;
	cout << "acoth(g+1): " << acoth(g + complex<double>(1.0)) << endl;
	cout << "asech(1/(g+1)): " << asech(complex<double>(1.) / (g + complex<double>(1.))) << endl;
	cout << "acsch(g+1): " << acsch(g + complex<double>(1.0)) << endl;

	//g *= 1.2;
	cout << "g *= 1.2: " << g << endl;
//	cout << "round(g): " << round(g) << endl;
//	cout << "fix(g)  : " << fix(g) << endl;
//	cout << "ceil(g) : " << ceil(g) << endl;
//	cout << "floor(g): " << floor(g) << endl;
//	cout << "rem(g)  : " << rem(g, 2.) << endl;
//	cout << "mod(g)  : " << mod(g, 2.) << endl;
	cout << "flip(g) : " << flip(g) << endl;
//	cout << "sort(g) : " << sort(g) << endl;
//	cout << "sort(g,1): " << sort(g, true) << endl;

	cout << endl;

	e = cast<complex<int> >(arr(10, 9, 3, 500));

	cout << "e          : " << e << endl;
	//cout << "e.mean()   : " << e.mean() << endl;
	//cout << "e.median() : " << e.median() << endl;

//	cout << "e.var()    : " << e.var() << endl;

//	cout << "e.std()    : " << e.std() << endl;

	cout << "e.isequal(cshift(e,6)): " << e.isequal(cshift(e,6)) << endl;

	array<double> h = linspace<double>(1,10);
	cout << "linspace(1, 10) (array): " << h << endl;
	cout << "h.length() " << h.length() << endl;
	h = logspace<double>(1.5, 3.3 , 24);
	cout << "logspace(1, 10) (array): " << h << endl;
	cout << "h.length() " << h.length() << endl;

	cout << "exp(range(1,5)) : " << exp(arr._<double>()(1.,2.,3.,4.,5.)) << endl;
	cout << "log2(16,32,64,128,256) : " << log2(arr._<double>()(16,32,64,128,256)) << endl;
	cout << "nextpow2(15,30,61,132,280) : " << nextpow2(arr._<double>()(15,30,61,132,280)) << endl;
}

#if 1
void complex_array_operator_sample()
{

	cout << endl << "ARRAY OPERATORS" << endl;
	cout << "--------------------------------------" << endl;

	int p[5] = { 5, 3, 1, -8, 9 };
	array<int> c(5,p);
	array<int> e(range<int>(1,5));
	array<int> f(e);

	cout << "original e: " << e << endl;
	cout << "original c: " << c << endl;

	cout << "---" << endl << endl;

	cout << "++e: " << ++e << endl;
	cout << "e++: " << e++ << endl;
	cout << "new e: " << e << endl;

	cout << "--e: " << --e << endl;
	cout << "e--: " << e-- << endl;
	cout << "new e: " << e << endl;

	cout << "---" << endl << endl;

	cout << "+e: " << +e << endl;
	cout << "-e: " << -e << endl;
	cout << "!e: " << !e << endl;
	cout << "~e: " << ~e << endl;

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
	//cout << "e && c: " << (e && c) << endl;
	//cout << "e || c: " << (e || c) << endl;

	cout << "---" << endl << endl;

	cout << "e + 3: " << (e + 3) << endl;
	cout << "e - 3: " << (e - 3) << endl;
	cout << "e * 3: " << (e * 3) << endl;
	cout << "e / 3: " << (e / 3) << endl;
	cout << "e % 3: " << (e % 3) << endl;
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
}

#endif

