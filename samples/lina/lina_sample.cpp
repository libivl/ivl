#include <ivl/lina.hpp>
#include <ivl/func.hpp>

#include <iostream>
#include <complex>

#include <string>
using namespace ivl;

int inv_sample()
{
	std::string line;
	double src[] = {1.0, 2.0, 6.0, 2.0, 5.0, 4.0, 3.0, 6.0, 7.0};
	array_2d<double> X(idx(3,3), src);

	std::cout << "Testing Matrix Invertion:" << std::endl;
	std::cout << "X:" << std::endl << X << std::endl;

	array_2d<double> Y;
	try {
		std::cout << "Y = inv(X):" << std::endl;
		std::getline(std::cin, line);

		lvalue(Y) = inv(X);
		std::cout << Y << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);

	return 0;
}

int inv_cmpl_sample()
{
	std::string line;
	std::complex<double> src[] = {
		1.0, 4.0, 7.0,
		2.0, std::complex<double>(9.0, 1), 8.0,
		std::complex<double>(3.0, 1), 6.0, 9.0
	};
	array_2d<std::complex<double> > X(idx(3,3), src);
	std::cout << "Testing Matrix Invertion (complex):" << std::endl;
	std::cout << "X:" << std::endl << X << std::endl;

	array_2d<std::complex<double> > Y;
	try {
		std::cout << "Y = inv(X):" << std::endl;

		std::getline(std::cin, line);

		lvalue(Y) = inv(X);
		std::cout << Y << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);

	return 0;
}

