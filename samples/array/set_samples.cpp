#include <iostream>

#include <ivl/array.hpp>
#include <ivl/array_2d.hpp>
#include <ivl/set.hpp>


void set_sample();

using namespace std;
using namespace ivl;

void set_main()
{
	set_sample();
}

//-------------------------------------------------------------------------------------
void set_sample()
{
#if 0
	//===================================================================
	//RADIX SORT
	//for array
	using ivl::rand;

	std::cout << "USING RADIXSORT" << std::endl << std::endl;
	ivl::array<int> a = rand(10, 1, 10);

	std::cout << "Initial random array with integers: " << std::endl << a << std::endl;
	radixsort(a);
	std::cout << "Sorted with radixsort: " << std::endl << a << std::endl << std::endl;
	//for array, with index
	ivl::size_array ind;
	a = rand(10, 1, 10);
	std::cout << "Initial random array with integers: " << std::endl << a << std::endl;
	radixsort(a,ind);
	std::cout << "Sorted with radixsort: " << std::endl << a << std::endl << " and index: " << ind << std::endl << std::endl;
	//for array of array
	ivl::array<ivl::array<int> > b(10);
	for(size_t i = 0; i < b.length(); i++) b[i] = rand(2, 1, 10);

	std::cout << "Initial random array of array with integers: " << std::endl << b << std::endl;
	radixsort(b);
	std::cout << "Sorted with radixsort: " << std::endl << b << std::endl << std::endl;
 	//for array of array, with index
	for(size_t i = 0; i < b.length(); i++) b[i] = rand(5, 1, 10);
	std::cout << "Initial random array of array with integers: " << std::endl << b << std::endl;
	radixsort(b,ind);
	std::cout << "Sorted with radixsort: " << std::endl << b << std::endl << " and index: " << ind << std::endl << std::endl;

	//===================================================================
	//UNIQUE_COUNT
	std::cout << "USING UNIQUE_COUNT" << std::endl << std::endl;
	//for array
	ivl::array<int> c = rand(10, 1, 10);
	std::cout << "Initial random array with integers: " << std::endl << c << std::endl;
	ivl::size_array f;
	ivl::array<ivl::size_array> i;
	c  = unique_count(c,f,i);
	//	c  = unique_count(c,f);  //could be also called without asking for index (which is faster)
	//	c  = unique_count(c);  //could be also called withou even asking for frequencies
	std::cout << "Array after unique_count: " << std::endl << c << std::endl
	<< "with frequencies: " << f << std::endl << "and index: " << i << std::endl << std::endl;

	//for array of array
	ivl::array<ivl::array<int> > d(10);
	for(size_t i = 0; i < d.length(); i++) d[i] = rand(2, 1, 10);

	std::cout << "Initial random array of array with integers: " << std::endl << d << std::endl;
	d = unique_count(d,f,i);
	std::cout << "Array of array after unique_count: " << std::endl << d << std::endl << "with frequencies: " <<
		f << std::endl << "and index: " << i << std::endl << std::endl;

	//===================================================================
	//INTERSECT
	std::cout << "USING INTERSECT" << std::endl << std::endl;
	//for array
	std::cout << "using intersect_us firstly" << std::endl << std::endl;
	ivl::array<int> k = rand(10, 1, 10);
	ivl::array<int> l = rand(10, 1, 10);

	ivl::size_array f1,f2;
	k = unique_count(k,f1,i);
	l = unique_count(l,f2,i);

	std::cout << "Initial unique and sorted arrays with integers to be intersected: " << std::endl;
	std::cout << "Array 1: " << std::endl << k << std::endl;
	std::cout << "Array 2: " << std::endl << l << std::endl;

	std::cout << "Number of intersecting values found: " << intersect_us(k,l) << std::endl <<std::endl;
	ivl::size_array i1,i2;
	ivl::array<int> common;
	std::cout << "Number of intersecting values found: " << intersect_us(k,l,common,i1,i2) << std::endl  << "common values: " << common << std::endl <<
	"while ids of intersectin elements are: " << std::endl << i1 << std::endl << i2 << std::endl << std::endl;


	std::cout << "If the corresponding frequencies for each element of k and l are " << std::endl
		<< f1 << std::endl << f2 << std::endl
		<< "then the interesection value is: " <<  intersect_us(k,l,f1,f2) << std::endl  << std::endl;

	std::cout << "using intersect now" << std::endl << std::endl;

	k = rand(10, 1, 10);
	l = rand(10, 1, 10);

	std::cout << "Initial random arrays with integers to be intersected: " << std::endl;
	std::cout << "Array 1: " << std::endl << k << std::endl;
	std::cout << "Array 2: " << std::endl << l << std::endl;

	std::cout << "Number of intersecting values found: " << intersect(k,l) << std::endl << std::endl ;

	ivl::array<ivl::size_array> ia,ib;
	ivl::array<int> com;
	std::cout <<	intersect(k,l,com,ia,ib) << std::endl;

	std::cout << "while the common values are : " << com << std::endl << " and the index for a : " << std::endl <<
		ia << std::endl << " and for b : " << std::endl << ib << std::endl << std::endl;


	std::cout << "use intersect with array of array " << std::endl << std::endl;

	ivl::array<ivl::array<int> > q(10),w(10),com2;

	for(size_t i = 0; i < q.length(); i++) q[i] = rand(2, 1, 10);
	for(size_t i = 0; i < w.length(); i++) w[i] = rand(2, 1, 10);

	//for array of array
	std::cout << "Initial random arrays of arrays with integers to be intersected: " << std::endl;
	std::cout << "Array of arrays 1: " << std::endl << q << std::endl;
	std::cout << "Array of arrays 2: " << std::endl << w << std::endl;

	std::cout << std::endl << "Number of intersecting arrays : " << intersect(q,w,com2,ia,ib) << std::endl <<
		"while common arrays are : " << com2 << std::endl << " and the index for a : " << std::endl <<
		ia << std::endl << " and for b : " << std::endl << ib << std::endl << std::endl;
#endif
}

