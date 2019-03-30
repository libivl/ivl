#include <ivl/ivl>

using namespace std;
using namespace ivl;

// TODO: STUB
int main()
{
	using ivl::sort;
	using ivl::unique;

	int d[] = { 1, 3, 5, 3, 2, -2, 0, -4, 0, 5, -7, 3, -1, -4 };
	array <int> u, x(d), y(x);
	size_array p, q, r, s;
	array <size_array> pi, ri;
	cout << endl;

	cout << "x = " << x << endl;
	cout << "sort(x) = " << sort(x) << endl;
	cout << "unique(x) = " << unique(x) << endl << endl;

	(_, u, p) = unique++(x);
	cout << "(_, u, p) = unique++(x)" << endl;
	cout << "u    = " << u << endl;
	cout << "x[p] = " << x[p] << endl;
	cout << "p    = " << p << endl << endl;

	(_, u, p) = unique[last]++(x);
	cout << "(_, u, p) = unique[last]++(x)" << endl;
	cout << "u    = " << u << endl;
	cout << "x[p] = " << x[p] << endl;
	cout << "p    = " << p << endl << endl;

 	(_, u, pi) = unique++(x);
	cout << "(_, u, pi) = unique++(x)" << endl;
	cout << "u           = " << u << endl;
	cout << "sort(x)     = " << sort(x) << endl;
	cout << "x[join(pi)] = " << x[join(pi)] << endl;
	cout << "join(pi)    = " << join(pi) << endl << endl;

	cout << "---------------------------------------" << endl;

	(_, u, p, q) = unique++(x);
	cout << "(_, u, p, q) = unique++(x)" << endl;
	cout << "u    = " << u << endl;
	cout << "x[p] = " << x[p] << endl;
	cout << "p    = " << p << endl;
	cout << "x    = " << x << endl;
	cout << "u[q] = " << u[q] << endl;
	cout << "q    = " << q << endl << endl;

	(_, u, p, q) = unique[last]++(x);
	cout << "(_, u, p, q) = unique[last]++(x)" << endl;
	cout << "u    = " << u << endl;
	cout << "x[p] = " << x[p] << endl;
	cout << "p    = " << p << endl;
	cout << "x    = " << x << endl;
	cout << "u[q] = " << u[q] << endl;
	cout << "q    = " << q << endl << endl;

	(_, u, pi, q) = unique++(x);
	cout << "(_, u, pi, q) = unique++(x)" << endl;
	cout << "u    = " << u << endl;
	cout << "sort(x)     = " << sort(x) << endl;
	cout << "x[join(pi)] = " << x[join(pi)] << endl;
	cout << "join(pi)    = " << join(pi) << endl;
	cout << "x    = " << x << endl;
	cout << "u[q] = " << u[q] << endl;
	cout << "q    = " << q << endl << endl;

	cout << "---------------------------------------" << endl;

	cout << "sort[in](x) = " << ivl::sort[in](x) << endl;
	cout << "unique[ord](x) = " << unique[ord](x) << endl << endl;

	(_, u, p) = unique[ord]++(x);
	cout << "(_, u, p) = unique[ord]++(x)" << endl;
	cout << "u    = " << u << endl;
	cout << "x[p] = " << x[p] << endl;
	cout << "p    = " << p << endl << endl;

	(_, u, p) = unique[ord][last]++(x);
	cout << "(_, u, p) = unique[ord][last]++(x)" << endl;
	cout << "u    = " << u << endl;
	cout << "x[p] = " << x[p] << endl;
	cout << "p    = " << p << endl << endl;

 	(_, u, pi) = unique[ord]++(x);
	cout << "(_, u, pi) = unique[ord]++(x)" << endl;
	cout << "u           = " << u << endl;
	cout << "sort(x)     = " << sort(x) << endl;
	cout << "x[join(pi)] = " << x[join(pi)] << endl;
	cout << "join(pi)    = " << join(pi) << endl << endl;

	cout << "---------------------------------------" << endl;

	cout << "x = " << (x = y) << endl;
	cout << "sort(x) = " << sort(x) << endl;
	cout << "unique[off](x) = " << unique[off](x) << endl << endl;

	(_, _, p) = unique++(x);
	(_, r) = unique[off]++(x);
	cout << "(_, _, p) = unique++(x)" << endl;
	cout << "(_, r) = unique[off]++(x)" << endl;
	cout << "p = " << p << endl;
	cout << "r = " << r << endl << endl;

	(_, _, p) = unique[last]++(x);
	(_, r) = unique[last][off]++(x);
	cout << "(_, _, p) = unique[last]++(x)" << endl;
	cout << "(_, r) = unique[last][off]++(x)" << endl;
	cout << "p = " << p << endl;
	cout << "r = " << r << endl << endl;

 	(_, _, pi) = unique++(x);
 	(_, ri) = unique[off]++(x);
	cout << "(_, _, pi) = unique++(x)" << endl;
	cout << "(_, ri) = unique[off]++(x)" << endl;
	cout << "join(pi) = " << join(pi) << endl;
	cout << "join(ri) = " << join(ri) << endl << endl;

	cout << "---------------------------------------" << endl;

	(_, _, p, q) = unique++(x);
	(_, r, s) = unique[off]++(x);
	cout << "(_, u, p, q) = unique++(x)" << endl;
	cout << "(_, r, s) = unique[off]++(x)" << endl;
	cout << "p = " << p << endl;
	cout << "r = " << r << endl;
	cout << "q = " << q << endl;
	cout << "s = " << s << endl << endl;

	(_, _, p, q) = unique[last]++(x);
	(_, r, s) = unique[last][off]++(x);
	cout << "(_, _, p, q) = unique[last]++(x)" << endl;
	cout << "(_, r, s) = unique[last][off]++(x)" << endl;
	cout << "p = " << p << endl;
	cout << "r = " << r << endl;
	cout << "q = " << q << endl;
	cout << "s = " << s << endl << endl;

	(_, _, pi, q) = unique++(x);
	(_, ri, s) = unique[off]++(x);
	cout << "(_, _, pi, q) = unique++(x)" << endl;
	cout << "(_, ri, s) = unique[off]++(x)" << endl;
	cout << "join(pi) = " << join(pi) << endl;
	cout << "join(ri) = " << join(ri) << endl;
	cout << "q = " << q << endl;
	cout << "s = " << s << endl << endl;

}