int qr_sample()
{
	std::string line;
	double src[] = {1.0, 2.0, 6.0, 2.0, 5.0, 4.0, 3.0, 6.0, 7.0, 12.0, 23.0, 14.0};

	array_2d<double> A(idx(3,4), src);

	std::cout << "Testing QR Decomposition:" << std::endl;
	std::cout << "A:" << std::endl << A << std::endl;

	array_2d<double> X;
	try {

		std::cout << "X = qr(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(X) = qr(A);
		std::cout << X << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<double> Q;
	array_2d<double> R;
	try {

		std::cout << "[Q,R] = qr(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(Q,R) = qr(A);
		std::cout << "Q:" << std::endl << Q << std::endl;
		std::cout << "R:" << std::endl << R << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);
	return 0;
}

int qr_cmpl_sample()
{
	std::string line;
	std::complex<double> src[] = {
		std::complex<double>(1.0, 1.0), 2.0, 6.0,
		2.0, 5.0, 4.0,
		3.0, 6.0, 7.0,
		12.0, 23.0, 14.0
	};

	array_2d<std::complex<double> > A(idx(3,4), src);

	std::cout << "Testing QR Decomposition:" << std::endl;
	std::cout << "A:" << std::endl << A << std::endl;

	array_2d<std::complex<double> > X;
	try {

		std::cout << "X = qr(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(X) = qr(A);
		std::cout << X << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<std::complex<double> > Q;
	array_2d<std::complex<double> > R;
	try {

		std::cout << "[Q,R] = qr(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(Q,R) = qr(A);
		std::cout << "Q:" << std::endl << Q << std::endl;
		std::cout << "R:" << std::endl << R << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);
	return 0;
}


int eig_sample()
{
	std::string line;
	double src[] = {1.0, 5.0, 6.0, 2.0, 5.0, 7.0, 3.0, 6.0, 8.0};
	double src2[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};

	array_2d<double> X(idx(3,3), src);
	array_2d<double> Y(idx(3,3), src2);

	std::cout << "Testing EigenValues and Eigenvector Computation:" << std::endl;
	std::cout << "X:" << std::endl << X << std::endl;

	array<std::complex<double> > E;
	try {
		std::cout << "E = eig(X):" << std::endl;

		std::getline(std::cin, line);

		lvalue(E) = eig++(X);
		std::cout << "E:" << std::endl << E << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<std::complex<double> > V;
	array_2d<std::complex<double> > D;
	try {

		std::cout << "[V,D] = eig(X):" << std::endl;

		std::getline(std::cin, line);

		lvalue(V, D) = eig++(X);
		std::cout << "V:" << std::endl << V << std::endl;
		std::cout << "D:" << std::endl << D << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::cout << "X:" << std::endl << X << std::endl;
	std::cout << "Y:" << std::endl << Y << std::endl;
	try {
		std::cout << "E = eig(X, Y):" << std::endl;

		std::getline(std::cin, line);

		lvalue(E) = eig++(X, Y);
		std::cout << "E:" << std::endl << E << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	try {

		std::cout << "[V,D] = eig(X,Y):" << std::endl;

		std::getline(std::cin, line);

		lvalue(V, D) = eig++(X, Y);
		std::cout << "V:" << std::endl << V << std::endl;
		std::cout << "D:" << std::endl << D << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);

	return 0;
}

int eig_cmpl_sample()
{
	std::string line;
	std::complex<double> src[] = {std::complex<double>(1.0, 1.0), 52.0, 6.0, 2.0, 5.0, 7.0, 3.0, 6.0, 8.0};

	array_2d<std::complex<double> > X(idx(3,3), src);

	std::cout << "Testing EigenValues and Eigenvector Computation:" << std::endl;
	std::cout << "X:" << std::endl << X << std::endl;

	array<std::complex<double> > E;
	try {
		std::cout << "E = eig(X):" << std::endl;

		std::getline(std::cin, line);

		lvalue(E) = eig++(X);
		std::cout << "E:" << std::endl << E << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<std::complex<double> > V;
	array_2d<std::complex<double> > D;
	try {

		std::cout << "[V,D] = eig(X):" << std::endl;

		std::getline(std::cin, line);

		lvalue(V, D) = eig++(X);
		std::cout << "V:" << std::endl << V << std::endl;
		std::cout << "D:" << std::endl << D << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);
	return 0;
}

int svd_sample()
{
	std::string line;
	double src[] = {1.0, 3.0, 5.0, 7.0, 2.0, 4.0, 6.0, 8.0};

	array_2d<double> A(idx(4,2), src);

	std::cout << "Testing SVD Decomposition:" << std::endl;
	std::cout << "A:" << std::endl << A << std::endl;

	array<double> s;
	try {

		std::cout << "S = svd(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(s) = svd++(A);
		std::cout << s << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<double> U;
	array_2d<double> S;
	try {
		std::cout << "[U, S] = svd(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(U, S) = svd++(A);
		std::cout << "U:" << std::endl << U << std::endl;
		std::cout << "S:" << std::endl << S << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<double> V;
	try {

		std::cout << "[U, S, V] = svd(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(U, S, V) = svd++(A);
		std::cout << "U:" << std::endl << U << std::endl;
		std::cout << "S:" << std::endl << S << std::endl;
		std::cout << "V:" << std::endl << V << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	try {

		std::cout << "pinv(A):" << std::endl;

		std::getline(std::cin, line);

		S = pinv(A);
		std::cout << S << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);
	return 0;
}

int svd_cmpl_sample()
{
	std::string line;
	std::complex<double> src[] = {
		std::complex<double>(1.0, 1.0), 3.0,
		5.0, 7.0,
		2.0, 4.0,
		6.0, 8.0
	};

	array_2d<std::complex<double> > A(idx(4,2), src);

	std::cout << "Testing SVD Decomposition:" << std::endl;
	std::cout << "A:" << std::endl << A << std::endl;

	array<double> s;
	try {

		std::cout << "S = svd(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(s) = svd++(A);
		std::cout << s << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<std::complex<double> > U;
	array_2d<double> S;
	try {
		std::cout << "[U, S] = svd(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(U, S) = svd++(A);
		std::cout << "U:" << std::endl << U << std::endl;
		std::cout << "S:" << std::endl << S << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	array_2d<std::complex<double> > V;
	try {

		std::cout << "[U, S, V] = svd(A):" << std::endl;

		std::getline(std::cin, line);

		lvalue(U, S, V) = svd++(A);
		std::cout << "U:" << std::endl << U << std::endl;
		std::cout << "S:" << std::endl << S << std::endl;
		std::cout << "V:" << std::endl << V << std::endl;

	} catch (ivl::ecomp e) {
		std::cerr << e.what() << std::endl;
	}

	std::getline(std::cin, line);
	return 0;
}


template < class F >
ret < array <int > , array <int > >
match ( const array <F >& x1 , const array <F >& y1 ,
const array <F >& x2 , const array <F >& y2 , F s )
{
	array_2d <F > Ax1 , Ax2 , Ay1 , Ay2 , U , S , V , tmp ;
	(_, Ax1 , Ax2 ) = meshgrid ++( x1 , x2 );
	(_, Ay1 , Ay2 ) = meshgrid ++( y1 , y2 );
	array_2d <F > D = sqrt (( Ax1 - Ax2 ) ->* 2 + ( Ay1 - Ay2 ) ->* 2);
	std::cout << D << std::endl;
	array_2d <F > G = exp ( - D ->* 2 / (2 * _ [ s ] ->* 2));
	std::cout << G << std::endl;
	(_, U , S , V ) = svd ++( G );
	array_2d <F > E = S > 0;
	std::cout << E << std::endl;
	array_2d <F > P = U ()* E ()* V (! _ );
	std::cout << P << std::endl;
	array_2d <F > P2 = mtimes(mtimes(U, E), transpose(V));
	std::cout << P2 << std::endl;
	array < int > c , r ;
	(_, tmp , c ) = max[1] ++( P );
	std::cout << tmp << " : " << c << std::endl;
	(_, tmp , r ) = max ++( P , _ , 0);
	std::cout << tmp << " : " << r << std::endl;
	array < bool > match = r [ c ] == rng (0 , c . length () - 1);
	return (_, find ( match ) ,
	c [ match ]);
}

int main()
{
	array<double> x1,y1,x2,y2;
	x1 = arr(1,2,3);
	y1 = arr(2,3,4);

	x2 = arr(13,12,11);
	y2 = arr(14,13,12);

	//array<int> r1, r2;
	//(_, r1, r2) = match<double>(x1, y1, x2, y2, 32);
	//std::cout << "match: " << r1 << " with " << r2 << std::endl;


	inv_sample();
	inv_cmpl_sample();
	qr_sample();
	qr_cmpl_sample();
	eig_sample();
	eig_cmpl_sample();
	svd_sample();
	svd_cmpl_sample();


	return 0;
}
