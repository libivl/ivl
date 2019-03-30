#include <typeinfo>
#include <ivl/ivl>

using namespace std;
using namespace ivl;
using namespace ivl::types;

void test1()
{
	std::cout << "[ t_and<t_true, t_true> ] _<> => ";
	std::cout << lazy<t_and<t_true, t_true> >::eval<tuple<> >::type::value << std::endl;
	
	std::cout << "[ t_and<t_true, t_false> ] _<> => ";
	std::cout << lazy<t_and<t_true, t_false> >::eval<tuple<> >::type::value << std::endl;

	std::cout << "[ t_and<t_true, __1> ] _<t_true> => ";
	std::cout << lazy<t_and<t_true, __1> >::eval<tuple<t_true> >::type::value << std::endl;

	std::cout << "[ t_and<t_true, __1> ] _<t_true> => ";
	std::cout << lazy<t_and<t_true, __1> >::eval<tuple<t_true> >::type::value << std::endl;

	std::cout << "[ t_and<__1, __2> ] _<t_true, t_true> => ";
	std::cout << lazy<t_and<__1, __2> >::eval<tuple<t_true, t_true> >::type::value << std::endl;

	
}

template <class T>
void test2()
{
	std::cout << "[ t_and<t_true, is_integer<__1> > ] _<T> => ";
	std::cout << lazy<t_and<t_true, is_integer<__1> > >::template eval<tuple<T> >::type::value << std::endl;

	std::cout << "[ t_and<t_true, is_floating<__1> > ] _<T> => ";
	std::cout << lazy<t_and<t_true, is_floating<__1> > >::template eval<tuple<T> >::type::value << std::endl;

	std::cout << "[ is_integer<get_value<array<__1> > > ] _<T> => ";
	std::cout << lazy<is_integer<get_value<array<__1> > > >::template eval<tuple<T> >::type::value << std::endl;

	std::cout << "[ is_integer<get_value<array<lazy_stop<__1> > > > ] _<T> => ";
	std::cout << lazy<is_integer<get_value<array<lazy_stop<__1> > > > >::template eval<tuple<T> >::type::value << std::endl;

	std::cout << "t_eq<__1, [ get_value<array<lazy_stop<__1> > > ] _<T> => ";
	std::cout << t_eq<__1, typename lazy<get_value<array<lazy_stop<__1> > > >::template eval<tuple<T> >::type>::type::value << std::endl;

	std::cout << "[ tuple<__2, __1> ] _<T, array<T> > => ";
	std::cout << typename lazy<tuple<__2, __1> >::template eval<tuple<T, array<T> > >::type() << std::endl;
	
}

int main()
{	
	test1();
	std::cout << "with T = int:" << std::endl;
	test2<int>();

	
	return 0;
}