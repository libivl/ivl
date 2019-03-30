#include <ivl/ivl>

using namespace std;
using namespace ivl;

//-----------------------------------------------------------------------------

 void slice_range()
 {
 	(0, _, 3)[0];        // ok
 	(0, _, 3)[0, _, 1];  // no match for ‘operator[]’
 }

//-----------------------------------------------------------------------------

// void array_method()
// {
// 	typedef array <int> A;
// 	array <A> a = arr(arr(1, 2), arr(3, 4));
// 	a[&A::length]();
// 	// array_core_functions.hpp:243:2: error: function returning a function
// }

//-----------------------------------------------------------------------------

// template <typename A>
// array_2d <int, data::outer <times_class, A, A> >  // where is times_class?
// outer_temp(const A& a)
// {
// 	return outer(a, array <int> (3, 1));  // points to destroyed temporary
//
//		notes: [kimon]
//		not supported yet. will certainly be supported. [medium difficulty]
//		correct syntax will be:
//
// 		return outer(a, permanent(array <int> (3, 1)));  // array will be stored, not referenced.
//
//
//		another, more advanced possible feature: arrays with reference count & smart pointers (OpenCV Mat style)
//		e.g.
//		
//		array<int, smartref> d(3, 1);
//		return outer(a, d);
//			// d allocates the array in the heap. the memory will be freed only when outer(a, d)
//			// and all the other views to it (if they were) are destroyed (refcount = 0)
//
// 	return outer(a, a);                   // ok
// }
//
// void outer_test()
// {
// 	array <int> a(3, 1);
// 	cout << outer_temp(a) << endl;
// }

//-----------------------------------------------------------------------------

 void it_construct()
 {
 	array <int> a(3, 1);

 	// no matching function for call to ‘array<...>::array(...::iterator)’
 	//array <int> b(3, a.begin()); //currently not & may not be supported

	// notes: [kimon]
	
	array <int> b(3, a);           // use this instead
	
	//array <int> c(iter_array(3, a.begin())); // or this for an iterator
	//TODO: iter_array(..) wraps an iterator to an array (view)	
 }

//-----------------------------------------------------------------------------

 template <typename S>
 void sort_const(const S& sort)
 {
 	sort(arr(3, 2, 1));
 	// passing ‘const sort_off_impl<...>’ as ‘this’ argument
 	// of ‘...::operator()(...)’ discards qualifiers
 	// (all ivl_func methods + operators are non-const)
 }

 template <typename S>
 void sort_byval(S sort)
 {
 	sort(arr(3, 2, 1));
	// this case is also clear, and does not need const qualifier on ()
 }
 
 void sort_test()
 {
 	sort_const(ivl::sort[off]);
 	sort_byval(ivl::sort[off]);
 }

//-----------------------------------------------------------------------------

void member_overload()
{
	string x = "x", y = "y";
	array <string> a = arr(x, y);
	int (string::*c) (const string& str) const = &string::compare;
	// cout << first(a[&string::compare](y) == 0) << endl;  // no match for operator[]
	cout << first(a[c](y) == 0) << endl;  // 2, should be 1 - random access bug
}

//-----------------------------------------------------------------------------

int main()
{
	array_2d<size_t> p(3,3,1);
	std::cout << p(idx(0),0) << std::endl;
	std::cout << "--------------------------------------------------------------------------------" << std::endl;

	array<array<int> > a = arr(1,2,3);
	std::cout << a << std::endl;
	std::cout << a + 1 << std::endl;

	
	array_2d<size_t> nn;
	nn(_,0).base();
	
	
//	member_overload();
}
